#pragma once
#include "afxcmn.h"
#include "FHPublicDefine.h"


// FHFileBrowser 对话框

class FHFileBrowser : public CDialog
{
	DECLARE_DYNAMIC(FHFileBrowser)

public:
	FHFileBrowser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FHFileBrowser();

// 对话框数据
	enum { IDD = IDD_DIALOGFILEBR };

	void DisplayFileList(const CList<FH_FileInfo>& fileList, const bool local = true);
	void SetEditFilePath(const CString& strPath, const bool local = true);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
	

	bool GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList);
	void OnSize(UINT nType, int cx, int cy);
	void ResizeControl(UINT nID, int x, int y); //nID为控件ID，x,y分别为对话框的当前长和宽;
private:
	void EnterDirectory(const CString& strFilename, const bool local = true);

	CString m_cCurrFilePath;
	CImageList m_cLocalImageList;
	CListCtrl m_cLocalFileList;
	CString m_cRemoteFilePath;
	CImageList m_cRemoteImageList;
	CListCtrl m_cRemoteFileList;

	CRect  m_cLastDlgRect;   // 用于保存原对话框大小
public:
	afx_msg void OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult);
};
