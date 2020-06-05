// Author: Sam Hardin
#pragma once
#include <string>
#include <vector>

#include "Header/Filters/BaseFilter.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Engine/Texture2D.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Engine/DirectionalLight.h"
#include "HDF5Layer.generated.h"

/*!
* \class HDF5Layer
* \brief Manage HDF5 data and display it
*/
UCLASS()
class VIZ_PROJECT00_API AHDF5Layer : public AActor
{
    GENERATED_BODY()

public:
	AHDF5Layer();
	~AHDF5Layer();

	/*!
	* \brief Sets the lights we can manipulate to the input vector
	* \param _lights a vector of directional light pointers
	*/
	void SetLightVec(std::vector<ADirectionalLight*> _lights);

	/*!
	* \brief Load the HDF5 file
	* \param aFilename An FString path to the desired HDF5 file
	*/
	void LoadHDF5FileFunc(FString aFilename);

	/*!
	* \brief Clear the procedural mesh and rebuild with updated parameters
	*/
	void RecreateMesh();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UProceduralMeshComponent* mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float height_factor = 0.005f;
	
	// Latitude / Longitude (Edited in UI)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D lat_window = FVector2D(10.f, 18.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D lon_window = FVector2D(126.f, 134.f);

	UPROPERTY(EditAnywhere)
	UMaterial* mat;

	int min_time[2];
	int max_time[2];

	FVector2D min_latLon;
	FVector2D max_latLon;

private:
	// Load the data into the class
	void LoadData(FString aFilename, float** lon, float** lat, int** hr, int** min);

	// Create mesh to represent data
	int CreateMesh(float const* lon, float const* lat);

	//Helpers for building mesh
	FVector CalcNormal(FVector const& a, FVector const& b, FVector const& c);

	int dimensions[2];

	float* lon = nullptr;
	float* lat = nullptr;
	int* hr = nullptr;
	int* min = nullptr;
	int dim_x = 0;
	int dim_y = 0;

	bool data_loaded = false;
	bool mesh_created = false;

	std::vector<ADirectionalLight*> lights;
	
	// Data
	std::vector<float> data;

	// Filters
	std::vector<size_t> selected_filters;
	std::vector<BaseFilter> filters;
};