/**************************************************************
**  文件名：
**  Copyright ? 2000  Shanghai XXX Co. Ltd.  技术开发部
**  All right reserved.
**  创建人：
**  日　期：
**  修改人：
**  日　期：
**  描　述：
**  版　本：
***************************************************************/

#ifndef _PHCDS_DATATYPE_H
#define _PHCDS_DATATYPE_H



#define MAX_SESSIONS 1000   /*最大打开会话数*/

#define MAX_ASYM_KAY_PAIR 2048   /*存储最大的密钥对*/

#ifndef NULL 
#define NULL 0
#endif



#define CARD_MAX_SESSIONS 1  /*每块卡最大的应用句柄数*/

//定义密码机应用中的各种常量--------------------

#define PINHASHALGID 			SDM_SHA1 /*用于Hash  用户Pin及管理员Pin的Hash 算法*/

#define MASTER_KEY_INDEX 		10   /*主密钥索引标识*/

#define STORE_PROTECT_KEY_INDEX 	0   /*密钥存储保护密钥*/

#define DEVICE_KEY_INDEX 		0   /*设备密钥标识*/





#define CONFIGFILE 	1   	/*配置文件路径标识*/

#define KEYFILE 	2   	/*非对成密钥文件路径标识*/

#define CERTFILE 	3   	/*证书文件路径标识*/

#define OTHERFILE 	4   	/*其他文件路径标识*/

#define KEKFILE 	5   	/*密钥加密密钥路径标识*/

  

#define READ_ASYM_SIGNPUBLIC_FLAG 	 1	//签名公钥   1 

#define READ_ASYM_SIGNPRIVATE_FLAG 	 2	//签名私钥   2 

#define READ_ASYM_ENCPUBLIC_FLAG 	 3	//加密公钥   3 

#define READ_ASYM_ENCPRIVATE_FLAG 	 4	//加密私钥   4 

#define READ_ASYM_USERPIN_FLAG 	 	 5	//用户Pin    5 

#define READ_ASYM_ADMINPIN_FLAG 	 6	//管理Pin    6 

#define READ_ASYM_INDEX_FLAG 	 	 7	//只查询索引 7 

#define READ_ASYM_KEY_ALGID_FLAG 	 8	//密钥算法   8 

#define READ_ASYM_KEY_LEN_FLAG 	 	 9	//密钥长度   9

#define READ_ASYM_SIGNPRIVATE_DEC_FLAG 	 10	//签名私钥原文   2 

#define READ_ASYM_ENCPRIVATE_DEC_FLAG 	 11	//加密私钥 原文  4  



#define READ_SYMM_KEY_FLAG       1  	//会话密钥密文

#define READ_SYMM_KEY_TYPE_FLAG  2   	//密钥类型

#define READ_SYMM_KEY_INDEX_FLAG 3    	//只查询索引

#define READ_SYMM_KEY_DEC_FLAG   4    	//会话密钥原文

				

  

#define MANAGER_SIGNKEY_TYPE	 	 0	//只生成签名密钥   

#define MANAGER_ENCKEY_TYPE 		 1	//只生成加密密钥   

#define MANAGER_SIGNENCKEY_TYPE 	 2	//生成一对密钥作为签名密钥和加密密钥 

#define MANAGER_SIGN_AND_ENCKEY_TYPE 	 3	//生成2对密钥分别作为签名密钥和加密密钥



#define READ_ASYM_SIGNPUBLIC_FLAG 	 1	//签名公钥   1 

#define READ_ASYM_SIGNPRIVATE_FLAG 	 2	//签名私钥   2 







/* ECC曲线类型 */



#define NIST_FP_160           1



#define NIST_FP_192           2



#define NIST_FP_224           3



#define NIST_FP_256           4



#define OSCCA_FP_192          5



#define OSCCA_FP_256          6



#define OSCCA_NEWFP_256       7







#define PARAID       NIST_FP_256



/*非对称算法机制：*/



#define SGD_RSA					0x00010000 /* RSA算法机制 */



#define SGD_SM2_1				0x00020100  //椭圆曲线签名算法



#define SGD_SM2_2				0x00020200  //椭圆曲线密钥交换协议



#define SGD_SM2_3				0x00020400  //椭圆曲线加密算法



#define RSA_DATA_VALUE_LEN	    2048  //RSA密码运算后的数据长度



#define ECC_KEY_BITS		    256  //ECC密钥长度

#define ECC_DATA_VALUE_LEN	    200  //ECC密钥长度

#define ECCref_MAX_CIPHER_LEN   136  //三未



/*对称算法机制：*/



#define SGD_SM1_ECB              0x00000101 /* SCB2 ECB加密机制 */ 

#define SGD_SM1_CBC              0x00000102 /* SCB2 CBC加密机制 */ 

#define SGD_SM1_CFB              0x00000104 /* SCB2 CFB加密机制 */ 

#define SGD_SM1_OFB              0x00000108 /* SCB2 OFB加密机制 */                                                           

#define SGD_SM1_MAC              0x00000110 /* SCB2 MAC加密机制 */                                                           

                                                                                                                             

#define SGD_SSF33_ECB            0x00000201 /* SSF33 ECB加密机制 */                                                          

#define SGD_SSF33_CBC            0x00000202 /* SSF33 CBC加密机制 */                                                          

#define SGD_SSF33_MAC            0x00000210 /* SSF33 MAC加密机制 */ 



#define SGD_SM4_ECB				 0x00000401



#define SGD_SMS4_ECB			 0x00000401

#define SGD_SMS4_CBC			 0x00000402

#define SGD_SMS4_CFB			 0x00000404

#define SGD_SMS4_OFB			 0x00000408

#define SGD_SMS4_MAC			 0x00000410



#define  SGD_RC2_ECB	         0x08000001

#define  SGD_RC2_CBC	         0x08000002

#define  SGD_RC2_CFB	         0x08000004

#define  SGD_RC2_OFB	         0x08000008

#define  SGD_RC2_MAC			 0x08000010   

      

#define  SGD_RC4_ECB	         0x04000001

#define  SGD_RC4_CBC	         0x04000002

#define  SGD_RC4_CFB	         0x04000004

#define  SGD_RC4_OFB	         0x04000008

#define  SGD_RC4_MAC	         0x04000010  



#define  SGD_AES_ECB			 0x02000001

#define  SGD_AES_CBC			 0x02000002

#define  SGD_AES_CFB			 0x02000004

#define  SGD_AES_OFB			 0x02000008

#define  SGD_AES_MAC			 0x02000010



#define	 SGD_3DES_ECB			 0x01000001                                                           

#define	 SGD_3DES_CBC			 0x01000002                                                            

#define	 SGD_3DES_CFB			 0x01000004                                                           

#define	 SGD_3DES_OFB			 0x01000008   

#define  SGD_3DES_MAC			 0x01000010                                                          





#define  CALG_3DES_ECB  0x00000001

#define  CALG_3DES_CBC	0x00000002 

#define  CALG_3DES_CFB	0x00000004 

#define  CALG_3DES_OFB	0x00000008    //老版本定义的类型 



#define SGD_3DES_KEY_LEN	    24



#define SGD_SM1_KEY_LEN		    16  /*带ID的SCH算法长度 */

                                                           

#define SGD_SSF33_KEY_LEN	    16  /* SHA-1算法长度 */  



#define SGD_SM4_KEY_LEN	 16



#define SGD_3DES_PADLEN					8

#define SGD_SM1_ECB_PADLEN              16 /* SCB2 ECB加密机制 */ 

#define SGD_SM1_CBC_PADLEN              16 /* SCB2 CBC加密机制 */ 

#define SGD_SM1_CFB_PADLEN              16 /* SCB2 CFB加密机制 */ 

#define SGD_SM1_OFB_PADLEN              16 /* SCB2 OFB加密机制 */                                                           

#define SGD_SSF33_ECB_PADLEN            16 /* SSF33 ECB加密机制 */                                                          

#define SGD_SSF33_CBC_PADLEN            16 /* SSF33 CBC加密机制 */                                                          

                                                        

                                                          



/*HASH算法机制 */



#define SGD_SM3			    0x00000001  /*带ID的SCH算法机制 */



#define SGD_SHA1	        0x00000002  /* SHA-1算法机制 */



#define SGD_SHA256	        0x00000004  /*SHA256杂凑算法 */



#define SGD_SM3_LEN		256  /*带ID的SCH算法长度 */



#define SGD_SHA1_LEN	        128  /* SHA-1算法长度 */



#define SGD_SHA256_LEN	        256  /*SHA256杂凑算法长度 */



#define SGD_SCH_ID	0x00000040// 带ID的SCH算法机制

#define SGD_SCH			SGD_SM3	//SM3杂凑算法







/*外加机制*/



#define SGD_RSA_SIGN_EX		0x00010001  //导入或导出RSA签名或验证密钥时使用



#define SGD_RSA_ENC_EX		0x00010002  //导入或导出RSA加密或解密密钥时使用





/*SJY16-D 算法机制*/

#define SDM_SCB2_ECB	0x00000001// SCB2 ECB加密机制

#define SDM_SCB2_CBC	0x00000002// SCB2 CBC加密机制

#define SDM_SCB2_CFB	0x00000004// SCB2 CFB加密机制

#define SDM_SCB2_OFB	0x00000008// SCB2 OFB加密机制

#define SDM_SCB2_MAC	0x00000010// SCB2 MAC机制



#define SDM_SSF33_ECB	0x00000020

#define SDM_SSF33_CBC	0x00000040

#define SDM_SSF33_CFB	0x00000080

#define SDM_SSF33_OFB	0x00000100

#define SDM_SSF33_MAC	0x00000200



#define SDM_SHA1		0x00000002// SHA-1算法机制

#define SDM_SHA256		0x00000004



#define SDM_RSA			0x00000001// RSA算法机制



typedef unsigned char		BYTE; 

typedef unsigned long		DWORD;



typedef DWORD       DLLHANDLE;                   

typedef DLLHANDLE   DLLINSTANCE;





typedef struct DeviceInfo_st{

       unsigned char IssuerName[40];

       unsigned char DeviceName[16];

       unsigned char DeviceSerial[16];

       unsigned int  DeviceVersion;

       unsigned int  StandardVersion;

       unsigned int  AsymAlgAbility[2];

       unsigned int  SymAlgAbility;

       unsigned int  HashAlgAbility;

       unsigned int  BufferSize;

}DEVICEINFO;



#define PIN_MAX_LEN      			256 

#define PIN_MIN_LEN      			8

#define MAX_LEN      				 256

#define FILENAME_MAX_LEN     128

#define USERKEY_MAX_LEN      256 

#define RSAref_MAX_BITS_1    2048

#define RSAref_MAX_LEN_1     ((RSAref_MAX_BITS_1 + 7) / 8)

#define RSAref_MAX_PBITS_1   ((RSAref_MAX_BITS_1 + 1) / 2)

#define RSAref_MAX_PLEN_1    ((RSAref_MAX_PBITS_1 + 7)/ 8)







typedef struct RSArefPublicKey_st

{

	unsigned int  bits;

	unsigned char m[RSAref_MAX_LEN_1];

	unsigned char e[RSAref_MAX_LEN_1];

} RSArefPublicKey, *pRSArefPublicKey;







typedef struct RSArefPrivateKey_st



{

unsigned int  bits;

unsigned char m[RSAref_MAX_LEN_1];

unsigned char e[RSAref_MAX_LEN_1];

unsigned char d[RSAref_MAX_LEN_1];

unsigned char prime[2][RSAref_MAX_PLEN_1];

unsigned char pexp[2][RSAref_MAX_PLEN_1];

unsigned char coef[RSAref_MAX_PLEN_1];

} RSArefPrivateKey, *pRSArefPrivateKey;







//密钥加密密钥

typedef struct tagUserKey
{
	unsigned int UserKeyIndex;//会话密钥索引值（注：0号密钥为初始密钥加密密钥）

	unsigned int uiAlgID;//对称算法类型

	unsigned char *UserKeyValue;//会话密钥值

	unsigned int UserKeyLen;//会话密钥长度

	unsigned char *UserKeyDecValue;//原文

	unsigned int UserKeyDecLen;//原文长度	

	

}UserKey, *PUserKey;



//用户应用密钥结构，用于记录所有的密钥信息并生成索引 用于此接口：ks_SaveAppKeyInfoToListFile

typedef struct tagUserAppKeyInfo

{

	unsigned int UserKeyIndex;

	unsigned int uiAlgID;

	unsigned int  uiKeyBits;

	unsigned char ucSigPubKey[1024];//公钥KEY

	unsigned int  uiSigPubKeyLen;

	unsigned char ucEncPubKey[1024];//公钥KEY

	unsigned int  uiEncPubKeyLen;

	unsigned int uiKeyType;

}UserAppKeyInfo, *PUserAppInfo;



typedef struct APPKEYLIST

{

	UserAppKeyInfo UserAppKeyInfoRecord;

	struct APPKEYLIST *Next;

}AppKeyList, *PAppKeyList;





typedef struct UserKeyList

{

	UserKey *UserKeyData;

	struct UserKeyList *Next;

}USERKEYLIST, *PUSERKEYLIST;



//非对称密钥对结构

typedef struct UserAsymKeyRecord

{

	unsigned int Index;//RSA密钥索引值（注：0号密钥为设备密钥）

	BYTE  *SignPublicKey;//签名公钥

	unsigned int   SignPublicKeyLen;



	BYTE  *SignPrivateKey;//签名私钥

	unsigned int   SignPrivateKeyLen;



	BYTE  *SignPrivateKeyDec;//签名私钥原文

	unsigned int   SignPrivateKeyDecLen;  //签名私钥原文长度



	BYTE  *EncPublicKey;//加密公钥

        unsigned int   EncPublicKeyLen;



	BYTE  *EncPrivateKey;//加密私钥

	unsigned int   EncPrivateKeyLen;



	BYTE  *EncPrivateKeyDec;//加密私钥原文

	unsigned int   EncPrivateKeyDecLen;//加密私钥原文长度





	BYTE  *UserPin;//用户使用PIN码

        unsigned int   UserPinLen;



	BYTE  *AdminPin;//管理员使用PIN码

	unsigned int   AdminPinLen;



        unsigned int   uiAlgID;//密钥算法

	unsigned int   AlgLen;//密钥长度

} UserAsymKey, *pUserAsymKey;





typedef struct keycontainer

{

	UserAsymKey *AsymKey;

	struct keycontainer *NextKey;

} KEYCONTAINER, *PKEYCONTAINER;



typedef struct deviceInfo_st

{

	void * deviceId;

	unsigned long ulDeviceId;

	unsigned int device_status;

	unsigned int keyindex;

}DEVICEHANDLEINFO;

typedef struct devicelist

{

	DEVICEHANDLEINFO *sessiondata;

	struct devicelist *Next;

}DEVICELIST, *LPDEVICELIST;



typedef struct session_st

{

	void * sessionId;

	unsigned long ulSessionId;

	unsigned int session_status;

	unsigned int keyindex;

}SESSIONINFO;





typedef struct sessionlist

{

	SESSIONINFO sessiondata;

	struct sessionlist *Next;

}SESSIONLIST, *LPSESSIONLIST;



//typedef struct Handle_struct{

//

//	unsigned int uiHandlemark;

//

//	unsigned int uiHandlecode;

//

//	unsigned int uiKeynumber;

//

//	unsigned int uiKeyindex[32];

//

//}Handlestruct;                /* 句柄结构 */











//typedef struct Device_struct{

//

//	unsigned int uiDevicemark;

//

//	unsigned int uiDevicecode;

//

//}Devicestruct;







#define ECCref_MAX_BITS			256

#define ECCref_MAX_LEN			((ECCref_MAX_BITS+7) / 8)



#define GM512ECCref_MAX_BITS			512

#define GM512ECCref_MAX_LEN			((GM512ECCref_MAX_BITS+7) / 8)





typedef struct EccKeyChain {

	int 						id;

	unsigned char 	signpubkey[ECCref_MAX_LEN*2];

	unsigned char 	signprikey[ECCref_MAX_LEN];

	unsigned char 	encpubkey[ECCref_MAX_LEN*2];

	unsigned char 	encprikey[ECCref_MAX_LEN];

}ECCKEY;







typedef struct ECCrefPublicKey_st
{	

	unsigned int  bits;

	unsigned char x[ECCref_MAX_LEN]; 

	unsigned char y[ECCref_MAX_LEN]; 

}ECCrefPublicKey;



typedef struct GM512ECCrefPublicKey_st
{	

	unsigned int  bits;

	unsigned char x[GM512ECCref_MAX_LEN]; 

	unsigned char y[GM512ECCref_MAX_LEN]; 

}GM512ECCrefPublicKey;



typedef struct ECCrefPrivateKey_st



{

    unsigned int  bits;

    unsigned char D[ECCref_MAX_LEN];

} ECCrefPrivateKey;



typedef struct GM512ECCrefPrivateKey_st



{

    unsigned int  bits;

    unsigned char D[GM512ECCref_MAX_LEN];

} GM512ECCrefPrivateKey;



typedef struct ECCCipher_st



{

	unsigned char x[ECCref_MAX_LEN]; 

	unsigned char y[ECCref_MAX_LEN]; 

	unsigned char C[ECCref_MAX_LEN];

    unsigned char M[ECCref_MAX_LEN];

} ECCCipher;



typedef struct ECCCipher_st_sw



{

	unsigned int clen;

	unsigned char x[ECCref_MAX_LEN]; 

	unsigned char y[ECCref_MAX_LEN]; 

	unsigned char C[ECCref_MAX_CIPHER_LEN];

    unsigned char M[ECCref_MAX_LEN];

} ECCCipher_sw;



typedef struct ECCSignature_st



{

	unsigned char r[ECCref_MAX_LEN];	

	unsigned char s[ECCref_MAX_LEN];	

} ECCSignature;









#endif



