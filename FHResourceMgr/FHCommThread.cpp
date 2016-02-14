// FHCommThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHCommThread.h"
#include "FHCommSocket.h"
#include "FHMessage.h"
#include "FHCommSocket.h"
#include "FHServerDlg.h"
#include "FHFileBrowserDlg.h"
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

void FHCommThread::SetIdentifyKey(CString key)
{
	m_cClientInfo.key = key;
}

void FHCommThread::RegisterSocket(FHCommSocket* pcSocket)
{
	if (NULL != pcSocket) {
		m_pcCommSocket = pcSocket;
	}
}

void FHCommThread::UnRegisterSocket()
{
	m_pcCommSocket = NULL;
}

void FHCommThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	FHMessage cMsg;
	while (!m_bQuit) {
		if (NULL != m_pcCommSocket) {
			if (m_pcCommSocket->RecvMessage()) {
				while (m_pcCommSocket->PopMessage(cMsg)) {
					if (FH_COMM_MACHINEINFO == cMsg.GetCommandID()) {
						m_cClientInfo.hostname = cMsg.GetMachineInfo().hostname;
						m_cClientInfo.address = m_pcCommSocket->GetPeerName();
						int ret = AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_UPDATECONNECT,0,(LPARAM)&m_cClientInfo);
					}
					else if (FH_COMM_FILEINFO == cMsg.GetCommandID()) {
						FH_MSG_FileInfo cFileInfo = cMsg.GetFileInfo();
						UINT key;
						sscanf_s(m_cClientInfo.key.GetString(), "%u", &key);
						AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_UPFILEINFO,(WPARAM)key,(LPARAM)&cMsg);
					}
				}
			}
			else {
				if (WSAECONNRESET == m_pcCommSocket->GetErrorCode()) {
					
					AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_CLIENTDISCONNECT, 0, (LPARAM)&m_cClientInfo);
					break;
				}
			}
		}
	}
}
