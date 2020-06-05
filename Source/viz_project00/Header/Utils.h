#pragma once

#include "CoreMinimal.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"

float   const globe_radius = 5000.f;
FVector const globe_center = FVector(0, -6000.f, 0);

// Macro to do a print to screen
#define PRINT(text)				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)
#define PRINTF(format, ...)		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__), false)

#define WARN(text)				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow,text)
#define WARNF(format, ...)		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__), false)

#define ERROR(text)				if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)
#define ERRORF(format, ...)		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__), false)

/*!
* \brief Maps latitude and longitude to the globe inplace on the input
* \param aLatLonAltitude Latitude and Longitude to map to the globe	
*/
static void MapOntoGlobe(FVector& aLatLonAltitude)
{
	float const pi = PI;
	float const lat = aLatLonAltitude.X * pi / 180.f;
	float const lon = aLatLonAltitude.Y * pi / 180.f;

	float altValue = aLatLonAltitude.Z;
	if (aLatLonAltitude.Z < 0.0)
		altValue = -10.0;

	float const radius = altValue + globe_radius;
	float const x = radius * cosf(lat) * sinf(lon);
	float const y = radius * cosf(lat) * cosf(lon);
	float const z = radius * sinf(lat);
	aLatLonAltitude = FVector(x, y, z);
	aLatLonAltitude += globe_center;
}