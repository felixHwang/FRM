#pragma once

// FHMessage ÃüÁîÄ¿±ê

#define FH_COMMANDID_CONFIG	1

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
	}
	FH_MSG_MachineInfo(const INT len, const CString& name)
	{
		lenHostname = len;
		hostname = name;
	}
};

class FHMessage /*: public CObject*/
{
public:
	/*DECLARE_SERIAL(FHMessage)*/
	FHMessage();
	virtual ~FHMessage();

	FHMessage& operator=(const FHMessage& cMsg);

	virtual void Serialize(CArchive& ar);

	UINT GetCommandID() const { return m_szCommandID; }
	void SetCommandID(UINT val) { m_szCommandID = val; hasConfigInfo = TRUE;}

	const FH_MSG_MachineInfo GetMachineInfo() const { return m_cConfigInfo; }
	void SetMachineInfo(const FH_MSG_MachineInfo& val) { m_cConfigInfo = val; }

private:
	void SerializeConfigData(CArchive& ar);

	UINT m_szCommandID;
	
	FH_MSG_MachineInfo m_cConfigInfo;

	BOOL hasConfigInfo;
	
};




