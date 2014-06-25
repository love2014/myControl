#pragma once

class IServer
{
public:
	IServer(void);
	virtual ~IServer(void);

public:
	virtual bool StartServer();
	virtual bool StopServer();

protected:
	virtual void PreThreadStartWork();
	virtual void PreThreadExit();
	virtual void OnThreadWork();

protected:
	HANDLE m_hThread;
	bool m_bThreadWorking;
	static unsigned WINAPI Thread_Work(LPVOID lp);
};
