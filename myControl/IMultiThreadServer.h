#pragma once
#include "iserver.h"

class IMultiThreadServer : public IServer
{
public:
	IMultiThreadServer(void);
	virtual ~IMultiThreadServer(void);

public:
	virtual bool StartServer();
	virtual bool StopServer();

protected:
	virtual void OnThreadWork();

protected:
	virtual void DoWork();

protected:
	volatile LONG m_nThreadCount;
	HANDLE m_hWorkEvent;
	HANDLE m_hQuitEvent;
};
