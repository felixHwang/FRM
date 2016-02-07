#pragma once

#include<map>
#include <winsock2.h>

// FHWinThread

class FHSocket;
class FHWinThread : public CWinThread
{
	DECLARE_DYNCREATE(FHWinThread)

protected:
	FHWinThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHWinThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();

	virtual void OnCallBack(WPARAM wParam,LPARAM lParam);

	virtual void RegisterSocket(const SOCKET& m_hSocket);

	virtual void UnRegisterSocket();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BOOL m_bQuit;
	SOCKET m_hSocket;

protected:
	FHSocket* m_pcSocket;
	FHWinThread* m_pcAcceptThread;
};


