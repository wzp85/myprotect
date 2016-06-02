// MyUtil.h: interface for the CMyUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUTIL_H__ECC1FA49_5955_4991_9D17_164B84F94EB1__INCLUDED_)
#define AFX_MYUTIL_H__ECC1FA49_5955_4991_9D17_164B84F94EB1__INCLUDED_

//#include "eccapi.h"
#include "DAI.h"
#include "DAIDef.h"


#define OPENDEVERROR    1
#define OPENAPPERROR    2
#define KEYWRONG        3
#define INITFAIL        4
#define CREATECONFAIL   5
#define GENPUBKEYFAIL   6
#define CLOSEDEVERROR   7
#define DEVAUTHERROR    8
#define PINERROR        9

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyUtil  
{
public:
	
	CMyUtil();
	virtual ~CMyUtil();

	static void ByteArray2String(CString& szData, const BYTE* lpData, UINT nLen, BOOL isHEX);
	static void ByteArray2NoWrapString(CString& szData, const BYTE* lpData, UINT nLen, BOOL isHEX);
	static void ECCKey2String(CString& szData, ECCPUBLICKEYBLOB& pubKey);
//	static void ECCKey2String(CString& szData, ECCrefPrivateKey& prvKey);
	static void RSAKey2String(CString& szData, RSAPUBLICKEYBLOB& pubKey);
	static void RSAKey2String(CString& szData, RSAPRIVATEKEYBLOB& prvKey);
	static void ReadData(char * filename, unsigned char *pData, int * length);
	static void Write2File(char * filename, unsigned char* pbData,int nDataLen);
	static void Write2FileAppend(char * filename, unsigned char* pbData,int nDataLen);
	static BOOL isNum( char  *pStr);
	static int ReadLabel(char *label_for_read,char *label);
	static int GetPubKey(char *usrPIN,HAPPLICATION *appHandle,RSAPUBLICKEYBLOB *pPubKey,ECCPUBLICKEYBLOB *epPubKey,int len);
	static int WriteLabel(LPSTR label,BYTE *lab_text,ULONG lab_text_len);
	static int GetAdminID(void *handle,int *id,int *admNum);
	static int KeyInit(char *usrPIN);
	static int WriteLabelEx(LPSTR label,BYTE *lab_text,ULONG lab_text_len,char *usrPIN);
//	static void ReadText(char * filename, unsigned char *pData, int * length);
	static int GetRtCertIndexSet(void *handle,unsigned int *num,unsigned int *indexSet,unsigned int *algTemp);
	static int GetCACertIndexSet(void *handle,unsigned int *num,unsigned int *indexSet,unsigned int *algTemp);
	static int IsCertFile(unsigned char *data,int data_len,unsigned char *in_data,unsigned int *in_data_len);
	static char * Pub_MemSearch(char * mem,int memLen,char * subMem,int subMemLen);
	static int GetParamFromString(unsigned char *pString, unsigned char *ParamName, unsigned char *ParamValue, unsigned int *pParamValueLen);
	static int Cert2Dercert(unsigned char *pucIn_cert, unsigned int uiIn_cert_len, unsigned char *pucOut_cert, unsigned int *puiOut_cert_len);
	static void RevStr(char *str);
};

#endif // !defined(AFX_MYUTIL_H__ECC1FA49_5955_4991_9D17_164B84F94EB1__INCLUDED_)
