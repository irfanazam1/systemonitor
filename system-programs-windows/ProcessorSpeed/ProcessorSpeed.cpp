// ProcessorSpeed.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ProcessorSpeed.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <atlbase.h>


// The one and only application object
CWinApp theApp;
using namespace std;
int ReadRegistry()
{
	CRegKey key;
	DWORD speed=0;
	if(key.Open(HKEY_LOCAL_MACHINE,"HARDWARE\\DESCRIPTION\\System\\CentralProcessor",KEY_READ)==ERROR_SUCCESS)
	{
		for(int i=0;i<100;i++)
		{
			char str[4];
			sprintf(str,"%d",i);
			DWORD val=0;
			CRegKey processorKey;
			if(processorKey.Open(key.m_hKey,str,KEY_READ)==ERROR_SUCCESS)
			{
				if(processorKey.QueryDWORDValue("~MHz",val)==ERROR_SUCCESS)
				{
					speed+=val;
				}
				else
				{
					key.Close();
					return speed;
				}
				processorKey.Close();
			}
			else
			{
				key.Close();
				return speed;
			}
		}
	}
	return 0;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		printf("%d",ReadRegistry());

	}

	return nRetCode;
}
