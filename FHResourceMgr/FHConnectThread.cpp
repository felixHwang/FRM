// FHConnectThread.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHConnectThread.h"
#include "FHConnectSocket.h"
#include "FHMessage.h"
#include "FHSocket.h"


// FHConnectThread

IMPLEMENT_DYNCREATE(FHConnectThread, CWinThread)

FHConnectThread::FHConnectThread()
{
}

FHConnectThread::~FHConnectThread()
{
}

BOOL FHConnectThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_bQuit = FALSE;
	return TRUE;
}

int FHConnectThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	//m_bQuit = TRUE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHConnectThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

void FHConnectThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	SOCKADDR_IN		sAddr;
	int				nAddrLen;
	SOCKET			hSocket;
	int bufferLen = 1024*1024;
	//char* pBuffer = new char[bufferLen];



	while (!m_bQuit)
	{
		FHMessage cMsg;
		if (NULL != m_pcSocket) {
			if (m_pcSocket->RecvMessage()) {
				
			}
		}
	} // while

}

void FHConnectThread::RegisterSocket(const SOCKET& hSocket)
{
	m_hSocket = hSocket;
	m_pcSocket = new FHConnectSocket(hSocket);
}

void FHConnectThread::UnRegisterSocket()
{

}

// FHConnectThread 消息处理程序
