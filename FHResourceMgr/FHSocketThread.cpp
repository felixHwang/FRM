// FHSocketThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHSocketThread.h"


// FHSocketThread

IMPLEMENT_DYNCREATE(FHSocketThread, CWinThread)

FHSocketThread::FHSocketThread()
{
	EnableAutomation();
}

FHSocketThread::~FHSocketThread()
{
}


void FHSocketThread::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CWinThread::OnFinalRelease();
}

BOOL FHSocketThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��

	if (!AfxSocketInit()) // ��ʼ��CSocket������õ�

	{

		return CWinThread::InitInstance(); // �����˳�

	}


	//{�Է����Socket���ӵ�socket���}

	//if(m_cServerSocket.Attach(m_uSocket)) // ����Attach֮ǰ�����Socket

	{

		m_cServerSocket.m_pcThread = this; // ����CSocket�������ӹ������߳�

		//m_cServerSocket.m_thrdIndex = m_thrdIndex;

		//m_serverSocket.m_pSerDlg = m_pSerDlg;

		// ����CSocketFile����CSocket����������

		//{�ѷ����Socket�󶨵�sockfile�ϣ�ͨ�Ų����ļ�����ʽ����}

		//m_pcSocketFile = new CSocketFile(&m_cServerSocket);

		// ����CArchive

		//m_pcArcIn = new CArchive(m_pcSocketFile, CArchive::load);

		// ���CArchive

		//m_pcArcOut = new CArchive(m_pcSocketFile, CArchive::store);

		return TRUE; // �����߳̾Ͳ��������˳�

	}

	int errorCode = ::GetLastError();
	return CWinThread::InitInstance(); // �����˳�
}

int FHSocketThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

void FHSocketThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	/*
	if (NULL != m_pcSocketFile) {
		m_pcSocketFile = new CSocketFile(&m_cServerSocket);
		m_pcArcIn = new CArchive(m_pcSocketFile, CArchive::load);
		m_pcArcOut = new CArchive(m_pcSocketFile, CArchive::store);
	}
	switch(wParam)

	{

	case FH_MSCMD_RECV:

		// ��������

		// �Ȱѽ��������¼��ص�

		//{�رս������ݣ���������������ݲ�ͣ��������ɴ��������������дһ�����}

		if (NULL != m_cServerSocket) {
			m_cServerSocket.AsyncSelect(FD_CLOSE);

			FHMessage* pRecvMsg;
			if (NULL != m_pcArcIn) {
				*m_pcArcIn >> pRecvMsg;
			}

			// ���´򿪽��������¼�

			m_cServerSocket.AsyncSelect(FD_READ|FD_CLOSE);
		}
		

		break;
	default:
		break;

	}

	*/

}

BEGIN_MESSAGE_MAP(FHSocketThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHSocketThread, CWinThread)
END_DISPATCH_MAP()

// ע��: ������� IID_IFHSocketThread ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {02B16F69-6C11-45F2-BB20-0CD474B05ED2}
static const IID IID_IFHSocketThread =
{ 0x2B16F69, 0x6C11, 0x45F2, { 0xBB, 0x20, 0xC, 0xD4, 0x74, 0xB0, 0x5E, 0xD2 } };

BEGIN_INTERFACE_MAP(FHSocketThread, CWinThread)
	INTERFACE_PART(FHSocketThread, IID_IFHSocketThread, Dispatch)
END_INTERFACE_MAP()


// FHSocketThread ��Ϣ�������
