#pragma once

#include "FHPublicDefine.h"

class FHConnectThread;
class FHConnectSocket;

class FHClientManager
{
public:
	FHClientManager(void);
	~FHClientManager(void);

	const CString& GetHostname();

	int StartConnect(const CString cStrAddr, const unsigned int port = FH_DEFAULT_CONNECT_PORT);

	BOOL StopConnect();
	void InitMachineInfo();
	bool SendServerDirInfo(CString strFilename);
private:
	FHConnectThread* m_pcConnectThread;
	FHConnectSocket* m_pcConnectSocket;

	CString m_cHostname;
	CString m_cCurrWorkingPath;
};
