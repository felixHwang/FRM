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
	CFileFind searchFile;
	CString strWildpath = strFilePath + "\\*.*";
	fileList.RemoveAll();

	if (0 != searchFile.FindFile(strWildpath, 0)) {

		int dirPos = 0;
		/*FH_FileInfo dotInfo;
		dotInfo.fileType = FH_FILETYPE_DIR;
		dotInfo.filename = "..";
		fileList.AddTail(dotInfo);*/

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

		FH_FileInfo dots;
		dots.filename = "..";
		dots.fileType = FH_FILETYPE_DIR;
		fileList.AddHead(dots);

		return TRUE;
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
	}
	else {
		absolutePath += '\\' + strFilename;
	}
	return TRUE;
};