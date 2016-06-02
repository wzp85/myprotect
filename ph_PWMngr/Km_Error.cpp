
#include "Km_Error.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "windows.h"

const char ErrorString[][100]={"未知错误","不支持","通信错误","硬件错误","打开设备错误","打开会话句柄错误","权限不满足","密钥不存在",
			"不支持的算法","不支持的算法模式","公钥运算错误","私钥运算错误","签名错误","验证错误","对称运算错误","步骤错误","文件大小错误",
			"文件不存在","文件操作偏移量错误","密钥类型错误","密钥错误","无效的用户名","无效的授权码","不支持的协议版本","错误的命令字",
			"错误的数据包格式","参数错误","已存在同名文件","获取配置错误","功能函数号错误","参数类型错误","内存分配错误","参数为空",
			"找不到IP","主机名为空","获取主机名错误","网络异常，请检查您的网络连接","网络异常，请检查您的网络连接",
			/*"网络异常，请检查您的网络连接"*/"  超时自动注销，请重新登录","网络异常，请检查您的网络连接","网络异常，请检查您的网络连接",
			"发送包编码错误","发送包解码错误","发送包头编码错误","发送包头解码错误","接收包编码错误","接收包解码错误",
			"打开文件失败","获取文件状态失败","空文件","读文件错误","写文件错误","删除文件错误","打开目录失败","关闭文件失败",
			"文件类型错误","文件参数错误","创建文件失败","删除目录失败","没有权限","登录失败","内存分配错误","初始化口令错误",
			"数据库查询错误","数据库更新错误","数据库插入数据错误","数据库删除数据错误","证书验证失败，请确认您导入的是否是根证书！",
			"证书信息不匹配,请检查您输入的数据","用上级证书验证该证书失败","不可预期的错误","传入的参数无效","没有该密钥对应的证书文件！",
			"密钥与证书不匹配！","修改日志策略文件失败！","日志时间小于6月，不能删除","索引号已经使用"," 日志在规定保存日期内，没有权限删除"};

unsigned int retValue[]={SDR_UNKNOWERR,SDR_NOTSUPPORT,SDR_COMMFAIL,SDR_HARDFAIL,SDR_OPENDEVICE,SDR_OPENSESSION,SDR_PARDENY,SDR_KEYNOTEXIST,SDR_ALGNOTSUPPORT,
			SDR_ALGMODNOTSUPPORT,SDR_PKOPERR,SDR_SKOPERR,SDR_SIGNERR,SDR_VERIFYERR,SDR_SYMOPERR,SDR_STEPERR,SDR_FILESIZEERR,SDR_FILENOEXIST,SDR_FILEOFSERR,
			SDR_KEYTYPEERR,SDR_KEYERR,SDR_INVALID_USER,SDR_INVALID_AUTHENCODE,SDR_PROTOCOL_VER_ERR,SDR_INVALID_COMMAND,SDR_INVALID_PACKAGE,
			SDR_INVALID_PARAMETERS,SDR_FILE_ALREADY_EXIST,SDR_GETCONFIG,SDR_FUNCNUM,SDR_LBLTYPE,SDR_MEMALLOC,SDR_INPUTEMPTY,SDR_NOGOODIP,
			SDR_NULLHOSTNAME,SDR_GETHOSTNAME,SDR_SOCKETCREAT,SDR_SOCKETCONN,SDR_SOCKETSEND,SDR_SOCKETRECV,SDR_SOCKETBIND,SDR_ARGVENCODE,
			SDR_ARGVDECODE,SDR_HEADENCODE,SDR_HEADDECODE,SDR_RETVENCODE,SDR_RETVDECODE,SDR_OPENFILE,SDR_GETFILESTAT,SDR_NULLFILE,SDR_READFILE,
			SDR_WRITEFILE,SDR_DELETEFILE,SDR_OPENDIR,SDR_CLOSEFILE,SDR_FILETYPE,SDR_FILEPARA,SDR_FILECREATE,SDR_DIRDELTE,SDR_NOPERMISSION,
			SDR_ICLOGIN,SDR_MALLOCERROR,KM_WRONGNAMEPASSWD,KM_DATABASE_SELECT,KM_DATABASE_UPDATE,KM_DATABASE_INSERT,KM_DATABASE_DELETE,
			KM_NOT_ROOTCERTERR,KM_RTCERTINFOINCOM,SIG_CHECKCERTERROR,UNEXPECTED_EXCEPTION,PARAMETER_INVALID,SIG_NOCERT,SIG_KEYCERT_MISMATCH,
			SIG_MODIFYSLXFEFAIL,SIG_SYSLOGTIME,SIG_INDEXERROR,SIG_SYLOGDELETEERROR};

int retValueParse(int ret,char *errorString)
{
	if(NULL == errorString)
		memset(errorString,0x00,100);
	BOOL isFind = FALSE;
	char errcodebuff[32]={0x00};
	for(int i=0;i<78;i++)
	{
		if(ret == retValue[i])
		{
			sprintf(errcodebuff,"Err code = %x",retValue[i]);
			memcpy(errorString,ErrorString[i],strlen(ErrorString[i]));
			strcat(errorString,errcodebuff);
			isFind = TRUE;
			break;
		}
		//sprintf(errcodebuff,"Err code = %d",ret);
	}
	if(!isFind)
	{
		sprintf(errcodebuff,"Err code = 0x%08x",ret);
		memcpy(errorString,errcodebuff,strlen(errcodebuff));
	}
	return 0;
}