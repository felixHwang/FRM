// fhtestthread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "fhtestthread.h"


// fhtestthread

IMPLEMENT_DYNCREATE(fhtestthread, CWinThread)

fhtestthread::fhtestthread()
{
}

fhtestthread::~fhtestthread()
{
}

BOOL fhtestthread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int fhtestthread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(fhtestthread, CWinThread)
END_MESSAGE_MAP()


// fhtestthread ��Ϣ�������
