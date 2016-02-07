#include "StdAfx.h"
#include "FHSocket.h"
#include "FHWinThread.h"
#include "FHPublicDefine.h"
#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHConnectThread.h"
#include "FHAcceptThread.h"

FHSocket::FHSocket(const FH_SOCKET_TYPE type)
:m_eSocketType(type)
,m_hSocket(-1)
{
}

FHSocket::FHSocket(const FH_SOCKET_TYPE type, const SOCKET socket)
:m_eSocketType(type)
,m_hSocket(socket)
{
	WSADATA sWSAData;
	memset(&sWSAData, 0, sizeof(WSADATA));
	//int nErrCode = WSAStartup(0x0101, &sWSAData);
}

FHSocket::~FHSocket(void)
{
}

BOOL FHSocket::CreateSocket(UINT uiPort /*= FH_DEFAULT_CONNECT_PORT*/)
{
	//AfxSocketInit();
	m_szPort = uiPort;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);

	return TRUE;

}

BOOL FHSocket::StartConnect(CString cStrAddr /*= _T("127.0.0.1")*/)
{

	m_cAddr = cStrAddr;
	m_cAddr = "127.0.0.1";

	//int lenAddr= WideCharToMultiByte(CP_ACP,0,cStrAddr.GetString(),-1,NULL,0,NULL,NULL);  
	//char* pAddr=new char[lenAddr];  
	//WideCharToMultiByte(CP_ACP,0,cStrAddr.GetString(),-1,pAddr,lenAddr,NULL,NULL);  

	unsigned long aip = inet_addr(m_cAddr.GetString());
	SOCKADDR_IN socketAddr ;
	memset(&socketAddr, 0, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(m_szPort);
	if (FH_SOCKET_TYPE_SERVER == m_eSocketType)
		socketAddr.sin_addr.S_un.S_addr = ADDR_ANY;
	else if (FH_SOCKET_TYPE_CLIENT == m_eSocketType)
		socketAddr.sin_addr.S_un.S_addr = aip;



	//delete[] pAddr;


	if (FH_SOCKET_TYPE_SERVER == m_eSocketType) {

		bind(m_hSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));
		int error = WSAGetLastError();

		if(SOCKET_ERROR == listen(m_hSocket, 10))
		{
			int error = WSAGetLastError();
			return FALSE;
		}

		FHAcceptThread* pcThread = (FHAcceptThread*)AfxBeginThread(RUNTIME_CLASS(FHAcceptThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		pcThread->RegisterSocket(m_hSocket);

		pcThread->ResumeThread();

		pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTACCEPT, 0);
	}
	else if (FH_SOCKET_TYPE_CLIENT == m_eSocketType) {

		int ret =  connect(m_hSocket, (sockaddr*)&socketAddr, sizeof(SOCKADDR));
		if (0 == ret) {

			FHConnectThread* pcThread = (FHConnectThread*)AfxBeginThread(RUNTIME_CLASS(FHConnectThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

			pcThread->RegisterSocket(m_hSocket);

			pcThread->ResumeThread();

			pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCONNECT, 0);
		}
		else {
			return FALSE;
		}
	}

	return TRUE;

}

BOOL FHSocket::CloseSocket()
{
	closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;
	return TRUE;
}

BOOL FHSocket::SendMessage(const FHMessage& msg)
{
	INT lenBuffer = 1024*1024;
	TCHAR* pBuffer = new TCHAR[lenBuffer];

	char* pWrite = pBuffer;
	UINT tmp = msg.GetCommandID();
	memcpy(pWrite, &tmp, sizeof(tmp));
	pWrite += sizeof(tmp);

	send(m_hSocket, pBuffer, sizeof(tmp), 0);
	

	FH_Command_ConfigInfo configInfo = msg.GetConfigInfo();
	INT totalSize = sizeof(INT)*2 + configInfo.lenHostname;
	pWrite = pBuffer;
	memcpy(pWrite, &totalSize, sizeof(totalSize));
	pWrite += sizeof(totalSize);

	tmp = configInfo.lenHostname;
	memcpy(pWrite, &tmp, sizeof(tmp));
	pWrite += sizeof(tmp);

	memcpy(pWrite, configInfo.hostname.GetString(), configInfo.lenHostname);

	send(m_hSocket, pBuffer, totalSize, 0);

	delete[] pBuffer;

	return TRUE;
}

BOOL FHSocket::RecvMessage(FHMessage& msg)
{
	INT lenBuffer = 1024*1024;
	TCHAR* pBuffer = new TCHAR[lenBuffer];

	
	int result = recv(m_hSocket, pBuffer, lenBuffer, 0);
	if (SOCKET_ERROR == result) {
		return FALSE;
	}
	else {
		// 构造消息命令
		UINT commandID = *(UINT*)pBuffer;
		if (FH_COMM_CONFIGINFO == commandID) {
			result = recv(m_hSocket, pBuffer, lenBuffer, 0);
			if (SOCKET_ERROR != result) {
				// hostname length
				INT totalSize = *(INT*)pBuffer;
				INT lenHostname = *(((INT*)pBuffer)+1);
				if (result != totalSize) {
					return FALSE;
				}
				CString hostname((char*)((UINT*)pBuffer+2),lenHostname);
				msg.SetCommandID(commandID);
				msg.SetConfigInfo(FH_Command_ConfigInfo(lenHostname,hostname));
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

SOCKET FHSocket::Accept(sockaddr* addr, int* addrlen)
{
	return accept(m_hSocket, addr, addrlen);
}
