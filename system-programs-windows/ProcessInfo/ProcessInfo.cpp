// ProcessInfo.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include <Tlhelp32.h>
#include "psapi.h"
#include <iostream.h>
#include <conio.h>

#pragma comment(lib, "psapi.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	
	PROCESS_MEMORY_COUNTERS memConters;
	HANDLE h=NULL;
	HANDLE hP=NULL;
	PROCESSENTRY32 p;
	h=CreateToolhelp32Snapshot (TH32CS_SNAPALL,NULL);
	p.dwSize=sizeof(PROCESSENTRY32);
	DWORD processSize=0;
	DWORD usageCount=0;
	DWORD processID=0;
	DWORD countThreads=0;
	char exeFileName[255];
	DWORD parentID=0;
	DWORD memUsed=0;
	DWORD pageFileUsage=0;
	DWORD pageFaults=0;
	if(Process32First(h,&p))
 	{		
			processSize=p.dwSize;
			usageCount=p.cntUsage;
			processID=p.th32ProcessID;
			countThreads=p.cntThreads;
			strcpy(exeFileName,p.szExeFile);
			parentID=p.th32ParentProcessID;

            hP= OpenProcess(PROCESS_QUERY_INFORMATION 
                                    /*PROCESS_VM_READ*/,
                                    FALSE, p.th32ProcessID);
            
			if(GetProcessMemoryInfo(hP,&memConters,sizeof(PROCESS_MEMORY_COUNTERS)))
			{
			    memUsed=memConters.WorkingSetSize;
				pageFileUsage=memConters.PagefileUsage;
				pageFaults=memConters.PageFaultCount;
			}

			 CloseHandle(hP);
		   cout<<"ID"<<","<<"Usage"<<","<<"Threads"<<","<<"FileName"<<","<<"Parent"<<","<<"Memory"<<","<<"PageFile"<<","<<"PageFaults"<<endl;
		   cout<<processID<<","<<usageCount<<","<<countThreads<<","<<exeFileName<<","<<parentID<<","<<memUsed<<","<<pageFileUsage<<","<<pageFaults<<endl;
		   
		
		
	}
	while(Process32Next(h,&p))
	{
			
			processSize=p.dwSize;
			usageCount=p.cntUsage;
			processID=p.th32ProcessID;
			countThreads=p.cntThreads;
			strcpy(exeFileName,p.szExeFile);
			parentID=p.th32ParentProcessID;

            hP= OpenProcess(  PROCESS_QUERY_INFORMATION
                                    /*PROCESS_VM_READ*/,
                                    FALSE, p.th32ProcessID);


			if(GetProcessMemoryInfo(hP,&memConters,sizeof(PROCESS_MEMORY_COUNTERS)))
			{
			    memUsed=memConters.WorkingSetSize;
				pageFileUsage=memConters.PagefileUsage;
				pageFaults=memConters.PageFaultCount;
			}

			cout<<processID<<","<<usageCount<<","<<countThreads<<","<<exeFileName<<","<<parentID
				<<","<<( memUsed>=1024?memUsed/1024:memUsed)<<(memUsed>=1024?"K":"B")
				<<","<<(pageFileUsage>=1024?pageFileUsage/1024:pageFileUsage)<<(pageFileUsage>=1024?"K":"B")
				<<","<<pageFaults<<endl;
			}
	return 0;
}

