// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "LoginWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainHUD::BeginPlay()
{
    if (LoginWidget)
    {
        ULoginWidget* LoginWidgetPtr = CreateWidget<ULoginWidget>(GetWorld(), LoginWidget);
        if (LoginWidget != nullptr)
        {
            LoginWidgetPtr->AddToViewport();
        }
    }

    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (Controller)
    {
        FInputModeUIOnly InputMode;
        Controller->SetInputMode(InputMode);
    }
}