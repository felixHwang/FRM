// FHConnectThread.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHConnectThread.h"
#include "FHConnectSocket.h"
#include "FHMessage.h"


// FHConnectThread

IMPLEMENT_DYNCREATE(FHConnectThread, CWinThread)

FHConnectThread::FHConnectThread()
:m_pcConnectSocket(NULL)
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
	m_bQuit = TRUE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHConnectThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

void FHConnectThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	while (!m_bQuit)
	{
		FHMessage cMsg;
		if (NULL != m_pcConnectSocket) {
			if (m_pcConnectSocket->RecvMessage()) {
				while (m_pcConnectSocket->PopMessage(cMsg)) {
					if (FH_COMM_OPEINFO == cMsg.GetCommandID()) {
						UINT opeCode = cMsg.GetOperatorInfo().operatorCode;
						if (FH_MSG_OPECODE_LSDIR == opeCode) {
							AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_REQFILEINFO, 0, (LPARAM)&cMsg);
						}
					}
				}
			}
			else {
				if (WSAECONNRESET == m_pcConnectSocket->GetErrorCode()) {
					int ret = AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_SERVERDISCONNECT);
					break;
				}
			}
		}

	} // while
}

void FHConnectThread::RegisterSocket(FHConnectSocket* pcSocket)
{
	if (NULL != pcSocket) {
		m_pcConnectSocket = pcSocket;
	}
}

void FHConnectThread::UnRegisterSocket()
{
	m_pcConnectSocket = NULL;
}

void FHConnectThread::StopThread()
{
	m_bQuit = TRUE;
	DWORD dwCode = 0;
	TerminateThread(this->m_hThread, dwCode);
	CloseHandle(this->m_hThread);
}


