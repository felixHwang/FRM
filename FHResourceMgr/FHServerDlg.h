#pragma once
#include "afxcmn.h"

#include "afxmt.h"
#include <list>
//#include <afxwin.h>
//#include "FHSocketThread.h"

// FHServerDlg �Ի���


class FHAcceptThread;
class FHAcceptSocket;

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

	static FHServerDlg* GetOwnerWin() {return m_pcOwnerWin;}

	//BOOL RegisterClientThread(FHSocketThread* pThread);
private:
	CListCtrl m_cClientCtrlList;
	CCriticalSection m_cCsSection; // �̳߳���
	FHAcceptSocket* m_pcServerSocket;

	static FHServerDlg *m_pcOwnerWin;

	

	//std::list<FHSocketThread*> m_cThreadList; // �̳߳�

	UINT m_szThreadIndex; // �̼߳�����

public:
	afx_msg void OnSelectOpen();
};
