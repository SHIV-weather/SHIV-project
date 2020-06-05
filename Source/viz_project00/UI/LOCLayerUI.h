// Author: Sam Hardin
#pragma once
#include "Layers/LOCLayer.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/SpinBox.h"
#include "LOCLayerUI.generated.h"

/*!*
 * \class ULOCLayerWidget
 * \brief The UI controls to manipulate WWLLN data at runtime
 */
UCLASS()
class ULOCLayerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /*!*
    * \brief Updates the UI with the given layer data
    * \param center a pointer a UI spinbox
    * \param size a pointer a UI spinbox
    */
    UFUNCTION(BlueprintCallable)
    void SetVariables(class USpinBox* center, class USpinBox* size);

    /*!*
    * \brief Updates the layer's center
    * \param time_WinCenter a pointer to a spin box in the UI
    */
    UFUNCTION(BlueprintCallable)
    float WindowTime(USpinBox* time_WinCenter);

    /*!*
    * \brief Updates the layer's size 
    * \param time_WinSize A pointer to a spin box in the UI
    */
    UFUNCTION(BlueprintCallable)
    float WindowSize(USpinBox* time_WinSize);

    /*!*
    * \brief Redraws the lightning objects
    */
    UFUNCTION(BlueprintCallable)
    void RedrawLighting();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* time_TXT;

    class USpinBox* winCenter;
    class USpinBox* winSize;

    /*!*
    * \brief Updates the UI with the given layer data
    * \param layer a pointer to the LOCLayer
    */
    void SetLayer(ALOCLayer* layer);

private:
    ALOCLayer* layer = nullptr;
};