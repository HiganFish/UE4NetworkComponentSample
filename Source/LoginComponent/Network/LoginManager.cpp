// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginManager.h"
#include "LoginComponent/Network/NetworkComponent.h"
#include "Engine/Engine.h"
#include "LoginNetworkPackage.h"

DEFINE_LOG_CATEGORY(MyLogLoginManager);
#define LOG_INFO(Format, ...)	\
UE_LOG(MyLogLoginManager, Log, TEXT(Format),	\
	__VA_ARGS__)

#define LOG_WARN(Format, ...)	\
UE_LOG(MyLogLoginManager, Warning, TEXT(Format), \
    __VA_ARGS__)

ULoginManager::ULoginManager()
{
    LoginNetworkComponent = CreateDefaultSubobject<UNetworkComponent>(TEXT("LoginNetworkComponent"));
}

int ULoginManager::Login(FString Username, FString Password)
{
    FString LoginIp = "192.168.80.160";
    int32 LoginPort = 8700;

    if (!LoginNetworkComponent->ConnectToServer(LoginIp, LoginPort, "LoginConnection"))
    {
        LOG_WARN("%s", "Can't connect to server");
        return -1;
    }

    LoginNetworkPackage LoginData(TCHAR_TO_ANSI(*Username), TCHAR_TO_ANSI(*Password));
    uint8 Buffer[512];
    SSIZE_T Len = LoginData.SerializeToBuffer(Buffer, sizeof Buffer);
    if (Len <= 0)
    {
        LOG_WARN("%s", "SerializeToBuffer Error");
        return -1;
    }

    SSIZE_T Result = LoginNetworkComponent->Send(Buffer, Len);
    LoginNetworkComponent->CloseConnection();

    return Result;
}