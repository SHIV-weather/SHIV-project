// Author: Sam Hardin
#pragma once
#include "CoreMinimal.h"

#include "Layers/LOCLayer.h"
#include "Layers/HDF5Layer.h"
#include "UI/LOCLayerUI.h"
#include "UI/HDF5LayerUI.h"

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "FactoryUI.generated.h"

/*!*
 * \class UFactoryWidget
 * \brief The UI controls that handle the lists of loaded files
 */
UCLASS()
class UFactoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /*!
    * \brief Adds an LOCLayer to the list
    * \param path The file path on disk
    * \param layer a pointer to the data layer
    * \param LOCUIClass a button to instantiate
    */
    void AddLOCFile(FString path, ALOCLayer* layer, TSubclassOf<class ULOCLayerButton> LOCUIClass);
    /*!
    * \brief Adds an HDF5Layer to the list
    * \param path The file path on disk
    * \param layer a pointer to the data layer
    * \param HDF5UIClass a button to instantiate
    */
    void AddHDF5File(FString path, AHDF5Layer* layer, TSubclassOf<class UHDF5LayerButton> HDF5UIClass);

    /*!
    * \brief Clears tints on the LOCLayer buttons
    */
    void ClearLOCTints();

    /*!
    * \brief Clears tints on the HDF5Layer buttons
    */
    void ClearHDF5Tints();

    UFUNCTION(BlueprintCallable, Category = "UI_Hooks")
        void SetWWLLN_UI(ULOCLayerWidget* widget);

    UFUNCTION(BlueprintCallable, Category = "UI_Hooks")
    void SetHDF5_UI(UHDF5LayerWidget* widget);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UScrollBox* HDF5_Files;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UScrollBox* WWLLN_Files;

    ULOCLayerWidget* LOC_widget;
    UHDF5LayerWidget* HDF5_widget;

private:
    
};