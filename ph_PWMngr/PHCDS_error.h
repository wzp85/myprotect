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

#ifndef _PHCDS_ERROR_H
#define _PHCDS_ERROR_H



#define SDR_OK	                                0x00000000

#define SDR_BSAE	                            0x00090000

#define PHCDS_SESSIONHANDLE_CLOSED            	SDR_BSAE+0x00000100  /*含义：函数执行过程中，该会话已经关闭。*/

#define PHCDS_SESSIONHANDLE_COUNT             	SDR_BSAE+0x00000101  /*含义：打开的会话太多。*/

#define PHCDS_SESSIONHANDLE_INVALID           	SDR_BSAE+0x00000102  /*含义：指定的会话句柄无效。*/

#define PHCDS_LOGIN_FAILED  		      	SDR_BSAE+0x00000103  /*含义：获取私钥使用权限失败。*/

#define PHCDS_LOGIN_REPEAT      	      	SDR_BSAE+0x00000104  /*含义：获取私钥使用权限重复。*/

#define PHCDS_NOT_LOGIN       	    	      	SDR_BSAE+0x00000105  /*含义：私钥使用权限未获取。*/

#define PHCDS_INPUT_LEN_ERROR                 	SDR_BSAE+0x00000106  /*含义：输入参数长度指示错误。*/

#define PHCDS_KEYID_INVALID           	      	SDR_BSAE+0x00000107  /*含义：指定的密钥号非法。*/

#define PHCDS_ALGID_INVALID                   	SDR_BSAE+0x00000108  /*含义：算法标识无效。*/

#define PHCDS_NOT_INITIALIZED         	      	SDR_BSAE+0x00000109  /*含义：未调用初始化。*/

#define PHCDS_ALREADY_INITIALIZED      	   	SDR_BSAE+0x00000110  /*含义：初始化已调用。*/

#define PHCDS_DEVICEHANDLE_INVALID           	SDR_BSAE+0x00000111  /*设备句柄无效*/

#define PHCDS_OPENDEVICE_ERROR          	SDR_BSAE+0x00000112	/*打开设备错误*/

#define PHCDS_CLOSEDEVICE_ERROR           	SDR_BSAE+0x00000113	/*关闭设备错误*/

#define PHCDS_OPENSESSION_ERROR           	SDR_BSAE+0x00000114	/*打开会话错误*/

#define PHCDS_CLOSESESSION_ERROR           	SDR_BSAE+0x00000115	/*关闭会话错误*/

#define PHCDS_GenerateRandom_ERROR           	SDR_BSAE+0x00000116	/*产生随机数错误*/

#define PHCDS_GenerateKeyPair_RSA_ERROR       	SDR_BSAE+0x00000117  /*产生RSA密钥对错误*/

#define PHCDS_ExternalPublicKeyOperation_ERROR  SDR_BSAE+0x00000118 /*外部公钥加密错误*/

#define PHCDS_ExternalPrivateKeyOperation_ERROR SDR_BSAE+0x00000119 /*外部私钥解密错误*/

#define PHCDS_ImportKey_ERROR 			SDR_BSAE+0x00000120 /*外部导入对称密钥错误*/

#define PHCDS_Encrypt_ERROR			SDR_BSAE+0x00000121  /*对称加密错误*/

#define PHCDS_Decrypt_ERROR			SDR_BSAE+0x00000122 /*对称解密错误*/

#define PHCDS_CalculateMAC_ERROR		SDR_BSAE+0x00000123 /*MAC计算错误*/

#define PHCDS_DestoryKey_ERROR			SDR_BSAE+0x00000124 /*销毁密码卡上的会话密钥错误*/

#define  PHCDS_HashInit_ERROR			SDR_BSAE+0x00000125 /*HASH初始化错误*/

#define  PHCDS_HashUpdate_ERROR			SDR_BSAE+0x00000126 /*HASH运算错误*/

#define  PHCDS_HashFinal_ERROR			SDR_BSAE+0x00000127 /*HASH运算结束错误*/

#define PHCDS_PARAMETER_INVALID     		SDR_BSAE+0x00000128    /*含义：输入参数无效。*/

#define PHCDS_SESSIONLIST_INVALID     		SDR_BSAE+0x00000129 /*含义：SESSION链表为空。*/

#define PHCDS_SESSIONID_INVALID     		SDR_BSAE+0x00000130  /*含义：SESSION链表中没有SESSIONID指示的会话。*/

#define PHCDS_SESSIONSTAT_INVALID    		SDR_BSAE+0x00000131 /*含义：SESSIONSTAT状态异常（非0和1）。*/

#define PHCDS_KEYCONTAINER_INVALID   		SDR_BSAE+0x00000132 /*含义：密钥容器链表为空。*/

#define PHCDS_KEYRECORD_INVALID     		SDR_BSAE+0x00000133 /*含义：密钥容器链表中没有指定的密钥。*/

#define PHCDS_KEYRECORDVALUETYPE_INVALID     	SDR_BSAE+0x00000134 /*含义：密钥内容的类型值无效。*/

#define PHCDS_USERKEYLIST_INVALID     		SDR_BSAE+0x00000135  /*含义：密钥加密密钥链表为空。*/

#define PHCDS_USERKEY_INVALID     		SDR_BSAE+0x00000136 /*含义：密钥加密密钥链表中没有指定的密钥。*/

#define PHCDS_USERKEYVALUETYPE_INVALID     	SDR_BSAE+0x00000137 /*含义：密钥内容的类型值无效。*/

#define PHCDS_FILETYPE_INVALID      		SDR_BSAE+0x00000138  //无效文件类型

#define PHCDS_PARAMNAME_INVALID      		SDR_BSAE+0x00000139 //无效参数名称

#define PHCDS_PARAMNAMELEN_INVALID      	SDR_BSAE+0x00000140 //无效参数名称长度

#define PHCDS_OPENFILE_ERROR      		SDR_BSAE+0x00000141 //打开文件失败

#define PHCDS_CREATFILE_ERROR      		SDR_BSAE+0x00000142//创建文件失败

#define PHCDS_WRITEFILE_ERROR	  		SDR_BSAE+0x00000143//写文件失败

#define PHCDS_CLOSEFILE_ERROR	   		SDR_BSAE+0x00000144//关闭文件失败

#define PHCDS_FSEEK_ERROR          		SDR_BSAE+0x00000145//改变文件指针失败

#define PHCDS_PAD_ERROR		   		SDR_BSAE+0x00000146 /*对称加解密补位错误*/

#define PHCDS_USEPIN_ERROR			SDR_BSAE+0x00000147  /*用户PIN错误*/

#define PHCDS_KEYTYPE_INVALID   	        SDR_BSAE+0x00000148  /*含义：密钥类型无效。*/

#define PHCDS_PRIVATEKEY_DECRYPT_ERROR    	SDR_BSAE+0x00000149  /*含义：私钥解密失败。*/

#define PHCDS_ERROR_DLL_LOAD_ERROR   		SDR_BSAE+0x00000150    //加载加密卡库失败

#define PHCDS_MEMALLOC_ERROR  	    		SDR_BSAE+0x00000151     //内存分配出错

#define PHCDS_DELETE_DIR_ERROR	   		SDR_BSAE+0x00000152//删除文件失败

#define PHCDS_EXPORT_KEY_LENGTH_ERROR	   	SDR_BSAE+0x00000153//备份密钥的长度有误

#define PHCDS_NO_KEY				SDR_BSAE+0x00000154 //无此密钥

#define PHCDS_CARD_FLAG_ERROR				   	SDR_BSAE+0x00000155 //加密卡标识配置有误

#define PHCDS_NO_CARD_SESSION_ERROR				SDR_BSAE+0x00000156 //没有加密卡会话

#define PHCDS_SOCKET_SERVER_RECV_ERROR				SDR_BSAE+0x00000157 //密码机接收数据错误

#define PHCDS_SOCKET_SERVER_PACKET_ERROR				SDR_BSAE+0x00000158 //密码机解析数据错误

#define PHCDS_SESSIONKEY_INVALID				SDR_BSAE+0x00000159 //会话密钥有误

#define PHCDS_CONFIGFILE_INVALID				SDR_BSAE+0x00000160 //配置文件有误

#define PHCDS_INDATA_MAXDATA				SDR_BSAE+0x00000161 //参数超过最大值

#define PHCDS_SESSIONKEYHANDLE_MAX               SDR_BSAE+0x00000162 //会话密钥句柄超过最大值

#define PHCDS_NOSUPPORT_ALGID               SDR_BSAE+0x00000163 //不支持的算法

#define PHCDS_HASH_MAXCOUNT               SDR_BSAE+0x00000164 //最大的hash数

#define PHCDS_AGREEMENTHANDLE_MAX               SDR_BSAE+0x00000165 //协商参数句柄超过最大值

#define PHCDS_KEY_ERROR               SDR_BSAE+0x00000166 //密钥格式错误

#define PHCDS_KEYLENGTH_ERROR               SDR_BSAE+0x00000167 //密钥长度错误

#define PHCDS_LOADKPKEY_ERROR               SDR_BSAE+0x00000168 //装载密钥保护密钥出错

#define PHCDS_VERIFYAPPKEY_ERROR            SDR_BSAE+0x00000169 //密钥生成时验证密钥有误

#endif

