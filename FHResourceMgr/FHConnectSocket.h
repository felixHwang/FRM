#pragma once

#include "FHSocket.h"

// FHConnectSocket ����Ŀ��

class FHConnectSocket : public FHSocket
{
public:
	FHConnectSocket();

	FHConnectSocket(const SOCKET socket);

	virtual ~FHConnectSocket();
};


