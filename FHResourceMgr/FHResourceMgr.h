// FHResourceMgr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFHResourceMgrApp:
// �йش����ʵ�֣������ FHResourceMgr.cpp
//

class CFHResourceMgrApp : public CWinApp
{
public:
	CFHResourceMgrApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFHResourceMgrApp theApp;