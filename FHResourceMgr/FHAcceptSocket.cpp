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
}