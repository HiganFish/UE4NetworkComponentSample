// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkComponent.h"
#include "Containers/UnrealString.h"
#include "Engine/Engine.h"
#include "NetworkPackageBase.h"

DEFINE_LOG_CATEGORY(MyLogNetworkComponent);

#define LOG_INFO(Format, ...)	\
UE_LOG(MyLogNetworkComponent, Log, TEXT(Format),	\
	__VA_ARGS__)

#define LOG_WARN(Format, ...)	\
UE_LOG(MyLogNetworkComponent, Warning, TEXT(Format),	\
	__VA_ARGS__)

// Sets default values for this component's properties
UNetworkComponent::UNetworkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	ClientSocket_ = nullptr;
	ConnectionPort_ = 0;
	Connecting_ = false;

	SumSendBytes_ = 0;
	SumRecvBytes_ = 0;
	ConnectedTime_ = 0;

	LogId = GetUniqueID();
}

// Called when the game starts
void UNetworkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UNetworkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (Connecting_)
	{
		ConnectedTime_ += DeltaTime;

		if (GEngine)
		{
			FString Log = FString::Printf(TEXT("Connction: %s send %0.2f bytes/s, recv %0.2f bytes/s"),
				*ConnectionName_, SumSendBytes_ / ConnectedTime_, SumRecvBytes_ / ConnectedTime_);

			GEngine->AddOnScreenDebugMessage(LogId, 2.0f, FColor::Red, Log);
		}
	}
}

bool UNetworkComponent::ConnectToServer(FString Ip, int32 Port, FString ConnectionName)
{
	if (!Connecting_)
	{
		FIPv4Address IpAddress;
		FIPv4Address::Parse(Ip, IpAddress);

		TSharedPtr<FInternetAddr> NetworkAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		NetworkAddr->SetIp(IpAddress.Value);
		NetworkAddr->SetPort(Port);

		ClientSocket_ = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, ConnectionName, false);

		if (ClientSocket_->Connect(*NetworkAddr))
		{
			Connecting_ = true;
			ConnectionIp_ = Ip;
			ConnectionPort_ = Port;
			ConnectionName_ = ConnectionName;

			LOG_INFO("Connection: %s connect to %s:%d success",
				*ConnectionName_, *ConnectionIp_, ConnectionPort_);

			return true;
		}
		else
		{
			Connecting_ = false;

			LOG_WARN("Connection: %s connect to %s:%d failed",
				*ConnectionName_, *ConnectionIp_, ConnectionPort_);

			return false;
		}
	}
	else
	{
		LOG_WARN("Connection: %s has connected to %s:%d can't connect to %s:%d",
			*ConnectionName_, *ConnectionIp_, ConnectionPort_, *Ip, Port);

		return false;
	}

	return false;
}

bool UNetworkComponent::Connected()
{
	return Connecting_;
}

bool UNetworkComponent::CloseConnection()
{
	if (Connecting_)
	{
		Connecting_ = false;

		LOG_INFO("Close connection: %s", *ConnectionName_);

		return ClientSocket_->Close();
	}

	return true;
}

SSIZE_T UNetworkComponent::Send(const uint8* Data, int32 Count)
{
	if (!Data || !Connecting_)
	{
		return -1;
	}

	int32 ResultSendBytes = 0;

	if (!ClientSocket_->Send(Data, Count, ResultSendBytes))
	{
		CloseConnection();
		LOG_WARN("Connection: %s send data error", *ConnectionName_);
		return -1;
	}

	LOG_INFO("Connection: %s send data %d bytes", *ConnectionName_, ResultSendBytes);

	SumSendBytes_ += ResultSendBytes;

	return ResultSendBytes;
}


SSIZE_T UNetworkComponent::Recv(uint8* Data, int32 Count)
{
	if (!Data || !Connecting_)
	{
		return -1;
	}

	int32 BytesRecvResult = 0;
	uint32 PendingData = 0;

	// 不使用HasPendingData进行判断 如果没有数据可读 则会阻塞
	if (ClientSocket_->HasPendingData(PendingData))
	{
		if (!ClientSocket_->Recv(Data, Count, BytesRecvResult))
		{
			CloseConnection();
			LOG_WARN("Connection: %s recv data error", *ConnectionName_);
			return -1;
		}

		LOG_INFO("Connection: %s recv data %d bytes", *ConnectionName_, BytesRecvResult);
	}

	SumRecvBytes_ += BytesRecvResult;

	return BytesRecvResult;
}

int32 UNetworkComponent::SendString(const FString& Data)
{
	int32 BufferLen = Data.Len();

	// FString中可能是宽字符 需要转换成ANSI字符
	uint8* DataBuffer = (uint8*)TCHAR_TO_ANSI(*Data);

	int32 SumSendBytes = 0;

	while (SumSendBytes < BufferLen)
	{
		int32 SendBytes = Send(DataBuffer + SumSendBytes, BufferLen - SumSendBytes);

		if (SendBytes == -1)
		{
			return SumSendBytes;
		}

		SumSendBytes += SendBytes;
	}

	return SumSendBytes;
}

FString UNetworkComponent::RecvAsString()
{
	char Buffer[4096]{};
	int32 Len = Recv((uint8*)Buffer, sizeof Buffer - 1);
	if (Len == -1)
	{
		return FString();
	}

	return FString(Len, Buffer);
}