#pragma once

#include "FHPublicDefine.h"

class FHAcceptThread;
class FHAcceptSocket;

class FHServerManager
{
public:
	FHServerManager(void);
	virtual ~FHServerManager(void);
	int StartListen(const CString cStrAddr, const unsigned int port = FH_DEFAULT_CONNECT_PORT);
	BOOL StopListen();
private:
	FHAcceptThread* m_pcAcceptThread;
	FHAcceptSocket* m_pcAcceptSocket;
};
