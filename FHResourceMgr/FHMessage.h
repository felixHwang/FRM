#pragma once

// FHMessage ÃüÁîÄ¿±ê

#define FH_COMMANDID_CONFIG	1

struct FH_Command_ConfigInfo {
	INT lenHostname;
	CString hostname;
	FH_Command_ConfigInfo()
	{
		lenHostname = 0;
		hostname = "";
	}
	FH_Command_ConfigInfo(const INT len, const CString& name)
	{
		lenHostname = len;
		hostname = name;
	}
};

class FHMessage : public CObject
{
public:
	DECLARE_SERIAL(FHMessage)
	FHMessage();
	virtual ~FHMessage();

	virtual void Serialize(CArchive& ar);

	UINT GetCommandID() const { return m_szCommandID; }
	void SetCommandID(UINT val) { m_szCommandID = val; hasConfigInfo = TRUE;}

	const FH_Command_ConfigInfo GetConfigInfo() const { return m_cConfigInfo; }
	void SetConfigInfo(const FH_Command_ConfigInfo& val) { m_cConfigInfo = val; }

private:
	void SerializeConfigData(CArchive& ar);

	UINT m_szCommandID;
	
	FH_Command_ConfigInfo m_cConfigInfo;

	BOOL hasConfigInfo;
	
};




