#pragma once



// fhtestthread

class fhtestthread : public CWinThread
{
	DECLARE_DYNCREATE(fhtestthread)

protected:
	fhtestthread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~fhtestthread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


