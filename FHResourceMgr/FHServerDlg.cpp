// FHServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHServerDlg.h"
#include "FHAcceptSocket.h"
#include "FHSocketThread.h"


// FHServerDlg �Ի���

IMPLEMENT_DYNAMIC(FHServerDlg, CDialog)

FHServerDlg::FHServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHServerDlg::IDD, pParent)
	, m_pcServerSocket(NULL)
{

	EnableAutomation();



	TCHAR tstr1[] = _TEXT("TEST1");
	TCHAR tstr2[] = _TEXT("TEST2");
	TCHAR tstr3[] = _TEXT("TEST3");
	/*
	m_cClientList.InsertString(0,tstr1);
	m_cClientList.InsertString(1,tstr2);
	m_cClientList.InsertString(2,tstr3);
	*/



}

FHServerDlg::~FHServerDlg()
{
}

void FHServerDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialog::OnFinalRelease();
}

void FHServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_cClientCtrlList);
}

BOOL FHServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cClientCtrlList.SetExtendedStyle(m_cClientCtrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	m_cClientCtrlList.InsertColumn(0, _TEXT("������"),LVCFMT_CENTER,100,0);
	
	m_cClientCtrlList.InsertColumn(1, _TEXT("IP��ַ"),LVCFMT_CENTER,100,1);
	m_cClientCtrlList.InsertColumn(2, _TEXT("״̬"),LVCFMT_LEFT,100,2);

	m_cClientCtrlList.InsertItem(0, _T("Java"));   
    m_cClientCtrlList.SetItemText(0, 1, _T("192.168.0.1"));   
    m_cClientCtrlList.SetItemText(0, 2, _T("Connect"));

	m_cClientCtrlList.InsertItem(1, _T("Pyt"));   
	m_cClientCtrlList.SetItemText(1, 1, _T("192.168.0.2"));   
	m_cClientCtrlList.SetItemText(1, 2, _T("Connect"));

	m_cClientCtrlList.InsertItem(2, _T("Cs"));   
	m_cClientCtrlList.SetItemText(2, 1, _T("192.168.0.3"));   
	m_cClientCtrlList.SetItemText(2, 2, _T("Disconnect"));

	if (NULL == m_pcServerSocket)
	{
		m_pcServerSocket = new FHAcceptSocket();
		if (NULL != m_pcServerSocket) {
			m_pcServerSocket->CreateSocket();
			m_pcServerSocket->StartConnect();
		}
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(FHServerDlg, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &FHServerDlg::OnNMRClickListOfClient)
	ON_COMMAND(ID_1_32774, &FHServerDlg::OnSelectOpen)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHServerDlg, CDialog)
END_DISPATCH_MAP()

// ע��: ������� IID_IFHServerDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E813554D-6368-4772-8D48-F7A77662C721}
static const IID IID_IFHServerDlg =
{ 0xE813554D, 0x6368, 0x4772, { 0x8D, 0x48, 0xF7, 0xA7, 0x76, 0x62, 0xC7, 0x21 } };

BEGIN_INTERFACE_MAP(FHServerDlg, CDialog)
	INTERFACE_PART(FHServerDlg, IID_IFHServerDlg, Dispatch)
END_INTERFACE_MAP()


// FHServerDlg ��Ϣ�������

void FHServerDlg::OnNMRClickListOfClient(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	POINT pt;
    GetCursorPos(&pt);
    int x=m_cClientCtrlList.GetSelectionMark();
     if (m_cClientCtrlList.GetSelectedCount() <= 0)  
    {  
        return;
    }  
    CMenu menu;
	
    menu.LoadMenu(IDR_MENU1);
    CMenu * pop=menu.GetSubMenu(0);
	if(NULL != pop) {
		pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
	}
}

void FHServerDlg::OnSelectOpen()
{
	// TODO: �ڴ���������������
	int i=0;
}

/*
BOOL FHServerDlg::RegisterClientThread(FHSocketThread* pThread)
{
	if (NULL != pThread) {
		pThread->m_pcMainDlg = this;
		m_cCsSection.Lock();	
		m_cThreadList.push_back(pThread);
		m_cCsSection.Unlock();
		return TRUE;
	}
	return FALSE;
}
*/