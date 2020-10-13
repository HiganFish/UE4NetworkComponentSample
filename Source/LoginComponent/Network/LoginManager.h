// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LoginManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLogLoginManager, Log, All);

class UNetworkComponent;
/**
 * 
 */
UCLASS()
class LOGINCOMPONENT_API ULoginManager : public UObject
{
    GENERATED_BODY()

public:
    ULoginManager();

    UNetworkComponent* LoginNetworkComponent;

    int Login(FString Username, FString Password);
};
