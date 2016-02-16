#include "StdAfx.h"
#include "FHSocket.h"
#include "FHPublicDefine.h"
#include "stdafx.h"
#include "FHLog.h"
#include "FHResourceMgr.h"
#include "FHConnectThread.h"
#include "FHAcceptThread.h"

#define FH_MSG_BUFFER_SIZE	SO_RCVBUF
#define FH_WRITE4BYTE(DESBUFFER, ORIBUFFER)	memcpy(DESBUFFER, ORIBUFFER, 4);
#define FH_WRITESTRING(DESBUFFER, ORIBUFFER, WRITELEN)	memcpy(DESBUFFER, ORIBUFFER, WRITELEN);

FHSocket::FHSocket(const FH_SOCKET_TYPE type)
:m_eSocketType(type)
,m_hSocket(-1)
,m_pcRecvBuffer(NULL)
,m_pcRemainBuffer(NULL)
,m_iRemainPos(0)
,m_bLastMsg(FALSE)
{
	m_pcRecvBuffer = new char[FH_MSG_BUFFER_SIZE];
	m_pcRemainBuffer = new char[FH_MSG_BUFFER_SIZE];
}

FHSocket::FHSocket(const FH_SOCKET_TYPE type, const SOCKET socket)
:m_eSocketType(type)
,m_hSocket(socket)
,m_pcRecvBuffer(NULL)
,m_pcRemainBuffer(NULL)
,m_iRemainPos(0)
,m_bLastMsg(FALSE)
{
	// SO_RCVBUF > SO_SNDBUF
	m_pcRecvBuffer = new char[FH_MSG_BUFFER_SIZE];
	m_pcRemainBuffer = new char[FH_MSG_BUFFER_SIZE];
	m_cLastMsg.Clear();
}

FHSocket::~FHSocket(void)
{
	CloseSocket();

	if (NULL != m_pcRecvBuffer) {
		delete[] m_pcRecvBuffer;
		m_pcRecvBuffer = NULL;
	}
	if (NULL != m_pcRemainBuffer) {
		delete[] m_pcRemainBuffer;
		m_pcRemainBuffer = NULL;
	}
}

BOOL FHSocket::CreateSocket(UINT uiPort /*= FH_DEFAULT_CONNECT_PORT*/)
{
	m_szPort = uiPort;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	BOOL bNodelay=TRUE;
	BOOL bDebug=TRUE;
	//setsockopt(m_hSocket, IPPROTO_TCP,TCP_NODELAY,(const char*)&bNodelay,sizeof(BOOL));
	//setsockopt(m_hSocket, SOL_SOCKET,SO_DEBUG,(const char*)&bDebug,sizeof(BOOL));   

	return TRUE;
}

BOOL FHSocket::StartConnect(CString cStrAddr)
 {
	m_cAddr = cStrAddr;
	//m_cAddr = "127.0.0.1";

	unsigned long aip = inet_addr(m_cAddr.GetString());
	SOCKADDR_IN socketAddr ;
	memset(&socketAddr, 0, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(m_szPort);
	if (FH_SOCKET_TYPE_SERVER == m_eSocketType)
		socketAddr.sin_addr.S_un.S_addr = ADDR_ANY;
	else if (FH_SOCKET_TYPE_CLIENT == m_eSocketType)
		socketAddr.sin_addr.S_un.S_addr = aip;

	if (FH_SOCKET_TYPE_SERVER == m_eSocketType) {
		ClearError();
		int retCode = bind(m_hSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));
		
		if(SOCKET_ERROR == listen(m_hSocket, 10))
		{
			SetErrorCode(GetLastError());
			return FALSE;
		}
	}
	else if (FH_SOCKET_TYPE_CLIENT == m_eSocketType) {
		ClearError();
		int retCode =  connect(m_hSocket, (sockaddr*)&socketAddr, sizeof(SOCKADDR));
		if (0 != retCode) {
			SetErrorCode(retCode);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL FHSocket::CloseSocket()
{
	if (INVALID_SOCKET != m_hSocket) {
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
	return TRUE;
}

BOOL FHSocket::SendMessage(const FHMessage& cMsg)
{
	ClearError();
	
	int tmp = cMsg.GetCommandID();
	char* pWrite = m_pcRecvBuffer + sizeof(int);
	memcpy(pWrite, &tmp, sizeof(tmp));
	pWrite += sizeof(int);

	if (FH_COMM_MACHINEINFO == tmp) {
		tmp = cMsg.GetMachineInfo().hostname.GetLength();
		memcpy(pWrite, &tmp, sizeof(int));
		pWrite += sizeof(int);	
		memcpy(pWrite,  cMsg.GetMachineInfo().hostname.GetString(), tmp);
		tmp += sizeof(int)*3;
		memcpy(m_pcRecvBuffer, &tmp, sizeof(int));
		tmp = Send(m_hSocket, m_pcRecvBuffer, tmp, 0);
		if (SOCKET_ERROR == tmp) {
			DisplayErrMessageBox(_T("发送客户端信息到服务器失败"), GetLastError());
			return FALSE;
		}
		else {
			// DisplayErrMessageBox(_T("发送机器信息到服务器成功"), tmp);
		}
	}
	else if (FH_COMM_OPEINFO == tmp) {
		int totalSize = 12;
		FH_MSG_OperatorInfo opeInfo = cMsg.GetOperatorInfo();
		tmp = opeInfo.operatorCode;
		FH_WRITE4BYTE(pWrite, &tmp)
		pWrite += 4;
		for (size_t i=0; i<opeInfo.opeItemVec.size(); ++i) {
			tmp = opeInfo.opeItemVec[i].lenFilePath;
			FH_WRITE4BYTE(pWrite, &tmp)
			pWrite += 4;
			FH_WRITESTRING(pWrite, opeInfo.opeItemVec[i].filePath.GetString(), tmp)
			pWrite += tmp;

			totalSize = totalSize + 4 + tmp;
		}

		FH_WRITE4BYTE(m_pcRecvBuffer, &totalSize)
		tmp = Send(m_hSocket, m_pcRecvBuffer, totalSize, 0);
		if (SOCKET_ERROR == tmp || tmp != totalSize) {
			DisplayErrMessageBox(_T("发送命令信息到客户端失败"), GetLastError());
			return FALSE;
		}
		else {
			// DisplayErrMessageBox(_T("发送命令信息到客户端成功"), tmp);
		}	
	}
	else if (FH_COMM_FILEINFO == tmp) {
		// calculate msg size
		const int itemFixedSize = 4*3 + 10;
		const FH_MSG_FileInfo& fileInfo = cMsg.GetFileInfo();
		int totalSize = fileInfo.lenFilePath + 12;
		for (size_t i=0; i<fileInfo.fileItemVec.size(); ++i) {
			totalSize += itemFixedSize + fileInfo.fileItemVec[i].lenFilename;
		}
		FH_WRITE4BYTE(m_pcRecvBuffer, &totalSize)
		
		tmp = fileInfo.lenFilePath;
		FH_WRITE4BYTE(pWrite, &tmp)
		pWrite += sizeof(tmp);
		int restSize = FH_MSG_BUFFER_SIZE - (pWrite-m_pcRecvBuffer);
		FH_WRITESTRING(pWrite, fileInfo.filePath.GetString(), tmp);
		pWrite += tmp;
		restSize -= tmp;

		for (size_t i=0; i<fileInfo.fileItemVec.size(); ++i) {
			if (-1 != fileInfo.fileItemVec[i].filename.Find("54")) {
				int i = 0;
			}
			if (itemFixedSize + fileInfo.fileItemVec[i].lenFilename > restSize) {
				tmp = Send(m_hSocket, m_pcRecvBuffer, pWrite-m_pcRecvBuffer, 0);
				if (SOCKET_ERROR == tmp) {
					SetErrorCode(GetLastError());
					DisplayErrMessageBox(_T("发送文件信息到服务器失败"), GetLastError());
					return FALSE;
				}
				else {
					// DisplayErrMessageBox(_T("缓冲区满，发送文件信息到服务器成功"), tmp);
				}

				restSize = FH_MSG_BUFFER_SIZE;
				pWrite = m_pcRecvBuffer;
			}

			tmp = fileInfo.fileItemVec[i].fileType;
			FH_WRITE4BYTE(pWrite, &tmp)
			pWrite += 4;
			restSize -= 4;

			tmp = fileInfo.fileItemVec[i].fileSize;
			FH_WRITE4BYTE(pWrite, &tmp)
			pWrite += 4;
			restSize -= 4;

			tmp = fileInfo.fileItemVec[i].lenFilename;
			FH_WRITE4BYTE(pWrite, &tmp)
			pWrite += 4;
			restSize -= 4;

			FH_WRITESTRING(pWrite, fileInfo.fileItemVec[i].filename.GetString(), tmp)
			pWrite += tmp;
			restSize -= tmp;

			tmp = 10;
			FH_WRITESTRING(pWrite, fileInfo.fileItemVec[i].fileCreateTime.GetString(), tmp)
			pWrite += tmp;
			restSize -= tmp;
		}

		tmp = Send(m_hSocket, m_pcRecvBuffer, pWrite-m_pcRecvBuffer, 0);
		if (SOCKET_ERROR == tmp) {
			SetErrorCode(GetLastError());
			DisplayErrMessageBox(_T("发送文件信息到服务器失败"), GetLastError());
			return FALSE;
		}
		else {
			// DisplayErrMessageBox(_T("发送文件信息到服务器成功"), tmp);
		}
	}

	return TRUE;
}

BOOL FHSocket::ParseRecvMessage(const char* pcData, const int recvSize)
{
	int totalSize = *((int*)pcData);
	const char* pRead = pcData + sizeof(int);
	int commandID = *((int*)pRead);
	pRead += sizeof(int);

	if (FH_COMM_MACHINEINFO == commandID) {
		int len = *((int*)pRead);
		pRead += sizeof(int);
		CString strName(pRead, len);
		FHMessage cMsg;
		cMsg.SetCommandID(commandID);
		cMsg.SetMachineInfo(FH_MSG_MachineInfo(strName));
		m_cListMsg.AddTail(cMsg);
		m_iRemainPos = 0;
	}
	else if (FH_COMM_OPEINFO == commandID) {
		int code = *((int*)pRead);
		pRead += sizeof(int);
		int len = *((int*)pRead);
		pRead += sizeof(int);
		CString strFilePath(pRead, len);

		FH_MSG_OperatorInfo::FH_MSG_OperatorInfo_Item item;
		item.lenFilePath = len;;
		item.filePath = strFilePath;
		FH_MSG_OperatorInfo opeInfo;
		opeInfo.opeItemVec.push_back(item);
		opeInfo.operatorCode = code;

		FHMessage cMsg;
		cMsg.SetCommandID(commandID);
		cMsg.SetOperatorInfo(opeInfo);
		m_cListMsg.AddTail(cMsg);
		m_iRemainPos = 0;
	}
	else if (FH_COMM_FILEINFO == commandID) {
		CString strHead;
		strHead.Format("FHSocket::Parse size=%d", recvSize);
		FHLog::DumpFile(strHead, pRead, recvSize);
		FHMessage cMsg;
		cMsg.SetCommandID(commandID);
		FH_MSG_FileInfo cFileInfo;
		if (FALSE == m_bLastMsg) {
			int len = *((int*)pRead);
			pRead += sizeof(int);
			CString filePath(pRead, len);
			pRead += len;
			cFileInfo.lenFilePath = len;
			cFileInfo.filePath = filePath;
		}
		
		int restBufferSize = recvSize - (pRead-pcData);
		while (restBufferSize > 22) {
			FH_MSG_FileInfo::FH_MSG_FileInfo_Item item;
			item.fileType = *((int*)pRead);
			item.fileSize = *(((int*)pRead)+1);
			item.lenFilename = *(((int*)pRead)+2);
			if (restBufferSize >= item.lenFilename + 22) {
				pRead += 12;
				CString filename(pRead, item.lenFilename);
				item.filename = filename;
				if (item.filename=="resource.h") {
					int i = 0;
				}
				pRead += item.lenFilename;
				CString createTime(pRead, 10);
				item.fileCreateTime = createTime;
				pRead += 10;

				restBufferSize = restBufferSize - 22 -item.lenFilename;
				cFileInfo.fileItemVec.push_back(item);
			}
			else {
				break;
			}
		}

		cMsg.SetFileInfo(cFileInfo);

		totalSize = totalSize - (pRead-pcData);
		
		// 接下来还要消息接收
		if (0 < totalSize) {
			totalSize += 8;
			m_bLastMsg = TRUE;
			m_cLastMsg.MergeFileInfo(cMsg);
			FH_WRITE4BYTE(m_pcRemainBuffer, &totalSize)
			m_iRemainPos = 8;
		}
		else {
			if (m_bLastMsg) {
				m_cLastMsg.MergeFileInfo(cMsg);
				m_cListMsg.AddTail(m_cLastMsg);
			}
			else {
				m_cListMsg.AddTail(cMsg);
			}
			m_bLastMsg = FALSE;
			m_iRemainPos = 0;
			m_cLastMsg.Clear();
		}

		if (0 < restBufferSize) {
			m_iRemainPos = 8;
		
			while (0 != restBufferSize) {
				// 保留大小和命令类型
				m_pcRemainBuffer[m_iRemainPos++] = *pRead++;
				--restBufferSize;

			}
		}
	}
	return TRUE;
}

BOOL FHSocket::RecvMessage()
{
	if (INVALID_SOCKET == m_hSocket) {
		return FALSE;
	}
	ClearError();
	int recvSize = Recv(m_hSocket, m_pcRecvBuffer, FH_MSG_BUFFER_SIZE, 0);
	if (SOCKET_ERROR == recvSize) {
		if (WSAECONNRESET != GetLastError()) {
			this->DisplayErrMessageBox("接收数据失败", GetLastError());
		}
		SetErrorCode(GetLastError());
		return FALSE;
	}
	else {

		// 上次有消息遗留，需要拼接处理
		if (0 < m_iRemainPos) {
			// 获取剩余消息大小和剩余需要接收大小
			int lastSize = *((int*)m_pcRemainBuffer);
			int lastNeed = lastSize - m_iRemainPos;
			// 此次依旧未能接收完全
			if (recvSize < lastNeed) {
				// 缓冲区无法完全装载,部分解析
				if (FH_MSG_BUFFER_SIZE < m_iRemainPos+recvSize) {
					int restCopySize = recvSize;
					char* pSrcBuffer = m_pcRecvBuffer;
					while (0 < restCopySize) {
						int canCopySize = restCopySize;
						if (canCopySize+m_iRemainPos > FH_MSG_BUFFER_SIZE) {
							canCopySize = FH_MSG_BUFFER_SIZE - m_iRemainPos;
						}
						
						memcpy(m_pcRemainBuffer+m_iRemainPos, pSrcBuffer, canCopySize);
						pSrcBuffer += canCopySize;
						m_iRemainPos += canCopySize;
						ParseRecvMessage(m_pcRemainBuffer, m_iRemainPos);
						restCopySize -= canCopySize;
					}
				}
				else {
					memcpy(m_pcRemainBuffer+m_iRemainPos, m_pcRecvBuffer, recvSize);
					m_iRemainPos += recvSize;
					return TRUE;
				}
			}
			else {	// 上次遗留消息可以接收完全
				// 读取到完整的消息，并开始解析（遗留消息处理）
				// 缓冲区无法完全装载,部分解析
				if (FH_MSG_BUFFER_SIZE < m_iRemainPos+lastNeed) {
					int restCopySize = lastNeed;
					char* pSrcBuffer = m_pcRecvBuffer;
					while (0 < restCopySize) {
						int canCopySize = restCopySize;
						if (canCopySize+m_iRemainPos > FH_MSG_BUFFER_SIZE) {
							canCopySize = FH_MSG_BUFFER_SIZE - m_iRemainPos;
						}

						memcpy(m_pcRemainBuffer+m_iRemainPos, pSrcBuffer, canCopySize);
						pSrcBuffer += canCopySize;
						m_iRemainPos += canCopySize;
						ParseRecvMessage(m_pcRemainBuffer, m_iRemainPos);
						restCopySize -= canCopySize;
					}
					
				}
				else {
					memcpy(m_pcRemainBuffer+m_iRemainPos, m_pcRecvBuffer, lastNeed);
					m_iRemainPos += lastNeed;
					ParseRecvMessage(m_pcRemainBuffer, m_iRemainPos);
				}

				// 处理剩余的消息
				char* pRead = m_pcRecvBuffer + lastNeed;
				int remaindSize = recvSize - lastNeed;
				int newSize = *((int*)pRead);
				while (0 != remaindSize && newSize <= remaindSize) {
					ParseRecvMessage(pRead, m_iRemainPos);
					remaindSize -= newSize;
					if (0 == remaindSize) {
						break;
					}
					pRead += newSize;
					newSize = *((int*)pRead);
				}
				if (0 != remaindSize) {
					memcpy(m_pcRemainBuffer, pRead, remaindSize);
					m_iRemainPos = remaindSize;
				}
			}
		}
		else { //上次消息未有遗留
			// 逻辑同上
			// 处理剩余的消息
			char* pRead = m_pcRecvBuffer;
			int remaindSize = recvSize;
			int newSize = *((int*)pRead);
			while (newSize <= remaindSize) {
				ParseRecvMessage(pRead, recvSize);
				remaindSize -= newSize;
				if (0 == remaindSize) {
					break;
				}
				pRead += newSize;
				newSize = *((int*)pRead);
			}
			if (0 != remaindSize) {
				memcpy(m_pcRemainBuffer, pRead, remaindSize);
				m_iRemainPos = remaindSize;
			}
		}
	}
	return TRUE;
}

BOOL FHSocket::Accept(SOCKET& socket, sockaddr* addr, int* addrlen)
{

	socket = accept(m_hSocket, addr, addrlen);
	if (INVALID_SOCKET != socket) {
		return TRUE;
	}
	else {
		SetErrorCode(GetLastError());
		return FALSE;
	}
}

CString FHSocket::GetPeerName()
{
	struct sockaddr_in sa;
	int len = sizeof(sa);
	if(!getpeername(m_hSocket, (struct sockaddr *)&sa, &len))
	{
		return CString(inet_ntoa(sa.sin_addr));
	}
	return CString("");
}

void FHSocket::DisplayErrMessageBox(CString str, int err)
{
	CString strErr;
	strErr.Format("[FHSocket]%s,err=%d", str.GetString(), err);
	AfxMessageBox(strErr);
}

BOOL FHSocket::PopMessage(FHMessage& cMsg)
{
	if (m_cListMsg.IsEmpty()) {
		return FALSE;
	}
	else {
		cMsg =  m_cListMsg.RemoveHead();
		return TRUE;
	}
}

void FHSocket::ClearError()
{
	m_iErrorCode = 0;
}

int FHSocket::GetErrorCode()
{
	return m_iErrorCode;
}

void FHSocket::SetErrorCode(int errorCode)
{
	m_iErrorCode = errorCode;
}

int FHSocket::Send(SOCKET s, const char* buf, int len, int flags)
{
	CString strHead;
	strHead.Format("FHSocket::Send size=%d", len);
	//FHLog::DumpFile(strHead, buf, len);
	return send(s, buf, len, flags);
}

int FHSocket::Recv(SOCKET s, char* buf, int len, int flags)
{
	int ret = recv(s, buf, len, flags);
	if (SOCKET_ERROR != ret) {
		CString strHead;
		strHead.Format("FHSocket::Recv size=%d", ret);
		//FHLog::DumpFile(strHead, buf, ret);
	}
	return ret;
}

