// FHResourceMgrDlg.h : 头文件
//

#pragma once

#include "FHClientDlg.h"
#include "FHServerDlg.h"
#include "FHConnectSocket.h"

// CFHResourceMgrDlg 对话框
class CFHResourceMgrDlg : public CDialog
{
// 构造
public:
	CFHResourceMgrDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FHRESOURCEMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
