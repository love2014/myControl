#include "StdAfx.h"
#include "IMultiThreadServer.h"
#include <process.h>

IMultiThreadServer::IMultiThreadServer(void)
{
	m_hQuitEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hWorkEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
}

IMultiThreadServer::~IMultiThreadServer(void)
{
	::CloseHandle(m_hQuitEvent);
	m_hQuitEvent = NULL;

	::CloseHandle(m_hWorkEvent);
	m_hWorkEvent = NULL;
}

bool IMultiThreadServer::StartServer()
{
	m_bThreadWorking = true;
	int f_nCreateCount = m_nThreadCount;
	m_nThreadCount = 0;

	for(int i = 0;i<f_nCreateCount;i++)
	{
		_beginthreadex(NULL,0,Thread_Work,this,0,NULL);
	}

	return true;
}

bool IMultiThreadServer::StopServer()
{
	while(m_nThreadCount > 0)
	{
		TRACE0("SetEvent\r\n");
		::SetEvent(m_hQuitEvent);
		::Sleep(50);
	}

	return true;
}

void IMultiThreadServer::OnThreadWork()
{
	::InterlockedIncrement(&m_nThreadCount);

#ifdef SELF_THREAD_INIT_COM
	::CoInitialize(NULL);
#endif

	HANDLE f_pWaits[2];
	f_pWaits[0] = m_hWorkEvent;
	f_pWaits[1] = m_hQuitEvent;

	while(m_bThreadWorking)
	{
		switch(::WaitForMultipleObjects(2,f_pWaits,FALSE,INFINITE))
		{
		case WAIT_OBJECT_0:
			{
				this->DoWork();
			}
			break;
		case WAIT_OBJECT_0 + 1:
			{
				m_bThreadWorking = false;
			}
			break;
		}
	}

#ifdef SELF_THREAD_INIT_COM
	::CoUninitialize();
#endif

	::InterlockedDecrement(&m_nThreadCount);
}

void IMultiThreadServer::DoWork()
{

}