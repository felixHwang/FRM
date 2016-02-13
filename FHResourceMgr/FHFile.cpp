#include "StdAfx.h"
#include "FHFile.h"

FHFile::FHFile(void)
{
}

FHFile::~FHFile(void)
{
}


bool FHFile::GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList)
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

		bool bWorking = true;;
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
		return true;
	}
	return false;
}