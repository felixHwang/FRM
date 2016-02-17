// FHFileBrowserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHFileBrowserDlg.h"
#include "FHFile.h"


// FHFileBrowserDlg 对话框

IMPLEMENT_DYNAMIC(FHFileBrowserDlg, CDialog)

FHFileBrowserDlg::FHFileBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHFileBrowserDlg::IDD, pParent)
	, m_cCurrFilePath(_T(""))
	, m_cRemoteFilePath(_T(""))
	, m_cIdentifyKey(_T(""))
{

}

FHFileBrowserDlg::~FHFileBrowserDlg()
{
}

void FHFileBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cCurrFilePath);
	DDX_Control(pDX, IDC_LIST3, m_cLocalFileList);
	DDX_Text(pDX, IDC_EDIT2, m_cRemoteFilePath);
	DDX_Control(pDX, IDC_LIST4, m_cRemoteFileList);
	DDX_Control(pDX, IDC_EDIT_LOG, m_cBrEditLog);
}


BEGIN_MESSAGE_MAP(FHFileBrowserDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &FHFileBrowserDlg::OnNMDblclkListItemLeft)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &FHFileBrowserDlg::OnNMDblclkListItemRight)
END_MESSAGE_MAP()


BOOL FHFileBrowserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
 
	m_cLocalImageList.Create(20,20,ILC_COLOR32,2,3);
	m_cLocalImageList.SetBkColor(RGB(255,255,255));
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FILEDEFAULT);
	m_cLocalImageList.Add(hIcon);
	hIcon =  AfxGetApp()->LoadIcon(IDI_ICON_FOLDERDEFAULT);
	m_cLocalImageList.Add(hIcon);
	m_cLocalFileList.SetImageList(&m_cLocalImageList,LVSIL_SMALL);


	m_cRemoteImageList.Create(20,20,ILC_COLOR32,2,3);
	m_cRemoteImageList.SetBkColor(RGB(255,255,255));
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FILENETWORK);
	m_cRemoteImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FOLDERNETWORK);
	m_cRemoteImageList.Add(hIcon);
	m_cRemoteFileList.SetImageList(&m_cRemoteImageList,LVSIL_SMALL);

	DWORD dwStyle = m_cLocalFileList.GetExtendedStyle();    
	dwStyle = dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES ;  
	m_cLocalFileList.SetExtendedStyle(dwStyle);
	dwStyle = m_cRemoteFileList.GetExtendedStyle();    
	dwStyle = dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES ;  
	m_cRemoteFileList.SetExtendedStyle(dwStyle);


	m_cLocalFileList.InsertColumn(0, _TEXT("文件名"),LVCFMT_CENTER,200,0);
	m_cLocalFileList.InsertColumn(1, _TEXT("创建时间"),LVCFMT_CENTER,100,1);

	m_cRemoteFileList.InsertColumn(0, _TEXT("文件名"),LVCFMT_CENTER,200,0);
	m_cRemoteFileList.InsertColumn(1, _TEXT("创建时间"),LVCFMT_CENTER,100,1);

	char currPath[257];
	GetCurrentDirectory(sizeof(currPath), currPath);
	SetEditFilePath(currPath);
	CList<FH_FileInfo> fileList;
	FHFile cFile;
	cFile.GetFileList(m_cCurrFilePath, fileList);
	DisplayFileList(fileList);

	return TRUE;
}

BOOL FHFileBrowserDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN) 
	{ 
		switch(pMsg->wParam)  
		{  
		case VK_RETURN:   // Enter 
			return TRUE;
		case VK_ESCAPE:   // Esc  
			return TRUE;
		} 
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void FHFileBrowserDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (SIZE_MINIMIZED != nType) {
		ResizeControl(IDC_EDIT1, cx, cy);		 //对每一个控件依次做调整
		ResizeControl(IDC_EDIT2, cx, cy);
		ResizeControl(IDC_LIST3, cx, cy); 
		ResizeControl(IDC_LIST4, cx, cy); 
		ResizeControl(IDC_EDIT_LOG, cx, cy);

		if (NULL != GetDlgItem(IDC_LIST3) && NULL != GetDlgItem(IDC_LIST4)) {
			double ratio = 1.0*cx/m_cLastDlgRect.Width();
			m_cLocalFileList.SetColumnWidth(0, m_cLocalFileList.GetColumnWidth(0)*ratio);
			m_cLocalFileList.SetColumnWidth(1, m_cLocalFileList.GetColumnWidth(1)*ratio);
			m_cRemoteFileList.SetColumnWidth(0, m_cRemoteFileList.GetColumnWidth(0)*ratio);
			m_cRemoteFileList.SetColumnWidth(1, m_cRemoteFileList.GetColumnWidth(1)*ratio);
		}


		GetClientRect(&m_cLastDlgRect);		//最后要更新对话框的大小，当做下一次变化的旧坐标
	}
}

void FHFileBrowserDlg::DisplayFileList(const CList<FH_FileInfo>& fileList, const BOOL local)
{
	CListCtrl* pcListCtrl = NULL;
	if (local) {
		pcListCtrl = &m_cLocalFileList;
	}
	else {
		pcListCtrl = &m_cRemoteFileList;
	}

	if (NULL != pcListCtrl) {
		pcListCtrl->DeleteAllItems();

		for (int i=0; i<fileList.GetSize(); ++i) {
			POSITION positon = fileList.FindIndex(i);
			FH_FileInfo cInfo = fileList.GetAt(positon);
			LVITEM lvItem={0};
			lvItem.mask = LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;   // 文字、图片、状态  
			lvItem.iItem = i; 
			if (FH_FILETYPE_NORMAL == cInfo.fileType) {
				lvItem.iImage = 0;
			}
			else {
				lvItem.iImage = 1;
			}
			lvItem.iSubItem = 0;
			int row = pcListCtrl->InsertItem(&lvItem);
			pcListCtrl->SetItemText(row, 0,cInfo.filename);
			CString strTime = cInfo.fileCreateTime;
			pcListCtrl->SetItemText(row, 1, strTime);
		}
	}
}
// FHFileBrowserDlg 消息处理程序

void FHFileBrowserDlg::OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int x = m_cLocalFileList.GetSelectionMark();
	if (m_cLocalFileList.GetSelectedCount() <= 0)  
	{  
		return;
	}

	POSITION position =  m_cLocalFileList.GetFirstSelectedItemPosition();
	if (NULL != position) {
		int index = m_cLocalFileList.GetNextSelectedItem(position);
		CString cFilename = m_cLocalFileList.GetItemText(index, 0);
		EnterDirectory(cFilename);
	}
}

void FHFileBrowserDlg::OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int x = m_cRemoteFileList.GetSelectionMark();
	if (m_cRemoteFileList.GetSelectedCount() <= 0)  
	{  
		return;
	}

	POSITION position =  m_cRemoteFileList.GetFirstSelectedItemPosition();
	if (NULL != position) {
		int index = m_cRemoteFileList.GetNextSelectedItem(position);
		CString cFilename = m_cRemoteFileList.GetItemText(index, 0);
		EnterDirectory(cFilename, FALSE);
	}
}

void FHFileBrowserDlg::SetIdentifyKey(const CString key)
{
	m_cIdentifyKey = key;
}

void FHFileBrowserDlg::SetEditFilePath(const CString& strPath, const BOOL local)
{
	if (local) {
		m_cCurrFilePath = strPath;
		this->SetDlgItemText(IDC_EDIT1, m_cCurrFilePath);
	}
	else {
		m_cRemoteFilePath = strPath;
		this->SetDlgItemText(IDC_EDIT2, m_cRemoteFilePath);
	}
}

void FHFileBrowserDlg::SetBrowerDescription(const CString& strText)
{
	this->SetDlgItemText(IDC_STATIC, strText);
}

void FHFileBrowserDlg::OutputFileBrowserLog(const CString strText)
{
	m_cBrEditLog.SetSel( -1, -1);      //设定光标选中的区域
	m_cBrEditLog.ReplaceSel(strText);
	m_cBrEditLog.SetSel( -1, -1);
	m_cBrEditLog.ReplaceSel("\n");
	m_cBrEditLog.LineScroll(m_cBrEditLog.GetLineCount());
}

void FHFileBrowserDlg::EnterDirectory(const CString& strFilename, const BOOL local)
{
	if (0 == strFilename.GetLength()) {
		return;
	}

	CString absPath;
	if (local) {
		absPath = m_cCurrFilePath;
	}
	else {
		absPath = m_cRemoteFilePath;
	}

	FHFile cFile;
	if (!cFile.JoinPath(strFilename, absPath)) {
		return;
	}

	if (local) {
		CList<FH_FileInfo> fileList;
		FHFile cFile;
		if (cFile.GetFileList(absPath, fileList)) {
			SetEditFilePath(absPath);
			DisplayFileList(fileList);
			OutputFileBrowserLog("显示本地目录：" + absPath);
		}
	}
	else {
		UINT keyNum;
		sscanf_s(m_cIdentifyKey.GetString(), "%u", &keyNum);
		AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_REQFILEINFO, keyNum, (LPARAM)&absPath);
	}
}

void FHFileBrowserDlg::ResizeControl(UINT nID, int x, int y)
{
	CWnd* pWnd = GetDlgItem(nID); 
	if(NULL != pWnd)
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);						//获取控件变化前的大小
		ScreenToClient(&rec);							//将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x/m_cLastDlgRect.Width();   //按照比例调整空间的新位置
		rec.top = rec.top*y/m_cLastDlgRect.Height();
		rec.bottom = rec.bottom*y/m_cLastDlgRect.Height();
		rec.right = rec.right*x/m_cLastDlgRect.Width();
		pWnd->MoveWindow(rec);							//伸缩控件
	}
}