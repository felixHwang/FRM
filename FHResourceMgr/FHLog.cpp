#include "StdAfx.h"
#include "FHLog.h"

#ifdef _DEBUG
#define FH_LOG_OPEN	0
#else
#define FH_LOG_OPEN	0
#endif // _DEBUG

FILE* FHLog::m_pcFile = NULL;


FHLog::FHLog(void)
{
}

FHLog::~FHLog(void)
{
}

BOOL FHLog::InitFileLog(CString strFilePath)
{
#if FH_LOG_OPEN
	m_pcFile = fopen(strFilePath.GetString(), "w");
	if (NULL != m_pcFile) {
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL FHLog::DumpFile(CString strHead, const void* pBuffer, const int size)
{
#if FH_LOG_OPEN
	if (NULL != m_pcFile && NULL != pBuffer) {
		fwrite(strHead.GetString(), strHead.GetLength(), 1, m_pcFile);
		char line[] = "\n";
		fwrite(line, sizeof(line), 1, m_pcFile);
		fwrite(pBuffer, size, 1, m_pcFile);
		fwrite(line, sizeof(line), 1, m_pcFile);
		fflush(m_pcFile);
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL FHLog::DeInitFileLog()
{
#if FH_LOG_OPEN
	if (NULL != m_pcFile) {
		fclose(m_pcFile);
		m_pcFile = NULL;
	}
#endif
	return TRUE;
}
