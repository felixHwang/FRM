#pragma once

#include "FHSocket.h"

// FHConnectSocket ÃüÁîÄ¿±ê

class FHConnectSocket : public FHSocket
{
public:
	FHConnectSocket();

	FHConnectSocket(const SOCKET socket);

	virtual ~FHConnectSocket();
};


