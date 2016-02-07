#pragma once


// FHDiagLogin 对话框

#define FH_DIAGLOGIN_SERVER 0X9001
#define FH_DIAGLOGIN_CLIENT 0X9002

class FHDiagLogin : public CDialog
{
	DECLARE_DYNAMIC(FHDiagLogin)

public:
	FHDiagLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FHDiagLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedServer();
	afx_msg void OnBnClickedClient();
	void OnClose();
};
