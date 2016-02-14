// FHClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHClientDlg.h"
#include "FHMessage.h"

const INT FH_TIMER_CLIENT_CONNECT = 1;

// FHClientDlg 对话框

IMPLEMENT_DYNAMIC(FHClientDlg, CDialog)

FHClientDlg::FHClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHClientDlg::IDD, pParent)
	, m_cEditAddr(_T("127.0.0.1")) // 输入服务器IP地址
	, m_cPromptText(_T("输入IP地址后开始连接，默认端口8989"))
	, m_bConnecting(FALSE)
	, m_szConnectTimes(0)
{
	EnableAutomation();
}

FHClientDlg::~FHClientDlg()
{
}

void FHClientDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialog::OnFinalRelease();
}

void FHClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cEditAddr);
	DDX_Text(pDX, IDC_STATIC2, m_cPromptText);
}

BEGIN_MESSAGE_MAP(FHClientDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &FHClientDlg::OnBnClickedButtonConnServer)
	ON_BN_CLICKED(IDC_BUTTON2, &FHClientDlg::OnBnClickedButtonDisconnServer)
	ON_MESSAGE(FH_MSCMD_SERVERDISCONNECT, RecvDisconnect)
	ON_MESSAGE(FH_MSCMD_REQFILEINFO, RecvRequestFileInfo)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHClientDlg, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFHClientDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {762B81F4-D5E7-43CE-9F08-1FED4A506C23}
static const IID IID_IFHClientDlg =
{ 0x762B81F4, 0xD5E7, 0x43CE, { 0x9F, 0x8, 0x1F, 0xED, 0x4A, 0x50, 0x6C, 0x23 } };

BEGIN_INTERFACE_MAP(FHClientDlg, CDialog)
	INTERFACE_PART(FHClientDlg, IID_IFHClientDlg, Dispatch)
END_INTERFACE_MAP()


// FHClientDlg 消息处理程序

BOOL FHClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	AbleConnectFunction(TRUE);

	this->SetWindowText("客户端："+m_cClientMgr.GetHostName());

	// OnBnClickedButtonConnServer();

	return TRUE;
}

void FHClientDlg::OnClose()
{
	m_cClientMgr.StopConnect();
	CDialog::OnClose();
}

void FHClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bConnecting) {
		return;
	}
	++m_szConnectTimes;
	StartConnect();
	CDialog::OnTimer(nIDEvent);
}

void FHClientDlg::OnBnClickedButtonConnServer()
{
	// TODO: 在此添加控件通知处理程序代码
	StartConnect();
}

void FHClientDlg::OnBnClickedButtonDisconnServer()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(FH_TIMER_CLIENT_CONNECT);
	m_cClientMgr.StopConnect();
	AbleConnectFunction(TRUE);
	m_bConnecting = FALSE;
	m_cPromptText = _T("已断开连接。");
	this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
}

LRESULT FHClientDlg::RecvDisconnect(WPARAM wParam,LPARAM lParam)
{
	AbleConnectFunction(TRUE);
	m_cClientMgr.StopConnect();
	m_szConnectTimes = 0;
	m_cPromptText = _T("服务端关闭，连接断开。");
	this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
	return 0;
}

LRESULT FHClientDlg::RecvRequestFileInfo(WPARAM wParam,LPARAM lParam)
{
	FHMessage cMsg =  *((FHMessage*)lParam);
	FH_MSG_OperatorInfo opeInfo = cMsg.GetOperatorInfo();
	if (0 < opeInfo.opeItemVec.size()) {
		m_cClientMgr.SendServerDirInfo(opeInfo.opeItemVec[0].filePath);
	}
	return 0;
}

BOOL FHClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN) 
	{ 
		switch(pMsg->wParam)  
		{  
		case VK_RETURN:   // Enter 
			return TRUE;
		case VK_ESCAPE:   // Esc  
			return TRUE;
		} 
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void FHClientDlg::AbleConnectFunction(BOOL flag)
{
	CButton* pConnectBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
	if(NULL != pConnectBtn) 
	{ 
		pConnectBtn->EnableWindow(flag); // True or False 
	}

	CEdit* pAddrEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	if(NULL != pAddrEdit) 
	{ 
		pAddrEdit->EnableWindow(flag); // True or False 
	}

	CButton* pDisConnectBtn = (CButton *)GetDlgItem(IDC_BUTTON2);
	if(NULL != pDisConnectBtn) 
	{ 
		pDisConnectBtn->EnableWindow(!flag); // True or False 
	}
}

void FHClientDlg::StartConnect()
{
	UpdateData(TRUE);
	if (INADDR_NONE == inet_addr(m_cEditAddr.GetString())) {
		CString errText;
		errText.Format("地址：%s 非法，重新输入正确地址（x.x.x.x）。", m_cEditAddr.GetString());
		AfxMessageBox(errText);
		return;
	}
	int ret = m_cClientMgr.StartConnect(m_cEditAddr.GetString());
	if (FH_ERR_NOERROR != ret) {
		m_cPromptText.Format("连接失败，请检查服务端状态,已经进行第 %d 次重新连接。", m_szConnectTimes);
		this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
		m_bConnecting = FALSE;
		SetTimer(FH_TIMER_CLIENT_CONNECT,1000,NULL);
		AbleConnectFunction(FALSE);
	}
	else {
		m_cPromptText = "连接成功";
		this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
		KillTimer(FH_TIMER_CLIENT_CONNECT);
		m_szConnectTimes = 0;
		m_bConnecting = TRUE;
		AbleConnectFunction(FALSE);
	}
}