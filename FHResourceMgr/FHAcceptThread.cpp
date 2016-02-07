// FHAcceptThread.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHAcceptThread.h"
#include "FHCommThread.h"
#include "FHSocket.h"
#include "FHAcceptSocket.h"

// FHAcceptThread

IMPLEMENT_DYNCREATE(FHAcceptThread, CWinThread)

FHAcceptThread::FHAcceptThread()
{
	EnableAutomation();
}

FHAcceptThread::~FHAcceptThread()
{
}

BOOL FHAcceptThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_bQuit = FALSE;
	return TRUE;
}

int FHAcceptThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	//m_bQuit = TRUE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHAcceptThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()


void FHAcceptThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	SOCKADDR_IN		sAddr;
	int				nAddrLen;
	SOCKET			hSocket;

	while(!m_bQuit)
	{
		nAddrLen = sizeof(SOCKADDR_IN);
		memset(&sAddr, 0, nAddrLen);
		if (NULL != m_pcSocket) {
			hSocket = accept(m_hSocket, (sockaddr *)&sAddr, &nAddrLen); /*m_pcSocket->Accept((SOCKADDR *)&sAddr, &nAddrLen);*/
			if (INVALID_SOCKET != hSocket) {
				FHCommThread* pcThread = (FHCommThread*)AfxBeginThread(RUNTIME_CLASS(FHCommThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
				if (NULL != pcThread) {
					pcThread->RegisterSocket(hSocket);
					
					// do some thing

					m_cVecConnectThead[hSocket] = pcThread;

					pcThread->ResumeThread();

					pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCOMM, 0);
				}
			}
			else {
				int err = GetLastError();
			}
		}
	} // while
}

void FHAcceptThread::RegisterSocket(const SOCKET& hSocket)
{
	m_hSocket = hSocket;
	m_pcSocket = new FHAcceptSocket(hSocket);
}

void FHAcceptThread::UnRegisterSocket()
{

}

// FHAcceptThread 消息处理程序
