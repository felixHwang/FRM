#pragma once

#include "FHConnectSocket.h"
#include "FHMessage.h"

// FHSocketThread



class FHServerDlg;

class FHSocketThread : public CWinThread
{
	friend class FHServerDlg;
	DECLARE_DYNCREATE(FHSocketThread)

protected:
	FHSocketThread();           // 动态创建所使用的受保护的构造函数
	virtual ~FHSocketThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();

	SOCKET m_hSocket; // Socket 句柄

	int m_thrdIndex;

	//CSCEServerDlg* m_pSerDlg; // 主界面指针

	SOCKET m_uSocket; // Socket 句柄

	FHConnectSocket m_cServerSocket; // 附加在这个线程上的CSocket

	void OnCallBack(WPARAM wParam,LPARAM lParam);

private:
	FHServerDlg* m_pcMainDlg;

	CSocketFile* m_pcSocketFile; // CSocketFile

	CArchive* m_pcArcIn; // 输入CArchive

	CArchive* m_pcArcOut; // 输出CArchive


	FHMessage m_cMessage;
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
};


