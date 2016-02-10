// FHAcceptThread.cpp : ʵ���ļ�
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
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_bQuit = FALSE;
	return TRUE;
}

int FHAcceptThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
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

		if (NULL != m_pcAcceptSocket) {
			if(m_pcAcceptSocket->Accept(hSocket, (SOCKADDR *)&sAddr, &nAddrLen)) {
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
				m_pcAcceptSocket->DisplayErrMessageBox("���տͻ�������ʧ��", m_pcAcceptSocket->GetErrorCode());
			}
		}

		//if (NULL != m_pcSocket) {
		//	hSocket = accept(m_hSocket, (sockaddr *)&sAddr, &nAddrLen); 
		//	/*m_pcSocket->Accept((SOCKADDR *)&sAddr, &nAddrLen);*/
		//	if (INVALID_SOCKET != hSocket) {
		//		FHCommThread* pcThread = (FHCommThread*)AfxBeginThread(RUNTIME_CLASS(FHCommThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		//		if (NULL != pcThread) {
		//			pcThread->RegisterSocket(hSocket);
		//			
		//			// do some thing

		//			m_cVecConnectThead[hSocket] = pcThread;

		//			pcThread->ResumeThread();

		//			pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCOMM, 0);
		//		}
		//	}
		//	else {
		//		int err = GetLastError();
		//	}
		//}
	} // while
}

void FHAcceptThread::RegisterSocket(const SOCKET& hSocket)
{
	m_hSocket = hSocket;
	m_pcSocket = new FHAcceptSocket(hSocket);
}

void FHAcceptThread::RegisterSocket(FHAcceptSocket* pcSocket)
{
	if (NULL != pcSocket) {
		m_pcAcceptSocket = pcSocket;
	}
}

void FHAcceptThread::UnRegisterSocket()
{
	m_pcAcceptSocket = NULL;
}

// FHAcceptThread ��Ϣ�������
