// FHCommThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHCommThread.h"
#include "FHCommSocket.h"
#include "FHMessage.h"
#include "FHCommSocket.h"
#include "FHServerDlg.h"
#include "FHFileBrowser.h"
#include <vector>
#include <string>

// FHCommThread

IMPLEMENT_DYNCREATE(FHCommThread, CWinThread)

FHCommThread::FHCommThread()
{
	EnableAutomation();
}

FHCommThread::~FHCommThread()
{
}


void FHCommThread::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CWinThread::OnFinalRelease();
}

BOOL FHCommThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_bQuit = FALSE;
	return TRUE;
}

int FHCommThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHCommThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHCommThread, CWinThread)
END_DISPATCH_MAP()

// ע��: ������� IID_IFHCommThread ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4FC39D3F-097F-4CA1-B693-044EFCC0DBE3}
static const IID IID_IFHCommThread =
{ 0x4FC39D3F, 0x97F, 0x4CA1, { 0xB6, 0x93, 0x4, 0x4E, 0xFC, 0xC0, 0xDB, 0xE3 } };

BEGIN_INTERFACE_MAP(FHCommThread, CWinThread)
	INTERFACE_PART(FHCommThread, IID_IFHCommThread, Dispatch)
END_INTERFACE_MAP()

void FHCommThread::RegisterSocket(const SOCKET& hSocket)
{
	m_hSocket = hSocket;
	m_pcSocket = new FHCommSocket(hSocket);
}

void FHCommThread::UnRegisterSocket()
{

}

void FHCommThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	FHMessage cMsg;
	while (!m_bQuit) {
		if (NULL != m_pcSocket) {
			if (m_pcSocket->RecvMessage()) {

				while (m_pcSocket->PopMessage(cMsg)) {
					if (FH_COMM_MACHINEINFO == cMsg.GetCommandID()) {
						m_cClientInfo.hostname = cMsg.GetMachineInfo().hostname;
						m_cClientInfo.address = m_pcSocket->GetPeerName();
						int ret = AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_UPDATECONNECT,0,(LPARAM)&m_cClientInfo);

						/*m_pcFileBrowserDlg = new FHFileBrowser();
						m_pcFileBrowserDlg->Create(IDD_DIALOGFILEBR);
						m_pcFileBrowserDlg->ShowWindow(SW_SHOW);*/
					}
				}
			}
			else {
				if (WSAECONNRESET == m_pcSocket->GetErrorCode()) {
					AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_CLIENTDISCONNECT, 0, (LPARAM)&m_cClientInfo);
					if (NULL != m_pcFileBrowserDlg) {
						m_pcFileBrowserDlg->DestroyWindow();
						delete m_pcFileBrowserDlg;
						m_pcFileBrowserDlg = NULL;
					}
					break;
				}
			}
		}
	}
}


// FHCommThread ��Ϣ�������
