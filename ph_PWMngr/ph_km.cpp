/*****************************************
*  psi2_clt.c
*  Copyright Wellhope 1999-2001
*  author: deng lin
*****************************************/

#include <stdlib.h>
#include <time.h>
#include "stdio.h"


#ifdef PHLINUX
    #include <sys/types.h>
	#include <pthread.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <sys/time.h>
	#include <signal.h>
	#include <unistd.h>
    #include <errno.h>
	#include <dlfcn.h>
#else
	#include <winsock2.h>
	#include <winuser.h>
	#include <windows.h>
#endif


#include "code.h"
#include "ph_km.h"
#include "misc.h"
#include "Km_Error.h"

#define PORT  6788

void swapRSAPubS2C( unsigned char * inData, int inDataLen,unsigned char * outData, int * outDataLen)
{
    int outLen=0;
    outLen = 4+4+256+4;
    memcpy(outDataLen,&outLen,sizeof(int));
    if(outData==NULL)
    {
		return;
    }
    memset(outData,0,outLen);
    RSAPUBLICKEYBLOB_km * pubKeyBlob = (RSAPUBLICKEYBLOB_km *)malloc(sizeof(RSAPUBLICKEYBLOB_km));
    memset(pubKeyBlob,0,sizeof(RSAPUBLICKEYBLOB_km));
    pubKeyBlob->AlgID=SGD_RSA;
    memcpy(&pubKeyBlob->BitLen,inData,4);
    memcpy(pubKeyBlob->Modulus,inData+4,256);
    memcpy(pubKeyBlob->PublicExponent,inData+4+256+256-4,4);
    memcpy(outData,pubKeyBlob,outLen);
    delete[] pubKeyBlob;

} 

void swapEccPubS2C( unsigned char * inData, int inDataLen,int algoType,unsigned char * outData, int * outDataLen)
{
    int outLen=0;
    outLen = sizeof(ECCPUBLICKEYBLOB_km);
    memcpy(outDataLen,&outLen,sizeof(int));
    if(outData==NULL)
    {
		return;
    }
    ECCPUBLICKEYBLOB_km * pubKeyBlob = (ECCPUBLICKEYBLOB_km *)malloc(sizeof(ECCPUBLICKEYBLOB_km));
    memset(pubKeyBlob,0,sizeof(ECCPUBLICKEYBLOB_km));
    ECCrefPublicKey * pubKey = (ECCrefPublicKey *)malloc(sizeof(ECCrefPublicKey));
    memcpy(pubKey,inData,inDataLen);
//    pubKeyBlob->AlgID = algoType;


    memcpy(&pubKeyBlob->BitLen,&pubKey->bits,4);
    memcpy(pubKeyBlob->XCoordinate+32,pubKey->x,32);
    memcpy(pubKeyBlob->YCoordinate+32,pubKey->y,32);
    memcpy(outData,pubKeyBlob,sizeof(ECCPUBLICKEYBLOB_km));
    delete[] pubKeyBlob;
    delete[] pubKey;


} 


void ViewMem(char * str,unsigned char * p, unsigned int len)
{
	unsigned int i=0;
	printf("\n------Info:%s------\n",str);
	for(;i<len;i++)
	{
		printf("0x%02x ",*(p+i));
	}
	printf("\n");
}

void printlogEx(char *szMsg)
{
#ifdef PHLOG
	
	FILE *fp = NULL;
	fp = fopen("/usr/local/phgcs/phgcs.log","a+");
	//fprintf(fp, "\nFile:%s*****\tLine:%d", __FILE__, __LINE__);
	fprintf(fp,"%s\n", szMsg);
	fclose(fp);
#endif	

}

int openDeviceSocket(char *hostIP,int *socketHandle)
{
	int ret = 0;

	int port = PORT;
	int i = 0;
	struct timeval tp;
	struct linger linger = { 0 };
    int on = 3;
	int nZero = 0;

	int nNetTimeout=60000;			//��λ������  ������60��

	ret = socket_conn(hostIP, port, socketHandle );
	if ( ret !=0 )
    {
		ret = socket_conn(hostIP, port, socketHandle );
    }
	if(ret == 0)
	{

		//modified by gxj at 2013.09.14   
#ifdef PHLINUX
		tp.tv_sec = TIMEOUT;		//��λ����
		tp.tv_usec = UTIMEOUT;		//��λ��΢��

		//SO_RCVTIMEO ���ճ�ʱ struct timeval
		//SO_SNDTIMEO ���ͳ�ʱ struct timeval

		setsockopt( *socketHandle, SOL_SOCKET, SO_RCVTIMEO, (const char * )&tp, sizeof(struct timeval) );
		setsockopt( *socketHandle, SOL_SOCKET, SO_SNDTIMEO, (const char * )&tp, sizeof(struct timeval) );



#else		
		//������win����struct timeval���ò�������
		//���÷��ͳ�ʱ
		setsockopt(*socketHandle, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout,sizeof(int));
		//���ý��ճ�ʱ
		setsockopt(*socketHandle, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout,sizeof(int));
#endif
		//modified end

		//SO_KEEPALIVE �������� int���Է������Ƿ���������⣨����������Զ������TCP���ӵ����롣 
		//���ø�ѡ������2Сʱ���ڴ��׽ӿڵ���һ����û�����ݽ�����TCP���Զ����Է� ��һ�����ִ��̽��ֽ�(keepalive probe)��
		//����һ���Է�������Ӧ��TCP�ֽ�.���ᵼ��������������� 
		//1���Է�����һ���������������� ACK��Ӧ��2Сʱ��TCP��������һ��̽��ֽڡ� 
		//2���Է��ѱ�������������������RST��Ӧ���׽ӿڵĴ����������ΪECONNRESET���׽� �ڱ����򱻹رա� 
		//3���Է����κ���Ӧ��Դ��berkeley��TCP��������8��̽��ֽڣ����75��һ������ͼ�õ� һ����Ӧ���ڷ�����һ��̽��ֽ�11����15���
		//��������Ӧ�ͷ������׽ӿڵĴ������ ����ΪETIMEOUT���׽ӿڱ����򱻹رա�
		//��ICMP�����ǡ�host unreachable (������ �ɴ�)����˵���Է�������û�б��������ǲ��ɴ��������´����������Ϊ EHOSTUNREACH��
		setsockopt( *socketHandle, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof(on) );	



		//SO_SNDBUF ���ͻ�������С,���һ�㷢�͵İ��ܴ��Ƶ������ôʹ�����ѡ��
		setsockopt (*socketHandle, SOL_SOCKET, SO_SNDBUF, ( char * )&nZero, sizeof( nZero ) );



		//1������ l_onoffΪ0�����ѡ��رգ�l_linger��ֵ�����ԣ������ں�ȱʡ�����close���û��������ظ������ߣ�������ܽ��ᴫ���κ�δ���͵����ݣ�
 
		//2������ l_onoffΪ��0��l_lingerΪ0�����׽ӿڹر�ʱTCPز�����ӣ�TCP�������������׽ӿڷ��ͻ������е��κ����ݲ�����һ��RST���Է���
		//������ͨ�����ķ�����ֹ���У��������TIME_WAIT״̬��
 
		//3������ l_onoff Ϊ��0��l_lingerΪ��0�����׽ӿڹر�ʱ�ں˽�����һ��ʱ�䣨��l_linger������������׽ӿڻ��������Բ������ݣ�
		//���̽�����˯��״̬��ֱ ����a���������ݷ������ұ��Է�ȷ�ϣ�֮�������������ֹ���У������ַ��ʼ���Ϊ0����b���ӳ�ʱ�䵽��
		//��������£�Ӧ�ó�����close�ķ���ֵ�Ƿǳ���Ҫ�ģ���������ݷ����겢��ȷ��ǰʱ�䵽��
		//close������EWOULDBLOCK�������׽ӿڷ��ͻ������е��κ����ݶ���ʧ��close�ĳɹ����ؽ��������Ƿ��͵����ݣ���FIN�����ɶԷ�TCPȷ�ϣ�
		//�������ܸ������ǶԷ�Ӧ�ý����Ƿ��Ѷ������ݡ�����׽ӿ���Ϊ�������ģ��������ȴ�close��ɡ�


		//��������������£�
		//1����������SO_LINGER���༴linger�ṹ�е�l_onoff����Ϊ���㣩�����������㳬ʱ�������closesocket()������������ִ�У������Ƿ����Ŷ�����δ���ͻ�δ��ȷ�ϡ����ֹرշ�ʽ��Ϊ��ǿ�ơ���ʧЧ���رգ���Ϊ�׽ӿڵ����·��������λ���Ҷ�ʧ��δ���͵����ݡ���Զ�˵�recv()���ý���WSAECONNRESET����
		//
		//2����������SO_LINGER��ȷ���˷���ĳ�ʱ�������closesocket()�����������̣�ֱ����ʣ���ݷ�����ϻ�ʱ�����ֹرճ�Ϊ�����š��򡰴��ݡ��رա���ע������׽ӿ���Ϊ��������SO_LINGER��Ϊ���㳬ʱ����closesocket()���ý���WSAEWOULDBLOCK���󷵻ء�
		//
		//3������һ�������׽ӿ���������SO_DONTLINGER��Ҳ����˵��linger�ṹ��l_onoff����Ϊ�㣩����closesocket()�����������ء����ǣ�������ܣ��Ŷӵ����ݽ����׽ӿڹر�ǰ���͡���ע�⣬�����������WINDOWS�׽ӿ�ʵ�ֽ���һ�β�ȷ����ʱ���ڱ����׽ӿ��Լ�������Դ����������������׽ӿڵ�Ӧ�ó�����˵��һ��Ӱ�졣


		linger.l_onoff = 1; 
		linger.l_linger = 0; 
		setsockopt( *socketHandle, SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));
	}

	return ret;
}

int Km_LoginIn (void ** phSessionHandle,char* uiIP,
	unsigned int uiAdminId,unsigned int uiHashAlgo,unsigned int uiSignAlgo,
	unsigned char * pucRandom,unsigned int uiRandomLength,
	unsigned char * pucRandomSign,unsigned int uiRandomSignLength,
	unsigned char * pucDevSign,unsigned int uiDevSignLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	ECCSignature eccst;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvLOGINValue argv;
	enum d_op inlist[6]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnLOGINValue retargv;
	enum d_op retlist[1]={D_INT};

	status = openDeviceSocket(uiIP,&socketHandle);
	if(status != 0)
    {
		return status;
	}
	*phSessionHandle=(void *)socketHandle;

	argv.uiAdminId=uiAdminId;
	argv.uiHashAlgo=uiHashAlgo;
	argv.uiSignAlgo=uiSignAlgo;
	argv.uiRandomLength=uiRandomLength;
	argv.pucRandom=pucRandom;
	


	if(SGD_SM2_1==uiSignAlgo)
	{		
		memset(&eccst,0x00,sizeof(ECCSignature));
		memcpy(eccst.r,pucRandomSign+32,32);
		memcpy(eccst.s,pucRandomSign+96,32);

		argv.uiRandomSignLength=sizeof(ECCSignature);
		argv.pucRandomSign=(unsigned char *)&eccst;	
	}
	else
	{
		argv.uiRandomSignLength=uiRandomSignLength;
		argv.pucRandomSign=pucRandomSign;	
	}
	
	argv.uiDevSignLength=uiDevSignLength;
	argv.pucDevSign=pucDevSign;

	pkt.func_num=KM_LOGININ;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,6);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	//������Ӳ��ɹ���رձ�������
	if(0 != status)
	{
		socket_close(socketHandle);	
	}
END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;







}

int Km_LoginOut (void *hSessionHandle)
{
	return socket_close((int)hSessionHandle);
}

int Km_CheckInitPasswd(void ** phSessionHandle,char* uiIP,
	unsigned char *ucName, unsigned int uiNameLength,
	unsigned char *ucPasswdHash, unsigned int uiPasswdHashLength,unsigned int *puiInitStatus)
{
	int status;
	int socketHandle;

	unsigned int date_len;
	
	char * recv_data;
	char * send_buf;

	packetInfo pkt;

	argvCIPValue argv;
	enum d_op inlist[2]={D_CHAR_LEN,D_CHAR_LEN};


	returnCIPValue retargv;
	enum d_op retlist[2]={D_INT,D_INT};


	status = openDeviceSocket(uiIP,&socketHandle);
	if(status != 0)
    {
		return status;
	}
	*phSessionHandle=(void *)socketHandle;

	pkt.func_num=KM_CHECKINITPASSWD;
	pkt.packetlen=uiPasswdHashLength+uiNameLength+2*sizeof(unsigned int);

	argv.ucName=ucName;
	argv.uiNameLength=uiNameLength;
	argv.ucPasswdHash=ucPasswdHash;
	argv.uiPasswdHashLength=uiPasswdHashLength;

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));


	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,2);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if (!data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	*puiInitStatus=retargv.sysStatus;


	//������Ӳ��ɹ���رձ�������
	if(0 != status)
	{
		socket_close(socketHandle);	
	}


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Km_ModifyInitPasswd (void ** phSessionHandle,char* uiIP,
	unsigned char *ucName,unsigned int uiNameLength,
	unsigned char*ucOldPasswordHash,unsigned int uiOldPasswordHashLength,
	unsigned char *ucNewPasswordHash,unsigned int uiNewPasswordHashLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;
	
	char *send_buf;
	char * recv_data;

	packetInfo pkt;

	argvMIPValue argv;
	enum d_op inlist[3]={D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnMIPValue retargv;
	enum d_op retlist[1]={D_INT};


	status = openDeviceSocket(uiIP,&socketHandle);
	if(status != 0)
    {
		return status;
	}

	pkt.func_num=KM_MODIFYINITPASSWD;
	pkt.packetlen=uiNameLength+uiOldPasswordHashLength+uiNewPasswordHashLength+3*sizeof(unsigned int);

	argv.ucName=ucName;
	argv.uiNameLength=uiNameLength;
	argv.ucOldPasswordHash=ucOldPasswordHash;
	argv.uiOldPasswordHashLength=uiOldPasswordHashLength;
	argv.ucNewPasswordHash=ucNewPasswordHash;
	argv.uiNewPasswordHashLength=uiNewPasswordHashLength;


	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	//������Ӳ��ɹ���رձ�������
	if(0 != status)
	{
		socket_close(socketHandle);	
	}

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

	


}



int Km_GenMainKey(void * hSessionHandle)
{
	int status;
	int socketHandle;

	unsigned int date_len;
	
	char *send_buf;
	char * recv_data;

	packetInfo pkt;

	argvGMKValue argv;
	enum d_op inlist[1]={D_INT};

	returnGMKValue retargv;
	enum d_op retlist[1]={D_INT};

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENMAINKEY;
	pkt.packetlen=sizeof(unsigned int);

	argv.uiAlgo=1;

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

	return 0;

}

int Km_GenKeyProKey(void * hSessionHandle,unsigned int iSymmAlgo)
{
	int status;
	int socketHandle;

	unsigned int date_len;
	
	
	char *send_buf;
	char * recv_data;

	packetInfo pkt;

	argvGKPKValue argv;
	enum d_op inlist[1]={D_INT};

	returnGKPKValue retargv;
	enum d_op retlist[1]={D_INT};


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENKEYPROKEY;
	pkt.packetlen=sizeof(unsigned int);

	//argv.uiAlgo=iSymmAlgo;
	argv.uiAlgo=0x00000001;

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

	return 0;

}

int Km_GenDevKey(void * hSessionHandle,unsigned char * pucDevName,unsigned int uiDevNameLength,
	unsigned int iASymmAlgo,unsigned int uiKeyLen,unsigned char * pucDevKeyPin,unsigned int ucDevKeyPinLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGDKValue argv;
	enum d_op inlist[4]={D_CHAR_LEN,D_INT,D_INT,D_CHAR_LEN};

	returnGDKValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiASymmAlgo=iASymmAlgo;
	argv.pucDevName=pucDevName;
	argv.uiDevNameLength=uiDevNameLength;
	argv.pucDevKeyPin=pucDevKeyPin;
	argv.uiDevKeyPinLength=ucDevKeyPinLength;
	argv.uiKeyLen=uiKeyLen;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENDEVKEY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Km_GenAdmin(void * hSessionHandle,ADMININFO* pAdminInfo,
	unsigned int uiAdminType,unsigned int uiAdminNum,
	unsigned char *pucPubKey,unsigned int uiPubKeyLen,
	unsigned char *pucSignValue,unsigned int *puiSignValueLen)
{
	int status;
	int socketHandle;

	/*----------------------------------------------------------------*/
	RSAPUBLICKEYBLOB_km rsapkb;
	RSArefPublicKey rsapkbst;

	ECCPUBLICKEYBLOB_km eccpkb; 
	ECCrefPublicKey eccpkst;
	/*----------------------------------------------------------------*/


	unsigned int date_len;

	char *send_buf;
	char * recv_data;

	packetInfo pkt;

	argvGAValue argv;
	enum d_op ga[8]={D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT};

	returnGAValue retargv;
	enum d_op retga[2]={D_INT,D_CHAR_LEN};


	argv.uiAdminId=pAdminInfo->iAdminId;
	argv.uiAdminNum=uiAdminNum;

	argv.pucName=pAdminInfo->ucName;
	argv.uiNameLen=pAdminInfo->uiNameLen;

	argv.pucTelephone=pAdminInfo->ucTelephone;
	argv.uiTelephoneLen=pAdminInfo->uiTelephoneLen;

	argv.uiPaperType=pAdminInfo->iPaperType;

	argv.pucPaperNum=pAdminInfo->ucPaperNum;
	argv.uiPaperNumLen=pAdminInfo->uiPaperNumLen;
	
	argv.uiAdminType=uiAdminType;

	
	if(sizeof(RSAPUBLICKEYBLOB_km) == uiPubKeyLen)		//�ж�ΪRSA��Կ
	{
		//-------------------------------------------------------
		//תΪRSArefPublicKey��ʽ��Կ
		memset(&rsapkb,0x00,sizeof(RSAPUBLICKEYBLOB_km));
		memset(&rsapkbst,0x00,sizeof(RSArefPublicKey));

		memcpy(&rsapkb,pucPubKey,uiPubKeyLen);
	
		memcpy(&rsapkbst,&rsapkb.BitLen,4+256);
		memcpy(rsapkbst.e+252,&rsapkb.PublicExponent,4);

		argv.pucPubKey=(unsigned char *)&rsapkbst;
		argv.uiPubKeyLen=sizeof(RSArefPublicKey);

		//-------------------------------------------------------
	}
	else if(sizeof(ECCPUBLICKEYBLOB_km) == uiPubKeyLen)	//�ж�ΪECC��Կ
	{

		//-------------------------------------------------------
		//תΪECCrefPublicKey��ʽ��Կ

		memset(&eccpkb,0x00,sizeof(ECCPUBLICKEYBLOB_km));
		memset(&eccpkst,0x00,sizeof(ECCrefPublicKey));

		memcpy(&eccpkb,pucPubKey,uiPubKeyLen);
	
		memcpy(&eccpkst.bits,&eccpkb.BitLen,sizeof(unsigned int));

		memcpy(eccpkst.x,eccpkb.XCoordinate+32,32);
		memcpy(eccpkst.y,eccpkb.YCoordinate+32,32);

		argv.pucPubKey=(unsigned char *)&eccpkst;
		argv.uiPubKeyLen=sizeof(ECCrefPublicKey);

	}
	else
		return 0xFFFFFFFF;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENADMIN;
	pkt.packetlen=sizeof(ADMININFO)+argv.uiPubKeyLen+1*sizeof(unsigned int);

	/*----------------------------------------------------------------*/
	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,ga,8);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retga,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}



	*puiSignValueLen=retargv.uiSignValueLen;
	if(NULL!=pucSignValue)
		memcpy(pucSignValue,retargv.pucSignValue,retargv.uiSignValueLen);
	status=retargv.status;


END2:
	free(recv_data);
END1:
	free(send_buf);

	return status;

}

int Km_GetDevKeyInfo (void * hSessionHandle,DEVKEYINFO *pDevKeyInfo)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	argvGDKIValue argv;
	enum d_op gdki[1]={D_INT};

	returnGDKIValue retargv;
	enum d_op retgdki[8]={D_INT,D_CHAR_LEN,D_INT,D_INT,D_INT,D_INT,D_INT,D_CHAR_LEN};

	argv.uiNum=1;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GETDEVKEYINFO;
	pkt.packetlen=data_proc_len((void *)&argv,gdki,1);

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,gdki,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retgdki,8))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	pDevKeyInfo->uiAlgo=retargv.uiAlgo;
	pDevKeyInfo->uiBakChooseKey=retargv.uiBakChooseKey;
	pDevKeyInfo->uiBakTotalKey=retargv.uiBakTotalKey;
	pDevKeyInfo->uiIfBak=retargv.uiIfBak;
	pDevKeyInfo->uiKeyLen=retargv.uiKeyLen;

	pDevKeyInfo->uiDevNameLen=retargv.uiDevNameLen;
	memcpy(pDevKeyInfo->ucDevName,retargv.ucDevName,retargv.uiDevNameLen);

	pDevKeyInfo->uiBakTimeLen=retargv.uiBakTimeLen;
	memcpy(pDevKeyInfo->ucBakTime,retargv.ucBakTime,retargv.uiBakTimeLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}



int Km_DevKeyBackup (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;//------���ݰ�
	/*----------------------------------------------------------------*/
	argvDKBValue argv;
	enum d_op dkb[2]={D_INT,D_CHAR_LEN};

	returnDKBValue retargv;
	enum d_op retdkb[2]={D_INT,D_CHAR_LEN};

	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	argv.pucKeyBackupKey=pucKeyBackupKey;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_DEVKEYBACKUP;//--------------------------����ǰ�ͷ,֪ͨ����˵����ĸ��ӿڣ���������
	pkt.packetlen=data_proc_len((void *)&argv,dkb,2);//------------pkt����

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));//-------������������ͨ�����ݰ�

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkb,2);//-------------�����װ
	if(status != TRUE)
    {
		goto END1;
	}
	//---------------------------------------------------------
	status=call_require(socketHandle,send_buf,&pkt);//---------------�������ݰ������񣺚i���ǣ��ȱ����ͷ��pkt�����Ͱ�ͷ֪ͨ�����
	if(status != 0)//------------Ϊ�����������ݷ������ڴ档Ȼ���ٷ��Ͱ��������ˣ����������misc.cpp�е�call_require()��
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);//-------���շ���˷��ذ���
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));//------------�������շ���˷������ݵ�ͨ�Ż���

	status=call_response_data(socketHandle,date_len,recv_data);//-------------���շ�������ݰ�
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkb,2))//-------------�����˱���
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	*puiKeyBakLength=retargv.uiKeyBakLength;
	if(NULL!=pucKeyBak)
		memcpy(pucKeyBak,retargv.pucKeyBak,retargv.uiKeyBakLength);

	status=retargv.status;
END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Km_DevKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucAdminPin, unsigned int uiAdminPinLength, 
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvDKRValue argv;
	enum d_op dkr[4]={D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN};

	returnDKRValue retargv;
	enum d_op retdkr[1]={D_INT};

	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBakLength=uiKeyBakLength;
	argv.pucKeyBak=pucKeyBak;
	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.pucAdminPin=pucAdminPin;
	argv.uiAdminPinLength=uiAdminPinLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_DEVKEYRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;





}



int Km_GenAppKey(void * hSessionHandle, unsigned int uikeyIndex, unsigned int uiAlgo, unsigned int uiKeyLength,
	unsigned char *pucKeyPasswd, unsigned int uiKeyPasswdLength,
	unsigned char *pucAppName, unsigned int uiAppNameLength, unsigned int uiKeyType)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGAKValue argv;
	enum d_op inlist[6]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT};

	returnGAKValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAlgo=uiAlgo;
	argv.uikeyIndex=uikeyIndex;
	argv.uiKeyPasswdLength=uiKeyPasswdLength;
	argv.pucKeyPasswd=pucKeyPasswd;
	argv.uiAppNameLength=uiAppNameLength;
	argv.pucAppName=pucAppName;
	argv.uiKeyType=uiKeyType;
	argv.uiKeyLength=uiKeyLength;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENAPPKEY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,6);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Km_GenAppKey_SIG(void * hSessionHandle, unsigned int uikeyIndex, unsigned int uiAlgo, unsigned int uiKeyLength,
	unsigned char *pucKeyPasswd, unsigned int uiKeyPasswdLength,unsigned char *pucAppName, unsigned int uiAppNameLength, 
	unsigned int uiKeyType,unsigned char *pucCityName,unsigned int uiCityNameLength,unsigned char *pucCNName,unsigned int uiCNNameLength,
	unsigned char *pucAreaName,unsigned int uiAreaNameLength,unsigned char *pucAtName,unsigned int uiAtNameLength,
	unsigned char *pucEmail,unsigned int uiEmailLength,unsigned char *pucOUValue,unsigned int uiOUValueLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGAKValueSIG argv;
	enum d_op inlist[12]={D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT};

	returnGAKValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAlgo=uiAlgo;
	argv.uikeyIndex=uikeyIndex;
	argv.uiKeyPasswdLength=uiKeyPasswdLength;
	argv.pucKeyPasswd=pucKeyPasswd;
	argv.uiAppNameLength=uiAppNameLength;
	argv.pucAppName=pucAppName;
	argv.uiKeyType=uiKeyType;
	argv.uiKeyLength=uiKeyLength;
	argv.uiCityNameLength=uiCityNameLength;
	argv.pucCityName=pucCityName;
	argv.uiCNNameLength=uiCNNameLength;
	argv.pucCNName=pucCNName;
	argv.uiAreaNameLength=uiAreaNameLength;
	argv.pucAreaName=pucAreaName;
	argv.uiAtNameLength=uiAtNameLength;
	argv.pucAtName=pucAtName;
	argv.uiEmailLength=uiEmailLength;
	argv.pucEmail=pucEmail;
	argv.pucOUValue = pucOUValue;
	argv.uiOUValueLength = uiOUValueLength;


	socketHandle=(int)hSessionHandle;

	puts("here----1");
	pkt.func_num=KM_GENAPPKEY_SIG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,12);
	puts("here----2");

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	puts("here----3");

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,12);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("here----4");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("here----5");

	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("here----6");

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Km_AppKeyModPasswd(void * hSessionHandle, unsigned int uikeyIndex, 
	unsigned char *pucOldKeyPasswd, unsigned int uiOldKeyPasswdLength, 
	unsigned char *pucNewKeyPasswd, unsigned int uiNewKeyPasswdLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKMPValue argv;
	enum d_op inlist[3]={D_INT,D_CHAR_LEN,D_CHAR_LEN};

	returnAKMPValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uikeyIndex=uikeyIndex;
	argv.pucNewKeyPasswd=pucNewKeyPasswd;
	argv.pucOldKeyPasswd=pucOldKeyPasswd;
	argv.uiNewKeyPasswdLength=uiNewKeyPasswdLength;
	argv.uiOldKeyPasswdLength=uiOldKeyPasswdLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPKEYMODPASSWD;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;



}

int Km_AppKeyBackup(void * hSessionHandle, unsigned int uiAlgo,
	unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength,
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKBValue argv;
	enum d_op inlist[3]={D_INT,D_INT_LEN,D_CHAR_LEN};

	returnAKBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiKeyIndexNum=uiKeyIndexNum;
	argv.puiKeyIndex=puiKeyIndex;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	//argv.uiAlgo=uiAlgo;

	argv.uiAlgo=0x00000001;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPKEYBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	*puiKeyBakLength=retargv.uiKeyBakLength;
	if(NULL!=pucKeyBak)
		memcpy(pucKeyBak,retargv.pucKeyBak,retargv.uiKeyBakLength);

	status=retargv.status;
	


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	
	
}

int Km_AppKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucAdminPin, unsigned int uiAdminPinLength, 
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength)
{
	
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvDKRValue argv;
	enum d_op dkr[4]={D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN};

	returnDKRValue retargv;
	enum d_op retdkr[1]={D_INT};

	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBakLength=uiKeyBakLength;
	argv.pucKeyBak=pucKeyBak;
	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.pucAdminPin=pucAdminPin;
	argv.uiAdminPinLength=uiAdminPinLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPKEYRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;





}

int Km_AppKeyDestroy(void * hSessionHandle,unsigned int uiTypeNum,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKDValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnAKDValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiKeyIndexNum=uiKeyIndexNum;
	argv.puiKeyIndex=puiKeyIndex;
	//argv.uiIsSIG=uiTypeNum;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPKEYDESTROY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,2);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,2);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Km_AppKeyGetList(void * hSessionHandle,unsigned int uiIsSig, unsigned char * puiKeyList,unsigned int *puiKeyListLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKGValue argv;
	enum d_op inlist[2]={D_INT,D_INT};

	returnAKGValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;
	argv.uiIsSIG=uiIsSig;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPKEYGETLIST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,2);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,2);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiKeyListLen=retargv.uiKeyListLen;
	if(NULL!=puiKeyList)
		memcpy(puiKeyList,retargv.puiKeyList,retargv.uiKeyListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}



int Km_GenKeyEncKey(void * hSessionHandle, unsigned int uikeyLabel, unsigned int uiAlgo, 
	unsigned char *pucEncKeyName, unsigned int uiEncKeyNameLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGKEKValue argv;
	enum d_op inlist[3]={D_INT,D_INT,D_INT_LEN};

	returnGKEKValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uikeyLabel=uikeyLabel;
	argv.uiAlgo=uiAlgo;
	argv.uiEncKeyNameLength=uiEncKeyNameLength;
	argv.pucEncKeyName=pucEncKeyName;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GENKEYENCKEY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;



}

int Km_KeyEncKeyBackup(void * hSessionHandle, unsigned int uiAlgo,
	unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength,
	unsigned char *pucKeyBak, unsigned int* puiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKBValue argv;
	enum d_op inlist[3]={D_INT,D_INT_LEN,D_CHAR_LEN};

	returnAKBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.uiKeyIndexNum=uiKeyIndexNum;
	argv.puiKeyIndex=puiKeyIndex;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_KEYENCKEYBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	*puiKeyBakLength=retargv.uiKeyBakLength;
	if(NULL!=pucKeyBak)
		memcpy(pucKeyBak,retargv.pucKeyBak,retargv.uiKeyBakLength);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	
	
}

int Km_KeyEncRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvKERValue argv;
	enum d_op inlist[3]={D_CHAR_LEN,D_INT,D_CHAR_LEN};

	returnKERValue retargv;
	enum d_op retlist[1]={D_INT};

	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;

	argv.pucKeyBak=pucKeyBak;
	argv.uiKeyBakLength=uiKeyBakLength;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_KEYENCRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;





}

int Km_KeyEncDestroy(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKDValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnAKDValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiKeyIndexNum=uiKeyIndexNum;
	argv.puiKeyIndex=puiKeyIndex;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_KEYENCDESTROY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Km_KeyEncKeyGetList(void * hSessionHandle, unsigned char * puiKeyList,unsigned int *puiKeyListLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvAKGValue argv;
	enum d_op inlist[1]={D_INT};

	returnAKGValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_KEYENCKEYGETLIST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiKeyListLen=retargv.uiKeyListLen;
	if(NULL!=puiKeyList)
		memcpy(puiKeyList,retargv.puiKeyList,retargv.uiKeyListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Km_DelAdmin(void *hSessionHandle,unsigned int uiAdminId)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvDAValue argv;
	enum d_op inlist[1]={D_INT};

	returnDAValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAdminId=uiAdminId;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_DELADMIN;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;


}

int Km_GetAdminList(void * hSessionHandle, unsigned char * puiAdminList,unsigned int *puiAdminListLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGALValue argv;
	enum d_op inlist[1]={D_INT};

	returnGALValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GETADMINLIST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiAdminListLen=retargv.uiAdminListLen;
	if(NULL!=puiAdminList)
		memcpy(puiAdminList,retargv.puiAdminList,retargv.uiAdminListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Km_AdminBackup(void * hSessionHandle, unsigned int uiAdminIndexNum,unsigned int *puiAdminIndex,
	unsigned char *pucAdminBak, unsigned int* puiAdminBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvABValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnABValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};


	argv.uiAdminIndexNum=uiAdminIndexNum;
	argv.puiAdminIndex=puiAdminIndex;


	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_ADMINBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	*puiAdminBakLength=retargv.uiAdminBakLength;
	if(NULL!=pucAdminBak)
		memcpy(pucAdminBak,retargv.pucAdminBak,retargv.uiAdminBakLength);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Km_AdminRecovery(void *hSessionHandle,unsigned char *pucAdminBackup, unsigned int uiAdminBackupLength )
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvARValue argv;
	enum d_op inlist[1]={D_CHAR_LEN};

	returnARValue retargv;
	enum d_op retlist[1]={D_INT};


	argv.pucAdminBackup=pucAdminBackup;
	argv.uiAdminBackupLength=uiAdminBackupLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_ADMINRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}



int Km_NetRestart(void * hSessionHandle,unsigned int eth)
{
	int status;
	int socketHandle;

	//unsigned int date_len;

	char * send_buf;
	//char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvNETRSValue argv;
	enum d_op inlist[1]={D_INT};

	//returnNETRSValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAlgo=eth;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_NETRESTART;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

/*
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);*/
END1:
	free(send_buf);
	return status;


}

int Km_ManagerNetModify(void * hSessionHandle,unsigned char * pucNet,unsigned int uiNetLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvMNMValue argv;
	enum d_op inlist[1]={D_CHAR_LEN};

	returnMNMValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiNetLen=uiNetLen;
	argv.pucNet=pucNet;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_MANAGERNETMODIFY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;




}

int Km_AppNetModify(void * hSessionHandle,unsigned char * pucNet,unsigned int uiNetLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvMNMValue argv;
	enum d_op inlist[1]={D_CHAR_LEN};

	returnMNMValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiNetLen=uiNetLen;
	argv.pucNet=pucNet;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_APPNETMODIFY;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;




}

int Km_GetNetConfig(void * hSessionHandle,unsigned int eth, unsigned char * pucNet,unsigned int *puiNetLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGNCValue argv;
	enum d_op inlist[1]={D_INT};

	returnGNCValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.eth=eth;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GETNETCONFIG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiNetLen=retargv.uiNetLen;
	if(NULL!=pucNet)
		memcpy(pucNet,retargv.pucNet,retargv.uiNetLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;




}

int Km_GetDeviceInfo(void * hSessionHandle,DEVICEINFO* pDevInfo)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGDIValue argv;
	enum d_op inlist[1]={D_INT};

	returnGDIValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_GETDEVINFO;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	memcpy(pDevInfo,retargv.pucDevInfo,retargv.uiDevInfoLen);
	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;




}

int Km_SymmCrypt(void * hSessionHandle,unsigned int oper,unsigned int uiAlgo,unsigned char * pucSymmKey,unsigned int uiSymmKeyLength,
	unsigned char *pucText,unsigned int uiTextLength,unsigned char *pucResault,unsigned int* puiResaultLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCRYPTValue argv;
	enum d_op inlist[4]={D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN};

	returnCRYPTValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=0x00000001;
	argv.uiOper=oper;

	argv.pucSymmKey=pucSymmKey;
	argv.uiSymmKeyLength=uiSymmKeyLength;
	argv.pucText=pucText;
	argv.uiTextLength=uiTextLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=KM_SYMMCRYPT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	*puiResaultLength=retargv.uiResaultLength;
	if(NULL!=retargv.pucResault)
		memcpy(pucResault,retargv.pucResault,retargv.uiResaultLength);

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;




}


int Km_Encode( char *src,long int src_len, char *dst)
{
	return encode(src,src_len,dst);
}

int Km_Decode(char *src, long int src_len, char *dst)
{
	return decode(src,src_len,dst);

}

int Km_Random(unsigned char * random,int len)
{
	int r=0;
	int i=0;

	srand((unsigned)time(NULL));

	for(i=0;i<len;i++) 
	{	
		for(;;)
		{
			r=((2 * rand() +256)% 256 ); 
			if(r!=0)
				break;
		}
		memcpy(random+i*1,&r,1);
	}

	return 0;

}




//ͬʱ������ݿ����ݺ��ļ����� 
int Sig_RootCertAdd(void * hSessionHandle,unsigned char *pucCertName,unsigned int uiCertNameLength,
	unsigned int uiCertIndex,unsigned int uiAlgo,unsigned char *pucAtName,unsigned int uiKeyLength,
	unsigned int uiAtNameLength,unsigned char *pucHost,unsigned int uiHostLength,unsigned char *pucPhone,
	unsigned int uiPhoneLength,unsigned char *pucRtCert,unsigned int uiRtCertLength,
	unsigned char 	*pucCertSN, unsigned int    uiCertSNLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRCAValue argv;
	enum d_op inlist[9]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnRCAValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAlgo=uiAlgo;
	argv.uiKeyLength = uiKeyLength;
	argv.pucCertName = pucCertName;
	argv.uiCertNameLength = uiCertNameLength;
	//argv.putCertIndex= pucCertIndex;
	argv.uiCertIndex = uiCertIndex;//changed by syc
	argv.pucAtName = pucAtName;
	argv.uiAtNameLength = uiAtNameLength;
	argv.pucHost = pucHost;
	argv.uiHostLength = uiHostLength;
	argv.pucPhone = pucPhone;
	argv.uiPhoneLength = uiPhoneLength;
	argv.pucRtCert = pucRtCert;
	argv.uiRtCertLength = uiRtCertLength;
	argv.uiCertSNLength = uiCertSNLength;
	argv.pucCertSN = pucCertSN;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_ROOTCERTADD;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,9);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	puts("sig here ------------- 1");

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,9);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("sig here ------------- 2");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("sig here ------------- 3");

	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}
	puts("sig here ------------- 4");

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("sig here ------------- 5");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{
		puts("sig here ------------- 6");
		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

//���ݿ���ļ���ɾ��
int Sig_RootCertDel(void * hSessionHandle,unsigned int uiCertIndexNum,unsigned int *puiCertIndex)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRCDValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnRCDValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiCertIndexNum = uiCertIndexNum;
	argv.certIndex = puiCertIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_ROOTCERTDEL;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	puts("sig here ------------- 1");

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("sig here ------------- 2");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("sig here ------------- 3");

	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}
	puts("sig here ------------- 4");

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("sig here ------------- 5");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{
		puts("sig here ------------- 6");
		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

//ֻ�������ݿ⣬�����ļ�
int Sig_RootCertUpdate(void *hSessionHandle,unsigned int uiAlgo,unsigned int uiCertIndex,unsigned char *pucCertName,
	unsigned int uiCertNameLength,unsigned char *pucAtName,unsigned int uiAtNameLength,unsigned char *pucHost,unsigned int uiHostLength,
	unsigned char *pucPhone,unsigned int uiPhoneLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRCUValue argv;
	enum d_op inlist[6]={D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnRCUValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiAlgo = uiAlgo;
	argv.uiCertIndex = uiCertIndex;
	argv.uiCertNameLength = uiCertNameLength;
	argv.pucCertName = pucCertName;
	argv.uiAtNameLength = uiAtNameLength;
	argv.pucAtName = pucAtName;
	argv.uiHostLength = uiHostLength;
	argv.pucHost = pucHost;
	argv.uiPhoneLength = uiPhoneLength;
	argv.pucPhone = pucPhone;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_ROOTCERTUPDATE;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	puts("sig here ------------- 1");

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,6);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("sig here ------------- 2");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("sig here ------------- 3");

	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}
	puts("sig here ------------- 4");

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("sig here ------------- 5");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{
		puts("sig here ------------- 6");
		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_RootCertGetList(void * hSessionHandle,unsigned char * puiKeyList,unsigned int *puiKeyListLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRCGValue argv;
	enum d_op inlist[1]={D_INT};

	returnRCGValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_ROOTCERTGETLIST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("Sig ---------------   1");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   2");
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   3");
	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("Sig ---------------   4");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiKeyListLen=retargv.uiCertListLen;
	if(NULL!=puiKeyList)
		memcpy(puiKeyList,retargv.puiCertList,retargv.uiCertListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_GenCertRequest(void * hSessionHandle,unsigned int uiSymmAlgo,unsigned int uiHashAlgo,unsigned int uiKeyAlgo,
						unsigned int uiIndexLength,unsigned char *pucIndex,unsigned int uiPasswordLength,unsigned char *pucPassword,
						unsigned int uiRequestLength,unsigned char *pucRequest,unsigned char *pucB64Req,unsigned char *pucReq)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSGCRValue argv;
	enum d_op inlist[6]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnSGCRValue retargv;
	enum d_op retlist[3]={D_INT,D_CHAR_LEN,D_CHAR_LEN};

	argv.uiSymmAlgo = uiSymmAlgo;
	argv.uiHashAlgo = uiHashAlgo;
	argv.uiKeyAlgo = uiKeyAlgo;
	argv.uiIndexLength = uiIndexLength;
	argv.pucIndex = pucIndex;
	argv.uiPasswordLength = uiPasswordLength;
	argv.pucPassword = pucPassword;
	argv.uiRequestLength = uiRequestLength;
	argv.pucRequest = pucRequest;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GENCERTREQUEST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,6);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("Sig ---------------   1");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   2");
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   3");
	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("Sig ---------------   4");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	if(NULL != pucB64Req)
		memcpy(pucB64Req,retargv.pucB64Req,retargv.uiB64ReqLength);
	if(NULL != pucReq)
		memcpy(pucReq,retargv.pucReq,retargv.uiReqLength);
	//*puiKeyListLen=retargv.uiCertListLen;
	//if(NULL!=puiKeyList)
	//	memcpy(puiKeyList,retargv.puiCertList,retargv.uiCertListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}
int Sig_GenCertOnline(void * hSessionHandle,unsigned int uiSymmAlgo,unsigned int uiHashAlgo,unsigned int uiKeyAlgo,
						unsigned int uiIndexLength,unsigned char *pucIndex,unsigned int uiPasswordLength,unsigned char *pucPassword,
						unsigned int uiIPAddrLength,unsigned char *pucIPaddr,unsigned int uiPortLength,unsigned char *pucPort,
						unsigned int uiRequestLength,unsigned char *pucRequest)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSGCOValue argv;
	enum d_op inlist[8]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnSGCOValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiSymmAlgo = uiSymmAlgo;
	argv.uiHashAlgo = uiHashAlgo;
	argv.uiKeyAlgo = uiKeyAlgo;
	argv.uiIndexLength = uiIndexLength;
	argv.pucIndex = pucIndex;
	argv.uiPasswordLength = uiPasswordLength;
	argv.pucPassword = pucPassword;
	argv.uiRequestLength = uiRequestLength;
	argv.pucRequest = pucRequest;
	argv.uiIPAddrLength = uiIPAddrLength;
	argv.pucIPAddr=pucIPaddr;

	argv.uiPortLength = uiPortLength;
	argv.pucPort=pucPort;
	
	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GENCERTREQUEST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,8);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,8);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("Sig ---------------   1");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   2");
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   3");
	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("Sig ---------------   4");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	//*puiKeyListLen=retargv.uiCertListLen;
	//if(NULL!=puiKeyList)
	//	memcpy(puiKeyList,retargv.puiCertList,retargv.uiCertListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_ImportEncCert(void * hSessionHandle,unsigned int uiKeyAlgo,
	unsigned int uiIndexLength,unsigned char *pucIndex,
	unsigned int uiPasswordLength,unsigned char *pucPassword,
	unsigned int uiEncCertLength,unsigned char *pucEncCert,
	unsigned int uiSigCertLength,unsigned char *pucSigCert,
	unsigned int uiEncPubKeyLength,unsigned char *pucEncPubKey, 
	unsigned int uiEncPrivKeyLength,unsigned char *pucEncPrivKey, 
	int encType
	)
{

    int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSISCValue argv;
	enum d_op inlist[8]={D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_INT};





	returnSISCValue retargv;
	enum d_op retlist[1]={D_INT};



	argv.uiKeyAlgo=uiKeyAlgo;
	argv.uiIndexLength=uiIndexLength;
	argv.pucIndex=pucIndex;
	argv.uiPasswordLength=uiPasswordLength;
	argv.pucPassword=pucPassword;
    argv.encType=encType;
	argv.uiEncCertLength=uiEncCertLength;
	argv.pucEncCert=pucEncCert;

	argv.uiSigCertLength=uiSigCertLength;
	argv.pucSigCert  =pucSigCert;
	argv.uiEncPubKeyLength=uiEncPubKeyLength;
	argv.pucEncPubKey=pucEncPubKey;
	argv.uiEncPrivKeyLength=uiEncPrivKeyLength;
	argv.pucEncPrivKey=pucEncPrivKey;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_IMPORTSIGCERT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,8);
	
	
	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,8);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("Sig ---------------   1");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   2");
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   3");
	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("Sig ---------------   4");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	//*puiKeyListLen=retargv.uiCertListLen;
	//if(NULL!=puiKeyList)
	//	memcpy(puiKeyList,retargv.puiCertList,retargv.uiCertListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}
int Sig_GetItemAppKeyInfo(void * hSessionHandle,unsigned int uiKeyIndex,unsigned char *pucItem,unsigned int *uiItemLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGIAKIValue argv;
	enum d_op inlist[1]={D_INT};

	returnGIAKIValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

//	argv.uiAlgo=1;
	argv.uiKeyIndex=uiKeyIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETITEMAPPKEYINFO;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("Sig ---------------   1");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   2");
	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	puts("Sig ---------------   3");
	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("Sig ---------------   4");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiItemLength=retargv.keyInfoItemLength;
	if(NULL!=pucItem)
		memcpy(pucItem,retargv.pucKeyInfoItem,retargv.keyInfoItemLength);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Sig_CACertAdd(void * hSessionHandle,unsigned int uiRtCertIndex,unsigned int uiRtCertType,unsigned int uiCACertIndex,unsigned int uiAlgo,unsigned int uiKeyLength,unsigned int uiCertIndexLength,
				unsigned char *putCertIndex,unsigned int uiCertNameLength,unsigned char	*pucCertName,unsigned int uiAtNameLength,unsigned char *pucAtName,
				unsigned int uiHostLength,unsigned char *pucHost,unsigned int uiPhoneLength,unsigned char *pucPhone,unsigned int uiCACertLength,
				unsigned char *pucCACert,unsigned int uiTrustChainLength,unsigned char *pucTrustChain,VerifyPriorityStrategy vs)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCCAPriorityValue argv;
	enum d_op inlist[28]={D_INT,D_INT,D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,
		D_CHAR_LEN,D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_INT,D_CHAR_LEN,D_INT,D_INT,D_INT,D_CHAR_LEN,
		D_CHAR_LEN,D_CHAR_LEN,D_INT,D_INT,D_CHAR_LEN};

	returnCCAValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiRtCertIndex = uiRtCertIndex;
	argv.uiRtCertType = uiRtCertType;

	argv.uiCACertIndex = uiCACertIndex;
	argv.uiAlgo=uiAlgo;
	argv.uiKeyLength = uiKeyLength;
	argv.putCertIndex = putCertIndex;
	argv.uiCertIndexLength = uiCertIndexLength;
	argv.pucCertName = pucCertName;
	argv.uiCertNameLength = uiCertNameLength;
	argv.pucAtName = pucAtName;
	argv.uiAtNameLength = uiAtNameLength;
	argv.pucHost = pucHost;
	argv.uiHostLength = uiHostLength;
	argv.pucPhone = pucPhone;
	argv.uiPhoneLength = uiPhoneLength;
	argv.pucCACert = pucCACert;
	argv.uiCACertLength = uiCACertLength;
	argv.pucTrustChain = pucTrustChain;
	argv.uiTrustChainLength = uiTrustChainLength;

	argv.option = vs.option;//�����ʶ����ʾʹ�õ���������֤����
	argv.uiCRLhandLen = vs.CRLhandLen;
	argv.pucCRLhand = vs.CRLhand;
	argv.uiautoCRLipLen = vs.autoCRLipLen;
	argv.pucautoCRLip= vs.autoCRLip;
	argv.uiautoCRLportLen = vs.autoCRLportLen;
	argv.pucautoCRLport = vs.autoCRLport;
	argv.uiautoCRLurlLen = vs.autoCRLurlLen;
	argv.pucautoCRLurl = vs.autoCRLurl;
	argv.uiautoCRLtime = vs.autoCRLtime;
	argv.uiautoFromHTTPurlLen = vs.autoFromHTTPurlLen;
	argv.pucautoFromHTTPurl = vs.autoFromHTTPurl;
	argv.uiautoFromHTTPtime = vs.autoFromHTTPtime;
	argv.uiautoCRLtype = vs.autoCRLtype;
	argv. uiCRLverifyTime=vs. CRLverifyTime;
	argv.uiOCSPipLen = vs.OCSPipLen;
	argv.pucOCSPip = vs.OCSPip;
	argv.uiOCSPprotLen = vs.OCSPprotLen;
	argv.pucOCSPport = vs.OCSPport;
	argv.uiOCSPurlLen = vs.OCSPurlLen;
	argv.pucOCSPurl = vs.OCSPurl;
	argv.uiOCSPcertstand = vs.OCSPcertstand;
	argv. uiOCSPtalktype=vs.OCSPtalktype;
	argv.uiOCSPverifyLen = vs.OCSPverifyLen;
	argv.pucOCSPverify = vs.OCSPverify;

	


	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTADD;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,28);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	
/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,28);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_CACertGetList(void * hSessionHandle,unsigned char * puiKeyList,unsigned int *puiKeyListLen)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCCGValue argv;
	enum d_op inlist[1]={D_INT};

	returnCCGValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiAlgo=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTGETLIST;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiKeyListLen=retargv.uiCertListLen;
	if(NULL!=puiKeyList)
		memcpy(puiKeyList,retargv.puiCertList,retargv.uiCertListLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_CACertDel(void * hSessionHandle,unsigned int uiCertIndexNum,unsigned int *puiCertIndex)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCCDValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnCCDValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiCertIndexNum = uiCertIndexNum;
	argv.certIndex = puiCertIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTDEL;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	puts("sig here ------------- 1");

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}
	puts("sig here ------------- 2");
	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}

	puts("sig here ------------- 3");

	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}
	puts("sig here ------------- 4");

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}
	puts("sig here ------------- 5");
/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{
		puts("sig here ------------- 6");
		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_GetCACertVS(void * hSessionHandle,unsigned int uiCertIndex,unsigned char *CACertSerialNum,unsigned int *uiRtCertType,unsigned int *uiRtCertIndex,VerifyPriorityStrategy *vs)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/

	argvGCAVSValue argv;
	enum d_op inlist[1]={D_INT};
	//------------------------------------------��ȡ����˷���ֵ


	returnGCAVSValue retargv;
	enum d_op retlist[20]={D_INT,D_INT,D_INT,D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_INT,D_CHAR_LEN,D_INT,D_INT,D_INT,
		D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_INT,D_INT,D_CHAR_LEN};

	argv.uiCertIndex = uiCertIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETCACERTVS;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));


/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,20))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiRtCertType = retargv.uiRtCertType;
	*uiRtCertIndex = retargv.uiRtCertIndex;
	if(CACertSerialNum != NULL)
		memcpy(CACertSerialNum,retargv.pucCACertIndex,retargv.uiCACertIndexLength);

	vs->option = retargv.option;
	vs->CRLhand = retargv.pucCRLhand;
	vs->CRLhandLen = retargv.uiCRLhandLen;
	vs->autoCRLip = retargv.pucautoCRLip;
	vs->autoCRLipLen = retargv.uiautoCRLipLen;

	vs->autoCRLport = retargv.pucautoCRLport;
	vs->autoCRLportLen = retargv.uiautoCRLportLen;
	vs->autoCRLurl = retargv.pucautoCRLurl;
	vs->autoCRLurlLen = retargv.uiautoCRLurlLen;
	vs->autoCRLtime = retargv.uiautoCRLtime;
	vs->autoFromHTTPurl = retargv.pucautoFromHTTPurl;
	vs->autoFromHTTPurlLen = retargv.uiautoFromHTTPurlLen;
	vs->autoFromHTTPtime = retargv.uiautoFromHTTPtime;
	vs->autoCRLtype = retargv.uiautoCRLtype;

	vs->CRLverifyTime = retargv.uiCRLverifyTime;

	vs->OCSPip = retargv.pucOCSPip;
	vs->OCSPipLen = retargv.uiOCSPipLen;
	vs->OCSPport = retargv.pucOCSPport;
	vs->OCSPurlLen = retargv.uiOCSPurlLen;

	vs->OCSPtalktype = retargv.uiOCSPtalktype;
	vs->OCSPcertstand = retargv.uiOCSPcertstand;
	vs->OCSPverify = retargv.pucOCSPverify;
	vs->OCSPverifyLen = retargv.uiOCSPverifyLen;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_UserCertImport(void * hSessionHandle,unsigned int uiCACertIndex,unsigned int uiAlgid,unsigned int uiKeyLength,unsigned int uiKeyType,unsigned int uiKeyIndex,
					unsigned int uiCertIndexLength,unsigned char *putCertIndex,unsigned int uiCertNameLength,unsigned char	*pucCertName,unsigned int uiAtNameLength,
					unsigned char *pucAtName,unsigned int uiHostLength,unsigned char *pucHost,unsigned int uiPhoneLength,unsigned char *pucPhone,unsigned int uiUsrEncCertLength,
					unsigned char *pucUsrEncCert,unsigned int uiUsrSigCertLength,unsigned char *pucUsrSigCert,unsigned int uiPrivateKeyAccessRightCodeLength,
					unsigned char *pucPrivateKeyAccessRightCode)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvUCIPValue argv;
	enum d_op inlist[13]={D_INT,D_INT,D_INT,D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnUCIPValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.uiCACertIndex = uiCACertIndex;
	argv.uiAlgo=uiAlgid;
	argv.uiKeyLength = uiKeyLength;
	argv.uiKeyIndex=uiKeyIndex;
	argv.uiKeyType=uiKeyType;

	argv.putCertIndex = putCertIndex;
	argv.uiCertIndexLength=uiCertIndexLength;
	argv.pucCertName = pucCertName;
	argv.uiCertNameLength = uiCertNameLength;
	argv.pucAtName = pucAtName;
	argv.uiAtNameLength = uiAtNameLength;
	argv.pucHost = pucHost;
	argv.uiHostLength = uiHostLength;
	argv.pucPhone = pucPhone;
	argv.uiPhoneLength = uiPhoneLength;

	argv.pucUsrSigCert=pucUsrSigCert;
	argv.uiUsrSigCertLength=uiUsrSigCertLength;
	argv.pucUsrEncCert=pucUsrEncCert;
	argv.uiUsrEncCertLength=uiUsrEncCertLength;

	argv.pucPrivateKeyAccessRightCode=pucPrivateKeyAccessRightCode;
	argv.uiPrivateKeyAccessRightCodeLength=uiPrivateKeyAccessRightCodeLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_USRCERTIMPORT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,13);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));


/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,13);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_AppKeyBackup(void * hSessionHandle, unsigned int uiAlgo,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucKeyBackupKey,
					unsigned int uiKeyBackupKeyLength,unsigned char *pucKeyBak, unsigned int* puiKeyBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSAKBValue argv;
	enum d_op inlist[3]={D_INT,D_INT_LEN,D_CHAR_LEN};

	returnSAKBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiKeyIndexNum=uiKeyIndexNum;
	argv.puiKeyIndex=puiKeyIndex;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	//argv.uiAlgo=uiAlgo;

	argv.uiAlgo=0x00000001;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_APPKEYBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	*puiKeyBakLength=retargv.uiKeyBakLength;
	if(NULL!=pucKeyBak)
		memcpy(pucKeyBak,retargv.pucKeyBak,retargv.uiKeyBakLength);

	status=retargv.status;
	


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	
	
}


int Sig_AppKeyRecovery (void *hSessionHandle,unsigned int uiAlgo,
	unsigned char *pucAdminPin, unsigned int uiAdminPinLength, 
	unsigned char *pucKeyBackupKey, unsigned int uiKeyBackupKeyLength, 
	unsigned char *pucKeyBak, unsigned int uiKeyBakLength)
{
	
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvDKRValue argv;
	enum d_op dkr[4]={D_CHAR_LEN,D_INT,D_CHAR_LEN,D_CHAR_LEN};

	returnDKRValue retargv;
	enum d_op retdkr[1]={D_INT};

	argv.uiKeyBackupKeyLength=uiKeyBackupKeyLength;
	argv.pucKeyBackupKey=pucKeyBackupKey;
	argv.uiKeyBakLength=uiKeyBakLength;
	argv.pucKeyBak=pucKeyBak;
	//argv.uiAlgo=uiAlgo;
	argv.uiAlgo=0x00000001;

	argv.pucAdminPin=pucAdminPin;
	argv.uiAdminPinLength=uiAdminPinLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_APPKEYRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;





}


int Sig_UserCertExport(void * hSessionHandle,unsigned int index,unsigned char *pucSigCert,unsigned int *uiSigCertLength,
						unsigned char *pucEncCert,unsigned int *uiEncCertLegnth)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvUCEPValue argv;
	enum d_op inlist[1]={D_INT};

	returnUCEPValue retargv;
	enum d_op retlist[3]={D_INT,D_CHAR_LEN,D_CHAR_LEN};

	argv.uiCertIndex=index;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_USRCERTEXPORT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiSigCertLength=retargv.uiSigCertLength;
	if(NULL!=pucSigCert)
		memcpy(pucSigCert,retargv.pucSigCert,retargv.uiSigCertLength);
	*uiEncCertLegnth=retargv.uiEncCertLength;
	if(NULL!=pucEncCert)
		memcpy(pucEncCert,retargv.pucEncCert,retargv.uiEncCertLength);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}



int Sig_GetLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength,
	unsigned int *uiPubKeyLength,unsigned char *pucPubKey)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGLValue argv;
	enum d_op inlist[1]={D_INT};

	returnGLValue retargv;
	enum d_op retlist[4]={D_INT,D_INT,D_CHAR_LEN,D_CHAR_LEN};


	argv.page=page;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETLOG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,4))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*count=retargv.pageCount;
	*logcontentlength=retargv.uiLogLength;
	if(NULL!=logcontent)
		memcpy(logcontent,retargv.pucLog,retargv.uiLogLength);


	*uiPubKeyLength=retargv.uiPubKeyLength;
	
	if(NULL != pucPubKey)
	{
		swapRSAPubS2C(retargv.pucPubKey,retargv.uiPubKeyLength,pucPubKey,(int*)uiPubKeyLength);
		//memcpy(pucPubKey,retargv.pucPubKey,retargv.uiPubKeyLength);
	}

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

int Sig_GetServiceLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGSLValue argv;
	enum d_op inlist[1]={D_INT};

	returnGSLValue retargv;
	enum d_op retlist[3]={D_INT,D_INT,D_CHAR_LEN};


	argv.page=page;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETSERVICELOG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);//�ڶ��ε��ýӿ������ﱨ��
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*count=retargv.pageCount;
	*logcontentlength=retargv.uiLogLength;

	if(NULL!=logcontent)
	{
		memcpy(logcontent,retargv.pucLog,retargv.uiLogLength);
	}		


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}



int Sig_GetServiceLogSearch(void * hSessionHandle,unsigned int page,
	unsigned int uiStartTimeLength,unsigned char *pStartTime,
	unsigned int uiEndTimeLength,unsigned char *pEndTime,
	/*unsigned int uiLogopkindLength,unsigned char *pLogopkind*/unsigned int uilogopKind,
	unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength)
{
int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGSLSValue argv;
	enum d_op inlist[4]={D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT};


	returnGSLSValue retargv;
	enum d_op retlist[3]={D_INT,D_INT,D_CHAR_LEN};


	argv.page=page;
	argv.uiStartTimeLength=uiStartTimeLength;
	argv.pStartTime=pStartTime;
	argv.uiEndTimeLength=	uiEndTimeLength;
	argv.pEndTime=pEndTime;
	argv.uiLogopkind=uilogopKind;
	//argv.pLogopkind=pLogopkind;
	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETSERVICELOGSEARCH;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,4);
	if(status != TRUE)
	{
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
	{
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
	{
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
	{
		goto END2;
	}

	/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*count=retargv.pageCount;
	*logcontentlength=retargv.uiLogLength;
	if(NULL!=logcontent)
		memcpy(logcontent,retargv.pucLog,retargv.uiLogLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}
int Sig_CheckServiceLog(void * hSessionHandle,unsigned int id)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCSLValue argv;
	enum d_op inlist[1]={D_INT};

	returnCSLValue retargv;
	enum d_op retlist[1]={D_INT};


	argv.id=id;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CHECKSERVICELOG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));



	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;	
	
	
	

	status=retargv.status;




END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_ModifyServiceLogXmlFile(void * hSessionHandle,unsigned int logContentType,unsigned int logPolicyType,unsigned int Logtime,unsigned int SLRvalue,	unsigned char * pucURL, unsigned int uiURLLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvMSLXFValue argv;
	enum d_op inlist[6]={D_INT,D_INT,D_INT,D_INT,D_INT,D_CHAR_LEN};

	returnMSLXFValue retargv;
	enum d_op retlist[1]={D_INT};


	argv.uiLogContentType=logContentType;
	argv.uiLogPolicyType=logPolicyType;
	argv.uiLogRequestType=SLRvalue;
	argv.pucURL=pucURL;
	argv.uiURLLength=uiURLLength;
	argv.uiLogCount = 0;//��־������ʱ��
	argv.uiLogTime = Logtime;
	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_MODIFYSERVICELOGXMLFILE;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,6);
	if(status != TRUE)
	{
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
	{
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
	{
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
	{
		goto END2;
	}

	/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}



int Sig_CACertExport(void * hSessionHandle,unsigned int uiCertIndex,unsigned int *uiCertLength,unsigned char *pucCert)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCCEPValue argv;
	enum d_op inlist[1]={D_INT};

	returnCCEPValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiCertIndex=uiCertIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTEXPORT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiCertLength=retargv.uiCertLength;
	if(pucCert!=NULL)
		memcpy(pucCert,retargv.pucCert,retargv.uiCertLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_RTCertExport(void * hSessionHandle,unsigned int uiCertIndex,unsigned int *uiCertLength,unsigned char *pucCert)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRCEPValue argv;
	enum d_op inlist[1]={D_INT};

	returnRCEPValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.uiCertIndex=uiCertIndex;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_RTCERTEXPORT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiCertLength=retargv.uiCertLength;
	if(pucCert!=NULL)
		memcpy(pucCert,retargv.pucCert,retargv.uiCertLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_CACertBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCACBValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnCACBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.puiKeyIndex=puiKeyIndex;
	argv.uiKeyIndexNum=uiKeyIndexNum;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);//segmentation fault
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiCertBakLength=retargv.uiCertBakLength;
	if(pucCertBak!=NULL)
		memcpy(pucCertBak,retargv.pucCertBak,retargv.uiCertBakLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_RTCertBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvRTCBValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnRTCBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.puiKeyIndex=puiKeyIndex;
	argv.uiKeyIndexNum=uiKeyIndexNum;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_RTCERTBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiCertBakLength=retargv.uiCertBakLength;
	if(pucCertBak!=NULL)
		memcpy(pucCertBak,retargv.pucCertBak,retargv.uiCertBakLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Sig_CACertRecovery(void * hSessionHandle,unsigned int uiCertBakLength,unsigned char *pucCertBak)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvCACRValue argv;
	enum d_op dkr[1]={D_CHAR_LEN};

	returnCACRValue retargv;
	enum d_op retdkr[1]={D_INT};

	argv.pucCertBak=pucCertBak;
	argv.uiCertBakLength=uiCertBakLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_CACERTRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Sig_ServiceLogDel(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned int uiYear,unsigned int uiMonth)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSLDValue argv;
	enum d_op inlist[3]={D_INT_LEN,D_INT,D_INT};

	returnSLDValue retargv;
	enum d_op retlist[1]={D_INT};

	argv.puiLogIndex=puiKeyIndex;
	argv.uiLogIndexNum=uiKeyIndexNum;
	argv.uiyear = uiYear;
	argv.uimonth = uiMonth;
	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_SERVICELOGDEL;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,3);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,3);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Sig_ServiceLogBackup(void * hSessionHandle,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,unsigned char *pucCertBak, unsigned int* puiCertBakLength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSLBValue argv;
	enum d_op inlist[1]={D_INT_LEN};

	returnSLBValue retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};

	argv.puiLogIndex=puiKeyIndex;
	argv.uiLogIndexNum=uiKeyIndexNum;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_SERVICELOGBACKUP;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*puiCertBakLength=retargv.uiLogBakLength;
	if(pucCertBak!=NULL)
		memcpy(pucCertBak,retargv.pucLogBak,retargv.uiLogBakLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Sig_ServiceLogRecovery(void * hSessionHandle,unsigned int uiCertBakLength,unsigned char *pucCertBak)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvSLRValue argv;
	enum d_op dkr[1]={D_CHAR_LEN};

	returnSLRValue retargv;
	enum d_op retdkr[1]={D_INT};

	argv.pucLogBak=pucCertBak;
	argv.uiLogBakLength=uiCertBakLength;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_SERVICELOGRECOVERY;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,1))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int Sig_MngrLogAuditAll(void * hSessionHandle,unsigned int *uiLogIndexNum,unsigned int *puiLogIndex,unsigned int *uiLogTimeLen,unsigned char *pucLogTime)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvMLAAValue argv;
	enum d_op dkr[1]={D_INT};

	returnMLAAValue retargv;
	enum d_op retdkr[3]={D_INT,D_INT_LEN,D_CHAR_LEN};

	argv.isAllAudit=1;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_MNGRLOGAUDITALL;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*uiLogIndexNum=retargv.uiLogIndexNum;
	if(puiLogIndex!=NULL)
		memcpy(puiLogIndex,retargv.puiLogIndex,retargv.uiLogIndexNum*sizeof(int));
	*uiLogTimeLen=retargv.uiLogTimeLen;
	if(pucLogTime!=NULL)
		memcpy(pucLogTime,retargv.pucLogTime,retargv.uiLogTimeLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_ManagementLogCOA(void * hSessionHandle,unsigned int uiAuditMold,unsigned int uiOptionLen,unsigned char *pucOption,unsigned int uiOptionTypeLen,
						unsigned char *pucOptionType,unsigned int uiOptionResultLen,unsigned char *pucOptionResult,unsigned int uiStartTimeLen,unsigned char *pucStartTime,
						unsigned int uiEndTimeLen,unsigned char *pucEndTime,unsigned int *auditResultCount,unsigned int *uiReLogTimeLenth,unsigned char *pucReLogTime)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvMLCOAValue argv;
	enum d_op dkr[6]={D_INT,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN,D_CHAR_LEN};

	returnMLCOAValue retargv;
	enum d_op retdkr[3]={D_INT,D_INT,D_CHAR_LEN};

	argv.uiAuditMold=uiAuditMold;
	argv.uiOptionLen=uiOptionLen;
	argv.pucOption=pucOption;
	argv.uiOptionTypeLen=uiOptionTypeLen;
	argv.pucOptionType=pucOptionType;
	argv.uiOptionResultLen=uiOptionResultLen;
	argv.pucOptionResult=pucOptionResult;
	argv.uiStartTimeLen=uiStartTimeLen;
	argv.pucStartTime=pucStartTime;
	argv.uiEndTimeLen=uiEndTimeLen;
	argv.pucEndTime=pucEndTime;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_MANAGEMENTLOGCOA;
	pkt.packetlen=data_proc_len((void *)&argv,dkr,6);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,dkr,6);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*auditResultCount=retargv.count;
	
	*uiReLogTimeLenth=retargv.uiLogTimeLen;
	if(pucReLogTime!=NULL)
		memcpy(pucReLogTime,retargv.pucLogTime,retargv.uiLogTimeLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}


int Sig_AppCertKeySet(void * hSessionHandle, unsigned int uikeyIndex,unsigned int *uikeyKeyType,unsigned int *uikeyIndex1,unsigned int uiType)
	
{
    int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvFourIntValue argv;
	enum d_op argvop[4]={D_INT,D_INT,D_INT,D_INT};

	returnFourIntValue retargv;
	enum d_op retdkr[4]={D_INT,D_INT,D_INT,D_INT};



	socketHandle=(int)hSessionHandle;
	argv.uiInt1=uikeyIndex;
	argv.uiInt2=*uikeyKeyType;
	argv.uiInt3=*uikeyIndex1;
	argv.uiInt4=uiType;

	
	pkt.func_num=SIG_APPKEYSET;
	pkt.packetlen=data_proc_len((void *)&argv,argvop,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,argvop,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,4))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	if(retargv.status==0&&uiType==0)
	{
		//*uikeyIndex=retargv.uiInt2;
		*uikeyKeyType=retargv.uiInt3;
		*uikeyIndex1=retargv.uiInt4;
			


	}

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	
}

int Sig_NTPAddrSet(void * hSessionHandle, unsigned int *uiAddrLen,unsigned char  *pucAddr)
	
{
    int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvOneCharValue argv;
	enum d_op argvop[1]={D_CHAR_LEN};

	returnOneIntOneCharValue retargv;
	enum d_op retdkr[2]={D_INT,D_CHAR_LEN};



	socketHandle=(int)hSessionHandle;
	argv.uiCharLen=*uiAddrLen;
	argv.uiChar=pucAddr;


	
	pkt.func_num=SIG_NTPIPSET;
	pkt.packetlen=data_proc_len((void *)&argv,argvop,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

	status=data_proc((void *)&argv,send_buf,X_ENCODE,argvop,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

	if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retdkr,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	//pucAddr=retargv.uiChar;
	*uiAddrLen=retargv.uiCharLen;
	if(retargv.uiCharLen>0&&pucAddr!=NULL)
		memcpy(pucAddr,retargv.uiChar,retargv.uiCharLen);

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	
}


int TestBase64()
{
	int ret=0;
	char *p="9czik1kZAZTjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JGeOk7je9geNSo/Dpdr6HaQf2BN1r2SdoxY7ZNdXacxZO1BJGUywPfGXcI8rplSBPs2hRj5EeTtd4lyPoegzUBTW6+tTRiNrAJfmtR0glzVgCvGZfWJlscA8KS2/NrMV15vpPxwZTzdAag4hn3zIv2xaITjakqsdpJWtz0eQiTA8CdNH8JwhHf14y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JH+/T6AtZ9H6OMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1Pgkan6bpj4zlYES2eXetd61A/F7CWCsuUxG9Y96GfWhTBZoq4lCsXZyiroXMRfIetTuyYeo3FtKKjKHB1MMrQvLRBUgNPOS6Ap08UAfJ7rtEX0Pm0ZDOsNTlGawx+GR1nHW7ebNr1c+X3X/LlIChPgJup2T9ONzqZf4jqP/LsU40OBSnN7A4gx4knjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkUM0UKFaEPFoqPwk2JzxHLfJh8zfw5PCDi6c4PSkFG8DOaRn3Oi2EUYr/3VHxxTTT/42dxrkLWoiSFDFPBn4W/UbTPc2H9ESPeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CRIKIH7SnO7GI3u5lv7YDe94WRjNOqtgVtar0JXOIqd+CyyL2fL4PNBW1P5gTzM98Fxdqf8Zoa7lP5/rq8S/BKwGkPNX+6D1os4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JFijQ+DvvUO6VabT3NK4LrU/GuyobKjaJ57vui7DfrRK4oYw9kkuHZhmYm7ZrFNdG8FUz5rtHqPB5C34+sHDV9C3lIkojzoybTjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkXwYNWI2CZHeNR1B7rjIGGlGpF8Ntrfx5TK984IKKEy6e+h3QjZQROWWwEWduFI1h/loyhq1XTFBKK5zmeXF8rHRhHVONGECsuMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CRN8AY8Wf+3/dNakrT5VmiQ8KLCeHqPYH1T9pM0nvlvswbCouqllG/EEt+pH8TVAUaOiZh2z6g4CoFmGSA1tZUFszBrUHUF88R4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JEsivQgZ7wqAXuOpxkD1Vle44WXvAkrNk3JGuwpMWn+wGK8LlOFQYZsnDOZwdmsjtslJQ3xOHGty9kDt0ElMDe/ohdiGzQxRxw+YVsAnMCRflAqL+pmcrQhNwz52VOKRlTtktTBMY10rr6tX7knXuis+KMRCd665iQg1rOibo6i/+Mte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CRwxaxDzag2yvjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkYA+yOsHJ4E2paxeAohz2f+uktnKoIobyp4Kq2wZgR74WeZj/TSebGB6cMPB/LdYug2R2v9/noYDDM/22L//M4sANHXbJbKlXRZGCK4Jmc+ot5iEe46bAHPu27Q48W93RcveugIU0P7xuoob2Ei6HFuNjvzVv3WO7WbpKf3sD0Yi4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkbWrJ9JZw0JCeIWu/k25jDHWqwu3h7VljMZUivnwsRvcaGAk8axc8iQpbIFBlLSKkfiUKgW9b/BGAz3yZzQko//jLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CRfAcGaCC17R00kRuJh7bEnnncRGPGCSlSk9E1WpQK3lMB4B3SscEBfMmyAVDZg8Vj6TqB5S77/501t41NKb0zXuMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JEIpOZENMk/gUg/GYEhbYXZslN9qDlv8p4uo6Y5mE5jmsk4W4qfAEGKeu8MtU4FLxFqAT0h/aTEkyDPKcuwTtxJ4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkfXJ8i17XDM0woo/0sjvfduFvxGZwZFSwey+IuL1OalE3YCU0npRcaFfyGFahdIX/DmQDOojnEFHhct2sjQfGrjjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR4y17T39T4JHjLXtPf1PgkeMte09/U+CR8XQiY0Zgr5ba9gJyzUJvlI7pf6EnI0eDyL88er2W6URFAQMsH+x8V0ajCDpi1iaXUR8f3CV/f4/QpoQMVxtvGputYgQ5ZXQT";
	char dec[4096]={0x00};
	
	char enc[4096]={0x00};
	long int declen=decode(p, strlen(p), dec);


	long int enclen= encode( dec,declen, enc);

	printf("\n cmp::::::::::::::::strlen(p)==%d   enclen==%d\n",strlen(p),enclen);


	ret=strcmp(p,enc);
	printf("cmp::::::::::::::::strcmp==%d",ret);
	return 0;
}

int Test_Km_Random()
{
	unsigned int randlen=0;
	unsigned char Random[4096]={0x00};
	printf("Please input the RandLen:\n");
	scanf("%d",&randlen);
	
	Km_Random(Random,randlen);


	ViewMem("Random",Random,randlen);

	return 0;
}

int pkiBase64Decode( PKI_DATA i_inData, PKI_PDATA o_outData )
{
	if (i_inData.value==NULL || i_inData.size<4  /* || i_inData.size%4!=0*/)
		return PARAMETER_INVALID;
	if(o_outData == NULL)
		return PARAMETER_INVALID;

	
	//����΢��IE������base64֤���ʽ
	PKI_DATA i_DataBuf;
	i_DataBuf.value=new BYTE[i_inData.size];
	memset(i_DataBuf.value,0x00,i_inData.size);

	char * pBegin=strstr((char *)i_inData.value,"-----BEGIN CERTIFICATE-----");
	char * pEnd=strstr((char *)i_inData.value,"-----END CERTIFICATE-----");


	if(NULL!= pBegin && NULL!= pEnd)
	{
		i_DataBuf.size=pEnd-(pBegin+sizeof("-----BEGIN CERTIFICATE-----"));
		memcpy(i_DataBuf.value,pBegin+sizeof("-----BEGIN CERTIFICATE-----"),i_DataBuf.size);
	}
	else
	{
		i_DataBuf.size=i_inData.size;
		memcpy(i_DataBuf.value,i_inData.value,i_DataBuf.size);
	}


	int count = 0;
	//��һ�εõ������ĳ��ȣ�ȥ��0D 0A��*3/4��ͬʱ��������=�õ����ĳ���
	//����0D 0A�����м���
	try
	{
		for(int i=0;i<i_DataBuf.size;i++)
		{
			if (i_DataBuf.value[i]==0x0D || i_DataBuf.value[i]==0x0A)
			{
				count+=1;
			}
		}

		if(i_DataBuf.value[i_DataBuf.size-1] == '=')
		{
			if(i_DataBuf.value[i_DataBuf.size-2] == '=')
				o_outData->size = (i_DataBuf.size-count)*3/4 -2;
			else
				o_outData->size = (i_DataBuf.size-count)*3/4 -1;
		}
		else
			o_outData->size = (i_DataBuf.size-count) *3/4;

		if (o_outData->value==NULL)
		{
			delete []i_DataBuf.value;
			i_DataBuf.value=NULL;
			return 0;
		}
		//�ڶ��εõ������ʵ������
		else
		{
			//ȥ��0D 0A��ȥ��==���0��Ȼ����н��룬�����ĩβ��ӵ�0ȥ��������еĻ�
			char*  ch64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			PKI_DATA buf;	//�洢û��0d0a������
			count  = 0;
			for(int i=0;i<i_DataBuf.size;i++)
			{
				if (i_DataBuf.value[i]==0x0D || i_DataBuf.value[i]==0x0A)
				{
					count+=1;
				}
			}
			buf.size = i_DataBuf.size-count;
			buf.value = new BYTE[buf.size];
			int j = 0;
			for(int i=0, j=0;i<i_DataBuf.size;i++)
			{
				if (i_DataBuf.value[i]!=0x0D && i_DataBuf.value[i]!=0x0A)
				{
					buf.value[j] = i_DataBuf.value[i];
					j++;
				}
			}

			PKI_DATA tmp;	//�洢����������
			tmp.size=buf.size*3/4;
			tmp.value = new BYTE[tmp.size];

			if(buf.value[buf.size-1] == '=')
			{
				if(buf.value[buf.size-2] == '=') // "=="
				{
					buf.value[buf.size-1]=0x00;
					buf.value[buf.size-2]=0x00;
					tmp.size -=2;
				}
				else // "="
				{
					buf.value[buf.size-1]=0x00;
					tmp.size -=1;
				}
			}

			for(int i=0;i<buf.size;i++) // map base64 ASCII character to 6 bit value
			{
				unsigned char *p=(unsigned char *)strchr((const char *)ch64,buf.value[i]);
				if(!p)
					break;
				buf.value[i]=p-(unsigned char *)ch64;
			}

			memset(tmp.value, 0, tmp.size);

			for(int i=0,j=0; i<buf.size; i+=4,j+=3)
			{
				tmp.value[j]=(buf.value[i]<<2) + ((buf.value[i+1]&0x30)>>4);
				tmp.value[j+1]=((buf.value[i+1]&0x0F)<<4) + ((buf.value[i+2]&0x3C)>>2);
				tmp.value[j+2]=((buf.value[i+2]&0x03)<<6) + buf.value[i+3];
			}

			delete [] buf.value;
			buf.value =NULL;

			memcpy(o_outData->value,tmp.value,tmp.size);
			delete [] tmp.value;
			tmp.value = NULL;

			delete []i_DataBuf.value;
			i_DataBuf.value=NULL;
			return 0;
		}

		return 0;
	}
	catch (...) 
	{
		return UNEXPECTED_EXCEPTION;
	}
}
int  PKI_CheckCert(void *  sessionHandle,unsigned int   i_inCertLen, unsigned int * i_inCert,unsigned int   i_trustCertLen, unsigned int * i_trustCert,
	unsigned int  i_certsChainLen, unsigned int *  i_certsChain, unsigned int   i_crlLen, unsigned int *  i_crl)
{
	return 0;
}

int  PKI_GetPublicKeyFromCert(void *  sessionHandle,unsigned int i_CertLen, unsigned char *i_Cert,unsigned int  *publickeyLen, unsigned char * publickey)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argPucArg argv;
	argv.uiIntValueLen = i_CertLen;
	argv.pucIntValue = i_Cert;
	enum d_op inlist[1]={D_CHAR_LEN};

	returnIntPuc retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};
	socketHandle=(int)sessionHandle;

	pkt.func_num=PKI_GETCERTALGO;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	*publickeyLen=retargv.uiOutValueLen;
	if(publickey != NULL) //�����ַΪ�գ���һ�η������ݳ��ȣ��ڶ��η�������
	{
		memcpy(publickey,retargv.pucOutValue,retargv.uiOutValueLen);
	} 
		

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
}

int  PKI_GetXMLCertInfo(void *  hSessionHandle,unsigned int   i_inCertLen,unsigned char * i_inCert, unsigned int *o_certInfoLen,unsigned char * o_certInfo)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argPucArg argv;
	argv.uiIntValueLen = i_inCertLen;
	argv.pucIntValue = i_inCert;
	enum d_op inlist[1]={D_CHAR_LEN};

	returnIntPuc retargv;
	enum d_op retlist[2]={D_INT,D_CHAR_LEN};
	socketHandle=(int)hSessionHandle;

	pkt.func_num=PKI_GETXMLCERTINFO;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}


	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,2))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;
	*o_certInfoLen=retargv.uiOutValueLen;
	if(o_certInfo!= NULL) //�����ַΪ�գ���һ�η������ݳ��ȣ��ڶ��η�������
	{
		memcpy(o_certInfo,retargv.pucOutValue,retargv.uiOutValueLen);
	}
		

END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}

//---------------------------------add by chunsy
int Sig_GetSysLog(void * hSessionHandle,unsigned int page,unsigned int *count,unsigned char *logcontent,unsigned int *logcontentlength)
{
	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGSYSValue argv;
	enum d_op inlist[1]={D_INT};

	returnGSYSValue retargv;
	enum d_op retlist[3]={D_INT,D_INT,D_CHAR_LEN};


	argv.page=page;

	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETSYSLOG;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,1);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,1);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*count=retargv.pageCount;
	*logcontentlength=retargv.uiLogLength;
	if(NULL!=logcontent)
		memcpy(logcontent,retargv.pucLog,retargv.uiLogLength);


END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;

}


int Sig_GetServiceLogAudit(void * hSessionHandle,unsigned int page,unsigned int uiStartTimelen,unsigned char *pucStartTime,unsigned int uiEndTimelen,unsigned char *pucEndTime,
	unsigned int SLAresultNum,unsigned int *count,unsigned char *logcontent,unsigned int* logcontentlength)
{

	int status;
	int socketHandle;

	unsigned int date_len;

	char * send_buf;
	char * recv_data;

	packetInfo pkt;

	/*----------------------------------------------------------------*/
	argvGSLAValue argv;
	enum d_op inlist[4]={D_INT,D_CHAR_LEN,D_CHAR_LEN,D_INT};


	returnGSLAValue retargv;
	enum d_op retlist[3]={D_INT,D_INT,D_CHAR_LEN};


	argv.page=page;
	argv.uiStartTimeLength=uiStartTimelen;
	argv.pStartTime=pucStartTime;
	argv.uiEndTimeLength=	uiEndTimelen;
	argv.pEndTime=pucEndTime;
	argv.uiLogresult=SLAresultNum;
	//argv.pLogresult=pucSLAresult;
	socketHandle=(int)hSessionHandle;

	pkt.func_num=SIG_GETSERVICELOGAUDIT;
	pkt.packetlen=data_proc_len((void *)&argv,inlist,4);

	/*----------------------------------------------------------------*/

	send_buf=(char *)calloc(pkt.packetlen,sizeof(char));

/**/status=data_proc((void *)&argv,send_buf,X_ENCODE,inlist,4);
	if(status != TRUE)
    {
		goto END1;
	}

	status=call_require(socketHandle,send_buf,&pkt);
	if(status != 0)
    {
		goto END1;
	}


	status=call_response_header(socketHandle,&date_len);
	if(status != 0)
    {
		goto END1;
	}

	recv_data=(char *)calloc(date_len,sizeof(char));

	status=call_response_data(socketHandle,date_len,recv_data);
	if(status != 0)
    {
		goto END2;
	}

/**/if ( !data_proc((void *)&retargv,(char *)recv_data,X_DECODE,retlist,3))
	{

		status= SDR_RETVDECODE;
		goto END2;
	}

	status=retargv.status;

	*count=retargv.pageCount;
	*logcontentlength=retargv.uiLogLength;
	if(NULL!=logcontent)
	{
		memcpy(logcontent,retargv.pucLog,retargv.uiLogLength);

	}
		
END2:
	free(recv_data);
END1:
	free(send_buf);
	return status;
	

}
