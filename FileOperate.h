#pragma once

#include <string>
using namespace std;

//配制文件操作类，读取文件的配制信息
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
