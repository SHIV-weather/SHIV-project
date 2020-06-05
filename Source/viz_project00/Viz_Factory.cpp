#include "Viz_Factory.h"
#include <sstream>
#include <algorithm>

#include "Engine.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

// For Singleton
AViz_Factory* AViz_Factory::self = nullptr;

AViz_Factory::AViz_Factory()
{
    hdf5_data = std::vector<AHDF5Layer*>();
    loc_data = std::vector<ALOCLayer*>();

    self = this;
}

void AViz_Factory::BeginPlay()
{
    Super::BeginPlay();

    // Add the lights into the vector
    if(light0 != nullptr)
        lights.push_back(light0);
    if (light1 != nullptr)
        lights.push_back(light1);
    if (light2 != nullptr)
        lights.push_back(light2);
    if (light3 != nullptr)
        lights.push_back(light3);
}

void AViz_Factory::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames)
{
    UEngine* Engine = self->GetGameInstance()->GetEngine();

    if (Engine)
    {
        if (Engine->GameViewport)
        {
            IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
            if (DesktopPlatform)
            {
                //Opening the file picker!
                uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
                DesktopPlatform->OpenFileDialog(nullptr, DialogTitle, DefaultPath, FString(""), FileTypes, SelectionFlag, OutFileNames);
            }
        }
    }
}

bool AViz_Factory::LoadFile(FString path)
{
    // Convert to std:string for easier parsing
    std::string temp = TCHAR_TO_UTF8(*path);
    std::string ext = temp.substr(temp.find_last_of(".") + 1);

    std::transform(ext.begin(), ext.end(), ext.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (ext == "loc")
    {
        return self->LoadLOCFile(path);
    }
    else if (ext == "hdf5")
    {
        return self->LoadHDF5File(path);
    }

    return false;
} 

bool AViz_Factory::LoadLOCFile(FString path)
{
    // Make the new layer
    ALOCLayer* newLayer = GetWorld()->SpawnActor<ALOCLayer>(ALOCLayer::StaticClass());

    // Load the data
    newLayer->LoadWWLLNFileFunc(path);

    // UI
    factory_UI->AddLOCFile(path, newLayer, LOC_UIClass);

    // Add it to our managed memory
    loc_data.push_back(newLayer);
    return true;
}

bool AViz_Factory::LoadHDF5File(FString path)
{
    // Make the new layer
    AHDF5Layer* newLayer = GetWorld()->SpawnActor<AHDF5Layer>(AHDF5Layer::StaticClass());
    newLayer->SetLightVec(lights);
    newLayer->mat = surfaceMaterial;

    // Load the data
    newLayer->LoadHDF5FileFunc(path);

    // UI
    factory_UI->AddHDF5File(path, newLayer, HDF5_UIClass);

    // Add it to our managed memory
    hdf5_data.push_back(newLayer);
    return true;
}