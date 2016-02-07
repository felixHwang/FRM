// FHWinThread.cpp : 实现文件
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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CWinThread::OnFinalRelease();
}

BOOL FHWinThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_bQuit = FALSE;
	return TRUE;
}

int FHWinThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	m_bQuit = TRUE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(FHWinThread, CWinThread)
	ON_THREAD_MESSAGE(FH_WM_THREAD, OnCallBack)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHWinThread, CWinThread)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFHWinThread 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

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


// FHWinThread 消息处理程序
