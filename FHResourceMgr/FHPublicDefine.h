#pragma once

#define FH_DEFAULT_CONNECT_PORT 8989

#define FH_MSCMD_RECV 0X0001 
#define FH_MSCMD_STARTACCEPT 0X0002
#define FH_MSCMD_STARTCONNECT 0X0003
#define FH_MSCMD_STARTCOMM 0X0004
#define FH_MSCMD_UPDATECONNECT		(WM_USER+1)
#define FH_MSCMD_SERVERDISCONNECT	(WM_USER+2)
#define FH_MSCMD_CLIENTDISCONNECT	(WM_USER+3)
#define FH_MSCMD_UPFILEINFO			(WM_USER+4)
#define FH_MSCMD_REQFILEINFO		(WM_USER+5)

#define FH_COMM_MACHINEINFO	0X00000001
#define FH_COMM_FILEINFO	0X00000002
#define FH_COMM_OPEINFO		0X00000003

#define FH_ERR_NOERROR	(0)

#define FH_FILETYPE_DIR (FILE_ATTRIBUTE_DIRECTORY)
#define FH_FILETYPE_NORMAL (FILE_ATTRIBUTE_NORMAL)

struct FH_MachineInfo {
	FH_MachineInfo()
	{
		key = "";
		hostname = "";
		address = "";
	}

	CString key;
	CString hostname;
	CString address;
};

struct FH_FileInfo {
	FH_FileInfo()
	{
		fileType = -1;
		fileSize = -1;
		filename = "";
		fileCreateTime = "";
	}

	int fileType;
	int fileSize;
	CString filename;
	CString fileCreateTime;
};