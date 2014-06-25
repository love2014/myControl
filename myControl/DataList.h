#pragma once

#include <list>
#include <vector>
using namespace std;

template <class T>
class CDataList
{
public:
	CDataList();
	virtual ~CDataList(void);

public:
	void SetNoticeEvent(HANDLE hNotice);
	void PushDataInList(T stData);
	void GetDataFromList(vector<T>& listData);
	void GetDataFromList(list<T>& listData);
	void ClearList();
private:
	list<T> m_listVector; //数据存取队列
	HANDLE m_hNoticeEvent; //通知事件
	CRITICAL_SECTION m_csList;
};

template <class T>
CDataList<T>::CDataList()
{
	this->m_hNoticeEvent = NULL;
	::InitializeCriticalSection(&m_csList);
}

template <class T>
CDataList<T>::~CDataList(void)
{
	m_listVector.clear();
	::DeleteCriticalSection(&m_csList);
}

template <class T>
void CDataList<T>::SetNoticeEvent(HANDLE hNotice)
{
	this->m_hNoticeEvent = hNotice;
}

template <class T>
void CDataList<T>::PushDataInList(T stData)
{
	::EnterCriticalSection(&m_csList);

	m_listVector.push_back(stData);
	if(m_listVector.size() >= 10000)
		m_listVector.pop_front();

	//注册了通知事件时，通知数据接收方
	if(m_hNoticeEvent)
		::SetEvent(m_hNoticeEvent);

	::LeaveCriticalSection(&m_csList);
}

template <class T>
void CDataList<T>::GetDataFromList(vector<T>& listData)
{
	::EnterCriticalSection(&m_csList);
	if(m_listVector.size() > 0)
	{
		listData.insert(listData.begin(),m_listVector.begin(),m_listVector.end());
		m_listVector.clear();
	}
	::LeaveCriticalSection(&m_csList);
}

template <class T>
void CDataList<T>::GetDataFromList(list<T>& listData)
{
	::EnterCriticalSection(&m_csList);
	if(m_listVector.size() > 0)
	{
		listData.insert(listData.begin(),m_listVector.begin(),m_listVector.end());
		m_listVector.clear();
	}
	::LeaveCriticalSection(&m_csList);
}

template <class T>
void CDataList<T>::ClearList()
{
	::EnterCriticalSection(&m_csList);
	m_listVector.clear();
	::LeaveCriticalSection(&m_csList);
}
