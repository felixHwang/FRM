#pragma once

#include <vector>

// FHMessage ÃüÁîÄ¿±ê

struct FH_MSG_MachineInfo {
	INT lenHostname;
	CString hostname;
	FH_MSG_MachineInfo()
	{
		lenHostname = 0;
		hostname = "";
	}
	FH_MSG_MachineInfo(const CString& name)
	{
		hostname = name;
		lenHostname = hostname.GetLength();
	}
	FH_MSG_MachineInfo(const INT len, const CString& name)
	{
		lenHostname = len;
		hostname = name;
	}

	void Clear()
	{
		lenHostname = 0;
		hostname = "";
	}
};

struct FH_MSG_FileInfo {
	struct FH_MSG_FileInfo_Item {
		int fileType;
		int fileSize;
		int lenFilename;
		CString filename;
		CString fileCreateTime;

		FH_MSG_FileInfo_Item() {
			fileType = -1;
			fileSize = -1;
			lenFilename = 0;
			filename = "";
			fileCreateTime = "";
		}

		FH_MSG_FileInfo_Item& operator=(const FH_MSG_FileInfo_Item& cItem) {
			fileType = cItem.fileType;
			fileSize = cItem.fileSize;
			lenFilename = cItem.lenFilename;
			filename = cItem.filename;
			fileCreateTime = cItem.fileCreateTime;
			return *this;
		}
	};

	int lenFilePath;
	CString filePath;
	std::vector<FH_MSG_FileInfo_Item> fileItemVec;
	

	FH_MSG_FileInfo()
	{
		lenFilePath = 0;
		filePath = "";
	}
	/*FH_MSG_FileInfo(const FH_MSG_FileInfo& cInfo) {}*/
	
	void Clear()
	{
		lenFilePath = 0;
		filePath = "";
		fileItemVec.clear();
	}
	
};

class FHMessage
{
public:
	FHMessage();
	virtual ~FHMessage();

	void Clear();

	FHMessage& operator=(const FHMessage& cMsg);

	virtual void Serialize(CArchive& ar);

	UINT GetCommandID() const { return m_szCommandID; }
	void SetCommandID(UINT val) { m_szCommandID = val; m_bHasConfigInfo = TRUE;}

	const FH_MSG_MachineInfo GetMachineInfo() const { return m_cConfigInfo; }
	void SetMachineInfo(const FH_MSG_MachineInfo& val) { m_cConfigInfo = val; }

	const FH_MSG_FileInfo GetFileInfo() const;
	void SetFileInfo(const FH_MSG_FileInfo& fileInfo);
	void MergeFileInfo(const FHMessage& cMsg);
	

private:
	void SerializeConfigData(CArchive& ar);

	UINT m_szCommandID;
	
	FH_MSG_MachineInfo m_cConfigInfo;
	
	FH_MSG_FileInfo m_cFileInfo;

	BOOL m_bHasConfigInfo;

	BOOL m_bHasFileInfo;
	
};




