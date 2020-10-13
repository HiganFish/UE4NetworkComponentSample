// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Networking.h"
#include "NetworkComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLogNetworkComponent, Log, All);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNetworkComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNetworkComponent();

	/*
	连接到服务器
	@param Ip 点分十进制
	@param Port 80
	@param ConnectionName

	@return 连接成功返回true 否则false
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool ConnectToServer(FString Ip, int32 Port, FString ConnectionName);

	/*
	返回客户端连接状态

	@return 连接中为true 否则为false
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool Connected();


	/*
	关闭连接

	@return 关闭连接成功返回true 失败返回false
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool CloseConnection();

	/*
	发送数据到服务器  不保证完全发送

	@param Data 待发送的数据的指针
	@param Count 待发送数据的长度
	@return 成功返回发送的字节数 失败返回 -1
	*/
	SSIZE_T Send(const uint8* Data, int32 Count);

	/*
	接受数据 不保证完全接收

	@param Data 接受数据的缓冲区
	@param Count 缓冲区长度
	@return 成功返回接收的字节数 失败返回-1
	*/
	SSIZE_T Recv(uint8* Data, int32 Count);

	/*
	发送字符串

	不出错时 保证全部发送

	@return 发送的字节数
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		int32 SendString(const FString& Data);

	/*
	接收数据并存到FString中

	@return 接收到的字符串
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		FString RecvAsString();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	FSocket* ClientSocket_;
	bool Connecting_;

	// 服务器IP
	FString ConnectionIp_;

	// 服务器端口
	int32 ConnectionPort_;

	// 连接名称
	FString ConnectionName_;

	// 发送的总字节数
	int32 SumSendBytes_;

	// 接受的总字节数
	int32 SumRecvBytes_;

	// 连接已经建立的时间
	float ConnectedTime_;

	// 独立的日志ID
	int32 LogId;
};