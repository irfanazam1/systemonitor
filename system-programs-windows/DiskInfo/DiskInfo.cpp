// DiskInfo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
int _tmain(int argc, _TCHAR* argv[])
{
	
	DWORD dwSectPerClust=0;
	DWORD dwBytesPerSect=0;
	DWORD dwFreeClusters=0;
	DWORD dwTotalClusters=0;
	BOOL fResult=FALSE;
	char str[4]={' ',':','/','\0'};
	if(argc==1)
	{
		for(char ch='C';ch<='Z';ch++)
		{
			str[0]=ch;
			fResult = GetDiskFreeSpace (str, 
			&dwSectPerClust, 
			&dwBytesPerSect,
			&dwFreeClusters, 
			&dwTotalClusters);
			if(fResult)
			{
				ULONGLONG l1 = dwTotalClusters;
				ULONGLONG l2 = dwBytesPerSect;
				ULONGLONG l3 = dwSectPerClust;
				ULONGLONG l4 = dwFreeClusters;
				DWORD size = ((l1*l2*l3)/1024)/1024;
				DWORD free = ((l2*l3*l4)/1024)/1024;
				DWORD used = size-free;
				printf("%s,%ld,%ld,%ld\n", str,size,used,free);
			}
			
		}
	}
	else if(argc==2)
	{
		fResult = GetDiskFreeSpace (argv[1], 
		&dwSectPerClust, 
		&dwBytesPerSect,
		&dwFreeClusters, 
		&dwTotalClusters);
		if(fResult)
		{
			ULONGLONG l1 = dwTotalClusters;
			ULONGLONG l2 = dwBytesPerSect;
			ULONGLONG l3 = dwSectPerClust;
			ULONGLONG l4 = dwFreeClusters;
			DWORD size = ((l1*l2*l3)/1024)/1024;
			DWORD free = ((l2*l3*l4)/1024)/1024;
			DWORD used = size-free;
			printf("%s,%ld,%ld,%ld\n", argv[1],size,used,free);
		}
		else
		{
			printf("Drive is invalid");
		}
	}
	
 	return 0;
}

