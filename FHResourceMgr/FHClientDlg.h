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

	void OnClose();
	BOOL DestroyWindow();
public:
	afx_msg void OnBnClickedButtonConnServer();

	void OnTimer(UINT_PTR nIDEvent);

	LRESULT RecvDisconnect(WPARAM wParam,LPARAM lParam);

private:
	void StartConnect();

	void AbleConnectFunction(bool flag = false);
	FHMessage m_cMessage;

	BOOL m_bConnecting;
	CString m_cEditAddr;
	//CEdit m_cEditCtrl;
public:
	afx_msg void OnBnClickedButtonDisconnServer();
private:
	CString m_cPromptText;
	UINT m_szConnectTimes;
	FHClientManager m_cClientMgr;
};
