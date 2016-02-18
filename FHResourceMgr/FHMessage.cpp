// FHMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHMessage.h"
#include "FHPublicDefine.h"

// FHMessage

FHMessage::FHMessage()
:m_szCommandID(-1)
,m_bHasMachineInfo(FALSE)
,m_bHasFileInfo(FALSE)
,m_bHasOpeInfo(FALSE)
{
}

FHMessage::~FHMessage()
{
}

FHMessage& FHMessage::operator=(const FHMessage& cMsg)
{
	this->SetCommandID(cMsg.GetCommandID());
	if (cMsg.m_bHasMachineInfo) {
		this->SetMachineInfo(cMsg.GetMachineInfo());
	}
	if (cMsg.m_bHasFileInfo) {
		this->SetFileInfo(cMsg.GetFileInfo());
	}
	if (cMsg.m_bHasOpeInfo) {
		this->SetOperatorInfo(cMsg.GetOperatorInfo());
	}
	return *this;
}

const FH_MSG_FileInfo FHMessage::GetFileInfo() const
{
	return m_cFileInfo;
}

void FHMessage::SetFileInfo(const FH_MSG_FileInfo& fileInfo)
{
	m_bHasFileInfo = TRUE;
	m_cFileInfo = fileInfo;
}

void FHMessage::Clear()
{
	m_bHasFileInfo = FALSE;
	m_bHasMachineInfo = FALSE;
	m_bHasOpeInfo = FALSE;

	m_cFileInfo.Clear();
	m_cMachineInfo.Clear();
	m_cOpeInfo.Clear();
}

void FHMessage::MergeFileInfo(const FHMessage& cMsg)
{
	if (cMsg.m_bHasFileInfo) {
		if (0 < cMsg.m_cFileInfo.lenFilePath) {
			m_cFileInfo.lenFilePath = cMsg.m_cFileInfo.lenFilePath;
			m_cFileInfo.filePath = cMsg.m_cFileInfo.filePath;
		}
		this->m_bHasFileInfo = TRUE;
		this->m_szCommandID = FH_COMM_FILEINFO;
		for (size_t i=0; i<cMsg.m_cFileInfo.fileItemVec.size(); ++i) {
			m_cFileInfo.fileItemVec.push_back(cMsg.m_cFileInfo.fileItemVec[i]);
		}
	}
	
}

const FH_MSG_OperatorInfo FHMessage::GetOperatorInfo() const
{
	return m_cOpeInfo;
}

void FHMessage::SetOperatorInfo(const FH_MSG_OperatorInfo& opeInfo)
{
	m_bHasOpeInfo = TRUE;
	m_cOpeInfo = opeInfo;

}

const FH_MSG_MachineInfo FHMessage::GetMachineInfo() const
{
	return m_cMachineInfo;
}

void FHMessage::SetMachineInfo(const FH_MSG_MachineInfo& val)
{
	m_bHasMachineInfo = TRUE;
	m_cMachineInfo = val;
}
