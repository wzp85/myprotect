#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "DAI.h"
#include "DAIDef.h"


#include <time.h>

#ifdef  WHLINUX
	#include  <dirent.h>
#else
	#include <windows.h>
#endif


HINSTANCE	pkiServerInstance = NULL;
PkiServerApi m_pkiServerApi;

int   LoadPkiServerDll(char* dllName)
{

	
		
#ifdef WHLINUX
	pkiServerInstance = dlopen(dllName,RTLD_NOW);
	dlerror();		
#else	
	pkiServerInstance = LoadLibraryA(dllName);
#endif
	if(pkiServerInstance == NULL)
	{
		return -1;
	}
	else
	{
		
		
			m_pkiServerApi.SKF_ConnectDev						   = (PROC_SKF_ConnectDev)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ConnectDev");
			m_pkiServerApi.SKF_GetDevInfo                          = (PROC_SKF_GetDevInfo)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GetDevInfo");
			m_pkiServerApi.SKF_DisConnectDev                       = (PROC_SKF_DisConnectDev)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DisConnectDev");
			m_pkiServerApi.SKF_EnumDev                             = (PROC_SKF_EnumDev)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EnumDev");
			m_pkiServerApi.SKF_GetPINInfo                          = (PROC_SKF_GetPINInfo)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GetPINInfo");
			m_pkiServerApi.SKF_GenRandom						   = (PROC_SKF_GenRandom)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenRandom");
			m_pkiServerApi.SKF_GenExtRSAKey						   = (PROC_SKF_GenExtRSAKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenExtRSAKey");
			m_pkiServerApi.SKF_CreateApplication				   = (PROC_SKF_CreateApplication)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CreateApplication");
			m_pkiServerApi.SKF_EnumApplication					   = (PROC_SKF_EnumApplication)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EnumApplication");
			m_pkiServerApi.SKF_CreateContainer                     = (PROC_SKF_CreateContainer)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CreateContainer");
			m_pkiServerApi.SKF_GetContainerType                    = (PROC_SKF_GetContainerType)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GetContainerType");
			m_pkiServerApi.SKF_GenRSAKeyPair					   = (PROC_SKF_GenRSAKeyPair)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenRSAKeyPair");
			m_pkiServerApi.SKF_VerifyPIN						   = (PROC_SKF_VerifyPIN)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_VerifyPIN");
			m_pkiServerApi.SKF_SetSymmKey						   = (PROC_SKF_SetSymmKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_SetSymmKey");
			m_pkiServerApi.SKF_EncryptInit                         = (PROC_SKF_EncryptInit)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EncryptInit");
			m_pkiServerApi.SKF_Encrypt                             = (PROC_SKF_Encrypt)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_Encrypt");
			m_pkiServerApi.SKF_DevAuth							   = (PROC_SKF_DevAuth)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DevAuth");
			m_pkiServerApi.SKF_DeleteApplication                   = (PROC_SKF_DeleteApplication)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DeleteApplication");
			m_pkiServerApi.SKF_OpenApplication                     = (PROC_SKF_OpenApplication)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_OpenApplication");
			m_pkiServerApi.SKF_OpenContainer                       = (PROC_SKF_OpenContainer)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_OpenContainer");
			m_pkiServerApi.SKF_CloseContainer                      = (PROC_SKF_CloseContainer)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CloseContainer");
			m_pkiServerApi.SKF_CreateFile                          = (PROC_SKF_CreateFile)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CreateFile");
			m_pkiServerApi.SKF_GetFileInfo                         = (PROC_SKF_GetFileInfo)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GetFileInfo");
			m_pkiServerApi.SKF_EnumFiles                           = (PROC_SKF_EnumFiles)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EnumFiles");
			m_pkiServerApi.SKF_WriteFile                           = (PROC_SKF_WriteFile)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_WriteFile");
			m_pkiServerApi.SKF_ReadFile                            = (PROC_SKF_ReadFile)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ReadFile");
			m_pkiServerApi.SKF_ChangePIN                           = (PROC_SKF_ChangePIN)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ChangePIN");
			m_pkiServerApi.SKF_GenECCKeyPair					   = (PROC_SKF_GenECCKeyPair)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenECCKeyPair");
			m_pkiServerApi.SKF_ECCSignData						   = (PROC_SKF_ECCSignData)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ECCSignData");
			m_pkiServerApi.SKF_ECCVerify                           = (PROC_SKF_ECCVerify)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ECCVerify");
			m_pkiServerApi.SKF_DigestInit						   = (PROC_SKF_DigestInit)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DigestInit");
			m_pkiServerApi.SKF_ExportPublicKey                     = (PROC_SKF_ExportPublicKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExportPublicKey");
			m_pkiServerApi.SKF_Digest                              = (PROC_SKF_Digest)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_Digest");
			m_pkiServerApi.SKF_DigestUpdate						   = (PROC_SKF_DigestUpdate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DigestUpdate");
			m_pkiServerApi.SKF_DigestFinal						   = (PROC_SKF_DigestFinal)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DigestFinal");
			m_pkiServerApi.SKF_RSASignData						   = (PROC_SKF_RSASignData)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_RSASignData");
			m_pkiServerApi.SKF_RSAVerify						   = (PROC_SKF_RSAVerify)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_RSAVerify");
			m_pkiServerApi.SKF_ClearSecureState                    = (PROC_SKF_ClearSecureState)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ClearSecureState");
			m_pkiServerApi.SKF_CloseApplication                    = (PROC_SKF_CloseApplication)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CloseApplication");
			m_pkiServerApi.SKF_GenExtRSAKey						   = (PROC_SKF_GenExtRSAKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenExtRSAKey");
			m_pkiServerApi.SKF_ExtRSAPubKeyOperation               = (PROC_SKF_ExtRSAPubKeyOperation)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtRSAPubKeyOperation");
			m_pkiServerApi.SKF_ExtRSAPriKeyOperation               = (PROC_SKF_ExtRSAPriKeyOperation)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtRSAPriKeyOperation");
			m_pkiServerApi.SKF_DecryptInit						   = (PROC_SKF_DecryptInit)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DecryptInit");
			m_pkiServerApi.SKF_Decrypt                             = (PROC_SKF_Decrypt)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_Decrypt");
			m_pkiServerApi.SKF_ImportRSAKeyPair                    = (PROC_SKF_ImportRSAKeyPair)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ImportRSAKeyPair");
			m_pkiServerApi.SKF_EnumContainer                       = (PROC_SKF_EnumContainer)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EnumContainer");
			m_pkiServerApi.SKF_ImportCertificate                   = (PROC_SKF_ImportCertificate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ImportCertificate");
			m_pkiServerApi.SKF_ExportCertificate                   = (PROC_SKF_ExportCertificate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExportCertificate");
			m_pkiServerApi.SKF_ExtECCEncrypt                       = (PROC_SKF_ExtECCEncrypt)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtECCEncrypt");
			m_pkiServerApi.SKF_ImportSessionKey                    = (PROC_SKF_ImportSessionKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ImportSessionKey");
			m_pkiServerApi.SKF_EncryptUpdate                       = (PROC_SKF_EncryptUpdate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EncryptUpdate");
			m_pkiServerApi.SKF_EncryptFinal                        = (PROC_SKF_EncryptFinal)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_EncryptFinal");
			m_pkiServerApi.SKF_DecryptUpdate                       = (PROC_SKF_DecryptUpdate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DecryptUpdate");                                                      
			m_pkiServerApi.SKF_DecryptFinal						   = (PROC_SKF_DecryptFinal)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DecryptFinal");
			m_pkiServerApi.SKF_RSAExportSessionKey				   = (PROC_SKF_RSAExportSessionKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_RSAExportSessionKey");
			m_pkiServerApi.SKF_ECCExportSessionKey				   = (PROC_SKF_ECCExportSessionKey)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ECCExportSessionKey");
			m_pkiServerApi.SKF_ExtECCSign					       = (PROC_SKF_ExtECCSign)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtECCSign");
			m_pkiServerApi.SKF_ExtECCVerify						   = (PROC_SKF_ExtECCVerify)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtECCVerify");
			m_pkiServerApi.SKF_GenerateAgreementDataWithECC		   = (PROC_SKF_GenerateAgreementDataWithECC)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenerateAgreementDataWithECC");
			m_pkiServerApi.SKF_GenerateAgreementDataAndKeyWithECC  = (PROC_SKF_GenerateAgreementDataAndKeyWithECC)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenerateAgreementDataAndKeyWithECC");
			m_pkiServerApi.SKF_GenerateKeyWithECC				   = (PROC_SKF_GenerateKeyWithECC)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_GenerateKeyWithECC");
			m_pkiServerApi.SKF_MacInit						       = (PROC_SKF_MacInit)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_MacInit");
			m_pkiServerApi.SKF_Mac						           = (PROC_SKF_Mac)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_Mac");
			m_pkiServerApi.SKF_MacUpdate						   = (PROC_SKF_MacUpdate)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_MacUpdate");
			m_pkiServerApi.SKF_MacFinal						       = (PROC_SKF_MacFinal)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_MacFinal");
			m_pkiServerApi.SKF_ImportECCKeyPair					   = (PROC_SKF_ImportECCKeyPair)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ImportECCKeyPair");
			m_pkiServerApi.SKF_ExtECCEncrypt					   = (PROC_SKF_ExtECCEncrypt)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtECCEncrypt");
			m_pkiServerApi.SKF_ExtECCDecrypt					   = (PROC_SKF_ExtECCDecrypt)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_ExtECCDecrypt");
			m_pkiServerApi.SKF_DeleteFile						   = (PROC_SKF_DeleteFile)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DeleteFile");
			m_pkiServerApi.SKF_DeleteContainer					   = (PROC_SKF_DeleteContainer)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_DeleteContainer");
			m_pkiServerApi.SKF_UnblockPIN						   = (PROC_SKF_UnblockPIN)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_UnblockPIN");
			m_pkiServerApi.SKF_SetLabel						       = (PROC_SKF_SetLabel)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_SetLabel");
		    m_pkiServerApi.SKF_CloseHandle						   = (PROC_SKF_CloseHandle)GetProcAddress(pkiServerInstance,(LPCSTR)"SKF_CloseHandle");
		}

	/*if(
		m_pkiServerApi.SDF_OpenDevice						  ==NULL||
		m_pkiServerApi.SDF_CloseDevice                        ==NULL||
		m_pkiServerApi.SDF_OpenSession                        ==NULL||
		m_pkiServerApi.SDF_CloseSession                       ==NULL||
		m_pkiServerApi.SDF_GetDeviceInfo                      ==NULL||
		m_pkiServerApi.SDF_GenerateRandom                     ==NULL||
		m_pkiServerApi.SDF_GetPrivateKeyAccessRight           ==NULL||
		m_pkiServerApi.SDF_ReleasePrivateKeyAccessRight       ==NULL||
		m_pkiServerApi.SDF_ExportSignPublicKey_RSA            ==NULL||
		m_pkiServerApi.SDF_ExportEncPublicKey_RSA             ==NULL||
		m_pkiServerApi.SDF_GenerateKeyPair_RSA                ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithIPK_RSA             ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithEPK_RSA             ==NULL||
		m_pkiServerApi.SDF_ImportKeyWithISK_RSA               ==NULL||
		m_pkiServerApi.SDF_ExchangeDigitEnvelopeBaseOnRSA     ==NULL||
		m_pkiServerApi.SDF_ExportSignPublicKey_ECC            ==NULL||
		m_pkiServerApi.SDF_ExportEncPublicKey_ECC             ==NULL||
		m_pkiServerApi.SDF_GenerateKeyPair_ECC                ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithIPK_ECC             ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithEPK_ECC             ==NULL||
		m_pkiServerApi.SDF_ImportKeyWithISK_ECC               ==NULL||
		m_pkiServerApi.SDF_GenerateAgreementDataWithECC       ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithECC                 ==NULL||
		m_pkiServerApi.SDF_GenerateAgreementDataAndKeyWithECC ==NULL||
		m_pkiServerApi.SDF_ExchangeDigitEnvelopeBaseOnECC     ==NULL||
		m_pkiServerApi.SDF_GenerateKeyWithKEK                 ==NULL||
		m_pkiServerApi.SDF_ImportKeyWithKEK                   ==NULL||
		m_pkiServerApi.SDF_ImportKey                          ==NULL||
		m_pkiServerApi.SDF_DestoryKey                         ==NULL||
		m_pkiServerApi.SDF_ExternalPublicKeyOperation_RSA     ==NULL||
		m_pkiServerApi.SDF_ExternalPrivateKeyOperation_RSA    ==NULL||
		m_pkiServerApi.SDF_InternalPublicKeyOperation_RSA     ==NULL||
		m_pkiServerApi.SDF_InternalPrivateKeyOperation_RSA    ==NULL||
		m_pkiServerApi.SDF_ExternalSign_ECC                   ==NULL||
		m_pkiServerApi.SDF_ExternalVerify_ECC                 ==NULL||
		m_pkiServerApi.SDF_InternalSign_ECC                   ==NULL||
		m_pkiServerApi.SDF_InternalVerify_ECC                 ==NULL||
		m_pkiServerApi.SDF_ExternalEncrytp_ECC                ==NULL||
		m_pkiServerApi.SDF_ExternalDecrypt_ECC                ==NULL||
		m_pkiServerApi.SDF_Encrypt                            ==NULL||
		m_pkiServerApi.SDF_Decrypt                            ==NULL||
		m_pkiServerApi.SDF_CalculateMAC                       ==NULL||
		m_pkiServerApi.SDF_HashInit                           ==NULL||
		m_pkiServerApi.SDF_HashUpdate                         ==NULL||
		m_pkiServerApi.SDF_HashFinal                          ==NULL||
		m_pkiServerApi.SDF_CreateFile                         ==NULL||
		m_pkiServerApi.SDF_ReadFile                           ==NULL||
		m_pkiServerApi.SDF_WriteFile                          ==NULL||
		m_pkiServerApi.SDF_DeleteFile                         ==NULL) 
	{                               
#ifndef WHLINUX                                 
		FreeLibrary(pkiServerInstance);
#endif                                          
		return WHERROR_PKIAPI_DLL_LOAD_ERROR;           
	}                               
	else                            
	{                               
		return  0;            
	}    */                           
                                      
	return 0;                            
}

int FreePkiServerDll()
{
	
	#ifdef WHLINUX
		if(pkiServerInstance!=NULL)
		{
			dlclose(pkiServerInstance);
			pkiServerInstance = NULL;
		}
		
	#else
		if(pkiServerInstance!=NULL)
		{
			FreeLibrary(pkiServerInstance);
			pkiServerInstance = NULL;
		}					
	#endif


	return 0;
}

DWORD GM_SKF_EnumDev(BOOL bPresent,LPSTR decName,ULONG *pulSize)//枚举设备
{
	return m_pkiServerApi.SKF_EnumDev(bPresent,decName,pulSize);
	//return 0;
}

DWORD GM_SKF_ConnectDev(LPSTR decName,DEVHANDLE *phDev)//连接设备
{
	return m_pkiServerApi.SKF_ConnectDev(decName,phDev);
}

DWORD GM_SKF_DisConnectDev(DEVHANDLE phDev)//断开设备
{
	return m_pkiServerApi.SKF_DisConnectDev(phDev);
}

DWORD GM_SKF_GetDevInfo(DEVHANDLE phDev,DEVINFO *devInfo)//获取设备信息
{
	return m_pkiServerApi.SKF_GetDevInfo(phDev,devInfo);
}

DWORD GM_SKF_GenRandom(DEVHANDLE phDev,BYTE *pbRandom,ULONG len)
{
	return m_pkiServerApi.SKF_GenRandom(phDev,pbRandom,8);
}

DWORD GM_SKF_GenExtRSAKey(DEVHANDLE hDev,
					      ULONG ulBitsLen,
						  RSAPRIVATEKEYBLOB *pBlob)//生成RSA外部密钥对
{
	return m_pkiServerApi.SKF_GenExtRSAKey(hDev,ulBitsLen,pBlob);
}
DWORD GM_SKF_CreateApplication(DEVHANDLE hDev,
								LPSTR szAppName,
								LPSTR szAdminPin,
								DWORD dwAdminPinRetryCount,
								LPSTR szUserPin,
								DWORD dwUserPinRetryCount,
								DWORD dwCreateFileRights,
								HAPPLICATION *phApplication)//创建应用
{
	/*dwCreateFileRights = SECURE_EVERYONE_ACCOUNT;*/
	return m_pkiServerApi.SKF_CreateApplication(hDev,
												szAppName,
												szAdminPin,
												dwAdminPinRetryCount,
												szUserPin,
												dwUserPinRetryCount,
												dwCreateFileRights,
												phApplication);
	
}
DWORD GM_SKF_EnumApplication(DEVHANDLE  phDev,LPSTR forEnumApplication,ULONG *thePulSize)//枚举应用
{
	return m_pkiServerApi.SKF_EnumApplication(phDev,forEnumApplication,thePulSize);
}

DWORD GM_SKF_DeleteApplication(DEVHANDLE hDev,LPSTR szAppName)
{
	return m_pkiServerApi.SKF_DeleteApplication(hDev,szAppName);
}

DWORD GM_SKF_CreateContainer(HAPPLICATION happlication,LPSTR szContainer,HCONTAINER *hcontainer)//创建容器
{
	return m_pkiServerApi.SKF_CreateContainer(happlication,szContainer,hcontainer);
	//return 0;	
}
DWORD GM_SKF_GetContainerType(HCONTAINER hcontainer,ULONG  *pulContainerType)//创建容器
{
	return m_pkiServerApi.SKF_GetContainerType(hcontainer,pulContainerType);
	//return 0;	
}
DWORD GM_SKF_CloseContainer(HCONTAINER hcontainer)//创建容器
{
	return m_pkiServerApi.SKF_CloseContainer(hcontainer);
	//return 0;	
}
DWORD GM_SKF_DeleteContainer(HAPPLICATION happlication,LPSTR szContainer)//创建容器
{
	return m_pkiServerApi.SKF_DeleteContainer(happlication,szContainer);
	//return 0;	
}

DWORD GM_SKF_GenRSAKeyPair(HCONTAINER hcontainer,ULONG uBitLong,RSAPUBLICKEYBLOB *rsapublickeyblobForSign)//生成RSA签名密钥对
{
	return m_pkiServerApi.SKF_GenRSAKeyPair(hcontainer,uBitLong,rsapublickeyblobForSign);
}

DWORD GM_SKF_VerifyPIN(HAPPLICATION happlication,ULONG type,LPSTR szUserPin,ULONG *pulRetryCount)//验证PIN码
{
//	#ifdef _56PKISERVER_
//		unsigned int pubKeyLen,priKeyLen; 
//		return m_pkiServerApi.SDF_GenerateKeyPair_RSA(hSessionHandle,SDM_RSA,uiKeyBits,(unsigned char *)pucPublicKey,&pubKeyLen,(unsigned char *)pucPrivateKey,&priKeyLen);
//	#else
		return m_pkiServerApi.SKF_VerifyPIN(happlication,type,szUserPin,pulRetryCount);
//	#endif
	//return m_pkiServerApi.SDF_GenerateKeyPair_RSA(hSessionHandle,uiKeyBits,pucPublicKey,pucPrivateKey);
}

DWORD GM_SKF_UnblockPIN(HAPPLICATION hApplication,LPSTR szAdminPIN,LPSTR szNewUserPIN,ULONG *pulRetryCount)
{
	return m_pkiServerApi.SKF_UnblockPIN(hApplication,szAdminPIN,szNewUserPIN,pulRetryCount);
}

DWORD GM_SKF_ChangePIN(HAPPLICATION hApplication,ULONG ulPINType,LPSTR szOldPin,LPSTR szNewPin,ULONG *pulRetryCount)
{
	return m_pkiServerApi.SKF_ChangePIN(hApplication,ulPINType,szOldPin,szNewPin,pulRetryCount);
}

DWORD GM_SKF_SetSymmKey(DEVHANDLE phDev,BYTE *pbData,ULONG ulAlgId,HANDLE *phKey)//设置明文对称密钥
{//SGD_SSF33_ECB或SGD_SM1_ECB 第二个入参16位！！！
	return m_pkiServerApi.SKF_SetSymmKey(phDev,pbData,ulAlgId,phKey);
}
DWORD GM_SKF_EncryptInit(HANDLE phKey,BLOCKCIPHERPARAM blockcipherparam)//加密初始化
{
	return m_pkiServerApi.SKF_EncryptInit(phKey,blockcipherparam);
}
DWORD GM_SKF_Encrypt(HANDLE hKey,				
					 BYTE *pbData,
					 ULONG ulDataLen,
					 BYTE *pbEncryptedData,
					 ULONG *pulEncryptedLen)
{
	return m_pkiServerApi.SKF_Encrypt(hKey,pbData,ulDataLen,pbEncryptedData,pulEncryptedLen);
}

DWORD GM_SKF_DevAuth(DEVHANDLE phDev,BYTE *forAuth,ULONG lenOfAuth)//设备认证
{
	return m_pkiServerApi.SKF_DevAuth(phDev,forAuth,lenOfAuth);
}
DWORD GM_SKF_DecryptInit(HANDLE phKey,BLOCKCIPHERPARAM DecryptParam)//解密初始化
{
	return m_pkiServerApi.SKF_DecryptInit(phKey,DecryptParam);
}
DWORD GM_SKF_Decrypt(HANDLE hKey,
					 BYTE *pbEncryptedData,
					 ULONG ulEncryptedLen,
					 BYTE *pbData,
					 ULONG *pulDataLen)
{
	return m_pkiServerApi.SKF_Decrypt(hKey,pbEncryptedData,ulEncryptedLen,pbData,pulDataLen);
}
DWORD GM_SKF_OpenApplication(DEVHANDLE phDev,LPSTR forEnumApplication,HAPPLICATION *happlication)
{
//#ifdef _SDF
	//BOOL flag;
	return m_pkiServerApi.SKF_OpenApplication(phDev,forEnumApplication,happlication);
//	
//#else
//	return m_pkiServerApi.SDF_ExportSignPublicKey_ECC(hSessionHandle, uiKeyIndex,pucPublicKey);
//#endif
		
}

DWORD GM_SKF_OpenContainer(HAPPLICATION happlication,LPSTR enumcontainer,HCONTAINER *hcontainer)//打开容器
{
//#ifdef _SDF
	//BOOL flag;
	return  m_pkiServerApi.SKF_OpenContainer(happlication,enumcontainer,hcontainer);
//	
//#else
//	return m_pkiServerApi.SDF_ExportEncPublicKey_ECC(hSessionHandle, uiKeyIndex,pucPublicKey);
//#endif
}

DWORD GM_SKF_GenECCKeyPair(HCONTAINER hcontainer,ULONG AlgID,ECCPUBLICKEYBLOB *eccpublickeyblob)//生成ECC签名密钥对
{
//#ifdef _SDF
	//BOOL flag;
	return  m_pkiServerApi.SKF_GenECCKeyPair(hcontainer,AlgID,eccpublickeyblob);
//#else
	//return m_pkiServerApi.SDF_ExportSignPrivateKey_RSA(hSessionHandle, uiKeyIndex,pucPrivateKey);
//#endif
}

DWORD GM_SKF_ECCSignData(HCONTAINER hcontainer,BYTE *pbHashdata,ULONG pbHashlen,PECCSIGNATUREBLOB eccsignatureblob)//ECC数字签名
{

	return m_pkiServerApi.SKF_ECCSignData(hcontainer,pbHashdata,pbHashlen,eccsignatureblob);

}
DWORD GM_SKF_ECCVerify(DEVHANDLE hDev , 
	                    ECCPUBLICKEYBLOB* pECCPubKeyBlob, 
						BYTE *pbData, 
						ULONG ulDataLen, 
						PECCSIGNATUREBLOB pSignature)//ECC验签
{
	return m_pkiServerApi.SKF_ECCVerify(hDev,pECCPubKeyBlob,pbData,ulDataLen,pSignature);
}
DWORD GM_SKF_DigestInit(DEVHANDLE phDev,ULONG hashAlgo,ECCPUBLICKEYBLOB * pEccpublickeyblob,BYTE * pucID,ULONG ulIdlen,HANDLE * phHash)//杂凑初始化
{
	return m_pkiServerApi.SKF_DigestInit(phDev,hashAlgo,pEccpublickeyblob,pucID,ulIdlen,phHash);
}

DWORD GM_SKF_ExportPublicKey(HCONTAINER hcontainer,BOOL b,BYTE *eccpublickeyblob,ULONG *pulBlobLen)//导出公钥
{
	return m_pkiServerApi.SKF_ExportPublicKey(hcontainer,b,eccpublickeyblob,pulBlobLen);
}

DWORD GM_SKF_DigestUpdate(HANDLE phHash,BYTE * pbData,ULONG ulDatalen)
{
	return m_pkiServerApi.SKF_DigestUpdate(phHash,pbData,ulDatalen);
}
DWORD GM_SKF_DigestFinal(HANDLE phHash,BYTE * pbHashdata,ULONG * pbHashlen)
{
	return m_pkiServerApi.SKF_DigestFinal(phHash,pbHashdata,pbHashlen);
}
DWORD GM_SKF_Digest(HANDLE hHash,
					  BYTE *pbData,
					  ULONG ulDataLen,
					  BYTE *pbHashData,
					  ULONG *pulHashLen)
{
	return m_pkiServerApi.SKF_Digest(hHash,pbData,ulDataLen,pbHashData,pulHashLen);
}
DWORD GM_SKF_RSASignData(HCONTAINER hcontainer,BYTE * pbDataforsign,ULONG uDatalenforsign,BYTE *pbSignature,ULONG *pulSignLen)//RSA签名
{
	return m_pkiServerApi.SKF_RSASignData(hcontainer,pbDataforsign,uDatalenforsign,pbSignature,pulSignLen);
}

DWORD GM_SKF_RSAVerify(DEVHANDLE     hDev,
					   RSAPUBLICKEYBLOB *pRSAPubKeyBlob,						   						  
                       BYTE          *pbData,
					   ULONG         ulDataLen,
					   BYTE          *pbSignature,
					   ULONG         ulSigLen)//RSA验签
{
	return m_pkiServerApi.SKF_RSAVerify(hDev,pRSAPubKeyBlob,pbData,ulDataLen,pbSignature,ulSigLen);
}

DWORD GM_SKF_ClearSecureState(HAPPLICATION happlication)//清楚登陆状态
{
	return m_pkiServerApi.SKF_ClearSecureState(happlication);
}

DWORD GM_SKF_CloseApplication(HAPPLICATION happlication)//关闭应用
{
	return m_pkiServerApi.SKF_CloseApplication(happlication);
}

DWORD GM_SKF_ExtRSAPubKeyOperation(DEVHANDLE hDev,
									RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
									BYTE *pbInput,
									ULONG ulInputLen,
									BYTE *pbOutput,
									ULONG *pulOutputLen)//RSA外来公钥运算
{
	return m_pkiServerApi.SKF_ExtRSAPubKeyOperation(hDev,pRSAPubKeyBlob,pbInput,ulInputLen,pbOutput,pulOutputLen);
}
DWORD GM_SKF_ExtRSAPriKeyOperation(DEVHANDLE hDev,
									RSAPRIVATEKEYBLOB *pRSAPriKeyBlob,
									BYTE *pbInput,
									ULONG ulInputLen,
									BYTE *pbOutput,
									ULONG *pulOutputLen)//RSA外来私钥运算
{
	return m_pkiServerApi.SKF_ExtRSAPriKeyOperation(hDev,pRSAPriKeyBlob,pbInput,ulInputLen,pbOutput,pulOutputLen);
}

DWORD GM_SKF_ImportRSAKeyPair(HCONTAINER hContainer,
							  ULONG ulSymAlgId,
                              BYTE *pbWrappedKey, 
							  ULONG ulWrappedKeyLen,
							  BYTE *pbEncryptedData,
							  ULONG ulEncryptedData)//导入RSA加密密钥对
{
	return m_pkiServerApi.SKF_ImportRSAKeyPair(hContainer,ulSymAlgId,pbWrappedKey,ulWrappedKeyLen,pbEncryptedData,ulEncryptedData);

}

DWORD GM_SKF_EnumContainer(HAPPLICATION happlication,LPSTR enumcontainer,ULONG *enumcontainerLen)
{
	return m_pkiServerApi.SKF_EnumContainer(happlication,enumcontainer,enumcontainerLen);
}
/*
DWORD GM_SKF_ImportCertificate(HCONTAINER,BOOL,BYTE *,ULONG)//导入数字证书
{
	return m_pkiServerApi.SKF_ImportCertificate(hcontainer,true,pbCer,cerLength);
}
DWORD GM_SKF_ExportCertificate(HCONTAINER,BOOL,BYTE *,ULONG *)//导出数字证书
{
	return m_pkiServerApi.SKF_ExportCertificate(hcontainer,true,pbCerOut,&cerLengthE);
}
*/
DWORD GM_SKF_ImportECCKeyPair(HCONTAINER hContainer,
	                          PENVELOPEDKEYBLOB pEnvelopedKeyBlob)//导入ECC加密密钥对
{
	return m_pkiServerApi.SKF_ImportECCKeyPair(hContainer,pEnvelopedKeyBlob);
}

DWORD GM_SKF_ImportSessionKey(HCONTAINER hContainer,
							  ULONG ulAlgId,
							  BYTE *pbWrapedData,
							  ULONG ulWrapedLen,
							  HANDLE *phKey)//导入会话密钥
{
	return m_pkiServerApi.SKF_ImportSessionKey(hContainer,ulAlgId,pbWrapedData,ulWrapedLen,phKey);
}

DWORD GM_SKF_RSAExportSessionKey(HCONTAINER hContainer,
								 ULONG ulAlgId,
								 RSAPUBLICKEYBLOB *pPubKey,								  
								 BYTE *pbData,
								 ULONG *pulDataLen,
                                 HANDLE *phSessionKey)//RSA生产并导出会话密钥
{
	return m_pkiServerApi.SKF_RSAExportSessionKey(hContainer,ulAlgId,pPubKey,pbData,pulDataLen,phSessionKey);
}

DWORD GM_SKF_ECCExportSessionKey(HCONTAINER hContainer, 
	                             ULONG ulAlgId, 
								 ECCPUBLICKEYBLOB *pPubKey, 
								 PECCCIPHERBLOB pData, 
								 HANDLE *phSessionKey)//ECC生产并导出会话密钥
{
	return m_pkiServerApi.SKF_ECCExportSessionKey(hContainer,ulAlgId,pPubKey,pData,phSessionKey);
}
DWORD GM_SKF_ExtECCSign(DEVHANDLE hDev, 
	                    ECCPRIVATEKEYBLOB *pECCPriKeyBlob,
						BYTE* pbData, 
						ULONG ulDataLen,
						PECCSIGNATUREBLOB pSignature)//ECC外来私钥签名
{
	return m_pkiServerApi.SKF_ExtECCSign(hDev,pECCPriKeyBlob,pbData,ulDataLen,pSignature);
}
DWORD GM_SKF_ExtECCVerify(DEVHANDLE phDev,ECCPUBLICKEYBLOB *eccpublickeyblob,BYTE *pbHasheddata,ULONG pbHashlen,PECCSIGNATUREBLOB eccsignatureblob)//ECC外来公钥验签
{
	return m_pkiServerApi.SKF_ExtECCVerify(phDev,eccpublickeyblob,pbHasheddata,pbHashlen,eccsignatureblob);
}
DWORD GM_SKF_ExtECCEncrypt(DEVHANDLE hDev,ECCPUBLICKEYBLOB *pECCPubKeyBlob,BYTE* pbPlainText,ULONG ulPlainTextLen,PECCCIPHERBLOB pCipherText)//ECC外来公钥加密
{
	return m_pkiServerApi.SKF_ExtECCEncrypt(hDev,pECCPubKeyBlob,pbPlainText,ulPlainTextLen,pCipherText);
}
DWORD GM_SKF_ExtECCDecrypt(DEVHANDLE hDev,ECCPRIVATEKEYBLOB *pECCPriKeyBlob,PECCCIPHERBLOB pCipherText,BYTE *pbPlainText,ULONG *pulPlainTextLen)//ECC外来私钥解密
{
	return m_pkiServerApi.SKF_ExtECCDecrypt(hDev,pECCPriKeyBlob,pCipherText,pbPlainText,pulPlainTextLen);
}
DWORD GM_SKF_GenerateAgreementDataWithECC(HCONTAINER hcontainer,ULONG a,ECCPUBLICKEYBLOB *pTempECCPubKeyBlob,BYTE *pbID,ULONG,HANDLE *pbAgreementHandle)//ECC生成密钥协商参数
{//SGD_SM2_1
	return m_pkiServerApi.SKF_GenerateAgreementDataWithECC(hcontainer,a,pTempECCPubKeyBlob,pbID,16,pbAgreementHandle);
}
DWORD GM_SKF_GenerateAgreementDataAndKeyWithECC(HANDLE hcontainer,
												ULONG ulAlgId,
												ECCPUBLICKEYBLOB *eccpublickeyblob,
												ECCPUBLICKEYBLOB *pTempECCPubKeyBlob,
												ECCPUBLICKEYBLOB *pTempECCPubKeyBlobForSponsor,
												BYTE *pbIDforSponsor,
												ULONG ulIdLen,
												BYTE *pbID,
												ULONG ulSponsorIdLen,
												HANDLE *pbKeyHandle)//产生协商数据并计算会话密钥
{
	return m_pkiServerApi.SKF_GenerateAgreementDataAndKeyWithECC(hcontainer,
																 ulAlgId,
																 eccpublickeyblob,
																 pTempECCPubKeyBlob,
																 pTempECCPubKeyBlobForSponsor,
																 pbIDforSponsor,
																 ulIdLen,
																 pbID,
																 ulSponsorIdLen,
																 pbKeyHandle);
}
DWORD GM_SKF_GenerateKeyWithECC(HANDLE pbAgreementHandle,
								ECCPUBLICKEYBLOB *eccpublickeyblob,
								ECCPUBLICKEYBLOB *pTempECCPubKeyBlobForSponsor,
								BYTE *pbIDforSponsor,
								ULONG ulIdLen,
								HANDLE *theKeyHandle)//ECC计算会话密钥
{
	return m_pkiServerApi.SKF_GenerateKeyWithECC(pbAgreementHandle,
												 eccpublickeyblob,
												 pTempECCPubKeyBlobForSponsor,
												 pbIDforSponsor,
												 ulIdLen,
												 theKeyHandle);
}
DWORD GM_SKF_MacInit(HANDLE phKey,BLOCKCIPHERPARAM *MacParam,HANDLE *phMac)//消息鉴别码
{
	return m_pkiServerApi.SKF_MacInit(phKey,MacParam,phMac);
}
DWORD GM_SKF_Mac(HANDLE hMac,
				 BYTE *pbData,
				 ULONG ulDataLen,
				 BYTE *pbMacData,
				 ULONG *pulMacLen)
{
	return m_pkiServerApi.SKF_Mac(hMac,pbData,ulDataLen,pbMacData,pulMacLen);
}
DWORD GM_SKF_EnumFiles(HAPPLICATION hApplication,LPSTR szFileList,ULONG *pulSize)
{
	return m_pkiServerApi.SKF_EnumFiles(hApplication,szFileList,pulSize);
}

DWORD GM_SKF_CreateFile(HAPPLICATION hApplication,
                        LPSTR szFileName,
						ULONG ulFileSize,						 
                        ULONG ulReadRights,
						ULONG ulWriteRights)
{
	return m_pkiServerApi.SKF_CreateFile(hApplication,szFileName,ulFileSize,ulReadRights,ulWriteRights);
}
DWORD GM_SKF_ReadFile(HAPPLICATION  hApplication,
                      LPSTR szFile,
					  ULONG ulOffset,
					  ULONG ulSize,
					  BYTE *pbOutData,
					  ULONG *pulOutLen)
{
	return m_pkiServerApi.SKF_ReadFile(hApplication,szFile,ulOffset,ulSize,pbOutData,pulOutLen);
}
DWORD GM_SKF_GetFileInfo(HAPPLICATION hApplication,LPSTR szFile,FILEATTRIBUTE *pFileInfo)
{
	return m_pkiServerApi.SKF_GetFileInfo(hApplication,szFile,pFileInfo);
}

DWORD GM_SKF_WriteFile(HAPPLICATION hApplication,
                       LPSTR szFile,
					   ULONG ulOffset,
					   BYTE *pbData,
					   ULONG ulSize)
{
	return m_pkiServerApi.SKF_WriteFile(hApplication,szFile,ulOffset,pbData,ulSize);
}
DWORD GM_SKF_DeleteFile(HAPPLICATION hApplication,LPSTR szFileName)
{
	return m_pkiServerApi.SKF_DeleteFile(hApplication,szFileName);
}
DWORD GM_SKF_SetLabel(DEVHANDLE phDev,LPSTR szLabel)
{
	return m_pkiServerApi.SKF_SetLabel(phDev,szLabel);
}
DWORD GM_SKF_CloseHandle(HANDLE hKey)
{
	return m_pkiServerApi.SKF_CloseHandle(hKey);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
DWORD GM_SDF_HashUpdate(void *hSessionHandle,unsigned char *pucData,unsigned int  uiDataLength)
{
	return m_pkiServerApi.SDF_HashUpdate(hSessionHandle,pucData,uiDataLength);
}
DWORD GM_SDF_HashFinal(void *hSessionHandle,unsigned char *pucHash,unsigned int  *puiHashLength)
{
	return m_pkiServerApi.SDF_HashFinal(hSessionHandle,pucHash,puiHashLength);
}

DWORD GM_SDF_CreatKeyInDevice(void *hSessionHandle,unsigned int uiKeyIndex,RSArefPublicKey *pucPublicKey)
{
	int ret = m_pkiServerApi.SDF_CreatEncryptKey(hSessionHandle,uiKeyIndex);
	if(ret !=0)
	{
		printf("SDF_CreatEncryptKey error ret=%d\n",ret);
		return ret;
	}
	#ifdef _56PKISERVER_
		int encPubKeyLen = 0;
		return m_pkiServerApi.SDF_ExportEncPublicKey_RSA(hSessionHandle,uiKeyIndex,(unsigned char *)pucPublicKey,(unsigned int *)&encPubKeyLen);	
	#else
		return m_pkiServerApi.SDF_ExportEncPublicKey_RSA(hSessionHandle,uiKeyIndex,pucPublicKey);
	#endif
	
}


//以下为管理接口
DWORD GM_SDF_ICLogin(void *hSessionHandle,unsigned char * pIcPassword,unsigned int  ICPasswordLen)
{
	return m_pkiServerApi.SDF_ICLogin(hSessionHandle,pIcPassword,ICPasswordLen);
}

DWORD GM_SDF_CreateMasterRSAKey(void *hSessionHandle)
{
	return m_pkiServerApi.SDF_CreateMasterRSAKey(hSessionHandle);
}

DWORD GM_SDF_CreateKPKey(void *hSessionHandle, unsigned int uiAlgID)
{
	return m_pkiServerApi.SDF_CreateKPKey(hSessionHandle,uiAlgID);
}

DWORD GM_SDF_CreateDeviceKey(void *hSessionHandle,unsigned int  uiAlgID,unsigned int  uiKeyBits,unsigned int  uiKeyType,unsigned char *iUserPin,unsigned int  iUserPinLen,unsigned char *iAdminPin,unsigned int  iAdminPinLen)
{
	return m_pkiServerApi.SDF_CreateDeviceKey(hSessionHandle,uiAlgID,uiKeyBits,uiKeyType,iUserPin,iUserPinLen,iAdminPin,iAdminPinLen);
}

DWORD GM_SDF_ResumeImportDeviceKey( void *hSessionHandle,unsigned int  uiKeyType,unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned char * PrivateKeyBuf,unsigned int PrivateKeyLen,unsigned char * PublicKeyBuf,unsigned int PublicKeyLen,unsigned int  uiAlgID,unsigned int  uiKeyBits,unsigned char *iUserPin,unsigned int  iUserPinLen,unsigned char *iAdminPin,unsigned int  iAdminPinLen)
{
	return m_pkiServerApi.SDF_ResumeImportDeviceKey(hSessionHandle,uiKeyType,uiSymmKeyAlgID,uiSymmKeyBuf,uiSymmKeyLen,PrivateKeyBuf,PrivateKeyLen,PublicKeyBuf,PublicKeyLen,uiAlgID,uiKeyBits,iUserPin,iUserPinLen,iAdminPin,iAdminPinLen);
}

DWORD GM_SDF_ExportDeviceKey(void *hSessionHandle,unsigned int  uiKeyType,unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned char * EPrivateKeyBuf,unsigned int *EPrivateKeyLen,unsigned char * PublicKeyBuf,unsigned int *PublicKeyLen,unsigned int  *uiAlgID,unsigned int  *uiKeyBits)
{
	return m_pkiServerApi.SDF_ExportDeviceKey(hSessionHandle,uiKeyType, uiSymmKeyAlgID,uiSymmKeyBuf,uiSymmKeyLen,EPrivateKeyBuf,EPrivateKeyLen, PublicKeyBuf,PublicKeyLen,uiAlgID,uiKeyBits);
}

DWORD GM_SDF_CreateAppKey(void *hSessionHandle,unsigned int  uiKeyIndex,unsigned int  uiAlgID,unsigned int  uiKeyBits,unsigned int  uiKeyType, unsigned char *iUuserPin, unsigned int  iUserPinLen, unsigned char *iAdminPin, unsigned int  iAdminPinLen)
{
	return m_pkiServerApi.SDF_CreateAppKey( hSessionHandle, uiKeyIndex,uiAlgID,uiKeyBits,uiKeyType,iUuserPin, iUserPinLen, iAdminPin, iAdminPinLen);

}

DWORD GM_SDF_ResumeImportAppKey( void *hSessionHandle,unsigned int  uiKeyIndex,unsigned int  uiKeyType,unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned char * PrivateKeyBuf,unsigned int PrivateKeyLen,unsigned char * PublicKeyBuf,unsigned int PublicKeyLen,unsigned int  uiAlgID,unsigned int  uiKeyBits,unsigned char *iUserPin,unsigned int  iUserPinLen,unsigned char *iAdminPin,unsigned int  iAdminPinLen)
{
	return  m_pkiServerApi.SDF_ResumeImportAppKey( hSessionHandle,uiKeyIndex,uiKeyType,uiSymmKeyAlgID,uiSymmKeyBuf,uiSymmKeyLen,PrivateKeyBuf,PrivateKeyLen,PublicKeyBuf,PublicKeyLen,uiAlgID,uiKeyBits,iUserPin,iUserPinLen,iAdminPin,iAdminPinLen);

}
DWORD GM_SDF_ExportAppKey( void *hSessionHandle,unsigned int  uiKeyType,unsigned int  uiKeyIndex,unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned char * ESignPrivateKeyBuf,unsigned int *ESignPrivateKeyLen,unsigned char * SignPublicKeyBuf,unsigned int *SignPublicKeyLen,unsigned int  *uiAlgID,unsigned int  *uiKeyBits)
{
	return  m_pkiServerApi.SDF_ExportAppKey( hSessionHandle,uiKeyType,uiKeyIndex,uiSymmKeyAlgID,uiSymmKeyBuf,uiSymmKeyLen,ESignPrivateKeyBuf,ESignPrivateKeyLen,SignPublicKeyBuf,SignPublicKeyLen,uiAlgID,uiKeyBits);

}
DWORD GM_SDF_DelAppKey(void *hSessionHandle, unsigned int  uiKeyIndex)
{
	return  m_pkiServerApi.SDF_DelAppKey(hSessionHandle, uiKeyIndex);

}
DWORD GM_SDF_CreateKEKey(  void *hSessionHandle,unsigned int  uiKeyIndex,unsigned int uiAlgID)
{
	return m_pkiServerApi.SDF_CreateKEKey(  hSessionHandle,uiKeyIndex,uiAlgID);

}
DWORD GM_SDF_ImportKEKey(void *hSessionHandle,unsigned int  uiKeyIndex, unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned int uiAlgID, unsigned char * uiKEKey,unsigned int uiKEKeyLen)
{
	return m_pkiServerApi.SDF_ImportKEKey(hSessionHandle,uiKeyIndex,uiSymmKeyAlgID,uiSymmKeyBuf, uiSymmKeyLen,uiAlgID,  uiKEKey, uiKEKeyLen);

}
DWORD GM_SDF_ExportKEKey(void *hSessionHandle, unsigned int  uiKeyIndex,unsigned int uiSymmKeyAlgID,unsigned char *uiSymmKeyBuf,unsigned int uiSymmKeyLen,unsigned int *uiAlgID,unsigned char *uiEKEKeyBuf,unsigned int *uiEKEKeyLen)
{
	return m_pkiServerApi.SDF_ExportKEKey(hSessionHandle, uiKeyIndex,uiSymmKeyAlgID,uiSymmKeyBuf, uiSymmKeyLen,uiAlgID,uiEKEKeyBuf,uiEKEKeyLen);

}
DWORD GM_SDF_DelKEKey(void *hSessionHandle, unsigned int  uiKeyIndex)
{
	return m_pkiServerApi.SDF_DelKEKey(hSessionHandle, uiKeyIndex);

}
DWORD GM_SDF_InternalPrivateKeyOperation_RSA_EX(void *hSessionHandle,unsigned int  uiKeyIndex,unsigned int  signKeyType,unsigned char *pucDataInput,unsigned int  uiInputLength,unsigned char *pucDataOutput,unsigned int  *puiOutputLength)
{
	return m_pkiServerApi.SDF_InternalPrivateKeyOperation_RSA_EX(hSessionHandle, uiKeyIndex,signKeyType,pucDataInput,uiInputLength,pucDataOutput,puiOutputLength);

}
DWORD GM_SDF_InternalDecrypt_ECC(void *hSessionHandle,unsigned int  uiISKIndex,unsigned int signKeyType,ECCCipher *pucEncData,unsigned char *pucData,unsigned int  *puiDataLength)
{
	return m_pkiServerApi.SDF_InternalDecrypt_ECC(hSessionHandle, uiISKIndex,signKeyType,pucEncData,pucData,puiDataLength);

}
*/


