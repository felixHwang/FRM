#pragma once

#include <winsock2.h>

class FHAcceptThread;
class FHSocket;
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

	virtual void RegisterSocket(const SOCKET& hSocket);

	virtual void UnRegisterSocket();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BOOL m_bQuit;
	SOCKET m_hSocket;
	FHSocket* m_pcSocket;
};


