#pragma once
#include "afxwin.h"
#include "FHMessage.h"

class FHConnectSocket;

// FHClientDlg 对话框

class FHClientDlg : public CDialog
{
	DECLARE_DYNAMIC(FHClientDlg)

public:
	FHClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FHClientDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	void OnExit();
	void OnClose();
	BOOL DestroyWindow();
public:
	afx_msg void OnBnClickedButtonConnServer();

	void OnTimer(UINT_PTR nIDEvent);

private:
	void SendConfigInfo();
	void InitConfigInfo();
	void ConnectServer();
	BOOL StartConnect();

	FHConnectSocket* m_pcClientSocket;

	CSocketFile* m_cSocketFile; // CSocketFile

	CArchive* m_cArcIn; // 输入CArchive

	CArchive* m_cArcOut; // 输出CArchive

	FH_MSG_MachineInfo m_cConfigInfo;

	FHMessage m_cMessage;

	BOOL m_bConnecting;
	CString m_cEditAddr;
	//CEdit m_cEditCtrl;
public:
	afx_msg void OnBnClickedButtonDisconnServer();
private:
	CString m_cPromptText;
	UINT m_szConnectTimes;
};
