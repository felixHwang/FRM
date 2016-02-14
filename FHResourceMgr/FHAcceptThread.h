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
	void RemoveCommChannel(CString key);
	void StopThread();

protected:
	DECLARE_MESSAGE_MAP()

private:
	struct FH_CommChannelDetail {
		FH_CommChannelDetail()
		{
			pcCommThread = NULL;
			pcCommSocket = NULL;
		}

		FH_MachineInfo machineInfo;
		FHCommThread* pcCommThread;
		FHCommSocket* pcCommSocket;
	};

	std::map<CString,FH_CommChannelDetail> m_cMapConnectDetail;
	FHAcceptSocket* m_pcAcceptSocket;
	BOOL m_bQuit;
	UINT m_szKeyIndex;
};


