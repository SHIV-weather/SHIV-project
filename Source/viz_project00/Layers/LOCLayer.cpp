#include "LOCLayer.h"
#include "Header/Utils.h"

#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"

ALOCLayer::ALOCLayer() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> tetraMesh(TEXT("/Game/Assets/tetra2"));
	static ConstructorHelpers::FObjectFinder<UMaterial> material(TEXT("/Game/Assets/Materials/red_marker"));

	PrimaryActorTick.bCanEverTick = true;

	// Set up the static Mesh component
	instance_component = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Instanced Mesh Component"));
	instance_component->SetStaticMesh(tetraMesh.Object);
	instance_component->SetMaterial(0, (UMaterialInterface*)material.Object);
}

void ALOCLayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (!data_loaded || start_loading)
		LoadData();

	if (!objects_created || start_creating)
		CreateObjects();
}

void ALOCLayer::LoadWWLLNFileFunc(FString aFilename)
{
	wwlln_filename = aFilename;
	start_loading = true;
	UE_LOG(LogTemp, Warning, TEXT("tempfunc called\n"));
}

void ALOCLayer::SetWindowCenter(int hr, int min)
{
	int halfSize = (window_size / 2);

	winMidHr = hr;
	winMidMin = min;

	startHr = hr;
	startMin = min - halfSize;
	if (startMin < 0)
	{
		int diff = (-startMin / 60) + 1;
		int minDiff = -startMin % 60;

		startHr -= diff;
		startMin = 60 - minDiff;
		if (startHr < 0)
		{
			startHr = 0;
			startMin = 0;
		}
	}

	endHr = hr;
	endMin = min + halfSize;
	if (endMin > 60)
	{
		int diff = endMin / 60;
		int minDiff = endMin % 60;

		endHr += diff;
		endMin = minDiff;
		if (endHr > 24)
		{
			endHr = 24;
			endMin = 0;
		}
	}
}

void ALOCLayer::SetWindowSize(int valMins)
{
	window_size = valMins;
	SetWindowCenter(winMidHr, winMidMin);
}

void ALOCLayer::RedrawLightning()
{
	DeleteObjects();
	CreateObjects();
}

void ALOCLayer::LoadData()
{
	//new load requests will clear previous data
	if (start_loading)
	{
		file_strings.Empty();
		lightning_records.clear();
		start_loading = false;
		data_loaded = false;

		FString full_path = wwlln_filename;

		UE_LOG(LogTemp, Warning, TEXT("Path for wwlln file follows:\n"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *full_path);

		bool load_successful = FFileHelper::LoadFileToStringArray(file_strings, *full_path);
		if (!load_successful)
		{
			UE_LOG(LogTemp, Warning, TEXT("Lightning datafile not found!"));
			data_loaded = true;
		}

		num_records = file_strings.Num();
		lightning_records.reserve(num_records);

		UE_LOG(LogTemp, Log, TEXT("Number of lines read: %i\n"), num_records);
		UE_LOG(LogTemp, Log, TEXT("Begin copying...\n"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Copying records...\n"));
		//Store data in vector of LightningRecord structures
		static size_t i = 0;
		size_t start_i = i;
		while (i < num_records)
		{
			FString line = file_strings[i];
			char const format[] = "%g/%g/%g,%g:%g:%g,%g,%g,%g,%g\n";
			std::string const string{ TCHAR_TO_UTF8(*line) };
			lightning_records.emplace_back();
			LightningRecord& current_record = lightning_records.back();

			sscanf_s(string.c_str(), format,
				&current_record.yr,
				&current_record.mon,
				&current_record.day,
				&current_record.hr,
				&current_record.min,
				&current_record.sec,
				&current_record.lat,
				&current_record.lon,
				&current_record.err,
				&current_record.sta);

			++i;
			if (i - start_i > (size_t)c_MAX_RECORDS_LOADED_PER_FRAME)
			{
				return;
			}
		}

		i = 0;
		data_loaded = true;
		start_creating = true;
		UE_LOG(LogTemp, Log, TEXT("End copying records...\n"));
	}
}

void ALOCLayer::DeleteObjects()
{
	instance_component->ClearInstances();
}

void ALOCLayer::CreateObjects()
{
	//new creation requests clear previous meshes
	if (start_creating)
	{
		instance_component->ClearInstances();
		instance_component->PreAllocateInstancesMemory(num_records);
		start_creating = false;
		objects_created = false;
	}
	else
	{
		//Create mesh instancees in the game world to mark lightning locations
		static size_t i = 0;
		size_t start_i = i;
		size_t meshes_made = 0;
		while (i < num_records)
		{
			LightningRecord& record = lightning_records[i++];

			if (record.hr >= startHr && record.hr <= endHr)
			{
				if (record.hr == startHr && record.min < startMin)
					continue;

				if (record.hr == endHr && record.min > endMin)
					continue;

				// Make the meshes
				FVector location;
				location.X = record.lat;
				location.Y = record.lon;
				location.Z = marker_altitude;
				MapOntoGlobe(location);

				FVector globe_location(0, -6000, 0);
				FVector location_direction = location - globe_location;
				location_direction.Normalize();

				FRotator rotator = location_direction.ToOrientationRotator();
				FRotator last_rotato = rotator;
				FVector no_scale = marker_scale;

				FTransform const transform(rotator, location, no_scale);
				record.id = instance_component->AddInstance(transform);

				++meshes_made;
				if (meshes_made - start_i > (size_t)c_MAX_MESHES_CREATED_PER_FRAME)
				{
					UE_LOG(LogTemp, Log, TEXT("Created %i markers..."), i - start_i);
					return;
				}
			}
		}

		i = 0;
		objects_created = true;
		UE_LOG(LogTemp, Log, TEXT("Marker creation complete."));
	}
}
