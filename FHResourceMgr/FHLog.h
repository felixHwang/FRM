#pragma once

class FHLog
{
public:
	FHLog(void);
	~FHLog(void);

	static BOOL InitFileLog(CString strFilePath);

	static BOOL DeInitFileLog();

	static BOOL DumpFile(CString strHead, const void* pBuffer, const int size);

private:
	static FILE* m_pcFile;
};
