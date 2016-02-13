#pragma once

#include<map>
#include "FHPublicDefine.h"

// FHAcceptThread

class FHSocket;
class FHAcceptSocket;
class FHCommSocket;
class FHCommThread;

class FHAcceptThread :public CWinThread
{
	DECLARE_DYNCREATE(FHAcceptThread)

public:
	FHAcceptThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHAcceptThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void OnCallBack(WPARAM wParam,LPARAM lParam);

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
	FHAcceptSocket* m_pcAcceptSocket;

	UINT m_szKeyIndex;

	std::map<CString,FH_CommChannelDetail> m_cVecConnectDetail;
};


