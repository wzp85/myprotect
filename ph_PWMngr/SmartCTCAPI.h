
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



//#define SGD_3DES_ECB  0x00000001  //3DES算法ECB加密模式  syc
//#define SGD_3DES_CBC  0x00000002  //3DES算法CBC加密模式  syc
//#define SGD_3DES_CFB  0x00000004  //3DES算法CFB加密模式  syc
//#define SGD_3DES_OFB  0x00000008  //3DES算法OFB加密模式  syc
//#define SGD_3DES_MAC  0x00000010  //3DES算法MAC运算  syc

//分组密码算法标识
#define SGD_SM1_ECB  0x00000101  //SM1算法ECB加密模式
#define SGD_SM1_CBC  0x00000102  //SM1算法CBC加密模式
#define SGD_SM1_CFB  0x00000104  //SM1算法CFB加密模式
#define SGD_SM1_OFB  0x00000108  //SM1算法OFB加密模式
#define SGD_SM1_MAC  0x00000110  //SM1算法MAC运算

#define SGD_SSF33_ECB 0x00000201 //SSF33算法ECB加密模式
#define SGD_SSF33_CBC 0x00000202 //SSF33算法CBC加密模式
#define SGD_SSF33_CFB 0x00000204 //SSF33算法CFB加密模式
#define SGD_SSF33_OFB 0x00000208 //SSF33算法OFB加密模式
#define SGD_SSF33_MAC 0x00000210 //SSF33算法MAC加密

#define SGD_SMS4_ECB  0x00000401 //SMS4算法ECB加密模式
#define SGD_SMS4_CBC  0x00000402
#define SGD_SMS4_CFB  0x00000404
#define SGD_SMS4_OFB  0x00000408
#define SGD_SMS4_MAC  0x00000410

//0x00000400-0x800000xx  其它分组密码算法预留

//非对称密钥算法标识
#define SGD_RSA     0x00010000    //RSA算法
#define SGD_SM2_1   0x00020100    //椭圆曲线签名算法
#define SGD_SM2_2   0x00020200    //椭圆曲线密钥交换协议
#define SGD_SM2_3   0x00020400    //椭圆曲线加密算法

//密码杂凑算法标识
#define SGD_SM3     0x00000001    //SM3杂凑算法
#define SGD_SHA1    0x00000002    //SHA1杂凑算法
#define SGD_SHA256  0x00000004    //SHA256杂凑算法
#define SGD_MD5		0x00000003

////为了社保的接口！----哈希标识
#define ALG_SCH     0x00000040    //SCH杂凑算法
#define ALG_SHA1    0x00000080    //SHA1杂凑算法
#define ALG_SHA256  0x00000100    //SHA256杂凑算法

//0x00000010-0x000000FF 为其它密码杂凑算法预留
//
/*	typedef char                 INT8;      //有符号8位整数*/
	typedef short                INT16;     //有符号16位整数
	typedef unsigned char        UINT8;     //无符号8位整数
	typedef unsigned short       UINT16;    //无符号16位整数
	typedef float                FP32;      //32位单精度浮点数
	typedef double               FP64;      //64位双精度浮点数
	typedef UINT8                BYTE;       //字节类型，无符号8位整数
	typedef INT16                SHORT;      //短整数，有符号16位整数
	typedef UINT16               USHORT;     //无符号16位整数
	typedef UINT32               UINT;       //无符号32位整数
	typedef UINT16               WORD;       //字类型，无符号16位整数
	typedef UINT32               FLAGS;      //标志类型，无符号32位整数
	typedef CHAR *               LPSTR;      //8位字符串指针
	typedef void *               HANDLE;     //句柄，指向任意数据对象的起始地址
	typedef HANDLE               DEVHANDLE;  //设备句柄
	typedef HANDLE               HAPPLICATION;  //应用句柄
	typedef HANDLE               HCONTAINER; //容器句柄
//	typedef char                 CHAR;
	
//设备权限类型             
#define     SECURE_NEVER_ACCOUNT       0x00000000             //不允许
#define     SECURE_ADM_ACCOUNT         0x00000001             //管理员权限
#define     SECURE_USER_ACCOUNT        0x00000010             //用户权限
#define     SECURE_EVERYONE_ACCOUNT    0x000000FF             //任何人

//PIN码类型
#define	ADMIN_TYPE						0x00000000	// 管理员PIN
#define USER_TYPE						0x00000001	// 用户PIN


//设备状态
#define  DEV_EMPTY_STATE     0x00000000    //设备不存在
#define  DEV_PRESENT_STATE   0x00000001    //设备存在
#define DEV_UNKNOW_STATE				0x00000002


//错误代码
#define  SAR_OK                      0x00000000          //成功
#define  SAR_FAIL                    0x0A000001          //失败
#define  SAR_UNKNOWNERR              0x0A000002          //异常错误
#define  SAR_NOTSUPPORTYETERR        0x0A000003          //不支持的服务
#define  SAR_FILEERR                 0x0A000004          //文件操作错误
#define  SAR_INVALIDHANDLEERR        0x0A000005          //无效的句柄
#define  SAR_INVALIDPARAMERR         0x0A000006          //无效的参数
#define  SAR_READFILEERR             0x0A000007          //读文件错误
#define  SAR_WRITEFILEERR            0x0A000008          //写文件错误
#define  SAR_NAMELENERR              0x0A000009          //名称长度错误
#define  SAR_KEYUSAGEERR             0x0A00000A          //密钥用途错误
#define  SAR_MODULUSLENERR           0x0A00000B          //模的长度错误
#define  SAR_NOTINITIALIZEERR        0x0A00000C          //未初始化
#define  SAR_OBJERR                  0x0A00000D          //对象错误
#define  SAR_MEMORYERR               0x0A00000E          //内存错误
#define  SAR_TIMEOUTERR              0x0A00000F          //超时
#define  SAR_INDATALENERR            0x0A000010          //输入数据长度错误
#define  SAR_INDATAERR               0x0A000011          //输入数据错误
#define  SAR_GENRANDERR              0x0A000012          //生成随机数错误
#define  SAR_HASHOBJERR              0x0A000013          //HASH对象错
#define  SAR_HASHERR                 0x0A000014          //HASH运算错误
#define  SAR_GENRSAKEYERR            0x0A000015          //产生RSA密钥错误
#define  SAR_RSAMODULUSLENERR        0x0A000016          //RSA密钥模长错误
#define  SAR_CSPIMPRTPUBKEYERR       0x0A000017          //CSP服务导入公钥错误
#define  SAR_RSAENCERR               0x0A000018          //RSA加密错误
#define  SAR_RSADECERR               0x0A000019          //RSA解密错误
#define  SAR_HASHNOTEQUALERR         0x0A00001A          //HASH值不相等
#define  SAR_KEYNOTFOUNTERR          0x0A00001B          //密钥未发现
#define  SAR_CERTNOTFOUNTERR         0x0A00001C          //证书未发现
#define  SAR_NOTEXPORTERR            0x0A00001D          //对象未导出
#define  SAR_DECRYPTPADERR           0x0A00001E          //解密时作补丁错误
#define  SAR_MACLENERR               0x0A00001F          //MAC长度错误
#define  SAR_BUFFER_TOO_SMALL        0x0A000020          //缓冲区不足
#define  SAR_KEYINFOTYPEERR          0x0A000021          //密钥类型错误
#define  SAR_NOT_EVENTERR            0x0A000022          //无事件错误
#define  SAR_DEVICE_REMOVED          0x0A000023          //设备已移除
#define  SAR_PIN_INCORRECT           0x0A000024          //PIN不正确
#define  SAR_PIN_LOCKED              0x0A000025          //PIN被锁死
#define  SAR_PIN_INVALID             0x0A000026          //PIN无效
#define  SAR_PIN_LEN_RANGE           0x0A000027          //PIN长度错误
#define  SAR_USER_ALREADY_LOGGED_IN  0x0A000028          //用户已经登录
#define  SAR_USER_PIN_NOT_INITIALIZED 0x0A000029         //没有初始化用户口令
#define  SAR_USER_TYPE_INVALID       0x0A00002A          //PIN类型错误
#define  SAR_APPLICATION_NAME_INVALID 0x0A00002B         //应用名称无效
#define  SAR_APPLICATION_EXISTS      0x0A00002C          //应用已经存在
#define  SAR_USER_NOT_LOGGED_IN      0x0A00002D          //用户没有登录
#define  SAR_APPLICATION_NOT_EXISTS  0x0A00002E          //应用不存在
#define  SAR_FILE_ALREADY_EXIST      0x0A00002F          //文件已经存在
#define  SAR_NO_ROOM                 0x0A000030          //空间不足
#define  SAR_FILE_NOT_EXIST          0x0A000031          //文件不存在
#define  SAR_NOTSUPPORTKEYTYPE       0x0A000032          //不支持SM2算法
	

//版本
typedef struct Struct_Version{
	BYTE major ;   //主版号
	BYTE minor ;   //次版号
	} VERSION;
	
	//设备信息
typedef struct Struct_DEVINFO {
	VERSION  Version;         //数据结构版本号,本结构的版本号为1.0
	CHAR Manufacturer[64];    //设备厂商信息, 以'\0'为结束符的ASCII字符串		
	CHAR Issuer[64];          //发行厂商信息, 以'\0'为结束符的ASCII字符串
	CHAR Label[32];           //设备标签, 以'\0'为结束符的ASCII字符串
	CHAR SerialNumber[32];    //序列号, 以'\0'为结束符的ASCII字符串	                 
	VERSION HWVersion;        //设备硬件版本
	VERSION FirmwareVersion;  //设备本身固件版本
	ULONG   AlgSymCap;        //分组密码算法标识
	ULONG   AlgAsymCap;       //非对称密码算法标识
	ULONG   AlgHashCap;       //密码杂凑算法标识   
    ULONG   DevAuthAlgId;     //设备认证使用的分组密码算法标识
	ULONG   TotalSpace;       //设备总空间
	ULONG   FreeSpace;        //用户可用空间
    BYTE    Reserved[64];     //保留扩展	
	}DEVINFO,*PDEVINFO;

// 服务端的RSA结构
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

//RSA 公钥数据结构
#define  MAX_RSA_MODULUS_LEN        256         //RSA算法的最大模长
#define  MAX_RSA_EXPONENT_LEN       4           //算法指数的最大长度  
typedef  struct Struct_RSAPUBLICKEYBLOB{	
	ULONG AlgID ;                               //算法标识号
	ULONG BitLen ;                              //模数的实际位长度  必须是8的整数倍
	BYTE Modulus[MAX_RSA_MODULUS_LEN];          //模数 n=p*q  实际长度是BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];  //公开密钥 e
	}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB; 
	
//RSA 私钥数据结构
typedef struct Struct_RSAPRIVATEKEYBLOB{
	ULONG AlgID ;                                //算法标识号
	ULONG BitLen ;                               //模数的实际位长度  必须送是8的整数倍
	BYTE Modulus[MAX_RSA_MODULUS_LEN];           //模数 n=p*q  实际长度是BitLen/8字节
	BYTE PublicExponent[MAX_RSA_EXPONENT_LEN];
	BYTE PrivateExponent[MAX_RSA_MODULUS_LEN];   //私有密钥d   实际长度是BitLen/8字节
	BYTE Prime1[MAX_RSA_MODULUS_LEN/2];          //素数p       实际长度是BitLen/16字节
	BYTE Prime2[MAX_RSA_MODULUS_LEN/2];          //素数q       实际长度是BitLen/16字节
	BYTE Prime1Exponent[MAX_RSA_MODULUS_LEN/2];  //d mod (p-1)值 实际长度是BitLen/16字节
	BYTE Prime2Exponent[MAX_RSA_MODULUS_LEN/2];  //d mod (q-1)值 实际长度是BitLen/16字节
	BYTE Coefficient[MAX_RSA_MODULUS_LEN/2];     //q 模 p 的乘法逆元 实际长度是BitLen/16字节
	}RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;
	
//ECC 公钥数据结构  
#define   ECC_MAX_XCOORDINATE_BITS_LEN  512//曲线上点的X的坐标
#define   ECC_MAX_YCOORDINATE_BITS_LEN  512//曲线上点的Y坐标
#define   ECC_MAX_MODULUS_BITS_LEN 512
//6.4.5 ECC公钥交换数据块 
//（1）类型定义 
typedef struct Struct_ECCPUBLICKEYBLOB{ 
	//ULONG AlgID; by shenjun at 20110401
	ULONG BitLen; 
	BYTE XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8]; 
	BYTE YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8]; 
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB; 

//6.4.6 ECC私钥交换数据块 
typedef struct Struct_ECCPRIVATEKEYBLOB{ 
	//ULONG AlgID; by shenjun at 20110401
	ULONG BitLen; 
	BYTE PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8]; 
}ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB; 
// ECC密文数据结构
typedef struct Struct_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  Hash[32];
	ULONG CipherLen;
	BYTE  Cipher[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}ECCCIPHERBLOB, *PECCCIPHERBLOB;

typedef struct SKF_ENVELOPEDKEYBLOB{
	ULONG Version;                  // 当前版本为 1
	ULONG ulSymmAlgID;              // 规范中的算法标识，限定ECB模式
	ULONG ulBits;					// 加密密钥对密钥长度 	
	BYTE cbEncryptedPriKey[64];     // 加密保护的加密私钥
	ECCPUBLICKEYBLOB PubKey;        // 加密公钥
	ECCCIPHERBLOB ECCCipherBlob;    // SM2 公钥加密的密钥加密密钥
}ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

// ECC签名数据结构
typedef struct Struct_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

//分组密码参数
#define  MAX_IV_LEN  32
typedef struct Struct_BLOCKCIPHERPARAM{
	BYTE IV[MAX_IV_LEN];    //初始向量
	ULONG IVLen;            //初始向量实际长度
	ULONG PaddingType;      //填充方式 0表示不填充，1表示按照PKCS#5方式进行
	ULONG FeedBitLen;	    // 
}BLOCKCIPHERPARAM,*PBLOCKCIPHERPARAM;



//文件属性
#define MAX_FILE_NAME_LEN    32    //最大文件名字长度 暂时定义为此值
typedef struct Struct_FILEATTRIBUTE{
	CHAR  FileName[32];     //文件名 以‘\0’结束的ASCII字符串，最大长度32
    ULONG FileSize;         //创建文件时定义的文件大小
    ULONG ReadRights;       //读取文件需要的权限
	ULONG WriteRights;      //写入文件需要的权限
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

#define  SGD_SM3 0x00000001 //SM3杂凑算法 
#define  SGD_SHA1 0x00000002 //SHA1杂凑算法 
#define  SGD_SHA256 0x00000004 //SHA256杂凑算法 
//#define  SGD_SHA1   32772 //SHA1杂凑算法——国际标准  syc
 
// 版本
typedef struct Struct_HT_Version{
	BYTE major;		//主版本号
	BYTE minor;		//次版本号
}HT_VERSION;


// 设备信息
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


// 设备初始化信息设备类型：
typedef struct Struct_HT_DEVINITINFO
{
	HT_VERSION AppVersion;
	CHAR Manufacturer[64];	//设备厂商信息,最长64个字符，不足64个字符以空白字符(ASCII码为0xFF)填充，不能以null（0x00）结束。
	CHAR Label[64];	//SIC/SZD标签,最长64个字符，不足64个字符以空白字符(ASCII码为0xFF)填充，不能以null（0x00）结束。
}HT_DEVINITINFO,*HT_PDEVINITINFO;


// RSA公钥交换数据块
typedef struct Struct_HT_RSAPUBLICKEYBLOB{
	ULONG	AlgID;
	ULONG	BitLen;
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];
}HT_RSAPUBLICKEYBLOB, *HT_PRSAPUBLICKEYBLOB;

// RSA私钥交换数据块
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


// ECC公钥交换数据块
typedef struct Struct_HT_ECCPUBLICKEYBLOB{
	ULONG	BitLen;
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];
}HT_ECCPUBLICKEYBLOB, *HT_PECCPUBLICKEYBLOB;

// ECC私钥交换数据块
typedef struct Struct_HT_ECCPRIVATEKEYBLOB{
	ULONG	BitLen;
	BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];
}HT_ECCPRIVATEKEYBLOB, *HT_PECCPRIVATEKEYBLOB;


// ECC密文数据结构
typedef struct Struct_HT_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE  Hash[32];
	ULONG CipherLen;
	BYTE  Cipher[256];
}HT_ECCCIPHERBLOB, *HT_PECCCIPHERBLOB;


// ECC签名数据结构
typedef struct Struct_HT_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
}HT_ECCSIGNATUREBLOB, *HT_PECCSIGNATUREBLOB;


typedef struct SKF_HT_ENVELOPEDKEYBLOB{
	ULONG Version;                  // 当前版本为 1
	ULONG ulSymmAlgID;              // 规范中的算法标识，限定ECB模式
	ULONG ulBits;					// 加密密钥对的密钥位长度
	BYTE cbEncryptedPriKey[64];     // 加密保护的加密私钥
	HT_ECCPUBLICKEYBLOB PubKey;        // 加密公钥
	HT_ECCCIPHERBLOB HT_ECCCIPHERBLOB;    // SM2 公钥加密的密钥加密密钥
}HT_ENVELOPEDKEYBLOB, *HT_PENVELOPEDKEYBLOB;

// 分组密码参数
typedef struct Struct_HT_BLOCKCIPHERPARAM{
	BYTE	IV[MAX_IV_LEN];
	ULONG	IVLen;
	ULONG	PaddingType;
	ULONG	FeedBitLen;
} HT_BLOCKCIPHERPARAM, *HT_PBLOCKCIPHERPARAM;

// 文件属性
typedef struct Struct_HT_FILEATTRIBUTE{
	CHAR	FileName[32];
	ULONG	FileSize;
	ULONG	ReadRights;
	ULONG	WriteRights; 
}HT_FILEATTRIBUTE, *HT_PFILEATTRIBUTE;
#pragma pack()



//设备管理函数共有9个
/****************************************************************************************************/
//等待设备插拔事件
//功能描述：该函数等待设备插拔事件， szDevName返回事件的设备名称
//                 
//参数：    
//          szDevName     [IN]      输入参数，发生事件的设备名称
//          ulDevNameLen  [IN/OUT]  输入参数，输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度，长度包含字符串结束符。
//          pulEvent      [OUT]     事件类型  1 表示插入，2 表示拔出
//返回值：  SAR_OK表示成功，SAR_FAIL返回失败。
//          返回其他错误值如下：
//          SAR_UNKNOWNERR发生未知错误。
//          SAR_MEMORYERR发生内存错误。
//          SAR_TIMEOUTERR等待超时。
//          SAR_NOT_EVENTERR无事件错误。
//          SAR_INVALIDPARAMERR参数无效。 
//备注：    无。
ULONG DEVAPI SKF_WaitForDevEvent(							
								 OUT      LPSTR   szDevName,
								 IN OUT  ULONG   ulDevNameLen,
								 OUT     ULONG   *pulEvent
								 );

/****************************************************************************************************/								 
//功能  : 该函数取消等待设备插入或者拔除事件
//参数
//返回值: SAR_OK: 成功
//其他  : 错误码
ULONG DEVAPI SKF_CancelWaitForDevEvent();


/****************************************************************************************************/
//枚举设备
//功能描述：该函数枚举当前驱动支持的所有设备列表或者当前状态为存在的设备，
//          通过该函数来管理，获得当前系统中设备列表的情况。
//          在进行设备连接前，要用该函数判断设备是否存在。
//参数：    bPresent      [IN] 输入参数，为 1 表示取当前设备状态为存在的设备列表。为 0 表示取当前驱动支持的设备列表。
//          szNameList    [OUT] 输出参数，设备名称列表，该参数为空，将由pulSize返回需要的内存空间的大小,多个设备之间用'\0'分割隔。
//          pulSize       [IN OUT ] 输入参数，输入设备名称列表的缓冲区长度，输出参数，返回pszeNameList需要的空间大小。
//返回值：  SAR_OK表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR发生未知错误。
//          SAR_MEMORYERR发生内存错误。
//          SAR_BUFFER_TOO_SMALL 缓存不够。 
//备注：    使用 DEVAPI 应该在访问设备前首先调用该函数。
ULONG DEVAPI SKF_EnumDev(
						 IN      BOOL   bPresent,
						 OUT     LPSTR  szNameList,
						 IN OUT  ULONG  *pulSize
				        );

/*****************************************************************************************************/
//连接设备
//功能描述： 通过设备名称连接设备，返回设备的句柄。
//           连接设备函数，是对设备进行其他操作的第一步，连接设备成功后，可以对设备发送其他指令，例如创建文件，
//           读写文件等等。为了节省和设备之间的通讯速度，一般在连接完一次设备后，尽可能多的进行该次连接的其他操作，
//           然后再断设备。该函数以共享的方式连接设备，一个应用连接后其他应用还可以连接设备，如果一个应用想对设备进行独
//           占操作，请在连接设备后，调用开始同步事务处理函数SKF_LockDev 。
//参数：     pszName   [IN]  输入参数,设备名称。
//           phDEV     [OUT] 输出参数,设备操作句柄。 
//返回值：   SAR_OK表示成功，SAR_FAIL返回失败。
//           返回其他错误值：
//           SAR_NAMELENERR 设备名称错误；
//           SAR_UNKNOWNERR 发生未知错误；
//           SAR_MEMORYERR 发生内存错误；
//           SAR_DEVICE_REMOVED 设备已移除。
//备注：     使用API算法服务或者文件管理函数之前调用。
ULONG DEVAPI SKF_ConnectDev(
							IN  LPSTR     szName,
							OUT DEVHANDLE *phDev
						   );


/*****************************************************************************************************/
//断开设备
//功能描述：断开一个已经连接的设备。调用断开设备函数成功后，该设备此次连接的句柄失效，如果希望重新对设备进行操作请重新连接设备。
//          断开连接操作并不影响设备的权限状态，也不会释放应用对设备的同步状态，这一点要特别注意!       
//参数：    hDev  [IN] 输入参数，连接设备返回的设备句柄。
//返回值：  SAR_OK表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_DEVICE_REMOVED 设备已移除。
//备注：    断开设备或者设备拔掉后句柄自动失效。
ULONG DEVAPI SKF_DisConnectDev(
							   IN DEVHANDLE hDev
						      );


/****************************************************************************************************/
//判断设备状态
//功能描述：判断设备是否存在于系统中，可以返回DEV_PRESENT_STATE或者DEV_EMPTY_STATE。
//          
//参数：    szDevName   [IN]   输入参数，连接名称。
//          pulDevState [OUT]  输出参数，返回的设备状态。
//返回值：  SAR_OK 表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//备注：    无。
ULONG DEVAPI SKF_GetDevState ( 
							  IN  LPSTR   szDevName, 
							  OUT ULONG   *pulDevState
							  );	

/****************************************************************************************************/
//设置设备标签
//功能描述 设置设备标签。
//          
//参数：    hDev   [IN]   连接设备时返回的设备句柄。
//          szLabel[IN]   设备标签字符串。该字符串应小于32字节。            
//返回值：  SAR_OK 表示成功。
//          返回其他错误值：
//备注：    无
ULONG  DEVAPI SKF_SetLabel ( 
							   IN  DEVHANDLE hDev, 
							   IN  LPSTR     szLabel
							   );	

/**************************************************************************************************/
//获取设备信息
//功能描述：获取设备的一些特定信息，包括设备的标志，厂商信息，口令的长度范围，支持的算法等。
//参数：    hDev      [IN]  输入参数，连接设备返回的设备句柄。
//          pDevInfo  [OUT] 输出参数，返回设备信息。 
//返回值：  SAR_OK 表示成功， SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_DEVICE_REMOVED 设备已移除；
//          SAR_BUFFER_TOO_SMALL 缓存不足；
//备注：    无                
ULONG DEVAPI SKF_GetDevInfo(
							IN  DEVHANDLE   hDev,
							OUT DEVINFO     *pDevInfo
						   );

/*******************************************************************************************/
//锁定设备， 开始同步事务处理
//功能够描述：通过调用该函数，设置对设备的独占权，互斥其他应用对设备的操作。
//            该函数调用成功后，其他应用再调用连接设备操作时会处于等待状态，一直到本应用释放了独占权。
//            该函数很好的解决了多个进程之间同时对设备访问处理的问题。
//            当一个应用结束了对设备的处理后，一定要调用结束同步事务处理函数，否则会导致其他应用不能再连接设备，
//            造成其他应用无响应状态。
//            该函数与释放设备函数一定要成对出现。
//参数：      hDev      [IN]  输入参数，连接设备返回的设备句柄。
//返回值：    SAR_OK 表示成功， SAR_FAIL 返回失败。
//            返回其他错误码：
//            SAR_UNKNOWNERR 发生未知错误；
//            SAR_DEVICE_REMOVED 设备已移除。
//备注:       断开设备或者设备拔掉之后，释放同步资源。
ULONG DEVAPI SKF_LockDev(
						 IN  DEVHANDLE   hDev,
						 IN  ULONG       ulTimeOut
						);
	

/******************************************************************************************/
//释放设备， 结束同步事务处理
//功能描述：调用该函数后，应用结束对该设备的独占状态，但没有断开对设备的连接
//          如果一个应用调用了开始同步事务处理函数，但是在操作结束后没有调用结束同步事务处理函数，
//          会导致其他应用对设备操作时处于无限等待状态。
//          该函数要与开始锁定设备处理函数成对出现。
//参数：    hDev      [IN]  输入参数，连接设备返回的设备句柄。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误码：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效。
//备注：    断开设备或者设备拔掉后句柄自动失效。
ULONG DEVAPI SKF_UnLockDev(
						   IN  DEVHANDLE   hDev
						  );  


/******************************************************************************************/
//设备命令传输
//功能: 将命令直接发给设备,并返回结果
//参数: hDev        [IN]    设备句柄
//      pbCommand   [IN]    设备命令
//      ulCommandLen[IN]    命令长度

ULONG DEVAPI SKF_Transmit( 
						  DEVHANDLE hDev, 
						  BYTE  * pbCommand, 
						  ULONG ulCommandLen,
						  BYTE  * pbData,
						  ULONG *pulDataLen
						  );


/***********************************************************/
//访问控制
//功能: 更改设备认证密钥
//参数: hDev        [IN]    设备句柄
//      pbKeyValue  [IN]    密钥值
//      ulKeyLen    [IN]    密钥长度
//返回值:SAR_OK     成功
//其他  :错误码
//备注  :权限要求:设备认证成功后才能使用
ULONG DEVAPI SKF_ChangeDevAuthKey( 
						  DEVHANDLE hDev, 
						  BYTE  * pbKeyValue, 
						  ULONG ulKeyLen
						  );


/***********************************************************/
//功能: 设备认证
//参数: hDev        [IN]    设备句柄
//      pbAuthData  [IN]    认证数据
//      ulLen       [IN]    认证数据长度
//返回值:SAR_OK     成功
//其他  :错误码

ULONG DEVAPI SKF_DevAuth( 
						 DEVHANDLE hDev, 
						 BYTE  * pbAuthData, 
						 ULONG ulLen
						 );

/******************************************************************************************/
//修改PIN
//功能描述：该函数能够修改Admin PIN 和User PIN的值。 只有知道原Admin PIN 或者User PIN的人才能修改。
//          如果修改不成功，该函数返回Admin PIN或者User PIN的剩余次数，当剩余次数为0时候，表示该PIN已经锁死。
//参数：      
//            hApplication  [IN]  输入参数，应用句柄。
//            ulPINType     [IN]  输入参数，PIN类型 ADMIN_TYPE=0或者USER_TYPE=1。 
//            szOldPin      [IN]  原PIN值
//            szNewPin      [IN]  新PIN值
//            pulRetryCount [OUT] 出错后重试次数
//返回值：    SAR_OK 表示成功，SAR_FAIL 返回失败。
//            返回其他错误值：
//            SAR_MEMORYERR 发生内存错误；
//            SAR_UNKNOWNERR 发生未知错误；
//            SAR_PIN_INCORRECT PIN错误；
//            SAR_PIN_INVALID PIN无效；
//            SAR_PIN_LEN_RANGE PIN长度错误；
//            SAR_PIN_LOCKED PIN锁死；
//            SAR_INVALIDHANDLEERR 句柄无效。
//备注：      无
ULONG DEVAPI SKF_ChangePIN(						  
						   IN  HAPPLICATION  hApplication,
						   IN  ULONG         ulPINType,
						   IN  LPSTR         szOldPin,
						   IN  LPSTR         szNewPin,
						   OUT ULONG         *pulRetryCount
						  );

/***********************************************************/
//功能: 获取PIN信息
//参数: hApplication           [IN]     输入参数，应用句柄。
//      ulPINType              [IN]     PIN类型
//      pulMaxRetryCount       [OUT]    最大重试次数
//      pulRemainRetryCount    [OUT]    当前剩余重试次数，当为0时表示已锁死
//      pbDefaultPin           [OUT]    是否为出厂默认PIN码
//返回值:SAR_OK     成功
//其他  :错误码

ULONG DEVAPI SKF_GetPINInfo(
							IN  HAPPLICATION hApplication,
							IN  ULONG  ulPINType,
							OUT ULONG *pulMaxRetryCount,
							OUT ULONG *pulRemainRetryCount,
							OUT BOOL  *pbDefaultPin
							);

/******************************************************************************************/
//校验口令
//功能描述：校验 Admin PIN 或者 User PIN 。校验成功后，会获得相应的权限，如果调用失败，会返口令的重试次数，
//          当口令的重试次数为0时，表明口令已经被锁死。
//参数：    
//          hApplication  [IN]  输入参数，应用句柄。
//          ulUserType    [IN]  用户类型  ADMIN或者USER
//          szPIN         [IN]  PIN值
//          pulRetryCount [OUT] 出错后返回重试次数
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_PIN_INCORRECT PIN错误；
//          SAR_PIN_INVALID PIN无效；
//          SAR_PIN_LEN_RANGE PIN长度错误；
//          SAR_PIN_LOCKED PIN锁死；
//          SAR_USER_ALREADY_LOGGED_IN PIN已经获得权限；
//          SAR_USER_PIN_NOT_INITIALIZED PIN为初始化错误；
//          SAR_USER_TYPE_INVALID PIN类型错误；
//          SAR_INVALIDHANDLEERR 句柄无效。
//备注：    无
ULONG DEVAPI SKF_VerifyPIN(                        
						   IN  HAPPLICATION  hApplication,
						   IN  ULONG         ulUserType,
						   IN  LPSTR         szPIN,
						   OUT ULONG         *pulRetryCount
						  );

/******************************************************************************************/
//解锁用户PIN
//功能够描述：当用户口令锁死后，调用该函数来解锁用户口令。只用知道Admin PIN才能解锁用户口令，如果输入Admin PIN
//            错误或者已经锁死，会调用失败，并返回Admin PIN重试次数。解锁后用户口令被设置为新值，重试次数也恢复到原值。
//参数：    
//          hApplication  [IN]  输入参数，应用句柄。
//          szAdminPIN    [IN]  管理员PIN
//          szNewUserPIN  [IN]  普通用户新PIN
//          pulRetryCount [OUT] 出错后重试次数
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值:
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_PIN_INCORRECT PIN错误；
//          SAR_PIN_INVALID PIN无效；
//          SAR_PIN_LEN_RANGE PIN长度错误；
//          SAR_PIN_LOCKED PIN锁死；
//          SAR_USER_PIN_NOT_INITIALIZED PIN为初始化错误；
//          SAR_INVALIDHANDLEERR 句柄无效。
//备注：    无
ULONG DEVAPI SKF_UnblockPIN(							
							IN  HAPPLICATION  hApplication,
							IN  LPSTR         szAdminPIN,
							IN  LPSTR         szNewUserPIN,
							OUT ULONG         *pulRetryCount
						   );


/******************************************************************************************/
//清楚安全状态
//功能描述：通过调用该函数，把应用之前获得所有权限，包括校验Admin PIN User PIN以及外部验证获得的权限全部清除掉。
//          执行完清除安全状态后，当前路径恢复到设备根目录。
//参数：    
//          hApplication    [IN]  输入参数，应用句柄。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效。
//备注：    无
ULONG DEVAPI SKF_ClearSecureState(
								  
								  IN HAPPLICATION  hApplication
								 );



/*****************************************************************************************/
/*
应用管理类  
*/
/*****************************************************************************************/

//创建应用函数
//功能描述：创建一个应用，以满足应用的需求。
//          一个设备可以创建多个应用。
//          在应用下，可以创建一个或多个应用证书，应用文件。
//参数：   hDev              [IN]  输入参数，连接设备返回的设备句柄。       
//         szAppName         [IN]  应用名称
//         szAdminPin        [IN]  管理员PIN
//         dwAdminPinRetryCount [IN] 管理员PIN的最大重试次数
//         szUserPin         [IN]  用户PIN
//         dwUserPinRetryCount [IN]用户PIN的最大重试次数
//         dwCreateFileRights  [IN]在该应用下创建文件和容器的权限
//         phApplication     [OUT] 应用的句柄
//返回值： SAR_OK 表示成功，SAR_FAIL返回失败。
//         返回其他错误值：
//         SAR_MMEORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//         SAR_INVALIDHANDLEERR 句柄无效；
//         SAR_APPLICATION_NAME_INVALID 应用名称无效；
//         SAR_APPLICATION_EXISTS 应用已经存在。
//备注：   无。
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
//枚举应用函数
//功能描述：枚举存在的所有应用。
//参数：   hDev              [IN]  输入参数，连接设备返回的设备句柄。       
//         szAppName         [OUT] 输出参数，返回应用名称，该参数为空，将由pulSize返回所需要的内存空间大小。
//         pulSize           [IN，OUT]  输入参数，输入应用名称的缓冲区长度
//                                      输出参数，返回szAppName所需要的空间大小。
//                                      每个应用的名称以单个NULL结束，以双NULL表示列表的结束。
//返回值： SAR_OK 表示成功，SAR_FAIL返回失败。
//         返回其他错误值：
//         SAR_MMEORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//备注：   无。
ULONG DEVAPI SKF_EnumApplication(
                                 IN      DEVHANDLE     hDev,
								 OUT     LPSTR         szAppName,
								 IN OUT  ULONG         *pulSize					
							    );

/******************************************************************************************/
//删除应用函数
//功能描述：删除一个应用，需要满足安全权限，才能够删除。
//参数：   hDev              [IN]  输入参数，连接设备返回的设备句柄。       
//         szAppName         [IN]  应用名称
//返回值： SAR_OK 表示成功，SAR_FAIL返回失败。
//         返回其他错误值：
//         SAR_MMEORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//         SAR_USER_NOT_LOGGED_IN 尚未校验用户PIN;
//         SAR_APPLICATION_NOT_EXISTS 应用不存在。
//备注：   无。
ULONG DEVAPI SKF_DeleteApplication(
                                   IN  DEVHANDLE     hDev,
								   IN  LPSTR         szAppName
							      );



/******************************************************************************************/
//打开应用函数
//功能描述：打开应用
//参数：   hDev              [IN]  输入参数，连接设备返回的设备句柄。       
//         szAppName         [IN]  应用名称
//         phApplication     [OUT] 应用的句柄
//返回值： SAR_OK 表示成功，SAR_FAIL返回失败。
//         返回其他错误值：
//         SAR_MMEORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//         SAR_APPLICATION_NOT_EXISTS 应用不存在。
//备注：   无。
ULONG DEVAPI SKF_OpenApplication(
                                 IN  DEVHANDLE     hDev,
								 IN  LPSTR         szAppName,
								 OUT HAPPLICATION  *phApplication
							    );

/******************************************************************************************/
//关闭应用函数
//功能描述：关闭应用             
//参数       phApplication     [IN]  应用的句柄
//返回值： SAR_OK 表示成功，SAR_FAIL返回失败。
//         返回其他错误值：
//         SAR_MMEORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//         SAR_USER_NOT_LOGGED_IN 尚未校验用户PIN;
//         SAR_INVALIDHANDLEERR 句柄无效。
//备注：   无。
ULONG DEVAPI SKF_CloseApplication(								 
								  IN  HAPPLICATION  phApplication
							      );


/*****************************************************************************************/
/*
文件管理类  
*/
/*****************************************************************************************/
//创建文件
//功能够描述：创建一个应用文件。
//            创建文件要指定文件的类型，名称，大小，以及文件的读写权限。 
//            文件创建后，大小不可以改变，可以删除。  
//参数：   hApplication       [IN]  应用句柄
//         szFileName         [IN]  文件名称
//         ulFileSize         [IN]  文件大小
//         ulReadRights       [IN]  文件读权限
//         ulWriteRights      [IN]  文件写权限
//返回值： SAR_OK 表示成功，SAR_FAIL 返回失败。
//         返回其他错误值：
//         SAR_MEMORYERR 发生内存错误；
//         SAR_UNKNOWNERR 发生未知错误；
//         SAR_USER_NOT_LOGGED_IN 尚未校验用户PIN；
//         SAR_INVALIDHANDLEERR 句柄无效；
//         SAR_FILEERR 文件错误；
//         SAR_NAMELENERR 文件名称长度错误；
//         SAR_FILE_ALREADY_EXIST 文件已经存在；
//         SAR_NO_ROOM 剩余空间不够。
//备注：   ulAcceccCondition                        具体权限值参见“设备权限类型”
//         bit32 ～ bit25   无意义的保留字节，0xFF；
//         bit24 ～ bit17   无意义的保留字节，0xFF；
//         bit16 ～ bit9    读权限，读此基本文件要满足的权限；
//         bit8  ～ bit1    写权限，写此基本文件要满足的权限。
ULONG DEVAPI SKF_CreateFile(                   
							IN HAPPLICATION  hApplication,
                            IN LPSTR         szFileName,
						    IN ULONG         ulFileSize,						 
                            IN ULONG         ulReadRights,
							IN ULONG         ulWriteRights
						   );


/******************************************************************************************/
//删除文件
//功能描述：删除文件后，文件中写入的内容将丢失。文件在设备占用的空间将释放。 
//          删除一个已经创建的文件。
//参数：    hApplication       [IN]  要删除文件所在的应用句柄。
//          szFileName         [IN]  要删除文件名称
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_USER_NOT_LOGGED_IN 尚未校验用户PIN；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_FILEERR 文件错误。
//备注：    无
ULONG DEVAPI SKF_DeleteFile(                    
						    IN HAPPLICATION  hApplication,
                            IN LPSTR         szFileName
						   );


/******************************************************************************************/
//枚举文件
//功能描述：枚举一个应用下存在的所有文件。 
//参数：    hApplication   [IN]  应用句柄。
//          szFileList     [OUT] 返回文件名称，如果该参数为空，由pulSize返回需要的缓冲区大小，
//                               多个文件之间以NULL结束，以双NULL表示列表的结束。
//          pulSize        [IN OUT] 输入为数据缓冲区的大小，输出为实际文件名称大小。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_EnumFiles(						   
						   IN     HAPPLICATION  hApplication,
						   OUT    LPSTR         szFileList,
						   IN OUT ULONG         *pulSize						 
						   );

/******************************************************************************************/
//获取文件属性信息
//功能描述：获取应用文件的属性信息，例如文件的大小、权限等。
//参数：    hApplication       [IN]  文件所在应用的句柄
//          szFile             [IN]  文件名称
//          pFileInfo          [OUT] 文件信息，指向文件属性结构的指针。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_FILEERR 文件错误；
//          SAR_FILE_NAME_INVALID 文件名称无效。
//备注：    无
ULONG DEVAPI SKF_GetFileInfo(
						     IN  HAPPLICATION    hApplication,
                             IN  LPSTR           szFile,
							 OUT FILEATTRIBUTE   *pFileInfo
							);



/******************************************************************************************/
//读文件
//功能描述：读应用文件中的数据，对于刚创建的文件，该函数也能调用成功，读出的数据是文件中原有的
//          默认数据值。对于一个应用文件首先要对其进行写操作，然后才能读出正确的数据。
//参数：    
//          hApplication       [IN]  应用句柄
//          szFile             [IN]  文件名
//          ulOffset           [IN]  读文件需要的偏移量
//          ulSize             [IN]  要读取的数据量
//          pbOutData          [OUT] 返回的数据缓冲区
//          pulOutLen          [IN，OUT] 输入输出参数，输入表示给出 的缓冲区大小；输出表示实际读取返回的数据大小
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_FILEERR 文件错误；
//          SAR_READFILEERR 读文件错误；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_ReadFile(                      
						  IN     HAPPLICATION  hApplication,
                          IN     LPSTR         szFile,
						  IN     ULONG         ulOffset,
						  IN     ULONG         ulSize,
						  OUT    BYTE          *pbOutData,
						  IN OUT ULONG         *pulOutLen
						 );


/******************************************************************************************/
//写文件
//功能描述：写数据到应用文件中。对于数据在文件中的偏移量和有效数据的长度由写入者自行记录，这样
//          在对数据进行读操作时候才能读出有效的数据。
//参数：    
//          hApplication       [IN]  应用句柄
//          szFile             [IN]  文件名
//          ulOffset           [IN]  写文件需要的偏移量
//          pbData             [IN]  写入数据的缓冲区。
//          ulSize             [IN]  写入数据的大小
//          pulLen             [OUT] 实际写入数据的大小
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_FILEERR 文件错误；
//          SAR_WRITEFILEERR 写文件错误；
//          SAR_FILE_NOT_EXIST 文件不存在；
//          SAR_DATA_LEN_RANGE 数据长度错误。
//备注：    无
ULONG DEVAPI SKF_WriteFile(                         
				 		   IN  HAPPLICATION  hApplication,
                           IN  LPSTR         szFile,
						   IN  ULONG         ulOffset,
						   IN  BYTE          *pbData,
						   IN  ULONG         ulSize
                          );

/*****************************************************************************************/
/*
容器管理类  
*/
/*****************************************************************************************/
//创建容器
//功能够描述： 创建密钥容器。密钥容器是密钥库的一部分，一个密钥容器包含某个特定用户的所有非对称
//             密钥：签名密钥对，交换密钥对。签名密钥对用于数字签名和验证数字签名；交互密钥对用于
//             加密和解密，通常用于加密和解密会话密钥。创建密钥容器的时候，要为每个密钥容器指定唯一
//             的名称，创建成功后返回指向密钥容器的指针。  
//参数：     
//             hApplication       [IN]  应用句柄
//             szContainer       [IN]  容器名称
//             phContainer         [OUT] 返回的容器句柄
//返回值：     SAR_OK 表示成功， SAR_FAIL 返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_NAMELENERR 名称长度错误。
//备注：       无
ULONG DEVAPI SKF_CreateContainer(							     
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR         szContainer,
								 OUT HCONTAINER    *phContainer
								 );



/******************************************************************************************/
//删除密钥容器
//功能够描述： 在应用下删除指定名称的容器并释放容器相关的资源
//参数：       hApplication    [IN]  应用句柄
//             szContainerName [IN]  指向删除容器的名称 
//返回值：     SAR_OK 表示成功，SAR_FAIL返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效。
//备注：       无
ULONG DEVAPI SKF_DeleteContainer(
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR    szContainerName
								 );
/******************************************************************************************/
//打开容器
//功能够描述: 获取容器句柄
//参数:     hApplication    [IN]  应用句柄
//          szContainerName [IN]  容器名称
//          phContainer     [OUT] 返回打开容器的句柄
//返回值:   SAR_OK      : 成功
//          其他 :        错误码
ULONG DEVAPI SKF_OpenContainer(
								 IN  HAPPLICATION  hApplication,
								 IN  LPSTR    szContainerName,
								 OUT HCONTAINER    *phContainer
								 );

/******************************************************************************************/
//关闭容器
//功能够描述: 关闭容器句柄,并获取容器句柄相关资源
//参数:     hContainer     [IN] 容器的句柄                 
//返回值:   SAR_OK      : 成功
//          其他 :        错误码

ULONG DEVAPI SKF_CloseContainer(
								HCONTAINER hContainer
								);


/******************************************************************************************/
//枚举容器
//功能描述：列举出指定容器中以存在的密钥容器。
//参数：       
//             hApplication    [IN]      应用句柄
//             szContainerName     [IN]      返回容器名称列表；多个容器之间用'\0'分隔。 当为空时候由pulSize返回需要的缓冲区大小（规范中没有这样说明！）
//             pulSize         [IN OUT]  输入时候是容器列表缓冲区大小，输出时候是需要的缓冲区大小（规范中没有这样说明！说的是返回容器名的长度!）
//返回值：     SAR_OK表示成功， SAR_FAIL返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：       无
ULONG DEVAPI SKF_EnumContainer(							   
							   IN      HAPPLICATION  hApplication,
							   OUT     LPSTR         szContainerName,
							   IN OUT  ULONG         *pulSize       
		   					  );

/*****************************************************************************************/
/*
获得容器类型 
//功能够描述:获得容器的类型
//参数:     hContainer     [IN] 容器的句柄  
//出参：    pulContainerType [OUT] 容器类型
//返回值:   SAR_OK      : 成功
//          其他 :        错误码
*/
/*****************************************************************************************/
ULONG DEVAPI SKF_GetContainerType(							   
							      HCONTAINER hContainer,
							      OUT  ULONG  *pulContainerType  
		   					  );

/*****************************************************************************************/
/*
导入数字证书
//参数:     hContainer     [IN] 容器的句柄  
//参数:     bSignFlag      [IN] 证书类型 ，true表示签名证书，false表示加密证书 
//参数:     pbCert         [IN] 指向证书内容缓存  
//参数:     ulCertLen      [IN] 证书长度  
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
导出数字证书
//参数:     hContainer     [IN] 容器的句柄  
//参数:     bSignFlag      [IN] 证书类型 ，true表示签名证书，false表示加密证书 
//参数:     pbCert         [OUT] 指向证书内容缓存  
//参数:     ulCertLen      [IN,OUT] 证书长度  
//
*/
/*****************************************************************************************/

ULONG DEVAPI SKF_ExportCertificate(
	                                HCONTAINER hContainer, 
									BOOL bSignFlag, 
									BYTE* pbCert, 
									ULONG* ulCertLen);


/*
密钥服务类  
*/
/*****************************************************************************************/
//产生随机数
//功能描述：产生随机数。由 hDEV 句柄指向的设备的随机数发生器产生随机数，随机数长度为 ulRandomLen，
//          得到的随机数保存到 pbRandom指向的缓冲区。
//参数：    hDev           [IN]  输入参数，连接设备返回的设备句柄。
//          pbRandom       [OUT] 返回的随机数缓冲区。
//          ulRandomLen    [IN]  需要返回的随机数长度。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_GenRandom(
						   IN   DEVHANDLE  hDev,
                           OUT  BYTE       *pbRandom,
						   IN   ULONG      ulRandomLen
						   );


/*****************************************************************************************/
//
//功能描述：生成外部RSA密钥对
//参数：    hDev           [IN]  输入参数，连接设备返回的设备句柄。
//          ulBitsLen      [IN]  密钥模长
//          pBlob          [IN]  返回的私钥数据结构。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_GenExtRSAKey(
							  IN    DEVHANDLE     hDev,
							  IN    ULONG         ulBitsLen,
							  OUT   RSAPRIVATEKEYBLOB    *pBlob
							  );


/******************************************************************************************/
//生成RSA签名密钥对
//功能描述：生成RSA签名密钥对并输出签名公钥
//参数：                  
//             hContainer      [IN]  密钥容器句柄。          
//             ulBitLen        [IN]  公私钥对的模长
//             pBlob           [OUT] 返回的RSA公钥数据结构
//返回值：     SAR_OK 表示成功，SAR_FAIL 返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效；
//             SAR_TIMEOUTERR 超时。
//备注：       权限要求: 须具备用户权限
ULONG DEVAPI SKF_GenRSAKeyPair(
							   IN   HCONTAINER    hContainer,
							   IN   ULONG         ulBitLen,
                               OUT  RSAPUBLICKEYBLOB *pBlob
							   );

/******************************************************************************************/
/******************************************************************************************/
//功能描述：导入RSA加密密钥对
//参数：       hContainer   [IN]  容器句柄
//             ulSymAlgId   [IN]  对称算法密钥标识。
//             pbWrappedKey [IN]  使用该容器内签名公钥保护的对称算法密钥
//             ulWrappedKeyLen[IN]保护的对称算法密钥长度
//             pbEncryptedData[IN]对称算法密钥保护的RSA加密私钥。私钥的格式
//                  遵循PKCS#1V2.1:RSA Cryptography Standard中的私钥格式定义				
//             ulEncryptedData[IN]对称算法密钥保护的RSA加密公私钥对长度。
//返回值：     SAR_OK 表示成功，SAR_FAIL 返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效。
//备注：       无
ULONG DEVAPI SKF_ImportRSAKeyPair(
                                  
								  IN   HCONTAINER    hContainer,
								  IN   ULONG         ulSymAlgId,
                                  IN   BYTE          *pbWrappedKey, 
								  IN   ULONG         ulWrappedKeyLen,
								  IN   BYTE          *pbEncryptedData,
								  IN   ULONG         ulEncryptedData
								  );

/******************************************************************************************/
//功能描述：RSA签名 使用hCountainer指定容器的签名私钥，对指定数据pbData进行数据签名。签名后的
//结果存放到pbSignature缓冲区,设置pulSignLen为签名的长度
//参数:   hContainer   [IN]  用来签名的私钥所在的容器密钥
//        pbData       [IN]  被签名的数据
//        ulDataLen    [IN]  签名数据的长度，应不大于RSA密钥模长-11
//        pbSignature  [OUT] 存放签名结果的缓冲区指针，如果值为NULL，用于取得签名结果长度
//        pulSignLen   [IN OUT] 输入为签名结果缓冲区大小，输出为签名结果长度
//返回值: SAR_OK:      成功
//        其他  :      错误码
ULONG  DEVAPI SKF_RSASignData(
							  IN     HCONTAINER hContainer,
							  IN     BYTE *pbData,
							  IN     ULONG ulDataLen,
							  OUT    BYTE* pbSignature,
							  IN OUT ULONG *pulSignLen
							  );

/******************************************************************************************/
//验证RSA签名
//功能描述：用RSA公钥对数据签名进行验签，与原始数据对比，若验签后的数据与原始数据相同，则说
//          明签名是有效的，否则签名无效。
//参数：    hDev           [IN]  输入参数，连接设备返回的设备句柄。
//          pRSAPubKeyBlob [IN]  RSA 公钥数据结构
//          pbData         [IN]  待验证签名的数据
//          ulDataLen      [IN]  数据长度，不大于公钥模长-11
//          pbSignature    [IN]  待验证的签名值
//          ulSigLen       [IN]  签名值长度,必须为公钥模长 
//返回值：  SAR_OK 表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_MEMORYERR 发生内存错误；
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_INVALIDHANDLEERR 句柄无效；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_KEYNOTFOUNTERR 密钥未发现；
//          SAR_INDATAERR 输入数据错误。
//备注：    无
ULONG DEVAPI SKF_RSAVerify(
						   IN   DEVHANDLE     hDev,
						   IN   RSAPUBLICKEYBLOB *pRSAPubKeyBlob,						   						  
                           IN   BYTE          *pbData,
						   IN   ULONG         ulDataLen,
						   IN   BYTE          *pbSignature,
						   IN   ULONG         ulSigLen
						  );

/******************************************************************************************/
//功能描述：生成会话密钥并用外部公钥加密输出
//参数：       hContainer    [IN]     容器句柄
//             ulAlgId       [IN]     会话密钥算法标识
//             pPubKey       [IN]     加密会话密钥的RSA公钥数据结构
//             pbData        [OUT]    导出的加密会话密钥密文，按照PKCS#1V1.5要求封装。
//             pulDataLen    [IN OUT] 返回导出数据长度
//             phSessionKey  [OUT]    导出的密钥句柄   
//返回值：     SAR_OK 表示成功，SAR_FAIL返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效；
//             SAR_KEYNOTFOUNTERR 密钥未发现。
//备注：       无
ULONG DEVAPI SKF_RSAExportSessionKey(
								  IN      HCONTAINER     hContainer,
								  IN      ULONG          ulAlgId,
								  IN      RSAPUBLICKEYBLOB *pPubKey,								  
								  OUT     BYTE          *pbData,
								  IN OUT  ULONG         *pulDataLen,
                                  OUT     HANDLE  *    phSessionKey
								  );

/******************************************************************************************/
//功能描述：RSA外来公钥运算,使用外部传入的RSA公钥对输入数据做公钥运算并输出结果
//参数:   hDev  [IN]  设备句柄
//        pRSAPubKeyBlob  [IN] RSA公钥数据结构
//        pbInput         [IN] 指向待运算的原始数据缓冲区
//        ulInputLen      [IN] 待运算原始数据的长度，必须为公钥模长
//        pbOutput        [IN] 指向RSA公钥运算
//        pulOutputLen    [IN OUT]调用前表示pbOutput 缓冲区的长度，返回RSA公钥运算结果的实际长度
//返回值: SAR_OK:      成功
//        其他  :      错误码
ULONG  DEVAPI  SKF_ExtRSAPubKeyOperation(
										 IN   DEVHANDLE        hDev,					
										 IN   RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
										 IN   BYTE             *pbInput,
										 IN   ULONG            ulInputLen,
										 OUT  BYTE             *pbOutput,
										 OUT  ULONG            *pulOutputLen
										 );

/******************************************************************************************/
//功能描述：RSA外来私钥运算,使用外部传入的RSA私钥对输入数据做私钥运算并输出结果
//参数:   hDev  [IN]  设备句柄
//        pRSAPriKeyBlob  [IN] RSA私钥数据结构
//        pbInput         [IN] 指向待运算的原始数据缓冲区
//        ulInputLen      [IN] 待运算原始数据的长度，必须为公钥模长
//        pbOutput        [IN] 指向RSA私钥运算，如果参数为NULL，则由pulOutputLen返回运算结果的实际长度
//        pulOutputLen    [IN OUT]调用前表示pbOutput 缓冲区的长度，返回RSA私钥运算结果的实际长度
//返回值: SAR_OK:      成功
//        其他  :      错误码
ULONG  DEVAPI  SKF_ExtRSAPriKeyOperation(
										 IN   DEVHANDLE        hDev,					
										 IN   RSAPRIVATEKEYBLOB *pRSAPriKeyBlob,
										 IN   BYTE             *pbInput,
										 IN   ULONG            ulInputLen,
										 OUT  BYTE             *pbOutput,
										 OUT  ULONG            *pulOutputLen
										 );




/******************************************************************************************/
//功能够描述：导出公钥           
//参数：       hContainer    [IN]    容器句柄
//             bSignFlag     [IN]    TRUE表示导出签名公钥，FALSE表示导出加密公钥。
//             pbBlob        [OUT]   指向RSA公钥结构或者ECC公钥结构，如果此参数为NULL，
//                                   由pulBlobLen返回pbBlob的长度。
//             pulBlobLen    [IN,OUT]调用时表示pbBlob的长度，返回导出公钥结构的大小
//返回值：     SAR_OK 表示成功，SAR_FAIL 返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效；
//             SAR_KEYNOTFOUNTERR 密钥未发现。
//备注：       无
ULONG DEVAPI SKF_ExportPublicKey(								
									IN      HCONTAINER    hContainer,
									IN      BOOL          bSignFlag,
									OUT     BYTE*          pbBlob,
									IN OUT  ULONG         *pulBlobLen
								  );

/******************************************************************************************/
//功能描述：导入会话密钥
//参数：       hContainer   [IN]  容器句柄
//             ulAlgId      [IN]  会话密钥算法标识
//             pbWrapedData [IN]  要导入的会话密钥密文
//             ulWrapedLen  [IN]  会话密钥密文长度
//             phKey        [OUT] 返回的密钥句柄
//返回值：     SAR_OK 表示成功， SAR_FAIL返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效。
//备注：       无

ULONG DEVAPI SKF_ImportSessionKey(
								  IN   HCONTAINER     hContainer,
								  IN   ULONG          ulAlgId,
								  IN   BYTE           *pbWrapedData,
								  IN   ULONG          ulWrapedLen,
								  OUT  HANDLE         *phKey
								  );


/******************************************************************************************/
//功能描述：明文导入会话密钥，设置明文对称密钥，返回密钥句柄
//参数：       hDev         [IN]  设备句柄
//             pbKey        [IN]  指向会话密钥值的缓冲区
//             ulAlgId      [IN]  会话密钥算法标识
//             phKey        [OUT] 返回会话密钥句柄
//返回值：     SAR_OK 表示成功， SAR_FAIL返回失败。
//             返回其他错误值：
//             SAR_MEMORYERR 发生内存错误；
//             SAR_UNKNOWNERR 发生未知错误；
//             SAR_INVALIDHANDLEERR 句柄无效；
//             SAR_INVALIDPARAMERR 参数无效。
//备注：       无
ULONG  DEVAPI   SKF_SetSymmKey(
							   IN DEVHANDLE hDev,
							   IN BYTE * pbKey,
							   IN ULONG ulAlgId,
							   OUT HANDLE *phKey
							   );

/******************************************************************************************/
//数据加密初始化
//功能描述：设置数据加密的算法相关参数。
//参数：    hKey           [IN]  加密密钥句柄      
//          EncryptParam   [IN]  分组密码算法相关参数：初时向量、初时向量长度、
//                               填充方式、反馈值的位长度。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误
//          SAR_MEMORYERR 发生内存错误
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_EncryptInit(					
							 IN   HANDLE             hKey,
							 IN   BLOCKCIPHERPARAM   EncryptParam
							 );



/******************************************************************************************/
//单组数据加密
//功能描述：单一分组数据的加密操作。用指定加密密钥对指定数据进行加密，被加密的数据只包含
//一个分组，加密后的密文保存到指定的缓冲区中。SKF_Encrypt 只对单个分组数据进行加密，在调用
//SKF_Encrypt之前，必须调用SKF_EncryptInit初始化加密操作。SKF_Encrypt等价于先调用SKF_EncryptUpdate
//再调用SKF_EncryptFinal。
//参数：    hKey            [IN]     加密密钥句柄。
//          pbData          [IN]     待加密数据
//          ulDataLen       [IN]     待加密数据长度
//          pbEncryptedData [OUT]    加密后的数据缓冲区指针，可以为NULL，用于获得加密后的数据长度
//          pulEncryptedLen [IN OUT] 输入，给出的缓冲区大小，输出，返回加密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_Encrypt(
						 IN   HANDLE       hKey,				
						 IN   BYTE          *pbData,
						 IN   ULONG         ulDataLen,
						 OUT  BYTE          *pbEncryptedData,
						 OUT  ULONG         *pulEncryptedLen
						 );

/******************************************************************************************/
//多组数据加密。
//功能描述：用指定加密密钥对指定数据进行加密，被加密的数据包含多个分组，加密后的密文保存到指定的
//          缓冲区中。在调用SKF_EncryptUpdate之前，必须调用SKF_EncryptInit初始化加密操作。在调用SKF_EncryptUpdate
//          之后，必须调用SKF_EncryptFinal结束加密操作。         
//参数：    hKey            [IN]  加密密钥句柄
//          pbData          [IN]  待加密数据
//          ulDataLen       [IN]  待加密数据长度
//          pbEncryptedData [OUT] 加密后数据缓冲区指针
//          pulEncryptedLen [OUT] 返回加密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_EncryptUpdate(
							   IN   HANDLE        hKey,
							   IN   BYTE          *pbData,
							   IN   ULONG         ulDataLen,
							   OUT  BYTE          *pbEncryptedData,
							   OUT  ULONG         *pulEncryptedLen
							   );


/******************************************************************************************/
//结束加密
//功能描述：结束多个分组数据的加密，返回剩余加密结果。先调用SKF_EncryptInit初始化加密操作，
//          再调用，SKF_EncryptUpdate对多个分组数据进行加密，最后调用SKF_EncryptFinal结束
//          多个分组数据的加密。  
//参数：    hKey               [IN]  加密密钥句柄
//          pbEncryptedData    [OUT] 加密后数据缓冲区指针
//          ulEncryptedDataLen [OUT] 返回加密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_EncryptFinal(							
							  IN   HANDLE        hKey,
							  OUT  BYTE          *pbEncryptedData,
							  OUT  ULONG         *ulEncryptedDataLen							
							  );

/******************************************************************************************/
//数据解密初始化
//功能描述：数据解密初时化，设置解密密钥相关参数。调用SKF_DecryptInit之后，可以调用SKF_Decrypt
//          对单个分组数据进行解密，也可以多次调用SKF_DecryptUpdate之后再调用SKF_DecryPtFinal完成
//          对多个分组数据的解密。        
//参数：    hKey           [IN]  解密密钥句柄
//          DecryptParam   [IN]  分组密码算法相关参数：算法标志号、密钥长度、初时向量、初时向量长度、
//                               填充方式、加密模式、反馈值的位长度。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_DecryptInit(
							 IN   HANDLE             hKey,
							 IN   BLOCKCIPHERPARAM   DecryptParam
							 );


/******************************************************************************************/
//单组数据的解密操作。
//功能描述：用指定解密密钥对指定的数据进行解密操作，被解密的数据只包含一个分组，解密后的数据保存在
//          一个指定的缓冲区中。SKF_Decrypt只对单个分组进行解密，在调用SKF_Decrypt之前，必须调用SKF_DecryptInit
//          初始化解密操作。SKF_Decrypt等价与先调用SKF_DecryptUpdate再调用SKF_DecryptFinal，SKF_Decrypt不能与
//          SKF_DecryptUpdate间隔调用。
  
//参数：    hKey            [IN]  解密密钥
//          pbEncryptedData [IN]  待解密数据
//          ulEncryptedLen  [IN]  待解密数据长度
//          pbData          [OUT] 指向解密后的数据缓冲区指针
//          pulDataLen      [IN OUT] 返回解密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    无
ULONG DEVAPI SKF_Decrypt(			
						 IN    HANDLE        hKey,
						 IN    BYTE          *pbEncryptedData,
						 IN    ULONG         ulEncryptedLen,
						 OUT   BYTE          *pbData,
						 OUT   ULONG         *pulDataLen
						 );

/******************************************************************************************/
//多组数据的解密操作。
//功能描述：用指定解密密钥对指定数据进行解密，被解密的数据包含多个分组，解密后的明文保存到指定的
//          缓冲区中。在调用SKF_DecryptUpdate之前，必须调用SKF_DecryptInit初始化解密操作。在调用SKF_DecryptUpdate
//          之后，必须调用SKF_DecryptFinal结束解密操作。
       
//参数：    hKey            [IN]     加密密钥句柄
//          pbEncryptedData [IN]     待解密数据
//          ulEncryptedLen  [IN]     待解密数据长度
//          pbData          [OUT]    指向解密后的数据缓冲区指针
//          pulDataLen      [IN OUT] 返回解密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_DecryptUpdate(							 
							   IN    HANDLE        hKey,
							   IN    BYTE          *pbEncryptedData,
							   IN    ULONG         ulEncryptedLen,
							   OUT   BYTE          *pbData,
							   OUT   ULONG         *pulDataLen
							   );


/******************************************************************************************/
//结束多个分组数据的解密
//功能描述：先调用SKF_DecryptInit初始化解密操作，再调用SKF_DecryptUpdate对多个分组数据进行解密，最后
//          调用SKF_DecryptFinal结束多个分组数据的解密。
//参数：    hKey              [IN]     解密密钥
//          pbDecryptData     [OUT]    指向解密后的数据缓冲区指针
//          pulDecryptDataLen [IN OUT] 返回解密后的数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERT 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    无
ULONG DEVAPI SKF_DecryptFinal(							 
							  IN      HANDLE        hKey,
							  OUT     BYTE          *pbDecryptedData,
							  IN OUT  ULONG         *pulDecryptedDataLen							
							 );


/******************************************************************************************/
//杂凑初始化
//功能描述：初始化消息杂凑计算操作，指定计算消息杂凑的算法。
//参数：    hDev            [IN]  输入参数，连接设备返回的设备句柄。
//          ulAlgID         [IN]  杂凑算法标识。
//          phHash          [OUT] 杂凑对象句柄。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足；
//          SAR_HASHOBJERR HASH对象错误；
//          SAR_HASHERR HASH错误。
//备注：    调用SKF_DigestInit之后，可以调用SKF_Digest
//          对单一分组数据计算消息摘要，也可以多次调用SKF_DigestUpdate之后再调用SKF_DigestFinal对多个数据分组
//          计算消息摘要。
ULONG DEVAPI SKF_DigestInit(
							IN   DEVHANDLE  hDev,
							IN   ULONG      ulAlgID,
							IN   ECCPUBLICKEYBLOB *pPubKey, 
							IN   unsigned char *pucID, 
							IN   ULONG ulIDLen,
							OUT  HANDLE     *phHash
						   );

/******************************************************************************************/
//单组数据杂凑
//功能描述：对单一分组的消息进行杂凑计算。 
//参数：    hHash           [IN]      杂凑对象句柄
//          pbData          [IN]      指向消息数据的缓冲区
//          ulDataLen       [IN]      消息数据长度
//          pbHashData      [OUT]     杂凑数据缓冲区指针，当此参数为NULL时，由pulHashLen返回
//                                    杂凑结果的长度
//          pulHashLen      [IN OUT]  调用时表示pblHashData缓冲区的长度，返回杂凑结果的长度。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足；
//          SAR_HASHOBJERR HASH对象错误；
//          SAR_HASHERR HASH错误。
//备注：    调用SKF_Digest之前，必须调用SKF_DigestInit初始化摘要计算。
//          SKF_Digest等价于多次调用SKF_DigestUpdate之后调用SKF_DigestFinal。
ULONG DEVAPI SKF_Digest(
						IN      HANDLE     hHash,
						IN      BYTE       *pbData,
						IN      ULONG      ulDataLen,
						OUT     BYTE       *pbHashData,
						IN OUT  ULONG      *pulHashLen
						);


/******************************************************************************************/
//多组数据杂凑
//功能描述：对多个分组的消息进行杂凑计算
//参数：    hHash           [IN]  杂凑对象句柄
//          pbData          [IN]  指向消息数据的缓冲区
//          ulDataLen       [IN]  消息数据的长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足；
//          SAR_HASHOBJERR HASH对象错误；
//          SAR_HASHERR HASH错误。
//备注：    调用SKF_DigestUpdate之前，必须调用SKF_DigestInit
//          初始化摘要计算操作。调用SKF_DigestUpdate之后，必须调用SKF_DigestFinal结束摘要计算。
ULONG DEVAPI SKF_DigestUpdate(
							  IN   HANDLE     hHash,
							  IN   BYTE       *pbData,
							  IN   ULONG      ulDataLen
							 );

/******************************************************************************************/
//结束杂凑
//功能描述 ：结束多个分组消息的杂凑计算操作，将杂凑保存到指定的缓冲区。
//参数：    hHash           [IN]     杂凑对象句柄
//          pHashData       [OUT]    返回的杂凑数据缓冲区指针，如果此参数NULL时，由pulHashLen
//                                   返回杂凑结果的长度
//          pulHashLen      [IN OUT] 调用时表示杂凑结果的长度，返回杂凑数据的长度
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足；
//          SAR_HASHOBJERR HASH对象错误；
//          SAR_HASHERR HASH错误。
//备注：    SKF_DigestFinal 必须用于SKF_DigestUpdate之后
ULONG DEVAPI SKF_DigestFinal(							
                             IN      HANDLE     hHash,
							 OUT     BYTE       *pHashData,
							 IN OUT  ULONG      *pulHashLen
						    );


/******************************************************************************************/
//消息鉴别码运算初始化
//功能描述：初始化消息鉴别码计算操作，设置计算消息鉴别码的密钥参数，并返回消息消息鉴别码句柄。 
//参数：    hKey            [IN]  计算消息鉴别码的密钥句柄
//          pMacParam       [IN]  消息认证计算相关参数，包括初始向量、初始向量长度、填充方法等。 
//          phMac           [OUT] 消息鉴别码对象句柄
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    消息鉴别码计算采用分组加密算法的CBC模式，将加密结果的最后一块作为计算结
//          果。待计算数据的长度必须是分组加密算法块长的倍数，接口内部不做数据填充。
ULONG DEVAPI SKF_MacInit(
						 IN   HANDLE              hKey,
						 IN   BLOCKCIPHERPARAM   * MacParam,
                         OUT  HANDLE              *phMac
					    );



/******************************************************************************************/
//单组数据的消息鉴别码运算。
//功能描述：SKF_Mac 计算单一分组数据的消息鉴别码
//参数:     hMac            [IN]     消息鉴别码句柄
//          pbData          [IN]     指向待计算数据的缓冲区 
//          ulDataLen       [IN]     待计算数据长度
//          pbMacData       [OUT]    指向计算后的Mac结果，如果此参数为NULL时，由pulMacLen
//                                   返回计算后Mac结果的长度。
//          pulMacLen       [IN OUT] 调用时表示pbMacData缓冲区的长度，返回计算Mac结果的长度。
//返回值：  SAR_OK 表示成功，SAR_FAIL 返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_MACLENERR MAC长度错误。
//备注：    在调用SKF_Mac之前，必须调用SKF_MacInit
//          初始化消息认真码操作。SKF_Mac等价于多次调用SKF_MacUpdate再调用SKF_MacFinal。 
ULONG DEVAPI SKF_Mac(
					 IN      HANDLE     hMac,
					 IN      BYTE       *pbData,
					 IN      ULONG      ulDataLen,
					 OUT     BYTE       *pbMacData,
					 IN OUT  ULONG      *pulMacLen
				    );

/******************************************************************************************/
//多组数据消息鉴别码运算。
//功能描述：计算多个分组数据的消息鉴别码  
//参数：    hMac            [IN]  消息认证码句柄
//          pbData          [IN]  待加密数据
//          ulDataLen       [IN]  待加密数据长度
//返回值：  SAR_OK 表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效；
//          SAR_BUFFER_TOO_SMALL 缓冲区不足。
//备注：    在调用SKF_MacUpdate之前，必须调用SKF_MacptInit初始化消息认真码计算操作。在调用SKF_MacUpdate
//          之后，必须调用SKF_MacFinal结束多个分组数据的消息认证码计算操作。
ULONG DEVAPI SKF_MacUpdate(
						   IN   HANDLE     hMac,
						   IN   BYTE       *pbData,
						   IN   ULONG      ulDataLen
						  );


/******************************************************************************************/
//结束消息鉴别码运算
//功能描述：结束多个分组数据的消息认证码计算操作。
//参数：    hMac            [IN]  消息鉴别码句柄   
//          pbMacData       [OUT] 指向消息鉴别码的缓冲区，当此参数为NULL为时，由pulMacDataLen
//                                返回消息鉴别码返回的长度
//          pulMacDataLen   [OUT] 调用时表示消息鉴别码缓冲区的最大长度，返回消息鉴别码的长度
//返回值：  SAR_OK 表示成功，SAR_FAIL返回失败。
//          返回其他错误值：
//          SAR_UNKNOWNERR 发生未知错误；
//          SAR_MEMORYERR 发生内存错误；
//          SAR_INVALIDPARAMERR 参数无效。
//备注：    SKF_MacFinal 必须用于SKF_MacUpdate之后。
ULONG DEVAPI SKF_MacFinal(
					      IN   HANDLE     hMac,
						  OUT  BYTE       *pbMacData,
						  OUT  ULONG      *pulMacDataLen
						 );

/******************************************************************************************/
//功能: 关闭会话密钥、杂凑、消息鉴别码、ECC密钥协商句柄。
//参数: hHandle    [IN] 要关闭的对象句柄
//返回值: SAR_OK   :成功。
//        其他     :错误码。
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