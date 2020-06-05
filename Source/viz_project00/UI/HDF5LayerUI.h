// Author: Sam Hardin
#pragma once
#include "Layers/HDF5Layer.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/SpinBox.h"
#include "HDF5LayerUI.generated.h"

/*!*
 * \class ULOCLayerWidget
 * \brief The UI controls to manipulate WWLLN data at runtime
 */
UCLASS()
class UHDF5LayerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /*!*
    * \brief Redraws the HDF5Mesh
    */
    UFUNCTION(BlueprintCallable)
        void RedrawMesh();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* start_time_TXT;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* end_time_TXT;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* latitude_TXT;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class UTextBlock* longitude_TXT;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class USpinBox* window_lat_min;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class USpinBox* window_lat_max;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class USpinBox* window_lon_min;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
        class USpinBox* window_lon_max;

    /*!*
    * \brief Updates the UI with the given layer data
    * \param layer a pointer to the HDF5Layer
    */
    void SetLayer(AHDF5Layer* layer);

private:
    AHDF5Layer* layer = nullptr;
};