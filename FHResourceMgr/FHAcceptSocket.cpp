#include "stdafx.h"
#include "FHAcceptSocket.h"

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
