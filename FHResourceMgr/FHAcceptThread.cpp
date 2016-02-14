// FHAcceptThread.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHSocket.h"
#include "FHAcceptThread.h"
#include "FHAcceptSocket.h"
#include "FHCommSocket.h"
#include "FHCommThread.h"

// FHAcceptThread

IMPLEMENT_DYNCREATE(FHAcceptThread, CWinThread)

FHAcceptThread::FHAcceptThread()
:m_pcAcceptSocket(NULL)
,m_bQuit(FALSE)
,m_szKeyIndex(0)
{
	EnableAutomation();
}

FHAcceptThread::~FHAcceptThread()
{
}

BOOL FHAcceptThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int FHAcceptThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHAcceptThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

void FHAcceptThread::OnCallBack(WPARAM wParam,LPARAM lParam)
{
	SOCKADDR_IN		sAddr;
	int				nAddrLen;
	SOCKET			hSocket;

	while(!m_bQuit)
	{
		nAddrLen = sizeof(SOCKADDR_IN);
		memset(&sAddr, 0, nAddrLen);

		if (NULL != m_pcAcceptSocket) {
			if(m_pcAcceptSocket->Accept(hSocket, (SOCKADDR *)&sAddr, &nAddrLen)) {

				FH_CommChannelDetail cChannelDetail;
				cChannelDetail.pcCommSocket = new FHCommSocket(hSocket);
				if (NULL != cChannelDetail.pcCommSocket) {
					cChannelDetail.pcCommThread = (FHCommThread*)AfxBeginThread(RUNTIME_CLASS(FHCommThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
					if (NULL != cChannelDetail.pcCommThread) {
						CString strKey;
						strKey.Format("%u", m_szKeyIndex);
						while (m_cMapConnectDetail.end() != m_cMapConnectDetail.find(strKey)) {
							++m_szKeyIndex;
							strKey.Format("%u", m_szKeyIndex);
						}
						
						cChannelDetail.machineInfo.key = strKey;
						m_cMapConnectDetail[strKey] = cChannelDetail;
						cChannelDetail.pcCommThread->RegisterSocket(cChannelDetail.pcCommSocket);
						cChannelDetail.pcCommThread->SetIdentifyKey(strKey);
						++m_szKeyIndex;

						cChannelDetail.pcCommThread->ResumeThread();

						cChannelDetail.pcCommThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_STARTCOMM, 0);
					}
					else {
						cChannelDetail.pcCommSocket->CloseSocket();
						delete cChannelDetail.pcCommSocket;
					}
				}	
			}
		}
		else {
			m_pcAcceptSocket->DisplayErrMessageBox("接收客户端连接失败", m_pcAcceptSocket->GetErrorCode());
		}
	}
}

void FHAcceptThread::RegisterSocket(FHAcceptSocket* pcSocket)
{
	if (NULL != pcSocket) {
		m_pcAcceptSocket = pcSocket;
	}
}

void FHAcceptThread::UnRegisterSocket()
{
	m_pcAcceptSocket = NULL;
}

FHSocket* FHAcceptThread::GetChannelSocket(CString key)
{
	std::map<CString,FH_CommChannelDetail>::iterator it = m_cMapConnectDetail.find(key);
	if (m_cMapConnectDetail.end() != it) {
		return it->second.pcCommSocket;
	}
	return NULL;
}

void FHAcceptThread::RemoveCommChannel(CString key)
{
	std::map<CString,FH_CommChannelDetail>::iterator it = m_cMapConnectDetail.find(key);
	if (m_cMapConnectDetail.end() != it) {
		FH_CommChannelDetail item = it->second;
		m_cMapConnectDetail.erase(it);
		if (NULL != item.pcCommSocket) {
			item.pcCommSocket->CloseSocket();
		}

		if (NULL != item.pcCommThread) {
			item.pcCommThread->StopThread();
			item.pcCommThread->UnRegisterSocket();
		}

		if (NULL != item.pcCommSocket) {
			delete item.pcCommSocket;
		}
		
	}
}

void FHAcceptThread::StopThread()
{
	while (0 < m_cMapConnectDetail.size()) {
		CString key = m_cMapConnectDetail.begin()->first;
		RemoveCommChannel(key);
	}
	m_bQuit = TRUE;
	DWORD dwCode = 0;
	TerminateThread(this->m_hThread, dwCode);
	CloseHandle(this->m_hThread);
}