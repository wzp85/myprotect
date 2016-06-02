#ifndef _CODE_H_
#define _CODE_H_

#include "PHCDS_datatype.h"

#define  TRUE  1
#define  FALSE 0

#define  bool_t int


#define  KM_LOGININ						1
#define  KM_LOGINOUT					2

#define  KM_CHECKINITPASSWD				3
#define  KM_MODIFYINITPASSWD			4
#define  KM_GENMAINKEY					5
#define  KM_GENKEYPROKEY				6
#define  KM_GENDEVKEY					7
#define  KM_GENADMIN					8

#define  KM_GETDEVKEYINFO				9
#define  KM_DEVKEYBACKUP				10
#define  KM_DEVKEYRECOVERY				11

#define  KM_GENAPPKEY					12
#define  KM_APPKEYMODPASSWD				13
#define  KM_APPKEYBACKUP				14              
#define  KM_APPKEYRECOVERY				15
#define  KM_APPKEYDESTROY				16
#define  KM_APPKEYGETLIST				17

#define  KM_GENKEYENCKEY				18
#define  KM_KEYENCKEYBACKUP				19
#define  KM_KEYENCRECOVERY				20
#define  KM_KEYENCDESTROY				21
#define  KM_KEYENCKEYGETLIST			22

#define  KM_DELADMIN					23
#define  KM_GETADMINLIST				24
#define  KM_ADMINBACKUP					25
#define  KM_ADMINRECOVERY				26


#define  KM_MANAGERNETMODIFY			27
#define  KM_APPNETMODIFY				28
#define  KM_NETRESTART					29
#define  KM_GETNETCONFIG				30

#define  KM_GETDEVINFO					31
#define  KM_SYMMCRYPT					32

#define  KM_GENAPPKEY_SIG				33
#define  SIG_ROOTCERTADD				34
#define  SIG_ROOTCERTDEL				35
#define  SIG_ROOTCERTUPDATE				36
#define  SIG_ROOTCERTGETLIST			37
#define  SIG_GENCERTREQUEST				38
#define  SIG_GETITEMAPPKEYINFO			39//该函数用于右键生成证书请求
#define  SIG_CACERTADD					40
#define  SIG_CACERTGETLIST				41
#define  SIG_CACERTDEL					42
#define  SIG_GETCACERTVS				43
#define  SIG_USRCERTIMPORT				44
#define  SIG_APPKEYBACKUP				45
#define  SIG_APPKEYRECOVERY				46
#define  SIG_USRCERTEXPORT				47

#define  SIG_GETLOG						48
#define  SIG_MODIFYSERVICELOGXMLFILE	49
#define  SIG_CACERTEXPORT				50
#define  SIG_RTCERTEXPORT				51

#define  SIG_CACERTBACKUP				52
#define  SIG_RTCERTBACKUP				53

#define  SIG_CACERTRECOVERY				54
#define  SIG_GETSERVICELOG				55
#define  SIG_SERVICELOGDEL				56
#define  SIG_SERVICELOGBACKUP			57
#define  SIG_SERVICELOGRECOVERY			58

#define  SIG_MNGRLOGAUDITALL			59
#define  SIG_MANAGEMENTLOGCOA			60				//管理日志分类审计
#define  SIG_CHECKSERVICELOG			61	
#define  SIG_GETSERVICELOGSEARCH		62	
#define  SIG_IMPORTSIGCERT    		63	
#define  SIG_APPKEYSET   		64

#define  SIG_NTPIPSET   			    65
#define  SIG_GETSYSLOG   			    66 //chunsy   
#define  SIG_GETSERVICELOGAUDIT         67 //chunsy 自定义报表

#define  PKI_GETXMLCERTINFO             80              //获取证书信息接口
#define  PKI_CHECKCERT                  81              //验证证书有效性接口
#define  PKI_GETCERTALGO                82              //获取证书算法标识chunsy

#define  MLOGCOA_ONLYOPTION						1000		//仅仅按照操作模块做							分类审计
#define  MLOGCOA_OPOPTYPE						1010		//按照操作模块和操作类型						分类审计
#define  MLOGCOA_OPOPOPRESULT					1100		//按照操作模块、类型、结果						分类审计
#define  MLOGCOA_OPOPOPTIME						1101		//按照操作模块、类型、结果、时间段				分类审计
#define  MLOGCOA_OPTIONTIME						1110		//按照操作模块、时间段							分类审计
#define  MLOGCOA_OPOPTYPETIME					1111		//按照操作模块、类型、时间段					分类审计



enum x_op
{
    X_ENCODE =0,
    X_DECODE = 1
};


enum d_op
{
    D_INT		= 0,
	D_INT_LEN	= 1,
	D_CHAR_LEN	= 2
};


typedef struct
{
    int  packetlen;
    int  func_num;
}packetInfo,*packetInfoPtr;

typedef struct
{
    int  size;
    BYTE *value;
}PKI_DATA, *PKI_PDATA;

typedef struct
{
    int        status;
    PKI_DATA   o_outData;
}returnPKI,*returnPKIPtr;




/*------------------------------------*/

typedef struct
{
    unsigned int		uiNameLength;
    unsigned char		*ucName;
    unsigned int		uiPasswdHashLength;
    unsigned char		*ucPasswdHash;
}argvCIPValue,*argvCIPValuePtr;

typedef struct
{
    int  status;
    int  sysStatus;
}returnCIPValue,*returnCIPValuePtr;

/*------------------------------------*/

typedef struct
{
    unsigned int		uiNameLength;
    unsigned char		*ucName;
    unsigned int		uiOldPasswordHashLength;
    unsigned char		*ucOldPasswordHash;
    unsigned int		uiNewPasswordHashLength;
    unsigned char		*ucNewPasswordHash;
}argvMIPValue,*argvMIPValuePtr;

typedef struct
{
    int					status;
}returnMIPValue,*returnMIPValuePtr;

/*------------------------------------*/

typedef struct
{
    unsigned int		uiAlgo;
}argvGMKValue,*argvGMKValuePtr;

typedef struct
{
    int					status;
}returnGMKValue,*returnGMKValuePtr;

/*------------------------------------*/

typedef struct
{
    unsigned int		uiAlgo;
}argvGKPKValue,*argvGKPKValuePtr;

typedef struct
{
    int					status;
}returnGKPKValue,*returnGKPKValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int		uiDevNameLength;
	unsigned char		*pucDevName;
	unsigned int		uiASymmAlgo;
	unsigned int		uiKeyLen;
	unsigned int		uiDevKeyPinLength;
	unsigned char		*pucDevKeyPin;
	
}argvGDKValue,*argvGDKValuePtr;

typedef struct
{
    int					status;
}returnGDKValue,*returnGDKValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uiAdminId;				//管理员标签
	unsigned int uiAdminNum;			//要生成的管理员个数

	unsigned int uiNameLen;				//管理员名称长度
	unsigned char *pucName;				//管理员名称

	unsigned int uiTelephoneLen;		//管理员电话号码长度
	unsigned char *pucTelephone;		//管理员电话号码

	unsigned int uiPaperType;			//证件类型

	unsigned int uiPaperNumLen;			//管理员证件长度
	unsigned char *pucPaperNum;			//证件号码
	
	unsigned int uiPubKeyLen;			//管理员公钥长度
	unsigned char *pucPubKey;			//管理员公钥

	unsigned int uiAdminType;			//管理员类型   0 为系统管理员 1 为密钥管理员
	
}argvGAValue,*argvGAValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiSignValueLen;
	unsigned char		*pucSignValue;
}returnGAValue,*returnGAValuePtr;

/*------------------------------------*/

typedef struct
{
    unsigned int		uiNum;
}argvGDKIValue,*argvGDKIValuePtr;

typedef struct
{
    int			status;

	unsigned int uiDevNameLen;			//设备名称长度
	unsigned char *ucDevName;			//设备名称

	unsigned int uiAlgo;				//算法类型

	unsigned int uiIfBak;				//是否已经备份

	unsigned int uiKeyLen;				//设备密钥长度
	unsigned int uiBakTotalKey;			//备份策略中总的Key个数
	unsigned int uiBakChooseKey;		//备份策略中要选择的Key的个数

	unsigned int uiBakTimeLen;			//备份时间的长度
	unsigned char *ucBakTime;			//备份时间
}returnGDKIValue,*returnGDKIValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int		uiAlgo;
    unsigned int		uiKeyBackupKeyLength;
    unsigned char		*pucKeyBackupKey;
}argvDKBValue,*argvDKBValuePtr;

typedef struct
{
    int					status;
    unsigned int		uiKeyBakLength;
    unsigned char		*pucKeyBak;
}returnDKBValue,*returnDKBValuePtr;

/*------------------------------------*/

typedef struct
{

    unsigned int		uiKeyBackupKeyLength;
    unsigned char		*pucKeyBackupKey;
	
	unsigned int		uiAlgo;
	unsigned int		uiKeyBakLength;
	unsigned char		*pucKeyBak;

	unsigned int		uiAdminPinLength;
	unsigned char		*pucAdminPin;
}argvDKRValue,*argvDKRValuePtr;

typedef struct
{
    int					status;
}returnDKRValue,*returnDKRValuePtr;

/*------------------------------------*/

typedef struct
{
    unsigned int		uikeyIndex;
	unsigned int		uiAlgo;
	unsigned int		uiKeyLength;
	unsigned int		uiKeyPasswdLength;
	unsigned char		*pucKeyPasswd;
	unsigned int		uiAppNameLength;
	unsigned char		*pucAppName;
	unsigned int		uiKeyType;

}argvGAKValue,*argvGAKValuePtr;

//签名服务器应用密钥结构体
typedef struct
{
	unsigned int        uiCityNameLength;
	unsigned char       *pucCityName;//---------------S
	unsigned int        uiCNNameLength;
	unsigned char       *pucCNName;//-----------------C
	unsigned int        uiAreaNameLength;
	unsigned char       *pucAreaName;//---------------L
	unsigned int        uiAtNameLength;
	unsigned char       *pucAtName;//-----------------O
	unsigned int        uiEmailLength;
	unsigned char       *pucEmail;//------------------E
	unsigned int		uiOUValueLength;
	unsigned char		*pucOUValue;//----------------OU
    unsigned int		uikeyIndex;//----------------密钥索引
	unsigned int		uiAlgo;//--------------------密钥算法标识
	unsigned int		uiKeyLength;//---------------密钥长度
	unsigned int		uiKeyPasswdLength;
	unsigned char		*pucKeyPasswd;
	unsigned int		uiAppNameLength;
	unsigned char		*pucAppName;//----------------CN
	unsigned int		uiKeyType;

}argvGAKValueSIG,*argvGAKValuePtrSIG;

typedef struct
{
    int					status;
}returnGAKValue,*returnGAKValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uikeyIndex; 
	unsigned int uiOldKeyPasswdLength;
	unsigned char *pucOldKeyPasswd;
	unsigned int uiNewKeyPasswdLength;
	unsigned char *pucNewKeyPasswd;
	

}argvAKMPValue,*argvAKMPValuePtr;

typedef struct
{
    int					status;
}returnAKMPValue,*returnAKMPValuePtr;

/*------------------------------------*/
typedef struct
{

	unsigned int	uiAlgo;
	unsigned int	uiKeyIndexNum;
	unsigned int	*puiKeyIndex;
	unsigned int	uiKeyBackupKeyLength;
	unsigned char	*pucKeyBackupKey;


}argvAKBValue,*argvAKBPValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiKeyBakLength;
	unsigned char		*pucKeyBak;

}returnAKBValue,*returnAKBValuePtr;

/*------------------------------------*/
typedef struct
{
	unsigned int	uiAdminIndexNum;
	unsigned int	*puiAdminIndex;

}argvABValue,*argvABValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiAdminBakLength;
	unsigned char		*pucAdminBak;

}returnABValue,*returnABValuePtr;

/*------------------------------------*/
typedef struct
{
	unsigned int		uiAdminBackupLength;
	unsigned char		*pucAdminBackup;


}argvARValue,*argvARValuePtr;

typedef struct
{
    int					status;

}returnARValue,*returnARValuePtr;

/*------------------------------------*/
typedef struct
{
	unsigned int	uiKeyIndexNum;
	unsigned int	*puiKeyIndex;
	//unsigned int    uiIsSIG;

}argvAKDValue,*argvAKDPValuePtr;

typedef struct
{
    int					status;
}returnAKDValue,*returnAKDValuePtr;


/*------------------------------------*/

typedef struct
{
	unsigned int	uiAlgo;
	unsigned int    uiIsSIG;
}argvAKGValue,*argvAKGValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiKeyListLen;
	unsigned char		*puiKeyList;

}returnAKGValue,*returnAKGValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int		uikeyLabel;
	unsigned int		uiAlgo;
	unsigned int		uiEncKeyNameLength;
	unsigned char		*pucEncKeyName;

}argvGKEKValue,*argvGKEKValuePtr;

typedef struct
{
    int					status;
}returnGKEKValue,*returnGKEKValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uiAdminId;
	unsigned int uiHashAlgo;
	unsigned int uiSignAlgo;
	unsigned int uiRandomLength;
	unsigned char * pucRandom;
	unsigned int uiRandomSignLength;
	unsigned char * pucRandomSign;
	unsigned int uiDevSignLength;
	unsigned char * pucDevSign;

}argvLOGINValue,*argvLOGINValuePtr;

typedef struct
{
    int					status;
}returnLOGINValue,*returnLOGINValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uiAdminId;

}argvDAValue,*argvDAValuePtr;

typedef struct
{
    int					status;
}returnDAValue,*returnDAValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int	uiAlgo;
}argvGALValue,*argvGALValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiAdminListLen;
	unsigned char		*puiAdminList;

}returnGALValue,*returnGALValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int	uiAlgo;
}argvNETRSValue,*argvNETRSValuePtr;

typedef struct
{
    int					status;
}returnNETRSValue,*returnNETRSValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int		eth;
}argvGNCValue,*argvGNCValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiNetLen;
	unsigned char		*pucNet;

}returnGNCValue,*returnGNCValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uiNetLen;
	unsigned char * pucNet;
}argvMNMValue,*argvMNMValuePtr;

typedef struct
{
    int					status;
}returnMNMValue,*returnMNMValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int uiNetLen;
	unsigned char * pucNet;
}argvANMValue,*argvANMValuePtr;

typedef struct
{
    int					status;
}returnANMValue,*returnANMValuePtr;

/*------------------------------------*/


typedef struct
{
	unsigned int	uiAlgo;
}argvGDIValue,*argvGDIValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiDevInfoLen;
	unsigned char		*pucDevInfo;
}returnGDIValue,*returnGDIValuePtr;

/*------------------------------------*/

typedef struct
{

    unsigned int		uiKeyBackupKeyLength;
    unsigned char		*pucKeyBackupKey;
	
	unsigned int		uiAlgo;
	unsigned int		uiKeyBakLength;
	unsigned char		*pucKeyBak;
}argvKERValue,*argvKERValuePtr;

typedef struct
{
    int					status;
}returnKERValue,*returnKERValuePtr;

/*------------------------------------*/

typedef struct
{
	unsigned int		uiOper;					//	加密/解密
	unsigned int		uiAlgo;					//	算法
    unsigned int		uiSymmKeyLength;		//	对称密钥
    unsigned char		*pucSymmKey;		
    unsigned int		uiTextLength;			//	密文/原文
    unsigned char		*pucText;	
}argvCRYPTValue,*argvCRYPTValuePtr;

typedef struct
{
    int					status;
    unsigned int		uiResaultLength;			//	原文/密文
    unsigned char		*pucResault;
}returnCRYPTValue,*returnCRYPTValuePtr;

typedef struct
{
	unsigned int        uiAlgo;
	unsigned int		uiKeyLength;
	unsigned int        uiCertIndex;
//	unsigned char		*putCertIndex;
	unsigned int        uiCertNameLength;
	unsigned char		*pucCertName;
//	unsigned char       *pucCertIndex;
	unsigned int        uiAtNameLength;
	unsigned char       *pucAtName;
	unsigned int        uiHostLength;
	unsigned char       *pucHost;
	unsigned int        uiPhoneLength;
	unsigned char       *pucPhone;
	unsigned int        uiRtCertLength;
	unsigned char       *pucRtCert;
	unsigned int        uiCertSNLength;
	unsigned char		*pucCertSN;
}argvRCAValue,*argvRCAValuePtr;


typedef struct
{
	unsigned int        status;
}returnRCAValue,*returnRCAValuePtr;


typedef struct
{
	unsigned int        uiCertIndexNum;
	unsigned int        *certIndex;
}argvRCDValue,*argvRCDValuePtr;

typedef struct
{
	unsigned int        status;
}returnRCDValue,*returnRCDValuePtr;

typedef struct
{
	unsigned int	    uiAlgo;
	unsigned int        uiCertIndex;
	unsigned int        uiCertNameLength;
	unsigned char	    *pucCertName;
	unsigned int		uiAtNameLength;
	unsigned char		*pucAtName;
	unsigned int		uiHostLength;
	unsigned char		*pucHost;
	unsigned int		uiPhoneLength;
	unsigned char		*pucPhone;
}argvRCUValue,*argvRCUValuePtr;

typedef struct
{
	unsigned int		status;
}returnRCUValue,*returnRCUValuePtr;


typedef struct
{
	unsigned int	uiAlgo;
}argvRCGValue,*argvRCGValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiCertListLen;
	unsigned char		*puiCertList;

}returnRCGValue,*returnRCGValuePtr;

typedef struct
{
	unsigned int		uiSymmAlgo;
	unsigned int		uiHashAlgo;
	unsigned int		uiKeyAlgo;
	unsigned int		uiIndexLength;
	unsigned char		*pucIndex;
	unsigned int		uiPasswordLength;
	unsigned char		*pucPassword;
	unsigned int		uiRequestLength;
	unsigned char		*pucRequest;
}argvSGCRValue,*argvSGCRValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiB64ReqLength;
	unsigned char		*pucB64Req;
	unsigned int		uiReqLength;
	unsigned char		*pucReq;
}returnSGCRValue,*returnSGCRValuePtr;

typedef struct
{
	unsigned int		uiSymmAlgo;
	unsigned int		uiHashAlgo;
	unsigned int		uiKeyAlgo;
	unsigned int		uiIndexLength;
	unsigned char		*pucIndex;
	unsigned int		uiPasswordLength;
	unsigned char		*pucPassword;
	unsigned int		uiIPAddrLength;
	unsigned char		*pucIPAddr;
	unsigned int		uiPortLength;
	unsigned char		*pucPort;
	unsigned int		uiRequestLength;
	unsigned char		*pucRequest;
}argvSGCOValue,*argvSGCOValuePtr;

typedef struct
{
	unsigned int		status;

}returnSGCOValue,*returnSGCOValuePtr;
	typedef struct
{
	unsigned int		uiKeyAlgo;
	unsigned int		uiIndexLength;
	unsigned char		*pucIndex;
	unsigned int		uiPasswordLength;
	unsigned char		*pucPassword;
	unsigned int		uiEncCertLength;
	unsigned char		*pucEncCert;
	unsigned int		uiSigCertLength;
	unsigned char		*pucSigCert;
	unsigned int		uiEncPubKeyLength;
	unsigned char		*pucEncPubKey;
	unsigned int		uiEncPrivKeyLength;
	unsigned char		*pucEncPrivKey;
	unsigned int		encType;

}argvSISCValue,*argvSISCValuePtr;

typedef struct
{
	unsigned int		status;

}returnSISCValue,*returnSISCValuePtr;

typedef struct
{
	unsigned int		uiKeyIndex;
}argvGIAKIValue,*argvGIAKIValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		keyInfoItemLength;
	unsigned char		*pucKeyInfoItem;
}returnGIAKIValue,returnGIAKIValuePtr;



typedef struct//-----------------add by chunsy  用于获取带优先级的CA验证策略
{
	unsigned int        option;

	unsigned int        CRLhandLen;//--------手动导入CRL
	unsigned char       *CRLhand;

	unsigned int        autoCRLipLen;//------自动同步CRL
	unsigned char       *autoCRLip;//----from ldap
	unsigned int        autoCRLportLen;
	unsigned char       *autoCRLport;
	unsigned int        autoCRLurlLen;
	unsigned char       *autoCRLurl;
	unsigned int        autoCRLtime;

	unsigned int        autoFromHTTPurlLen;//-----from Http
	unsigned char       *autoFromHTTPurl;
	unsigned int        autoFromHTTPtime;
	unsigned int        autoCRLtype;

	unsigned int        CRLverifyTime;//---------CRL发布点验证
	
	unsigned int        OCSPipLen;//------------OCSP验证
	unsigned char       *OCSPip;
	unsigned int        OCSPprotLen;
	unsigned char       *OCSPport;
	unsigned int        OCSPurlLen;
	unsigned char       *OCSPurl;
	unsigned int        OCSPcertstand;
	unsigned int        OCSPtalktype;

	unsigned int        OCSPverifyLen;//---------------OCSP发布点验证
	unsigned char       *OCSPverify;

}VerifyPriorityStrategy,*VerifyPriorityStrategyPtr;

typedef struct//chunsy 4/28
{
	unsigned int		uiRtCertIndex;
	unsigned int        uiRtCertType;
	unsigned int		uiCACertIndex;
	unsigned int        uiAlgo;
	unsigned int		uiKeyLength;
	unsigned int        uiCertIndexLength;
	unsigned char		*putCertIndex;
	unsigned int        uiCertNameLength;
	unsigned char		*pucCertName;
	unsigned int        uiAtNameLength;
	unsigned char       *pucAtName;
	unsigned int        uiHostLength;
	unsigned char       *pucHost;
	unsigned int        uiPhoneLength;
	unsigned char       *pucPhone;
	unsigned int        uiCACertLength;
	unsigned char       *pucCACert;
	unsigned int		uiTrustChainLength; //7
	unsigned char		*pucTrustChain;
	//验证策略部分

	unsigned int        option;

	unsigned int        uiCRLhandLen;//--------手动导入CRL
	unsigned char       *pucCRLhand;

	unsigned int        uiautoCRLipLen;//------自动同步CRL
	unsigned char       *pucautoCRLip;//---from ldap
	unsigned int        uiautoCRLportLen;
	unsigned char       *pucautoCRLport;
	unsigned int        uiautoCRLurlLen;
	unsigned char       *pucautoCRLurl;
	unsigned int        uiautoCRLtime;

	unsigned int        uiautoFromHTTPurlLen;//-----from Http
	unsigned char       *pucautoFromHTTPurl;
	unsigned int        uiautoFromHTTPtime;
	unsigned int        uiautoCRLtype;

	unsigned int        uiCRLverifyTime;//---------CRL发布点验证
	
	unsigned int        uiOCSPipLen;//------------OCSP验证
	unsigned char       *pucOCSPip;
	unsigned int        uiOCSPprotLen;
	unsigned char       *pucOCSPport;
	unsigned int        uiOCSPurlLen;
	unsigned char       *pucOCSPurl;
	unsigned int        uiOCSPcertstand;
	unsigned int        uiOCSPtalktype;

	unsigned int        uiOCSPverifyLen;//---------------OCSP发布点验证
	unsigned char       *pucOCSPverify;
	
}argvCCAPriorityValue,*argvCCAPriorityValuePtr;



typedef struct
{
	unsigned int		status;
}returnCCAValue,*returnCCAValuePtr;

typedef struct
{
	unsigned int	uiAlgo;
}argvCCGValue,*argvCCGValuePtr;

typedef struct
{
    int					status;
	unsigned int		uiCertListLen;
	unsigned char		*puiCertList;
}returnCCGValue,*returnCCGValuePtr;

typedef struct
{
	unsigned int        uiCertIndexNum;
	unsigned int        *certIndex;
}argvCCDValue,*argvCCDValuePtr;

typedef struct
{
	unsigned int        status;
}returnCCDValue,*returnCCDValuePtr;

typedef struct
{
	unsigned int        uiCertIndex;
}argvGCAVSValue,*argvGCAVSValuePtr;

typedef struct
{
	unsigned int        status;
	unsigned int		uiRtCertIndex;
	unsigned int        uiRtCertType;//上级证书的类型用于多级CA判断add by syc 14/12/05
	unsigned int		uiCACertIndexLength;
	unsigned char		*pucCACertIndex;
	//验证策略部分
	unsigned int        option;
	unsigned int        uiCRLhandLen;//--------手动导入CRL
	unsigned char       *pucCRLhand;
	unsigned int        uiautoCRLipLen;//------自动同步CRL
	unsigned char       *pucautoCRLip;
	unsigned int        uiautoCRLportLen;
	unsigned char       *pucautoCRLport;
	unsigned int        uiautoCRLurlLen;
	unsigned char       *pucautoCRLurl;
	unsigned int        uiautoCRLtime;
	unsigned int        uiautoFromHTTPurlLen;//-----from Http
	unsigned char       *pucautoFromHTTPurl;
	unsigned int        uiautoFromHTTPtime;

	unsigned int        uiautoCRLtype;
	unsigned int        uiCRLverifyTime;//---------CRL发布点验证
	unsigned int        uiOCSPipLen;//------------OCSP验证
	unsigned char       *pucOCSPip;
	unsigned int        uiOCSPprotLen;
	unsigned char       *pucOCSPport;
	unsigned int        uiOCSPurlLen;
	unsigned char       *pucOCSPurl;
	unsigned int        uiOCSPcertstand;
	unsigned int        uiOCSPtalktype;
	unsigned int        uiOCSPverifyLen;//---------------OCSP发布点验证
	unsigned char       *pucOCSPverify;
	
}returnGCAVSValue,*returnGCAVSValuePtr;

typedef struct
{
	unsigned int		uiCACertIndex;
	unsigned int        uiAlgo;
	unsigned int		uiKeyLength;
	unsigned int		uiKeyType;
	unsigned int		uiKeyIndex;

	unsigned int        uiCertIndexLength;
	unsigned char		*putCertIndex;
	unsigned int        uiCertNameLength;
	unsigned char		*pucCertName;
	unsigned int        uiAtNameLength;
	unsigned char       *pucAtName;
	unsigned int        uiHostLength;
	unsigned char       *pucHost;
	unsigned int        uiPhoneLength;
	unsigned char       *pucPhone;
	unsigned int        uiUsrEncCertLength;
	unsigned char       *pucUsrEncCert;
	unsigned int		uiUsrSigCertLength;
	unsigned char		*pucUsrSigCert;
	unsigned int		uiPrivateKeyAccessRightCodeLength;
	unsigned char		*pucPrivateKeyAccessRightCode;
}argvUCIPValue,*argvUCIPValuePtr;

typedef struct
{
	unsigned int		status;
}returnUCIPValue,*returnUCIPValuePtr;

typedef struct
{
	unsigned int	uiAlgo;
	unsigned int	uiKeyIndexNum;
	unsigned int	*puiKeyIndex;
	unsigned int	uiKeyBackupKeyLength;
	unsigned char	*pucKeyBackupKey;
}argvSAKBValue,*argvSAKBValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiKeyBakLength;
	unsigned char		*pucKeyBak;
}returnSAKBValue,*returnSAKBValuePtr;

typedef struct
{
	unsigned int        uiCertIndex;
}argvUCEPValue,*argvUCEPValuePtr;


typedef struct
{
	unsigned int        status;
	unsigned int		uiEncCertLength;
	unsigned char		*pucEncCert;
	unsigned int		uiSigCertLength;
	unsigned char		*pucSigCert;
}returnUCEPValue,*returnUCEPValuePtr;


typedef struct
{
	unsigned int		page;//第几页
}argvGLValue,*argvGLValuePtr;


typedef struct
{
	unsigned int		status;
	unsigned int		pageCount;
	unsigned int		uiLogLength;
	unsigned char		*pucLog;
	unsigned int		uiPubKeyLength;
	unsigned char		*pucPubKey;
}returnGLValue,*returnGLValuePtr;

typedef struct
{
	unsigned int		page;//第几页
}argvGSLValue,*argvGSLValuePtr;

typedef struct
{
	unsigned int       page;
}argvGSYSValue,*argvGSYSValuePtr;//chunsy


typedef struct
{
	unsigned int		status;
	unsigned int		pageCount;
	unsigned int		uiLogLength;
	unsigned char		*pucLog;
}returnGSLValue,*returnGSLValuePtr;

typedef struct
{
	unsigned int        status;
	unsigned int        pageCount;
	unsigned int        uiLogLength;
	unsigned char       *pucLog;
}returnGSYSValue,*returnGSYSValuePtr;//chunsy
typedef struct
{
	unsigned int		page;//第几页
	unsigned int	 uiStartTimeLength;
	unsigned char		*pStartTime;
	unsigned int		uiEndTimeLength;
	unsigned char		 *pEndTime;
	unsigned int		uiLogopkind;
	//unsigned char	*pLogopkind;
}argvGSLSValue,*argvGSLSValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		pageCount;
	unsigned int		uiLogLength;
	unsigned char		*pucLog;
}returnGSLSValue,*returnGSLSValuePtr;

//-----------------报表的结构体
typedef struct
{
	unsigned int		page;//第几页
	unsigned int	 uiStartTimeLength;
	unsigned char		*pStartTime;
	unsigned int		uiEndTimeLength;
	unsigned char		 *pEndTime;
	unsigned int		uiLogresult;
	//unsigned char	*pLogresult;
}argvGSLAValue,*argvGSLAValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		pageCount;
	unsigned int		uiLogLength;
	unsigned char		*pucLog;
}returnGSLAValue,*returnGSLAValuePtr;



typedef struct
{
	unsigned int		id;//日志索性
}argvCSLValue,*argvCSLValuePtr;


typedef struct
{
    int					status;
}returnCSLValue,*returnCSLValuePtr;

typedef struct
{
	unsigned int		uiLogContentType;
	unsigned int		uiLogPolicyType;
	unsigned int		uiLogRequestType;
	unsigned int        uiLogCount;
	unsigned int        uiLogTime;
	unsigned int		uiURLLength;
	unsigned char		*pucURL;
}argvMSLXFValue,*argvMSLXFValuePtr;

typedef struct
{
	unsigned int		status;
}returnMSLXFValue,*returnMSLXFValuePtr;


typedef struct
{
	unsigned int        uiCertIndex;
}argvCCEPValue,*argvCCEPValuePtr;


typedef struct
{
	unsigned int        status;
	unsigned int		uiCertLength;
	unsigned char		*pucCert;
}returnCCEPValue,*returnCCEPValuePtr;

typedef struct
{
	unsigned int        uiCertIndex;
}argvRCEPValue,*argvRCEPValuePtr;


typedef struct
{
	unsigned int        status;
	unsigned int		uiCertLength;
	unsigned char		*pucCert;
}returnRCEPValue,*returnRCEPValuePtr;


typedef struct
{
	unsigned int	uiKeyIndexNum;
	unsigned int	*puiKeyIndex;
}argvCACBValue,*argvCACBValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiCertBakLength;
	unsigned char		*pucCertBak;
}returnCACBValue,*returnCACBValuePtr;

typedef struct
{
	unsigned int	uiKeyIndexNum;
	unsigned int	*puiKeyIndex;
}argvRTCBValue,*argvRTCBValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiCertBakLength;
	unsigned char		*pucCertBak;
}returnRTCBValue,*returnRTCBValuePtr;

typedef struct
{
	unsigned int		uiCertBakLength;
	unsigned char		*pucCertBak;
}argvCACRValue,*argvCACRValuePtr;

typedef struct
{
	unsigned int		status;
}returnCACRValue,*returnCACRValuePtr;

typedef struct
{
	unsigned int	uiLogIndexNum;
	unsigned int	*puiLogIndex;
	unsigned int    uiyear;//年月
	unsigned int    uimonth;
}argvSLDValue,*argvSLDValuePtr;

typedef struct
{
	unsigned int		status;
}returnSLDValue,*returnSLDValuePtr;

typedef struct
{
	unsigned int	uiLogIndexNum;
	unsigned int	*puiLogIndex;
}argvSLBValue,*argvSLBValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiLogBakLength;
	unsigned char		*pucLogBak;
}returnSLBValue,*returnSLBValuePtr;

typedef struct
{
	unsigned int		uiLogBakLength;
	unsigned char		*pucLogBak;
}argvSLRValue,*argvSLRValuePtr;

typedef struct
{
	unsigned int		status;
}returnSLRValue,*returnSLRValuePtr;

typedef struct
{
	unsigned int		isAllAudit;//1表示审计所有日志
}argvMLAAValue,*argvMLAAValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int		uiLogIndexNum;
	unsigned int		*puiLogIndex;
	unsigned int		uiLogTimeLen;
	unsigned char		*pucLogTime;
}returnMLAAValue,*returnMLAAValuePtr;

typedef struct
{
	unsigned int		uiAuditMold;			//审计类型

	unsigned int		uiOptionLen;			
	unsigned char		*pucOption;				//审计子项：操作模块
	unsigned int		uiOptionTypeLen;
	unsigned char		*pucOptionType;			//审计子项：操作类型
	unsigned int		uiOptionResultLen;
	unsigned char		*pucOptionResult;		//审计子项：操作结果
	unsigned int		uiStartTimeLen;
	unsigned char		*pucStartTime;			//审计子项：时间段查询时左区间值
	unsigned int		uiEndTimeLen;
	unsigned char		*pucEndTime;			//审计子项：时间段查询时右区间值
}argvMLCOAValue,*argvMLCOAValuePtr;//Management Log Classification Of Audit Struct:管理日志分类审计结构
typedef struct
{
	unsigned int		status;
	unsigned int		count;
	unsigned int		uiLogTimeLen;
	unsigned char		*pucLogTime;
}returnMLCOAValue,*returnMLCOAValuePtr;
typedef struct
{
	unsigned int		uiInt1;			
	unsigned int		uiInt2;	
	unsigned int		uiInt3;	 
}argvThreeIntValue,*argvThreeIntValuePtr;

typedef struct
{
	unsigned int		uiInt1;			
	unsigned int		uiInt2;	
	unsigned int		uiInt3;	
}returnThreeIntValue,*returnThreeIntValuePtr;
typedef struct
{
	unsigned int		uiInt1;			

	unsigned int		uiInt2;	
	unsigned int		uiInt3;	
	unsigned int		uiInt4;
 
}argvFourIntValue,*argvFourIntValuePtr;

typedef struct
{
	unsigned int 		uiCharLen;			

	unsigned char *		uiChar;	
	
 
}argvOneCharValue,*argvOneCharValuePtr;
typedef struct
{
	unsigned int		status;			

	unsigned int		uiInt2;	
	unsigned int		uiInt3;	
    unsigned int		uiInt4;	
}returnFourIntValue,*returnFourIntValuePtr;

typedef struct
{
	unsigned int		status;
}returnOneIntValue,*returnOneIntValuePtr;

typedef struct
{
	unsigned int		status;
	unsigned int 		uiCharLen;			
	unsigned char *		uiChar;	
}returnOneIntOneCharValue,*returnOneIntOneCharValuePtr;





typedef struct CRL_LIST {
	
  PKI_DATA serialNumber;//需要大于30个字节
  BYTE     revokeTime[20];
  BYTE     reasonCode;
  struct CRL_LIST *next;
}CRL_LIST;
typedef struct {
  PKI_DATA nameInfo;//modify by shenjun at 20090430
  int       keySize;
}CERTREQ_INFO;
typedef struct {
  int bitLen;
  char  *bits;
} PKI_BITS;
typedef struct {
  PKI_DATA ExtOid;
  INT critical;
  PKI_DATA extvalue;
}EXTENTIONS;
//CA证书策略数据结构
typedef struct {
  int		certValidMonths;
  PKI_BITS	signKeyUsage;
  PKI_BITS	encryptionKeyUsage;
  PKI_DATA	serialNumber;		//zhangxj added in 2003-12-4
								//如果是双证的两个序列号，中间以"||"进行隔离，前面是签名证书
								//序列号，后面是加密证书序列号
  int		countofExtensions;	//zhangxj added in 2003-12-4
  EXTENTIONS *extensions;
} CERT_POLICY;
typedef struct {
 
  int		countofExtensions;	
  EXTENTIONS *extensions;
} CRL_EXTENSIONS;
//证书信息数据结构
typedef struct {
  BYTE beginTime[20];
  BYTE endTime[20];
} TIME_PERIOD;

typedef struct {
  BYTE encryptionAlgo[30];
  BYTE subjectPubKey[300];
}SUBJECT_PUBLIC_KEY_INFO;


typedef struct {
  int version;
  BYTE serialNumber[30];
  BYTE signatureAlgo[30];
  PKI_DATA issuer;
  TIME_PERIOD validTime;
  PKI_DATA subject;
  SUBJECT_PUBLIC_KEY_INFO subjectPubKeyInfo;
} PKI_CERT_INFO;

typedef struct {
  int certCnt;
  PKI_CERT_INFO signCert;
  PKI_CERT_INFO encryptionCert;
  PKI_DATA  fingerPrint;
} PKI_CERTINFO;
/*------------------------------------*/

/*------------------------------------*/
//  全部改回到类似签名服务器接口的传参方式，不用每种业务定义一种结构类型

typedef struct
{
	unsigned int	uiIntValueLen;
	unsigned char	*pucIntValue;
}argPucArg,*argPucArgPtr;

typedef struct
{
    int    status;
	unsigned int	uiOutValueLen;
	unsigned char	*pucOutValue;
	//unsigned int    uipublickeylen;
	//unsigned char   *pucpublickey;
} returnIntPuc,*returnIntPucPtr;
//该类型在以下功能使用
/*
1）证书解析功能
2）
*/
//typedef struct
//{
//	unsigned int	uiIntValueLen;
//	unsigned char	*pucIntValue;
//}argPucAr,*argPucArgPt;
//typedef struct
//{
//    int    status;
//	unsigned int	uiOutValueLen;
//	unsigned char	*pucOutValue;
//	//unsigned int    uipublickeylen;
//	//unsigned char   *pucpublickey;
//} returnIntPu,*returnIntPucPt;
//该类型在以下功能使用
/*
1）证书解析功能

*/


int int_proc( char *p,int *num,enum x_op op_type);
int byte_array_proc( char *p, char *result, int length, enum x_op op_type);

int packet_proc( packetInfo *pkt,char *result,enum x_op op_type);
int packet_len( packetInfo );

void PKI_DATA_free( PKI_DATA * );
void returnPKI_free(returnPKI *);


int data_proc_len(void *retv,enum d_op *op_list,int op_num);

void data_proc_free(void *argv ,enum d_op *op_list,int op_num);

bool_t data_proc(void *argv ,char * result,enum x_op op_type,enum d_op *op_list,int op_num);

//int Write2File(char * filename, unsigned char* pbData,unsigned int nDataLen);

long int encode( char *src,long int src_len, char *dst);
long int decode(char *src, long int src_len, char *dst);
void Transform(char * pdata, int len);
#endif
