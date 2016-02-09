#pragma once

#define FH_DEFAULT_CONNECT_PORT 8989

#define FH_MSCMD_RECV 0X0001 
#define FH_MSCMD_STARTACCEPT 0X0002
#define FH_MSCMD_STARTCONNECT 0X0003
#define FH_MSCMD_STARTCOMM 0X0004
#define FH_MSCMD_UPDATECONNECT		(WM_USER+1)
#define FH_MSCMD_SERVERDISCONNECT	(WM_USER+2)

#define FH_COMM_MACHINEINFO	0X09000001

#define FH_ERR_NOERROR	(0)

#define FH_FILETYPE_DIR (FILE_ATTRIBUTE_DIRECTORY)
#define FH_FILETYPE_NORMAL (FILE_ATTRIBUTE_NORMAL)

struct FH_MachineInfo {
	CString hostname;
	CString address;
};

struct FH_FileInfo {
	int filetype;
	CString filename;
	CTime fileCreateTime;
};