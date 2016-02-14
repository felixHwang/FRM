#pragma once
#include "afxcmn.h"
#include "afxmt.h"
#include <map>
#include "FHServerManager.h"

// FHServerDlg �Ի���


class FHFileBrowserDlg;

class FHServerDlg : public CDialog
{
	DECLARE_DYNAMIC(FHServerDlg)

public:
	FHServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FHServerDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	afx_msg void OnNMRClickListOfClient(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT RefleshConnectList(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT RecvClientDisconnect(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT RefleshFileInfo(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT RequestFileInfo(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSelectOpen();
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnClose();
private:
	CListCtrl m_cClientCtrlList;
	std::map<CString, FHFileBrowserDlg*> m_cFileBrList;
	FHServerManager m_cServerManager;
};
