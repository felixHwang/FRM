// FHMessage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHMessage.h"

// FHMessage

FHMessage::FHMessage()
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
		// ���л�����
		ar<<m_szCommandID;
	}
	else {
		// �����л�����
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
		// ���л�����
		ar<<m_cConfigInfo.addr<<m_cConfigInfo.hostname;
	}
	else {
		// �����л�����
		ar>>m_cConfigInfo.addr>>m_cConfigInfo.hostname;
	}
	*/
}

IMPLEMENT_SERIAL(FHMessage,CObject,1)
// FHMessage ��Ա����
