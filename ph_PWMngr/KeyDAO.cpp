
// KeyDAO.cpp: implementation of the CKeyDao class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "TestTools.h"
#include "KeyDAO.h"
#include "MyUtil.h"


#include <string>
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//unsigned long devH = 0;
//unsigned long sessH = 0;
char dllName_in[64]={0x00};

CKeyDao CKeyDao::hInst;

CKeyDao* CKeyDao::GetInstance() 
{
	return &hInst;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeyDao::CKeyDao()
{
	m_hDevice = NULL;
}

CKeyDao::~CKeyDao()
{
//	CloseDevice();
}

void ErrAlert(LPCTSTR szMsg, int nErr)
{
	CString szErr;
	szErr.Format("%s: error code=%d", szMsg, nErr);
	//AfxMessageBox(szErr,"",MB_ICONERROR);
	MessageBox(NULL,szErr,"",MB_ICONERROR);
}

BOOL CKeyDao::WhichKey(char *dllname, char *pkiapidllname)
{
	HINSTANCE hinst;
	int ret = 0;
	hinst = LoadLibrary("autonk_sign.dll");
	if(NULL == hinst)
	{
		return FALSE;
	}
	typedef DWORD (__stdcall *PROC_WHICHKEY)(char *,char *);
	PROC_WHICHKEY which_key =(PROC_WHICHKEY)GetProcAddress(hinst,"WHICH_KEY");
	ret = which_key(dllname,pkiapidllname);
	if(1 == ret && !strcmp("SKF_APP.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if( 2 == ret && !strcmp("HTHRSSRSATOGM.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if(3 == ret && !strcmp("KALOGM.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if(4 == ret && !strcmp("ZFHLGM.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if(5 == ret && !strcmp("SKFAPI.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if(6 == ret && !strcmp("FTTOGM.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else if(7 == ret && !strcmp("SKF_APP.dll",dllname))
	{
		memcpy(dllName_in,dllname,strlen(dllname)+1);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CKeyDao::OpenDevice(DEVHANDLE *handle)
{
	int ret = 0;
	int result = 0;
	HINSTANCE hinst;
	char dllname[256];
	memset(dllname,0,256);
	char pkiapidllname[256];
	memset(pkiapidllname,0,256);
	hinst = LoadLibrary("autonk_sign.dll");
	if(NULL == hinst)
	{
		return FALSE;
	}
	typedef DWORD (__stdcall *PROC_WHICHKEY)(char *,char *);
	PROC_WHICHKEY which_key =(PROC_WHICHKEY)GetProcAddress(hinst,"WHICH_KEY");
	result = which_key(dllname,pkiapidllname);
	if(result == -1)
	{
		/*CString rt;
		rt.Format("%d",result);
		MessageBox(NULL," 调用which_key返回值==========="+rt,"提示",MB_OK);*/
		return FALSE;
	}
	memcpy(dllName_in,dllname,strlen(dllname)+1);
	ret = LoadPkiServerDll(dllName_in);
	if(ret)
	{
		//ErrAlert("加载动态库失败",ret);
		/*CString rtl;
		rtl.Format("%d",ret);
		MessageBox(NULL," 调用LoadPkiServerDll返回值==========="+rtl,"提示",MB_OK);*/
		return FALSE;
	}

	char decname[256] = "0";
	LPSTR decName = decname;
	ULONG lengSize = 256;
	ULONG *pulSize=&lengSize;
	
	BYTE pbHashdata[32]={0};
	ULONG pbHashlen=0;

	ret = GM_SKF_EnumDev(true,decName,pulSize);
	if(ret)
	{
		//ErrAlert("枚举设备失败",ret);
		return FALSE;
	}
	ret = GM_SKF_ConnectDev(decName,handle);
	if(ret)
	{
		//ErrAlert("连接设备失败",ret);
		return FALSE;
	}
	m_hDevice = handle;

	return TRUE;
}

BOOL CKeyDao::CloseDevice(DEVHANDLE C_handle)
{
	int ret = 0;
	ret = GM_SKF_DisConnectDev(C_handle);
	if(ret)
	{
		//ErrAlert("断开设备失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::DevAuth(DEVHANDLE D_handle)
{
	int ret = 0;
	BYTE authCode[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	DEVINFO DevInfo={0};
	ret=GM_SKF_GetDevInfo ( D_handle, &DevInfo); //获取设备信息
	if(ret==SAR_FAIL)
	{
		ret = GM_SKF_SetLabel(D_handle,"1234567890abcdef");
		if(ret !=0 )
		{
			return FALSE;
		}
		ret = GM_SKF_GetDevInfo ( D_handle, &DevInfo);
	}
	//设备认证
	BYTE pucRandom[17]={0};
	ULONG ulRandomLen=8;
	ret = GM_SKF_GenRandom(D_handle,pucRandom,ulRandomLen);
	if(ret != 0)
	{			
		return FALSE;
	}
	ULONG ulKeyLen=16;
	HANDLE hKey;
		
	if(DevInfo.DevAuthAlgId == 0x0)
	{
		DevInfo.DevAuthAlgId = SGD_SSF33_ECB;
	}
	ret = GM_SKF_SetSymmKey(D_handle, authCode,DevInfo.DevAuthAlgId,&hKey);
	if(ret != 0)
	{			
		return FALSE;
	}
	//加密随机数
	BYTE pucAuthCode[128]={0};
	ULONG ulAuthCodeLen=128;

	memset(pucRandom+8,0x00,8);
		
	BLOCKCIPHERPARAM EncryptParam ;
	memset(&EncryptParam, 0, sizeof(BLOCKCIPHERPARAM)); //设备认证时
	ret = GM_SKF_EncryptInit(hKey,EncryptParam);
	if(ret != 0)
	{				
		return FALSE;
	}
		
	ret = GM_SKF_Encrypt( hKey,pucRandom,16,pucAuthCode,&ulAuthCodeLen);
	GM_SKF_CloseHandle(hKey);
	if(ret != 0)
	{				
		return FALSE;
	}
	//设备认证
	{
			
		ret = GM_SKF_DevAuth(D_handle,pucAuthCode,ulAuthCodeLen);
		//如果使用authCode认证出错,再使用authCode1认证	
		if(ret != 0)
		{	
			BYTE bRandom[0x10] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, bKey[0x40] = {0}, bData1[1024] = {0};
			memcpy(bKey, "1111111111111111", 16);
			ret = GM_SKF_GenRandom(D_handle, bRandom, 8);
			if(ret != 0)
			{			
			return FALSE;
			}
			ret = GM_SKF_SetSymmKey(D_handle, bKey,DevInfo.DevAuthAlgId,&hKey);
			if(ret != 0)
			{			
				return FALSE;
			}
			//加密随机数
				
			ret = GM_SKF_EncryptInit(hKey,EncryptParam);
			if(ret != 0)
			{				
				return FALSE;
			}
			ret = GM_SKF_Encrypt( hKey,bRandom,0x10,pucAuthCode,&ulAuthCodeLen);
			GM_SKF_CloseHandle(hKey);
			if(ret != 0)
			{				
				return FALSE;
			}
				
			ret = GM_SKF_DevAuth(D_handle,pucAuthCode,ulAuthCodeLen);
			if(ret != 0)
			{
				ErrAlert("设备认证失败",ret);
				return FALSE;
			}
				
		}
	}
	return TRUE;
}

BOOL CKeyDao::CreateApplication(DEVHANDLE hDev,
								LPSTR szAppName,
								LPSTR szAdminPin,
								DWORD dwAdminPinRetryCount,
								LPSTR szUserPin,
								DWORD dwUserPinRetryCount,
								DWORD dwCreateFileRights,
								HAPPLICATION *phApplication)
{
	int ret = 0;
	ret = GM_SKF_DeleteApplication(hDev,szAppName);
	ret = GM_SKF_CreateApplication(hDev,szAppName,szAdminPin,dwAdminPinRetryCount,szUserPin,dwUserPinRetryCount,dwCreateFileRights,phApplication);
	if(ret)
	{
		//ErrAlert("创建应用失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::CreateContainer(HAPPLICATION happlication,LPSTR szContainer,HCONTAINER *hcontainer)
{
	int ret = 0;
	ret = GM_SKF_CreateContainer(happlication,szContainer,hcontainer);
	if(ret)
	{
		//ErrAlert("创建容器失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::GetContainerType(HCONTAINER hcontainer,ULONG *pulContainerType)
{
	int ret = 0;
	ret = GM_SKF_GetContainerType(hcontainer,pulContainerType);
	if(ret)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::VerifyPIN(HAPPLICATION happlication,ULONG type,LPSTR szUserPin,ULONG *pulRetryCount)
{
	int ret = 0;
	ret = GM_SKF_VerifyPIN(happlication,type,szUserPin,pulRetryCount);
	if(ret)
	{
		/*ErrAlert("校验口令失败",ret);*/
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::Logout(HAPPLICATION happlication)
{
	int ret = 0;
	ret = GM_SKF_ClearSecureState(happlication);
	if(ret)
	{
		/*ErrAlert("登陆退出失败",ret);*/
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::UnblockPIN(HAPPLICATION hApplication,LPSTR szAdminPIN,LPSTR szNewUserPIN,ULONG *pulRetryCount)
{
	int ret = 0;
	ret = GM_SKF_UnblockPIN(hApplication,szAdminPIN,szNewUserPIN,pulRetryCount);
	if(ret)
	{
		ErrAlert("解锁PIN失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::ChangePIN(HAPPLICATION hApplication,ULONG ulPINType,LPSTR szOldPin,LPSTR szNewPin,ULONG *pulRetryCount)
{
	int ret = 0;
	ret = GM_SKF_ChangePIN(hApplication,ulPINType,szOldPin,szNewPin,pulRetryCount);
	if(ret)
	{
		ErrAlert("修改PIN码失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::GenRSAKeyPair(HCONTAINER hcontainer,ULONG uBitLong,RSAPUBLICKEYBLOB *rsapublickeyblobForSign)
{
	int ret = 0;
	ret = GM_SKF_GenRSAKeyPair(hcontainer,uBitLong,rsapublickeyblobForSign);
	if(ret)
	{
		//ErrAlert("生成签名密钥对失败",ret);
		return FALSE;
	}
	return TRUE;
}

DWORD CKeyDao::GenECCKeyPair(HCONTAINER hcontainer,ULONG AlgID,ECCPUBLICKEYBLOB *eccpublickeyblob)
{
	int ret = 0;
	ret = GM_SKF_GenECCKeyPair(hcontainer,AlgID,eccpublickeyblob);
	if(ret == SAR_NOTSUPPORTKEYTYPE)
	{
		//ErrAlert("载体不支持SM2算法",ret);
		return ret;
	}
	if(0 != ret)
	{
		return ret;
	}
	return 0;
}

BOOL CKeyDao::CreateFile(HAPPLICATION hApplication,
						LPSTR szFileName,
						ULONG ulFileSize,						 
						ULONG ulReadRights,
						ULONG ulWriteRights)
{
	int ret = 0;
	ret = GM_SKF_CreateFile(hApplication,szFileName,ulFileSize,ulReadRights,ulWriteRights);
	if(ret)
	{
		//ErrAlert("创建文件失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::WriteFile(HAPPLICATION hApplication,
                       LPSTR szFile,
					   ULONG ulOffset,
					   BYTE *pbData,
					   ULONG ulSize)
{
	int ret = 0;
	ret = GM_SKF_WriteFile(hApplication,szFile,ulOffset,pbData,ulSize);
	if(ret)
	{
		//ErrAlert("写入文件失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::GenRandom(DEVHANDLE phDev,BYTE *pbRandom,ULONG len)
{
	int ret = 0;
	ret = GM_SKF_GenRandom(phDev,pbRandom,len);
	if(ret)
	{
//		ErrAlert("生成随机数失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::RSASignData(HCONTAINER hcontainer,BYTE * pbDataforsign,ULONG uDatalenforsign,BYTE *pbSignature,ULONG *pulSignLen)
{
	int ret = 0;
	ret = GM_SKF_RSASignData(hcontainer,pbDataforsign,uDatalenforsign,pbSignature,pulSignLen);
	if(0!=ret)
	{
//		ErrAlert("签名失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::DigestInit(DEVHANDLE phDev,ULONG hashAlgo,ECCPUBLICKEYBLOB * pEccpublickeyblob,BYTE * pucID,ULONG ulIdlen,HANDLE * phHash)
{
	int ret = 0;
	ret = GM_SKF_DigestInit(phDev,hashAlgo,pEccpublickeyblob,pucID,ulIdlen,phHash);
	if(ret)
	{
		//ErrAlert("杂凑初始化失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::Digest(HANDLE hHash,
					 BYTE *pbData,
					 ULONG ulDataLen,
					 BYTE *pbHashData,
					 ULONG *pulHashLen)
{
	int ret = 0;
	ret = GM_SKF_Digest(hHash,pbData,ulDataLen,pbHashData,pulHashLen);
	if(ret)
	{
		//ErrAlert("杂凑失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::EnumContainer(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize)
{
	int ret = 0;
	ret = GM_SKF_EnumContainer(hApplication,szContainerName,pulSize);
	if(ret)
	{
		ErrAlert("枚举容器失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer)
{
	int ret = 0;
	ret = GM_SKF_OpenContainer(hApplication,szContainerName,phContainer);
	if(ret)
	{
		ErrAlert("打开容器失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::CloseContainer(HCONTAINER hcontainer)
{
	int ret = 0;
	ret = GM_SKF_CloseContainer(hcontainer);
	if(ret)
	{
		ErrAlert("关闭容器失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::EnumApplication(DEVHANDLE hDev,LPSTR szAppName,ULONG *pulSize)
{
	int ret = 0;
	ret = GM_SKF_EnumApplication(hDev,szAppName,pulSize);
	if(ret)
	{
		//ErrAlert("枚举应用失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::OpenApplication(DEVHANDLE hDev,LPSTR szAppName,HAPPLICATION *phApplication)
{
	int ret = 0;
	ret = GM_SKF_OpenApplication(hDev,szAppName,phApplication);
	if(ret)
	{
		/*ErrAlert("打开应用失败",ret);*/
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::EnumFiles(HAPPLICATION hApplication,LPSTR szFileList,ULONG *pulSize)
{
	int ret = 0;
	ret = GM_SKF_EnumFiles(hApplication,szFileList,pulSize);
	if(ret)
	{
		//ErrAlert("枚举文件失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::ReadFile(HAPPLICATION hApplication,LPSTR szFile,ULONG ulOffset,ULONG ulSize,BYTE *pbOutData,ULONG *pulOutLen)
{
	int ret = 0;
	ret = GM_SKF_ReadFile(hApplication,szFile,ulOffset,ulSize,pbOutData,pulOutLen);
	if(ret)
	{
		/*ErrAlert("读取文件失败",ret);*/
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::GetFileInfo(HAPPLICATION hApplication,LPSTR szFile,FILEATTRIBUTE *pFileInfo)
{
	int ret = 0;
	ret = GM_SKF_GetFileInfo(hApplication,szFile,pFileInfo);
	if(ret)
	{
		//ErrAlert("获取文件信息失败",ret);
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::ECCSignData(HCONTAINER hcontainer,BYTE *pbHashdata,ULONG pbHashlen,PECCSIGNATUREBLOB eccsignatureblob)
{
	int ret = 0;
	ret = GM_SKF_ECCSignData(hcontainer,pbHashdata,pbHashlen,eccsignatureblob);
	if(0 != ret)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::ExportPublicKey(HCONTAINER hContainer,BOOL bSignFlag,BYTE* pbBlob,ULONG *pulBlobLen)
{
	int ret = 0;
	ret = GM_SKF_ExportPublicKey(hContainer,bSignFlag,pbBlob,pulBlobLen);
	if(0 != ret)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::RSAVerify(DEVHANDLE     hDev,
						RSAPUBLICKEYBLOB *pRSAPubKeyBlob,						   						  
						BYTE          *pbData,
						ULONG         ulDataLen,
						BYTE          *pbSignature,
						ULONG         ulSigLen)
{
	int ret=0;
	ret=GM_SKF_RSAVerify(hDev,pRSAPubKeyBlob,pbData,ulDataLen,pbSignature,ulSigLen);
	if(0 != ret)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CKeyDao::ExtRSAPubKeyOperation(DEVHANDLE hDev,
									RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
									BYTE *pbInput,
									ULONG ulInputLen,
									BYTE *pbOutput,
									ULONG *pulOutputLen)
{
	int ret=0;
	ret=GM_SKF_ExtRSAPubKeyOperation(hDev,pRSAPubKeyBlob,pbInput,ulInputLen,pbOutput,pulOutputLen);
	if(0 != ret)
	{
		return FALSE;
	}
	return TRUE;
}