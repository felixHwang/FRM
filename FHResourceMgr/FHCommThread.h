#pragma once

#include <winsock2.h>
#include "FHPublicDefine.h"

class FHAcceptThread;
class FHCommSocket;
class FHFileBrowser;
// FHCommThread

class FHCommThread : public CWinThread
{
	DECLARE_DYNCREATE(FHCommThread)

protected:
	FHCommThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHCommThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();

	void OnCallBack(WPARAM wParam,LPARAM lParam);

	void RegisterSocket(FHCommSocket* pcSocket);
	virtual void UnRegisterSocket();

	void SetIdentityKey(CString key);
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
	BOOL m_bQuit;
	FH_MachineInfo m_cClientInfo;
	FHCommSocket* m_pcCommSocket;
};


