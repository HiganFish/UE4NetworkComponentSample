// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkPackageBase.h"

/**
 * 
 */
class LoginNetworkPackage : public NetworkPackageBase
{
public:

	LoginNetworkPackage() = default;
	LoginNetworkPackage(std::string username, std::string password);

	ssize_t SerializeToBuffer(uint8_t* buffer, size_t BufferLen) override;

	ssize_t DeSerializeFromBuffer(const uint8_t* buffer, size_t buffer_len) override;

	const std::string& GetAuthenticationKey() const;

private:
	static uint32_t login_number;

	std::string authentication_key_;
};

class LoginResultPackage : public NetworkPackageBase
{
public:
	LoginResultPackage();

	ssize_t SerializeToBuffer(uint8_t* buffer, size_t BufferLen) override;

	ssize_t DeSerializeFromBuffer(const uint8_t* buffer, size_t buffer_len) override;

private:
};