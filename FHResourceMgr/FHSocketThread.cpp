// FHSocketThread.cpp : 实现文件
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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CWinThread::OnFinalRelease();
}

BOOL FHSocketThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化

	if (!AfxSocketInit()) // 初始化CSocket必须调用的

	{

		return CWinThread::InitInstance(); // 立刻退出

	}


	//{对服务端Socket附加的socket句柄}

	//if(m_cServerSocket.Attach(m_uSocket)) // 重新Attach之前传入的Socket

	{

		m_cServerSocket.m_pcThread = this; // 告诉CSocket它所附加工作的线程

		//m_cServerSocket.m_thrdIndex = m_thrdIndex;

		//m_serverSocket.m_pSerDlg = m_pSerDlg;

		// 建立CSocketFile，将CSocket附加在上面

		//{把服务端Socket绑定到sockfile上，通信采用文件流方式进行}

		//m_pcSocketFile = new CSocketFile(&m_cServerSocket);

		// 输入CArchive

		//m_pcArcIn = new CArchive(m_pcSocketFile, CArchive::load);

		// 输出CArchive

		//m_pcArcOut = new CArchive(m_pcSocketFile, CArchive::store);

		return TRUE; // 这样线程就不会立刻退出

	}

	int errorCode = ::GetLastError();
	return CWinThread::InitInstance(); // 立刻退出
}

int FHSocketThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
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

		// 接收数据

		// 先把接收数据事件关掉

		//{关闭接受数据，避免后续接受数据不停传来，造成处理堵塞，这样读写一次完成}

		if (NULL != m_cServerSocket) {
			m_cServerSocket.AsyncSelect(FD_CLOSE);

			FHMessage* pRecvMsg;
			if (NULL != m_pcArcIn) {
				*m_pcArcIn >> pRecvMsg;
			}

			// 重新打开接收数据事件

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

// 注意: 我们添加 IID_IFHSocketThread 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {02B16F69-6C11-45F2-BB20-0CD474B05ED2}
static const IID IID_IFHSocketThread =
{ 0x2B16F69, 0x6C11, 0x45F2, { 0xBB, 0x20, 0xC, 0xD4, 0x74, 0xB0, 0x5E, 0xD2 } };

BEGIN_INTERFACE_MAP(FHSocketThread, CWinThread)
	INTERFACE_PART(FHSocketThread, IID_IFHSocketThread, Dispatch)
END_INTERFACE_MAP()


// FHSocketThread 消息处理程序
