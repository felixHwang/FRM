#pragma once


// fhdiag �Ի���

class fhdiag : public CDialog
{
	DECLARE_DYNAMIC(fhdiag)

public:
	fhdiag(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~fhdiag();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
