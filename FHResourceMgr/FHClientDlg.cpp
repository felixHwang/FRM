// FHClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHClientDlg.h"
#include "FHConnectSocket.h"
#include "FHMessage.h"

const INT FH_TIMER_CLIENT_CONNECT = 1;

// FHClientDlg 对话框

IMPLEMENT_DYNAMIC(FHClientDlg, CDialog)


FHClientDlg::FHClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHClientDlg::IDD, pParent)
	, m_cEditAddr(_T("输入服务器IP地址"))
	, m_bConnecting(FALSE)
	, m_cPromptText(_T("输入IP地址后开始连接，默认端口8989"))
	, m_szConnectTimes(0)
{
	EnableAutomation();
}

FHClientDlg::~FHClientDlg()
{
	if (NULL != m_pcClientSocket) {
		delete m_pcClientSocket;
		m_pcClientSocket = NULL;
	}
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
	//DDX_Control(pDX, IDC_EDIT1, m_cEditCtrl);
	DDX_Text(pDX, IDC_STATIC2, m_cPromptText);
}

void FHClientDlg::OnExit()
{
	CWnd* pcParent = GetParent();
	if (NULL != pcParent) {
		this->DestroyWindow();
		pcParent->DestroyWindow();
	}

}

void FHClientDlg::OnClose()
{
	CWnd* pcParent = GetParent();
	CDialog::OnClose();
	if (NULL != pcParent) {
		::SendMessage(pcParent->m_hWnd, WM_CLOSE, 0, 0); 
	}
	
}

BOOL FHClientDlg::DestroyWindow()
{
	CWnd* pcParent = GetParent();
	if (NULL != pcParent) {
		::SendMessage(pcParent->m_hWnd, WM_CLOSE, 0, 0); 
	}
	return CDialog::DestroyWindow();
}

BEGIN_MESSAGE_MAP(FHClientDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &FHClientDlg::OnBnClickedButtonConnServer)
	ON_BN_CLICKED(IDC_BUTTON2, &FHClientDlg::OnBnClickedButtonDisconnServer)
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

void FHClientDlg::OnBnClickedButtonConnServer()
{
	// TODO: 在此添加控件通知处理程序代码
	ConnectServer();
}

BOOL FHClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitConfigInfo();

	if (NULL != m_pcClientSocket) {
		m_pcClientSocket = new FHConnectSocket();
		if (NULL != m_pcClientSocket) {
			m_pcClientSocket->CreateSocket();

			StartConnect();
		}
	}
	return TRUE;
}

void FHClientDlg::InitConfigInfo()
{
	char hostname[255];
	PHOSTENT hostinfo;
	
	//m_cConfigInfo.addr = _T("X.X.X.X");
	m_cConfigInfo.hostname = _T("Unknow");

	if(0 == gethostname(hostname, sizeof(hostname))) {
		// CA2W
		// 这是获取主机名，如果获得主机名成功的话，将返回一个指针，指向hostinfo，hostinfo
		
		//int lenAnsi = strlen(hostname);
		//TCHAR* pTmpStr = new TCHAR[sizeof(TCHAR)*lenAnsi];
		//memset(pTmpStr,0,lenAnsi*sizeof(TCHAR));
		//MultiByteToWideChar(CP_ACP, 0, hostname, -1, pTmpStr, sizeof(TCHAR)*lenAnsi);
		m_cConfigInfo.hostname.Format(_T("%s"), hostname);
		m_cConfigInfo.lenHostname = m_cConfigInfo.hostname.GetLength();
		//delete[] pTmpStr;
		/*
		if(NULL != (hostinfo = gethostbyname(hostname))) 
		{ 
			char* pAddr = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			//lenAnsi = strlen(pAddr);
			//TCHAR* pTmpStr = new TCHAR[sizeof(TCHAR)*lenAnsi];
			//memset(pTmpStr,0,lenAnsi*sizeof(TCHAR));
			//MultiByteToWideChar(CP_ACP, 0, pAddr, -1, pTmpStr, sizeof(TCHAR)*lenAnsi);
			m_cConfigInfo.addr.Format(_T("%s"), pAddr);
		}
		*/
	}
}

void FHClientDlg::SendConfigInfo()
{
	if (NULL != m_pcClientSocket) {
		FHMessage cMsg;
		cMsg.SetCommandID(FH_COMM_MACHINEINFO);
		cMsg.SetMachineInfo(m_cConfigInfo);
		m_pcClientSocket->SendMessage(cMsg);
	}
	/*
	if (NULL != m_cArcOut) {
		FHMessage cMessage;
		cMessage.SetMachineInfo(m_cConfigInfo);
		*m_cArcOut << &cMessage;

		m_cArcOut->Flush();
		//发送内容给服务器
		//CString strText = _T("client reply");
		//m_pcClientSocket->Send(strText, strText.GetLength());
	}
	*/
}

void FHClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	++m_szConnectTimes;
	m_cPromptText.Format(_T("连接服务器失败，第 %d 次尝试重新连接，请稍后……"), m_szConnectTimes);
	this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
	StartConnect();
	CDialog::OnTimer(nIDEvent);
}

BOOL FHClientDlg::StartConnect()
{

	if (NULL != m_pcClientSocket) {
		if (m_pcClientSocket->StartConnect("127.0.0.1")) {
			m_cPromptText = _T("连接服务器成功。");
			this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
			m_szConnectTimes = 0;

			SendConfigInfo();

			return TRUE;
		}
	}
	/*
	if (NULL != m_pcClientSocket && !m_bConnecting) {
		if (m_pcClientSocket->StartConnect()) {
			m_cSocketFile = new CSocketFile(m_pcClientSocket);
			// 输入CArchive
			m_cArcIn = new CArchive(m_cSocketFile, CArchive::load);
			// 输出CArchive
			m_cArcOut = new CArchive(m_cSocketFile, CArchive::store);
			m_bConnecting = TRUE;
			KillTimer(FH_TIMER_CLIENT_CONNECT);
			m_cPromptText = _T("连接服务器成功。");
			this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
			m_szConnectTimes = 0;

			SendConfigInfo();
			return TRUE;
		}
	}
	*/
	return FALSE;
}

void FHClientDlg::ConnectServer()
{
	/*
	if (NULL != m_pcClientSocket) {
		if (!StartConnect()) {
			if (WSAECONNREFUSED == m_pcClientSocket->GetLastError()) {
				m_cPromptText.Format(_T("连接失败，请检查服务端状态。"));
				this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
				SetTimer(FH_TIMER_CLIENT_CONNECT,500,NULL);
			}
			else {
				// message error
			}
		}
	}
	*/
}

void FHClientDlg::OnBnClickedButtonDisconnServer()
{
	// TODO: 在此添加控件通知处理程序代码
}
