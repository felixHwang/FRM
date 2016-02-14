#pragma once

#include <winsock2.h>
#include "FHPublicDefine.h"

class FHAcceptThread;
class FHCommSocket;
class FHFileBrowserDlg;
// FHCommThread

class FHCommThread : public CWinThread
{
	DECLARE_DYNCREATE(FHCommThread)

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	FHCommThread();
	virtual ~FHCommThread();

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();

	void OnCallBack(WPARAM wParam,LPARAM lParam);

	void RegisterSocket(FHCommSocket* pcSocket);
	void UnRegisterSocket();

	void SetIdentifyKey(CString key);
	void StopThread();

private:
	FH_MachineInfo m_cClientInfo;
	FHCommSocket* m_pcCommSocket;
	BOOL m_bQuit;
};


