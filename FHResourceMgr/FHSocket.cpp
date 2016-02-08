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
,m_pcRecvBuffer(NULL)
,m_pcRemainBuffer(NULL)
,m_iRemainPos(0)
{
	m_pcRecvBuffer = new char[SO_RCVBUF];
	m_pcRemainBuffer = new char[SO_RCVBUF];
}

FHSocket::FHSocket(const FH_SOCKET_TYPE type, const SOCKET socket)
:m_eSocketType(type)
,m_hSocket(socket)
,m_pcRecvBuffer(NULL)
,m_pcRemainBuffer(NULL)
,m_iRemainPos(0)
{
	m_pcRecvBuffer = new char[SO_RCVBUF];
	m_pcRemainBuffer = new char[SO_RCVBUF];
	//WSADATA sWSAData;
	//memset(&sWSAData, 0, sizeof(WSADATA));
	//int nErrCode = WSAStartup(0x0101, &sWSAData);
}

FHSocket::~FHSocket(void)
{
	if (NULL != m_pcRecvBuffer) {
		delete[] m_pcRecvBuffer;
		m_pcRecvBuffer = NULL;
	}
	if (NULL != m_pcRemainBuffer) {
		delete[] m_pcRemainBuffer;
		m_pcRemainBuffer = NULL;
	}
}

BOOL FHSocket::CreateSocket(UINT uiPort /*= FH_DEFAULT_CONNECT_PORT*/)
{
	//AfxSocketInit();
	m_szPort = uiPort;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	BOOL bNodelay=TRUE;
	BOOL bDebug=TRUE;
	setsockopt(m_hSocket, IPPROTO_TCP,TCP_NODELAY,(const char*)&bNodelay,sizeof(BOOL));
	setsockopt(m_hSocket, SOL_SOCKET,SO_DEBUG,(const char*)&bDebug,sizeof(BOOL));   

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

BOOL FHSocket::SendMessage(const FHMessage& cMsg)
{
	INT lenBuffer = 1024*1024;
	TCHAR* pBuffer = new TCHAR[lenBuffer];

	
	int tmp = cMsg.GetCommandID();
	char* pWrite = m_pcRecvBuffer + sizeof(int);
	memcpy(pWrite, &tmp, sizeof(tmp));
	pWrite += sizeof(int);

	if (FH_COMM_MACHINEINFO == tmp) {
		tmp = cMsg.GetMachineInfo().hostname.GetLength();
		memcpy(pWrite, &tmp, sizeof(int));
		pWrite += sizeof(int);
		memcpy(pWrite,  cMsg.GetMachineInfo().hostname.GetString(), tmp);
		tmp += sizeof(int)*3;
		memcpy(m_pcRecvBuffer, &tmp, sizeof(int));
		tmp = send(m_hSocket, m_pcRecvBuffer, tmp, 0);
		if (SOCKET_ERROR == tmp) {
			AfxMessageBox("发送客户端信息失败", GetLastError());
		}
	}

	return TRUE;
}

BOOL FHSocket::ParseRecvMessage(const char* pcData)
{
	int totalSize = *((int*)pcData);
	const char* pRead = pcData + sizeof(int);
	int commandID = *((int*)pRead);
	pRead += sizeof(int);

	if (FH_COMM_MACHINEINFO == commandID) {
		int len = *((int*)pRead);
		pRead += sizeof(int);
		CString strName(pRead, len);
		FHMessage cMsg;
		cMsg.SetCommandID(commandID);
		cMsg.SetMachineInfo(FH_MSG_MachineInfo(strName));
		m_cListMsg.AddTail(cMsg);
		m_iRemainPos = 0;
	}
	return TRUE;
}

BOOL FHSocket::RecvMessage()
{
	if (INVALID_SOCKET == m_hSocket) {
		return FALSE;
	}

	INT lenBuffer = SO_RCVBUF;
	
	int recvSize = recv(m_hSocket, m_pcRecvBuffer, lenBuffer, 0);
	if (SOCKET_ERROR == recvSize) {
		this->DisplayErrMessageBox("接收数据失败", GetLastError());
		return FALSE;
	}
	else {

		// 上次有消息遗留，需要拼接处理
		if (0 < m_iRemainPos) {
			int lastSize = *((int*)m_pcRemainBuffer);
			int lastNeed = lastSize - m_iRemainPos;
			// 此次依旧未能接收完全
			if (recvSize < lastNeed) {
				memcpy(m_pcRemainBuffer+m_iRemainPos, m_pcRecvBuffer, recvSize);
				m_iRemainPos += recvSize;
				return TRUE;
			}
			else {	// 上次遗留消息可以接收完全
				// 读取到完整的消息，并开始解析（遗留消息处理）
				memcpy(m_pcRemainBuffer+m_iRemainPos, m_pcRecvBuffer, lastNeed);
				ParseRecvMessage(m_pcRemainBuffer);

				// 处理剩余的消息
				char* pRead = m_pcRecvBuffer + lastNeed;
				int remaindSize = recvSize - lastNeed;
				int newSize = *((int*)pRead);
				while (newSize <= remaindSize) {
					ParseRecvMessage(pRead);
					remaindSize -= newSize;
					if (0 == remaindSize) {
						break;
					}
					pRead += newSize;
					newSize = *((int*)pRead);
				}
				if (0 != remaindSize) {
					memcpy(m_pcRemainBuffer, pRead, remaindSize);
					m_iRemainPos = remaindSize;
				}
			}
		}
		else { //上次消息未有遗留
			// 逻辑同上
			// 处理剩余的消息
			char* pRead = m_pcRecvBuffer;
			int remaindSize = recvSize;
			int newSize = *((int*)pRead);
			while (newSize <= remaindSize) {
				ParseRecvMessage(pRead);
				remaindSize -= newSize;
				if (0 == remaindSize) {
					break;
				}
				pRead += newSize;
				newSize = *((int*)pRead);
			}
			if (0 != remaindSize) {
				memcpy(m_pcRemainBuffer, pRead, remaindSize);
				m_iRemainPos = remaindSize;
			}
		}
	}
	return TRUE;
}

SOCKET FHSocket::Accept(sockaddr* addr, int* addrlen)
{
	return accept(m_hSocket, addr, addrlen);
}

CString FHSocket::GetPeerName()
{
	struct sockaddr_in sa;
	int len = sizeof(sa);
	if(!getpeername(m_hSocket, (struct sockaddr *)&sa, &len))
	{
		return CString(inet_ntoa(sa.sin_addr));
	}
	return CString("");
}

void FHSocket::DisplayErrMessageBox(CString str, int err)
{
	CString strErr;
	strErr.Format("[FHSocket]%s,err=%d", str.GetString(), err);
	AfxMessageBox(strErr);
}

BOOL FHSocket::PopMessage(FHMessage& cMsg)
{
	if (m_cListMsg.IsEmpty()) {
		return FALSE;
	}
	else {
		cMsg =  m_cListMsg.RemoveHead();
		return TRUE;
	}
}
