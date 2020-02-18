// CpuUsage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "GetCpuUsage.h"
using namespace std;

int main(int argc, char* argv[])
{
	while(1)
	{
		try
		{
			Sleep(2000);
			if(argc !=2)
			{
				printf("Proper Use: File Name to write the output\n");
				exit(0);
			}
			char * fileName = argv[1];
			ofstream out;
			out.open(fileName,ios::out);
			if(!out.good())
			{
				printf("Unable to write file\n");
			}
			int Cpu = GetCpuUsage();
			char *mem = GetMemoryInformation();
			char cpu[4];
			sprintf(cpu,",%d",Cpu);
			if(cpu=="")
			{
				Cpu=0;
				sprintf(cpu,",%d",Cpu);
			}
			char * result = strcat(mem,cpu);
			out.write(result,strlen(result));
			out.flush();
			out.close();
			result=NULL;
			mem=NULL;
		}
		catch(...)
		{
			throw;
		}
	}
	return 0;
}
