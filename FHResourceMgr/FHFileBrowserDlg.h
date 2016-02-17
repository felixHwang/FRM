#pragma once
#include "afxcmn.h"
#include "FHPublicDefine.h"
#include "afxwin.h"


// FHFileBrowserDlg �Ի���

class FHFileBrowserDlg : public CDialog
{
	DECLARE_DYNAMIC(FHFileBrowserDlg)

public:
	FHFileBrowserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FHFileBrowserDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGFILEBR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();

public:
	afx_msg void OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult);

	void SetIdentifyKey(const CString key);
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnSize(UINT nType, int cx, int cy);

	void DisplayFileList(const CList<FH_FileInfo>& fileList, const BOOL local = TRUE);
	void SetEditFilePath(const CString& strPath, const BOOL local = TRUE);

	void SetBrowerDescription(const CString& strText);
	void OutputFileBrowserLog(const CString strText);

private:
	void ResizeControl(UINT nID, int x, int y);
	void EnterDirectory(const CString& strFilename, const BOOL local = TRUE);

	CImageList m_cLocalImageList;
	CListCtrl m_cLocalFileList;
	CImageList m_cRemoteImageList;
	CListCtrl m_cRemoteFileList;
	CListCtrl m_cLogList;
	CRect  m_cLastDlgRect;   // ���ڱ���ԭ�Ի����С
	CString m_cRemoteFilePath;
	CString m_cCurrFilePath;
	CString m_cIdentifyKey;
};
