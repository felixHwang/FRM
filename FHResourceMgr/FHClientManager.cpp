#include "StdAfx.h"
#include "resource.h"
#include "FHClientManager.h"
#include "FHConnectThread.h"
#include "FHConnectSocket.h"

FHClientManager::FHClientManager(void)
:m_pcConnectThread(NULL)
,m_pcConnectSocket(NULL)
,m_cHostname("Unknow")
{
	
}

FHClientManager::~FHClientManager(void)
{
	if (NULL != m_pcConnectThread) {
		m_pcConnectThread->StopThread();
	}

	if (NULL != m_pcConnectSocket) {
		m_pcConnectSocket->CloseSocket();
		delete m_pcConnectSocket;
		m_pcConnectSocket = NULL;
	}

	if (NULL != m_pcConnectThread) {
		m_pcConnectThread->UnRegisterSocket();
		m_pcConnectThread = NULL;
	}
}

int FHClientManager::StartConnect(const CString cStrAddr, const unsigned int port /*= FH_DEFAULT_CONNECT_PORT*/)
{
	if (NULL == m_pcConnectSocket) {
		m_pcConnectSocket = new FHConnectSocket();
		m_pcConnectSocket->CreateSocket(port);
	}
	if (NULL != m_pcConnectSocket) {
		if (!m_pcConnectSocket->StartConnect(cStrAddr)) {
			return m_pcConnectSocket->GetErrorCode();
		}

		if (NULL == m_pcConnectThread) {
			m_pcConnectThread = (FHConnectThread*)AfxBeginThread(RUNTIME_CLASS(FHConnectThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		}
		if (NULL != m_pcConnectThread) {
			m_pcConnectThread->RegisterSocket(m_pcConnectSocket);
			m_pcConnectThread->ResumeThread();
			m_pcConnectThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCONNECT, 0);
		}
	}

	InitMachineInfo();
	return 0;
}

BOOL FHClientManager::StopConnect()
{
	if (NULL != m_pcConnectThread) {
		m_pcConnectThread->SuspendThread();
	}

	if (NULL != m_pcConnectSocket) {
		m_pcConnectSocket->CloseSocket();
	}

	if (NULL != m_pcConnectThread) {
		m_pcConnectThread->UnRegisterSocket();
	}

	if (NULL != m_pcConnectSocket) {
		delete m_pcConnectSocket;
		m_pcConnectSocket = NULL;
	}
	return TRUE;
}

void FHClientManager::InitMachineInfo()
{
	char hostname[256];

	if(0 == gethostname(hostname, sizeof(hostname))) {
		m_cHostname = hostname;
		// CA2W
		// 这是获取主机名，如果获得主机名成功的话，将返回一个指针，指向hostinfo，hostinfo
		// PHOSTENT hostinfo;
		//int lenAnsi = strlen(hostname);
		//TCHAR* pTmpStr = new TCHAR[sizeof(TCHAR)*lenAnsi];
		//memset(pTmpStr,0,lenAnsi*sizeof(TCHAR));
		//MultiByteToWideChar(CP_ACP, 0, hostname, -1, pTmpStr, sizeof(TCHAR)*lenAnsi);
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

	if (NULL != m_pcConnectSocket) {
		FHMessage cMsg;
		cMsg.SetCommandID(FH_COMM_MACHINEINFO);
		cMsg.SetMachineInfo(FH_MSG_MachineInfo(CString(hostname,strlen(hostname))));
		m_pcConnectSocket->SendMessage(cMsg);
	}
}

const CString& FHClientManager::GetHostname()
{
	return m_cHostname;
}
