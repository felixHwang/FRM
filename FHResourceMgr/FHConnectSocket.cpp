// FHConnectSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHConnectSocket.h"
#include "FHSocketThread.h"


// FHConnectSocket

FHConnectSocket::FHConnectSocket()
:FHSocket(FH_SOCKET_TYPE_CLIENT)
{
}

FHConnectSocket::FHConnectSocket(const SOCKET socket)
:FHSocket(FH_SOCKET_TYPE_CLIENT, socket)
{

}

FHConnectSocket::~FHConnectSocket()
{
}


// FHConnectSocket 成员函数
BOOL FHConnectSocket::CreateSocket(UINT uiPort)
{
	return FHSocket::CreateSocket(uiPort);
}

BOOL FHConnectSocket::StartConnect(CString cStrAddr)
{

	return FHSocket::StartConnect(cStrAddr);
	/*
	AfxSocketInit();
	m_cAddr = cStrAddr;
	if (FH_TYPE_SOCKET_SERVER == m_eSocketType) {

			/*
		  if (!AfxSocketInit())
		{
			AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
			return 1;
		}

		m_exit = false;

		CServerDlg *aDlg = (CServerDlg *)lParam;

		CString strPort;
	    
		aDlg->GetDlgItemText(IDC_EDIT_PORT, strPort);
	    
		UINT nPort = atoi(strPort);
	    
		//socket------------------------------------------------
		*/
		//FHConnectSocket serverSocket;
		//最好不要使用aSocket.Create创建，因为容易会出现10048错误
		/*
		if (!this->Socket())
		{
		   // TCHAR szError[256] = {0};
	        
		   // sprintf(szError, _T("Create Faild: %d"), GetLastError());
	        
		   // AfxMessageBox(szError);
	        
			return FALSE; 
		}
		
		BOOL bOptVal = TRUE;
		int bOptLen = sizeof(BOOL);

		 //设置Socket的选项, 解决10048错误必须的步骤
		this->SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);
		*/

		//this->AsyncSelect(FD_READ|FD_CLOSE|FD_CONNECT|FD_ACCEPT);
		 //监听
	/*
		if(!this->Listen(10))
		{    
			//char szError[256] = {0};
	        
			//sprintf(szError, "Listen Faild: %d", GetLastError());
	        
			//AfxMessageBox(szError);
	        
			return FALSE;
		}
	    

		/*
		CString strText;
	    
		aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);
	    
		strText += "Server Start!  ";
	    
		aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);

		*/

		/*
		while(TRUE)
		{
			//接收外部连接
			if(!this->Accept(serverSocket))
			{
				continue;
			}
			else
			{
				char szRecvMsg[256] = {0};
				char szOutMsg[256] = {0};    
	            
					//接收客户端内容:阻塞
				serverSocket.Receive(szRecvMsg, 256);

				sprintf(szOutMsg, "Receive Msg: %s  ", szRecvMsg);
	            

				/*
				aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);
	            
				strText += szOutMsg;
	            
				aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);
		 */
					//发送内容给客户端
		/*
				serverSocket.Send("Have Receive The Msg", 50);

					//关闭
				serverSocket.Close();
			}
	        */
		//}
		//return TRUE;
	//}
	//else {
	/*
		if (this->Connect(m_cAddr, m_szPort))
		{

			return TRUE;
			char szRecValue[1024] = {0};

			//发送内容给服务器
			CString strText = _T("client reply");
			this->Send(strText, strText.GetLength());

			//接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
			this->Receive((void *)szRecValue, 1024);

			//AfxMessageBox(szRecValue);
		}
		/*
		else
		{
			char szMsg[1024] = {0};

			sprintf(szMsg, "create faild: %d", aSocket.GetLastError());

			AfxMessageBox(szMsg);
		}
		*/
		
	//}

	//this->Close();
	    
			//关闭
		//aSocket.Close();
		//serverSocket.Close();
	    
		//aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);
	    
		//strText += "Have Close!";
	    
		//aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);

	/*
	    
		//绑定端口
		if (!aSocket.Bind(nPort))
		{
			char szError[256] = {0};
	            
			sprintf(szError, "Bind Faild: %d", GetLastError());
	            
			AfxMessageBox(szError);
	            
			return 1; 
		}

			this->Listen(5);
			CSocket cSocketRecv;
			this->Accept(cSocketRecv);
		}
		else {
			this->Connect(m_cAddr.GetString(), m_szPort);
		}
*/
	//return FALSE;
}

void FHConnectSocket::OnAccept(int nErrorCode)

{
/*
	// TODO: 在此添加专用代码和/或调用基类

	FHSocketThread* pcThread;
	if(0 == nErrorCode)

	{
		// 创建一个连接Socket

		FHConnectSocket connectSocket(FH_TYPE_SOCKET_NORMOL);

		Accept(connectSocket); // connectSocket将和客户端连接


		// 创建一个线程

		pcThread = (FHSocketThread*)AfxBeginThread(RUNTIME_CLASS(FHSocketThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		//{服务端Socket得到客服端连接，要创建一个连接的Socket与客户端连接通信（以后这个连接Socket与客户端绑定通信），创建一个线程来为连接Socket服务}

		// 添加到线程池中

		//m_pSerDlg->m_csThrdList.Lock(); // 加锁

		//m_pSerDlg->m_thrdList.push_back(pThread);

		//m_pSerDlg->m_csThrdList.Unlock(); // 解锁

		//pThread->m_pSerDlg = m_pSerDlg;

		/*

		* 将CSocket交给新建的线程

		* 这样这个CSocket将和新建的线程一起工作

		* 注意现在是在界面线程中，因为是监听CSocket，是CServerDlg的成员变量

		* 必须通过Detach()得到HANDLE之后在工作线程中重新Attach()才行

		*/

		//{如何把创建的Socket绑定到新建的工作线程中？现在用服务端Socket是在主应用程序中，用Detach、attach对Socket进行解绑、加绑，即把主线程中创建的连接Socket“离开”主线程，附加在工作线程上}
/*
		pcThread->m_hSocket = connectSocket.Detach();

		BOOL flag =  pcThread->m_cServerSocket.Attach(pcThread->m_hSocket);
		

		// 线程编号，通过这个在通信时区别不同的客户端

		//{如何区分各工作线程（与客户端连接通信的Socket）？通过主程序（主线程）中的id标示}

		//pcThread->m_thrdIndex = m_pSerDlg->m_thrdIndex++;

		// 启动线程

		pcThread->ResumeThread();

	}
*/
	
	//CSocket::OnAccept(nErrorCode);

}


void FHConnectSocket::OnReceive(int nErrorCode)

{

	// 通过自定义消息WM_THREAD和消息参数WP_RECV通知线程去读取数据

	//{由Socket绑定的线程通过消息去通知接收数据}

	//m_pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_RECV, 0);

	//CSocket::OnReceive(nErrorCode);

}