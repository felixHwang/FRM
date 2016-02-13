#pragma once
#include "afxcmn.h"
#include "FHPublicDefine.h"


// FHFileBrowser �Ի���

class FHFileBrowser : public CDialog
{
	DECLARE_DYNAMIC(FHFileBrowser)

public:
	FHFileBrowser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FHFileBrowser();

// �Ի�������
	enum { IDD = IDD_DIALOGFILEBR };

	void DisplayFileList(const CList<FH_FileInfo>& fileList, const bool local = true);
	void SetEditFilePath(const CString& strPath, const bool local = true);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
	

	bool GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList);
	void OnSize(UINT nType, int cx, int cy);
	void ResizeControl(UINT nID, int x, int y); //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�;
private:
	void EnterDirectory(const CString& strFilename, const bool local = true);

	CString m_cCurrFilePath;
	CImageList m_cLocalImageList;
	CListCtrl m_cLocalFileList;
	CString m_cRemoteFilePath;
	CImageList m_cRemoteImageList;
	CListCtrl m_cRemoteFileList;

	CRect  m_cLastDlgRect;   // ���ڱ���ԭ�Ի����С
public:
	afx_msg void OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult);
};
