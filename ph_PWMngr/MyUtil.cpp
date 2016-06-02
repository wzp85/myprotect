// MyUtil.cpp: implementation of the CMyUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyUtil.h"
#include "ph_km.h"
#include "KeyDAO.h"
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyUtil::CMyUtil()
{

}

CMyUtil::~CMyUtil()
{

}


void CMyUtil::ByteArray2String(CString& szData, const BYTE* lpData, UINT nLen, BOOL isHEX)
{
	CString szTmp;
	for (UINT n = 0; n < nLen; n++) {
		szTmp.Format(isHEX ? _T("%02X ") : _T("%-04d "), lpData[n]);
		szData += szTmp;
		if ((n+1) % 16 == 0) {
			szData += "\r\n";
		}
		else if ((n+1) % 8 == 0) {
			szData += "- ";
		}
	}
}

void CMyUtil::ByteArray2NoWrapString(CString& szData, const BYTE* lpData, UINT nLen, BOOL isHEX)
{
	CString szTmp;
	for (UINT n = 0; n < nLen; n++) {
		szTmp.Format(isHEX ? _T("%02X") : _T("%-04d"), lpData[n]);
		szData += szTmp;
	}
}

void CMyUtil::ECCKey2String(CString& szData, ECCPUBLICKEYBLOB& pubKey)
{
	const BYTE* lpPubKey = (const BYTE*) &pubKey;
	UINT nLen = sizeof(pubKey);
	CMyUtil::ByteArray2String(szData, lpPubKey, nLen, TRUE);
}

//void CMyUtil::ECCKey2String(CString& szData, ECCrefPrivateKey& prvKey)
//{
//	const BYTE* lpPrvKey = (const BYTE*) &prvKey;
//	UINT nLen = sizeof(prvKey);
//	CMyUtil::ByteArray2String(szData, lpPrvKey, nLen, TRUE);
//}

void CMyUtil::RSAKey2String(CString& szData, RSAPUBLICKEYBLOB& pubKey)
{
	const BYTE* lpPubKey = (const BYTE*) &pubKey;
	UINT nLen = sizeof(pubKey);
	CMyUtil::ByteArray2String(szData, lpPubKey, nLen, TRUE);
}

void CMyUtil::RSAKey2String(CString& szData, RSAPRIVATEKEYBLOB& prvKey)
{
	const BYTE* lpPrvKey = (const BYTE*) &prvKey;
	UINT nLen = sizeof(prvKey);
	CMyUtil::ByteArray2String(szData, lpPrvKey, nLen, TRUE);
}

void CMyUtil::ReadData(char * filename, unsigned char *pData, int * length)
{
	FILE *stream;
	int count, total=0;
	char buffer[100];
	
	if(pData)
	{
		/*if( ( stream = fopen( filename, "rb" ) ) == NULL )
			return -1;*/
	//	MessageBox(NULL,"stream","",MB_OK);
		stream = fopen( filename, "rb" ) ;
	//	MessageBox(NULL,"stream---------2","",MB_OK);
		count = fread( pData, 1, *length, stream );
	//	MessageBox(NULL,"stream----------3","",MB_OK);
		*length = count;
		fclose( stream );
	}
	else
	{
		/*if( ( stream = fopen( filename, "rb" ) ) == NULL )
			return( -1 );*/
		//MessageBox(NULL,"stream----------4","",MB_OK);


//		MessageBox(NULL,"filename======="+(CString)filename,"",MB_OK);
		stream = fopen( filename, "rb" ) ;

		//int reterr=GetLastError();
		//char reterrdata[32]={0x00};
		//sprintf(reterrdata,"fopenFile err== %d",reterr);
		//MessageBox(NULL,"Error"+(CString)reterrdata,"",MB_OK);

		if(NULL ==  stream)
		{
//			MessageBox(NULL,"stream====NULL","",MB_OK);
			return;
		}
//		MessageBox(NULL,"stream----------5","",MB_OK);
		while( !feof( stream ) )
		{
			/* Attempt to read in 10 bytes: */
		//	MessageBox(NULL,"stream----------6","",MB_OK);
			count = fread( buffer, sizeof( char ), 100, stream );
		//	MessageBox(NULL,"stream----------7","",MB_OK);
			if( ferror( stream ) )      
			{
				perror( "Read error" );
				break;
			}	
			/* Total up actual bytes read */
			total += count;
		}
		*length = total;
		fclose( stream );
	}
	return ;
}

//void CMyUtil::ReadText(char * filename, unsigned char *pData, int * length)
//{
//	FILE *stream=NULL;
//	int count, total=0;
//	char buffer[100]={0x00};
//	
//	if(pData)
//	{
//		/*if( ( stream = fopen( filename, "r" ) ) == NULL )
//			return -1;*/
//		MessageBox(NULL,"stream","",MB_OK);
//		stream = fopen( filename, "r" ) ;
//		MessageBox(NULL,"stream---------2","",MB_OK);
//		count = fread( pData, 1, *length, stream );
//		MessageBox(NULL,"stream----------3","",MB_OK);
//		*length = count;
//		fclose( stream );
//	}
//	else
//	{
//		/*if( ( stream = fopen( filename, "r" ) ) == NULL )
//			return( -1 );*/
//		MessageBox(NULL,"stream----------4","",MB_OK);
//
//
//		MessageBox(NULL,"filename======="+(CString)filename,"",MB_OK);
//		stream = fopen( filename, "r" ) ;
//		if(NULL ==  stream)
//		{
//			MessageBox(NULL,"stream====NULL","",MB_OK);
//			return;
//		}
//		MessageBox(NULL,"stream----------5","",MB_OK);
//		while( !feof( stream ) )
//		{
//			/* Attempt to read in 10 bytes: */
//			MessageBox(NULL,"stream----------6","",MB_OK);
//			count = fread( buffer, sizeof( char ), 100, stream );
//			MessageBox(NULL,"stream----------7","",MB_OK);
//			if( ferror( stream ) )      
//			{
//				perror( "Read error" );
//				break;
//			}	
//			/* Total up actual bytes read */
//			total += count;
//		}
//		*length = total;
//		fclose( stream );
//	}
//	/*return 0;*/
//}

void CMyUtil::Write2File(char * filename, unsigned char* pbData,int nDataLen)
{	
	FILE *stream;
	/*if( ( stream = fopen( filename, "wb" ) ) == NULL )
		return -1;*/
	stream = fopen( filename, "wb" );
	::fwrite(pbData, 1, nDataLen, stream);
	fclose( stream );
	/*return 0;*/
}

void CMyUtil::Write2FileAppend(char * filename, unsigned char* pbData,int nDataLen)
{
	FILE *stream;
	/*if( ( stream = fopen( filename, "wb" ) ) == NULL )
		return -1;*/
	stream = fopen( filename, "a+" );
	::fwrite(pbData, 1, nDataLen, stream);
	fclose( stream );
	/*return 0;*/
}

BOOL CMyUtil::isNum(char *pStr)
{
	char *p = pStr;

	for(unsigned int i = 0 ; i < strlen(pStr); i++)
	{
		if (!((*(p + i) >= '0')&&(*(p + i) <= '9')))
		{
			  return FALSE;
		}

		if (i >= strlen(pStr))
		{
			 return TRUE;
		}
    
	}
	 return TRUE;
}

int CMyUtil::ReadLabel(char *label_for_read,char *label)
{
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		return OPENDEVERROR;
	}

	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		return OPENAPPERROR;
	}

	//读标签
	BYTE *LAB_text=NULL;
	ULONG LAB_text_Length = 0;
	FILEATTRIBUTE fileattribute={0x00};
	if(!keyDao.GetFileInfo(phApplication,label_for_read,&fileattribute))
	{
		return KEYWRONG;
	}
	LAB_text_Length = fileattribute.FileSize;
	LAB_text = new BYTE[LAB_text_Length+1];
	memset(LAB_text,0x00,LAB_text_Length+1);
	if(!keyDao.ReadFile(phApplication,label_for_read,0,fileattribute.FileSize,LAB_text,&LAB_text_Length))
	{
		return KEYWRONG;
	}
	char *src = (char *)LAB_text;
	memset(label,0,LAB_text_Length);
	memcpy(label,src,LAB_text_Length);

	delete LAB_text;
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		return CLOSEDEVERROR;
	}
	return 0;
}

int CMyUtil::GetPubKey(char *usrPIN,HAPPLICATION *appHandle,RSAPUBLICKEYBLOB *pPubKey,ECCPUBLICKEYBLOB *epPubKey,int len)
{
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		return OPENDEVERROR;
	}
	if(!keyDao.DevAuth(smart_DeviceHandle))
	{
		return DEVAUTHERROR;
	}
	LPSTR szAppName = "wellhope";
	LPSTR szAdminPin = "123456";
	DWORD dwAdminPinRetryCount = 6;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,usrPIN);
	DWORD dwUserPinRetryCount = 10;
	DWORD dwCreateFileRights = SECURE_EVERYONE_ACCOUNT;
	HAPPLICATION application;	

	char appName[32]={0x00};
	LPSTR appNameLS = appName;
	ULONG handSize = 0;
	ULONG *thepulSize = &handSize;

	if(!keyDao.CreateApplication(smart_DeviceHandle,szAppName,szAdminPin,dwAdminPinRetryCount,szUserPin,dwUserPinRetryCount,dwCreateFileRights,&application))
	{
		return INITFAIL;
	}
	appHandle = (HAPPLICATION *)&application;


	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	if(!keyDao.VerifyPIN(application,type,szUserPin,&pulRetryCount))
	{
		return PINERROR;
	}
	LPSTR szContainer = "LAB_USERCERT";
	HCONTAINER phContainer;
	if(!keyDao.CreateContainer(application,szContainer,&phContainer))
	{
		return CREATECONFAIL;
	}

	/*ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	if(!keyDao.VerifyPIN(application,type,szUserPin,&pulRetryCount))
	{
		return PINERROR;
	}*/

//	ULONG ulBitLen = 1024;
	if((1024 == len || 2048 == len) && (epPubKey == NULL))
	{
		RSAPUBLICKEYBLOB pBlob={0};
		if(!keyDao.GenRSAKeyPair(phContainer,len,&pBlob))
		{
			return GENPUBKEYFAIL;
		}
		memcpy(pPubKey,(const BYTE *)&pBlob,sizeof(RSAPUBLICKEYBLOB));
	}
	else if(256 == len && (pPubKey == NULL))
	{
		int ret = 0;
		ECCPUBLICKEYBLOB epBlob={0};
		ret = keyDao.GenECCKeyPair(phContainer,SGD_SM2_1,&epBlob);
		if(0 != ret && SAR_NOTSUPPORTKEYTYPE != ret)
		{
			return GENPUBKEYFAIL;
		}
		else if(SAR_NOTSUPPORTKEYTYPE == ret)
		{
			return SAR_NOTSUPPORTKEYTYPE;
		}
		memcpy(epPubKey,(const BYTE *)&epBlob,sizeof(ECCPUBLICKEYBLOB));
	}
	if(!keyDao.Logout(application))
	{
		return PINERROR;
	}
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		return CLOSEDEVERROR;
	}
	return 0;
}

int CMyUtil::WriteLabel(LPSTR label,BYTE *lab_text,ULONG lab_text_len)
{			
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		return OPENDEVERROR;
	}
	char name[32]={0x00};
	LPSTR szAppName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	if(!keyDao.EnumApplication(smart_DeviceHandle,szAppName,pulSize))
	{
		return 3;
	}
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szAppName,&phApplication))
	{
		return OPENAPPERROR;
	}
    ULONG ulReadRights = SECURE_EVERYONE_ACCOUNT;
	ULONG ulWriteRights = SECURE_EVERYONE_ACCOUNT;
	if(!keyDao.CreateFile(phApplication,label,lab_text_len,ulReadRights,ulWriteRights))
	{
		return 4;
	}
	ULONG ulOffset = 0;
	if(!keyDao.WriteFile(phApplication,label,0,lab_text,lab_text_len))
	{
		return 5;
	}
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		return 6;
	}
	return 0;
}

int CMyUtil::WriteLabelEx(LPSTR label,BYTE *lab_text,ULONG lab_text_len,char *usrPIN)
{
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		return OPENDEVERROR;
	}
	char name[32]={0x00};
	LPSTR szAppName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	if(!keyDao.EnumApplication(smart_DeviceHandle,szAppName,pulSize))
	{
		return 3;
	}
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szAppName,&phApplication))
	{
		return OPENAPPERROR;
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	if(!keyDao.VerifyPIN(phApplication,type,usrPIN,&pulRetryCount))
	{
		return PINERROR;
	}
    ULONG ulReadRights = SECURE_EVERYONE_ACCOUNT;
	ULONG ulWriteRights = SECURE_EVERYONE_ACCOUNT;
	if(!keyDao.CreateFile(phApplication,label,lab_text_len,ulReadRights,ulWriteRights))
	{
		return 4;
	}
	ULONG ulOffset = 0;
	if(!keyDao.WriteFile(phApplication,label,0,lab_text,lab_text_len))
	{
		return 5;
	}
	if(!keyDao.Logout(phApplication))
	{
		return PINERROR;
	}
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		return 6;
	}
	return 0;
}

int CMyUtil::GetAdminID(void *handle,int *id,int *admNum)
{
	int ret = 0;
	int admin_id = 0;
	int admin_num = 0;
	char adminIndexBuf[32]={0x00};
	void *phSessionHandle;
	if(NULL == handle)
		return -1;
	else
		phSessionHandle = handle;
	unsigned char *puiAdminList=NULL;
	unsigned int puiAdminListLen=0;
	ret = Km_GetAdminList(phSessionHandle,NULL,&puiAdminListLen);
	if(0 != ret)
	{
		return ret;
	}
	puiAdminList = new unsigned char[puiAdminListLen+1];
	memset(puiAdminList,0x00,puiAdminListLen+1);
	ret = Km_GetAdminList(phSessionHandle,puiAdminList,&puiAdminListLen);
	if(0 != ret)
	{
		delete puiAdminList;
		return ret;
	}
	if(0 == ret && 0 == puiAdminListLen)
	{
		*id = 0;
		return 0;
	}
	char *keyList = (char *)puiAdminList;
	char *str = strstr(keyList,"uiAdminType");
	char *source = str + strlen("uiAdminType");
	for(int i = 0;i < 16;i++)
	{
		if(source == NULL)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;
		//数据库id字段项
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		//管理员序列号
		char adminIndexBuf[32]={0x00};		
		char *str_appName = strstr(str2,"|");
		/*if(str_appName == NULL)
			break;*/
		memcpy(adminIndexBuf,str2,str_appName-str2);
		admin_id = atoi(adminIndexBuf);//=================================获取密码机管理员列表中最后一个管理员的序列号
		admin_num++;
		char *str3 = str2 + strlen(adminIndexBuf) + 1;

		//管理员名称
		char adminNameBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(adminNameBuf,str3,str_keyIndex-str3);
		char *str4 = str3 + strlen(adminNameBuf) + 1;
		
		//管理员电话号码
		char adminTelBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(adminTelBuf,str4,str_algId-str4);
		char *str5 = str4 + strlen(adminTelBuf) + 1;

		//证件类型
		char adminPaperType[1]={0x00};
		memcpy(adminPaperType,str5,1);
		char *str6 = str5 + 2;

		//证件号码
		char adminPaperNum[32]={0x00};
		char *str_apn=strstr(str6,"|");
		memcpy(adminPaperNum,str6,str_apn-str6);
		char *str7 = str6 + strlen(adminPaperNum) + 1;

		//编码后的公钥
		char pubKeyBuf[1024]={0x00};
		char *str_pubKey = strstr(str7,"|");
		memcpy(pubKeyBuf,str7,str_pubKey-str7);
		char *str8 = str7 + strlen(pubKeyBuf) + 1;

		//DEVKEYINFO devInfo={0x00};
		//ret = Km_GetDevKeyInfo(hSessionHandle,&devInfo);
		//CString maxNum;
		//maxNum.Format("%d",devInfo.uiBakTotalKey);
		//m_listCtrlAdminMngr.SetItemText(nCount,6,maxNum);//---------显示最大管理员数量

		//管理员类型
		char adminType[1]={0x00};
		char *str_adminType=strstr(str8,"|");
		memcpy(adminType,str8,1);
		CString admin_type;
		if(0 == atoi(adminType))
			admin_type = "系统管理员";
		if(1 == atoi(adminType))
			admin_type = "密钥管理员";

		char *str9 = str8 + 2;

		source = str9;
	}
	delete puiAdminList;
	*id = admin_id;
	*admNum = admin_num;
	return 0;
}

int CMyUtil::KeyInit(char *usrPIN)
{
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		return OPENDEVERROR;
	}
	if(!keyDao.DevAuth(smart_DeviceHandle))
	{
		return DEVAUTHERROR;
	}
	LPSTR szAppName = "wellhope";
	LPSTR szAdminPin = "123456";
	DWORD dwAdminPinRetryCount = 6;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,usrPIN);
	DWORD dwUserPinRetryCount = 10;
	DWORD dwCreateFileRights = SECURE_USER_ACCOUNT;
	HAPPLICATION application;	

	char appName[32]={0x00};
	LPSTR appNameLS = appName;
	ULONG handSize = 0;
	ULONG *thepulSize = &handSize;

	if(!keyDao.CreateApplication(smart_DeviceHandle,szAppName,szAdminPin,dwAdminPinRetryCount,szUserPin,dwUserPinRetryCount,dwCreateFileRights,&application))
	{
		return INITFAIL;
	}
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		return CLOSEDEVERROR;
	}
	return 0;
}

int CMyUtil::GetRtCertIndexSet(void *handle,unsigned int *num,unsigned int *indexSet,unsigned int *algTemp)
{
	int ret = 0;
	void *phSessionHandle;
	unsigned int index[256]={0};
	unsigned int algBuf[256] = {0};

	if(NULL == handle)
		return -1;
	else 
		phSessionHandle = handle;

	unsigned char * puiKeyList=NULL;
	unsigned int puiKeyListLen=0;

	ret = Sig_RootCertGetList(phSessionHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		return ret;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_RootCertGetList(phSessionHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		delete puiKeyList;
		return ret;
	}
	if(0 == puiKeyListLen)
	{
		*num=0;
		return 0;
	}
	//此处添加显示代码,把读出来的字符串解析后显示在listctrl中
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	int time = 0;

	for(int i=0;i<256;i++)
	{
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------证书名称
		char *str_appName = strstr(str2,"|");
		memcpy(appNameBuf,str2,str_appName-str2);  
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		char *str4 = str3 + strlen(algIdBuf)+1;

		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
		//这个地方应该如何得到证书索引号呢？它存在于服务端的xml文件中！
		char *str5 = str4 + strlen(keyIndexBuf)+1;

		char keyLength[32]={0x00};
		char *str_keyLength=strstr(str5,"|");
		memcpy(keyLength,str5,str_keyLength-str5);
		algBuf[i]=atoi(keyLength);
		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
		time++;
		index[i]=atoi(serialNum);
//		MessageBox(NULL,serialNum,"根证书索引",MB_OK);
		char *str10 = str9 + strlen(serialNum);

		char timeBuf[32]={0x00};
		memcpy(timeBuf,str10,20);
		char *str11 = str10 + strlen(timeBuf);

		source = str11;
	}
	delete puiKeyList;

	//CString itime;
	//itime.Format("%d",num);
	//MessageBox(NULL,itime,"根证书索引总数",MB_OK);
	*num = time;
//	indexSet = index;
	memcpy(indexSet,index,time*sizeof(int));
	memcpy(algTemp,algBuf,time*sizeof(int));
	return 0;
}

int CMyUtil::GetCACertIndexSet(void *handle,unsigned int *num,unsigned int *indexSet,unsigned int *algTemp)
{
	int ret = 0;

	void *phSessionHandle;
	unsigned int index[256]={0};
	unsigned int algBuf[256] = {0};

	if(NULL == handle)
		return -1;
	else 
		phSessionHandle = handle;

	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Sig_CACertGetList(phSessionHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		return ret;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_CACertGetList(phSessionHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		delete puiKeyList;
		return ret;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGCACertGetList.txt",puiKeyList,puiKeyListLen);
	//return;

	if(0 == puiKeyListLen)
	{
		*num=0;
		return 0;
	}
	//此处添加显示代码,把读出来的字符串解析后显示在listctrl中
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	int time = 0;
	for(int i=0;i<256;i++)
	{
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;

		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------证书名称
		char *str_appName = strstr(str2,"|");
		memcpy(appNameBuf,str2,str_appName-str2); 
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		char *str4 = str3 + strlen(algIdBuf)+1;

		//证书序列号
		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
		char *str5 = str4 + strlen(keyIndexBuf)+1;

		char keyLength[32]={0x00};
		char *str_keyLength=strstr(str5,"|");
		memcpy(keyLength,str5,str_keyLength-str5);
		algBuf[i]=atoi(keyLength);
		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
		time++;
		index[i]=atoi(serialNum);
		char *str10 = str9 + strlen(serialNum);

		char timeBuf[32]={0x00};
		memcpy(timeBuf,str10,20);
		char *str11 = str10 + strlen(timeBuf);

		source = str11;
	}
	delete puiKeyList;

	*num = time;

	memcpy(indexSet,index,time*sizeof(int));
	memcpy(algTemp,algBuf,time*sizeof(int));

	return 0;
}


int CMyUtil::IsCertFile(unsigned char *data,int data_len,unsigned char *in_data,unsigned int *in_data_len)
{


	char to_cmp[2]={0x30,0x82};

	if(strncmp(to_cmp,(char*)data,2) && !strncmp("M",(char*)data,1))
	{
		//B64解码，可能是B64格式的证书文件
		char dst[4096]={0x00};
		int length = 0;
		length = Km_Decode((char*)data,data_len,dst);
		memcpy(in_data,dst,length);
		*in_data_len = length;
	}
	else if(!strncmp(to_cmp,(char*)data,2) && strncmp("M",(char*)data,1))
	{
		//直接传，可能是DER格式的证书文件
		memcpy(in_data,data,data_len);
		*in_data_len = data_len;
	}
	else if(strstr((char*)data,"BEGIN CERTIFICATE"))
	{
		//可能，是pem格式的证书文件
		PKI_DATA in_cert,out_cert;
		in_cert.size = data_len;
		out_cert.size=0;
		out_cert.value = new unsigned char[2048];
		in_cert.value = new unsigned char[data_len+1];
		memset(in_cert.value,0x00,data_len+1);
		memcpy(in_cert.value,data,data_len);
		pkiBase64Decode(in_cert,&out_cert);
		memcpy(in_data,out_cert.value,out_cert.size);
		*in_data_len = out_cert.size;
	}
	else
	{
		return -1;
	}
	return 0;
}


char *  CMyUtil::Pub_MemSearch(char * mem,int memLen,char * subMem,int subMemLen)
{
	int j=0;

	for(int i=0;i<(memLen-subMemLen+1);i++)
	{
		if(mem[i]==subMem[0])
		{		
			for(j=0; j<= subMemLen;j++)
			{
				if(mem[i+j]!=subMem[j])
					break;
			}

			if(j==subMemLen)
				return (&mem[i]);
		}
	}
	return NULL;
}
// 解析XML数据中的数据项
int CMyUtil::GetParamFromString(unsigned char *pString, unsigned char *ParamName, unsigned char *ParamValue, unsigned int *pParamValueLen)
{
	char str1[50];
	char str2[50];
	char* index1,*index2;
	memset(str1,0,50);
	sprintf(str1,"<%s>",ParamName);
	
	memset(str2,0,50);
	sprintf(str2,"</%s>",ParamName);
	index1 = strstr((char *)pString,(const char *)str1);
	if(index1 == NULL)
		return -1;

	index2 = strstr((char *)pString,(const char *)str2);
	if(index2 == NULL)
		return -1;

	if(index2<index1)
		return -1;
	else
	{
		if(ParamValue!=NULL)
			memcpy(ParamValue,index1+strlen(str1),index2-index1-strlen(str1));
		if(pParamValueLen!=NULL)
			*pParamValueLen=index2-index1-strlen(str1);
	}
	return 0;
}

//把证书统一转换成后台需要的二进制格式
int CMyUtil::Cert2Dercert(unsigned char *pucIn_cert, unsigned int uiIn_cert_len, unsigned char *pucOut_cert, unsigned int *puiOut_cert_len)
{
	char to_cmp[2]={0x30,0x82};
	//unsigned char in_data[2048]={0x00};
	//unsigned int  in_data_len=0;
	int len = 0;
	//len = uiRtCertLength;
	//return;
	//不是3082开头 且开始是M 表示是Base格式
	if(strncmp(to_cmp,(char*)pucIn_cert,2) && !strncmp("M",(char*)pucIn_cert,1))
	{
		if (pucOut_cert==NULL)  //第一次调用返回数据长度
		{
			*puiOut_cert_len = uiIn_cert_len*4/3;
			return 0;
		}
		//B64解码
		int length = 0;
		//int len;
		length = Km_Decode((char*)pucIn_cert,len,(char*)pucOut_cert);
		*puiOut_cert_len  = length;
	}
	else if(!strncmp(to_cmp,(char*)pucIn_cert,2) && strncmp("M",(char*)pucIn_cert,1))
	{
		//直接传
		if (pucOut_cert==NULL)  //第一次调用返回数据长度
		{
			*puiOut_cert_len = uiIn_cert_len;
			return 0;
		}
		//int len;
		len=uiIn_cert_len;
		memcpy(pucOut_cert,pucIn_cert,len);
		*puiOut_cert_len = uiIn_cert_len;
	}
	else if(strstr((char*)pucIn_cert,"BEGIN CERTIFICATE"))
	{//pem编码
		if (pucOut_cert==NULL)  //第一次调用返回数据长度
		{
			*puiOut_cert_len = uiIn_cert_len;
			return 0;
		}
		PKI_DATA in_cert,out_cert;
		in_cert.size = uiIn_cert_len;
		in_cert.value = pucIn_cert;   //转换前数据
		out_cert.size = uiIn_cert_len;
		out_cert.value = pucOut_cert;  //转换后数据

		pkiBase64Decode(in_cert,&out_cert);
		*puiOut_cert_len = out_cert.size;

	}
	else
	{		
		return -1;
	}
	return 0;
}



void CMyUtil::RevStr(char *str)
{
	int len;
	char *ptr;

	len = strlen(str);
	ptr = str + len - 1;

	while(str != ptr)
	{
		char ch;
		ch = *str;
		*str = *ptr;
		*ptr = ch;
		str++;
		//ptr自减前，在这里加一个判断，如果相等则结束循环
		//否则ptr就减一
		if(str == ptr)
			break;
		else
			ptr--;

	}
}
