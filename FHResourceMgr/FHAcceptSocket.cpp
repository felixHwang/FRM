#include "stdafx.h"
#include "StdAfx.h"
#include "FHAcceptSocket.h"
#include "FHAcceptThread.h"
#include "FHWinThread.h"

#include "FHResourceMgr.h"

FHAcceptSocket::FHAcceptSocket()
:FHSocket(FH_SOCKET_TYPE_SERVER)
{
}

FHAcceptSocket::FHAcceptSocket(const SOCKET socket)
:FHSocket(FH_SOCKET_TYPE_SERVER, socket)
{

}

FHAcceptSocket::~FHAcceptSocket(void)
{
}


BOOL FHAcceptSocket::CreateSocket(UINT uiPort /*= FH_DEFAULT_CONNECT_PORT*/)
{
	return FHSocket::CreateSocket(uiPort);
}

BOOL FHAcceptSocket::StartConnect(CString cStrAddr /*= _T("127.0.0.1")*/)
{
	return FHSocket::StartConnect(cStrAddr);

	/*
	if (FH_SOCKET_TYPE_SERVER == m_eSocketType) {

		//int lenAddr= WideCharToMultiByte(CP_ACP,0,cStrAddr.GetString(),-1,NULL,0,NULL,NULL);  
		//char* pAddr=new char[lenAddr];  
		//WideCharToMultiByte(CP_ACP,0,cStrAddr.GetString(),-1,pAddr,lenAddr,NULL,NULL);  
		// pAddr[lenAddr+1]='\0';  

		unsigned long aip = inet_addr(cStrAddr.GetString());
		SOCKADDR_IN addrServ ;
		addrServ.sin_family = AF_INET;
		addrServ.sin_port = htons(m_szPort);
		addrServ.sin_addr.S_un.S_addr = aip;

		bind(m_hSocket, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));

		if(SOCKET_ERROR == listen(m_hSocket, 20))
		{
			int error = WSAGetLastError();
			return FALSE;
		}

		FHAcceptThread* pcThread = (FHAcceptThread*)AfxBeginThread(RUNTIME_CLASS(FHWinThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		pcThread->RegisterSocket(m_hSocket);

		pcThread->ResumeThread();

		pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTACCEPT, 0);
	}

	return FALSE;
	*/
}