// autonk.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "stdio.h"
#include "dbt.h"
#include "setupapi.h"
#include "tchar.h"
#include <process.h>
#include <string.h>
#include <stdlib.h>
//#include "vld.h"
#ifdef __cplusplus
extern "C"
{
#endif
	
#include "hidsdi.h"
#include "hidusage.h"	
#ifdef __cplusplus
}
#endif

#define guidNum	3
#define MAX_LEN 256
//#define MAX_DLLNAME	 32			//动态库名称的最大长度
#define MAX_DLLNAME	 64
char	impTypePath[MAX_LEN/2] = {0};
typedef void * handle_t;

BOOL	IsRun;

static  GUID g_guidInterfaceUSB
= { // {a5dcbf10-6530-11d2-901f-00c04fb951ed}
	0xa5dcbf10,
		0x6530,
		0x11d2,
	{ 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed } };

static  GUID g_guidInterfaceCRAD
= { // {{0821b887-6502-4103-8e32-d1e75d346b3b}}
	0x0821b887,
		0x6502,
		0x4103,
	{ 0x8e, 0x32, 0xd1, 0xe7, 0x5d, 0x34, 0x6b, 0x3b } };

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}



bool EnumDevicecheck(char *pID_Dev, char *vID_dev)
{
	
	GUID guid[guidNum];

	HidD_GetHidGuid(&guid[0]);//枚举hid设备，具体需要根据监控的设备类型自己调整

	guid[1] = g_guidInterfaceUSB;
	guid[2] = g_guidInterfaceCRAD;

	for(int i=0;i<guidNum;i++)
	{
	
		HDEVINFO hDevInfo = SetupDiGetClassDevs(&guid[i], NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
		if (hDevInfo == INVALID_HANDLE_VALUE)
		{
			continue;	
		}
		DWORD dwIndex = 0;
		SP_DEVICE_INTERFACE_DATA devInterfaceData = {0};
		devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		BOOL bRet = FALSE;
		
		PSP_DEVICE_INTERFACE_DETAIL_DATA pspdidd;
		SP_DEVICE_INTERFACE_DATA         spdid;
		SP_DEVINFO_DATA                  spdd;
		DWORD                            dwSize;
		
		spdid.cbSize = sizeof(spdid);
		
		//获取当前所有devicepath
		
		while(true)
		{
			bRet = SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &guid[i], dwIndex, &spdid);
			if (!bRet) 
			{
				break;
			}			
			dwSize = 0;
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &spdid, NULL, 0, &dwSize, NULL);
			if (dwSize)
			{
				pspdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
				if ( pspdidd == NULL ) 
				{																																				
					continue; 
				}
				pspdidd->cbSize = sizeof(*pspdidd); 
				ZeroMemory((PVOID)&spdd, sizeof(spdd));
				spdd.cbSize = sizeof(spdd);
				
				long res = SetupDiGetDeviceInterfaceDetail(hDevInfo, &spdid, pspdidd, dwSize, &dwSize, &spdd);
				if ( res )
				{
					//pspdidd->DevicePath为设备路径，可以使用一些方法判断是否为自己所关心的设备，如path中的特殊子串或者使用相应的函数获取pid vid
					//从而决定要不要加入自己的path列表中
					char * sTmp;
					char  pID[32]="";
					char  vID[32]="";
					char * finddata="hid#";
					char * finddata2="usb#";
					char * p=NULL;
					char * start=NULL;
					int existKeyVID,existKeyPID;
				

					sTmp = pspdidd->DevicePath;	
					
					p = strstr(sTmp,finddata);
					if(p==NULL)
					{
						p = strstr(sTmp,finddata2);
					}

					start = p + 4;
					strncat(vID, start, 8);
					start = start + 9;
					strncat(pID, start, 8);

					
					existKeyVID = strcmp(vID, vID_dev);
					existKeyPID = strcmp(pID, pID_Dev);

					if((existKeyVID == 0)&&(existKeyPID == 0))
					{
						HeapFree(GetProcessHeap(), 0, pspdidd);
						SetupDiDestroyDeviceInfoList(hDevInfo);
						return true;
					}
					
				}
				HeapFree(GetProcessHeap(), 0, pspdidd);

			}
			dwIndex++;
		}
		SetupDiDestroyDeviceInfoList(hDevInfo);
	}
	return false;
}

int	GetWindowsDrive(char *cWinDrive)
{
	UINT	size;

	char	buffer[MAX_LEN] = {0};

	size = GetWindowsDirectory(buffer,MAX_LEN);
	if(size==0)
		return GetLastError();

	char *index = strstr(buffer,"\\");

	memcpy(cWinDrive,buffer,index-buffer);

	return 0;
}

void GetPath(char *path, int type)
{

	char driverName[16] = {0};
	char wellhopepath[MAX_LEN] = {0};

	GetWindowsDrive(driverName);
	sprintf(wellhopepath,"%s/Program Files/cryptosoft/Config",driverName);
	CreateDirectory(wellhopepath,NULL);
	if(type==1)	//配置文件路径
		sprintf(path,"%s/Program Files/cryptosoft/Config/regwin.xml",driverName);
	if(type==2)	//配置文件路径
		sprintf(path,"%s\\Program Files (x86)\\cryptosoft\\Config\\regwin.xml",driverName);
	if(type==3)	//配置文件路径
		sprintf(path,"%s/Program Files/cryptosoft/Config/phwin.xml",driverName);
	if(type==4)	//配置文件路径
		sprintf(path,"%s\\Program Files (x86)\\cryptosoft\\Config\\phwin.xml",driverName);
}
/*
void GetPath(char *path, int type,int flag)
{
	char driverName[16] = {0};
	char wellhopepath[MAX_LEN] = {0};

	GetWindowsDrive(driverName);
	sprintf(wellhopepath,"%s/Program Files/cryptosoft/Config",driverName);
	CreateDirectory(wellhopepath,NULL);
	if((type==1)&&(flag == 1))	//配置文件路径
		sprintf(path,"%s/Program Files/cryptosoft/Config/regwingm.xml",driverName);
	if((type==2)&&(flag == 2))	//配置文件路径
		sprintf(path,"%s\\Program Files (x86)\\cryptosoft\\Config\\regwingm.xml",driverName);
	if((type==3)&&(flag == 3))	//配置文件路径
		sprintf(path,"%s/Program Files/cryptosoft/Config/regwincsp.xml",driverName);
	if((type==4)&&(flag == 4))	//配置文件路径
		sprintf(path,"%s\\Program Files (x86)\\cryptosoft\\Config\\regwincsp.xml",driverName);
}
*/
BOOL IsWow64() 
{ 
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); 
    LPFN_ISWOW64PROCESS fnIsWow64Process; 
    BOOL bIsWow64 = FALSE; 
    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle("kernel32"),"IsWow64Process"); 
    if (NULL != fnIsWow64Process) 
    { 
        fnIsWow64Process(GetCurrentProcess(),&bIsWow64);
    } 
    return bIsWow64; 
} 

static int readdata(char * filename, BYTE *pData, DWORD * length)
{
	FILE *stream = NULL;
	int count, total=0;
	char buffer[100] = {0};
	int	ret = 0;
	
	if(pData)
	{
		if( ( stream = fopen( filename, "rb" ) ) == NULL )
		{
			printf("%s open failed!\n",filename);
			return -1;
		}
		
		count = fread( pData, 1, *length, stream );
		*length = count;
		fclose( stream );
	}
	else
	{
		if( ( stream = fopen( filename, "rb" ) ) == NULL )
			return -1;
		
		while( !feof( stream ) )
		{
			/* Attempt to read in 10 bytes: */
			count = fread( buffer, sizeof( char ), 100, stream );
			if( ferror( stream ) )      
			{
				ret = -1;
				perror( "Read error" );
				break;
			}
			
			/* Total up actual bytes read */
			total += count;
		}
		*length = total;
		fclose( stream );
	}
	
	return ret;
}

static int GetParamFromConfEx(char *ParamName,char *ParamValue)
{

	DWORD	dwFileLength = 0;
	BYTE	*pFileData = NULL;
	int		ret = 0;
	char	errorMessage[MAX_LEN] = {0};

	if(IsWow64())
		GetPath(impTypePath,4);
	else
	    GetPath(impTypePath,3);
	while(1)
	{
        OutputDebugString(impTypePath);
		ret = readdata(impTypePath,pFileData,&dwFileLength);
		if(ret!=0)
		{
			sprintf(errorMessage,"ReadFile %s Error!\n",impTypePath);
			OutputDebugString(errorMessage);
			break;
		}
		pFileData = new BYTE[dwFileLength+1];
		if(pFileData==NULL)
		{
			ret = -1;
			break;
		}

		memset(pFileData,0,dwFileLength+1);
		ret = readdata(impTypePath,pFileData,&dwFileLength);
		if(ret!=0)
		{
			sprintf(errorMessage,"ReadFile %s Error!\n",impTypePath);
			OutputDebugString(errorMessage);
			break;
		}

		char str1[50];
		memset(str1,0,50);
		sprintf(str1,"<%s>",ParamName);

		char str2[50];
		memset(str2,0,50);
		sprintf(str2,"</%s>",ParamName);
		char* index1 = strstr((char *)pFileData,(char *)str1);
		if(index1 == NULL)
		{
			ret = -1;
			break;
		}

		char* index2 = strstr((char *)pFileData,(char *)str2);
		if(index2 == NULL)
		{
			ret = -1;
			break;
		}

		if(index2<index1)
		{
			ret = -1;
			break;
		}
		else if(index2-index1-strlen(str1)>MAX_DLLNAME)
		{
			ret = -1;
			break;
		}
		else
			memcpy(ParamValue,index1+strlen(str1),index2-index1-strlen(str1));
		
		break;
	}

	delete [] pFileData;
	pFileData = NULL;

	return ret;
}
static int GetParamFromConf(char *ParamName,char *ParamValue)
{

	DWORD	dwFileLength = 0;
	BYTE	*pFileData = NULL;
	int		ret = 0;
	char	errorMessage[MAX_LEN] = {0};

	if(IsWow64())
		GetPath(impTypePath,2);
	else
	    GetPath(impTypePath,1);
	while(1)
	{
        OutputDebugString(impTypePath);
		ret = readdata(impTypePath,pFileData,&dwFileLength);
		if(ret!=0)
		{
			sprintf(errorMessage,"ReadFile %s Error!\n",impTypePath);
			OutputDebugString(errorMessage);
			break;
		}
		pFileData = new BYTE[dwFileLength+1];
		if(pFileData==NULL)
		{
			ret = -1;
			break;
		}

		memset(pFileData,0,dwFileLength+1);
		ret = readdata(impTypePath,pFileData,&dwFileLength);
		if(ret!=0)
		{
			sprintf(errorMessage,"ReadFile %s Error!\n",impTypePath);
			OutputDebugString(errorMessage);
			break;
		}

		char str1[50];
		memset(str1,0,50);
		sprintf(str1,"<%s>",ParamName);

		char str2[50];
		memset(str2,0,50);
		sprintf(str2,"</%s>",ParamName);
		char* index1 = strstr((char *)pFileData,(char *)str1);
		if(index1 == NULL)
		{
			ret = -1;
			break;
		}

		char* index2 = strstr((char *)pFileData,(char *)str2);
		if(index2 == NULL)
		{
			ret = -1;
			break;
		}

		if(index2<index1)
		{
			ret = -1;
			break;
		}
		else if(index2-index1-strlen(str1)>MAX_DLLNAME)
		{
			ret = -1;
			break;
		}
		else
			memcpy(ParamValue,index1+strlen(str1),index2-index1-strlen(str1));
		
		break;
	}

	delete [] pFileData;
	pFileData = NULL;

	return ret;
}


DWORD __stdcall  WHICH_KEY(char *dllname, char *pkiapidllname)
{

	IsRun = true;
	int ret = 0;
	int EkeyID = 0;
	int pos=0;
	int pos2=0;

	int		dDevNum;
	char	i_pid[MAX_LEN/2] = {0};
	char	i_vid[MAX_LEN/2] = {0};
	char	DevName[MAX_LEN/2] = {0};

	char	DevNum[] = "DevNum";
	char	Buf[3];
	memset(Buf, 0, 3);
	ret = GetParamFromConf(DevNum, Buf);
	if(ret != 0)
		return ret;
	dDevNum = atoi(Buf);

	char DevNameLabel[MAX_LEN/2] = {0};
	char PIDLabel[MAX_LEN/2] = {0};
	char VIDLabel[MAX_LEN/2] = {0};
	char KeyTypeLabel[MAX_LEN/2] = {0};
	char PkiapiTypeLabel[MAX_LEN/2] = {0};
	char cdllname[MAX_DLLNAME] = {0};
	char pkiapiname[MAX_DLLNAME] = {0};
	char DevID[MAX_LEN/2] = {0};
	char KeyTypeID[MAX_LEN/2] = {0};
	char pkiapiDllNameList[8][MAX_LEN/2];
	char keyDllNameList[8][MAX_LEN/2];
	int pkiCount = 0;
	int dllCount = 0;
	bool pkiFlag = false;
	for(int i=1; i<=dDevNum; i++)
	{
		memset(DevNameLabel, 0, MAX_LEN/2);
		memset(DevName, 0, MAX_LEN/2);
		sprintf(DevNameLabel, "DevName", i);
		ret = GetParamFromConf(DevNameLabel, DevName);

		memset(PIDLabel, 0, MAX_LEN/2);
		memset(i_pid, 0, MAX_LEN/2);
		sprintf(PIDLabel, "PID%03d", i);
		ret = GetParamFromConf(PIDLabel, i_pid);

		memset(VIDLabel, 0, MAX_LEN/2);
		memset(i_vid, 0, MAX_LEN/2);
		sprintf(VIDLabel, "VID%03d", i);
		ret = GetParamFromConf(VIDLabel, i_vid);

	
		memset(KeyTypeLabel, 0, MAX_LEN/2);
		memset(cdllname, 0, MAX_DLLNAME);
		sprintf(KeyTypeLabel, "KeyProviderType%03d", i);
		ret = GetParamFromConf(KeyTypeLabel, cdllname);

		memset(PkiapiTypeLabel, 0, MAX_LEN/2);
		memset(pkiapiname, 0, MAX_DLLNAME);
		sprintf(PkiapiTypeLabel, "PkiapiType%03d", i);
		ret = GetParamFromConf(PkiapiTypeLabel, pkiapiname);
		

		memset(DevID, 0, MAX_LEN/2);
		memset(KeyTypeID, 0, MAX_LEN/2);
		sprintf(DevID, "DevID%03d", i);
		ret = GetParamFromConf(DevID, KeyTypeID);
		OutputDebugString(KeyTypeID);

		if(EnumDevicecheck(i_pid, i_vid) == true)
		{
			if(dllname != NULL)
			{
				pkiFlag = false;
				for(int j=0;j<pkiCount;j++)
				{
					if(strcmp(pkiapiDllNameList[j],cdllname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(pkiapiDllNameList[pkiCount], cdllname, strlen(cdllname)+1); 
					pkiCount++;
					memcpy(dllname+pos, cdllname, strlen(cdllname)+1); 
					pos+=strlen(cdllname)+1;
				}
				pkiFlag = false;
				for(int j=0;j<dllCount;j++)
				{
					if(strcmp(keyDllNameList[j],pkiapiname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(keyDllNameList[dllCount], pkiapiname, strlen(pkiapiname)+1); 
					dllCount++;
					memcpy(pkiapidllname+pos2, pkiapiname, strlen(pkiapiname)+1); 
					pos2+=strlen(pkiapiname)+1;	
				}
				

				EkeyID = atoi(KeyTypeID);
			}
		}	
	}


	/*if(isHT_KEY()) 
	{ 
		if(dllname != NULL)
		{
			memcpy(dllname+pos, "HTGM.dll", strlen("HTGM.dll")+1 ); 
			memcpy(pkiapidllname+pos2, "pkiapi_ecc.dll", strlen("pkiapi_ecc.dll")+1 ); 
		}
		if(EkeyID == 0)
			EkeyID = 10;
		else
			EkeyID = 11;
	}

	if(EkeyID == 0)
	{
		memcpy(dllname, "UNknownware.dll", strlen("UNknownware.dll")+1 ); 
		return -1;
	}*/

	return EkeyID;
}
//识别无驱无软的卡或者key
DWORD __stdcall  WHICH_KEYEx(char *dllname, char *pkiapidllname)
{

	IsRun = true;
	int ret = 0;
	int EkeyID = 0;
	int pos=0;
	int pos2=0;

	int		dDevNum;
	char	i_pid[MAX_LEN/2] = {0};
	char	i_vid[MAX_LEN/2] = {0};
	char	DevName[MAX_LEN/2] = {0};

	char	DevNum[] = "DevNum";
	char	Buf[3];
	memset(Buf, 0, 3);
	ret = GetParamFromConfEx(DevNum, Buf);
	if(ret != 0)
		return ret;
	dDevNum = atoi(Buf);

	char DevNameLabel[MAX_LEN/2] = {0};
	char KeyTypeLabel[MAX_LEN/2] = {0};
	char PkiapiTypeLabel[MAX_LEN/2] = {0};
	char cdllname[MAX_DLLNAME] = {0};
	char pkiapiname[MAX_DLLNAME] = {0};
	char DevID[MAX_LEN/2] = {0};
	char KeyTypeID[MAX_LEN/2] = {0};

	for(int i=1; i<=dDevNum; i++)
	{
		memset(DevNameLabel, 0, MAX_LEN/2);
		memset(DevName, 0, MAX_LEN/2);
		sprintf(DevNameLabel, "DevName%03d", i);
		ret = GetParamFromConfEx(DevNameLabel, DevName);

		

	
		memset(KeyTypeLabel, 0, MAX_LEN/2);
		memset(cdllname, 0, MAX_DLLNAME);
		sprintf(KeyTypeLabel, "KeyProviderType%03d", i);
		ret = GetParamFromConfEx(KeyTypeLabel, cdllname);

		memset(PkiapiTypeLabel, 0, MAX_LEN/2);
		memset(pkiapiname, 0, MAX_DLLNAME);
		sprintf(PkiapiTypeLabel, "PkiapiType%03d", i);
		ret = GetParamFromConfEx(PkiapiTypeLabel, pkiapiname);
		

		memset(DevID, 0, MAX_LEN/2);
		memset(KeyTypeID, 0, MAX_LEN/2);
		sprintf(DevID, "DevID%03d", i);
		ret = GetParamFromConfEx(DevID, KeyTypeID);
		OutputDebugString(KeyTypeID);

		
		if(dllname != NULL)
		{
			memcpy(dllname+pos, cdllname, strlen(cdllname)+1); 
			pos+=strlen(cdllname)+1;

			if(pkiapidllname != NULL)
			{
				memcpy(pkiapidllname+pos2, pkiapiname, strlen(pkiapiname)+1); 
				pos2+=strlen(pkiapiname)+1;				
			}

			EkeyID = atoi(KeyTypeID);
		}
			
	}


	

	return EkeyID;
}
/*
DWORD __stdcall  WHICH_KEYESymmType(char *symmtype)
{
    IsRun = true;
	int ret = 0;
	int EkeyID = 0;
	int pos=0;

	int		dDevNum;
	char	i_pid[MAX_LEN/2] = {0};
	char	i_vid[MAX_LEN/2] = {0};
	char	DevName[MAX_LEN/2] = {0};

	char	DevNum[] = "DevNum";
	char	Buf[3];
	memset(Buf, 0, 3);
	ret = GetParamFromConf(DevNum, Buf);
	if(ret != 0)
		return ret;
	dDevNum = atoi(Buf);

	char DevNameLabel[MAX_LEN/2] = {0};
	char PIDLabel[MAX_LEN/2] = {0};
	char VIDLabel[MAX_LEN/2] = {0};
	char DevID[MAX_LEN/2] = {0};
	char KeyTypeID[MAX_LEN/2] = {0};
	
	char SymmTypeLable[MAX_LEN/2] = {0};
	char SymmType[MAX_LEN/2] = {0};
	char symmNameList[50][MAX_LEN/2];
	int  symmCount = 0;

	bool pkiFlag = false;
	for(int i=1; i<=dDevNum; i++)
	{
		memset(DevNameLabel, 0, MAX_LEN/2);
		memset(DevName, 0, MAX_LEN/2);
		sprintf(DevNameLabel, "DevName%03d", i);
		ret = GetParamFromConf(DevNameLabel, DevName);

		memset(PIDLabel, 0, MAX_LEN/2);
		memset(i_pid, 0, MAX_LEN/2);
		sprintf(PIDLabel, "PID%03d", i);
		ret = GetParamFromConf(PIDLabel, i_pid);

		memset(VIDLabel, 0, MAX_LEN/2);
		memset(i_vid, 0, MAX_LEN/2);
		sprintf(VIDLabel, "VID%03d", i);
		ret = GetParamFromConf(VIDLabel, i_vid);

		memset(DevID, 0, MAX_LEN/2);
		memset(KeyTypeID, 0, MAX_LEN/2);
		sprintf(DevID, "DevID%03d", i);
		ret = GetParamFromConf(DevID, KeyTypeID);
		OutputDebugString(KeyTypeID);

		memset(SymmTypeLable, 0, MAX_LEN/2);
		memset(SymmType, 0, MAX_LEN/2);
		sprintf(SymmTypeLable, "SymmType%03d", i);
		ret = GetParamFromConf(SymmTypeLable, SymmType);

		if(EnumDevicecheck(i_pid, i_vid) == true)
		{
			if(symmtype != NULL)
			{
				pkiFlag = false;
				for(int j=0;j<symmCount;j++)
				{
					if(strcmp(symmNameList[j],SymmType)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(symmNameList[symmCount], SymmType, strlen(SymmType)+1); 
					symmCount++;
					memcpy(symmtype+pos, SymmType, strlen(SymmType)+1); 
					pos+=strlen(SymmType)+1;
				}

				EkeyID = atoi(KeyTypeID);
			}
		}	
	}

	return EkeyID;

}
*/


//识别有驱的key
DWORD __stdcall  WHICH_KEYExx(char *dllname, char *pkiapidllname, char *symmtype)
{

	IsRun = true;
	int ret = 0;
	int EkeyID = 0;
	int pos=0;
	int pos2=0;

	int		dDevNum;
	char	i_pid[MAX_LEN/2] = {0};
	char	i_vid[MAX_LEN/2] = {0};
	char	DevName[MAX_LEN/2] = {0};

	char	DevNum[] = "DevNum";
	char	Buf[3];
	memset(Buf, 0, 3);
	ret = GetParamFromConf(DevNum, Buf);
	if(ret != 0)
		return ret;
	dDevNum = atoi(Buf);

	char DevNameLabel[MAX_LEN/2] = {0};
	char PIDLabel[MAX_LEN/2] = {0};
	char VIDLabel[MAX_LEN/2] = {0};
	char KeyTypeLabel[MAX_LEN/2] = {0};
	char PkiapiTypeLabel[MAX_LEN/2] = {0};
	char cdllname[MAX_DLLNAME] = {0};
	char pkiapiname[MAX_DLLNAME] = {0};
	char DevID[MAX_LEN/2] = {0};
	char KeyTypeID[MAX_LEN/2] = {0};
	char pkiapiDllNameList[8][MAX_LEN/2];
	char keyDllNameList[8][MAX_LEN/2];
	int pkiCount = 0;
	int dllCount = 0;

	char SymmTypeLable[MAX_LEN/2] = {0};
	char SymmType[MAX_LEN/2] = {0};
	char symmNameList[50][MAX_LEN/2];
	int  symmCount = 0;
	int pos3 = 0;

	bool pkiFlag = false;
	for(int i=1; i<=dDevNum; i++)
	{
		memset(DevNameLabel, 0, MAX_LEN/2);
		memset(DevName, 0, MAX_LEN/2);
		sprintf(DevNameLabel, "DevName%03d", i);
		ret = GetParamFromConf(DevNameLabel, DevName);

		memset(PIDLabel, 0, MAX_LEN/2);
		memset(i_pid, 0, MAX_LEN/2);
		sprintf(PIDLabel, "PID%03d", i);
		ret = GetParamFromConf(PIDLabel, i_pid);

		memset(VIDLabel, 0, MAX_LEN/2);
		memset(i_vid, 0, MAX_LEN/2);
		sprintf(VIDLabel, "VID%03d", i);
		ret = GetParamFromConf(VIDLabel, i_vid);

	
		memset(KeyTypeLabel, 0, MAX_LEN/2);
		memset(cdllname, 0, MAX_DLLNAME);
		sprintf(KeyTypeLabel, "KeyProviderType%03d", i);
		ret = GetParamFromConf(KeyTypeLabel, cdllname);

		memset(PkiapiTypeLabel, 0, MAX_LEN/2);
		memset(pkiapiname, 0, MAX_DLLNAME);
		sprintf(PkiapiTypeLabel, "PkiapiType%03d", i);
		ret = GetParamFromConf(PkiapiTypeLabel, pkiapiname);
		

		memset(DevID, 0, MAX_LEN/2);
		memset(KeyTypeID, 0, MAX_LEN/2);
		sprintf(DevID, "DevID%03d", i);
		ret = GetParamFromConf(DevID, KeyTypeID);
		OutputDebugString(KeyTypeID);

		memset(SymmTypeLable, 0, MAX_LEN/2);
		memset(SymmType, 0, MAX_LEN/2);
		sprintf(SymmTypeLable, "SymmType%03d", i);
		ret = GetParamFromConf(SymmTypeLable, SymmType);

		if(EnumDevicecheck(i_pid, i_vid) == true)
		{
			if(dllname != NULL)
			{
				pkiFlag = false;
				for(int j=0;j<pkiCount;j++)
				{
					if(strcmp(pkiapiDllNameList[j],cdllname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(pkiapiDllNameList[pkiCount], cdllname, strlen(cdllname)+1); 
					pkiCount++;
					memcpy(dllname+pos, cdllname, strlen(cdllname)+1); 
					pos+=strlen(cdllname)+1;
				}
				pkiFlag = false;
				for(int j=0;j<dllCount;j++)
				{
					if(strcmp(keyDllNameList[j],pkiapiname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(keyDllNameList[dllCount], pkiapiname, strlen(pkiapiname)+1); 
					dllCount++;
					memcpy(pkiapidllname+pos2, pkiapiname, strlen(pkiapiname)+1); 
					pos2+=strlen(pkiapiname)+1;	
				}

				
				memcpy(symmNameList[symmCount], SymmType, strlen(SymmType)+1); 
				symmCount++;
				memcpy(symmtype+pos3, SymmType, strlen(SymmType)+1); 
				pos3+=strlen(SymmType)+1;
				

				EkeyID = atoi(KeyTypeID);
			}
		}	
	}

	return EkeyID;
}

DWORD __stdcall  WHICH_KEY_Symm_Hash(char *dllname, char *pkiapidllname, char *symmtype, char *hashtype)
{

	IsRun = true;
	int ret = 0;
	int EkeyID = 0;
	int pos=0;
	int pos2=0;

	int		dDevNum;
	char	i_pid[MAX_LEN/2] = {0};
	char	i_vid[MAX_LEN/2] = {0};
	char	DevName[MAX_LEN/2] = {0};

	char	DevNum[] = "DevNum";
	char	Buf[3];
	memset(Buf, 0, 3);
	ret = GetParamFromConf(DevNum, Buf);
	if(ret != 0)
		return ret;
	dDevNum = atoi(Buf);

	char DevNameLabel[MAX_LEN/2] = {0};
	char PIDLabel[MAX_LEN/2] = {0};
	char VIDLabel[MAX_LEN/2] = {0};
	char KeyTypeLabel[MAX_LEN/2] = {0};
	char PkiapiTypeLabel[MAX_LEN/2] = {0};
	char cdllname[MAX_DLLNAME] = {0};
	char pkiapiname[MAX_DLLNAME] = {0};
	char DevID[MAX_LEN/2] = {0};
	char KeyTypeID[MAX_LEN/2] = {0};
	char pkiapiDllNameList[8][MAX_LEN/2];
	char keyDllNameList[8][MAX_LEN/2];
	int pkiCount = 0;
	int dllCount = 0;

	char SymmTypeLable[MAX_LEN/2] = {0};
	char SymmType[MAX_LEN/2] = {0};
	char symmNameList[50][MAX_LEN/2];
	int  symmCount = 0;
	int pos3 = 0;

	char HashTypeLable[MAX_LEN/2] = {0};
	char HashType[MAX_LEN/2] = {0};
	char hashNameList[50][MAX_LEN/2];
	int  hashCount = 0;
	int pos4 = 0;
	

	bool pkiFlag = false;
	for(int i=1; i<=dDevNum; i++)
	{
		memset(DevNameLabel, 0, MAX_LEN/2);
		memset(DevName, 0, MAX_LEN/2);
		sprintf(DevNameLabel, "DevName%03d", i);
		ret = GetParamFromConf(DevNameLabel, DevName);

		memset(PIDLabel, 0, MAX_LEN/2);
		memset(i_pid, 0, MAX_LEN/2);
		sprintf(PIDLabel, "PID%03d", i);
		ret = GetParamFromConf(PIDLabel, i_pid);

		memset(VIDLabel, 0, MAX_LEN/2);
		memset(i_vid, 0, MAX_LEN/2);
		sprintf(VIDLabel, "VID%03d", i);
		ret = GetParamFromConf(VIDLabel, i_vid);

	
		memset(KeyTypeLabel, 0, MAX_LEN/2);
		memset(cdllname, 0, MAX_DLLNAME);
		sprintf(KeyTypeLabel, "KeyProviderType%03d", i);
		ret = GetParamFromConf(KeyTypeLabel, cdllname);

		memset(PkiapiTypeLabel, 0, MAX_LEN/2);
		memset(pkiapiname, 0, MAX_DLLNAME);
		sprintf(PkiapiTypeLabel, "PkiapiType%03d", i);
		ret = GetParamFromConf(PkiapiTypeLabel, pkiapiname);
		

		memset(DevID, 0, MAX_LEN/2);
		memset(KeyTypeID, 0, MAX_LEN/2);
		sprintf(DevID, "DevID%03d", i);
		ret = GetParamFromConf(DevID, KeyTypeID);
		OutputDebugString(KeyTypeID);

		memset(SymmTypeLable, 0, MAX_LEN/2);
		memset(SymmType, 0, MAX_LEN/2);
		sprintf(SymmTypeLable, "SymmType%03d", i);
		ret = GetParamFromConf(SymmTypeLable, SymmType);

		memset(HashTypeLable, 0, MAX_LEN/2);
		memset(HashType, 0, MAX_LEN/2);
		sprintf(HashTypeLable, "HashType%03d", i);
		ret = GetParamFromConf(HashTypeLable, HashType);

		if(EnumDevicecheck(i_pid, i_vid) == true)
		{
			if(dllname != NULL)
			{
				pkiFlag = false;
				for(int j=0;j<pkiCount;j++)
				{
					if(strcmp(pkiapiDllNameList[j],cdllname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(pkiapiDllNameList[pkiCount], cdllname, strlen(cdllname)+1); 
					pkiCount++;
					memcpy(dllname+pos, cdllname, strlen(cdllname)+1); 
					pos+=strlen(cdllname)+1;
				}
				pkiFlag = false;
				for(int j=0;j<dllCount;j++)
				{
					if(strcmp(keyDllNameList[j],pkiapiname)==0)
					{
						pkiFlag = true;
						break;
					}
				}
				if(!pkiFlag)
				{
					memcpy(keyDllNameList[dllCount], pkiapiname, strlen(pkiapiname)+1); 
					dllCount++;
					memcpy(pkiapidllname+pos2, pkiapiname, strlen(pkiapiname)+1); 
					pos2+=strlen(pkiapiname)+1;	
				}

				
				memcpy(symmNameList[symmCount], SymmType, strlen(SymmType)+1); 
				symmCount++;
				memcpy(symmtype+pos3, SymmType, strlen(SymmType)+1); 
				pos3+=strlen(SymmType)+1;
				
				memcpy(hashNameList[hashCount], HashType, strlen(HashType)+1); 
				hashCount++;
				memcpy(hashtype+pos4, HashType, strlen(HashType)+1); 
				pos4+=strlen(HashType)+1;


				EkeyID = atoi(KeyTypeID);
			}
		}	
	}

	return EkeyID;
}

