// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Engine/Engine.h"
#include "Network/LoginManager.h"

ULoginWidget::ULoginWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
    LoginManager = CreateDefaultSubobject<ULoginManager>(TEXT("LoginManager"));
}

bool ULoginWidget::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    ButtonSignIn->OnClicked.__Internal_AddDynamic(this, &ULoginWidget::ButtonSignInEvent, 
        FName("ButtonSignInEvent"));

    ButtonSignUp->OnClicked.__Internal_AddDynamic(this, &ULoginWidget::ButtonSignUpEvent,
        FName("ButtonSignUpEvent"));

    return true;
}

void ULoginWidget::ButtonSignInEvent()
{
    FString Username = EditableTextBoxUsername->GetText().ToString();
    FString Password = EditableTextBoxPassword->GetText().ToString();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "SignIn: " + Username + "###" + Password);

        if (LoginManager)
        {
            int Result = LoginManager->Login(Username, Password);
            if (Result == -1)
            {
                GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "SignIn-Result: Error");
            }
        }
     
    }
}

void ULoginWidget::ButtonSignUpEvent()
{
    FString Username = EditableTextBoxUsername->GetText().ToString();
    FString Password = EditableTextBoxPassword->GetText().ToString();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "SignUp: " + Username + "###" + Password);
    }
}