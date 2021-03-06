#include "StdAfx.h"
#include "FHFile.h"
#include "FHMessage.h"

FHFile::FHFile(void)
{
}

FHFile::~FHFile(void)
{
}


BOOL FHFile::GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList)
{
	if ("我的电脑" == strFilePath) {
		char szBuf[60];  
		memset(szBuf, 0, sizeof(szBuf));  

		GetLogicalDriveStrings(sizeof(szBuf), szBuf);  

		for(char* pDriver= szBuf;  *pDriver;  pDriver+=strlen(pDriver)+1) {
			ULARGE_INTEGER FreeAv,TotalBytes,FreeBytes;
			// 过滤空驱动盘符
			if (GetDiskFreeSpaceEx(pDriver, &FreeAv, &TotalBytes, &FreeBytes)) {
				if (0 < TotalBytes.QuadPart) {
					FH_FileInfo item;
					item.fileType = FH_FILETYPE_DIR;
					item.filename = pDriver;
					item.fileSize = -1;
					item.fileCreateTime = "";
					fileList.AddTail(item);
				}
			}
		}
		return TRUE;
	}
	else {
		CFileFind searchFile;
		CString strWildpath = strFilePath + "\\*.*";
		fileList.RemoveAll();

		if (0 != searchFile.FindFile(strWildpath, 0)) {

			FH_FileInfo dots;
			dots.filename = "..";
			dots.fileType = FH_FILETYPE_DIR;
			fileList.AddHead(dots);

			int dirPos = 0;

			BOOL bWorking = TRUE;;
			while (bWorking) {
				bWorking = searchFile.FindNextFile();
				if (searchFile.IsDots()) {
					continue;
				}

				FH_FileInfo cInfo;
				CTime cTime;
				cInfo.fileSize = 0;
				if (searchFile.GetCreationTime(cTime)) {
					cInfo.fileCreateTime = cTime.Format("%Y-%m-%d %H:%M:%S");
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
	}
	return FALSE;
}

BOOL FHFile::GetFileList(const CString& strFilePath, FH_MSG_FileInfo& cFileInfo)
{
	CList<FH_FileInfo> fileList;
	if (GetFileList(strFilePath, fileList)) {
		cFileInfo.lenFilePath = strFilePath.GetLength();
		cFileInfo.filePath = strFilePath;

		for (int i=0; i<fileList.GetSize(); ++i) {
			POSITION positon = fileList.FindIndex(i);
			FH_FileInfo cInfo = fileList.GetAt(positon);
			FH_MSG_FileInfo::FH_MSG_FileInfo_Item item;
			item.fileSize = cInfo.fileSize;
			item.fileType = cInfo.fileType;
			item.lenFilename = cInfo.filename.GetLength();
			item.filename = cInfo.filename;
			item.fileCreateTime = cInfo.fileCreateTime;
			cFileInfo.fileItemVec.push_back(item);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL FHFile::JoinPath(const CString& strFilename, CString& absolutePath)
{
	int index = absolutePath.GetLength();
	if (0 >= index) {
		return FALSE;
	}
	// remove last '\' or '/'
	while ('\\' == absolutePath[index-1] || '/' == absolutePath[index-1]) {
		--index;
		if (0 == index) {
			return FALSE;		// last '\\\' maybe invalid
		}
	}
	if (0 != index && index != absolutePath.GetLength()) {
		absolutePath.Truncate(index);
	}

	if (".." == strFilename) {
		int index1 = absolutePath.ReverseFind('\\');
		int index2 = absolutePath.ReverseFind('/');
		int newLen = (index1>index2)?index1:index2;
		// root dir already or not
		if (-1 != newLen) {
			absolutePath.Truncate(newLen);
		}
		else {
			absolutePath = "我的电脑";
		}
	}
	else {
		if ("我的电脑" == absolutePath) {
			absolutePath = strFilename;
		}
		else {
			absolutePath += '\\' + strFilename;
		}
	}
	return TRUE;
};