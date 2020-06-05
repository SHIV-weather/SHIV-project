// Author: Sam Hardin
#pragma once
#include "CoreMinimal.h"
#include "Layers/LOCLayer.h"
#include "Layers/HDF5Layer.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "LayerButton.generated.h"

/*!*
 * \class ULOCLayerButton
 * \brief The UI button for the list of LOCLayers
 */
UCLASS()
class ULOCLayerButton : public UUserWidget
{
    GENERATED_BODY()

public:
    /*!
    * \brief Connects the button on the list with the loaded layer data
    * \param filepath the file's name
    * \param layer pointer to the layer data
    * \param factory pointer to the factory widget
    */
    void FillData(FString filepath, ALOCLayer* layer, class UFactoryWidget* factory);

    /*!
    * \brief Updates the layer controls with this button's layer data.
    *   Also updates the factory UI to show which layer is selected
    */
    UFUNCTION()
    void OnClicked();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* Filename;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UButton* Bttn;

    ALOCLayer* layer;

private:
    class UFactoryWidget* factory;
};

/*!*
 * \class UHDF5LayerButton
 * \brief The UI button for the list of HDF5Layers
 */
UCLASS()
class UHDF5LayerButton : public UUserWidget
{
    GENERATED_BODY()

public:
    /*!
    * \brief Connects the button on the list with the loaded layer data
    * \param filepath the file's name
    * \param layer pointer to the layer data
    * \param factory pointer to the factory widget
    */
    void FillData(FString filepath, AHDF5Layer* layer, class UFactoryWidget* factory);

    /*!
    * \brief Updates the layer controls with this button's layer data.
    *   Also updates the factory UI to show which layer is selected
    */
    UFUNCTION()
    void OnClicked();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* Filename;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UButton* Bttn;

    AHDF5Layer* layer;

private:
    class UFactoryWidget* factory;
};