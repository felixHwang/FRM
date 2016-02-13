#pragma once

#include "FHSocket.h"

class FHAcceptSocket :public FHSocket
{
public:
	FHAcceptSocket();

	FHAcceptSocket(const SOCKET socket);

	virtual ~FHAcceptSocket(void);
};
