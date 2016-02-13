// FHResourceMgr.cpp : 定义应用程序的类行为。
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


// CFHResourceMgrApp 构造

CFHResourceMgrApp::CFHResourceMgrApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CFHResourceMgrApp 对象

CFHResourceMgrApp theApp;


// CFHResourceMgrApp 初始化

BOOL CFHResourceMgrApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	FHDiagLogin loginDlg;
	INT_PTR nLoginResult = /*FH_DIAGLOGIN_SERVER*/ loginDlg.DoModal();
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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
*/
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
