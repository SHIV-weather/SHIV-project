// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseController.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Header/Utils.h"

AControls::AControls()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void AControls::BeginPlay()
{
    Super::BeginPlay();

    SetupInputComponent();
}

void AControls::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent = CastChecked<UInputComponent>(this->GetComponentByClass(UInputComponent::StaticClass()));
    check(InputComponent);

    InputComponent->BindAction("OnMouseClick", IE_Pressed, this, &AControls::OnMouseClick);
    InputComponent->BindAction("OnMouseRelease", IE_Released, this, &AControls::OnMouseRelease);
    InputComponent->BindAction("OnEscape", IE_Pressed, this, &AControls::EscapePressed);

    // TODO: Mouse Wheel Zoom
    //InputComponent->BindAxis("OnMouseUp", this, &AControls::OnMouseUp);
    //InputComponent->BindAxis("OnMouseDown", this, &AControls::OnMouseDown);
}

void AControls::Tick(float DeltaTime)
{
    FVector loc = GetPawn()->GetTransform().GetLocation();

    // Only if the right mouse is pressed
    if (mouseVisible == false)
    {
        // Get mouse delta
        FVector2D currPos;
        GetMousePosition(currPos.X, currPos.Y);

        // Find the proper offsets
        FVector right = GetPawn()->GetActorRightVector();
        FVector up = GetPawn()->GetActorUpVector();
        right.Normalize();
        up.Normalize();

        // update position
        loc += right * -(currPos.X - m_lastMousePos.X) * m_camSpeed;
        loc += up * (currPos.Y - m_lastMousePos.Y) * m_camSpeed;

        // Reset mouse position
        SetMouseLocation(m_lastMousePos.X, m_lastMousePos.Y);
    }

    if (IsInputKeyDown(EKeys::Up))
    {
        m_dist -= 100;

        if (m_dist < 5020)
            m_dist = 5020;
    }
    if (IsInputKeyDown(EKeys::Down))
    {
        m_dist += 100;

        if (m_dist > 13000)
            m_dist = 13000;
    }

    // Find offset
    FVector offset = loc - m_lookAt;
    offset.Normalize();
    offset *= m_dist;

    // new postion
    FVector pos = m_lookAt + offset;

    // move and rotate the actor
    FRotator rotato = UKismetMathLibrary::FindLookAtRotation(pos, m_lookAt);
    GetPawn()->SetActorLocationAndRotation(pos, rotato, false, nullptr, ETeleportType::TeleportPhysics);
}

void AControls::EscapePressed()
{
    UE_LOG(LogTemp, Warning, TEXT("Escape Pressed"));
    FGenericPlatformMisc::RequestExit(true);
}

void AControls::OnMouseClick()
{
    if (mouseVisible == false)
        return;

    if (IsInputKeyDown(EKeys::RightMouseButton))
    {
        GetMousePosition(m_lastMousePos.X, m_lastMousePos.Y);
        ToggleMouse();
    }
}

void AControls::OnMouseRelease()
{
    if (mouseVisible == true)
        return;

    if (WasInputKeyJustReleased(EKeys::RightMouseButton))
    {
        ToggleMouse();
    }
}

void AControls::ToggleMouse()
{
    //SetIgnoreLookInput(!mouseVisible);
    bShowMouseCursor =       !bShowMouseCursor;
    bEnableClickEvents =     !bEnableClickEvents;
    bEnableMouseOverEvents = !bEnableMouseOverEvents;
    mouseVisible =           !mouseVisible;
}