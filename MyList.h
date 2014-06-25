#pragma once
#include "DataList.h"

template <class T>
class CMyList
{
public:
	CMyList(void);
	virtual ~CMyList(void);
public:
	void SetNoticeEvent(HANDLE hNotice);
	void AddDataToList(T& stData);
	void GetDataFromList(vector<T>& listData);
	void GetDataFromList(list<T>& listData);
	void ClearList();
protected:
	CDataList<T> m_listData;
};

template <class T>
CMyList<T>::CMyList()
{
}

template<class T>
CMyList<T>::~CMyList()
{

}

template<class T>
void CMyList<T>::SetNoticeEvent(HANDLE hNotice)
{
	m_listData.SetNoticeEvent(hNotice);
}

template<class T>
void CMyList<T>::AddDataToList(T& stData)
{
	m_listData.PushDataInList(stData);
}

template<class T>
void CMyList<T>::GetDataFromList(vector<T>& listData)
{
	m_listData.GetDataFromList(listData);
}

template<class T>
void CMyList<T>::GetDataFromList(list<T>& listData)
{
	m_listData.GetDataFromList(listData);
}

template<class T>
void CMyList<T>::ClearList()
{
	m_listData.ClearList();
}