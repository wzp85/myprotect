#ifndef _PKISERVERAPIDEF_H_
#define _PKISERVERAPIDEF_H_

#include <stdio.h>
#include <string.h>

/*
//对称算法标识
#define SGD_3DES_ECB	0x00000001	//SM1算法ECB加密模式
#define SGD_3DES_CBC	0x00000002	//SM1算法CBC加密模式
#define SGD_3DES_CFB	0x00000004	//SM1算法CFB加密模式
#define SGD_3DES_OFB	0x00000008	//SM1算法OFB加密模式
#define SGD_3DES_MAC	0x00000010	//SM1算法MAC加密模式

#define SGD_SM1_ECB		0x00000101	//SM1算法ECB加密模式
#define SGD_SM1_CBC		0x00000102	//SM1算法CBC加密模式
#define SGD_SM1_CFB		0x00000104	//SM1算法CFB加密模式
#define SGD_SM1_OFB		0x00000108	//SM1算法OFB加密模式
#define SGD_SM1_MAC		0x00000110	//SM1算法MAC加密模式
#define SGD_SSF33_ECB	0x00000201	//SSF33算法ECB加密模式
#define SGD_SSF33_CBC	0x00000202	//SSF33算法CBC加密模式
#define SGD_SSF33_CFB	0x00000204	//SSF33算法CFB加密模式
#define SGD_SSF33_OFB	0x00000208	//SSF33算法OFB加密模式
#define SGD_SSF33_MAC	0x00000210	//SSF33算法MAC加密模式
*/
#define SGD_SM4_ECB		0x00000401	//SSF33算法ECB加密模式
#define SGD_SM4_CBC		0x00000402	//SSF33算法CBC加密模式
#define SGD_SM4_CFB		0x00000404	//SSF33算法CFB加密模式
#define SGD_SM4_OFB		0x00000408	//SSF33算法OFB加密模式
#define SGD_SM4_MAC		0x00000410	//SSF33算法MAC加密模式

/*
#define  SGD_RC2_ECB	0x80000001
#define  SGD_RC2_CBC	0x80000002

#define  SGD_RC4_ECB	0x40000001

#define  SGD_AES_ECB	0x20000001
#define  SGD_AES_CBC	0x20000002

#define	 SGD_3DES_ECB	0x10000001
*/
#define  SGD_RC2_ECB	0x08000001
#define  SGD_RC2_CBC	0x08000002

#define  SGD_RC4_ECB	0x04000001

#define  SGD_AES_ECB	0x02000001
#define  SGD_AES_CBC	0x02000002

//#define	 SGD_3DES_ECB	0x01000001
//非对称算法标识
#define SGD_RSA			0x00010000	//RSA算法
#define SGD_SM2_1		0x00020100	//椭圆曲线签名算法
#define SGD_SM2_2		0x00020200	//椭圆曲线密钥交换协议
#define SGD_SM2_3		0x00020400	//椭圆曲线加密算法

//杂凑算法标识
#define SGD_SM3			0x00000001	//SM3杂凑算法
#define SGD_SHA1		0x00000002	//SHA1杂凑算法
#define SGD_SHA256		0x00000004	//SHA256杂凑算法


#define SGD_SHA224		0x10000001
#define SGD_SHA384  0x10000002
#define SGD_SHA512  0x10000004
#define SGD_MD2		0x10000008
//#define SGD_MD5		0x10000010

#ifdef _56PKISERVER_

//56所加密算法

//对称算法机制： 
#define SDM_SCB2_ECB	0x00000001// SCB2 ECB加密机制
#define SDM_SCB2_CBC	0x00000002// SCB2 CBC加密机制
#define SDM_SCB2_CFB	0x00000004// SCB2 CFB加密机制
#define SDM_SCB2_OFB	0x00000008// SCB2 OFB加密机制
#define SDM_SCB2_MAC	0x00000010// SCB2 MAC机制

//非对称算法机制：
#define SDM_RSA			0x00000001// RSA算法机制

//HASH算法机制：
#define SDM_MD5			0x00000001
#define SDM_SHA1		0x00000002// SHA-1算法机制
#define SDM_SHA256		0x00000004

#endif


//typedef struct DeviceInfo_st{
//unsigned char IssuerName[40];
//unsigned char DeviceName[16];
//unsigned char DeviceSerial[16];
//unsigned int  DeviceVersion;
//unsigned int  StandardVersion;
//unsigned int  AsymAlgAbility[2];
//unsigned int  SymAlgAbility;
//unsigned int  HashAlgAbility;
//unsigned int  BufferSize;
//}DEVICEINFO;

#define RSAref_MAX_BITS    2048

#define RSAref_MAX_LEN     ((RSAref_MAX_BITS + 7) / 8)
#define RSAref_MAX_PBITS   ((RSAref_MAX_BITS + 1) / 2)
#define RSAref_MAX_PLEN    ((RSAref_MAX_PBITS + 7)/ 8)
/*typedef struct RSArefPublicKey_st
{
unsigned int  bits;
unsigned char m[RSAref_MAX_LEN];
unsigned char e[RSAref_MAX_LEN];
} RSArefPublicKey;
*/
//typedef struct RSArefPrivateKey_st
//{
//unsigned int  bits;
//unsigned char m[RSAref_MAX_LEN];
//unsigned char e[RSAref_MAX_LEN];
//unsigned char d[RSAref_MAX_LEN];
//unsigned char prime[2][RSAref_MAX_PLEN];
//unsigned char pexp[2][RSAref_MAX_PLEN];
//unsigned char coef[RSAref_MAX_PLEN];
//} RSArefPrivateKey;


//#define ECCref_MAX_BITS			256 
//#define ECCref_MAX_BITS			512   syc
#define ECCref_MAX_LEN			((ECCref_MAX_BITS+7) / 8)
//typedef struct ECCrefPublicKey_st
//{
//	unsigned int  bits;
//	unsigned char x[ECCref_MAX_LEN]; 
//	unsigned char y[ECCref_MAX_LEN]; 
//} ECCrefPublicKey;

//typedef struct ECCrefPrivateKey_st
//{
//    unsigned int  bits;
//    //unsigned char D[ECCref_MAX_LEN];
//	unsigned char K[ECCref_MAX_LEN];
//} ECCrefPrivateKey;


//typedef struct ECCCipher_st
//{
//	unsigned char x[ECCref_MAX_LEN]; 
//	unsigned char y[ECCref_MAX_LEN];	
//   //unsigned char M[ECCref_MAX_LEN];
//	unsigned char M[32];
//	unsigned int L;
//	unsigned char C[ECCref_MAX_LEN];
//} ECCCipher;


//typedef struct ECCSignature_st
//{
//	unsigned char r[ECCref_MAX_LEN];	
//	unsigned char s[ECCref_MAX_LEN];	
//} ECCSignature;


#endif