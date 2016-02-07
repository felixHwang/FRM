#pragma once
#include "afxcmn.h"

#include "afxmt.h"
#include <list>
//#include "FHSocketThread.h"

// FHServerDlg 对话框


class FHAcceptThread;
class FHAcceptSocket;

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

	//BOOL RegisterClientThread(FHSocketThread* pThread);
private:
	CListCtrl m_cClientCtrlList;
	CCriticalSection m_cCsSection; // 线程池锁
	FHAcceptSocket* m_pcServerSocket;

	

	//std::list<FHSocketThread*> m_cThreadList; // 线程池

	UINT m_szThreadIndex; // 线程计数器

public:
	afx_msg void OnSelectOpen();
};
