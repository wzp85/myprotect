/**************************************************************
**  �ļ�����
**  Copyright ? 2000  Shanghai XXX Co. Ltd.  ����������
**  All right reserved.
**  �����ˣ�
**  �ա��ڣ�
**  �޸��ˣ�
**  �ա��ڣ�
**  �衡����
**  �桡����
***************************************************************/

#ifndef _PHCDS_DATATYPE_H
#define _PHCDS_DATATYPE_H



#define MAX_SESSIONS 1000   /*���򿪻Ự��*/

#define MAX_ASYM_KAY_PAIR 2048   /*�洢������Կ��*/

#ifndef NULL 
#define NULL 0
#endif



#define CARD_MAX_SESSIONS 1  /*ÿ�鿨����Ӧ�þ����*/

//���������Ӧ���еĸ��ֳ���--------------------

#define PINHASHALGID 			SDM_SHA1 /*����Hash  �û�Pin������ԱPin��Hash �㷨*/

#define MASTER_KEY_INDEX 		10   /*����Կ������ʶ*/

#define STORE_PROTECT_KEY_INDEX 	0   /*��Կ�洢������Կ*/

#define DEVICE_KEY_INDEX 		0   /*�豸��Կ��ʶ*/





#define CONFIGFILE 	1   	/*�����ļ�·����ʶ*/

#define KEYFILE 	2   	/*�ǶԳ���Կ�ļ�·����ʶ*/

#define CERTFILE 	3   	/*֤���ļ�·����ʶ*/

#define OTHERFILE 	4   	/*�����ļ�·����ʶ*/

#define KEKFILE 	5   	/*��Կ������Կ·����ʶ*/

  

#define READ_ASYM_SIGNPUBLIC_FLAG 	 1	//ǩ����Կ   1 

#define READ_ASYM_SIGNPRIVATE_FLAG 	 2	//ǩ��˽Կ   2 

#define READ_ASYM_ENCPUBLIC_FLAG 	 3	//���ܹ�Կ   3 

#define READ_ASYM_ENCPRIVATE_FLAG 	 4	//����˽Կ   4 

#define READ_ASYM_USERPIN_FLAG 	 	 5	//�û�Pin    5 

#define READ_ASYM_ADMINPIN_FLAG 	 6	//����Pin    6 

#define READ_ASYM_INDEX_FLAG 	 	 7	//ֻ��ѯ���� 7 

#define READ_ASYM_KEY_ALGID_FLAG 	 8	//��Կ�㷨   8 

#define READ_ASYM_KEY_LEN_FLAG 	 	 9	//��Կ����   9

#define READ_ASYM_SIGNPRIVATE_DEC_FLAG 	 10	//ǩ��˽Կԭ��   2 

#define READ_ASYM_ENCPRIVATE_DEC_FLAG 	 11	//����˽Կ ԭ��  4  



#define READ_SYMM_KEY_FLAG       1  	//�Ự��Կ����

#define READ_SYMM_KEY_TYPE_FLAG  2   	//��Կ����

#define READ_SYMM_KEY_INDEX_FLAG 3    	//ֻ��ѯ����

#define READ_SYMM_KEY_DEC_FLAG   4    	//�Ự��Կԭ��

				

  

#define MANAGER_SIGNKEY_TYPE	 	 0	//ֻ����ǩ����Կ   

#define MANAGER_ENCKEY_TYPE 		 1	//ֻ���ɼ�����Կ   

#define MANAGER_SIGNENCKEY_TYPE 	 2	//����һ����Կ��Ϊǩ����Կ�ͼ�����Կ 

#define MANAGER_SIGN_AND_ENCKEY_TYPE 	 3	//����2����Կ�ֱ���Ϊǩ����Կ�ͼ�����Կ



#define READ_ASYM_SIGNPUBLIC_FLAG 	 1	//ǩ����Կ   1 

#define READ_ASYM_SIGNPRIVATE_FLAG 	 2	//ǩ��˽Կ   2 







/* ECC�������� */



#define NIST_FP_160           1



#define NIST_FP_192           2



#define NIST_FP_224           3



#define NIST_FP_256           4



#define OSCCA_FP_192          5



#define OSCCA_FP_256          6



#define OSCCA_NEWFP_256       7







#define PARAID       NIST_FP_256



/*�ǶԳ��㷨���ƣ�*/



#define SGD_RSA					0x00010000 /* RSA�㷨���� */



#define SGD_SM2_1				0x00020100  //��Բ����ǩ���㷨



#define SGD_SM2_2				0x00020200  //��Բ������Կ����Э��



#define SGD_SM2_3				0x00020400  //��Բ���߼����㷨



#define RSA_DATA_VALUE_LEN	    2048  //RSA�������������ݳ���



#define ECC_KEY_BITS		    256  //ECC��Կ����

#define ECC_DATA_VALUE_LEN	    200  //ECC��Կ����

#define ECCref_MAX_CIPHER_LEN   136  //��δ



/*�Գ��㷨���ƣ�*/



#define SGD_SM1_ECB              0x00000101 /* SCB2 ECB���ܻ��� */ 

#define SGD_SM1_CBC              0x00000102 /* SCB2 CBC���ܻ��� */ 

#define SGD_SM1_CFB              0x00000104 /* SCB2 CFB���ܻ��� */ 

#define SGD_SM1_OFB              0x00000108 /* SCB2 OFB���ܻ��� */                                                           

#define SGD_SM1_MAC              0x00000110 /* SCB2 MAC���ܻ��� */                                                           

                                                                                                                             

#define SGD_SSF33_ECB            0x00000201 /* SSF33 ECB���ܻ��� */                                                          

#define SGD_SSF33_CBC            0x00000202 /* SSF33 CBC���ܻ��� */                                                          

#define SGD_SSF33_MAC            0x00000210 /* SSF33 MAC���ܻ��� */ 



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

#define  CALG_3DES_OFB	0x00000008    //�ϰ汾��������� 



#define SGD_3DES_KEY_LEN	    24



#define SGD_SM1_KEY_LEN		    16  /*��ID��SCH�㷨���� */

                                                           

#define SGD_SSF33_KEY_LEN	    16  /* SHA-1�㷨���� */  



#define SGD_SM4_KEY_LEN	 16



#define SGD_3DES_PADLEN					8

#define SGD_SM1_ECB_PADLEN              16 /* SCB2 ECB���ܻ��� */ 

#define SGD_SM1_CBC_PADLEN              16 /* SCB2 CBC���ܻ��� */ 

#define SGD_SM1_CFB_PADLEN              16 /* SCB2 CFB���ܻ��� */ 

#define SGD_SM1_OFB_PADLEN              16 /* SCB2 OFB���ܻ��� */                                                           

#define SGD_SSF33_ECB_PADLEN            16 /* SSF33 ECB���ܻ��� */                                                          

#define SGD_SSF33_CBC_PADLEN            16 /* SSF33 CBC���ܻ��� */                                                          

                                                        

                                                          



/*HASH�㷨���� */



#define SGD_SM3			    0x00000001  /*��ID��SCH�㷨���� */



#define SGD_SHA1	        0x00000002  /* SHA-1�㷨���� */



#define SGD_SHA256	        0x00000004  /*SHA256�Ӵ��㷨 */



#define SGD_SM3_LEN		256  /*��ID��SCH�㷨���� */



#define SGD_SHA1_LEN	        128  /* SHA-1�㷨���� */



#define SGD_SHA256_LEN	        256  /*SHA256�Ӵ��㷨���� */



#define SGD_SCH_ID	0x00000040// ��ID��SCH�㷨����

#define SGD_SCH			SGD_SM3	//SM3�Ӵ��㷨







/*��ӻ���*/



#define SGD_RSA_SIGN_EX		0x00010001  //����򵼳�RSAǩ������֤��Կʱʹ��



#define SGD_RSA_ENC_EX		0x00010002  //����򵼳�RSA���ܻ������Կʱʹ��





/*SJY16-D �㷨����*/

#define SDM_SCB2_ECB	0x00000001// SCB2 ECB���ܻ���

#define SDM_SCB2_CBC	0x00000002// SCB2 CBC���ܻ���

#define SDM_SCB2_CFB	0x00000004// SCB2 CFB���ܻ���

#define SDM_SCB2_OFB	0x00000008// SCB2 OFB���ܻ���

#define SDM_SCB2_MAC	0x00000010// SCB2 MAC����



#define SDM_SSF33_ECB	0x00000020

#define SDM_SSF33_CBC	0x00000040

#define SDM_SSF33_CFB	0x00000080

#define SDM_SSF33_OFB	0x00000100

#define SDM_SSF33_MAC	0x00000200



#define SDM_SHA1		0x00000002// SHA-1�㷨����

#define SDM_SHA256		0x00000004



#define SDM_RSA			0x00000001// RSA�㷨����



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







//��Կ������Կ

typedef struct tagUserKey
{
	unsigned int UserKeyIndex;//�Ự��Կ����ֵ��ע��0����ԿΪ��ʼ��Կ������Կ��

	unsigned int uiAlgID;//�Գ��㷨����

	unsigned char *UserKeyValue;//�Ự��Կֵ

	unsigned int UserKeyLen;//�Ự��Կ����

	unsigned char *UserKeyDecValue;//ԭ��

	unsigned int UserKeyDecLen;//ԭ�ĳ���	

	

}UserKey, *PUserKey;



//�û�Ӧ����Կ�ṹ�����ڼ�¼���е���Կ��Ϣ���������� ���ڴ˽ӿڣ�ks_SaveAppKeyInfoToListFile

typedef struct tagUserAppKeyInfo

{

	unsigned int UserKeyIndex;

	unsigned int uiAlgID;

	unsigned int  uiKeyBits;

	unsigned char ucSigPubKey[1024];//��ԿKEY

	unsigned int  uiSigPubKeyLen;

	unsigned char ucEncPubKey[1024];//��ԿKEY

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



//�ǶԳ���Կ�Խṹ

typedef struct UserAsymKeyRecord

{

	unsigned int Index;//RSA��Կ����ֵ��ע��0����ԿΪ�豸��Կ��

	BYTE  *SignPublicKey;//ǩ����Կ

	unsigned int   SignPublicKeyLen;



	BYTE  *SignPrivateKey;//ǩ��˽Կ

	unsigned int   SignPrivateKeyLen;



	BYTE  *SignPrivateKeyDec;//ǩ��˽Կԭ��

	unsigned int   SignPrivateKeyDecLen;  //ǩ��˽Կԭ�ĳ���



	BYTE  *EncPublicKey;//���ܹ�Կ

        unsigned int   EncPublicKeyLen;



	BYTE  *EncPrivateKey;//����˽Կ

	unsigned int   EncPrivateKeyLen;



	BYTE  *EncPrivateKeyDec;//����˽Կԭ��

	unsigned int   EncPrivateKeyDecLen;//����˽Կԭ�ĳ���





	BYTE  *UserPin;//�û�ʹ��PIN��

        unsigned int   UserPinLen;



	BYTE  *AdminPin;//����Աʹ��PIN��

	unsigned int   AdminPinLen;



        unsigned int   uiAlgID;//��Կ�㷨

	unsigned int   AlgLen;//��Կ����

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

//}Handlestruct;                /* ����ṹ */











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



