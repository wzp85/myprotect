
#ifndef  _SMARTCTCAPI_H_
#define  _SMARTCTCAPI_H_
#ifdef __cplusplus
extern "C" {
#endif	
#include <windows.h>
#define IN
#define OUT
#define DEVAPI  __stdcall
//#define ADMIN_TYPE 0
//#define USER_TYPE  1
#ifndef TRUE
#define TRUE       0x00000001
#endif
#ifndef FALSE
#define FALSE      0x00000000
#endif



//#define SGD_3DES_ECB  0x00000001  //3DES�㷨ECB����ģʽ  syc
//#define SGD_3DES_CBC  0x00000002  //3DES�㷨CBC����ģʽ  syc
//#define SGD_3DES_CFB  0x00000004  //3DES�㷨CFB����ģʽ  syc
//#define SGD_3DES_OFB  0x00000008  //3DES�㷨OFB����ģʽ  syc
//#define SGD_3DES_MAC  0x00000010  //3DES�㷨MAC����  syc

//���������㷨��ʶ
#define SGD_SM1_ECB  0x00000101  //SM1�㷨ECB����ģʽ
#define SGD_SM1_CBC  0x00000102  //SM1�㷨CBC����ģʽ
#define SGD_SM1_CFB  0x00000104  //SM1�㷨CFB����ģʽ
#define SGD_SM1_OFB  0x00000108  //SM1�㷨OFB����ģʽ
#define SGD_SM1_MAC  0x00000110  //SM1�㷨MAC����

#define SGD_SSF33_ECB 0x00000201 //SSF33�㷨ECB����ģʽ
#define SGD_SSF33_CBC 0x00000202 //SSF33�㷨CBC����ģʽ
#define SGD_SSF33_CFB 0x00000204 //SSF33�㷨CFB����ģʽ
#define SGD_SSF33_OFB 0x00000208 //SSF33�㷨OFB����ģʽ
#define SGD_SSF33_MAC 0x00000210 //SSF33�㷨MAC����

#define SGD_SMS4_ECB  0x00000401 //SMS4�㷨ECB����ģʽ
#define SGD_SMS4_CBC  0x00000402
#define SGD_SMS4_CFB  0x00000404
#define SGD_SMS4_OFB  0x00000408
#define SGD_SMS4_MAC  0x00000410

//0x00000400-0x800000xx  �������������㷨Ԥ��

//�ǶԳ���Կ�㷨��ʶ
#define SGD_RSA     0x00010000    //RSA�㷨
#define SGD_SM2_1   0x00020100    //��Բ����ǩ���㷨
#define SGD_SM2_2   0x00020200    //��Բ������Կ����Э��
#define SGD_SM2_3   0x00020400    //��Բ���߼����㷨

//�����Ӵ��㷨��ʶ
#define SGD_SM3     0x00000001    //SM3�Ӵ��㷨
#define SGD_SHA1    0x00000002    //SHA1�Ӵ��㷨
#define SGD_SHA256  0x00000004    //SHA256�Ӵ��㷨
#define SGD_MD5		0x00000003

////Ϊ���籣�Ľӿڣ�----��ϣ��ʶ
#define ALG_SCH     0x00000040    //SCH�Ӵ��㷨
#define ALG_SHA1    0x00000080    //SHA1�Ӵ��㷨
#define ALG_SHA256  0x00000100    //SHA256�Ӵ��㷨

//0x00000010-0x000000FF Ϊ���������Ӵ��㷨Ԥ��
//
/*	typedef char                 INT8;      //�з���8λ����*/
	typedef short                INT16;     //�з���16λ����
	typedef unsigned char        UINT8;     //�޷���8λ����
	typedef unsigned short       UINT16;    //�޷���16λ����
	typedef float                FP32;      //32λ�����ȸ�����
	typedef double               FP64;      //64λ˫���ȸ�����
	typedef UINT8                BYTE;       //�ֽ����ͣ��޷���8λ����
	typedef INT16                SHORT;      //���������з���16λ����
	typedef UINT16               USHORT;     //�޷���16λ����
	typedef UINT32               UINT;       //�޷���32λ����
	typedef UINT16               WORD;       //�����ͣ��޷���16λ����
	typedef UINT32               FLAGS;      //��־���ͣ��޷���32λ����
	typedef CHAR *               LPSTR;      //8λ�ַ���ָ��
	typedef void *               HANDLE;     //�����ָ���������ݶ������ʼ��ַ
	typedef HANDLE               DEVHANDLE;  //�豸���
	typedef HANDLE               HAPPLICATION;  //Ӧ�þ��
	typedef HANDLE               HCONTAINER; //�������
//	typedef char                 CHAR;
	
//�豸Ȩ������             
#define     SECURE_NEVER_ACCOUNT       0x00000000             //������
#define     SECURE_ADM_ACCOUNT         0x00000001             //����ԱȨ��
#define     SECURE_USER_ACCOUNT        0x00000010             //�û�Ȩ��
#define     SECURE_EVERYONE_ACCOUNT    0x000000FF             //�κ���

//PIN������
#define	ADMIN_TYPE						0x00000000	// ����ԱPIN
#define USER_TYPE						0x00000001	// �û�PIN


//�豸״̬
#define  DEV_EMPTY_STATE     0x00000000    //�豸������
#define  DEV_PRESENT_STATE   0x00000001    //�豸����
#define DEV_UNKNOW_STATE				0x00000002


//�������
#define  SAR_OK                      0x00000000          //�ɹ�
#define  SAR_FAIL                    0x0A000001          //ʧ��
#define  SAR_UNKNOWNERR              0x0A000002          //�쳣����
#define  SAR_NOTSUPPORTYETERR        0x0A000003          //��֧�ֵķ���
#define  SAR_FILEERR                 0x0A000004          //�ļ���������
#define  SAR_INVALIDHANDLEERR        0x0A000005          //��Ч�ľ��
#define  SAR_INVALIDPARAMERR         0x0A000006          //��Ч�Ĳ���
#define  SAR_READFILEERR             0x0A000007          //���ļ�����
#define  SAR_WRITEFILEERR            0x0A000008          //д�ļ�����
#define  SAR_NAMELENERR              0x0A000009          //���Ƴ��ȴ���
#define  SAR_KEYUSAGEERR             0x0A00000A          //��Կ��;����
#define  SAR_MODULUSLENERR           0x0A00000B          //ģ�ĳ��ȴ���
#define  SAR_NOTINITIALIZEERR        0x0A00000C          //δ��ʼ��
#define  SAR_OBJERR                  0x0A00000D          //�������
#define  SAR_MEMORYERR               0x0A00000E          //�ڴ����
#define  SAR_TIMEOUTERR              0x0A00000F          //��ʱ
#define  SAR_INDATALENERR            0x0A000010          //�������ݳ��ȴ���
#define  SAR_INDATAERR               0x0A000011          //�������ݴ���
#define  SAR_GENRANDERR              0x0A000012          //�������������
#define  SAR_HASHOBJERR              0x0A000013          //HASH�����
#define  SAR_HASHERR                 0x0A000014          //HASH�������
#define  SAR_GENRSAKEYERR            0x0A000015          //����RSA��Կ����
#define  SAR_RSAMODULUSLENERR        0x0A000016          //RSA��Կģ������
#define  SAR_CSPIMPRTPUBKEYERR       0x0A000017          //CSP�����빫Կ����
#define  SAR_RSAENCERR               0x0A000018          //RSA���ܴ���
#define  SAR_RSADECERR               0x0A000019          //RSA���ܴ���
#define  SAR_HASHNOTEQUALERR         0x0A00001A          //HASHֵ�����
#define  SAR_KEYNOTFOUNTERR          0x0A00001B          //��Կδ����
#define  SAR_CERTNOTFOUNTERR         0x0A00001C          //֤��δ����
#define  SAR_NOTEXPORTERR            0x0A00001D          //����δ����
#define  SAR_DECRYPTPADERR           0x0A00001E          //����ʱ����������
#define  SAR_MACLENERR               0x0A00001F          //MAC���ȴ���
#define  SAR_BUFFER_TOO_SMALL        0x0A000020          //����������
#define  SAR_KEYINFOTYPEERR          0x0A000021          //��Կ���ʹ���
#define  SAR_NOT_EVENTERR            0x0A000022          //���¼�����
#define  SAR_DEVICE_REMOVED          0x0A000023          //�豸���Ƴ�
#define  SAR_PIN_INCORRECT           0x0A000024          //PIN����ȷ
#define  SAR_PIN_LOCKED              0x0A000025          //PIN������
#define  SAR_PIN_INVALID             0x0A000026          //PIN��Ч
#define  SAR_PIN_LEN_RANGE           0x0A000027          //PIN���ȴ���
#define  SAR_USER_ALREADY_LOGGED_IN  0x0A000028          //�û��Ѿ���¼
#define  SAR_USER_PIN_NOT_INITIALIZED 0x0A000029         //û�г�ʼ���û�����
#define  SAR_USER_TYPE_INVALID       0x0A00002A          //PIN���ʹ���
#define  SAR_APPLICATION_NAME_INVALID 0x0A00002B         //Ӧ��������Ч
#define  SAR_APPLICATION_EXISTS      0x0A00002C          //Ӧ���Ѿ�����
#define  SAR_USER_NOT_LOGGED_IN      0x0A00002D          //�û�û�е�¼
#define  SAR_APPLICATION_NOT_EXISTS  0x0A00002E          //Ӧ�ò�����
#define  SAR_FILE_ALREADY_EXIST      0x0A00002F          //�ļ��Ѿ�����
#define  SAR_NO_ROOM                 0x0A000030          //�ռ䲻��
#define  SAR_FILE_NOT_EXIST          0x0A000031          //�ļ�������
#define  SAR_NOTSUPPORTKEYTYPE       0x0A000032          //��֧��SM2�㷨
	

//�汾
typedef struct Struct_Version{
	BYTE major ;   //�����
	BYTE minor ;   //�ΰ��
	} VERSION;
	
	//�豸��Ϣ
typedef struct Struct_DEVINFO {
	VERSION  Version;         //���ݽṹ�汾��,���ṹ�İ汾��Ϊ1.0
	CHAR Manufacturer[64];    //�豸������Ϣ, ��'\0'Ϊ��������ASCII�ַ���		
	CHAR Issuer[64];          //���г�����Ϣ, ��'\0'Ϊ��������ASCII�ַ���
	CHAR Label[32];           //�豸��ǩ, ��'\0'Ϊ��������ASCII�ַ���
	CHAR SerialNumber[32];    //���к�, ��'\0'Ϊ��������ASCII�ַ���	                 
	VERSION HWVersion;        //�豸Ӳ���汾
	VERSION FirmwareVersion;  //�豸����̼��汾
	ULONG   AlgSymCap;        //���������㷨��ʶ
	ULONG   AlgAsymCap;       //�ǶԳ������㷨��ʶ
	ULONG   AlgHashCap;       //�����Ӵ��㷨��ʶ   
    ULONG   DevAuthAlgId;     //�豸��֤ʹ�õķ��������㷨��ʶ
	ULONG   TotalSpace;       //�豸�ܿռ�
	ULONG   FreeSpace;        //�û����ÿռ�
    BYTE    Reserved[64];     //������չ	
	}DEVINFO,*PDEVINFO;

// ����˵�RSA�ṹ
#define RSAref_MAX_BITS    2048
#define RSAref_MAX_LEN     ((RSAref_MAX_BITS + 7) / 8)
#define RSAref_MAX_PBITS   ((RSAref_MAX_BITS + 1) / 2)
#define RSAref_MAX_PLEN    ((RSAref_MAX_PBITS + 7)/ 8)
//typedef struct RSArefPublicKey_st
//{
//unsigned int  bits;
//unsigned char m[RSAref_MAX_LEN];
//unsigned char e[RSAref_MAX_LEN];
//} RSArefPublicKey;

//RSA ��Կ���ݽṹ
#define  MAX_RSA_MODULUS_LEN        256         //RSA�㷨�����ģ��
#define  MAX_RSA_EXPONENT_LEN       4           //�㷨ָ������󳤶�  
typedef  struct Struct_RSAPUBLICKEYBLOB{	
	ULONG AlgID ;                               //�㷨��ʶ��
	ULONG BitLen ;                              //ģ����ʵ��λ����  ������8��������
	BYTE Modulus[MAX_RSA_MODULUS_LEN];          //ģ�� n=p*q  ʵ�ʳ�����BitLen/8�ֽ�
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];  //������Կ e
	}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB; 
	
//RSA ˽Կ���ݽṹ
typedef struct Struct_RSAPRIVATEKEYBLOB{
	ULONG AlgID ;                                //�㷨��ʶ��
	ULONG BitLen ;                               //ģ����ʵ��λ����  ��������8��������
	BYTE Modulus[MAX_RSA_MODULUS_LEN];           //ģ�� n=p*q  ʵ�ʳ�����BitLen/8�ֽ�
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];
	BYTE PrivateExponent[MAX_RSA_MODULUS_LEN];   //˽����Կd   ʵ�ʳ�����BitLen/8�ֽ�
	BYTE Prime1[MAX_RSA_MODULUS_LEN/2];          //����p       ʵ�ʳ�����BitLen/16�ֽ�
	BYTE Prime2[MAX_RSA_MODULUS_LEN/2];          //����q       ʵ�ʳ�����BitLen/16�ֽ�
	BYTE Prime1Exponent[MAX_RSA_MODULUS_LEN/2];  //d mod (p-1)ֵ ʵ�ʳ�����BitLen/16�ֽ�
	BYTE Prime2Exponent[MAX_RSA_MODULUS_LEN/2];  //d mod (q-1)ֵ ʵ�ʳ�����BitLen/16�ֽ�
	BYTE Coefficient[MAX_RSA_MODULUS_LEN/2];     //q ģ p �ĳ˷���Ԫ ʵ�ʳ�����BitLen/16�ֽ�
	}RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;
	
//ECC ��Կ���ݽṹ  
#define   ECC_MAX_XCOORDINATE_BITS_LEN  512//�����ϵ��X������
#define   ECC_MAX_YCOORDINATE_BITS_LEN  512//�����ϵ��Y����
#define   ECC_MAX_MODULUS_BITS_LEN 512
//6.4.5 ECC��Կ�������ݿ� 
//��1�����Ͷ��� 
typedef struct Struct_ECCPUBLICKEYBLOB{ 
	//ULONG AlgID; by shenjun at 20110401
	ULONG BitLen; 
	BYTE XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8]; 
	BYTE YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8]; 
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB; 

//6.4.6 ECC˽Կ�������ݿ� 
typedef struct Struct_ECCPRIVATEKEYBLOB{ 
	//ULONG AlgID; by shenjun at 20110401
	ULONG BitLen; 
	BYTE PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8]; 
}ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB; 
// ECC�������ݽṹ
typedef struct Struct_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  Hash[32];
	ULONG CipherLen;
	BYTE  Cipher[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}ECCCIPHERBLOB, *PECCCIPHERBLOB;

typedef struct SKF_ENVELOPEDKEYBLOB{
	ULONG Version;                  // ��ǰ�汾Ϊ 1
	ULONG ulSymmAlgID;              // �淶�е��㷨��ʶ���޶�ECBģʽ
	ULONG ulBits;					// ������Կ����Կ���� 	
	BYTE cbEncryptedPriKey[64];     // ���ܱ����ļ���˽Կ
	ECCPUBLICKEYBLOB PubKey;        // ���ܹ�Կ
	ECCCIPHERBLOB ECCCipherBlob;    // SM2 ��Կ���ܵ���Կ������Կ
}ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

// ECCǩ�����ݽṹ
typedef struct Struct_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

//�����������
#define  MAX_IV_LEN  32
typedef struct Struct_BLOCKCIPHERPARAM{
	BYTE IV[MAX_IV_LEN];    //��ʼ����
	ULONG IVLen;            //��ʼ����ʵ�ʳ���
	ULONG PaddingType;      //��䷽ʽ 0��ʾ����䣬1��ʾ����PKCS#5��ʽ����
	ULONG FeedBitLen;	    // 
}BLOCKCIPHERPARAM,*PBLOCKCIPHERPARAM;



//�ļ�����
#define MAX_FILE_NAME_LEN    32    //����ļ����ֳ��� ��ʱ����Ϊ��ֵ
typedef struct Struct_FILEATTRIBUTE{
	CHAR  FileName[32];     //�ļ��� �ԡ�\0��������ASCII�ַ�������󳤶�32
    ULONG FileSize;         //�����ļ�ʱ������ļ���С
    ULONG ReadRights;       //��ȡ�ļ���Ҫ��Ȩ��
	ULONG WriteRights;      //д���ļ���Ҫ��Ȩ��
}FILEATTRIBUTE, *PFILEATTRIBUTE;


#pragma pack(1)
#define APPFILE 0x7430
#define ALG_SSF33	1
#define ALG_SM1		2

#define TRANS_TYPE_PUBKEY_SKF2HS	1
#define TRANS_TYPE_PUBKEY_HS2SKF	2
#define TRANS_TYPE_PRIKEY_SKF2HS	3
#define TRANS_TYPE_PRIKEY_HS2SKF	4

#define ALG_SM3		0x40
//#define ALG_SHA1	0x80  syc
//#define ALG_SHA256	0x100  syc
#define ALG_MD5		0x8003

#define  SGD_SM3 0x00000001 //SM3�Ӵ��㷨 
#define  SGD_SHA1 0x00000002 //SHA1�Ӵ��㷨 
#define  SGD_SHA256 0x00000004 //SHA256�Ӵ��㷨 
//#define  SGD_SHA1   32772 //SHA1�Ӵ��㷨�������ʱ�׼  syc
 
// �汾
typedef struct Struct_HT_Version{
	BYTE major;		//���汾��
	BYTE minor;		//�ΰ汾��
}HT_VERSION;


// �豸��Ϣ
typedef struct Struct_HT_DEVINFO{
	HT_VERSION Version;
	CHAR Manufacturer[64];
	CHAR Issuer[64];
	CHAR Label[32];
	CHAR SerialNumber[32];
	HT_VERSION HWVersion;
	HT_VERSION FirmwareVersion;
	ULONG AlgSymCap;
	ULONG AlgAsymCap;
	ULONG AlgHashCap;
	ULONG DevAuthAlgId;
	ULONG TotalSpace;
	ULONG FreeSpace;
	BYTE Reserved[64];
}HT_DEVINFO, *HT_PDEVINFO;


typedef struct HT_IndexSt
{
	DWORD dwID;
	char szName[32];
}HT_INDEXFILETABLE, *HT_PINDEXFILETABLE;


// �豸��ʼ����Ϣ�豸���ͣ�
typedef struct Struct_HT_DEVINITINFO
{
	HT_VERSION AppVersion;
	CHAR Manufacturer[64];	//�豸������Ϣ,�64���ַ�������64���ַ��Կհ��ַ�(ASCII��Ϊ0xFF)��䣬������null��0x00��������
	CHAR Label[64];	//SIC/SZD��ǩ,�64���ַ�������64���ַ��Կհ��ַ�(ASCII��Ϊ0xFF)��䣬������null��0x00��������
}HT_DEVINITINFO,*HT_PDEVINITINFO;


// RSA��Կ�������ݿ�
typedef struct Struct_HT_RSAPUBLICKEYBLOB{
	ULONG	AlgID;
	ULONG	BitLen;
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];
}HT_RSAPUBLICKEYBLOB, *HT_PRSAPUBLICKEYBLOB;

// RSA˽Կ�������ݿ�
typedef struct Struct_HT_RSAPRIVATEKEYBLOB{
	ULONG	AlgID;
	ULONG	BitLen;
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];
	BYTE	PrivateExponent[MAX_RSA_MODULUS_LEN];
	BYTE	Prime1[MAX_RSA_MODULUS_LEN/2];
	BYTE	Prime2[MAX_RSA_MODULUS_LEN/2];
	BYTE	Prime1Exponent[MAX_RSA_MODULUS_LEN/2];
	BYTE	Prime2Exponent[MAX_RSA_MODULUS_LEN/2];
	BYTE	Coefficient[MAX_RSA_MODULUS_LEN/2];
}HT_RSAPRIVATEKEYBLOB, *HT_PRSAPRIVATEKEYBLOB;


// ECC��Կ�������ݿ�
typedef struct Struct_HT_ECCPUBLICKEYBLOB{
	ULONG	BitLen;
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];
}HT_ECCPUBLICKEYBLOB, *HT_PECCPUBLICKEYBLOB;

// ECC˽Կ�������ݿ�
typedef struct Struct_HT_ECCPRIVATEKEYBLOB{
	ULONG	BitLen;
	BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];
}HT_ECCPRIVATEKEYBLOB, *HT_PECCPRIVATEKEYBLOB;


// ECC�������ݽṹ
typedef struct Struct_HT_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  Hash[32];
	ULONG CipherLen;
	BYTE  Cipher[256];
}HT_ECCCIPHERBLOB, *HT_PECCCIPHERBLOB;


// ECCǩ�����ݽṹ
typedef struct Struct_HT_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}HT_ECCSIGNATUREBLOB, *HT_PECCSIGNATUREBLOB;


typedef struct SKF_HT_ENVELOPEDKEYBLOB{
	ULONG Version;                  // ��ǰ�汾Ϊ 1
	ULONG ulSymmAlgID;              // �淶�е��㷨��ʶ���޶�ECBģʽ
	ULONG ulBits;					// ������Կ�Ե���Կλ����
	BYTE cbEncryptedPriKey[64];     // ���ܱ����ļ���˽Կ
	HT_ECCPUBLICKEYBLOB PubKey;        // ���ܹ�Կ
	HT_ECCCIPHERBLOB HT_ECCCIPHERBLOB;    // SM2 ��Կ���ܵ���Կ������Կ
}HT_ENVELOPEDKEYBLOB, *HT_PENVELOPEDKEYBLOB;

// �����������
typedef struct Struct_HT_BLOCKCIPHERPARAM{
	BYTE	IV[MAX_IV_LEN];
	ULONG	IVLen;
	ULONG	PaddingType;
	ULONG	FeedBitLen;
} HT_BLOCKCIPHERPARAM, *HT_PBLOCKCIPHERPARAM;

// �ļ�����
typedef struct Struct_HT_FILEATTRIBUTE{
	CHAR	FileName[32];
	ULONG	FileSize;
	ULONG	ReadRights;
	ULONG	WriteRights; 
}HT_FILEATTRIBUTE, *HT_PFILEATTRIBUTE;
#pragma pack()



//�豸����������9��
/****************************************************************************************************/
//�ȴ��豸����¼�
//�����������ú����ȴ��豸����¼��� szDevName�����¼����豸����
//                 
//������    
//          szDevName     [IN]      ��������������¼����豸����
//          ulDevNameLen  [IN/OUT]  �������������/���������������ʱ��ʾ���������ȣ����ʱ��ʾ�豸���Ƶ���Ч���ȣ����Ȱ����ַ�����������
//          pulEvent      [OUT]     �¼�����  1 ��ʾ���룬2 ��ʾ�γ�
//����ֵ��  SAR_OK��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ���£�
//          SAR_UNKNOWNERR����δ֪����
//          SAR_MEMORYERR�����ڴ����
//          SAR_TIMEOUTERR�ȴ���ʱ��
//          SAR_NOT_EVENTERR���¼�����
//          SAR_INVALIDPARAMERR������Ч�� 
//��ע��    �ޡ�
ULONG DEVAPI SKF_WaitForDevEvent(							
								 OUT      LPSTR   szDevName,
								 IN OUT  ULONG   ulDevNameLen,
								 OUT     ULONG   *pulEvent
								 );

/****************************************************************************************************/								 
//����  : �ú���ȡ���ȴ��豸������߰γ��¼�
//����
//����ֵ: SAR_OK: �ɹ�
//����  : ������
ULONG DEVAPI SKF_CancelWaitForDevEvent();


/****************************************************************************************************/
//ö���豸
//�����������ú���ö�ٵ�ǰ����֧�ֵ������豸�б���ߵ�ǰ״̬Ϊ���ڵ��豸��
//          ͨ���ú�����������õ�ǰϵͳ���豸�б�������
//          �ڽ����豸����ǰ��Ҫ�øú����ж��豸�Ƿ���ڡ�
//������    bPresent      [IN] ���������Ϊ 1 ��ʾȡ��ǰ�豸״̬Ϊ���ڵ��豸�б�Ϊ 0 ��ʾȡ��ǰ����֧�ֵ��豸�б�
//          szNameList    [OUT] ����������豸�����б��ò���Ϊ�գ�����pulSize������Ҫ���ڴ�ռ�Ĵ�С,����豸֮����'\0'�ָ����
//          pulSize       [IN OUT ] ��������������豸�����б�Ļ��������ȣ��������������pszeNameList��Ҫ�Ŀռ��С��
//����ֵ��  SAR_OK��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR����δ֪����
//          SAR_MEMORYERR�����ڴ����
//          SAR_BUFFER_TOO_SMALL ���治���� 
//��ע��    ʹ�� DEVAPI Ӧ���ڷ����豸ǰ���ȵ��øú�����
ULONG DEVAPI SKF_EnumDev(
						 IN      BOOL   bPresent,
						 OUT     LPSTR  szNameList,
						 IN OUT  ULONG  *pulSize
				        );

/*****************************************************************************************************/
//�����豸
//���������� ͨ���豸���������豸�������豸�ľ����
//           �����豸�������Ƕ��豸�������������ĵ�һ���������豸�ɹ��󣬿��Զ��豸��������ָ����紴���ļ���
//           ��д�ļ��ȵȡ�Ϊ�˽�ʡ���豸֮���ͨѶ�ٶȣ�һ����������һ���豸�󣬾����ܶ�Ľ��иô����ӵ�����������
//           Ȼ���ٶ��豸���ú����Թ���ķ�ʽ�����豸��һ��Ӧ�����Ӻ�����Ӧ�û����������豸�����һ��Ӧ������豸���ж�
//           ռ���������������豸�󣬵��ÿ�ʼͬ����������SKF_LockDev ��
//������     pszName   [IN]  �������,�豸���ơ�
//           phDEV     [OUT] �������,�豸��������� 
//����ֵ��   SAR_OK��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//           ������������ֵ��
//           SAR_NAMELENERR �豸���ƴ���
//           SAR_UNKNOWNERR ����δ֪����
//           SAR_MEMORYERR �����ڴ����
//           SAR_DEVICE_REMOVED �豸���Ƴ���
//��ע��     ʹ��API�㷨��������ļ�������֮ǰ���á�
ULONG DEVAPI SKF_ConnectDev(
							IN  LPSTR     szName,
							OUT DEVHANDLE *phDev
						   );


/*****************************************************************************************************/
//�Ͽ��豸
//�����������Ͽ�һ���Ѿ����ӵ��豸�����öϿ��豸�����ɹ��󣬸��豸�˴����ӵľ��ʧЧ�����ϣ�����¶��豸���в��������������豸��
//          �Ͽ����Ӳ�������Ӱ���豸��Ȩ��״̬��Ҳ�����ͷ�Ӧ�ö��豸��ͬ��״̬����һ��Ҫ�ر�ע��!       
//������    hDev  [IN] ��������������豸���ص��豸�����
//����ֵ��  SAR_OK��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_DEVICE_REMOVED �豸���Ƴ���
//��ע��    �Ͽ��豸�����豸�ε������Զ�ʧЧ��
ULONG DEVAPI SKF_DisConnectDev(
							   IN DEVHANDLE hDev
						      );


/****************************************************************************************************/
//�ж��豸״̬
//�����������ж��豸�Ƿ������ϵͳ�У����Է���DEV_PRESENT_STATE����DEV_EMPTY_STATE��
//          
//������    szDevName   [IN]   ����������������ơ�
//          pulDevState [OUT]  ������������ص��豸״̬��
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//��ע��    �ޡ�
ULONG DEVAPI SKF_GetDevState ( 
							  IN  LPSTR   szDevName, 
							  OUT ULONG   *pulDevState
							  );	

/****************************************************************************************************/
//�����豸��ǩ
//�������� �����豸��ǩ��
//          
//������    hDev   [IN]   �����豸ʱ���ص��豸�����
//          szLabel[IN]   �豸��ǩ�ַ��������ַ���ӦС��32�ֽڡ�            
//����ֵ��  SAR_OK ��ʾ�ɹ���
//          ������������ֵ��
//��ע��    ��
ULONG  DEVAPI SKF_SetLabel ( 
							   IN  DEVHANDLE hDev, 
							   IN  LPSTR     szLabel
							   );	

/**************************************************************************************************/
//��ȡ�豸��Ϣ
//������������ȡ�豸��һЩ�ض���Ϣ�������豸�ı�־��������Ϣ������ĳ��ȷ�Χ��֧�ֵ��㷨�ȡ�
//������    hDev      [IN]  ��������������豸���ص��豸�����
//          pDevInfo  [OUT] ��������������豸��Ϣ�� 
//����ֵ��  SAR_OK ��ʾ�ɹ��� SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_DEVICE_REMOVED �豸���Ƴ���
//          SAR_BUFFER_TOO_SMALL ���治�㣻
//��ע��    ��                
ULONG DEVAPI SKF_GetDevInfo(
							IN  DEVHANDLE   hDev,
							OUT DEVINFO     *pDevInfo
						   );

/*******************************************************************************************/
//�����豸�� ��ʼͬ��������
//���ܹ�������ͨ�����øú��������ö��豸�Ķ�ռȨ����������Ӧ�ö��豸�Ĳ�����
//            �ú������óɹ�������Ӧ���ٵ��������豸����ʱ�ᴦ�ڵȴ�״̬��һֱ����Ӧ���ͷ��˶�ռȨ��
//            �ú����ܺõĽ���˶������֮��ͬʱ���豸���ʴ�������⡣
//            ��һ��Ӧ�ý����˶��豸�Ĵ����һ��Ҫ���ý���ͬ����������������ᵼ������Ӧ�ò����������豸��
//            �������Ӧ������Ӧ״̬��
//            �ú������ͷ��豸����һ��Ҫ�ɶԳ��֡�
//������      hDev      [IN]  ��������������豸���ص��豸�����
//����ֵ��    SAR_OK ��ʾ�ɹ��� SAR_FAIL ����ʧ�ܡ�
//            �������������룺
//            SAR_UNKNOWNERR ����δ֪����
//            SAR_DEVICE_REMOVED �豸���Ƴ���
//��ע:       �Ͽ��豸�����豸�ε�֮���ͷ�ͬ����Դ��
ULONG DEVAPI SKF_LockDev(
						 IN  DEVHANDLE   hDev,
						 IN  ULONG       ulTimeOut
						);
	

/******************************************************************************************/
//�ͷ��豸�� ����ͬ��������
//�������������øú�����Ӧ�ý����Ը��豸�Ķ�ռ״̬����û�жϿ����豸������
//          ���һ��Ӧ�õ����˿�ʼͬ�����������������ڲ���������û�е��ý���ͬ������������
//          �ᵼ������Ӧ�ö��豸����ʱ�������޵ȴ�״̬��
//          �ú���Ҫ�뿪ʼ�����豸�������ɶԳ��֡�
//������    hDev      [IN]  ��������������豸���ص��豸�����
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          �������������룺
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//��ע��    �Ͽ��豸�����豸�ε������Զ�ʧЧ��
ULONG DEVAPI SKF_UnLockDev(
						   IN  DEVHANDLE   hDev
						  );  


/******************************************************************************************/
//�豸�����
//����: ������ֱ�ӷ����豸,�����ؽ��
//����: hDev        [IN]    �豸���
//      pbCommand   [IN]    �豸����
//      ulCommandLen[IN]    �����

ULONG DEVAPI SKF_Transmit( 
						  DEVHANDLE hDev, 
						  BYTE  * pbCommand, 
						  ULONG ulCommandLen,
						  BYTE  * pbData,
						  ULONG *pulDataLen
						  );


/***********************************************************/
//���ʿ���
//����: �����豸��֤��Կ
//����: hDev        [IN]    �豸���
//      pbKeyValue  [IN]    ��Կֵ
//      ulKeyLen    [IN]    ��Կ����
//����ֵ:SAR_OK     �ɹ�
//����  :������
//��ע  :Ȩ��Ҫ��:�豸��֤�ɹ������ʹ��
ULONG DEVAPI SKF_ChangeDevAuthKey( 
						  DEVHANDLE hDev, 
						  BYTE  * pbKeyValue, 
						  ULONG ulKeyLen
						  );


/***********************************************************/
//����: �豸��֤
//����: hDev        [IN]    �豸���
//      pbAuthData  [IN]    ��֤����
//      ulLen       [IN]    ��֤���ݳ���
//����ֵ:SAR_OK     �ɹ�
//����  :������

ULONG DEVAPI SKF_DevAuth( 
						 DEVHANDLE hDev, 
						 BYTE  * pbAuthData, 
						 ULONG ulLen
						 );

/******************************************************************************************/
//�޸�PIN
//�����������ú����ܹ��޸�Admin PIN ��User PIN��ֵ�� ֻ��֪��ԭAdmin PIN ����User PIN���˲����޸ġ�
//          ����޸Ĳ��ɹ����ú�������Admin PIN����User PIN��ʣ���������ʣ�����Ϊ0ʱ�򣬱�ʾ��PIN�Ѿ�������
//������      
//            hApplication  [IN]  ���������Ӧ�þ����
//            ulPINType     [IN]  ���������PIN���� ADMIN_TYPE=0����USER_TYPE=1�� 
//            szOldPin      [IN]  ԭPINֵ
//            szNewPin      [IN]  ��PINֵ
//            pulRetryCount [OUT] ��������Դ���
//����ֵ��    SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//            ������������ֵ��
//            SAR_MEMORYERR �����ڴ����
//            SAR_UNKNOWNERR ����δ֪����
//            SAR_PIN_INCORRECT PIN����
//            SAR_PIN_INVALID PIN��Ч��
//            SAR_PIN_LEN_RANGE PIN���ȴ���
//            SAR_PIN_LOCKED PIN������
//            SAR_INVALIDHANDLEERR �����Ч��
//��ע��      ��
ULONG DEVAPI SKF_ChangePIN(						  
						   IN  HAPPLICATION  hApplication,
						   IN  ULONG         ulPINType,
						   IN  LPSTR         szOldPin,
						   IN  LPSTR         szNewPin,
						   OUT ULONG         *pulRetryCount
						  );

/***********************************************************/
//����: ��ȡPIN��Ϣ
//����: hApplication           [IN]     ���������Ӧ�þ����
//      ulPINType              [IN]     PIN����
//      pulMaxRetryCount       [OUT]    ������Դ���
//      pulRemainRetryCount    [OUT]    ��ǰʣ�����Դ�������Ϊ0ʱ��ʾ������
//      pbDefaultPin           [OUT]    �Ƿ�Ϊ����Ĭ��PIN��
//����ֵ:SAR_OK     �ɹ�
//����  :������

ULONG DEVAPI SKF_GetPINInfo(
							IN  HAPPLICATION hApplication,
							IN  ULONG  ulPINType,
							OUT ULONG *pulMaxRetryCount,
							OUT ULONG *pulRemainRetryCount,
							OUT BOOL  *pbDefaultPin
							);

/******************************************************************************************/
//У�����
//����������У�� Admin PIN ���� User PIN ��У��ɹ��󣬻�����Ӧ��Ȩ�ޣ��������ʧ�ܣ��᷵��������Դ�����
//          ����������Դ���Ϊ0ʱ�����������Ѿ���������
//������    
//          hApplication  [IN]  ���������Ӧ�þ����
//          ulUserType    [IN]  �û�����  ADMIN����USER
//          szPIN         [IN]  PINֵ
//          pulRetryCount [OUT] ����󷵻����Դ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_PIN_INCORRECT PIN����
//          SAR_PIN_INVALID PIN��Ч��
//          SAR_PIN_LEN_RANGE PIN���ȴ���
//          SAR_PIN_LOCKED PIN������
//          SAR_USER_ALREADY_LOGGED_IN PIN�Ѿ����Ȩ�ޣ�
//          SAR_USER_PIN_NOT_INITIALIZED PINΪ��ʼ������
//          SAR_USER_TYPE_INVALID PIN���ʹ���
//          SAR_INVALIDHANDLEERR �����Ч��
//��ע��    ��
ULONG DEVAPI SKF_VerifyPIN(                        
						   IN  HAPPLICATION  hApplication,
						   IN  ULONG         ulUserType,
						   IN  LPSTR         szPIN,
						   OUT ULONG         *pulRetryCount
						  );

/******************************************************************************************/
//�����û�PIN
//���ܹ����������û����������󣬵��øú����������û����ֻ��֪��Admin PIN���ܽ����û�����������Admin PIN
//            ��������Ѿ������������ʧ�ܣ�������Admin PIN���Դ������������û��������Ϊ��ֵ�����Դ���Ҳ�ָ���ԭֵ��
//������    
//          hApplication  [IN]  ���������Ӧ�þ����
//          szAdminPIN    [IN]  ����ԱPIN
//          szNewUserPIN  [IN]  ��ͨ�û���PIN
//          pulRetryCount [OUT] ��������Դ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ:
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_PIN_INCORRECT PIN����
//          SAR_PIN_INVALID PIN��Ч��
//          SAR_PIN_LEN_RANGE PIN���ȴ���
//          SAR_PIN_LOCKED PIN������
//          SAR_USER_PIN_NOT_INITIALIZED PINΪ��ʼ������
//          SAR_INVALIDHANDLEERR �����Ч��
//��ע��    ��
ULONG DEVAPI SKF_UnblockPIN(							
							IN  HAPPLICATION  hApplication,
							IN  LPSTR         szAdminPIN,
							IN  LPSTR         szNewUserPIN,
							OUT ULONG         *pulRetryCount
						   );


/******************************************************************************************/
//�����ȫ״̬
//����������ͨ�����øú�������Ӧ��֮ǰ�������Ȩ�ޣ�����У��Admin PIN User PIN�Լ��ⲿ��֤��õ�Ȩ��ȫ���������
//          ִ���������ȫ״̬�󣬵�ǰ·���ָ����豸��Ŀ¼��
//������    
//          hApplication    [IN]  ���������Ӧ�þ����
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//��ע��    ��
ULONG DEVAPI SKF_ClearSecureState(
								  
								  IN HAPPLICATION  hApplication
								 );



/*****************************************************************************************/
/*
Ӧ�ù�����  
*/
/*****************************************************************************************/

//����Ӧ�ú���
//��������������һ��Ӧ�ã�������Ӧ�õ�����
//          һ���豸���Դ������Ӧ�á�
//          ��Ӧ���£����Դ���һ������Ӧ��֤�飬Ӧ���ļ���
//������   hDev              [IN]  ��������������豸���ص��豸�����       
//         szAppName         [IN]  Ӧ������
//         szAdminPin        [IN]  ����ԱPIN
//         dwAdminPinRetryCount [IN] ����ԱPIN��������Դ���
//         szUserPin         [IN]  �û�PIN
//         dwUserPinRetryCount [IN]�û�PIN��������Դ���
//         dwCreateFileRights  [IN]�ڸ�Ӧ���´����ļ���������Ȩ��
//         phApplication     [OUT] Ӧ�õľ��
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MMEORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//         SAR_INVALIDHANDLEERR �����Ч��
//         SAR_APPLICATION_NAME_INVALID Ӧ��������Ч��
//         SAR_APPLICATION_EXISTS Ӧ���Ѿ����ڡ�
//��ע��   �ޡ�
ULONG DEVAPI SKF_CreateApplication(
                                   IN  DEVHANDLE     hDev,
								   IN  LPSTR         szAppName,
								   IN  LPSTR         szAdminPin,
								   IN  DWORD         dwAdminPinRetryCount,
								   IN  LPSTR         szUserPin,
								   IN  DWORD         dwUserPinRetryCount,
								   IN  DWORD		 dwCreateFileRights,
								   OUT HAPPLICATION  *phApplication												  
							      );

/******************************************************************************************/
//ö��Ӧ�ú���
//����������ö�ٴ��ڵ�����Ӧ�á�
//������   hDev              [IN]  ��������������豸���ص��豸�����       
//         szAppName         [OUT] �������������Ӧ�����ƣ��ò���Ϊ�գ�����pulSize��������Ҫ���ڴ�ռ��С��
//         pulSize           [IN��OUT]  �������������Ӧ�����ƵĻ���������
//                                      �������������szAppName����Ҫ�Ŀռ��С��
//                                      ÿ��Ӧ�õ������Ե���NULL��������˫NULL��ʾ�б�Ľ�����
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MMEORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//��ע��   �ޡ�
ULONG DEVAPI SKF_EnumApplication(
                                 IN      DEVHANDLE     hDev,
								 OUT     LPSTR         szAppName,
								 IN OUT  ULONG         *pulSize					
							    );

/******************************************************************************************/
//ɾ��Ӧ�ú���
//����������ɾ��һ��Ӧ�ã���Ҫ���㰲ȫȨ�ޣ����ܹ�ɾ����
//������   hDev              [IN]  ��������������豸���ص��豸�����       
//         szAppName         [IN]  Ӧ������
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MMEORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//         SAR_USER_NOT_LOGGED_IN ��δУ���û�PIN;
//         SAR_APPLICATION_NOT_EXISTS Ӧ�ò����ڡ�
//��ע��   �ޡ�
ULONG DEVAPI SKF_DeleteApplication(
                                   IN  DEVHANDLE     hDev,
								   IN  LPSTR         szAppName
							      );



/******************************************************************************************/
//��Ӧ�ú���
//������������Ӧ��
//������   hDev              [IN]  ��������������豸���ص��豸�����       
//         szAppName         [IN]  Ӧ������
//         phApplication     [OUT] Ӧ�õľ��
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MMEORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//         SAR_APPLICATION_NOT_EXISTS Ӧ�ò����ڡ�
//��ע��   �ޡ�
ULONG DEVAPI SKF_OpenApplication(
                                 IN  DEVHANDLE     hDev,
								 IN  LPSTR         szAppName,
								 OUT HAPPLICATION  *phApplication
							    );

/******************************************************************************************/
//�ر�Ӧ�ú���
//�����������ر�Ӧ��             
//����       phApplication     [IN]  Ӧ�õľ��
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MMEORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//         SAR_USER_NOT_LOGGED_IN ��δУ���û�PIN;
//         SAR_INVALIDHANDLEERR �����Ч��
//��ע��   �ޡ�
ULONG DEVAPI SKF_CloseApplication(								 
								  IN  HAPPLICATION  phApplication
							      );


/*****************************************************************************************/
/*
�ļ�������  
*/
/*****************************************************************************************/
//�����ļ�
//���ܹ�����������һ��Ӧ���ļ���
//            �����ļ�Ҫָ���ļ������ͣ����ƣ���С���Լ��ļ��Ķ�дȨ�ޡ� 
//            �ļ������󣬴�С�����Ըı䣬����ɾ����  
//������   hApplication       [IN]  Ӧ�þ��
//         szFileName         [IN]  �ļ�����
//         ulFileSize         [IN]  �ļ���С
//         ulReadRights       [IN]  �ļ���Ȩ��
//         ulWriteRights      [IN]  �ļ�дȨ��
//����ֵ�� SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//         ������������ֵ��
//         SAR_MEMORYERR �����ڴ����
//         SAR_UNKNOWNERR ����δ֪����
//         SAR_USER_NOT_LOGGED_IN ��δУ���û�PIN��
//         SAR_INVALIDHANDLEERR �����Ч��
//         SAR_FILEERR �ļ�����
//         SAR_NAMELENERR �ļ����Ƴ��ȴ���
//         SAR_FILE_ALREADY_EXIST �ļ��Ѿ����ڣ�
//         SAR_NO_ROOM ʣ��ռ䲻����
//��ע��   ulAcceccCondition                        ����Ȩ��ֵ�μ����豸Ȩ�����͡�
//         bit32 �� bit25   ������ı����ֽڣ�0xFF��
//         bit24 �� bit17   ������ı����ֽڣ�0xFF��
//         bit16 �� bit9    ��Ȩ�ޣ����˻����ļ�Ҫ�����Ȩ�ޣ�
//         bit8  �� bit1    дȨ�ޣ�д�˻����ļ�Ҫ�����Ȩ�ޡ�
ULONG DEVAPI SKF_CreateFile(                   
							IN HAPPLICATION  hApplication,
                            IN LPSTR         szFileName,
						    IN ULONG         ulFileSize,						 
                            IN ULONG         ulReadRights,
							IN ULONG         ulWriteRights
						   );


/******************************************************************************************/
//ɾ���ļ�
//����������ɾ���ļ����ļ���д������ݽ���ʧ���ļ����豸ռ�õĿռ佫�ͷš� 
//          ɾ��һ���Ѿ��������ļ���
//������    hApplication       [IN]  Ҫɾ���ļ����ڵ�Ӧ�þ����
//          szFileName         [IN]  Ҫɾ���ļ�����
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_USER_NOT_LOGGED_IN ��δУ���û�PIN��
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_FILEERR �ļ�����
//��ע��    ��
ULONG DEVAPI SKF_DeleteFile(                    
						    IN HAPPLICATION  hApplication,
                            IN LPSTR         szFileName
						   );


/******************************************************************************************/
//ö���ļ�
//����������ö��һ��Ӧ���´��ڵ������ļ��� 
//������    hApplication   [IN]  Ӧ�þ����
//          szFileList     [OUT] �����ļ����ƣ�����ò���Ϊ�գ���pulSize������Ҫ�Ļ�������С��
//                               ����ļ�֮����NULL��������˫NULL��ʾ�б�Ľ�����
//          pulSize        [IN OUT] ����Ϊ���ݻ������Ĵ�С�����Ϊʵ���ļ����ƴ�С��
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_EnumFiles(						   
						   IN     HAPPLICATION  hApplication,
						   OUT    LPSTR         szFileList,
						   IN OUT ULONG         *pulSize						 
						   );

/******************************************************************************************/
//��ȡ�ļ�������Ϣ
//������������ȡӦ���ļ���������Ϣ�������ļ��Ĵ�С��Ȩ�޵ȡ�
//������    hApplication       [IN]  �ļ�����Ӧ�õľ��
//          szFile             [IN]  �ļ�����
//          pFileInfo          [OUT] �ļ���Ϣ��ָ���ļ����Խṹ��ָ�롣
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_FILEERR �ļ�����
//          SAR_FILE_NAME_INVALID �ļ�������Ч��
//��ע��    ��
ULONG DEVAPI SKF_GetFileInfo(
						     IN  HAPPLICATION    hApplication,
                             IN  LPSTR           szFile,
							 OUT FILEATTRIBUTE   *pFileInfo
							);



/******************************************************************************************/
//���ļ�
//������������Ӧ���ļ��е����ݣ����ڸմ������ļ����ú���Ҳ�ܵ��óɹ����������������ļ���ԭ�е�
//          Ĭ������ֵ������һ��Ӧ���ļ�����Ҫ�������д������Ȼ����ܶ�����ȷ�����ݡ�
//������    
//          hApplication       [IN]  Ӧ�þ��
//          szFile             [IN]  �ļ���
//          ulOffset           [IN]  ���ļ���Ҫ��ƫ����
//          ulSize             [IN]  Ҫ��ȡ��������
//          pbOutData          [OUT] ���ص����ݻ�����
//          pulOutLen          [IN��OUT] ������������������ʾ���� �Ļ�������С�������ʾʵ�ʶ�ȡ���ص����ݴ�С
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_FILEERR �ļ�����
//          SAR_READFILEERR ���ļ�����
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_ReadFile(                      
						  IN     HAPPLICATION  hApplication,
                          IN     LPSTR         szFile,
						  IN     ULONG         ulOffset,
						  IN     ULONG         ulSize,
						  OUT    BYTE          *pbOutData,
						  IN OUT ULONG         *pulOutLen
						 );


/******************************************************************************************/
//д�ļ�
//����������д���ݵ�Ӧ���ļ��С������������ļ��е�ƫ��������Ч���ݵĳ�����д�������м�¼������
//          �ڶ����ݽ��ж�����ʱ����ܶ�����Ч�����ݡ�
//������    
//          hApplication       [IN]  Ӧ�þ��
//          szFile             [IN]  �ļ���
//          ulOffset           [IN]  д�ļ���Ҫ��ƫ����
//          pbData             [IN]  д�����ݵĻ�������
//          ulSize             [IN]  д�����ݵĴ�С
//          pulLen             [OUT] ʵ��д�����ݵĴ�С
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_FILEERR �ļ�����
//          SAR_WRITEFILEERR д�ļ�����
//          SAR_FILE_NOT_EXIST �ļ������ڣ�
//          SAR_DATA_LEN_RANGE ���ݳ��ȴ���
//��ע��    ��
ULONG DEVAPI SKF_WriteFile(                         
				 		   IN  HAPPLICATION  hApplication,
                           IN  LPSTR         szFile,
						   IN  ULONG         ulOffset,
						   IN  BYTE          *pbData,
						   IN  ULONG         ulSize
                          );

/*****************************************************************************************/
/*
����������  
*/
/*****************************************************************************************/
//��������
//���ܹ������� ������Կ��������Կ��������Կ���һ���֣�һ����Կ��������ĳ���ض��û������зǶԳ�
//             ��Կ��ǩ����Կ�ԣ�������Կ�ԡ�ǩ����Կ����������ǩ������֤����ǩ����������Կ������
//             ���ܺͽ��ܣ�ͨ�����ڼ��ܺͽ��ܻỰ��Կ��������Կ������ʱ��ҪΪÿ����Կ����ָ��Ψһ
//             �����ƣ������ɹ��󷵻�ָ����Կ������ָ�롣  
//������     
//             hApplication       [IN]  Ӧ�þ��
//             szContainer       [IN]  ��������
//             phContainer         [OUT] ���ص��������
//����ֵ��     SAR_OK ��ʾ�ɹ��� SAR_FAIL ����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_NAMELENERR ���Ƴ��ȴ���
//��ע��       ��
ULONG DEVAPI SKF_CreateContainer(							     
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR         szContainer,
								 OUT HCONTAINER    *phContainer
								 );



/******************************************************************************************/
//ɾ����Կ����
//���ܹ������� ��Ӧ����ɾ��ָ�����Ƶ��������ͷ�������ص���Դ
//������       hApplication    [IN]  Ӧ�þ��
//             szContainerName [IN]  ָ��ɾ������������ 
//����ֵ��     SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//��ע��       ��
ULONG DEVAPI SKF_DeleteContainer(
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR    szContainerName
								 );
/******************************************************************************************/
//������
//���ܹ�����: ��ȡ�������
//����:     hApplication    [IN]  Ӧ�þ��
//          szContainerName [IN]  ��������
//          phContainer     [OUT] ���ش������ľ��
//����ֵ:   SAR_OK      : �ɹ�
//          ���� :        ������
ULONG DEVAPI SKF_OpenContainer(
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR    szContainerName,
								 OUT HCONTAINER    *phContainer
								 );

/******************************************************************************************/
//�ر�����
//���ܹ�����: �ر��������,����ȡ������������Դ
//����:     hContainer     [IN] �����ľ��                 
//����ֵ:   SAR_OK      : �ɹ�
//          ���� :        ������

ULONG DEVAPI SKF_CloseContainer(
								HCONTAINER hContainer
								);


/******************************************************************************************/
//ö������
//�����������оٳ�ָ���������Դ��ڵ���Կ������
//������       
//             hApplication    [IN]      Ӧ�þ��
//             szContainerName     [IN]      �������������б��������֮����'\0'�ָ��� ��Ϊ��ʱ����pulSize������Ҫ�Ļ�������С���淶��û������˵������
//             pulSize         [IN OUT]  ����ʱ���������б�������С�����ʱ������Ҫ�Ļ�������С���淶��û������˵����˵���Ƿ����������ĳ���!��
//����ֵ��     SAR_OK��ʾ�ɹ��� SAR_FAIL����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��       ��
ULONG DEVAPI SKF_EnumContainer(							   
							   IN      HAPPLICATION  hApplication,
							   OUT     LPSTR         szContainerName,
							   IN OUT  ULONG         *pulSize       
		   					  );

/*****************************************************************************************/
/*
����������� 
//���ܹ�����:�������������
//����:     hContainer     [IN] �����ľ��  
//���Σ�    pulContainerType [OUT] ��������
//����ֵ:   SAR_OK      : �ɹ�
//          ���� :        ������
*/
/*****************************************************************************************/
ULONG DEVAPI SKF_GetContainerType(							   
							      HCONTAINER hContainer,
							      OUT  ULONG  *pulContainerType  
		   					  );

/*****************************************************************************************/
/*
��������֤��
//����:     hContainer     [IN] �����ľ��  
//����:     bSignFlag      [IN] ֤������ ��true��ʾǩ��֤�飬false��ʾ����֤�� 
//����:     pbCert         [IN] ָ��֤�����ݻ���  
//����:     ulCertLen      [IN] ֤�鳤��  
//
*/
/*****************************************************************************************/

ULONG DEVAPI SKF_ImportCertificate(
	                                HCONTAINER hContainer, 
	                                BOOL bSignFlag,  
	                                BYTE* pbCert, 
	                                ULONG ulCertLen);


/*****************************************************************************************/
/*
/*
��������֤��
//����:     hContainer     [IN] �����ľ��  
//����:     bSignFlag      [IN] ֤������ ��true��ʾǩ��֤�飬false��ʾ����֤�� 
//����:     pbCert         [OUT] ָ��֤�����ݻ���  
//����:     ulCertLen      [IN,OUT] ֤�鳤��  
//
*/
/*****************************************************************************************/

ULONG DEVAPI SKF_ExportCertificate(
	                                HCONTAINER hContainer, 
									BOOL bSignFlag, 
									BYTE* pbCert, 
									ULONG* ulCertLen);


/*
��Կ������  
*/
/*****************************************************************************************/
//���������
//����������������������� hDEV ���ָ����豸���������������������������������Ϊ ulRandomLen��
//          �õ�����������浽 pbRandomָ��Ļ�������
//������    hDev           [IN]  ��������������豸���ص��豸�����
//          pbRandom       [OUT] ���ص��������������
//          ulRandomLen    [IN]  ��Ҫ���ص���������ȡ�
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_GenRandom(
						   IN   DEVHANDLE  hDev,
                           OUT  BYTE       *pbRandom,
						   IN   ULONG      ulRandomLen
						   );


/*****************************************************************************************/
//
//���������������ⲿRSA��Կ��
//������    hDev           [IN]  ��������������豸���ص��豸�����
//          ulBitsLen      [IN]  ��Կģ��
//          pBlob          [IN]  ���ص�˽Կ���ݽṹ��
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_GenExtRSAKey(
							  IN    DEVHANDLE     hDev,
							  IN    ULONG         ulBitsLen,
							  OUT   RSAPRIVATEKEYBLOB    *pBlob
							  );


/******************************************************************************************/
//����RSAǩ����Կ��
//��������������RSAǩ����Կ�Բ����ǩ����Կ
//������                  
//             hContainer      [IN]  ��Կ���������          
//             ulBitLen        [IN]  ��˽Կ�Ե�ģ��
//             pBlob           [OUT] ���ص�RSA��Կ���ݽṹ
//����ֵ��     SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//             SAR_TIMEOUTERR ��ʱ��
//��ע��       Ȩ��Ҫ��: ��߱��û�Ȩ��
ULONG DEVAPI SKF_GenRSAKeyPair(
							   IN   HCONTAINER    hContainer,
							   IN   ULONG         ulBitLen,
                               OUT  RSAPUBLICKEYBLOB *pBlob
							   );

/******************************************************************************************/
/******************************************************************************************/
//��������������RSA������Կ��
//������       hContainer   [IN]  �������
//             ulSymAlgId   [IN]  �Գ��㷨��Կ��ʶ��
//             pbWrappedKey [IN]  ʹ�ø�������ǩ����Կ�����ĶԳ��㷨��Կ
//             ulWrappedKeyLen[IN]�����ĶԳ��㷨��Կ����
//             pbEncryptedData[IN]�Գ��㷨��Կ������RSA����˽Կ��˽Կ�ĸ�ʽ
//                  ��ѭPKCS#1V2.1:RSA Cryptography Standard�е�˽Կ��ʽ����				
//             ulEncryptedData[IN]�Գ��㷨��Կ������RSA���ܹ�˽Կ�Գ��ȡ�
//����ֵ��     SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//��ע��       ��
ULONG DEVAPI SKF_ImportRSAKeyPair(
                                  
								  IN   HCONTAINER    hContainer,
								  IN   ULONG         ulSymAlgId,
                                  IN   BYTE          *pbWrappedKey, 
								  IN   ULONG         ulWrappedKeyLen,
								  IN   BYTE          *pbEncryptedData,
								  IN   ULONG         ulEncryptedData
								  );

/******************************************************************************************/
//����������RSAǩ�� ʹ��hCountainerָ��������ǩ��˽Կ����ָ������pbData��������ǩ����ǩ�����
//�����ŵ�pbSignature������,����pulSignLenΪǩ���ĳ���
//����:   hContainer   [IN]  ����ǩ����˽Կ���ڵ�������Կ
//        pbData       [IN]  ��ǩ��������
//        ulDataLen    [IN]  ǩ�����ݵĳ��ȣ�Ӧ������RSA��Կģ��-11
//        pbSignature  [OUT] ���ǩ������Ļ�����ָ�룬���ֵΪNULL������ȡ��ǩ���������
//        pulSignLen   [IN OUT] ����Ϊǩ�������������С�����Ϊǩ���������
//����ֵ: SAR_OK:      �ɹ�
//        ����  :      ������
ULONG  DEVAPI SKF_RSASignData(
							  IN     HCONTAINER hContainer,
							  IN     BYTE *pbData,
							  IN     ULONG ulDataLen,
							  OUT    BYTE* pbSignature,
							  IN OUT ULONG *pulSignLen
							  );

/******************************************************************************************/
//��֤RSAǩ��
//������������RSA��Կ������ǩ��������ǩ����ԭʼ���ݶԱȣ�����ǩ���������ԭʼ������ͬ����˵
//          ��ǩ������Ч�ģ�����ǩ����Ч��
//������    hDev           [IN]  ��������������豸���ص��豸�����
//          pRSAPubKeyBlob [IN]  RSA ��Կ���ݽṹ
//          pbData         [IN]  ����֤ǩ��������
//          ulDataLen      [IN]  ���ݳ��ȣ������ڹ�Կģ��-11
//          pbSignature    [IN]  ����֤��ǩ��ֵ
//          ulSigLen       [IN]  ǩ��ֵ����,����Ϊ��Կģ�� 
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_MEMORYERR �����ڴ����
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_INVALIDHANDLEERR �����Ч��
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_KEYNOTFOUNTERR ��Կδ���֣�
//          SAR_INDATAERR �������ݴ���
//��ע��    ��
ULONG DEVAPI SKF_RSAVerify(
						   IN   DEVHANDLE     hDev,
						   IN   RSAPUBLICKEYBLOB *pRSAPubKeyBlob,						   						  
                           IN   BYTE          *pbData,
						   IN   ULONG         ulDataLen,
						   IN   BYTE          *pbSignature,
						   IN   ULONG         ulSigLen
						  );

/******************************************************************************************/
//�������������ɻỰ��Կ�����ⲿ��Կ�������
//������       hContainer    [IN]     �������
//             ulAlgId       [IN]     �Ự��Կ�㷨��ʶ
//             pPubKey       [IN]     ���ܻỰ��Կ��RSA��Կ���ݽṹ
//             pbData        [OUT]    �����ļ��ܻỰ��Կ���ģ�����PKCS#1V1.5Ҫ���װ��
//             pulDataLen    [IN OUT] ���ص������ݳ���
//             phSessionKey  [OUT]    ��������Կ���   
//����ֵ��     SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//             SAR_KEYNOTFOUNTERR ��Կδ���֡�
//��ע��       ��
ULONG DEVAPI SKF_RSAExportSessionKey(
								  IN      HCONTAINER     hContainer,
								  IN      ULONG          ulAlgId,
								  IN      RSAPUBLICKEYBLOB *pPubKey,								  
								  OUT     BYTE          *pbData,
								  IN OUT  ULONG         *pulDataLen,
                                  OUT     HANDLE  *    phSessionKey
								  );

/******************************************************************************************/
//����������RSA������Կ����,ʹ���ⲿ�����RSA��Կ��������������Կ���㲢������
//����:   hDev  [IN]  �豸���
//        pRSAPubKeyBlob  [IN] RSA��Կ���ݽṹ
//        pbInput         [IN] ָ��������ԭʼ���ݻ�����
//        ulInputLen      [IN] ������ԭʼ���ݵĳ��ȣ�����Ϊ��Կģ��
//        pbOutput        [IN] ָ��RSA��Կ����
//        pulOutputLen    [IN OUT]����ǰ��ʾpbOutput �������ĳ��ȣ�����RSA��Կ��������ʵ�ʳ���
//����ֵ: SAR_OK:      �ɹ�
//        ����  :      ������
ULONG  DEVAPI  SKF_ExtRSAPubKeyOperation(
										 IN   DEVHANDLE        hDev,					
										 IN   RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
										 IN   BYTE             *pbInput,
										 IN   ULONG            ulInputLen,
										 OUT  BYTE             *pbOutput,
										 OUT  ULONG            *pulOutputLen
										 );

/******************************************************************************************/
//����������RSA����˽Կ����,ʹ���ⲿ�����RSA˽Կ������������˽Կ���㲢������
//����:   hDev  [IN]  �豸���
//        pRSAPriKeyBlob  [IN] RSA˽Կ���ݽṹ
//        pbInput         [IN] ָ��������ԭʼ���ݻ�����
//        ulInputLen      [IN] ������ԭʼ���ݵĳ��ȣ�����Ϊ��Կģ��
//        pbOutput        [IN] ָ��RSA˽Կ���㣬�������ΪNULL������pulOutputLen������������ʵ�ʳ���
//        pulOutputLen    [IN OUT]����ǰ��ʾpbOutput �������ĳ��ȣ�����RSA˽Կ��������ʵ�ʳ���
//����ֵ: SAR_OK:      �ɹ�
//        ����  :      ������
ULONG  DEVAPI  SKF_ExtRSAPriKeyOperation(
										 IN   DEVHANDLE        hDev,					
										 IN   RSAPRIVATEKEYBLOB *pRSAPriKeyBlob,
										 IN   BYTE             *pbInput,
										 IN   ULONG            ulInputLen,
										 OUT  BYTE             *pbOutput,
										 OUT  ULONG            *pulOutputLen
										 );




/******************************************************************************************/
//���ܹ�������������Կ           
//������       hContainer    [IN]    �������
//             bSignFlag     [IN]    TRUE��ʾ����ǩ����Կ��FALSE��ʾ�������ܹ�Կ��
//             pbBlob        [OUT]   ָ��RSA��Կ�ṹ����ECC��Կ�ṹ������˲���ΪNULL��
//                                   ��pulBlobLen����pbBlob�ĳ��ȡ�
//             pulBlobLen    [IN,OUT]����ʱ��ʾpbBlob�ĳ��ȣ����ص�����Կ�ṹ�Ĵ�С
//����ֵ��     SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//             SAR_KEYNOTFOUNTERR ��Կδ���֡�
//��ע��       ��
ULONG DEVAPI SKF_ExportPublicKey(								
									IN      HCONTAINER    hContainer,
									IN      BOOL          bSignFlag,
									OUT     BYTE*          pbBlob,
									IN OUT  ULONG         *pulBlobLen
								  );

/******************************************************************************************/
//��������������Ự��Կ
//������       hContainer   [IN]  �������
//             ulAlgId      [IN]  �Ự��Կ�㷨��ʶ
//             pbWrapedData [IN]  Ҫ����ĻỰ��Կ����
//             ulWrapedLen  [IN]  �Ự��Կ���ĳ���
//             phKey        [OUT] ���ص���Կ���
//����ֵ��     SAR_OK ��ʾ�ɹ��� SAR_FAIL����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//��ע��       ��

ULONG DEVAPI SKF_ImportSessionKey(
								  IN   HCONTAINER     hContainer,
								  IN   ULONG          ulAlgId,
								  IN   BYTE           *pbWrapedData,
								  IN   ULONG          ulWrapedLen,
								  OUT  HANDLE         *phKey
								  );


/******************************************************************************************/
//�������������ĵ���Ự��Կ���������ĶԳ���Կ��������Կ���
//������       hDev         [IN]  �豸���
//             pbKey        [IN]  ָ��Ự��Կֵ�Ļ�����
//             ulAlgId      [IN]  �Ự��Կ�㷨��ʶ
//             phKey        [OUT] ���ػỰ��Կ���
//����ֵ��     SAR_OK ��ʾ�ɹ��� SAR_FAIL����ʧ�ܡ�
//             ������������ֵ��
//             SAR_MEMORYERR �����ڴ����
//             SAR_UNKNOWNERR ����δ֪����
//             SAR_INVALIDHANDLEERR �����Ч��
//             SAR_INVALIDPARAMERR ������Ч��
//��ע��       ��
ULONG  DEVAPI   SKF_SetSymmKey(
							   IN DEVHANDLE hDev,
							   IN BYTE * pbKey,
							   IN ULONG ulAlgId,
							   OUT HANDLE *phKey
							   );

/******************************************************************************************/
//���ݼ��ܳ�ʼ��
//�����������������ݼ��ܵ��㷨��ز�����
//������    hKey           [IN]  ������Կ���      
//          EncryptParam   [IN]  ���������㷨��ز�������ʱ��������ʱ�������ȡ�
//                               ��䷽ʽ������ֵ��λ���ȡ�
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_EncryptInit(					
							 IN   HANDLE             hKey,
							 IN   BLOCKCIPHERPARAM   EncryptParam
							 );



/******************************************************************************************/
//�������ݼ���
//������������һ�������ݵļ��ܲ�������ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ�����ֻ����
//һ�����飬���ܺ�����ı��浽ָ���Ļ������С�SKF_Encrypt ֻ�Ե����������ݽ��м��ܣ��ڵ���
//SKF_Encrypt֮ǰ���������SKF_EncryptInit��ʼ�����ܲ�����SKF_Encrypt�ȼ����ȵ���SKF_EncryptUpdate
//�ٵ���SKF_EncryptFinal��
//������    hKey            [IN]     ������Կ�����
//          pbData          [IN]     ����������
//          ulDataLen       [IN]     ���������ݳ���
//          pbEncryptedData [OUT]    ���ܺ�����ݻ�����ָ�룬����ΪNULL�����ڻ�ü��ܺ�����ݳ���
//          pulEncryptedLen [IN OUT] ���룬�����Ļ�������С����������ؼ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_Encrypt(
						 IN   HANDLE       hKey,				
						 IN   BYTE          *pbData,
						 IN   ULONG         ulDataLen,
						 OUT  BYTE          *pbEncryptedData,
						 OUT  ULONG         *pulEncryptedLen
						 );

/******************************************************************************************/
//�������ݼ��ܡ�
//������������ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ����
//          �������С��ڵ���SKF_EncryptUpdate֮ǰ���������SKF_EncryptInit��ʼ�����ܲ������ڵ���SKF_EncryptUpdate
//          ֮�󣬱������SKF_EncryptFinal�������ܲ�����         
//������    hKey            [IN]  ������Կ���
//          pbData          [IN]  ����������
//          ulDataLen       [IN]  ���������ݳ���
//          pbEncryptedData [OUT] ���ܺ����ݻ�����ָ��
//          pulEncryptedLen [OUT] ���ؼ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_EncryptUpdate(
							   IN   HANDLE        hKey,
							   IN   BYTE          *pbData,
							   IN   ULONG         ulDataLen,
							   OUT  BYTE          *pbEncryptedData,
							   OUT  ULONG         *pulEncryptedLen
							   );


/******************************************************************************************/
//��������
//������������������������ݵļ��ܣ�����ʣ����ܽ�����ȵ���SKF_EncryptInit��ʼ�����ܲ�����
//          �ٵ��ã�SKF_EncryptUpdate�Զ���������ݽ��м��ܣ�������SKF_EncryptFinal����
//          ����������ݵļ��ܡ�  
//������    hKey               [IN]  ������Կ���
//          pbEncryptedData    [OUT] ���ܺ����ݻ�����ָ��
//          ulEncryptedDataLen [OUT] ���ؼ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_EncryptFinal(							
							  IN   HANDLE        hKey,
							  OUT  BYTE          *pbEncryptedData,
							  OUT  ULONG         *ulEncryptedDataLen							
							  );

/******************************************************************************************/
//���ݽ��ܳ�ʼ��
//�������������ݽ��ܳ�ʱ�������ý�����Կ��ز���������SKF_DecryptInit֮�󣬿��Ե���SKF_Decrypt
//          �Ե����������ݽ��н��ܣ�Ҳ���Զ�ε���SKF_DecryptUpdate֮���ٵ���SKF_DecryPtFinal���
//          �Զ���������ݵĽ��ܡ�        
//������    hKey           [IN]  ������Կ���
//          DecryptParam   [IN]  ���������㷨��ز������㷨��־�š���Կ���ȡ���ʱ��������ʱ�������ȡ�
//                               ��䷽ʽ������ģʽ������ֵ��λ���ȡ�
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_DecryptInit(
							 IN   HANDLE             hKey,
							 IN   BLOCKCIPHERPARAM   DecryptParam
							 );


/******************************************************************************************/
//�������ݵĽ��ܲ�����
//������������ָ��������Կ��ָ�������ݽ��н��ܲ����������ܵ�����ֻ����һ�����飬���ܺ�����ݱ�����
//          һ��ָ���Ļ������С�SKF_Decryptֻ�Ե���������н��ܣ��ڵ���SKF_Decrypt֮ǰ���������SKF_DecryptInit
//          ��ʼ�����ܲ�����SKF_Decrypt�ȼ����ȵ���SKF_DecryptUpdate�ٵ���SKF_DecryptFinal��SKF_Decrypt������
//          SKF_DecryptUpdate������á�
  
//������    hKey            [IN]  ������Կ
//          pbEncryptedData [IN]  ����������
//          ulEncryptedLen  [IN]  ���������ݳ���
//          pbData          [OUT] ָ����ܺ�����ݻ�����ָ��
//          pulDataLen      [IN OUT] ���ؽ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��
ULONG DEVAPI SKF_Decrypt(			
						 IN    HANDLE        hKey,
						 IN    BYTE          *pbEncryptedData,
						 IN    ULONG         ulEncryptedLen,
						 OUT   BYTE          *pbData,
						 OUT   ULONG         *pulDataLen
						 );

/******************************************************************************************/
//�������ݵĽ��ܲ�����
//������������ָ��������Կ��ָ�����ݽ��н��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ����
//          �������С��ڵ���SKF_DecryptUpdate֮ǰ���������SKF_DecryptInit��ʼ�����ܲ������ڵ���SKF_DecryptUpdate
//          ֮�󣬱������SKF_DecryptFinal�������ܲ�����
       
//������    hKey            [IN]     ������Կ���
//          pbEncryptedData [IN]     ����������
//          ulEncryptedLen  [IN]     ���������ݳ���
//          pbData          [OUT]    ָ����ܺ�����ݻ�����ָ��
//          pulDataLen      [IN OUT] ���ؽ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_DecryptUpdate(							 
							   IN    HANDLE        hKey,
							   IN    BYTE          *pbEncryptedData,
							   IN    ULONG         ulEncryptedLen,
							   OUT   BYTE          *pbData,
							   OUT   ULONG         *pulDataLen
							   );


/******************************************************************************************/
//��������������ݵĽ���
//�����������ȵ���SKF_DecryptInit��ʼ�����ܲ������ٵ���SKF_DecryptUpdate�Զ���������ݽ��н��ܣ����
//          ����SKF_DecryptFinal��������������ݵĽ��ܡ�
//������    hKey              [IN]     ������Կ
//          pbDecryptData     [OUT]    ָ����ܺ�����ݻ�����ָ��
//          pulDecryptDataLen [IN OUT] ���ؽ��ܺ�����ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERT ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    ��
ULONG DEVAPI SKF_DecryptFinal(							 
							  IN      HANDLE        hKey,
							  OUT     BYTE          *pbDecryptedData,
							  IN OUT  ULONG         *pulDecryptedDataLen							
							 );


/******************************************************************************************/
//�Ӵճ�ʼ��
//������������ʼ����Ϣ�Ӵռ��������ָ��������Ϣ�Ӵյ��㷨��
//������    hDev            [IN]  ��������������豸���ص��豸�����
//          ulAlgID         [IN]  �Ӵ��㷨��ʶ��
//          phHash          [OUT] �Ӵն�������
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㣻
//          SAR_HASHOBJERR HASH�������
//          SAR_HASHERR HASH����
//��ע��    ����SKF_DigestInit֮�󣬿��Ե���SKF_Digest
//          �Ե�һ�������ݼ�����ϢժҪ��Ҳ���Զ�ε���SKF_DigestUpdate֮���ٵ���SKF_DigestFinal�Զ�����ݷ���
//          ������ϢժҪ��
ULONG DEVAPI SKF_DigestInit(
							IN   DEVHANDLE  hDev,
							IN   ULONG      ulAlgID,
							IN   ECCPUBLICKEYBLOB *pPubKey, 
							IN   unsigned char *pucID, 
							IN   ULONG ulIDLen,
							OUT  HANDLE     *phHash
						   );

/******************************************************************************************/
//���������Ӵ�
//�����������Ե�һ�������Ϣ�����Ӵռ��㡣 
//������    hHash           [IN]      �Ӵն�����
//          pbData          [IN]      ָ����Ϣ���ݵĻ�����
//          ulDataLen       [IN]      ��Ϣ���ݳ���
//          pbHashData      [OUT]     �Ӵ����ݻ�����ָ�룬���˲���ΪNULLʱ����pulHashLen����
//                                    �Ӵս���ĳ���
//          pulHashLen      [IN OUT]  ����ʱ��ʾpblHashData�������ĳ��ȣ������Ӵս���ĳ��ȡ�
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㣻
//          SAR_HASHOBJERR HASH�������
//          SAR_HASHERR HASH����
//��ע��    ����SKF_Digest֮ǰ���������SKF_DigestInit��ʼ��ժҪ���㡣
//          SKF_Digest�ȼ��ڶ�ε���SKF_DigestUpdate֮�����SKF_DigestFinal��
ULONG DEVAPI SKF_Digest(
						IN      HANDLE     hHash,
						IN      BYTE       *pbData,
						IN      ULONG      ulDataLen,
						OUT     BYTE       *pbHashData,
						IN OUT  ULONG      *pulHashLen
						);


/******************************************************************************************/
//���������Ӵ�
//�����������Զ���������Ϣ�����Ӵռ���
//������    hHash           [IN]  �Ӵն�����
//          pbData          [IN]  ָ����Ϣ���ݵĻ�����
//          ulDataLen       [IN]  ��Ϣ���ݵĳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㣻
//          SAR_HASHOBJERR HASH�������
//          SAR_HASHERR HASH����
//��ע��    ����SKF_DigestUpdate֮ǰ���������SKF_DigestInit
//          ��ʼ��ժҪ�������������SKF_DigestUpdate֮�󣬱������SKF_DigestFinal����ժҪ���㡣
ULONG DEVAPI SKF_DigestUpdate(
							  IN   HANDLE     hHash,
							  IN   BYTE       *pbData,
							  IN   ULONG      ulDataLen
							 );

/******************************************************************************************/
//�����Ӵ�
//�������� ���������������Ϣ���Ӵռ�����������Ӵձ��浽ָ���Ļ�������
//������    hHash           [IN]     �Ӵն�����
//          pHashData       [OUT]    ���ص��Ӵ����ݻ�����ָ�룬����˲���NULLʱ����pulHashLen
//                                   �����Ӵս���ĳ���
//          pulHashLen      [IN OUT] ����ʱ��ʾ�Ӵս���ĳ��ȣ������Ӵ����ݵĳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㣻
//          SAR_HASHOBJERR HASH�������
//          SAR_HASHERR HASH����
//��ע��    SKF_DigestFinal ��������SKF_DigestUpdate֮��
ULONG DEVAPI SKF_DigestFinal(							
                             IN      HANDLE     hHash,
							 OUT     BYTE       *pHashData,
							 IN OUT  ULONG      *pulHashLen
						    );


/******************************************************************************************/
//��Ϣ�����������ʼ��
//������������ʼ����Ϣ�����������������ü�����Ϣ���������Կ��������������Ϣ��Ϣ���������� 
//������    hKey            [IN]  ������Ϣ���������Կ���
//          pMacParam       [IN]  ��Ϣ��֤������ز�����������ʼ��������ʼ�������ȡ���䷽���ȡ� 
//          phMac           [OUT] ��Ϣ�����������
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    ��Ϣ�����������÷�������㷨��CBCģʽ�������ܽ�������һ����Ϊ�����
//          �������������ݵĳ��ȱ����Ƿ�������㷨�鳤�ı������ӿ��ڲ�����������䡣
ULONG DEVAPI SKF_MacInit(
						 IN   HANDLE              hKey,
						 IN   BLOCKCIPHERPARAM   * MacParam,
                         OUT  HANDLE              *phMac
					    );



/******************************************************************************************/
//�������ݵ���Ϣ���������㡣
//����������SKF_Mac ���㵥һ�������ݵ���Ϣ������
//����:     hMac            [IN]     ��Ϣ��������
//          pbData          [IN]     ָ����������ݵĻ����� 
//          ulDataLen       [IN]     ���������ݳ���
//          pbMacData       [OUT]    ָ�������Mac���������˲���ΪNULLʱ����pulMacLen
//                                   ���ؼ����Mac����ĳ��ȡ�
//          pulMacLen       [IN OUT] ����ʱ��ʾpbMacData�������ĳ��ȣ����ؼ���Mac����ĳ��ȡ�
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL ����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_MACLENERR MAC���ȴ���
//��ע��    �ڵ���SKF_Mac֮ǰ���������SKF_MacInit
//          ��ʼ����Ϣ�����������SKF_Mac�ȼ��ڶ�ε���SKF_MacUpdate�ٵ���SKF_MacFinal�� 
ULONG DEVAPI SKF_Mac(
					 IN      HANDLE     hMac,
					 IN      BYTE       *pbData,
					 IN      ULONG      ulDataLen,
					 OUT     BYTE       *pbMacData,
					 IN OUT  ULONG      *pulMacLen
				    );

/******************************************************************************************/
//����������Ϣ���������㡣
//�����������������������ݵ���Ϣ������  
//������    hMac            [IN]  ��Ϣ��֤����
//          pbData          [IN]  ����������
//          ulDataLen       [IN]  ���������ݳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//          SAR_BUFFER_TOO_SMALL ���������㡣
//��ע��    �ڵ���SKF_MacUpdate֮ǰ���������SKF_MacptInit��ʼ����Ϣ���������������ڵ���SKF_MacUpdate
//          ֮�󣬱������SKF_MacFinal��������������ݵ���Ϣ��֤����������
ULONG DEVAPI SKF_MacUpdate(
						   IN   HANDLE     hMac,
						   IN   BYTE       *pbData,
						   IN   ULONG      ulDataLen
						  );


/******************************************************************************************/
//������Ϣ����������
//������������������������ݵ���Ϣ��֤����������
//������    hMac            [IN]  ��Ϣ��������   
//          pbMacData       [OUT] ָ����Ϣ������Ļ����������˲���ΪNULLΪʱ����pulMacDataLen
//                                ������Ϣ�����뷵�صĳ���
//          pulMacDataLen   [OUT] ����ʱ��ʾ��Ϣ�����뻺��������󳤶ȣ�������Ϣ������ĳ���
//����ֵ��  SAR_OK ��ʾ�ɹ���SAR_FAIL����ʧ�ܡ�
//          ������������ֵ��
//          SAR_UNKNOWNERR ����δ֪����
//          SAR_MEMORYERR �����ڴ����
//          SAR_INVALIDPARAMERR ������Ч��
//��ע��    SKF_MacFinal ��������SKF_MacUpdate֮��
ULONG DEVAPI SKF_MacFinal(
					      IN   HANDLE     hMac,
						  OUT  BYTE       *pbMacData,
						  OUT  ULONG      *pulMacDataLen
						 );

/******************************************************************************************/
//����: �رջỰ��Կ���Ӵա���Ϣ�����롢ECC��ԿЭ�̾����
//����: hHandle    [IN] Ҫ�رյĶ�����
//����ֵ: SAR_OK   :�ɹ���
//        ����     :�����롣
ULONG DEVAPI SKF_CloseHandle(
							 HANDLE hHandle
							 );

ULONG DEVAPI SKF_ImportECCKeyPair(IN HCONTAINER hContainer,
	                              PENVELOPEDKEYBLOB pEnvelopedKeyBlob);
ULONG DEVAPI SKF_ExtECCEncrypt(DEVHANDLE hDev, 
	                           ECCPUBLICKEYBLOB *pECCPubKeyBlob,
							   BYTE* pbPlainText, 
							   ULONG ulPlainTextLen, 
							   PECCCIPHERBLOB pCipherText);
ULONG DEVAPI SKF_ExtECCDecrypt (IN DEVHANDLE hDev, 
	                            IN ECCPRIVATEKEYBLOB *pECCPriKeyBlob, 
								IN PECCCIPHERBLOB pCipherText, 
								OUT BYTE *pbPlainText, 
								IN OUT ULONG *pulPlainTextLen);

ULONG DEVAPI SKF_ExtECCSign(DEVHANDLE hDev, 
	                        ECCPRIVATEKEYBLOB *pECCPriKeyBlob,
							BYTE* pbData, 
							ULONG ulDataLen,
							PECCSIGNATUREBLOB pSignature);
ULONG DEVAPI SKF_ExtECCVerify(DEVHANDLE hDev, 
	                          ECCPUBLICKEYBLOB *pECCPubKeyBlob,
							  BYTE* pbData, 
							  ULONG ulDataLen, 
							  PECCSIGNATUREBLOB pSignature);
ULONG DEVAPI SKF_ECCSignData(HCONTAINER hContainer, 
	                         BYTE *pbData, 
							 ULONG ulDataLen, 
							 PECCSIGNATUREBLOB pSignature);
ULONG DEVAPI SKF_ECCVerify(DEVHANDLE hDev , 
	                       ECCPUBLICKEYBLOB* pECCPubKeyBlob, 
						   BYTE *pbData, 
						   ULONG ulDataLen, 
						   PECCSIGNATUREBLOB pSignature);

ULONG DEVAPI SKF_ECCExportSessionKey(HCONTAINER hContainer, 
	                                  ULONG ulAlgId, 
									  ECCPUBLICKEYBLOB *pPubKey, 
									  PECCCIPHERBLOB pData, 
									  HANDLE *phSessionKey);



#ifdef __cplusplus
}
#endif

#endif