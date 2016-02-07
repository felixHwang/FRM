// FHResourceMgrDlg.h : ͷ�ļ�
//

#pragma once

#include "FHClientDlg.h"
#include "FHServerDlg.h"
#include "FHConnectSocket.h"

// CFHResourceMgrDlg �Ի���
class CFHResourceMgrDlg : public CDialog
{
// ����
public:
	CFHResourceMgrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FHRESOURCEMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelectServer();
	afx_msg void OnBnClickedButtonSelectClient();

private:
	FHClientDlg m_cClientDlg;
	FHServerDlg m_cServerDlg;
	FHConnectSocket* m_pcServerSocket;
	FHConnectSocket* m_pcClientSocket;
};
