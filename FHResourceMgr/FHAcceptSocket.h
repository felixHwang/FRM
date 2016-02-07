#pragma once

#include "FHSocket.h"

class FHAcceptSocket :public FHSocket
{
public:
	FHAcceptSocket();

	FHAcceptSocket(const SOCKET socket);

	virtual ~FHAcceptSocket(void);

	virtual BOOL CreateSocket(UINT uiPort = FH_DEFAULT_CONNECT_PORT);

	virtual BOOL StartConnect(CString cStrAddr = _T("127.0.0.1"));
};
