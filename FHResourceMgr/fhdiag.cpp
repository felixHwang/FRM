// fhdiag.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "fhdiag.h"


// fhdiag �Ի���

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


// fhdiag ��Ϣ�������
