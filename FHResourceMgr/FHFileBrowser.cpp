// FHFileBrowser.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHFileBrowser.h"


// FHFileBrowser 对话框

IMPLEMENT_DYNAMIC(FHFileBrowser, CDialog)

FHFileBrowser::FHFileBrowser(CWnd* pParent /*=NULL*/)
	: CDialog(FHFileBrowser::IDD, pParent)
	, m_cCurrFilePath(_T(""))
	, m_cRemoteFilePath(_T(""))
{

}

FHFileBrowser::~FHFileBrowser()
{
}

void FHFileBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cCurrFilePath);
	DDX_Control(pDX, IDC_LIST3, m_cLocalFileList);
	DDX_Text(pDX, IDC_EDIT2, m_cRemoteFilePath);
	DDX_Control(pDX, IDC_LIST4, m_cRemoteFileList);
}


BEGIN_MESSAGE_MAP(FHFileBrowser, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &FHFileBrowser::OnNMDblclkListItemLeft)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &FHFileBrowser::OnNMDblclkListItemRight)
END_MESSAGE_MAP()


BOOL FHFileBrowser::OnInitDialog()
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


	m_cLocalFileList.InsertColumn(0, _TEXT("文件名"),LVCFMT_CENTER,100,0);
	m_cLocalFileList.InsertColumn(1, _TEXT("创建时间"),LVCFMT_CENTER,100,1);

	m_cRemoteFileList.InsertColumn(0, _TEXT("文件名"),LVCFMT_CENTER,100,0);
	m_cRemoteFileList.InsertColumn(1, _TEXT("创建时间"),LVCFMT_CENTER,100,1);

	char currPath[257];
	GetCurrentDirectory(sizeof(currPath), currPath);
	SetEditFilePath(currPath);
	CList<FH_FileInfo> fileList;
	GetFileList(m_cCurrFilePath, fileList);
	DisplayFileList(fileList);

	return TRUE;
}

void FHFileBrowser::ResizeControl(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd* pWnd = GetDlgItem(nID); 
	if(NULL != pWnd)
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);		//获取控件变化前的大小
		ScreenToClient(&rec);			//将控件大小装换位在对话框中的区域坐标
		rec.left=rec.left*x/m_cLastDlgRect.Width();  //按照比例调整空间的新位置
		rec.top=rec.top*y/m_cLastDlgRect.Height();
		rec.bottom=rec.bottom*y/m_cLastDlgRect.Height();
		rec.right=rec.right*x/m_cLastDlgRect.Width();
		pWnd->MoveWindow(rec);			//伸缩控件
		//pWnd->UpdateWindow();
		//pWnd->UpdateData();
	}
}

void FHFileBrowser::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(SIZE_MINIMIZED != nType)
	{
		ResizeControl(IDC_EDIT1,cx,cy);  //对每一个控件依次做调整
		ResizeControl(IDC_EDIT2,cx,cy);
		ResizeControl(IDC_LIST3,cx,cy); 
		ResizeControl(IDC_LIST4,cx,cy); 
		ResizeControl(IDC_LIST5,cx,cy);
		GetClientRect(&m_cLastDlgRect);   //最后要更新对话框的大小，当做下一次变化的旧坐标；
	}
}

bool FHFileBrowser::GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList)
{
	CFileFind searchFile;
	CString strWildpath = strFilePath + "\\*.*";
	fileList.RemoveAll();

	if (0 != searchFile.FindFile(strWildpath, 0)) {

		int dirPos = 0;
		FH_FileInfo dotInfo;
		dotInfo.fileType = FH_FILETYPE_DIR;
		dotInfo.filename = "..";
		fileList.AddTail(dotInfo);

		BOOL bWorking = true;;
		while (bWorking) {
			bWorking = searchFile.FindNextFile();
			if (searchFile.IsDots()) {
				continue;
			}

			FH_FileInfo cInfo;
			CTime cTime;
			if (searchFile.GetCreationTime(cTime)) {
				cInfo.fileCreateTime = cTime.Format("%Y-%m-%d %H:%M:%S");;
			}
			cInfo.filename = searchFile.GetFileName();
			if (searchFile.IsDirectory()) {
				
				cInfo.fileType = FH_FILETYPE_DIR;
				POSITION position = fileList.FindIndex(dirPos++);
				fileList.InsertAfter(position, cInfo);
			}
			else {
				cInfo.fileType = FH_FILETYPE_NORMAL;
				fileList.AddTail(cInfo);
			}
		}
		searchFile.Close();
		return true;
	}
	return false;
}

void FHFileBrowser::DisplayFileList(const CList<FH_FileInfo>& fileList, const bool local)
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
// FHFileBrowser 消息处理程序

void FHFileBrowser::OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult)
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

void FHFileBrowser::OnNMDblclkListItemRight(NMHDR *pNMHDR, LRESULT *pResult)
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
		EnterDirectory(cFilename, false);
	}
}

void FHFileBrowser::EnterDirectory(const CString& strFilename, const bool local)
{
	if (0 == strFilename.GetLength()) {
		return;
	}

	CString relPath;
	if (local) {
		relPath = m_cCurrFilePath;
	}
	else {
		relPath = m_cRemoteFilePath;
	}

	CList<FH_FileInfo> fileList;

	int index = relPath.GetLength();
	if (0 >= index) {
		return;
	}
	// remove last '\' or '/'
	while ('\\' == relPath[index-1] || '/' == relPath[index-1]) {
		--index;
		if (0 == index) {
			return;		// last '\\\' maybe invalid
		}
	}
	if (0 != index && index != relPath.GetLength()) {
		relPath.Truncate(index);
	}
	
	if (".." == strFilename) {
		int index1 = relPath.ReverseFind('\\');
		int index2 = relPath.ReverseFind('/');
		int newLen = (index1>index2)?index1:index2;
		// root dir already or not
		if (-1 != newLen) {
			relPath.Truncate(newLen);
		}
	}
	else {
		relPath += '\\' + strFilename;
	}

	if (local) {
		if (GetFileList(relPath, fileList)) {
			SetEditFilePath(relPath);
			DisplayFileList(fileList);
		}
	}
	else {
		AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_REQFILEINFO, 0, (LPARAM)&relPath);
	}
	
}

void FHFileBrowser::SetEditFilePath(const CString& strPath, const bool local)
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

