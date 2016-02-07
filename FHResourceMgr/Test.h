#pragma once


// Test 对话框

class Test : public CDialog
{
	DECLARE_DYNAMIC(Test)

public:
	Test(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Test();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
