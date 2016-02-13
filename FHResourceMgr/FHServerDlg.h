#pragma once
#include "afxcmn.h"

#include "afxmt.h"
#include <map>
#include "FHServerManager.h"
//#include <afxwin.h>
//#include "FHSocketThread.h"

// FHServerDlg �Ի���


class FHAcceptThread;
class FHAcceptSocket;
class FHFileBrowser;

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

private:
	CListCtrl m_cClientCtrlList;

	std::map<CString, FHFileBrowser*> m_cFileBrList;

	FHServerManager m_cServerManager;

public:
	afx_msg void OnSelectOpen();
	LRESULT RecvClientDisconnect(WPARAM wParam,LPARAM lParam);
	LRESULT RefleshFileInfo(WPARAM wParam,LPARAM lParam);
	LRESULT RequestFileInfo(WPARAM wParam,LPARAM lParam);
};
