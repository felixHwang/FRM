#include "StdAfx.h"
#include "resource.h"
#include "FHServerManager.h"
#include "FHAcceptThread.h"
#include "FHAcceptSocket.h"

FHServerManager::FHServerManager(void)
:m_pcAcceptThread(NULL)
,m_pcAcceptSocket(NULL)
{
}

FHServerManager::~FHServerManager(void)
{
}


int FHServerManager::StartListen(const CString cStrAddr, const unsigned int port /*= FH_DEFAULT_CONNECT_PORT*/)
{
	if (NULL == m_pcAcceptSocket) {
		m_pcAcceptSocket = new FHAcceptSocket();
		m_pcAcceptSocket->CreateSocket(port);
	}
	if (NULL != m_pcAcceptSocket) {
		if (!m_pcAcceptSocket->StartConnect(cStrAddr)) {
			return m_pcAcceptSocket->GetErrorCode();
		}

		if (NULL == m_pcAcceptThread) {
			m_pcAcceptThread = (FHAcceptThread*)AfxBeginThread(RUNTIME_CLASS(FHAcceptThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		}
		if (NULL != m_pcAcceptThread) {
			m_pcAcceptThread->RegisterSocket(m_pcAcceptSocket);
			m_pcAcceptThread->ResumeThread();
			m_pcAcceptThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCONNECT, 0);
		}
	}
	return FH_ERR_NOERROR;
}

BOOL FHServerManager::StopListen()
{
	if (NULL != m_pcAcceptThread) {
		m_pcAcceptThread->SuspendThread();
	}

	if (NULL != m_pcAcceptSocket) {
		m_pcAcceptSocket->CloseSocket();
	}

	if (NULL != m_pcAcceptThread) {
		m_pcAcceptThread->UnRegisterSocket();
	}

	if (NULL != m_pcAcceptSocket) {
		delete m_pcAcceptSocket;
		m_pcAcceptSocket = NULL;
	}
	return TRUE;
}

FHSocket* FHServerManager::GetChannelSocket(CString key)
{
	if (NULL != m_pcAcceptThread) {
		return m_pcAcceptThread->GetChannelSocket(key);
	}
	return NULL;
}
