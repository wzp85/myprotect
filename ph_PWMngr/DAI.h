#ifndef _PKISERVER_H_
#define _PKISERVER_H_

#include <Windows.h>
#include <WinCrypt.h>
#include "stdio.h"
#include "DAIDef.h"

#include "SmartCTCAPI.h"

#define DLL   __stdcall
//#define DLL   
//typedef  DWORD (DLL *PROC_SDF_OpenSession)(void *hDeviceHandle,void **phSessionHandle);
//typedef  DWORD (DLL *PROC_SDF_ExternalPublicKeyOperation_RSA)(void *hSessionHandle, RSArefPublicKey *pucPublicKey,unsigned char *pucDataInput,unsigned int  uiInputLength,unsigned char *pucDataOutput,unsigned int  *puiOutputLength);



		typedef DWORD (DLL* PROC_SKF_ConnectDev)(LPSTR,DEVHANDLE *);//连接设备
		typedef DWORD (DLL* PROC_SKF_GetDevInfo)(DEVHANDLE,DEVINFO *);//获取设备信息
		typedef DWORD (DLL* PROC_SKF_DisConnectDev)(DEVHANDLE);//断开设备
		typedef DWORD (DLL* PROC_SKF_EnumDev)(BOOL,LPSTR,ULONG *);//枚举设备
		typedef DWORD (DLL* PROC_SKF_GetPINInfo)(HAPPLICATION,ULONG,ULONG *,ULONG *,BOOL *);//获取PIN码信息
		typedef DWORD (DLL* PROC_SKF_GenRandom)(DEVHANDLE,BYTE *,ULONG);//生成随机数
		typedef DWORD (DLL* PROC_SKF_GenExtRSAKey)(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//生成外部RSA密钥对
		typedef DWORD (DLL* PROC_SKF_CreateApplication)(DEVHANDLE,LPSTR,LPSTR,DWORD,LPSTR,DWORD,DWORD,HAPPLICATION *);//创建应用
		typedef DWORD (DLL* PROC_SKF_EnumApplication)(DEVHANDLE,LPSTR,ULONG *);//枚举应用
		typedef DWORD (DLL* PROC_SKF_CreateContainer)(HAPPLICATION,LPSTR,HCONTAINER *);//创建容器
		typedef DWORD (DLL* PROC_SKF_GenRSAKeyPair)(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *);//生成RSA签名密钥对
	
		typedef DWORD (DLL* PROC_SKF_VerifyPIN)(HAPPLICATION,ULONG,LPSTR,ULONG *);
		typedef DWORD (DLL* PROC_SKF_SetSymmKey)(DEVHANDLE,BYTE *,ULONG,HANDLE *);//设置明文对称密钥
		typedef DWORD (DLL* PROC_SKF_EncryptInit)(HANDLE,BLOCKCIPHERPARAM);
		typedef DWORD (DLL* PROC_SKF_Encrypt)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//
		typedef DWORD (DLL* PROC_SKF_DevAuth)(DEVHANDLE,BYTE *,ULONG);//设备认证
		typedef DWORD (DLL* PROC_SKF_DeleteApplication)(DEVHANDLE,LPSTR);
		typedef DWORD (DLL* PROC_SKF_OpenApplication)(DEVHANDLE,LPSTR,HAPPLICATION *);
		typedef DWORD (DLL* PROC_SKF_OpenContainer)(HAPPLICATION,LPSTR,HCONTAINER *);//打开容器
		typedef DWORD (DLL* PROC_SKF_CreateFile)(HAPPLICATION,LPSTR,ULONG,ULONG,ULONG);// 创建文件
		typedef DWORD (DLL* PROC_SKF_EnumFiles)(HAPPLICATION,LPSTR,ULONG *);//枚举文件
		typedef DWORD (DLL* PROC_SKF_WriteFile)(HAPPLICATION,LPSTR,ULONG,BYTE *,ULONG);//写文件
		typedef DWORD (DLL* PROC_SKF_ReadFile)(HAPPLICATION,LPSTR,ULONG,ULONG,BYTE *,ULONG *);//读文件
		typedef DWORD (DLL* PROC_SKF_ChangePIN)(HAPPLICATION,ULONG,LPSTR,LPSTR,ULONG *);//修改pin码
		typedef DWORD (DLL* PROC_SKF_GenECCKeyPair)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *);//生成ECC签名密钥对
		typedef DWORD (DLL* PROC_SKF_ECCSignData)(HCONTAINER,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC数字签名
		typedef DWORD (DLL* PROC_SKF_ECCVerify)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC数字验签
		typedef DWORD (DLL* PROC_SKF_DigestInit)(DEVHANDLE,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//杂凑初始化
		typedef DWORD (DLL* PROC_SKF_ExportPublicKey)(HCONTAINER,BOOL,BYTE *,ULONG *);//导出公钥
		typedef DWORD (DLL* PROC_SKF_Digest)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_DigestUpdate)(HANDLE,BYTE *,ULONG);
		typedef DWORD (DLL* PROC_SKF_DigestFinal)(HANDLE,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_RSASignData)(HCONTAINER,BYTE *,ULONG,BYTE *,ULONG *);//RSA签名
		typedef DWORD (DLL* PROC_SKF_RSAVerify)(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG);//RSA验签
		typedef DWORD (DLL* PROC_SKF_ClearSecureState)(HAPPLICATION);//清楚登陆状态
		typedef DWORD (DLL* PROC_SKF_CloseApplication)(HAPPLICATION);//关闭应用
		typedef DWORD (DLL* PROC_SKF_GenExtRSAKey)(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//生成RSA私钥
		typedef DWORD (DLL* PROC_SKF_ExtRSAPubKeyOperation)(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA外来公钥运算
		typedef DWORD (DLL* PROC_SKF_ExtRSAPriKeyOperation)(DEVHANDLE,RSAPRIVATEKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA外来私钥运算
		typedef DWORD (DLL* PROC_SKF_DecryptInit)(HANDLE,BLOCKCIPHERPARAM);//解密初始化
		typedef DWORD (DLL* PROC_SKF_Decrypt)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//解密
		typedef DWORD (DLL* PROC_SKF_ImportRSAKeyPair)(HCONTAINER,ULONG,BYTE *,ULONG,BYTE *,ULONG);//导入RSA加密密钥对
		typedef DWORD (DLL* PROC_SKF_EnumContainer)(HAPPLICATION,LPSTR,ULONG *);
		typedef DWORD (DLL* PROC_SKF_ImportCertificate)(HCONTAINER,BOOL,BYTE *,ULONG);//导入数字证书
		typedef DWORD (DLL* PROC_SKF_ExportCertificate)(HCONTAINER,BOOL,BYTE *,ULONG *);//导出数字证书
		typedef DWORD (DLL* PROC_SKF_ExtECCEncrypt)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCCIPHERBLOB);//ECC外来公钥加密
		typedef DWORD (DLL* PROC_SKF_ImportECCKeyPair)(HCONTAINER,PENVELOPEDKEYBLOB);//导入ECC加密密钥对
		typedef DWORD (DLL* PROC_SKF_ExtECCDecrypt)(DEVHANDLE,ECCPRIVATEKEYBLOB *,PECCCIPHERBLOB,BYTE *,ULONG *);//ECC外来私钥解密
		typedef DWORD (DLL* PROC_SKF_ImportSessionKey)(HCONTAINER,ULONG,BYTE *,ULONG,HANDLE *);//导入会话密钥
		typedef DWORD (DLL* PROC_SKF_EncryptUpdate)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//多组数据加密-encryptupdate
		typedef DWORD (DLL* PROC_SKF_EncryptFinal)(HANDLE,BYTE *,ULONG *);//结束多组加密 
		typedef DWORD (DLL* PROC_SKF_DecryptUpdate)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//多组数据解密
		typedef DWORD (DLL* PROC_SKF_DecryptFinal)(HANDLE,BYTE *,ULONG *);//结束多组解密
		typedef DWORD (DLL* PROC_SKF_RSAExportSessionKey)(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *,BYTE *,ULONG *,HANDLE *);//RSA生产并导出会话密钥
		typedef DWORD (DLL* PROC_SKF_ECCExportSessionKey)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,PECCCIPHERBLOB,HANDLE *);//ECC生产并导出会话密钥
		typedef DWORD (DLL* PROC_SKF_ExtECCSign)(DEVHANDLE,ECCPRIVATEKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC外来私钥签名
		typedef DWORD (DLL* PROC_SKF_ExtECCVerify)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC外来公钥验签
		typedef DWORD (DLL* PROC_SKF_GenerateAgreementDataWithECC)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC生成密钥协商参数
		typedef DWORD (DLL* PROC_SKF_GenerateAgreementDataAndKeyWithECC)(HANDLE,ULONG,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG,HANDLE *);//产生协商数据并计算会话密钥
		typedef DWORD (DLL* PROC_SKF_GenerateKeyWithECC)(HANDLE,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC计算会话密钥
		typedef DWORD (DLL* PROC_SKF_MacInit)(HANDLE,BLOCKCIPHERPARAM *, HANDLE *);//消息鉴别码
		typedef DWORD (DLL* PROC_SKF_Mac)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_MacUpdate)(HANDLE,BYTE *,ULONG);
		typedef DWORD (DLL* PROC_SKF_MacFinal)(HANDLE,BYTE *,ULONG *); 
		typedef DWORD (DLL* PROC_SKF_DeleteFile)(HAPPLICATION,LPSTR);//删除文件
		typedef DWORD (DLL* PROC_SKF_DeleteContainer)(HAPPLICATION,LPSTR);//删除文件
		typedef DWORD (DLL* PROC_SKF_GetFileInfo)(HAPPLICATION hApplication,LPSTR szFile,FILEATTRIBUTE *pFileInfo);
		typedef DWORD (DLL* PROC_SKF_UnblockPIN)(HAPPLICATION hApplication,LPSTR szAdminPIN,LPSTR szNewUserPIN,ULONG *pulRetryCount);
		typedef DWORD (DLL* PROC_SKF_SetLabel)(DEVHANDLE hDev, LPSTR szLabel);
		typedef DWORD (DLL* PROC_SKF_CloseHandle)(HANDLE );
		typedef DWORD (DLL* PROC_SKF_GetContainerType)(HCONTAINER,ULONG *);
		typedef DWORD (DLL* PROC_SKF_CloseContainer) (HCONTAINER ); 

typedef struct PKISERVERAPI 
{
//	PROC_SDF_OpenDevice									SDF_OpenDevice                        ;
	PROC_SKF_ConnectDev									SKF_ConnectDev;
	PROC_SKF_GetDevInfo									SKF_GetDevInfo;
	PROC_SKF_DisConnectDev								SKF_DisConnectDev;
	PROC_SKF_EnumDev									SKF_EnumDev;
	PROC_SKF_GetPINInfo									SKF_GetPINInfo;
	PROC_SKF_GenRandom									SKF_GenRandom;
//	PROC_SKF_GenExtRSAKey								SKF_GenExtRSAKey;
	PROC_SKF_CreateApplication							SKF_CreateApplication;
	PROC_SKF_EnumApplication							SKF_EnumApplication;
	PROC_SKF_CreateContainer							SKF_CreateContainer;
	PROC_SKF_GetContainerType							SKF_GetContainerType;
	PROC_SKF_GenRSAKeyPair								SKF_GenRSAKeyPair;
	PROC_SKF_VerifyPIN									SKF_VerifyPIN;
	PROC_SKF_SetSymmKey									SKF_SetSymmKey;
	PROC_SKF_EncryptInit								SKF_EncryptInit;
	PROC_SKF_Encrypt									SKF_Encrypt;
	PROC_SKF_DevAuth									SKF_DevAuth;
	PROC_SKF_DeleteApplication							SKF_DeleteApplication;
	PROC_SKF_OpenApplication							SKF_OpenApplication;
	PROC_SKF_OpenContainer								SKF_OpenContainer;
	PROC_SKF_CloseContainer								SKF_CloseContainer;
	PROC_SKF_CreateFile									SKF_CreateFile;
	PROC_SKF_EnumFiles									SKF_EnumFiles;
	PROC_SKF_WriteFile									SKF_WriteFile;
	PROC_SKF_ReadFile									SKF_ReadFile;
	PROC_SKF_ChangePIN									SKF_ChangePIN;
	PROC_SKF_GenECCKeyPair								SKF_GenECCKeyPair;
	PROC_SKF_ECCSignData								SKF_ECCSignData;
	PROC_SKF_ECCVerify									SKF_ECCVerify;
	PROC_SKF_DigestInit									SKF_DigestInit;
	PROC_SKF_ExportPublicKey							SKF_ExportPublicKey;
	PROC_SKF_Digest										SKF_Digest;
	PROC_SKF_DigestUpdate								SKF_DigestUpdate;
	PROC_SKF_DigestFinal								SKF_DigestFinal;
	PROC_SKF_RSASignData								SKF_RSASignData;
	PROC_SKF_RSAVerify									SKF_RSAVerify;
	PROC_SKF_ClearSecureState							SKF_ClearSecureState;
	PROC_SKF_CloseApplication							SKF_CloseApplication;
	PROC_SKF_GenExtRSAKey								SKF_GenExtRSAKey;
	PROC_SKF_ExtRSAPubKeyOperation						SKF_ExtRSAPubKeyOperation;
	PROC_SKF_ExtRSAPriKeyOperation						SKF_ExtRSAPriKeyOperation;
	PROC_SKF_DecryptInit								SKF_DecryptInit;
	PROC_SKF_Decrypt									SKF_Decrypt;
	PROC_SKF_ImportRSAKeyPair							SKF_ImportRSAKeyPair;
	PROC_SKF_EnumContainer								SKF_EnumContainer;
	PROC_SKF_ImportCertificate							SKF_ImportCertificate;
	PROC_SKF_ExportCertificate							SKF_ExportCertificate;
	PROC_SKF_ExtECCEncrypt								SKF_ExtECCEncrypt;
	PROC_SKF_ExtECCDecrypt								SKF_ExtECCDecrypt;
	PROC_SKF_ImportSessionKey							SKF_ImportSessionKey;
	PROC_SKF_EncryptUpdate								SKF_EncryptUpdate;
	PROC_SKF_EncryptFinal								SKF_EncryptFinal;
	PROC_SKF_DecryptUpdate								SKF_DecryptUpdate;
	PROC_SKF_DecryptFinal								SKF_DecryptFinal;
	PROC_SKF_RSAExportSessionKey						SKF_RSAExportSessionKey;
	PROC_SKF_ECCExportSessionKey						SKF_ECCExportSessionKey;
	PROC_SKF_ExtECCSign									SKF_ExtECCSign;
	PROC_SKF_ExtECCVerify								SKF_ExtECCVerify;
	PROC_SKF_GenerateAgreementDataWithECC				SKF_GenerateAgreementDataWithECC;
	PROC_SKF_GenerateAgreementDataAndKeyWithECC			SKF_GenerateAgreementDataAndKeyWithECC;
	PROC_SKF_GenerateKeyWithECC							SKF_GenerateKeyWithECC;
	PROC_SKF_MacInit									SKF_MacInit;
	PROC_SKF_Mac										SKF_Mac;
	PROC_SKF_MacUpdate									SKF_MacUpdate;
	PROC_SKF_MacFinal									SKF_MacFinal;
	PROC_SKF_ImportECCKeyPair							SKF_ImportECCKeyPair;
	PROC_SKF_DeleteFile									SKF_DeleteFile;
	PROC_SKF_DeleteContainer							SKF_DeleteContainer;
	PROC_SKF_GetFileInfo                                SKF_GetFileInfo;
	PROC_SKF_UnblockPIN									SKF_UnblockPIN;
	PROC_SKF_SetLabel                                   SKF_SetLabel;
	PROC_SKF_CloseHandle                                SKF_CloseHandle;
} PkiServerApi;

  

int	LoadPkiServerDll(char* dllName);
int FreePkiServerDll();
//DWORD GM_SDF_OpenDevice(void **phDeviceHandle) ;
;
DWORD GM_SKF_UnblockPIN(HAPPLICATION hApplication,LPSTR szAdminPIN,LPSTR szNewUserPIN,ULONG *pulRetryCount);
DWORD GM_SKF_GetFileInfo(HAPPLICATION hApplication,LPSTR szFile,FILEATTRIBUTE *pFileInfo);
DWORD GM_SKF_ConnectDev(LPSTR,DEVHANDLE *);//连接设备
DWORD GM_SKF_GetDevInfo(DEVHANDLE,DEVINFO *) ;
DWORD GM_SKF_DisConnectDev(DEVHANDLE);
DWORD GM_SKF_EnumDev(BOOL,LPSTR,ULONG *);
DWORD GM_SKF_GetPINInfo(HAPPLICATION,ULONG,ULONG *,ULONG *,BOOL *) ;
DWORD GM_SKF_GenRandom(DEVHANDLE,BYTE *,ULONG);
DWORD GM_SKF_GenExtRSAKey(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//生成外部RSA密钥对
DWORD GM_SKF_CreateApplication(DEVHANDLE,LPSTR,LPSTR,DWORD,LPSTR,DWORD,DWORD,HAPPLICATION *);//创建应用
DWORD GM_SKF_EnumApplication(DEVHANDLE,LPSTR,ULONG *);
DWORD GM_SKF_CreateContainer(HAPPLICATION,LPSTR,HCONTAINER *);//创建容器
DWORD GM_SKF_GetContainerType(HAPPLICATION,ULONG *);//创建容器
ULONG GM_SKF_CloseContainer(HCONTAINER hContainer);
DWORD GM_SKF_GenRSAKeyPair(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *);//生成RSA签名密钥对
DWORD GM_SKF_VerifyPIN(HAPPLICATION,ULONG,LPSTR,ULONG *);
DWORD GM_SKF_SetSymmKey(DEVHANDLE,BYTE *,ULONG,HANDLE *);//设置明文对称密钥
DWORD GM_SKF_EncryptInit(HANDLE,BLOCKCIPHERPARAM);
DWORD GM_SKF_Encrypt(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_DevAuth(DEVHANDLE,BYTE *,ULONG);//设备认证
DWORD GM_SKF_DeleteApplication(DEVHANDLE,LPSTR);
DWORD GM_SKF_OpenApplication(DEVHANDLE,LPSTR,HAPPLICATION *);
DWORD GM_SKF_OpenContainer(HAPPLICATION,LPSTR,HCONTAINER *);//打开容器
DWORD GM_SKF_CreateFile(HAPPLICATION,LPSTR,ULONG,ULONG,ULONG);// 创建文件
DWORD GM_SKF_EnumFiles(HAPPLICATION,LPSTR,ULONG *);//枚举文件
DWORD GM_SKF_WriteFile(HAPPLICATION,LPSTR,ULONG,BYTE *,ULONG);//写文件
DWORD GM_SKF_ReadFile(HAPPLICATION,LPSTR,ULONG,ULONG,BYTE *,ULONG *);//读文件
DWORD GM_SKF_ChangePIN(HAPPLICATION,ULONG,LPSTR,LPSTR,ULONG *);//修改pin码
DWORD GM_SKF_GenECCKeyPair(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *);//生成ECC签名密钥对
DWORD GM_SKF_ECCSignData(HCONTAINER,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC数字签名
DWORD GM_SKF_ECCVerify(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC数字验签
DWORD GM_SKF_DigestInit(DEVHANDLE,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//杂凑初始化
DWORD GM_SKF_ExportPublicKey(HCONTAINER,BOOL,BYTE *,ULONG *);//导出公钥
DWORD GM_SKF_Digest(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_DigestUpdate(HANDLE,BYTE *,ULONG);
DWORD GM_SKF_DigestFinal(HANDLE,BYTE *,ULONG *);
DWORD GM_SKF_RSASignData(HCONTAINER,BYTE *,ULONG,BYTE *,ULONG *);//RSA签名
DWORD GM_SKF_RSAVerify(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG);//RSA验签
DWORD GM_SKF_ClearSecureState(HAPPLICATION);//清楚登陆状态
DWORD GM_SKF_CloseApplication(HAPPLICATION);//关闭应用
DWORD GM_SKF_ExtRSAPubKeyOperation(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA外来公钥运算
DWORD GM_SKF_ExtRSAPriKeyOperation(DEVHANDLE,RSAPRIVATEKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA外来私钥运算
DWORD GM_SKF_DecryptInit(HANDLE,BLOCKCIPHERPARAM);//解密初始化
DWORD GM_SKF_Decrypt(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//解密
DWORD GM_SKF_ImportRSAKeyPair(HCONTAINER,ULONG,BYTE *,ULONG,BYTE *,ULONG);//导入RSA加密密钥对
DWORD GM_SKF_EnumContainer(HAPPLICATION,LPSTR,ULONG *);
DWORD GM_SKF_ImportCertificate(HCONTAINER,BOOL,BYTE *,ULONG);//导入数字证书
DWORD GM_SKF_ExportCertificate(HCONTAINER,BOOL,BYTE *,ULONG *);//导出数字证书
DWORD GM_SKF_ExtECCEncrypt(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCCIPHERBLOB);//ECC外来公钥加密
DWORD GM_SKF_ImportECCKeyPair(HCONTAINER,PENVELOPEDKEYBLOB);//导入ECC加密密钥对
DWORD GM_SKF_ExtECCDecrypt(DEVHANDLE,ECCPRIVATEKEYBLOB *,PECCCIPHERBLOB,BYTE *,ULONG *);//ECC外来私钥解密
DWORD GM_SKF_ImportSessionKey(HCONTAINER,ULONG,BYTE *,ULONG,HANDLE *);//导入会话密钥
DWORD GM_SKF_EncryptUpdate(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//多组数据加密-encryptupdate
DWORD GM_SKF_EncryptFinal(HANDLE,BYTE *,ULONG *);//结束多组加密 
DWORD GM_SKF_DecryptUpdate(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//多组数据解密
DWORD GM_SKF_DecryptFinal(HANDLE,BYTE *,ULONG *);//结束多组解密
DWORD GM_SKF_RSAExportSessionKey(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *,BYTE *,ULONG *,HANDLE *);//RSA生产并导出会话密钥
DWORD GM_SKF_ECCExportSessionKey(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,PECCCIPHERBLOB,HANDLE *);//ECC生产并导出会话密钥
DWORD GM_SKF_ExtECCSign(DEVHANDLE,ECCPRIVATEKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC外来私钥签名
DWORD GM_SKF_ExtECCVerify(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC外来公钥验签
DWORD GM_SKF_GenerateAgreementDataWithECC(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC生成密钥协商参数
DWORD GM_SKF_GenerateAgreementDataAndKeyWithECC(HANDLE,ULONG,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG,HANDLE *);//产生协商数据并计算会话密钥
DWORD GM_SKF_GenerateKeyWithECC(HANDLE,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC计算会话密钥
DWORD GM_SKF_MacInit(HANDLE,BLOCKCIPHERPARAM *, HANDLE *);//消息鉴别码
DWORD GM_SKF_Mac(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_MacUpdate(HANDLE,BYTE *,ULONG);
DWORD GM_SKF_MacFinal(HANDLE,BYTE *,ULONG *); 
DWORD GM_SKF_DeleteFile(HAPPLICATION,LPSTR); 
DWORD GM_SKF_DeleteContainer(HAPPLICATION,LPSTR);
DWORD GM_SKF_SetLabel(DEVHANDLE,LPSTR);
DWORD GM_SKF_CloseHandle(HANDLE);

#endif