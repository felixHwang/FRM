// FHServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FHResourceMgr.h"
#include "FHServerDlg.h"
#include "FHFileBrowserDlg.h"
#include "FHSocket.h"

// FHServerDlg 对话框

IMPLEMENT_DYNAMIC(FHServerDlg, CDialog)

FHServerDlg::FHServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FHServerDlg::IDD, pParent)
{
	EnableAutomation();
}

FHServerDlg::~FHServerDlg()
{
}

void FHServerDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialog::OnFinalRelease();
}

void FHServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_cClientCtrlList);
}

BOOL FHServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cClientCtrlList.SetExtendedStyle(m_cClientCtrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_cClientCtrlList.InsertColumn(0, _TEXT("主机名"),LVCFMT_CENTER,150,0);
	m_cClientCtrlList.InsertColumn(1, _TEXT("IP地址"),LVCFMT_CENTER,110,1);
	m_cClientCtrlList.InsertColumn(2, _TEXT("识别码"),LVCFMT_LEFT,50,2);

	
	//m_cClientCtrlList.InsertItem(0, _T("Java"));   
 //   m_cClientCtrlList.SetItemText(0, 1, _T("192.168.0.1"));   
 //   m_cClientCtrlList.SetItemText(0, 2, _T("Connect"));

	//m_cClientCtrlList.InsertItem(1, _T("Pyt"));   
	//m_cClientCtrlList.SetItemText(1, 1, _T("192.168.0.2"));   
	//m_cClientCtrlList.SetItemText(1, 2, _T("Connect"));

	//m_cClientCtrlList.InsertItem(2, _T("Cs"));   
	//m_cClientCtrlList.SetItemText(2, 1, _T("192.168.0.3"));   
	//m_cClientCtrlList.SetItemText(2, 2, _T("Disconnect"));


	//LVFINDINFO info;
	//POINT  pos1;
	//info.flags = LVFI_PARTIAL|LVFI_STRING;
	//info.psz = "Cs";
	//int nIndex2 = m_cClientCtrlList.FindItem(&info);
	//m_cClientCtrlList.GetItemPosition(nIndex2, &pos1);


	//int nIndex1;
	//info.flags = LVFI_PARTIAL|LVFI_STRING;
	//info.psz = "Pyt";

	//// Delete all of the items that begin with the string.
	//if (-1 != (nIndex1 = m_cClientCtrlList.FindItem(&info)))
	//{
	//	m_cClientCtrlList.DeleteItem(nIndex1);
	//}

	//info.flags = LVFI_PARTIAL|LVFI_STRING;
	//info.psz = "Cs";
	//int nIndex3 = m_cClientCtrlList.FindItem(&info);
	//POINT  pos2;
	//m_cClientCtrlList.get
	//m_cClientCtrlList.GetItemPosition(nIndex3, &pos2);

	m_cServerManager.StartListen("127.0.0.1");

	return TRUE;
}

BEGIN_MESSAGE_MAP(FHServerDlg, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &FHServerDlg::OnNMRClickListOfClient)
	ON_COMMAND(ID_1_32774, &FHServerDlg::OnSelectOpen)
	ON_MESSAGE(FH_MSCMD_UPDATECONNECT, RefleshConnectList)
	ON_MESSAGE(FH_MSCMD_CLIENTDISCONNECT, RecvClientDisconnect)
	ON_MESSAGE(FH_MSCMD_UPFILEINFO, RefleshFileInfo)
	ON_MESSAGE(FH_MSCMD_REQFILEINFO, RequestFileInfo)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FHServerDlg, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IFHServerDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {E813554D-6368-4772-8D48-F7A77662C721}
static const IID IID_IFHServerDlg =
{ 0xE813554D, 0x6368, 0x4772, { 0x8D, 0x48, 0xF7, 0xA7, 0x76, 0x62, 0xC7, 0x21 } };

BEGIN_INTERFACE_MAP(FHServerDlg, CDialog)
	INTERFACE_PART(FHServerDlg, IID_IFHServerDlg, Dispatch)
END_INTERFACE_MAP()

// FHServerDlg 消息处理程序

BOOL FHServerDlg::PreTranslateMessage(MSG* pMsg)
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

void FHServerDlg::OnNMRClickListOfClient(NMHDR *pNMHDR, LRESULT *pResult)
{

	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int x = m_cClientCtrlList.GetSelectionMark();
	if (0 >= m_cClientCtrlList.GetSelectedCount())  
	{  
		return;
	}

	POINT pt;
	GetCursorPos(&pt);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pop = menu.GetSubMenu(0);
	if (NULL != pop) {
		pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
}

void FHServerDlg::OnSelectOpen()
{
	// TODO: 在此添加命令处理程序代码

	//m_cClientCtrlList.GetFirstSelectedItemPosition();
	POSITION pos = m_cClientCtrlList.GetFirstSelectedItemPosition();  
	if (NULL != pos) {  
		while (pos) {  
			int item = m_cClientCtrlList.GetNextSelectedItem(pos);  
			CString key = m_cClientCtrlList.GetItemText(item, 2);
			CString hostName = m_cClientCtrlList.GetItemText(item, 0);
			UINT keyNum;
			sscanf_s(key.GetString(), "%u", &keyNum);
			if (m_cFileBrList.end() != m_cFileBrList.find(key)) {
				// m_cFileBrList[key]->ShowWindow(SW_SHOW);
				CString strFilePath = "";
				RequestFileInfo(keyNum, (LPARAM)&strFilePath);
			}
			else {
				FHFileBrowserDlg* fileBR = new FHFileBrowserDlg();
				if (NULL != fileBR) {
					m_cFileBrList[key] = fileBR;
					fileBR->Create(IDD_DIALOGFILEBR, this);
					fileBR->SetIdentifyKey(key);
					fileBR->SetBrowerDescription(hostName + ":" + key);
					// fileBR->ShowWindow(SW_SHOW);
					CString strFilePath = "";
					RequestFileInfo(keyNum, (LPARAM)&strFilePath);
				}
			}
		}
	}  
}

LRESULT FHServerDlg::RefleshConnectList(WPARAM wParam,LPARAM lParam)
{
	FH_MachineInfo cInfo = *((FH_MachineInfo*)lParam);

	int count = m_cClientCtrlList.GetItemCount();
	m_cClientCtrlList.InsertItem(count, cInfo.hostname);
	m_cClientCtrlList.SetItemText(count, 1, cInfo.address);
	m_cClientCtrlList.SetItemText(count, 2, cInfo.key);

	return 0;
}

LRESULT FHServerDlg::RecvClientDisconnect(WPARAM wParam,LPARAM lParam)
{
	FH_MachineInfo cInfo = *((FH_MachineInfo*)lParam);

	int count = m_cClientCtrlList.GetItemCount();  
	for(int i=0; i<count; i++)  
	{  
		if(cInfo.key == m_cClientCtrlList.GetItemText(i,2))  
		{  
			m_cClientCtrlList.DeleteItem(i);
			const std::map<CString, FHFileBrowserDlg*>::iterator it = m_cFileBrList.find(cInfo.key);
			if (m_cFileBrList.end() != it) {
				FHFileBrowserDlg* fileBR = it->second;
				m_cFileBrList.erase(it);
				fileBR->DestroyWindow();
				delete fileBR;
			}
			break;
		}  
	}  

	return 0;
}

LRESULT FHServerDlg::RefleshFileInfo(WPARAM wParam,LPARAM lParam)
{
	UINT keyValue = wParam;
	CString key;
	key.Format("%u", keyValue);
	std::map<CString, FHFileBrowserDlg*>::iterator it = m_cFileBrList.find(key);
	if (it == m_cFileBrList.end()) {
		return -1;
	}

	FHFileBrowserDlg* pcFileBrowser = it->second;
	if (NULL == pcFileBrowser) {
		return -1;
	}

	FHMessage cMsg =  *((FHMessage*)lParam);
	CList<FH_FileInfo> infoList;
	FH_FileInfo dots;
	dots.filename = "..";
	dots.fileType = FH_FILETYPE_DIR;
	infoList.AddTail(dots);
	FH_MSG_FileInfo fileInfo = cMsg.GetFileInfo();
	for (size_t i=0; i<fileInfo.fileItemVec.size(); ++i) {
		FH_FileInfo item;
		item.fileType = fileInfo.fileItemVec[i].fileType;
		item.fileSize = fileInfo.fileItemVec[i].fileSize;
		item.filename = fileInfo.fileItemVec[i].filename;
		item.fileCreateTime = fileInfo.fileItemVec[i].fileCreateTime;
		infoList.AddTail(item);
	}
	pcFileBrowser->ShowWindow(TRUE);
	pcFileBrowser->DisplayFileList(infoList, FALSE);
	pcFileBrowser->SetEditFilePath(fileInfo.filePath, FALSE);
	
	return 0;
}

LRESULT FHServerDlg::RequestFileInfo(WPARAM wParam,LPARAM lParam)
{
	UINT keyValue = wParam;
	CString key;
	key.Format("%u", keyValue);
	FHSocket* pcSocket = m_cServerManager.GetChannelSocket(key);
	if (NULL != pcSocket) {
		FHMessage cMsg;
		cMsg.SetCommandID(FH_COMM_OPEINFO);
		FH_MSG_OperatorInfo opeInfo;
		opeInfo.operatorCode = FH_MSG_OPECODE_LSDIR;
		FH_MSG_OperatorInfo::FH_MSG_OperatorInfo_Item item;
		item.filePath = *(CString*)lParam;
		item.lenFilePath = item.filePath.GetLength();
		opeInfo.opeItemVec.push_back(item);
		cMsg.SetOperatorInfo(opeInfo);
		pcSocket->SendMessage(cMsg);
	}
	return 0;
}