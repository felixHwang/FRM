#pragma once
#include "afxcmn.h"

#include "afxmt.h"
#include <map>
#include "FHServerManager.h"
//#include <afxwin.h>
//#include "FHSocketThread.h"

// FHServerDlg 对话框


class FHAcceptThread;
class FHAcceptSocket;
class FHFileBrowser;

class FHServerDlg : public CDialog
{
	DECLARE_DYNAMIC(FHServerDlg)

public:
	FHServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FHServerDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
