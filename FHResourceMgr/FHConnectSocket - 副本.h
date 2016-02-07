#pragma once

// FHConnectSocket 命令目标

#include "FHPublicDefine.h"

enum FH_TYPE_SOCKET {
	FH_TYPE_SOCKET_CLIENT = 0,
	FH_TYPE_SOCKET_SERVER,
	FH_TYPE_SOCKET_NORMOL
};



class CDialog;

class FHConnectSocket : public CSocket
{
public:
	FHConnectSocket(FH_TYPE_SOCKET type = FH_TYPE_SOCKET_NORMOL);
	virtual ~FHConnectSocket();

	BOOL CreateSocket(UINT uiPort = FH_DEFAULT_CONNECT_PORT);

	BOOL StartConnect(CString cStrAddr = _T("127.0.0.1"));
	void OnAccept(int nErrorCode);
	void OnReceive(int nErrorCode);

	void SendConfigInfoToSvr();

	CWinThread* m_pcThread; // 该CSocket所在的线程
private:
	FH_TYPE_SOCKET m_eSocketType;
	CString m_cAddr;
	UINT m_szPort;
	CDialog* m_pcMainDlg;
	UINT m_szThreadIndex;

	CSocketFile* m_cSocketFile; // CSocketFile

	//CArchive* m_cArcIn; // 输入CArchive

	CArchive* m_cArcOut; // 输出CArchive
};


