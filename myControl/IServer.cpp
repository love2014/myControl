#include "StdAfx.h"
#include "IServer.h"
#include <process.h>

IServer::IServer(void)
{
	m_bThreadWorking = false;
	m_hThread = NULL;
}

IServer::~IServer(void)
{
}

bool IServer::StartServer()
{
	m_bThreadWorking = true;
	m_hThread = (HANDLE)_beginthreadex(NULL,0,Thread_Work,this,0,NULL);
	if(m_hThread)
		return true;
	else return false;
}

bool IServer::StopServer()
{
	m_bThreadWorking = false;

	if(::WaitForSingleObject(m_hThread,1 * 1000) == WAIT_OBJECT_0)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		return true;
	}
	else
	{
		::TerminateThread(m_hThread,0);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
		return false;
	}
}

void IServer::PreThreadStartWork()
{

}

void IServer::PreThreadExit()
{

}

void IServer::OnThreadWork()
{

}

unsigned WINAPI IServer::Thread_Work(LPVOID lp)
{
	IServer* pServer = (IServer*)lp;

	pServer->PreThreadStartWork();
	while(pServer->m_bThreadWorking)
	{
		pServer->OnThreadWork();
	}
	pServer->PreThreadExit();

	return 0;
}
