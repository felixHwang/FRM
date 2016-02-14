#pragma once

#include "FHPublicDefine.h"

struct FH_MSG_FileInfo;

class FHFile
{
public:
	FHFile(void);
	~FHFile(void);
	BOOL GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList);
	BOOL GetFileList(const CString& strFilePath, FH_MSG_FileInfo& cFileInfo);
	BOOL JoinPath(const CString& strFilename, CString& absolutePath);
};
