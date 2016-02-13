// FHMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHMessage.h"

// FHMessage

FHMessage::FHMessage()
:m_bHasConfigInfo(FALSE)
,m_bHasFileInfo(FALSE)
,m_bHasOpeInfo(FALSE)
{
}

FHMessage::~FHMessage()
{
}

void FHMessage::Serialize(CArchive& ar)
{
	/*
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		// 序列化数据
		ar<<m_szCommandID;
	}
	else {
		// 反序列化数据
		ar>>m_szCommandID;

	}
	if (FH_COMMANDID_CONFIG == m_szCommandID) {
		SerializeConfigData(ar);
	}
	*/
	

}

void FHMessage::SerializeConfigData(CArchive& ar)
{
	/*
	if (ar.IsStoring()) {
		// 序列化数据
		ar<<m_cConfigInfo.addr<<m_cConfigInfo.hostname;
	}
	else {
		// 反序列化数据
		ar>>m_cConfigInfo.addr>>m_cConfigInfo.hostname;
	}
	*/
}

//IMPLEMENT_SERIAL(FHMessage,CObject,1)

FHMessage& FHMessage::operator=(const FHMessage& cMsg)
{
	this->SetCommandID(cMsg.GetCommandID());
	if (cMsg.m_bHasConfigInfo) {
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
	m_bHasConfigInfo = FALSE;
	m_bHasOpeInfo = FALSE;

	m_cFileInfo.Clear();
	m_cConfigInfo.Clear();
	m_cOpeInfo.Clear();
}

void FHMessage::MergeFileInfo(const FHMessage& cMsg)
{
	if (cMsg.m_bHasFileInfo) {
		this->m_bHasFileInfo = TRUE;
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
