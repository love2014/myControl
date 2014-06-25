#include "StdAfx.h"
#include "FileOperate.h"


CFileOperate::CFileOperate(void)
{
	
}

CFileOperate::~CFileOperate(void)
{
}

string strGetSystemCofigFile()
{
	TCHAR tPath[MAX_PATH];
	GetModuleFileName(NULL,tPath,MAX_PATH);

	string f_strFile = tPath;

	int f_index = f_strFile.find_last_of('\\');
	f_strFile = f_strFile.substr(0,f_index + 1);
	f_strFile += "BusinessSystemInfo.ini";

	return f_strFile;
}

string CFileOperate::GetConfigKeyStringValue(const char* pSection,const char* pConfigKey)
{

	char tReturnString[MAX_PATH];
	DWORD dwLength;
	
	string strFile = strGetSystemCofigFile();
	dwLength = GetPrivateProfileString(pSection,pConfigKey,"",tReturnString,MAX_PATH,strFile.data());

	if(dwLength == 0)
		return "";
	else
		return tReturnString;
		
}

DWORD CFileOperate::GetConfigKeyIntValue(const char* pSection,const char* pConfigKey)
{
	string strValue = GetConfigKeyStringValue(pSection,pConfigKey);

	if(strlen(strValue.data()) == 0)
		return 0;
	else
		return atoi(strValue.data());
}

void CFileOperate::WriteConfigKeyValue(const char* pSection,const char* pKeyName,const char* pString)
{
	WritePrivateProfileString(pSection,pKeyName,pString,strGetSystemCofigFile().data());
}