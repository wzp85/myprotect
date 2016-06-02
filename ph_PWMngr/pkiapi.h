//////////////////////////////////////////////////////////////////////////
//																		//	
//								APPDLL的导出函数						//
//																		//
//////////////////////////////////////////////////////////////////////////
#ifndef PKIAPI_H
#define PKIAPI_H
#include "globalcert.h"
//#include "code.h"

/*
#ifdef WHLINUX
#include "../include/whcrypt.h"
#else
#include <WinCrypt.h>
#endif
*/


#define MAX_LABEL_SIZE	255
#define MAX_PASSWD_SIZE MAX_LABEL_SIZE

#define CALG_PMC3DES1 11
#define CALG_PMC3DES2 12
#define CALG_PMC3DES3 13
#define CALG_PMC3DES4 14
#define CALG_PMC3DES5 15

#define CALG_PMCHASH 32773

/* A macro to make make declaring DER Coding */

#define MKDER( value )	( ( BYTE * ) value )

#define MAXPUBKEYBLOBLEN	276		//PUBKEYBLOB的最大长度
#define MAXSIMPLEBLOBLEN	268		//SIMPLEBLOB的最大长度
#define	MAXSIGNATURE		256		//签名的最大长度
//版本
#define X509_VERSION_V1 MKDER("\xa0\x03\x02\x01\x00")
#define X509_VERSION_V2 MKDER("\xa0\x03\x02\x01\x01")
#define X509_VERSION_V3 MKDER("\xa0\x03\x02\x01\x02")
#define X509_VERSION_V4 MKDER("\xa0\x03\x02\x01\x03")
#define CRL_VERSION_V2 MKDER("\x02\x01\x01")
#define AA_VERSION_V1 MKDER("\x02\x01\x00")
#define AA_VERSION_V2 MKDER("\x02\x01\x01")
//初始序列号
#define SERIALNUMBER MKDER("\x02\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00") 
//签名算法
#define ALGO_SHA1RSA MKDER("\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D\x01\x01\x05\x05\x00")
#define ALGO_RSARSA  MKDER("\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D\x01\x01\x01\x05\x00")

//Distinguished Name
#define DN_C  MKDER("\x06\x03\x55\x04\x06")
#define DN_S  MKDER("\x06\x03\x55\x04\x08")
#define DN_L  MKDER("\x06\x03\x55\x04\x07")
#define DN_O  MKDER("\x06\x03\x55\x04\x0A")
#define DN_OU MKDER("\x06\x03\x55\x04\x0B")
#define DN_CN MKDER("\x06\x03\x55\x04\x03")
#define DN_DC  MKDER("\x06\x0a\x09\x92\x26\x89\x93\xf2\x2c\x64\x01\x19")//modify by shenjun at 20090423 add "DN_DC"
#define DN_E  MKDER("\x06\x09\x2a\x86\x48\x86\xf7\x0d\x01\x09\x01")

//扩展项
#ifdef GB_VERSION
#define X509_SUBJECT_KEYID MKDER("\x30\x29\x06\x03\x55\x1D\x0E\x04\x22\x04\x20")
#define X509_ISSUER_KEYID MKDER("\x30\x2B\x06\x03\x55\x1D\x23\x04\x24\x30\x22\x80\x20")	
#else
#define X509_SUBJECT_KEYID MKDER("\x30\x1D\x06\x03\x55\x1D\x0E\x04\x16\x04\x14")
#define X509_ISSUER_KEYID MKDER("\x30\x1F\x06\x03\x55\x1D\x23\x04\x18\x30\x16\x80\x14")
#endif
	
#define X509_KEYUSAGE_ENC MKDER("\x30\x0E\x06\x03\x55\x1D\x0F\x01\x01\xFF\x04\x04\x03\x02\x05\x20")
#define X509_KEYUSAGE_SIG MKDER("\x30\x0E\x06\x03\x55\x1D\x0F\x01\x01\xFF\x04\x04\x03\x02\x06\xC0")
#define X509_KEYUSAGE_ROOT MKDER("\x30\x0E\x06\x03\x55\x1D\x0F\x01\x01\xFF\x04\x04\x03\x02\x01\x06")

#define X509_CACERT_BASICCONSTRAIN MKDER("\x30\x0F\x06\x03\x55\x1D\x13\x01\x01\xFF\x04\x05\x30\x03\x01\x01\xFF")

#define CA_VERSION_0 MKDER("\x30\x10\x06\x09\x2B\x06\x01\x04\x01\x82\x37\x15\x01\x04\x03\x02\x01\x00")

typedef enum{
	ROOTCERT,
		SIGCERT,
		ENCCERT,
		SINGLECERT
}CERT_TYPE;


typedef unsigned int ALG_ID;



//////////////////////////////////////////////////////////////////////////
//																		//
//								数据结构和接口定义						//
//																		//
//////////////////////////////////////////////////////////////////////////


typedef struct _CRYPTOAPI_BLOB_ 
{
  DWORD    cbData;
  BYTE*    pbData;
}ANYVALUE,  *PANYVALUE,					//任意数据
CERT_INDEX,     *PCERT_INDEX,			//证书索引号
CERTSTORE_INDEX,  *PCERTSTORE_INDEX,	//证书库存储块的索引号
CERT_CONTENT,    *PCERT_CONTENT;		//整个完整的证书内容。


typedef enum {
  LBL_CONFIG,
  LBL_CERT,
  LBL_KEY,
  LBL_OTHER
}LABEL_TYPE;

typedef enum {
  MODE_RD,
  MODE_WR,
  MODE_RW
}LABEL_MODE;

typedef struct CRL_LIST {
  BYTE     serialNumber[30];
  BYTE     revokeTime[20];
  BYTE     reasonCode;
  struct CRL_LIST *next;

}CRL_LIST;

typedef struct PKI_CRLINFO{
  SIGNCERT_SUBJECT issuer;
  TIME_PERIOD time;
  CRL_LIST *certList;
}PKI_CRLINFO;

//////////////////////////////////////////////////////////////////////////
//		PA相关的数据结构

typedef struct PA_CERTREQ_INFO{
	NAME_INFO  nameInfo;  
	int		countOfExtension;  
	EXTENTIONS* extensions;	//Array Point
}PA_CERTREQ_INFO;

typedef struct PA_CERTINFO{
	int version;   
	NAME_INFO nameInfo;   
	BYTE signatureAlgo[30];   
	PKI_DATA serialNumber;   
	TIME_PERIOD validTime;   
	int	countOfExtension;   
	PKI_DATA extensions;	
}PA_CERTINFO;
//////////////////////////////////////////////////////////////////////////

typedef struct ATTRIBUTES{
	PKI_DATA attrOID; 
	int      attrDataType;  //BMP STRING(0x1E), BIT STRING(0x03)
	PKI_DATA attrValue;
} ATTRIBUTES;


typedef struct ATTR_CERTINFO{
  int version;
  NAME_INFO holder;
  NAME_INFO issuer;
  PKI_DATA  holderSerialNumber;
  PKI_DATA  issuerSerialNumber;
  BYTE signatureAlgo[30];
  PKI_DATA serialNumber;
  TIME_PERIOD validTime;
  int		countOfAttribute;
  ATTRIBUTES *attributes;		//Array Point
  int		countOfExtension;
  EXTENTIONS* extensions;	//Array Point
}ATTR_CERTINFO;

typedef struct ATTR_CERTREQ_INFO{
  PKI_DATA  holderCert;
  int		countOfAttribute;
  ATTRIBUTES *attributes;		//Array Point
  int		countOfExtension;
  EXTENTIONS* extensions;	//Array Point
}ATTR_CERTREQ_INFO;





#ifdef __cplusplus
extern "C" {
#endif





int WINAPI pkiLogin(char pinType,char *pin);
int WINAPI pkiLogout();
int WINAPI pkiFormat(unsigned char *soPin);
int WINAPI pkiUnlock(char *oldpin);
int WINAPI pkiSetPin(char userType,char *newPin);
int WINAPI pkiSetHardWare(DWORD HardWareType);

int WINAPI pkiReadLabel(BYTE *label,LABEL_TYPE type, BYTE *buf, int *size);
int WINAPI pkiWriteLabel(BYTE *label,LABEL_TYPE type,LABEL_MODE mode,BYTE *buf, int size );
int WINAPI pkiDeleteLabel(char *label,LABEL_TYPE type );
int WINAPI pkiReadLabelList(LABEL_TYPE type, char *lbl_arr, int *num);


int WINAPI pkiInit();
int WINAPI pkiEnd();
int WINAPI pkiBase64Encode(PKI_DATA i_inData,PKI_PDATA o_outData );
int WINAPI pkiBase64Decode(PKI_DATA i_inData,PKI_PDATA o_outData );



/*摘要算法*/
int WINAPI pkiHashData( UINT  i_hashAlgo,    
					   PKI_DATA i_inData,    
					   PKI_PDATA o_outData);
int WINAPI pkiHashDataEx( UINT  i_hashAlgo,    
						 PKI_DATA i_inData,
						 unsigned long TotalBit[2],
						 DWORD	dwFlag,
						 PKI_PDATA o_outData);

/*对称算法*/
int WINAPI pkiGenerateRandom(int i_length, PKI_PDATA  o_outData );
int WINAPI pkiRWKCryptData(int  i_isEncryption,    
						   UINT i_symmAlgo,    
						   PKI_DATA  i_symmKey,    
						   PKI_DATA i_inData,    
						   PKI_PDATA o_outData );
int WINAPI pkiSymmCryptData(int  i_isEncryption,
							int  i_symmAlgo,
							PKI_DATA i_symmKey,
							PKI_DATA i_inData,
							PKI_PDATA o_outData );
int WINAPI pkiPBKCryptData(int  i_isEncryption,    
						   UINT i_symmAlgo,    
						   BYTE *i_passwd,    
						   PKI_DATA i_inData,    
						   PKI_PDATA o_outData );

/*非对称算法*/
int WINAPI pkiGetKeyPairDer(int i_keySize,int i_keyAlgo,    
				PKI_PDATA o_pubKey,    
				PKI_PDATA o_privKey );
int WINAPI pkiGenRsaKeyInDevice(BYTE *keylabel,BYTE *passwd,
					int i_keySize,    
					PKI_PDATA o_pubKey );
int WINAPI pkiGenRsaExKeyInDevice(BYTE *keylabel,BYTE *i_passwd,
					int i_keySize,    
					PKI_PDATA o_pubKey );
int WINAPI pkiUpdatePrivKey(  int i_isDual, BYTE *i_keyLabel, BYTE *i_passwd, PKI_DATA  i_encPrivKey );
int WINAPI pkiCheckPrivKey(BYTE *i_keyLabel,BYTE *i_passwd );
int WINAPI pkiChangePrivKeyPasswd(BYTE *i_privKeyLabel,BYTE *i_oldPasswd,BYTE *i_newPasswd );
int WINAPI pkiPubKeyEncrypt(PKI_DATA i_pubKey, PKI_DATA i_inData, PKI_PDATA o_outData);
int WINAPI pkiPrivKeyDecrypt(BYTE *i_keyLabel,  BYTE	 *i_passwd,PKI_DATA	i_inData,PKI_PDATA	o_outData);
int WINAPI pkiGetPublicKey(char *KeyLabel,int pubKeyType,PKI_DATA *o_pubKey);



/*证书生产管理*/

int WINAPI pkiCheckCert(PKI_DATA i_inCert,
						PKI_DATA i_trustCert,
						PKI_DATA i_certsChain,
						PKI_DATA i_crl);
int WINAPI pkiGetCertInfo(PKI_DATA i_inData,    
						  PKI_CERTINFO *o_certInfo );

int WINAPI pkiGetXMLCertInfo(PKI_DATA  i_inCert,
							 PKI_PDATA o_certInfo);

int WINAPI pkiGetCRLInfo(PKI_DATA i_inCRL,     
						 PKI_PDATA o_crlInfo );

int WINAPI pkiPubKeyEncryptByCert(PKI_DATA i_Cert, PKI_DATA i_inData,  PKI_PDATA o_outData);



/*签名验证*/
int WINAPI pkiSignData(BYTE *i_keyLabel,    
					   BYTE *i_keyPasswd, 
					   ALG_ID digestAlgo,
					   PKI_DATA i_inData,    
					   PKI_PDATA o_outData );

int WINAPI pkiVerifyData(PKI_DATA i_checkCert, PKI_DATA i_signature );

int	WINAPI pkiGetSignature(BYTE *i_keyLabel, 
						   BYTE *i_keyPasswd,
						   ALG_ID digestAlgo,
						   PKI_DATA i_inData,
						   PKI_DATA *signature);

int WINAPI pkiVerifySignature(ALG_ID digestAlgo,
							  PKI_DATA i_checkCert,    
							  PKI_DATA i_clearText,    
							  PKI_DATA i_signature );

int WINAPI pkiVerifySignatureEx(ALG_ID digestAlgo,
							    PKI_DATA i_pubKey,    
								PKI_DATA i_clearText,    
								PKI_DATA i_signature );




/*数字信封*/
int WINAPI pkiSealEnvelope(PKI_DATA i_encCert,
						   UINT i_symmAlgo,
						   PKI_DATA i_inData,
						   PKI_PDATA o_outData );

int WINAPI pkiOpenEnvelope(BYTE *i_decKeyLabel,
						   BYTE *i_passwd,    
						   PKI_DATA i_inData,    
						   PKI_PDATA o_outData );

int WINAPI pkiSealEnvelopeEx(PKI_PDATA	i_encCerts,
							 int  i_encCertscount,
							 UINT  i_symmAlgo,
							 PKI_DATA  i_inData,
							 PKI_PDATA  o_outData);





int WINAPI pkiGenCertRequest(CERTREQ_INFO  i_certReqInfo,    
							 BYTE *i_passwd,    
							 UINT i_symmAlgo,    
							 BYTE *i_keyLabel,    
							 PKI_PDATA o_certReq);

int WINAPI pkiSignRootCert(PKI_DATA  i_certReq,    
						   BYTE     *i_caKeyLabel,    
						   BYTE     *i_passwd,    
						   CERT_POLICY i_certPolicy,    
						   PKI_PDATA  o_cert );

int WINAPI pkiSignDualCert(PKI_DATA i_certReq,    
						   PKI_DATA i_encPubKey,    
						   BYTE *i_caKeyLabel,    
						   BYTE *i_passwd,    
						   CERT_POLICY i_certPolicy,
						   PKI_PDATA o_encCert,
						   PKI_PDATA o_signCert );

int WINAPI pkiSignSingleCert(CERTREQ_INFO i_certReqInfo,    
							 PKI_DATA i_signPubKey,    
							 BYTE *i_caKeyLabel,    
							 BYTE *i_passwd,    
							 CERT_POLICY i_certPolicy,    
							 PKI_PDATA o_cert );

int WINAPI pkiSignSingleCertEx(PKI_DATA i_certReq,    
// 							 PKI_DATA i_signPubKey,    
							 BYTE *i_caKeyLabel,    
							 BYTE *i_passwd,    
							 CERT_POLICY i_certPolicy,    
							 PKI_PDATA o_cert );

int WINAPI pmiSignPACert (PA_CERTREQ_INFO i_paCertReqInfo,    
						  BYTE *i_keyLabel,    
						  BYTE *i_passwd,	    
						  int  i_acValidMonth,	    
						  PKI_DATA *o_paCert );

int WINAPI	pmiGetPACertInfo (PKI_DATA i_paCert,    
							  PA_CERTINFO *o_paCertInfo );




int WINAPI pkiSignCRL(CRL_LIST *i_crlList,    
					  BYTE *i_caLabel,    
					  BYTE *i_passwd,    
					  int i_crlValidDays,    
					  PKI_PDATA o_outData );

int WINAPI pkiSecureSplitData(BYTE *i_inData,    
							  int  i_inDataLen,    
							  BYTE *i_passwd1,    
							  BYTE *i_passwd2,    
							  BYTE *i_passwd3,    
							  BYTE *o_outData1,    
							  BYTE *o_outData2,    
							  BYTE *o_outData3,    
							  int  *o_outDataLen );

int WINAPI pkiSecureUniteData(BYTE *i_inData1,    
							  BYTE *i_inData2,    
							  BYTE *i_inData3,    
							  int  i_inDataLen,    
							  BYTE *i_passwd1,    
							  BYTE *i_passwd2,    
							  BYTE *i_passwd3,    
							  BYTE *o_outData,
							  int  *o_outDataLen );
int WINAPI pkiGetPrivateKey(BYTE *i_keyLable,
							BYTE *i_passwd,
							PKI_DATA *o_outData);


int WINAPI pkiImportCert(BYTE *label, 
						 int dwStoreType,
						 int CertType,
						 BYTE *buf, int size );

int WINAPI pkiExportCert(BYTE *label, 
						 int dwStoreType,
						 int CertType,
						 BYTE *buf, int *size );








///////////////////////////////////////////////
//AA证书相关接口
int WINAPI pmiSignAttrCert (
    ATTR_CERTREQ_INFO i_attrCertReqInfo,
    BYTE *i_keyLabel,
    BYTE *i_passwd,	
    int  i_acValidDays,	
    PKI_DATA *o_attrCert );

int WINAPI pmiGetAttrCertInfo(
    PKI_DATA i_acCert,
    ATTR_CERTINFO *o_attrCertInfo );

int WINAPI pmiGetAttrCertInfoEnd(
	ATTR_CERTINFO *i_attrCertInfo );

#ifdef __cplusplus
}  //extern "C" {
#endif

#endif
