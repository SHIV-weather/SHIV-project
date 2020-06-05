// Author: Sam Hardin
#include "UI/HDF5LayerUI.h"

void UHDF5LayerWidget::RedrawMesh()
{
    if (layer == nullptr)
        return;

    layer->lat_window.X = window_lat_min->GetValue();
    layer->lat_window.Y = window_lat_max->GetValue();

    layer->lon_window.X = window_lon_min->GetValue();
    layer->lon_window.Y = window_lon_max->GetValue();

    layer->RecreateMesh();
}

void UHDF5LayerWidget::SetLayer(AHDF5Layer* inLayer)
{
    layer = inLayer;
    if (layer == nullptr)
        return;

    // Reflect the variables
    latitude_TXT->SetText(FText::FromString(FString::Printf(TEXT("Lat: %.2f - %.2f"), layer->min_latLon.X, layer->max_latLon.X)));
    longitude_TXT->SetText(FText::FromString(FString::Printf(TEXT("Lon: %.2f - %.2f"), layer->min_latLon.Y, layer->max_latLon.Y)));

    start_time_TXT->SetText(FText::FromString(FString::Printf(TEXT("Start Time - %02d:%02d"), layer->min_time[0], layer->min_time[1])));
    end_time_TXT->SetText(FText::FromString(FString::Printf(TEXT("End Time - %02d:%02d"), layer->max_time[0], layer->max_time[1])));

    window_lat_min->SetValue(layer->lat_window.X);
    window_lat_max->SetValue(layer->lat_window.Y);

    window_lon_min->SetValue(layer->lon_window.X);
    window_lon_max->SetValue(layer->lon_window.Y);
}