// FHConnectSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHConnectSocket.h"
#include "FHSocketThread.h"


// FHConnectSocket

FHConnectSocket::FHConnectSocket()
:FHSocket(FH_SOCKET_TYPE_CLIENT)
{
}

FHConnectSocket::FHConnectSocket(const SOCKET socket)
:FHSocket(FH_SOCKET_TYPE_CLIENT, socket)
{

}

FHConnectSocket::~FHConnectSocket()
{
}


// FHConnectSocket ��Ա����
BOOL FHConnectSocket::CreateSocket(UINT uiPort)
{
	return FHSocket::CreateSocket(uiPort);
}

BOOL FHConnectSocket::StartConnect(CString cStrAddr)
{
	return FHSocket::StartConnect(cStrAddr);
}