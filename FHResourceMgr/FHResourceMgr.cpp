// FHResourceMgr.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHResourceMgrDlg.h"
#include "FHDiagLogin.h"
#include "FHClientDlg.h"
#include "FHServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFHResourceMgrApp

BEGIN_MESSAGE_MAP(CFHResourceMgrApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFHResourceMgrApp ����

CFHResourceMgrApp::CFHResourceMgrApp()
{
	// TODO: �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFHResourceMgrApp ����

CFHResourceMgrApp theApp;


// CFHResourceMgrApp ��ʼ��

BOOL CFHResourceMgrApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	FHDiagLogin loginDlg;
	INT_PTR nLoginResult = loginDlg.DoModal();
	if (FH_DIAGLOGIN_CLIENT == nLoginResult) {
		// client
		FHClientDlg clientDlg;
		m_pMainWnd = &clientDlg;
		INT_PTR ret = clientDlg.DoModal();
		int i = 1;
		
	}
	else if (FH_DIAGLOGIN_SERVER == nLoginResult)
	{
		// server
		FHServerDlg serverDlg;
		m_pMainWnd = &serverDlg;
		serverDlg.DoModal();
	}

	/*
	CFHResourceMgrDlg dlg;

	dlg.Create(IDD_FHRESOURCEMGR_DIALOG);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô�����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô�����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
*/
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}