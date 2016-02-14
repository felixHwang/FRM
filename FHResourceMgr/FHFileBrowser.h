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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();

public:
	afx_msg void OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult);

	void SetIdentifyKey(const CString key);
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList);
	void OnSize(UINT nType, int cx, int cy);

	void DisplayFileList(const CList<FH_FileInfo>& fileList, const BOOL local = TRUE);
	void SetEditFilePath(const CString& strPath, const BOOL local = TRUE);

	void SetBrowerDescription(const CString& strText);

private:
	void ResizeControl(UINT nID, int x, int y);
	void EnterDirectory(const CString& strFilename, const BOOL local = TRUE);
	
	CImageList m_cLocalImageList;
	CListCtrl m_cLocalFileList;
	CImageList m_cRemoteImageList;
	CListCtrl m_cRemoteFileList;
	CRect  m_cLastDlgRect;   // 用于保存原对话框大小
	CString m_cRemoteFilePath;
	CString m_cCurrFilePath;
	CString m_cIdentifyKey;

};
