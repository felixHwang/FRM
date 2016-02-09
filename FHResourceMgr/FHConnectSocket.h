#pragma once

#include "FHSocket.h"

// FHConnectSocket ����Ŀ��

#include "FHPublicDefine.h"

enum FH_TYPE_SOCKET {
	FH_TYPE_SOCKET_CLIENT = 0,
	FH_TYPE_SOCKET_SERVER,
	FH_TYPE_SOCKET_NORMOL
};



class CDialog;

class FHConnectSocket : public FHSocket
{
public:
	FHConnectSocket();

	FHConnectSocket(const SOCKET socket);

	virtual ~FHConnectSocket();

	BOOL CreateSocket(UINT uiPort = FH_DEFAULT_CONNECT_PORT);

	BOOL StartConnect(CString cStrAddr = _T("127.0.0.1"));

	void SendConfigInfoToSvr();

	CWinThread* m_pcThread; // ��CSocket���ڵ��߳�
private:
	FH_TYPE_SOCKET m_eSocketType;
	CString m_cAddr;
	UINT m_szPort;
	CDialog* m_pcMainDlg;
	UINT m_szThreadIndex;

	CSocketFile* m_cSocketFile; // CSocketFile

	//CArchive* m_cArcIn; // ����CArchive

	CArchive* m_cArcOut; // ���CArchive
};


