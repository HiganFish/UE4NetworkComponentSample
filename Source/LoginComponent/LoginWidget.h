// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UButton;
class UEditableTextBox;
class ULoginManager;
/**
 * 
 */
UCLASS()
class LOGINCOMPONENT_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    ULoginWidget(const FObjectInitializer& ObjectInitializer);

    virtual bool Initialize() override;
    UFUNCTION()
    void ButtonSignInEvent();
    UFUNCTION()
    void ButtonSignUpEvent();

    UPROPERTY(Meta = (BindWidget))
    UButton* ButtonSignIn;

    UPROPERTY(Meta = (BindWidget))
    UButton* ButtonSignUp;

    UPROPERTY(Meta = (BindWidget))
    UEditableTextBox* EditableTextBoxUsername;

    UPROPERTY(Meta = (BindWidget))
    UEditableTextBox* EditableTextBoxPassword;

    ULoginManager* LoginManager;
};
