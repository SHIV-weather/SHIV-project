// Author: Sam Hardin
#include "LayerButton.h"
#include "UI/FactoryUI.h"
#include "Misc/Paths.h"

void ULOCLayerButton::FillData(FString filepath, ALOCLayer* inLayer, UFactoryWidget* inFactory)
{
    FString file = FPaths::GetBaseFilename(filepath);
    Filename->SetText(FText::FromString(file));

    // TODO: Make Tooltip
    //Filename->SetToolTip(FText::FromString(file));

    factory = inFactory;
    layer = inLayer;
}

void ULOCLayerButton::OnClicked()
{
    factory->ClearLOCTints();
    this->SetColorAndOpacity(FColor(128, 128, 128, 255));

    factory->LOC_widget->SetLayer(layer);
}

void UHDF5LayerButton::FillData(FString filepath, AHDF5Layer* inLayer, UFactoryWidget* inFactory)
{
    FString file = FPaths::GetBaseFilename(filepath);
    Filename->SetText(FText::FromString(file));

    factory = inFactory;
    layer = inLayer;
}

void UHDF5LayerButton::OnClicked()
{
    factory->ClearHDF5Tints();
    this->SetColorAndOpacity(FColor(128, 128, 128, 255));

    factory->HDF5_widget->SetLayer(layer);
}