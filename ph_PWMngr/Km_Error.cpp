
#include "Km_Error.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "windows.h"

const char ErrorString[][100]={"δ֪����","��֧��","ͨ�Ŵ���","Ӳ������","���豸����","�򿪻Ự�������","Ȩ�޲�����","��Կ������",
			"��֧�ֵ��㷨","��֧�ֵ��㷨ģʽ","��Կ�������","˽Կ�������","ǩ������","��֤����","�Գ��������","�������","�ļ���С����",
			"�ļ�������","�ļ�����ƫ��������","��Կ���ʹ���","��Կ����","��Ч���û���","��Ч����Ȩ��","��֧�ֵ�Э��汾","�����������",
			"��������ݰ���ʽ","��������","�Ѵ���ͬ���ļ�","��ȡ���ô���","���ܺ����Ŵ���","�������ʹ���","�ڴ�������","����Ϊ��",
			"�Ҳ���IP","������Ϊ��","��ȡ����������","�����쳣������������������","�����쳣������������������",
			/*"�����쳣������������������"*/"  ��ʱ�Զ�ע���������µ�¼","�����쳣������������������","�����쳣������������������",
			"���Ͱ��������","���Ͱ��������","���Ͱ�ͷ�������","���Ͱ�ͷ�������","���հ��������","���հ��������",
			"���ļ�ʧ��","��ȡ�ļ�״̬ʧ��","���ļ�","���ļ�����","д�ļ�����","ɾ���ļ�����","��Ŀ¼ʧ��","�ر��ļ�ʧ��",
			"�ļ����ʹ���","�ļ���������","�����ļ�ʧ��","ɾ��Ŀ¼ʧ��","û��Ȩ��","��¼ʧ��","�ڴ�������","��ʼ���������",
			"���ݿ��ѯ����","���ݿ���´���","���ݿ�������ݴ���","���ݿ�ɾ�����ݴ���","֤����֤ʧ�ܣ���ȷ����������Ƿ��Ǹ�֤�飡",
			"֤����Ϣ��ƥ��,���������������","���ϼ�֤����֤��֤��ʧ��","����Ԥ�ڵĴ���","����Ĳ�����Ч","û�и���Կ��Ӧ��֤���ļ���",
			"��Կ��֤�鲻ƥ�䣡","�޸���־�����ļ�ʧ�ܣ�","��־ʱ��С��6�£�����ɾ��","�������Ѿ�ʹ��"," ��־�ڹ涨���������ڣ�û��Ȩ��ɾ��"};

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