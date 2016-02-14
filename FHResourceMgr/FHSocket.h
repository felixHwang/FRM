#pragma once

#include <winsock2.h>
#include "FHPublicDefine.h"
#include "FHMessage.h"

enum FH_SOCKET_TYPE {
	FH_SOCKET_TYPE_CLIENT = 0,
	FH_SOCKET_TYPE_SERVER,
	FH_SOCKET_TYPE_NORMOL
};


class FHSocket
{
public:
	FHSocket(const FH_SOCKET_TYPE type);

	FHSocket(const FH_SOCKET_TYPE type, const SOCKET socket);
	virtual ~FHSocket(void);

 	virtual BOOL CreateSocket(UINT uiPort = FH_DEFAULT_CONNECT_PORT);

	virtual BOOL StartConnect(CString cStrAddr);

	virtual BOOL CloseSocket();

	virtual BOOL Accept(SOCKET& socket, sockaddr* addr, int* addrlen);

	BOOL SendMessage(const FHMessage& msg);

	BOOL RecvMessage();

	BOOL PopMessage(FHMessage& cMsg);

	virtual CString GetPeerName();

	void DisplayErrMessageBox(CString str, int err);

	int GetErrorCode();

	void ClearError();

protected:
	void SetErrorCode(int errorCode);

	BOOL ParseRecvMessage(const char* pcData);
	SOCKET m_hSocket;
	FH_SOCKET_TYPE m_eSocketType;
	CString m_cAddr;
	UINT m_szPort;

	CList<FHMessage> m_cListMsg;
	FHMessage m_cLastMsg;
	BOOL m_bLastMsg;	// message complete or not

	char* m_pcRecvBuffer;
	char* m_pcRemainBuffer;
	int m_iRemainPos;
	int m_iErrorCode;
};
