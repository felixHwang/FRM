// FHWinThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHWinThread.h"


// FHWinThread

IMPLEMENT_DYNCREATE(FHWinThread, CWinThread)

FHWinThread::FHWinThread()
{
	EnableAutomation();
}

FHWinThread::~FHWinThread()
{
}


void FHWinThread::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CWinThread::OnFinalRelease();
}

BOOL FHWinThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_bQuit = FALSE;
	return TRUE;
}

int FHWinThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	m_bQuit = TRUE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHWinThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHWinThread, CWinThread)
END_DISPATCH_MAP()

// ע��: ������� IID_IFHWinThread ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {47078593-4647-49B5-A0E8-4B9E5470C625}
static const IID IID_IFHWinThread =
{ 0x47078593, 0x4647, 0x49B5, { 0xA0, 0xE8, 0x4B, 0x9E, 0x54, 0x70, 0xC6, 0x25 } };

BEGIN_INTERFACE_MAP(FHWinThread, CWinThread)
	INTERFACE_PART(FHWinThread, IID_IFHWinThread, Dispatch)
END_INTERFACE_MAP()

void FHWinThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{

	/*
	SOCKADDR_IN		sAddr;
	int				nAddrLen;
	SOCKET			hSocket;

	while(!m_bQuit)
	{
		nAddrLen = sizeof(SOCKADDR_IN);
		memset(&sAddr, 0, nAddrLen);
		hSocket = accept(m_hSocket, (SOCKADDR *)&sAddr, &nAddrLen);
		if (INVALID_SOCKET != hSocket) {
			FHWinThread* pcThread = (FHWinThread*)AfxBeginThread(RUNTIME_CLASS(FHWinThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

			pcThread->m_hSocket = m_hSocket;
			// do some thing

			//m_cVecConnectThead[hSocket] = pcThread;
		}
		else {
			
		}
	} // while
	*/
}

void FHWinThread::RegisterSocket(const SOCKET& m_hSocket)
{

}

void FHWinThread::UnRegisterSocket()
{

}


// FHWinThread ��Ϣ�������
