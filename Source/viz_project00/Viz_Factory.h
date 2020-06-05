// Author: Sam Hardin
#pragma once
#include <string>
#include <vector>

#include "CoreMinimal.h"
#include "Layers/LOCLayer.h"
#include "Layers/HDF5Layer.h"
#include "UI/FactoryUI.h"
#include "Viz_Factory.generated.h"

/*!
* \class Factory
* \brief Singleton manager to load and manage data from files
*/
UCLASS()
class AViz_Factory : public AActor
{
    GENERATED_BODY()

public:
    AViz_Factory();

    virtual void BeginPlay() override;

    /*!*************************************************************************
    * \brief Loads a file from disk and adds a Layer to the appropriate list
    * \param path The path to the file
    ***************************************************************************/
    UFUNCTION(BlueprintCallable, Category = "FileOpening")
    static bool LoadFile(FString path);

    /*!*************************************************************************
    * \brief Opens a file explorer window
    * \param DialogTitle Title of the dialog box
    * \param DefaultPath The default path the window opens to
    * \param FileTypes Types of files to look for, delimited by '|'
    * \param OutFileNames All files that were opened by the file dialog window
    ***************************************************************************/
    UFUNCTION(BlueprintCallable, Category = "FileOpening")
    static void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);
    
    /*!*************************************************************************
    * \brief Sets the reference to the Factory widget
    * \param in A pointer to the factory widget
    ***************************************************************************/
    UFUNCTION(BlueprintCallable, Category = "FileOpening")
    static void SetUI(UFactoryWidget* in) { self->factory_UI = in; }

    AHDF5Layer* GetHDF5Layer(size_t idx) { return hdf5_data[idx]; }
    std::vector<AHDF5Layer*>& GetHDF5Layers() { return hdf5_data; }
    
    ALOCLayer* GetLOCLayer(size_t idx) { return loc_data[idx]; }
    std::vector<ALOCLayer*>& GetLOCLayers() { return loc_data; }

    ///////////////////////////////////////////////////////////////////////////
    // Variables to send to HDF5 surfaces
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* light0 = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* light1 = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* light2 = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADirectionalLight* light3 = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterial* surfaceMaterial;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class ULOCLayerButton> LOC_UIClass;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UHDF5LayerButton> HDF5_UIClass;

private:
    bool LoadLOCFile(FString path);
    bool LoadHDF5File(FString path);

    // For singleton
    static AViz_Factory* self;

    UFactoryWidget* factory_UI;

    // Light info for the AHDF5 Layers
    std::vector<ADirectionalLight*> lights;
    std::vector<AHDF5Layer*> hdf5_data;
    std::vector<ALOCLayer*> loc_data;
};