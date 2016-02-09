#pragma once

#include <winsock2.h>

// FHConnectThread

class FHConnectSocket;
class FHSocket;

class FHConnectThread : public CWinThread
{
	DECLARE_DYNCREATE(FHConnectThread)
public:
	FHConnectThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHConnectThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	void OnCallBack(WPARAM wParam,LPARAM lParam);

	void RegisterSocket(FHConnectSocket* pcSocket);

	void RegisterSocket(const SOCKET& hSocket);

	virtual void UnRegisterSocket();

	void StopThread();

protected:
	DECLARE_MESSAGE_MAP()
	BOOL m_bQuit;
	//SOCKET m_hSocket;
	FHSocket* m_pcSocket;
	FHConnectSocket* m_pcConnectSocket;


};


