// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "Test.h"


// Test 对话框

IMPLEMENT_DYNAMIC(Test, CDialog)

Test::Test(CWnd* pParent /*=NULL*/)
	: CDialog(Test::IDD, pParent)
{

}

Test::~Test()
{
}

void Test::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Test, CDialog)
END_MESSAGE_MAP()


// Test 消息处理程序
