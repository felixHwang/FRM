#include "StdAfx.h"
#include "FHCommSocket.h"

FHCommSocket::FHCommSocket(void)
:FHSocket(FH_SOCKET_TYPE_NORMOL)
{
}

FHCommSocket::FHCommSocket(const SOCKET socket)
:FHSocket(FH_SOCKET_TYPE_NORMOL, socket)
{

}

FHCommSocket::~FHCommSocket(void)
{
}
