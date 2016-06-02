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



		typedef DWORD (DLL* PROC_SKF_ConnectDev)(LPSTR,DEVHANDLE *);//�����豸
		typedef DWORD (DLL* PROC_SKF_GetDevInfo)(DEVHANDLE,DEVINFO *);//��ȡ�豸��Ϣ
		typedef DWORD (DLL* PROC_SKF_DisConnectDev)(DEVHANDLE);//�Ͽ��豸
		typedef DWORD (DLL* PROC_SKF_EnumDev)(BOOL,LPSTR,ULONG *);//ö���豸
		typedef DWORD (DLL* PROC_SKF_GetPINInfo)(HAPPLICATION,ULONG,ULONG *,ULONG *,BOOL *);//��ȡPIN����Ϣ
		typedef DWORD (DLL* PROC_SKF_GenRandom)(DEVHANDLE,BYTE *,ULONG);//���������
		typedef DWORD (DLL* PROC_SKF_GenExtRSAKey)(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//�����ⲿRSA��Կ��
		typedef DWORD (DLL* PROC_SKF_CreateApplication)(DEVHANDLE,LPSTR,LPSTR,DWORD,LPSTR,DWORD,DWORD,HAPPLICATION *);//����Ӧ��
		typedef DWORD (DLL* PROC_SKF_EnumApplication)(DEVHANDLE,LPSTR,ULONG *);//ö��Ӧ��
		typedef DWORD (DLL* PROC_SKF_CreateContainer)(HAPPLICATION,LPSTR,HCONTAINER *);//��������
		typedef DWORD (DLL* PROC_SKF_GenRSAKeyPair)(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *);//����RSAǩ����Կ��
	
		typedef DWORD (DLL* PROC_SKF_VerifyPIN)(HAPPLICATION,ULONG,LPSTR,ULONG *);
		typedef DWORD (DLL* PROC_SKF_SetSymmKey)(DEVHANDLE,BYTE *,ULONG,HANDLE *);//�������ĶԳ���Կ
		typedef DWORD (DLL* PROC_SKF_EncryptInit)(HANDLE,BLOCKCIPHERPARAM);
		typedef DWORD (DLL* PROC_SKF_Encrypt)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//
		typedef DWORD (DLL* PROC_SKF_DevAuth)(DEVHANDLE,BYTE *,ULONG);//�豸��֤
		typedef DWORD (DLL* PROC_SKF_DeleteApplication)(DEVHANDLE,LPSTR);
		typedef DWORD (DLL* PROC_SKF_OpenApplication)(DEVHANDLE,LPSTR,HAPPLICATION *);
		typedef DWORD (DLL* PROC_SKF_OpenContainer)(HAPPLICATION,LPSTR,HCONTAINER *);//������
		typedef DWORD (DLL* PROC_SKF_CreateFile)(HAPPLICATION,LPSTR,ULONG,ULONG,ULONG);// �����ļ�
		typedef DWORD (DLL* PROC_SKF_EnumFiles)(HAPPLICATION,LPSTR,ULONG *);//ö���ļ�
		typedef DWORD (DLL* PROC_SKF_WriteFile)(HAPPLICATION,LPSTR,ULONG,BYTE *,ULONG);//д�ļ�
		typedef DWORD (DLL* PROC_SKF_ReadFile)(HAPPLICATION,LPSTR,ULONG,ULONG,BYTE *,ULONG *);//���ļ�
		typedef DWORD (DLL* PROC_SKF_ChangePIN)(HAPPLICATION,ULONG,LPSTR,LPSTR,ULONG *);//�޸�pin��
		typedef DWORD (DLL* PROC_SKF_GenECCKeyPair)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *);//����ECCǩ����Կ��
		typedef DWORD (DLL* PROC_SKF_ECCSignData)(HCONTAINER,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC����ǩ��
		typedef DWORD (DLL* PROC_SKF_ECCVerify)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC������ǩ
		typedef DWORD (DLL* PROC_SKF_DigestInit)(DEVHANDLE,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//�Ӵճ�ʼ��
		typedef DWORD (DLL* PROC_SKF_ExportPublicKey)(HCONTAINER,BOOL,BYTE *,ULONG *);//������Կ
		typedef DWORD (DLL* PROC_SKF_Digest)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_DigestUpdate)(HANDLE,BYTE *,ULONG);
		typedef DWORD (DLL* PROC_SKF_DigestFinal)(HANDLE,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_RSASignData)(HCONTAINER,BYTE *,ULONG,BYTE *,ULONG *);//RSAǩ��
		typedef DWORD (DLL* PROC_SKF_RSAVerify)(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG);//RSA��ǩ
		typedef DWORD (DLL* PROC_SKF_ClearSecureState)(HAPPLICATION);//�����½״̬
		typedef DWORD (DLL* PROC_SKF_CloseApplication)(HAPPLICATION);//�ر�Ӧ��
		typedef DWORD (DLL* PROC_SKF_GenExtRSAKey)(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//����RSA˽Կ
		typedef DWORD (DLL* PROC_SKF_ExtRSAPubKeyOperation)(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA������Կ����
		typedef DWORD (DLL* PROC_SKF_ExtRSAPriKeyOperation)(DEVHANDLE,RSAPRIVATEKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA����˽Կ����
		typedef DWORD (DLL* PROC_SKF_DecryptInit)(HANDLE,BLOCKCIPHERPARAM);//���ܳ�ʼ��
		typedef DWORD (DLL* PROC_SKF_Decrypt)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//����
		typedef DWORD (DLL* PROC_SKF_ImportRSAKeyPair)(HCONTAINER,ULONG,BYTE *,ULONG,BYTE *,ULONG);//����RSA������Կ��
		typedef DWORD (DLL* PROC_SKF_EnumContainer)(HAPPLICATION,LPSTR,ULONG *);
		typedef DWORD (DLL* PROC_SKF_ImportCertificate)(HCONTAINER,BOOL,BYTE *,ULONG);//��������֤��
		typedef DWORD (DLL* PROC_SKF_ExportCertificate)(HCONTAINER,BOOL,BYTE *,ULONG *);//��������֤��
		typedef DWORD (DLL* PROC_SKF_ExtECCEncrypt)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCCIPHERBLOB);//ECC������Կ����
		typedef DWORD (DLL* PROC_SKF_ImportECCKeyPair)(HCONTAINER,PENVELOPEDKEYBLOB);//����ECC������Կ��
		typedef DWORD (DLL* PROC_SKF_ExtECCDecrypt)(DEVHANDLE,ECCPRIVATEKEYBLOB *,PECCCIPHERBLOB,BYTE *,ULONG *);//ECC����˽Կ����
		typedef DWORD (DLL* PROC_SKF_ImportSessionKey)(HCONTAINER,ULONG,BYTE *,ULONG,HANDLE *);//����Ự��Կ
		typedef DWORD (DLL* PROC_SKF_EncryptUpdate)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//�������ݼ���-encryptupdate
		typedef DWORD (DLL* PROC_SKF_EncryptFinal)(HANDLE,BYTE *,ULONG *);//����������� 
		typedef DWORD (DLL* PROC_SKF_DecryptUpdate)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//�������ݽ���
		typedef DWORD (DLL* PROC_SKF_DecryptFinal)(HANDLE,BYTE *,ULONG *);//�����������
		typedef DWORD (DLL* PROC_SKF_RSAExportSessionKey)(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *,BYTE *,ULONG *,HANDLE *);//RSA�����������Ự��Կ
		typedef DWORD (DLL* PROC_SKF_ECCExportSessionKey)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,PECCCIPHERBLOB,HANDLE *);//ECC�����������Ự��Կ
		typedef DWORD (DLL* PROC_SKF_ExtECCSign)(DEVHANDLE,ECCPRIVATEKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC����˽Կǩ��
		typedef DWORD (DLL* PROC_SKF_ExtECCVerify)(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC������Կ��ǩ
		typedef DWORD (DLL* PROC_SKF_GenerateAgreementDataWithECC)(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC������ԿЭ�̲���
		typedef DWORD (DLL* PROC_SKF_GenerateAgreementDataAndKeyWithECC)(HANDLE,ULONG,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG,HANDLE *);//����Э�����ݲ�����Ự��Կ
		typedef DWORD (DLL* PROC_SKF_GenerateKeyWithECC)(HANDLE,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC����Ự��Կ
		typedef DWORD (DLL* PROC_SKF_MacInit)(HANDLE,BLOCKCIPHERPARAM *, HANDLE *);//��Ϣ������
		typedef DWORD (DLL* PROC_SKF_Mac)(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
		typedef DWORD (DLL* PROC_SKF_MacUpdate)(HANDLE,BYTE *,ULONG);
		typedef DWORD (DLL* PROC_SKF_MacFinal)(HANDLE,BYTE *,ULONG *); 
		typedef DWORD (DLL* PROC_SKF_DeleteFile)(HAPPLICATION,LPSTR);//ɾ���ļ�
		typedef DWORD (DLL* PROC_SKF_DeleteContainer)(HAPPLICATION,LPSTR);//ɾ���ļ�
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
DWORD GM_SKF_ConnectDev(LPSTR,DEVHANDLE *);//�����豸
DWORD GM_SKF_GetDevInfo(DEVHANDLE,DEVINFO *) ;
DWORD GM_SKF_DisConnectDev(DEVHANDLE);
DWORD GM_SKF_EnumDev(BOOL,LPSTR,ULONG *);
DWORD GM_SKF_GetPINInfo(HAPPLICATION,ULONG,ULONG *,ULONG *,BOOL *) ;
DWORD GM_SKF_GenRandom(DEVHANDLE,BYTE *,ULONG);
DWORD GM_SKF_GenExtRSAKey(DEVHANDLE,ULONG,RSAPRIVATEKEYBLOB *);//�����ⲿRSA��Կ��
DWORD GM_SKF_CreateApplication(DEVHANDLE,LPSTR,LPSTR,DWORD,LPSTR,DWORD,DWORD,HAPPLICATION *);//����Ӧ��
DWORD GM_SKF_EnumApplication(DEVHANDLE,LPSTR,ULONG *);
DWORD GM_SKF_CreateContainer(HAPPLICATION,LPSTR,HCONTAINER *);//��������
DWORD GM_SKF_GetContainerType(HAPPLICATION,ULONG *);//��������
ULONG GM_SKF_CloseContainer(HCONTAINER hContainer);
DWORD GM_SKF_GenRSAKeyPair(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *);//����RSAǩ����Կ��
DWORD GM_SKF_VerifyPIN(HAPPLICATION,ULONG,LPSTR,ULONG *);
DWORD GM_SKF_SetSymmKey(DEVHANDLE,BYTE *,ULONG,HANDLE *);//�������ĶԳ���Կ
DWORD GM_SKF_EncryptInit(HANDLE,BLOCKCIPHERPARAM);
DWORD GM_SKF_Encrypt(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_DevAuth(DEVHANDLE,BYTE *,ULONG);//�豸��֤
DWORD GM_SKF_DeleteApplication(DEVHANDLE,LPSTR);
DWORD GM_SKF_OpenApplication(DEVHANDLE,LPSTR,HAPPLICATION *);
DWORD GM_SKF_OpenContainer(HAPPLICATION,LPSTR,HCONTAINER *);//������
DWORD GM_SKF_CreateFile(HAPPLICATION,LPSTR,ULONG,ULONG,ULONG);// �����ļ�
DWORD GM_SKF_EnumFiles(HAPPLICATION,LPSTR,ULONG *);//ö���ļ�
DWORD GM_SKF_WriteFile(HAPPLICATION,LPSTR,ULONG,BYTE *,ULONG);//д�ļ�
DWORD GM_SKF_ReadFile(HAPPLICATION,LPSTR,ULONG,ULONG,BYTE *,ULONG *);//���ļ�
DWORD GM_SKF_ChangePIN(HAPPLICATION,ULONG,LPSTR,LPSTR,ULONG *);//�޸�pin��
DWORD GM_SKF_GenECCKeyPair(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *);//����ECCǩ����Կ��
DWORD GM_SKF_ECCSignData(HCONTAINER,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC����ǩ��
DWORD GM_SKF_ECCVerify(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC������ǩ
DWORD GM_SKF_DigestInit(DEVHANDLE,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//�Ӵճ�ʼ��
DWORD GM_SKF_ExportPublicKey(HCONTAINER,BOOL,BYTE *,ULONG *);//������Կ
DWORD GM_SKF_Digest(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_DigestUpdate(HANDLE,BYTE *,ULONG);
DWORD GM_SKF_DigestFinal(HANDLE,BYTE *,ULONG *);
DWORD GM_SKF_RSASignData(HCONTAINER,BYTE *,ULONG,BYTE *,ULONG *);//RSAǩ��
DWORD GM_SKF_RSAVerify(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG);//RSA��ǩ
DWORD GM_SKF_ClearSecureState(HAPPLICATION);//�����½״̬
DWORD GM_SKF_CloseApplication(HAPPLICATION);//�ر�Ӧ��
DWORD GM_SKF_ExtRSAPubKeyOperation(DEVHANDLE,RSAPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA������Կ����
DWORD GM_SKF_ExtRSAPriKeyOperation(DEVHANDLE,RSAPRIVATEKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG *);//RSA����˽Կ����
DWORD GM_SKF_DecryptInit(HANDLE,BLOCKCIPHERPARAM);//���ܳ�ʼ��
DWORD GM_SKF_Decrypt(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//����
DWORD GM_SKF_ImportRSAKeyPair(HCONTAINER,ULONG,BYTE *,ULONG,BYTE *,ULONG);//����RSA������Կ��
DWORD GM_SKF_EnumContainer(HAPPLICATION,LPSTR,ULONG *);
DWORD GM_SKF_ImportCertificate(HCONTAINER,BOOL,BYTE *,ULONG);//��������֤��
DWORD GM_SKF_ExportCertificate(HCONTAINER,BOOL,BYTE *,ULONG *);//��������֤��
DWORD GM_SKF_ExtECCEncrypt(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCCIPHERBLOB);//ECC������Կ����
DWORD GM_SKF_ImportECCKeyPair(HCONTAINER,PENVELOPEDKEYBLOB);//����ECC������Կ��
DWORD GM_SKF_ExtECCDecrypt(DEVHANDLE,ECCPRIVATEKEYBLOB *,PECCCIPHERBLOB,BYTE *,ULONG *);//ECC����˽Կ����
DWORD GM_SKF_ImportSessionKey(HCONTAINER,ULONG,BYTE *,ULONG,HANDLE *);//����Ự��Կ
DWORD GM_SKF_EncryptUpdate(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//�������ݼ���-encryptupdate
DWORD GM_SKF_EncryptFinal(HANDLE,BYTE *,ULONG *);//����������� 
DWORD GM_SKF_DecryptUpdate(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);//�������ݽ���
DWORD GM_SKF_DecryptFinal(HANDLE,BYTE *,ULONG *);//�����������
DWORD GM_SKF_RSAExportSessionKey(HCONTAINER,ULONG,RSAPUBLICKEYBLOB *,BYTE *,ULONG *,HANDLE *);//RSA�����������Ự��Կ
DWORD GM_SKF_ECCExportSessionKey(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,PECCCIPHERBLOB,HANDLE *);//ECC�����������Ự��Կ
DWORD GM_SKF_ExtECCSign(DEVHANDLE,ECCPRIVATEKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC����˽Կǩ��
DWORD GM_SKF_ExtECCVerify(DEVHANDLE,ECCPUBLICKEYBLOB *,BYTE *,ULONG,PECCSIGNATUREBLOB);//ECC������Կ��ǩ
DWORD GM_SKF_GenerateAgreementDataWithECC(HCONTAINER,ULONG,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC������ԿЭ�̲���
DWORD GM_SKF_GenerateAgreementDataAndKeyWithECC(HANDLE,ULONG,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,BYTE *,ULONG,HANDLE *);//����Э�����ݲ�����Ự��Կ
DWORD GM_SKF_GenerateKeyWithECC(HANDLE,ECCPUBLICKEYBLOB *,ECCPUBLICKEYBLOB *,BYTE *,ULONG,HANDLE *);//ECC����Ự��Կ
DWORD GM_SKF_MacInit(HANDLE,BLOCKCIPHERPARAM *, HANDLE *);//��Ϣ������
DWORD GM_SKF_Mac(HANDLE,BYTE *,ULONG,BYTE *,ULONG *);
DWORD GM_SKF_MacUpdate(HANDLE,BYTE *,ULONG);
DWORD GM_SKF_MacFinal(HANDLE,BYTE *,ULONG *); 
DWORD GM_SKF_DeleteFile(HAPPLICATION,LPSTR); 
DWORD GM_SKF_DeleteContainer(HAPPLICATION,LPSTR);
DWORD GM_SKF_SetLabel(DEVHANDLE,LPSTR);
DWORD GM_SKF_CloseHandle(HANDLE);

#endif