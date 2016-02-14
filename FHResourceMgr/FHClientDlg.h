#pragma once
#include "afxwin.h"
#include "FHMessage.h"
#include "FHClientManager.h"

class FHConnectSocket;

// FHClientDlg �Ի���

class FHClientDlg : public CDialog
{
	DECLARE_DYNAMIC(FHClientDlg)

public:
	FHClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FHClientDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnBnClickedButtonConnServer();
	afx_msg void OnBnClickedButtonDisconnServer();

	void OnTimer(UINT_PTR nIDEvent);
	void OnClose();

	LRESULT RecvDisconnect(WPARAM wParam,LPARAM lParam);
	LRESULT RecvRequestFileInfo(WPARAM wParam,LPARAM lParam);

	BOOL PreTranslateMessage(MSG* pMsg);

private:
	void StartConnect();
	void AbleConnectFunction(BOOL flag = FALSE);

	FHClientManager m_cClientMgr;
	FHMessage m_cMessage;
	CString m_cEditAddr;
	CString m_cPromptText;
	BOOL m_bConnecting;
	UINT m_szConnectTimes;
	
};
