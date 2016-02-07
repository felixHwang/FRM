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
	FHSocketThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~FHSocketThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();

	SOCKET m_hSocket; // Socket ���

	int m_thrdIndex;

	//CSCEServerDlg* m_pSerDlg; // ������ָ��

	SOCKET m_uSocket; // Socket ���

	FHConnectSocket m_cServerSocket; // ����������߳��ϵ�CSocket

	void OnCallBack(WPARAM wParam,LPARAM lParam);

private:
	FHServerDlg* m_pcMainDlg;

	CSocketFile* m_pcSocketFile; // CSocketFile

	CArchive* m_pcArcIn; // ����CArchive

	CArchive* m_pcArcOut; // ���CArchive


	FHMessage m_cMessage;
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
};


