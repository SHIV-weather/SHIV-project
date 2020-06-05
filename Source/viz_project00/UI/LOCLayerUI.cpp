// Author: Sam Hardin
#include "LOCLayerUI.h"

void ULOCLayerWidget::SetVariables(class USpinBox* center, class USpinBox* size)
{
    winCenter = center;
    winSize = size;
}

float ULOCLayerWidget::WindowTime(USpinBox* time_WinCenter)
{
    // Sanity check
    if (layer == nullptr)
        return 0.0f;

    float val = time_WinCenter->GetValue();

    // Get the time
    int hr = (int)val;
    float minPercent = val - (float)hr;
    int min = (int)(minPercent * 60.0f);

    layer->SetWindowCenter(hr, min);
    time_TXT->SetText(FText::FromString(FString::Printf(TEXT("Time - %02d:%02d"), hr, min)));

    return val;
}

float ULOCLayerWidget::WindowSize(USpinBox* time_WinSize)
{
    // Sanity check
    if (layer == nullptr)
        return 0.0f;

    float val = time_WinSize->GetValue();

    layer->SetWindowSize(val);

    return val;
}

void ULOCLayerWidget::RedrawLighting()
{
    // Sanity check
    if (layer == nullptr)
        return;

    layer->RedrawLightning();
}

void ULOCLayerWidget::SetLayer(ALOCLayer* inLayer)
{
    layer = inLayer;
    if (layer == nullptr)
        return;

    winCenter->SetValue(layer->GetWinCenter());
    winSize->SetValue(layer->GetWinSize());

    float val = winCenter->GetValue();

    // Get the time
    int hr = (int)val;
    float minPercent = val - (float)hr;
    int min = (int)(minPercent * 60.0f);

    time_TXT->SetText(FText::FromString(FString::Printf(TEXT("Time - %02d:%02d"), hr, min)));
}
