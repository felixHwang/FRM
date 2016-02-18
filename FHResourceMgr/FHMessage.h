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

		FH_MSG_FileInfo_Item()
		{
			fileType = -1;
			fileSize = -1;
			lenFilename = 0;
			filename = "";
			fileCreateTime = "";
		}

		FH_MSG_FileInfo_Item& operator=(const FH_MSG_FileInfo_Item& cItem)
		{
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
	
	void Clear()
	{
		lenFilePath = 0;
		filePath = "";
		fileItemVec.clear();
	}
	
};

#define FH_MSG_OPECODE_LSDIR		1

struct FH_MSG_OperatorInfo
{
	struct FH_MSG_OperatorInfo_Item
	{
		INT lenFilePath;
		CString filePath;
		FH_MSG_OperatorInfo_Item()
		{
			lenFilePath = -1;
			filePath = "";
		}
		FH_MSG_OperatorInfo_Item(const FH_MSG_OperatorInfo_Item& item)
		{
			lenFilePath = item.lenFilePath;
			filePath = item.filePath;
		}
		FH_MSG_OperatorInfo_Item& operator=(const FH_MSG_OperatorInfo_Item& item)
		{
			lenFilePath = item.lenFilePath;
			filePath = item.filePath;
			return *this;
		}
	};

	UINT operatorCode;
	std::vector<FH_MSG_OperatorInfo_Item> opeItemVec;

	FH_MSG_OperatorInfo()
	{
		operatorCode = 0;
	}

	void Clear()
	{
		operatorCode = 0;
		opeItemVec.clear();
	}
};

class FHMessage
{
public:
	FHMessage();
	virtual ~FHMessage();

	void Clear();

	FHMessage& operator=(const FHMessage& cMsg);

	UINT GetCommandID() const { return m_szCommandID; }
	void SetCommandID(UINT val) { m_szCommandID = val; }

	const FH_MSG_MachineInfo GetMachineInfo() const;
	void SetMachineInfo(const FH_MSG_MachineInfo& val);

	const FH_MSG_FileInfo GetFileInfo() const;
	void SetFileInfo(const FH_MSG_FileInfo& fileInfo);
	void MergeFileInfo(const FHMessage& cMsg);

	const FH_MSG_OperatorInfo GetOperatorInfo() const;
	void SetOperatorInfo(const FH_MSG_OperatorInfo& opeInfo);

private:
	UINT m_szCommandID;
	
	FH_MSG_MachineInfo m_cMachineInfo;
	FH_MSG_FileInfo m_cFileInfo;
	FH_MSG_OperatorInfo m_cOpeInfo;

	BOOL m_bHasMachineInfo;
	BOOL m_bHasFileInfo;
	BOOL m_bHasOpeInfo;
};




