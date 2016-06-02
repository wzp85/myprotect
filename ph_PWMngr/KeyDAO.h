
// EMDevMngr.h: interface for the CKeyDao class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYDAO_H__55753998_F8A6_4ACA_950E_B760690A81BF__INCLUDED_)
#define AFX_KEYDAO_H__55753998_F8A6_4ACA_950E_B760690A81BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "eccapi.h"
#include "DAI.h"
#include "DAIDef.h"

typedef enum enumAlogId 
{
	ALGO_ID_RSA		        = SGD_RSA,
	ALGO_ID_SM2_SIGN		= SGD_SM2_1,
	ALGO_ID_SM2_EXCHANGE	= SGD_SM2_2,
	ALGO_ID_SM2_ENC			= SGD_SM2_3,
	ALGO_ID_HASH_SM3		= SGD_SM3,
	ALGO_ID_HASH_SHA1		= SGD_SHA1,
	ALGO_ID_HASH_SHA256		= SGD_SHA256,
	ALGO_ID_HASH_SHA224		= SGD_SHA224,
	ALGO_ID_HASH_SHA384		= SGD_SHA384,
	ALGO_ID_HASH_SHA512		= SGD_SHA512,
	ALGO_ID_HASH_MD2		= SGD_MD2,
	ALGO_ID_HASH_MD5		= SGD_MD5,

	ALGO_ID_SYMM_3DES_ECB	= SGD_3DES_ECB,
	ALGO_ID_SYMM_3DES_CBC	= SGD_3DES_CBC,
	ALGO_ID_SYMM_3DES_CFB	= SGD_3DES_CFB,
	ALGO_ID_SYMM_3DES_OFB	= SGD_3DES_OFB,
	ALGO_ID_SYMM_3DES_MAC	= SGD_3DES_MAC,

	ALGO_ID_SYMM_SM1_ECB	= SGD_SM1_ECB,
	ALGO_ID_SYMM_SM1_CBC	= SGD_SM1_CBC,
	ALGO_ID_SYMM_SM1_CFB	= SGD_SM1_CFB,
	ALGO_ID_SYMM_SM1_OFB	= SGD_SM1_OFB,
	ALGO_ID_SYMM_SM1_MAC	= SGD_SM1_MAC,
	ALGO_ID_SYMM_SSF33_ECB	= SGD_SSF33_ECB,
	ALGO_ID_SYMM_SSF33_CBC	= SGD_SSF33_CBC,
	ALGO_ID_SYMM_SSF33_CFB	= SGD_SSF33_CFB,
	ALGO_ID_SYMM_SSF33_OFB	= SGD_SSF33_OFB,
	ALGO_ID_SYMM_SSF33_MAC	= SGD_SSF33_MAC,

	ALGO_ID_SYMM_SM4_ECB	= SGD_SM4_ECB,
	ALGO_ID_SYMM_SM4_CBC	= SGD_SM4_CBC,
	ALGO_ID_SYMM_SM4_CFB	= SGD_SM4_CFB,
	ALGO_ID_SYMM_SM4_OFB	= SGD_SM4_OFB,
	ALGO_ID_SYMM_SM4_MAC	= SGD_SM4_MAC,

	ALGO_ID_SYMM_AES_ECB	= SGD_AES_ECB,
	ALGO_ID_SYMM_AES_CBC	= SGD_AES_CBC,

	ALGO_ID_SYMM_RC2_ECB	= SGD_RC2_ECB,

	ALGO_ID_SYMM_RC2_CBC	= SGD_RC2_CBC,

	ALGO_ID_SYMM_RC4_ECB	= SGD_RC4_ECB,
} AlgoId;

class CKeyDao 
{
public:

	BOOL WhichKey(char *dllname, char *pkiapidllname);



	BOOL ExtRSAPubKeyOperation(DEVHANDLE hDev,
								RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
								BYTE *pbInput,
								ULONG ulInputLen,
								BYTE *pbOutput,
								ULONG *pulOutputLen);
	BOOL RSAVerify(DEVHANDLE     hDev,
					RSAPUBLICKEYBLOB *pRSAPubKeyBlob,						   						  
					BYTE          *pbData,
					ULONG         ulDataLen,
					BYTE          *pbSignature,
					ULONG         ulSigLen);

	BOOL GetFileInfo(HAPPLICATION hApplication,LPSTR szFile,FILEATTRIBUTE *pFileInfo);
	BOOL EnumFiles(HAPPLICATION hApplication,LPSTR szFileList,ULONG *pulSize);
	BOOL ReadFile(HAPPLICATION hApplication,LPSTR szFile,ULONG ulOffset,ULONG ulSize,BYTE *pbOutData,ULONG *pulOutLen);
	BOOL OpenApplication(DEVHANDLE hDev,LPSTR szAppName,HAPPLICATION *phApplication);
	BOOL EnumApplication(DEVHANDLE hDev,LPSTR szAppName,ULONG *pulSize);
	BOOL OpenContainer(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
	BOOL EnumContainer(HAPPLICATION hApplication,LPSTR szContainerName,ULONG *pulSize);
	BOOL GetContainerType(HCONTAINER hcontainer,ULONG *pulContainerType);
	BOOL CloseContainer(HCONTAINER hcontainer);
	BOOL Digest(HANDLE hHash,
				BYTE *pbData,
				ULONG ulDataLen,
				BYTE *pbHashData,
				ULONG *pulHashLen);
	BOOL DigestInit(DEVHANDLE phDev,ULONG hashAlgo,ECCPUBLICKEYBLOB * pEccpublickeyblob,BYTE * pucID,ULONG ulIdlen,HANDLE * phHash);
	BOOL RSASignData(HCONTAINER hcontainer,BYTE * pbDataforsign,ULONG uDatalenforsign,BYTE *pbSignature,ULONG *pulSignLen);
	BOOL ECCSignData(HCONTAINER hcontainer,BYTE *pbHashdata,ULONG pbHashlen,PECCSIGNATUREBLOB eccsignatureblob);
	BOOL GenRandom(DEVHANDLE phDev,BYTE *pbRandom,ULONG len);
	BOOL ExportPublicKey(HCONTAINER hContainer,BOOL bSignFlag,BYTE* pbBlob,ULONG *pulBlobLen);
	BOOL WriteFile(HAPPLICATION hApplication,
                    LPSTR szFile,
					ULONG ulOffset,
					BYTE *pbData,
					ULONG ulSize);
	BOOL CreateFile(HAPPLICATION hApplication,
                    LPSTR szFileName,
					ULONG ulFileSize,						 
                    ULONG ulReadRights,
					ULONG ulWriteRights);
	BOOL GenRSAKeyPair(HCONTAINER hcontainer,ULONG uBitLong,RSAPUBLICKEYBLOB *rsapublickeyblobForSign);
	DWORD GenECCKeyPair(HCONTAINER hcontainer,ULONG AlgID,ECCPUBLICKEYBLOB *eccpublickeyblob);
	BOOL VerifyPIN(HAPPLICATION happlication,ULONG type,LPSTR szUserPin,ULONG *pulRetryCount);
	BOOL Logout(HAPPLICATION happlication);
	BOOL UnblockPIN(HAPPLICATION hApplication,LPSTR szAdminPIN,LPSTR szNewUserPIN,ULONG *pulRetryCount);
	BOOL ChangePIN(HAPPLICATION hApplication,ULONG ulPINType,LPSTR szOldPin,LPSTR szNewPin,ULONG *pulRetryCount);
	BOOL CreateContainer(HAPPLICATION happlication,LPSTR szContainer,HCONTAINER *hcontainer);
	BOOL CreateApplication(DEVHANDLE hDev,
							LPSTR szAppName,
							LPSTR szAdminPin,
							DWORD dwAdminPinRetryCount,
							LPSTR szUserPin,
							DWORD dwUserPinRetryCount,
							DWORD dwCreateFileRights,
							HAPPLICATION *phApplication);
	BOOL DevAuth(DEVHANDLE D_handle);
	BOOL OpenDevice(DEVHANDLE *O_handle);
	BOOL CloseDevice(DEVHANDLE C_handle);
	
	CKeyDao();
	virtual ~CKeyDao();
	static CKeyDao* GetInstance();

private:
	static CKeyDao hInst;

private:
	BOOL InitCheckAndOpenSession(void **hSession);
	
	void * m_hDevice;
//	void * m_hSession;
};

#endif // !defined(AFX_EMDEVMNGR_H__55753998_F8A6_4ACA_950E_B760690A81BF__INCLUDED_)
