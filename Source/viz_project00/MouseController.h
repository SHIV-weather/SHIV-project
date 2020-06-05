// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MouseController.generated.h"

/*!*****************************************************************************
 * \class AControls
 * \brief This is the controls that defines the user's interactions
 *
 * This input interpreter is setup to use keyboard & mouse
 *
 ******************************************************************************/
UCLASS()
class VIZ_PROJECT00_API AControls : public APlayerController
{
	GENERATED_BODY()
	
public:
    /*!*************************************************************************
    * Constructor that sets up a few default values to ensure the mouse is
    * visible and mouse events are firing
    ***************************************************************************/
    AControls();

    /*!*************************************************************************
    * Bind the input events to functions
    ***************************************************************************/
    void SetupInputComponent();

    /*!*************************************************************************
    * Called at the beginning of the 'play' session. Calls SetupInputComponent
    ***************************************************************************/
    void BeginPlay();

    /*!*************************************************************************
    * Called every frame. Handles the main movement logic
    ***************************************************************************/
    void Tick(float DeltaTime);

private:
    ///////////////////////////////////////////////////////////////////////////
    // Event Responses
    void EscapePressed();
    void OnMouseClick();
    void OnMouseRelease();

    ///////////////////////////////////////////////////////////////////////////
    // Variables
    FVector2D m_lastMousePos;
    FVector m_lookAt = FVector(0.f, -6000.f, 0.f);
    float m_dist = 10000.f;
    float m_camSpeed = 10.f;

    ///////////////////////////////////////////////////////////////////////////
    // Helpers
    void ToggleMouse();
    bool mouseVisible = true;
};
