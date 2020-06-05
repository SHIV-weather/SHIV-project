// Author: Sam Hardin
#include "FactoryUI.h"
#include "UI/LayerButton.h"

void UFactoryWidget::AddLOCFile(FString path, ALOCLayer* layer, TSubclassOf<class ULOCLayerButton> LOCUIClass)
{
    if (LOCUIClass) // Check the selected UI class is not NULL
    {
        ULOCLayerButton* locLayer = CreateWidget<ULOCLayerButton>(GetWorld(), LOCUIClass);
        if (!locLayer)
            return;

        WWLLN_Files->AddChild(locLayer);
        locLayer->FillData(path, layer, this);

        if(!locLayer->Bttn->OnClicked.IsBound())
        {
            locLayer->Bttn->OnClicked.AddDynamic(locLayer, &ULOCLayerButton::OnClicked);
        }

        // Select the new option
        locLayer->OnClicked();
    }
}

void UFactoryWidget::AddHDF5File(FString path, AHDF5Layer* layer, TSubclassOf<class UHDF5LayerButton> HDF5UIClass)
{
    if (HDF5UIClass) // Check the selected UI class is not NULL
    {
        UHDF5LayerButton* hdf5Layer = CreateWidget<UHDF5LayerButton>(GetWorld(), HDF5UIClass);
        if (!hdf5Layer)
            return;

        HDF5_Files->AddChild(hdf5Layer);
        hdf5Layer->FillData(path, layer, this);

        if (!hdf5Layer->Bttn->OnClicked.IsBound())
        {
            hdf5Layer->Bttn->OnClicked.AddDynamic(hdf5Layer, &UHDF5LayerButton::OnClicked);
        }

        // Select the new option
        hdf5Layer->OnClicked();
    }
}

void UFactoryWidget::ClearLOCTints()
{
    int32 childCount = WWLLN_Files->GetChildrenCount();

    for (int i = 0; i < childCount; ++i)
    {
        if (ULOCLayerButton* btn = Cast<ULOCLayerButton>(WWLLN_Files->GetChildAt(i)))
        {
            btn->SetColorAndOpacity(FColor(255, 255, 255, 255));
        }
    }
}

void UFactoryWidget::ClearHDF5Tints()
{
    int32 childCount = HDF5_Files->GetChildrenCount();

    for (int i = 0; i < childCount; ++i)
    {
        if (UHDF5LayerButton* btn = Cast<UHDF5LayerButton>(HDF5_Files->GetChildAt(i)))
        {
            btn->SetColorAndOpacity(FColor(255, 255, 255, 255));
        }
    }
}

void UFactoryWidget::SetWWLLN_UI(ULOCLayerWidget* widget)
{
    LOC_widget = widget;
}

void UFactoryWidget::SetHDF5_UI(UHDF5LayerWidget* widget)
{
    HDF5_widget = widget;
}