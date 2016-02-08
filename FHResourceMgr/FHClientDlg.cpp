// FHClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHClientDlg.h"
#include "FHConnectSocket.h"
#include "FHMessage.h"

const INT FH_TIMER_CLIENT_CONNECT = 1;

// FHClientDlg �Ի���

IMPLEMENT_DYNAMIC(FHClientDlg, CDialog)


FHClientDlg::FHClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHClientDlg::IDD, pParent)
	, m_cEditAddr(_T("���������IP��ַ"))
	, m_bConnecting(FALSE)
	, m_cPromptText(_T("����IP��ַ��ʼ���ӣ�Ĭ�϶˿�8989"))
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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IFHClientDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {762B81F4-D5E7-43CE-9F08-1FED4A506C23}
static const IID IID_IFHClientDlg =
{ 0x762B81F4, 0xD5E7, 0x43CE, { 0x9F, 0x8, 0x1F, 0xED, 0x4A, 0x50, 0x6C, 0x23 } };

BEGIN_INTERFACE_MAP(FHClientDlg, CDialog)
	INTERFACE_PART(FHClientDlg, IID_IFHClientDlg, Dispatch)
END_INTERFACE_MAP()


// FHClientDlg ��Ϣ�������

void FHClientDlg::OnBnClickedButtonConnServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		// ���ǻ�ȡ���������������������ɹ��Ļ���������һ��ָ�룬ָ��hostinfo��hostinfo
		
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
		//�������ݸ�������
		//CString strText = _T("client reply");
		//m_pcClientSocket->Send(strText, strText.GetLength());
	}
	*/
}

void FHClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	++m_szConnectTimes;
	m_cPromptText.Format(_T("���ӷ�����ʧ�ܣ��� %d �γ����������ӣ����Ժ󡭡�"), m_szConnectTimes);
	this->SetDlgItemText(IDC_STATIC2, m_cPromptText);
	StartConnect();
	CDialog::OnTimer(nIDEvent);
}

BOOL FHClientDlg::StartConnect()
{

	if (NULL != m_pcClientSocket) {
		if (m_pcClientSocket->StartConnect("127.0.0.1")) {
			m_cPromptText = _T("���ӷ������ɹ���");
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
			// ����CArchive
			m_cArcIn = new CArchive(m_cSocketFile, CArchive::load);
			// ���CArchive
			m_cArcOut = new CArchive(m_cSocketFile, CArchive::store);
			m_bConnecting = TRUE;
			KillTimer(FH_TIMER_CLIENT_CONNECT);
			m_cPromptText = _T("���ӷ������ɹ���");
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
				m_cPromptText.Format(_T("����ʧ�ܣ���������״̬��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
