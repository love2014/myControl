#pragma once

#include <string>
using namespace std;

//�����ļ������࣬��ȡ�ļ���������Ϣ
class CFileOperate
{
public:
	CFileOperate(void);
public:
	~CFileOperate(void);
public:
	static string GetConfigKeyStringValue(const char* pSection,const char* pConfigKey);
	static DWORD GetConfigKeyIntValue(const char* pSection,const char* pConfigKey);
	static void WriteConfigKeyValue(const char* pSection,const char* pKeyName,const char* pString);
};
