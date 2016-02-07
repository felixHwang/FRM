#pragma once



// fhtestthread

class fhtestthread : public CWinThread
{
	DECLARE_DYNCREATE(fhtestthread)

protected:
	fhtestthread();           // 动态创建所使用的受保护的构造函数
	virtual ~fhtestthread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


