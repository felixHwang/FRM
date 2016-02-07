// FHDiagLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHDiagLogin.h"


// FHDiagLogin �Ի���

IMPLEMENT_DYNAMIC(FHDiagLogin, CDialog)

FHDiagLogin::FHDiagLogin(CWnd* pParent /*=NULL*/)
	: CDialog(FHDiagLogin::IDD, pParent)
{

}

FHDiagLogin::~FHDiagLogin()
{
}

void FHDiagLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FHDiagLogin, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &FHDiagLogin::OnBnClickedServer)
	ON_BN_CLICKED(IDOK, &FHDiagLogin::OnBnClickedClient)
END_MESSAGE_MAP()


// FHDiagLogin ��Ϣ�������

void FHDiagLogin::OnBnClickedServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(FH_DIAGLOGIN_SERVER);
}

void FHDiagLogin::OnBnClickedClient()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(FH_DIAGLOGIN_CLIENT);
}

void FHDiagLogin::OnClose()
{
	EndDialog(IDCANCEL);
}