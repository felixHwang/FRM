#pragma once

#include "FHPublicDefine.h"

class FHFile
{
public:
	FHFile(void);
	~FHFile(void);
	bool GetFileList(const CString& strFilePath, CList<FH_FileInfo>& fileList);
};
