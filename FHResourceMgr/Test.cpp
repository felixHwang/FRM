// Test.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "Test.h"


// Test �Ի���

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


// Test ��Ϣ�������
