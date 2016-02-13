// FHAcceptThread.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHAcceptThread.h"
#include "FHCommThread.h"
#include "FHSocket.h"
#include "FHAcceptSocket.h"
#include "FHCommSocket.h"

// FHAcceptThread

IMPLEMENT_DYNCREATE(FHAcceptThread, CWinThread)

FHAcceptThread::FHAcceptThread()
:m_szKeyIndex(0)
{
	EnableAutomation();
}

FHAcceptThread::~FHAcceptThread()
{
}

BOOL FHAcceptThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_bQuit = FALSE;
	return TRUE;
}

int FHAcceptThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	//m_bQuit = TRUE;
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
						while (m_cVecConnectDetail.end() != m_cVecConnectDetail.find(strKey)) {
							++m_szKeyIndex;
							strKey.Format("%u", m_szKeyIndex);	// format twice ?
						}
						
						cChannelDetail.machineInfo.key = strKey;
						m_cVecConnectDetail[strKey] = cChannelDetail;
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

void FHAcceptThread::RegisterSocket(const SOCKET& hSocket)
{
	m_hSocket = hSocket;
	m_pcSocket = new FHAcceptSocket(hSocket);
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
	std::map<CString,FH_CommChannelDetail>::iterator it = m_cVecConnectDetail.find(key);
	if (m_cVecConnectDetail.end() != it) {
		return it->second.pcCommSocket;
	}
	return NULL;
}

// FHAcceptThread 消息处理程序
