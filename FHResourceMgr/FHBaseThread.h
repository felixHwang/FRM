#pragma once

class FHSocket;

class FHBaseThread
{
public:
	FHBaseThread(void);
	virtual ~FHBaseThread(void);

	//virtual void OnCallBack(WPARAM wParam,LPARAM lParam);

	virtual void RegisterSocket(const SOCKET& m_hSocket) = 0;

	virtual void UnRegisterSocket() = 0;

protected:
	BOOL m_bQuit;
	SOCKET m_hSocket;
	FHSocket* m_pcSocket;
};
