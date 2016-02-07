#pragma once
#include "fhsocket.h"

class FHCommSocket :
	public FHSocket
{
public:
	FHCommSocket(void);

	FHCommSocket(const SOCKET socket);

	~FHCommSocket(void);
};
