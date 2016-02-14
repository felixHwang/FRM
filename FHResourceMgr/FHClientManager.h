#pragma once

#include "FHPublicDefine.h"

class FHConnectThread;
class FHConnectSocket;

class FHClientManager
{
public:
	FHClientManager(void);
	~FHClientManager(void);

	int StartConnect(const CString cStrAddr, const unsigned int port = FH_DEFAULT_CONNECT_PORT);

	BOOL StopConnect();

	const CString& GetHostName();

	BOOL SendServerDirInfo(CString strFilePath);

private:
	void InitMachineInfo();

	FHConnectThread* m_pcConnectThread;
	FHConnectSocket* m_pcConnectSocket;

	CString m_cHostname;
	CString m_cCurrWorkingPath;
};
