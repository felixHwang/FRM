#include "stdafx.h"
#include "resource.h"
#include "FHFile.h"
#include "FHClientManager.h"
#include "FHConnectThread.h"
#include "FHConnectSocket.h"

FHClientManager::FHClientManager(void)
:m_pcConnectThread(NULL)
,m_pcConnectSocket(NULL)
,m_cHostname("Unknow")
,m_cCurrWorkingPath("")
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

	char currPath[257];
	GetCurrentDirectory(sizeof(currPath), currPath);
	m_cCurrWorkingPath = currPath;
	//SendServerDirInfo(currPath);
	return 0;
}

BOOL FHClientManager::StopConnect()
{
	if (NULL != m_pcConnectThread) {
		// m_pcConnectThread->SuspendThread();
		m_pcConnectThread->StopThread();
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

const CString& FHClientManager::GetHostName()
{
	if ("Unknow" == m_cHostname) {
		char hostname[257];
		if(0 == gethostname(hostname, sizeof(hostname))) {
			m_cHostname = hostname;
		}
	}
	return m_cHostname;
}

BOOL FHClientManager::SendServerDirInfo(CString strFilePath)
{
	if (NULL != m_pcConnectSocket) {
		FHFile cfile;
		FH_MSG_FileInfo cFileInfo;
		CString strFilePathNew = strFilePath;
		if ("" == strFilePathNew) {
			strFilePathNew = m_cCurrWorkingPath;
		}

		if (cfile.GetFileList(strFilePathNew, cFileInfo)) {
			m_cCurrWorkingPath = strFilePathNew;
			FHMessage cMsg;
			cMsg.SetCommandID(FH_COMM_FILEINFO);
			cMsg.SetFileInfo(cFileInfo);
			m_pcConnectSocket->SendMessage(cMsg);
			return TRUE;
		}
	}
	return FALSE;
}

void FHClientManager::InitMachineInfo()
{
	if (NULL != m_pcConnectSocket) {
		FHMessage cMsg;
		cMsg.SetCommandID(FH_COMM_MACHINEINFO);
		cMsg.SetMachineInfo(FH_MSG_MachineInfo(GetHostName()));
		m_pcConnectSocket->SendMessage(cMsg);
	}
}
