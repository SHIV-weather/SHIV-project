// Author: Sam Hardin
#pragma once
#include <string>
#include <vector>

#include "Header/Filters/BaseFilter.h"

#include "CoreMinimal.h"
#include "Engine/Classes/Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "LOCLayer.generated.h"

/*!
* \class LOCLayer
* \brief Manage LOC data and display it
*/
UCLASS()
class VIZ_PROJECT00_API ALOCLayer : public AActor
{
    GENERATED_BODY()

public:
	ALOCLayer();

	/*!
	* \brief Called every frame, this handles loading large files over multiple frames
	*/
    virtual void Tick(float DeltaTime) override;

	/*!
	* \brief Load an .loc file into the project
	* \param aFilename path to the .loc file to load
	*/
    UFUNCTION(BlueprintCallable)
    void LoadWWLLNFileFunc(FString aFilename);

	/*!
	* \brief set the center of the window to the given time
	* \param hr the hour
	* \param min the minutes
	*/
	void SetWindowCenter(int hr, int min);
	/*!
	* \brief Set the window size
	* \param valMins the value to set in minutes
	*/
	void SetWindowSize(int valMins);
	/*!
	* \brief return the center of the window in hours
	*/
	float GetWinCenter() { return (winMidHr + winMidMin / 60.f); }
	/*!
	* \brief
	* \return the size of the window in minutes
	*/
	float GetWinSize() { return window_size; }

	/*!
	* \brief Clears all instances of lightning and redraws them from scratch
	*/
	void RedrawLightning();


	UPROPERTY(EditAnywhere)
		FColor render_color = FColor(255, 0, 0);

private:
	//Structure to hold the data for one lightning record
	struct LightningRecord
	{
		LightningRecord() = default;

		int id = -1; //id of mesh in instance_component

		float yr = 0;
		float mon = 0;
		float day = 0;
		float hr = 0;
		float min = 0;
		float sec = 0;
		float lat = 0;
		float lon = 0;
		float err = 0;
		float sta = 0;
	};

	void LoadData();
	void DeleteObjects();
	void CreateObjects();

	//Vector of all lightning records currently loaded
	std::vector<LightningRecord> lightning_records;

	UPROPERTY(EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* instance_component;

	//state tracking to spread work over multiple frames
	FString wwlln_filename;
	bool start_loading = false;
	bool data_loaded = true;
	bool start_creating = false;
	bool objects_created = true;
	size_t num_records = 0;
	TArray<FString> file_strings;


	int c_MAX_MESHES_CREATED_PER_FRAME = 500000;
	int c_MAX_RECORDS_LOADED_PER_FRAME = 500000;

	UPROPERTY(EditAnywhere)
	FVector marker_scale = FVector(20.0f, 20.0f, 20.0f);

	UPROPERTY(EditAnywhere)
	float marker_altitude = 1.f;

	bool use_spherical_coords = true;

	int startHr = 11;
	int startMin = 45;
	int endHr = 13;
	int endMin = 15;

	int winMidHr = 12;
	int winMidMin = 30;

	int window_size = 30;

	// Data
	std::vector<float> data;

	// Filters
	std::vector<size_t> selected_filters;
	std::vector<BaseFilter> filters;
};