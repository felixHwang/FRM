#include "StdAfx.h"
#include "FHBaseThread.h"

FHBaseThread::FHBaseThread(void)
:m_bQuit(FALSE)
,m_hSocket(INVALID_SOCKET)
,m_pcSocket(NULL)

{
}

FHBaseThread::~FHBaseThread(void)
{
}

/*
void FHBaseThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{

	int i = 0;

	/*
	SOCKADDR_IN		sAddr;
	int				nAddrLen;
	SOCKET			hSocket;

	while(!m_bQuit)
	{
		nAddrLen = sizeof(SOCKADDR_IN);
		memset(&sAddr, 0, nAddrLen);
		hSocket = accept(m_hSocket, (SOCKADDR *)&sAddr, &nAddrLen);
		if (INVALID_SOCKET != hSocket) {
			FHWinThread* pcThread = (FHWinThread*)AfxBeginThread(RUNTIME_CLASS(FHWinThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

			pcThread->m_hSocket = m_hSocket;
			// do some thing

			//m_cVecConnectThead[hSocket] = pcThread;
		}
		else {
			
		}
	} // while
	*/
//}
//*/