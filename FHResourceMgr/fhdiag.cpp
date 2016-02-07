// fhdiag.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "fhdiag.h"


// fhdiag 对话框

IMPLEMENT_DYNAMIC(fhdiag, CDialog)

fhdiag::fhdiag(CWnd* pParent /*=NULL*/)
	: CDialog(fhdiag::IDD, pParent)
{

}

fhdiag::~fhdiag()
{
}

void fhdiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(fhdiag, CDialog)
END_MESSAGE_MAP()


// fhdiag 消息处理程序
