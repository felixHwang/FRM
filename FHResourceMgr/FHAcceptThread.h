#pragma once

#include<map>
#include <winsock2.h>
#include "FHBaseThread.h"

// FHAcceptThread

class FHCommThread;
class FHAcceptSocket;

class FHAcceptThread :/* public FHBaseThread,*/public CWinThread
{
	DECLARE_DYNCREATE(FHAcceptThread)

public:
	FHAcceptThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~FHAcceptThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void OnCallBack(WPARAM wParam,LPARAM lParam);

	virtual void RegisterSocket(const SOCKET& hSocket);
	void RegisterSocket(FHAcceptSocket* pcSocket);
	virtual void UnRegisterSocket();

protected:
	DECLARE_MESSAGE_MAP()


	BOOL m_bQuit;
	SOCKET m_hSocket;
	FHSocket* m_pcSocket;
	FHAcceptSocket* m_pcAcceptSocket;

	std::map<SOCKET,FHCommThread*> m_cVecConnectThead;
};


