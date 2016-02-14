// FHFileBrowser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHFileBrowser.h"
#include "FHFile.h"


// FHFileBrowser �Ի���

IMPLEMENT_DYNAMIC(FHFileBrowser, CDialog)

FHFileBrowser::FHFileBrowser(CWnd* pParent /*=NULL*/)
	: CDialog(FHFileBrowser::IDD, pParent)
	, m_cCurrFilePath(_T(""))
	, m_cRemoteFilePath(_T(""))
	, m_cIdentifyKey(_T(""))
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


	m_cLocalFileList.InsertColumn(0, _TEXT("�ļ���"),LVCFMT_CENTER,100,0);
	m_cLocalFileList.InsertColumn(1, _TEXT("����ʱ��"),LVCFMT_CENTER,100,1);

	m_cRemoteFileList.InsertColumn(0, _TEXT("�ļ���"),LVCFMT_CENTER,100,0);
	m_cRemoteFileList.InsertColumn(1, _TEXT("����ʱ��"),LVCFMT_CENTER,100,1);

	char currPath[257];
	GetCurrentDirectory(sizeof(currPath), currPath);
	SetEditFilePath(currPath);
	CList<FH_FileInfo> fileList;
	GetFileList(m_cCurrFilePath, fileList);
	DisplayFileList(fileList);

	return TRUE;
}

BOOL FHFileBrowser::PreTranslateMessage(MSG* pMsg)
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

void FHFileBrowser::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(SIZE_MINIMIZED != nType)
	{
		ResizeControl(IDC_EDIT1,cx,cy);		 //��ÿһ���ؼ�����������
		ResizeControl(IDC_EDIT2,cx,cy);
		ResizeControl(IDC_LIST3,cx,cy); 
		ResizeControl(IDC_LIST4,cx,cy); 
		ResizeControl(IDC_LIST5,cx,cy);
		GetClientRect(&m_cLastDlgRect);		//���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ�����
	}
}

BOOL FHFileBrowser::GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList)
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

		BOOL bWorking = TRUE;;
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
		return TRUE;
	}
	return FALSE;
}

void FHFileBrowser::DisplayFileList(const CList<FH_FileInfo>& fileList, const BOOL local)
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
			lvItem.mask = LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;   // ���֡�ͼƬ��״̬  
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
// FHFileBrowser ��Ϣ�������

void FHFileBrowser::OnNMDblclkListItemLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

void FHFileBrowser::SetIdentifyKey(const CString key)
{
	m_cIdentifyKey = key;
}

void FHFileBrowser::SetEditFilePath(const CString& strPath, const BOOL local)
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

void FHFileBrowser::SetBrowerDescription(const CString& strText)
{
	this->SetDlgItemText(IDC_STATIC, strText);
}

void FHFileBrowser::EnterDirectory(const CString& strFilename, const BOOL local)
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
		if (GetFileList(absPath, fileList)) {
			SetEditFilePath(absPath);
			DisplayFileList(fileList);
		}
	}
	else {
		UINT keyNum;
		sscanf_s(m_cIdentifyKey.GetString(), "%u", &keyNum);
		AfxGetApp()->m_pMainWnd->SendMessage(FH_MSCMD_REQFILEINFO, keyNum, (LPARAM)&absPath);
	}
}

void FHFileBrowser::ResizeControl(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd* pWnd = GetDlgItem(nID); 
	if(NULL != pWnd)
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);						//��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);							//���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x/m_cLastDlgRect.Width();   //���ձ��������ռ����λ��
		rec.top = rec.top*y/m_cLastDlgRect.Height();
		rec.bottom = rec.bottom*y/m_cLastDlgRect.Height();
		rec.right = rec.right*x/m_cLastDlgRect.Width();
		pWnd->MoveWindow(rec);							//�����ؼ�
	}
}