#ifndef _PHCDSAPI_
#define _PHCDSAPI_
#include "PHCDS_datatype.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 


#ifdef WIN32
	#define TIMEOUT      0
	#define UTIMEOUT     100000
#else
	#define TIMEOUT      0
	#define UTIMEOUT     100000
#endif
/*------------------------------------------------------------*/

#define SGD_RSA			0x00010000	//RSA算法
#define SGD_SM2_1		0x00020100	//椭圆曲线签名算法
#define SGD_SM2_2		0x00020200	//椭圆曲线密钥交换协议
#define SGD_SM2_3		0x00020400	//椭圆曲线加密算法

#define SGD_SM3			0x00000001	//SM3杂凑算法
#define SGD_SHA1		0x00000002	//SHA1杂凑算法
#define SGD_SHA256		0x00000004	//SHA256杂凑算法
#define SGD_MD5			0x00000003

/*------------------------------------------------------------*/

#define SGD_SM1_ECB		0x00000101	//SM1算法ECB加密模式
#define SGD_SM1_CBC		0x00000102	//SM1算法CBC加密模式
#define SGD_SM1_CFB		0x00000104	//SM1算法CFB加密模式
#define SGD_SM1_OFB		0x00000108	//SM1算法OFB加密模式
#define SGD_SM1_MAC		0x00000110	//SM1算法MAC加密模式

#define SGD_SMS4_ECB	0x00000401	//SMS4算法ECB加密模式
#define SGD_SMS4_CBC	0x00000402	//SMS4算法CBC加密模式
#define SGD_SMS4_CFB	0x00000404	//SMS4算法CFB加密模式
#define SGD_SMS4_OFB	0x00000408	//SMS4算法OFB加密模式
#define SGD_SMS4_MAC	0x00000410	//SMS4算法MAC加密模式

#define	SGD_3DES_ECB	0x01000001  //3DES算法ECB加密模式                                                         
#define	SGD_3DES_CBC	0x01000002  //3DES算法CBC加密模式                                                             
#define	SGD_3DES_CFB	0x01000004  //3DES算法CFB加密模式                                                            
#define	SGD_3DES_OFB	0x01000008  //3DES算法OFB加密模式    
#define SGD_3DES_MAC	0x01000010  //3DES算法MAC加密模式    

#define SGD_SSF33_ECB 0x00000201 //SSF33算法ECB加密模式
#define SGD_SSF33_CBC 0x00000202 //SSF33算法CBC加密模式
#define SGD_SSF33_CFB 0x00000204 //SSF33算法CFB加密模式
#define SGD_SSF33_OFB 0x00000208 //SSF33算法OFB加密模式
#define SGD_SSF33_MAC 0x00000210 //SSF33算法MAC加密

/*------------------------------------------------------------*/






/*----------------------SFK层公钥结构-----------------------------*/

#define  MAX_RSA_MODULUS_LEN_km        256         //RSA算法的最大模长
#define  MAX_RSA_EXPONENT_LEN_km       4           //算法指数的最大长度  

typedef  struct Struct_RSAPUBLICKEYBLOB_km
{	
	unsigned int AlgID ;                               //算法标识号

	unsigned int BitLen ;                              //模数的实际位长度  必须是8的整数倍

	unsigned char Modulus[MAX_RSA_MODULUS_LEN_km];          //模数 n=p*q  实际长度是BitLen/8字节

	unsigned char PublicExponent[MAX_RSA_EXPONENT_LEN_km];  //公开密钥 e

}RSAPUBLICKEYBLOB_km, *PRSAPUBLICKEYBLOB_km; 





#define   ECC_MAX_XCOORDINATE_BITS_LEN_km  512//曲线上点的X的坐标
#define   ECC_MAX_YCOORDINATE_BITS_LEN_km  512//曲线上点的Y坐标
#define   ECC_MAX_MODULUS_BITS_LEN_km 512

typedef struct Struct_ECCPUBLICKEYBLOB_km{ 

	unsigned long BitLen; 

	unsigned char XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN_km/8]; 

	unsigned char YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN_km/8]; 

}ECCPUBLICKEYBLOB_km, *PECCPUBLICKEYBLOB_km; 

/*------------------------SFK层公钥结构-------------------------*/



/****************************************设备管理类****************************************/
typedef struct ADMININFO
{
	unsigned int iAdminId;				//管理员标签

	unsigned int uiNameLen;				//管理员名称长度
	unsigned char ucName[32];			//管理员名称

	unsigned int uiTelephoneLen;		//管理员电话号码长度
	unsigned char ucTelephone[16];		//管理员电话号码

	unsigned int iPaperType;			//证件类型

	unsigned int uiPaperNumLen;			//管理员电话号码长度
	unsigned char ucPaperNum[32];		//证件号码

}ADMININFO, *PADMININFO;

typedef struct DEVKEYINFO
{
	unsigned int uiDevNameLen;				//设备名称长度
	unsigned char ucDevName[32];			//设备名称

	unsigned int uiAlgo;					//算法类型

	unsigned int uiIfBak;					//是否已经备份

	unsigned int uiKeyLen;					//设备密钥长度

	unsigned int uiBakTotalKey;				//备份策略中总的Key个数
	unsigned int uiBakChooseKey;			//备份策略中要选择的Key的个数


	unsigned int uiBakTimeLen;				//备份时间的长度
	unsigned char ucBakTime[32];			//备份时间

}DEVKEYINFO, *PDEVKEYINFO;


/****************************************设备管理类****************************************/


int Km_LoginIn (void ** phSessionHandle,char* uiIP,
	unsigned int uiAdminId,unsigned int uiHashAlgo,unsigned int uiSignAlgo,
	unsigned char * pucRandom,unsigned int uiRandomLength,
	unsigned char * pucRandomSign,unsigned int uiRandomSignLength,
	unsigned char * pucDevSign,unsigned int uiDevSignLength);

int Km_LoginOut (void *hSessionHandle);

int Km_CheckInitPasswd(void ** phSessionHandle,char* uiIP,
	unsigned char *ucName, unsigned int uiNameLength,
	unsigned char *ucPasswdHash, unsigned int uiPasswdHashLength,unsigned int *puiInitStatus);

int Km_ModifyInitPasswd (void ** phSessionHandle,char* uiIP,
	unsigned char *ucName,unsigned int uiNameLength,
	unsigned char*ucOldPasswordHash,unsigned int uiOldPasswordHashLength,
	unsigned char *ucNewPasswordHash,unsigned int uiNewPasswordHashLength);

int Km_GenMainKey(void * hSessionHandle);

int Km_GenKeyProKey(void * hSessionHandle,unsigned int iSymmAlgo);

int Km_GenDevKey(void * hSessionHandle,unsigned char * pucDevName,unsigned int uiDevNameLength,
	unsigned int iASymmAlgo,unsigned int uiKeyLen,unsigned char * pucDevKeyPin,unsigned int ucDevKeyPinLength);

int Km_GenAdmin(void * hSessionHandle,ADMININFO* pAdminInfo,
	unsigned int uiAdminType,unsigned int uiAdminNum,
	unsigned char *pucPubKey,unsigned int uiPubKeyLen,
	unsigned char *pucSignValue,unsigned int *puiSignValueLen);

int Km_GetDevKeyInfo (void * hSessionHandle,DEVKEYINFO *pDevKeyInfo);

int Km_DevKeyBackup (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength);

int Km_DevKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucAdminPin, unsigned int uiAdminPinLength, 
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength);

int Km_GenAppKey(void * hSessionHandle, unsigned int uikeyIndex, unsigned int uiAlgo, unsigned int uiKeyLength,
	unsigned char *pucKeyPasswd, unsigned int uiKeyPasswdLength,
	unsigned char *pucAppName, unsigned int uiAppNameLength, unsigned int uiKeyType);

int Km_GenAppKey_SIG(void * hSessionHandle, unsigned int uikeyIndex, unsigned int uiAlgo, unsigned int uiKeyLength,
	unsigned char *pucKeyPasswd, unsigned int uiKeyPasswdLength,unsigned char *pucAppName, unsigned int uiAppNameLength, 
	unsigned int uiKeyType,unsigned char *pucCityName,unsigned int uiCityNameLength,unsigned char *pucCNName,unsigned int uiCNNameLength,
	unsigned char *pucAreaName,unsigned int uiAreaNameLength,unsigned char *pucAtName,unsigned int uiAtNameLength,
	unsigned char *pucEmail,unsigned int uiEmailLength,unsigned char *pucOUValue,unsigned int uiOUValueLength);

int Km_AppKeyModPasswd(void * hSessionHandle, unsigned int uikeyLabel, 
	unsigned char *pucOldKeyPasswd, unsigned int uiOldKeyPasswdLength, 
	unsigned char *pucNewKeyPasswd, unsigned int uiNewKeyPasswdLength);

int Km_AppKeyBackup(void * hSessionHandle, unsigned int uiAlgo,
	unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength,
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength);

int Km_AppKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucAdminPin, unsigned int uiAdminPinLength, 
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength);

int Km_AppKeyDestroy(void * hSessionHandle,unsigned int uiTypeNum,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex);

int Km_AppKeyGetList(void * hSessionHandle,unsigned int uiIsSig, unsigned char * puiKeyList,unsigned int *puiKeyListLen);




int Km_GenKeyEncKey(void * hSessionHandle, unsigned int uikeyLabel, unsigned int uiAlgo, 
	unsigned char *pucEncKeyName, unsigned int uiEncKeyNameLength);

int Km_KeyEncKeyBackup(void * hSessionHandle, unsigned int uiAlgo,
	unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength,
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength);

int Km_KeyEncRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength);

int Km_KeyEncDestroy(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex);

int Km_KeyEncKeyGetList(void * hSessionHandle, unsigned char * puiKeyList,unsigned int *puiKeyListLen);



int Km_DelAdmin(void * phSessionHandle,	unsigned int uiAdminId);

int Km_GetAdminList(void * hSessionHandle, unsigned char * puiAdminList,unsigned int *puiAdminListLen);

int Km_AdminBackup(void * hSessionHandle, unsigned int uiAdminIndexNum,unsigned int *puiAdminIndex,
	unsigned char *pucAdminBak, unsigned int* puiAdminBakLength);

int Km_AdminRecovery(void *hSessionHandle,unsigned char *pucAdminBackup, unsigned int uiAdminBackupLength );



int Km_NetRestart(void * hSessionHandle,unsigned int eth);

int Km_ManagerNetModify(void * hSessionHandle,unsigned char * pucNet,unsigned int uiNetLen);

int Km_AppNetModify(void * hSessionHandle,unsigned char * pucNet,unsigned int uiNetLen);

int Km_GetNetConfig(void * hSessionHandle,unsigned int eth, unsigned char * pucNet,unsigned int *puiNetLen);

int Km_GetDeviceInfo(void * hSessionHandle,DEVICEINFO* pDevInfo);

int	Km_SymmCrypt(void * hSessionHandle,unsigned int oper,unsigned int uiAlgo,unsigned char * pucSymmKey,unsigned int uiSymmKeyLength,
	unsigned char *pucText,unsigned int uiTextLength,unsigned char *pucResault,unsigned int* puiResaultLength);



int Km_Encode( char *src,long int src_len, char *dst);

int Km_Decode(char *src, long int src_len, char *dst);

int Km_Random(unsigned char * random,int len);

int Sig_RootCertAdd(void * hSessionHandle,unsigned char *pucCertName,unsigned int uiCertNameLength,
	unsigned int uiCertIndex,unsigned int uiAlgo,unsigned char *pucAtName,unsigned int uiKeyLength,
	unsigned int uiAtNameLength,unsigned char *pucHost,unsigned int uiHostLength,unsigned char *pucPhone,
	unsigned int uiPhoneLength,unsigned char *pucRtCert,unsigned int uiRtCertLength,
	unsigned char		*pucCertSN, unsigned int        uiCertSNLength);

int Sig_RootCertDel(void * hSessionHandle,unsigned int uiCertIndexNum,unsigned int *puiCertIndex);

int Sig_RootCertUpdate(void *hSessionHandle,unsigned int uiAlgo,unsigned int uiCertIndex,unsigned char *pucCertName,
	unsigned int uiCertNameLength,unsigned char *pucAtName,unsigned int uiAtNameLength,unsigned char *pucHost,unsigned int uiHostLength,
	unsigned char *pucPhone,unsigned int uiPhoneLength);

int Sig_RootCertGetList(void * hSessionHandle,unsigned char * puiKeyList,unsigned int *puiKeyListLen);

int Sig_GenCertRequest(void * hSessionHandle,unsigned int uiSymmAlgo,unsigned int uiHashAlgo,unsigned int uiKeyAlgo,
						unsigned int uiIndexLength,unsigned char *pucIndex,unsigned int uiPasswordLength,unsigned char *pucPassword,
						unsigned int uiRequestLength,unsigned char *pucRequest,unsigned char *pucB64Req,unsigned char *pucReq);
int Sig_GenCertOnline(void * hSessionHandle,unsigned int uiSymmAlgo,unsigned int uiHashAlgo,unsigned int uiKeyAlgo,
						unsigned int uiIndexLength,unsigned char *pucIndex,unsigned int uiPasswordLength,unsigned char *pucPassword,
						unsigned int uiIPAddrLength,unsigned char *pucIPaddr,unsigned int uiPortLength,unsigned char *pucPort,
						unsigned int uiRequestLength,unsigned char *pucRequest);

int Sig_ImportEncCert(void * hSessionHandle,unsigned int uiKeyAlgo,
	unsigned int uiIndexLength,unsigned char *pucIndex,
	unsigned int uiPasswordLength,unsigned char *pucPassword,
	unsigned int uiEncCertLength,unsigned char *pucEncCert,
	unsigned int uiSigCertLength,unsigned char *pucSigCert,
	unsigned int uiEncPubKeyLength,unsigned char *pucEncPubKey, 
	unsigned int uiEncPrivKeyLength,unsigned char *pucEncPrivKey, 
	int encType
	);
int Sig_GetItemAppKeyInfo(void * hSessionHandle,unsigned int uiKeyIndex,unsigned char *pucItem,unsigned int *uiItemLength);

int Sig_CACertAdd(void * hSessionHandle,unsigned int uiRtCertIndex,unsigned int uiRtCertType,unsigned int uiCACertIndex,unsigned int uiAlgo,unsigned int uiKeyLength,unsigned int uiCertIndexLength,
				unsigned char *putCertIndex,unsigned int uiCertNameLength,unsigned char	*pucCertName,unsigned int uiAtNameLength,unsigned char *pucAtName,
				unsigned int uiHostLength,unsigned char *pucHost,unsigned int uiPhoneLength,unsigned char *pucPhone,unsigned int uiCACertLength,
				unsigned char *pucCACert,unsigned int uiTrustChainLength,unsigned char *pucTrustChain,VerifyPriorityStrategy vs);

int Sig_CACertGetList(void * hSessionHandle,unsigned char * puiKeyList,unsigned int *puiKeyListLen);


int Sig_CACertDel(void * hSessionHandle,unsigned int uiCertIndexNum,unsigned int *puiCertIndex);

int Sig_GetCACertVS(void * hSessionHandle,unsigned int uiCertIndex,unsigned char *CACertSerialNum,unsigned int *uiRtCertType,unsigned int *uiRtCertIndex,VerifyPriorityStrategy *vs);

int pkiBase64Decode( PKI_DATA i_inData, PKI_PDATA o_outData );


int Sig_UserCertImport(void * hSessionHandle,unsigned int uiCACertIndex,unsigned int uiAlgid,unsigned int uiKeyLength,unsigned int uiKeyType,unsigned int uiKeyIndex,
					unsigned int uiCertIndexLength,unsigned char *putCertIndex,unsigned int uiCertNameLength,unsigned char	*pucCertName,unsigned int uiAtNameLength,
					unsigned char *pucAtName,unsigned int uiHostLength,unsigned char *pucHost,unsigned int uiPhoneLength,unsigned char *pucPhone,unsigned int uiUsrEncCertLength,
					unsigned char *pucUsrEncCert,unsigned int uiUsrSigCertLength,unsigned char *pucUsrSigCert,unsigned int uiPrivateKeyAccessRightCodeLength,
					unsigned char *pucPrivateKeyAccessRightCode);


int Sig_AppKeyBackup(void * hSessionHandle, unsigned int uiAlgo,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucKeyBackupKey,
					unsigned int uiKeyBackupKeyLength,unsigned char *pucKeyBak, unsigned int* puiKeyBakLength);


int Sig_AppKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,unsigned char *pucAdminPin, unsigned int uiAdminPinLength,unsigned char *pucKeyBackupKey,
					unsigned int uiKeyBackupKeyLength,unsigned char *pucKeyBak, unsigned int uiKeyBakLength);


int Sig_UserCertExport(void * hSessionHandle,unsigned int index,unsigned char *pucSigCert,unsigned int *uiSigCertLength,
						unsigned char *pucEncCert,unsigned int *uiEncCertLegnth);

int Sig_GetLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength,
	unsigned int *uiPubKeyLength,unsigned char *pucPubKey);

int Sig_GetServiceLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength);
int Sig_GetServiceLogSearch(void * hSessionHandle,unsigned int page,unsigned int uiStartTimeLength,unsigned char *pStartTime,unsigned int uiStartEndLength,unsigned char *pStartEnd,unsigned int uilogopKind,
	unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength);


int Sig_ModifyServiceLogXmlFile(void * hSessionHandle,unsigned int logContentType,unsigned int logPolicyType,unsigned int Logtime,unsigned int SLRvalue,	unsigned char * pucURL, unsigned int uiURLLength);

int Sig_CACertExport(void * hSessionHandle,unsigned int uiCertIndex,unsigned int *uiCertLength,unsigned char *pucCert);

int Sig_RTCertBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength);

int Sig_RTCertExport(void * hSessionHandle,unsigned int uiCertIndex,unsigned int *uiCertLength,unsigned char *pucCert);

int Sig_CACertBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength);

int Sig_CACertRecovery(void * hSessionHandle,unsigned int uiCertBakLength,unsigned char *pucCertBak);

int Sig_ServiceLogDel(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned int year,unsigned int month);

int Sig_ServiceLogBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength);

int Sig_ServiceLogRecovery(void * hSessionHandle,unsigned int uiCertBakLength,unsigned char *pucCertBak);

int Sig_MngrLogAuditAll(void * hSessionHandle,unsigned int *uiLogIndexNum,unsigned int *puiLogIndex,unsigned int *uiLogTimeLen,unsigned char *pucLogTime);

int Sig_ManagementLogCOA(void * hSessionHandle,unsigned int uiAuditMold,unsigned int uiOptionLen,unsigned char *pucOption,unsigned int uiOptionTypeLen,
						unsigned char *pucOptionType,unsigned int uiOptionResultLen,unsigned char *pucOptionResult,unsigned int uiStartTimeLen,unsigned char *pucStartTime,
						unsigned int uiEndTimeLen,unsigned char *pucEndTime,unsigned int *auditResultCount,unsigned int *uiReLogTimeLenth,unsigned char *pucReLogTime);
int  PKI_GetXMLCertInfo(void *  hSessionHandle,unsigned int   i_inCertLen,unsigned char * i_inCert, unsigned int *o_certInfoLen,unsigned char * o_certInfo);
int  PKI_CheckCert(void *  sessionHandle,unsigned int   i_inCertLen, unsigned int * i_inCert,unsigned int   i_trustCertLen, unsigned int * i_trustCert,
	unsigned int  i_certsChainLen, unsigned int *  i_certsChain, unsigned int   i_crlLen, unsigned int *  i_crl);


int  Sig_AppCertKeySet(void * hSessionHandle, unsigned int uikeyIndex,unsigned int *uikeyKeyType,unsigned int *uikeyIndex1,unsigned int uiType);

int Sig_NTPAddrSet(void * hSessionHandle, unsigned int *uiAddrLen,unsigned char  *pucAddr);
int Test_Km_Random();
int Sig_CheckServiceLog(void * hSessionHandle,unsigned int id);
int TestBase64();
//----------------------chunsy
int Sig_GetSysLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength);

int Sig_GetServiceLogAudit(void * hSessionHandle,unsigned int page,unsigned int uiStartTimelen,unsigned char *pucStartTime,unsigned int uiEndTimelen,unsigned char *pucEndTime,
	unsigned int uiSLAresultNum,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength);
int  PKI_GetPublicKeyFromCert(void * sessionHandle,unsigned int i_CertLen, unsigned char *i_Cert,unsigned int  *publickeyLen, unsigned char * publickey);
#endif
