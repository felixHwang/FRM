#pragma once

#include<map>
#include <winsock2.h>
#include "FHBaseThread.h"
#include "FHPublicDefine.h"

// FHAcceptThread

class FHCommThread;
class FHAcceptSocket;
class FHCommSocket;

class FHAcceptThread :/* public FHBaseThread,*/public CWinThread
{
	DECLARE_DYNCREATE(FHAcceptThread)

public:
	FHAcceptThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHAcceptThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void OnCallBack(WPARAM wParam,LPARAM lParam);

	virtual void RegisterSocket(const SOCKET& hSocket);
	void RegisterSocket(FHAcceptSocket* pcSocket);
	virtual void UnRegisterSocket();

	FHSocket* GetChannelSocket(CString key);

protected:
	DECLARE_MESSAGE_MAP()
	
	struct FH_CommChannelDetail {
		FH_MachineInfo machineInfo;
		FHCommThread* pcCommThread;
		FHCommSocket* pcCommSocket;
	};


	BOOL m_bQuit;
	SOCKET m_hSocket;
	FHSocket* m_pcSocket;
	FHAcceptSocket* m_pcAcceptSocket;

	UINT m_szKeyIndex;

	std::map<CString,FH_CommChannelDetail> m_cVecConnectDetail;
};


