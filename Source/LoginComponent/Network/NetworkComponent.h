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
	���ӵ�������
	@param Ip ���ʮ����
	@param Port 80
	@param ConnectionName

	@return ���ӳɹ�����true ����false
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool ConnectToServer(FString Ip, int32 Port, FString ConnectionName);

	/*
	���ؿͻ�������״̬

	@return ������Ϊtrue ����Ϊfalse
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool Connected();


	/*
	�ر�����

	@return �ر����ӳɹ�����true ʧ�ܷ���false
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		bool CloseConnection();

	/*
	�������ݵ�������  ����֤��ȫ����

	@param Data �����͵����ݵ�ָ��
	@param Count ���������ݵĳ���
	@return �ɹ����ط��͵��ֽ��� ʧ�ܷ��� -1
	*/
	SSIZE_T Send(const uint8* Data, int32 Count);

	/*
	�������� ����֤��ȫ����

	@param Data �������ݵĻ�����
	@param Count ����������
	@return �ɹ����ؽ��յ��ֽ��� ʧ�ܷ���-1
	*/
	SSIZE_T Recv(uint8* Data, int32 Count);

	/*
	�����ַ���

	������ʱ ��֤ȫ������

	@return ���͵��ֽ���
	*/
	UFUNCTION(BlueprintCallable, Category = "NetworkComponent")
		int32 SendString(const FString& Data);

	/*
	�������ݲ��浽FString��

	@return ���յ����ַ���
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

	// ������IP
	FString ConnectionIp_;

	// �������˿�
	int32 ConnectionPort_;

	// ��������
	FString ConnectionName_;

	// ���͵����ֽ���
	int32 SumSendBytes_;

	// ���ܵ����ֽ���
	int32 SumRecvBytes_;

	// �����Ѿ�������ʱ��
	float ConnectedTime_;

	// ��������־ID
	int32 LogId;
};