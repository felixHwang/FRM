// FHConnectSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "FHConnectSocket.h"
#include "FHPublicDefine.h"


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
