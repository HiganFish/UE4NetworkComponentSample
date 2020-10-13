// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOGINCOMPONENT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "AccountManager")
    TSubclassOf<class ULoginWidget> LoginWidget;
};
