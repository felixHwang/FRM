// FHConnectSocket.cpp : ʵ���ļ�
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


// FHConnectSocket ��Ա����
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
		//��ò�Ҫʹ��aSocket.Create��������Ϊ���׻����10048����
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

		 //����Socket��ѡ��, ���10048�������Ĳ���
		this->SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);
		*/

		//this->AsyncSelect(FD_READ|FD_CLOSE|FD_CONNECT|FD_ACCEPT);
		 //����
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
			//�����ⲿ����
			if(!this->Accept(serverSocket))
			{
				continue;
			}
			else
			{
				char szRecvMsg[256] = {0};
				char szOutMsg[256] = {0};    
	            
					//���տͻ�������:����
				serverSocket.Receive(szRecvMsg, 256);

				sprintf(szOutMsg, "Receive Msg: %s  ", szRecvMsg);
	            

				/*
				aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);
	            
				strText += szOutMsg;
	            
				aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);
		 */
					//�������ݸ��ͻ���
		/*
				serverSocket.Send("Have Receive The Msg", 50);

					//�ر�
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

			//�������ݸ�������
			CString strText = _T("client reply");
			this->Send(strText, strText.GetLength());

			//���շ��������ͻ���������(�÷���������, �ڴ˵ȴ������ݽ��յ��ż�������ִ��)
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
	    
			//�ر�
		//aSocket.Close();
		//serverSocket.Close();
	    
		//aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);
	    
		//strText += "Have Close!";
	    
		//aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);

	/*
	    
		//�󶨶˿�
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
	// TODO: �ڴ����ר�ô����/����û���

	FHSocketThread* pcThread;
	if(0 == nErrorCode)

	{
		// ����һ������Socket

		FHConnectSocket connectSocket(FH_TYPE_SOCKET_NORMOL);

		Accept(connectSocket); // connectSocket���Ϳͻ�������


		// ����һ���߳�

		pcThread = (FHSocketThread*)AfxBeginThread(RUNTIME_CLASS(FHSocketThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		//{�����Socket�õ��ͷ������ӣ�Ҫ����һ�����ӵ�Socket��ͻ�������ͨ�ţ��Ժ��������Socket��ͻ��˰�ͨ�ţ�������һ���߳���Ϊ����Socket����}

		// ��ӵ��̳߳���

		//m_pSerDlg->m_csThrdList.Lock(); // ����

		//m_pSerDlg->m_thrdList.push_back(pThread);

		//m_pSerDlg->m_csThrdList.Unlock(); // ����

		//pThread->m_pSerDlg = m_pSerDlg;

		/*

		* ��CSocket�����½����߳�

		* �������CSocket�����½����߳�һ����

		* ע���������ڽ����߳��У���Ϊ�Ǽ���CSocket����CServerDlg�ĳ�Ա����

		* ����ͨ��Detach()�õ�HANDLE֮���ڹ����߳�������Attach()����

		*/

		//{��ΰѴ�����Socket�󶨵��½��Ĺ����߳��У������÷����Socket������Ӧ�ó����У���Detach��attach��Socket���н�󡢼Ӱ󣬼������߳��д���������Socket���뿪�����̣߳������ڹ����߳���}
/*
		pcThread->m_hSocket = connectSocket.Detach();

		BOOL flag =  pcThread->m_cServerSocket.Attach(pcThread->m_hSocket);
		

		// �̱߳�ţ�ͨ�������ͨ��ʱ����ͬ�Ŀͻ���

		//{������ָ������̣߳���ͻ�������ͨ�ŵ�Socket����ͨ�����������̣߳��е�id��ʾ}

		//pcThread->m_thrdIndex = m_pSerDlg->m_thrdIndex++;

		// �����߳�

		pcThread->ResumeThread();

	}
*/
	
	//CSocket::OnAccept(nErrorCode);

}


void FHConnectSocket::OnReceive(int nErrorCode)

{

	// ͨ���Զ�����ϢWM_THREAD����Ϣ����WP_RECV֪ͨ�߳�ȥ��ȡ����

	//{��Socket�󶨵��߳�ͨ����Ϣȥ֪ͨ��������}

	//m_pcThread->PostThreadMessage(FH_WM_THREAD, FH_MSCMD_RECV, 0);

	//CSocket::OnReceive(nErrorCode);

}