// fhtestthread.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int fhtestthread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(fhtestthread, CWinThread)
END_MESSAGE_MAP()


// fhtestthread 消息处理程序
