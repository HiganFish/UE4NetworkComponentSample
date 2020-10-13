//
// Created by rjd67 on 2020/10/13.
//
#define UE4

#ifdef UE4
#pragma once
#include "CoreMinimal.h"
#include "string"

#define uint32_t uint32
#define uint8_t uint8
#define ssize_t SSIZE_T
#undef UE4
#else
#include <cstdint>
#include <sys/types.h>
#include <cstring>
#include <string>

#ifndef HIGAN_NETWORKPACKAGEBASE_H
#define HIGAN_NETWORKPACKAGEBASE_H
#endif //HIGAN_NETWORKPACKAGEBASE_H
#endif

// �����
enum PackageCode : uint8_t
{
	HEART_BEAT,
	LOGIN
};


/*
���ݰ�����

�ṩ ���Id ����� �Լ���ID �������ݰ�ͷ

������������ ��������µĳ�Ա���� ����д SerializeToBuffer����

��дSerializeToBuffer����ʱ

1. ���Ե��� SerializeHeaderToBuffer ���л���ͷ����
2. Ȼ���д�������µĳ�Ա���������л�����
3. ������ SerializeCheckSumToBuffer����У���
*/
class NetworkPackageBase
{
public:
	// package_code �����  no �����к�
	NetworkPackageBase(PackageCode package_code, uint32_t no);

	NetworkPackageBase();
	~NetworkPackageBase() = default;

public:

	/*
	���л�����ͷ Body У���
	������д��������Body���ֵ�����
	���л�Bodyǰ����SerializeHeaderToBuffer����ͷ��
	���к����SerializeCheckSumToBuffer����β��
	@parma BodySize Body���ֳ���
	@parma buffer ��Ż�������ָ��
	@parma buffer_len ����������
	@return �ɹ� ���浽�������е����ݳ���  ʧ�ܷ���-1
	*/
	virtual ssize_t SerializeToBuffer(uint8_t* buffer, size_t buffer_len);

protected:

	/*
	���л� ͷ�����ݵ�������
	4 PackageBytes_  ���ܴ�С
	4 player_id_ ���ID
	1 PackageCode_ �����
	4 no_ ��ID
	4 CheckSum �����л�ͷ����ʱ�� ��ʼ��Ϊ0
	xxx Body
	4 CheckSum
	@parme body_size ���ݲ����ֽ���
	@parme buffer ������л������ݵĻ�����
	@parme BufferSize ����������
	@return �ɹ��������л����ֽ��� ʧ�ܷ���-1
	*/
	ssize_t SerializeHeaderToBuffer(size_t body_size, uint8_t* buffer, size_t buffer_len);

	/*
	����У��� �����丽��Header��
	@parma data ����У��͵�����ָ��
	@parma data_len ����У��͵����ݳ���
	*/
	void SerializeCheckSumToBuffer(uint8_t* data, size_t data_len);

public:

	/*
	��Buffer�з����л�����
	@return �ɹ����ؽ��������ݳ��� ���ݹ����޷�����0 �������󷵻�-1
	*/
	virtual ssize_t DeSerializeFromBuffer(const uint8_t* buffer, size_t buffer_len);

protected:

	/*
	�����л�ͷ�����ݲ�����
	@parma data ����ָ��
	@parma data_len ���ݳ���
	@param body_len ����body���ȵ�ָ�� ����Ҫ��Ϊ��
	@return �����ɹ����ؽ������ֽ���  ���Ȳ�������0 У����󷵻�-1
	*/
	ssize_t DeSerializeHeaderFromBuffer(const uint8_t* data, size_t data_len, size_t* body_len);

protected:
	const static size_t BUFFER_LEN = 4096;

	// ������У���
	const static size_t CHECKSUM_SIZE = 4;

	const static size_t HEADER_SIZE = 4 + 4 + 1 + 4 + CHECKSUM_SIZE;

	/*
	У������
	@param data ��Ŵ�У�����ݵ�ָ��
	@param package_size ���ݰ��ĳ���
	@return ��ȷ����true  ���򷵻�false
	*/
	bool CheckData(const uint8_t* data, size_t package_size);
private:

	// �����л�������ֽ���
	// uint32_t PackageSize_;

	uint32_t player_id_;

	// ��������
	PackageCode package_code_;

	// �������
	uint32_t no_;

	// У��� ʹ��BCC�㷨 �������ֽڲ���������� ������У��  ���л�ʱӦ����Header��
	// uint32_t CheckSum_;

};
