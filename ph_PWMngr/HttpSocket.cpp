// HttpSocket.cpp: implementation of the CHttpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HttpSocket.h"



using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAXHEADERSIZE 4096
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHttpSocket::CHttpSocket()
{
	m_s=NULL;
	m_phostent=NULL;
	m_port=80;

	m_bConnected=FALSE;

	for(int i=0;i<256;i++)
		m_ipaddr[i]='\0';
	memset(m_requestheader,0,MAXHEADERSIZE);
	memset(m_ResponseHeader,0,MAXHEADERSIZE);

	m_nCurIndex = 0;		//
	m_bResponsed = FALSE;
	m_nResponseHeaderSize = -1;
/*
	m_nBufferSize = nBufferSize;
	m_pBuffer = new char[nBufferSize];
	memset(m_pBuffer,0,nBufferSize);*/
}

CHttpSocket::~CHttpSocket()
{
	CloseSocket();
}

BOOL CHttpSocket::Socket()
{
	if(m_bConnected)return FALSE;

	struct protoent *ppe; 
	ppe = getprotobyname("tcp"); 
	
	///����SOCKET����
	m_s=socket(PF_INET,SOCK_STREAM,ppe->p_proto);
	if(m_s==INVALID_SOCKET)
	{
		//MessageBox(NULL,"socket()����ִ��ʧ��!","����",MB_OK);
		return FALSE;
	}

	return TRUE;

}

BOOL CHttpSocket::Connect(char *szHostName,int nPort)
{
	
    unsigned long non_blocking = 1;
    unsigned long blocking = 0;

	if(szHostName==NULL)
		return FALSE;

	///���Ѿ�����,���ȹر�
	if(m_bConnected)
	{
		CloseSocket();
	}

	if (	ioctlsocket(m_s,FIONBIO,&blocking) < 0)  //����Ϊ������

	{
    	CloseSocket();
	}

	///����˿ں�
	m_port=nPort;

	///�������������IP��ַ
	m_phostent=gethostbyname(szHostName);
	if(m_phostent==NULL)
	{
		//MessageBox(NULL,"gethostbyname()����ִ��ʧ��!","����",MB_OK);
		return FALSE;
	}
	
	///����
	struct in_addr ip_addr;
	memcpy(&ip_addr,m_phostent->h_addr_list[0],4);///h_addr_list[0]��4���ֽ�,ÿ���ֽ�8λ
	
	struct sockaddr_in destaddr;
	memset((void *)&destaddr,0,sizeof(destaddr)); 
	destaddr.sin_family=AF_INET;
	destaddr.sin_port=htons(m_port);
	destaddr.sin_addr=ip_addr;

	///����������IP��ַ�ַ���
	sprintf(m_ipaddr,"%d.%d.%d.%d",
		destaddr.sin_addr.S_un.S_un_b.s_b1,
		destaddr.sin_addr.S_un.S_un_b.s_b2,
		destaddr.sin_addr.S_un.S_un_b.s_b3,
		destaddr.sin_addr.S_un.S_un_b.s_b4);
	/*inet_addr();�Ѵ����IP��ַ�ַ���ת��Ϊin_addr��ʽ;
	  inet_ntoa();�����෴*/
	
	/*ע�����sturct in_addr �Ľṹ:һ��32λ����;һ��ͬ�����ʽʹ��
	(1)ÿ8λһ����s_b1~s_b4;
	(2)ÿ16λһ����s_w1~s_w2;
	(3)32λs_addr
	struct   in_addr {
    union   {
			  struct{
				unsigned  char   s_b1,
								 s_b2,
								 s_b3,
								 s_b4;
					} S_un_b;
              struct{
				unsigned  short  s_w1,
                                 s_w2
			        }S_un_w;      
               unsigned long  S_addr;
			} S_un;
		};
	*/
  
    
	if(connect(m_s,(struct sockaddr*)&destaddr,sizeof(destaddr))==-1)
	{
 
       struct timeval tv; 
        fd_set writefds;
        // �������ӳ�ʱʱ��
        int error;

        tv.tv_sec = 60*10; // ����

        tv.tv_usec = 0; // ����

        FD_ZERO(&writefds); 

        FD_SET(m_s, &writefds); 

        if(select(m_s+1,NULL,&writefds,NULL,&tv) != 0){ 

            if(FD_ISSET(m_s,&writefds)){

                int len=sizeof(error); 

                //�����һ��һ��Ҫ����Ҫ��Է���ǽ 

                if(getsockopt(m_s, SOL_SOCKET, SO_ERROR,  (char *)&error, &len) < 0)

				{return FALSE;}

                if(error != 0) 

                { return FALSE;}

            }

		}else 
           return FALSE;
	}

	ioctlsocket(m_s,FIONBIO,&blocking);
	///�����Ѿ����ӵı�־
	m_bConnected=TRUE;
	return TRUE;
}

///������������URL���HTTP����ͷ
const char *CHttpSocket::FormatRequestHeader(char *pServer,char *pObject, long &Length,char *pContentValue,
									  char *pCookie,char *pReferer,long nFrom,
									  long nTo,int nServerType )
{
	char szPort[10];
	sprintf(szPort,"%d",m_port);
	memset(m_requestheader,'\0',4096);

	///��1��:����,�����·��,�汾
	if(nServerType==0)
	{
	strcat(m_requestheader,"POST ");
	}else{
	strcat(m_requestheader,"GET ");
	}
	strcat(m_requestheader,pObject);
	strcat(m_requestheader," HTTP/1.0");
    strcat(m_requestheader,"\r\n");

	///��2��:����
    strcat(m_requestheader,"Host: ");
	strcat(m_requestheader,pServer);
    strcat(m_requestheader,"\r\n");

	///��3��:
	//if(pReferer != NULL)
	//{
	//	strcat(m_requestheader,"Referer:");
	//	strcat(m_requestheader,pReferer);
	//	strcat(m_requestheader,"\r\n");		
	//}

	///��4��:���յ���������
    //strcat(m_requestheader,"Accept:*/*");
    //strcat(m_requestheader,"\r\n");

	 ///��5��:���������
    //strcat(m_requestheader,"User-Agent:Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)");
    //strcat(m_requestheader,"\r\n");

	//��6��:��������,����
	//strcat(m_requestheader,"Connection:Keep-Alive");
	//strcat(m_requestheader,"\r\n");

	
	strcat(m_requestheader,"Content-Type: text/xml; charset=UTF-8");
	strcat(m_requestheader,"\r\n");

    strcat(m_requestheader,"SOAPAction: \"\"");
	strcat(m_requestheader,"\r\n");

	///��7��:Cookie.
	//if(pCookie != NULL)
	//{
	//	strcat(m_requestheader,"Set Cookie:0");
	//	strcat(m_requestheader,pCookie);
	//	strcat(m_requestheader,"\r\n");
	//}

	///��8��:�����������ʼ�ֽ�λ��(�ϵ������Ĺؼ�)
	//if(nFrom > 0)
	//{
	//	strcat(m_requestheader,"Range: bytes=");
	//	_ltoa(nFrom,szTemp,10);
	//	strcat(m_requestheader,szTemp);
	//	strcat(m_requestheader,"-");
	//	if(nTo > nFrom)
	//	{
	//		_ltoa(nTo,szTemp,10);
	//		strcat(m_requestheader,szTemp);
	//	}
	//	strcat(m_requestheader,"\r\n");
   //}
	if(pContentValue != NULL)
	 {
		 char szContentLength[10];
         //sprintf(szContentLength,"%d",strlen(pContentValue)+2);
		 _itoa(strlen(pContentValue)+2,szContentLength,10); //�ѳ���ת����assic�� ������ʽ

	     strcat(m_requestheader,"Content-Length: ");
         strcat(m_requestheader,szContentLength);
	     strcat(m_requestheader,"\r\n");
         strcat(m_requestheader,"\r\n");
     
     	 strcat(m_requestheader,pContentValue);

	}
	 //strcat(m_requestheader,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	 //strcat(m_requestheader,"<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" ");
     //strcat(m_requestheader,"xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ");
     //strcat(m_requestheader,"xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ");
     //strcat(m_requestheader,"xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"><SOAP-ENV:Body>");
	 //strcat(m_requestheader,"<authentication><certid xsi:type=\"xsd:string\">1</certid><randomdata xsi:type=\"xsd:string\">randomdata</randomdata><certdata xsi:type=\"xsd:string\"></certdata><signdata xsi:type=\"xsd:string\"></signdata>");
	 //strcat(m_requestheader,"<clientip xsi:type=\"xsd:string\">192.168.0.1</clientip></authentication></SOAP-ENV:Body></SOAP-ENV:Envelope>" );
     strcat(m_requestheader,"\r\n");


	
	///���һ��:����
	strcat(m_requestheader,"\r\n");

	///���ؽ��
	Length=strlen(m_requestheader);

	return m_requestheader;
}

///��������ͷ
BOOL CHttpSocket::SendRequest(const char *pRequestHeader, long Length)
{
	if(!m_bConnected)return FALSE;

	if(pRequestHeader==NULL)
		pRequestHeader=m_requestheader;
	if(Length==0)
		Length=strlen(m_requestheader);

	if(send(m_s,pRequestHeader,Length,0)==SOCKET_ERROR)
	{
		//MessageBox(NULL,"send()����ִ��ʧ��!","����",MB_OK);
		return FALSE;
	}
	int nLength;
	GetResponseHeader(nLength);
	return TRUE;
}

long CHttpSocket::Receive(char* pBuffer,long nMaxLength)
{
	if(!m_bConnected)return NULL;

	///��������
	long nLength=0;
   char  *buf;
   buf = (char *)pBuffer;
   int recvLen=nMaxLength;
   int recvBytes=0;
   int i=0;
   while( recvLen > 0 )
    {
        recvBytes = recv( m_s, buf, recvLen, 0 );
        if( recvBytes <= 0 )
        {
           if(i<0) 
			   return -1;
		   else
			   return  nLength;
        }


        buf += recvBytes;
        recvLen -= recvBytes;


		nLength+=recvBytes;
    }
	
	return nLength;
}

///�ر��׽���
BOOL CHttpSocket::CloseSocket()
{
	if(m_s != NULL)
	{
		if(closesocket(m_s)==SOCKET_ERROR)
		{
			//MessageBox(NULL,"closesocket()����ִ��ʧ��!","����",MB_OK);
			return FALSE;
		}
	}
	m_s = NULL;
	m_bConnected=FALSE;
	return TRUE;
}

int CHttpSocket::GetRequestHeader(char *pHeader, int nMaxLength) const
{
	int nLength;
	if(int(strlen(m_requestheader))>nMaxLength)
	{
		nLength=nMaxLength;
	}
	else
	{
		nLength=strlen(m_requestheader);
	}
	memcpy(pHeader,m_requestheader,nLength);
	return nLength;
}

//���ý��ջ��߷��͵��ʱ��
BOOL CHttpSocket::SetTimeout(int nTime, int nType)
{
	if(nType == 0)
	{
		nType = SO_RCVTIMEO;
	}
	else
	{
		nType = SO_SNDTIMEO;
	}

	DWORD dwErr;
    dwErr=setsockopt(m_s,SOL_SOCKET,nType,(char*)&nTime,sizeof(nTime)); 
	if(dwErr)
	{
		//MessageBox(NULL,"setsockopt()����ִ��ʧ��!","����",MB_OK);
		return FALSE;
	}
	return TRUE;
}

//��ȡHTTP����ķ���ͷ
const char* CHttpSocket::GetResponseHeader(int &nLength)
{
	if(!m_bResponsed)
	{
		char c = 0;
		int nIndex = 0;
		BOOL bEndResponse = FALSE;
		while(!bEndResponse && nIndex < MAXHEADERSIZE)
		{
			recv(m_s,&c,1,0);
			m_ResponseHeader[nIndex++] = c;
			if(nIndex >= 4)
			{
				if(m_ResponseHeader[nIndex - 4] == '\r' && m_ResponseHeader[nIndex - 3] == '\n'
					&& m_ResponseHeader[nIndex - 2] == '\r' && m_ResponseHeader[nIndex - 1] == '\n')
				bEndResponse = TRUE;
			}
		}
		m_nResponseHeaderSize = nIndex;
		m_bResponsed = TRUE;
	}
	
	nLength = m_nResponseHeaderSize;
	return m_ResponseHeader;
}

//����HTTP��Ӧͷ�е�һ��.
int CHttpSocket::GetResponseLine(char *pLine, int nMaxLength)
{
	if(m_nCurIndex >= m_nResponseHeaderSize)
	{
		m_nCurIndex = 0;
		return -1;
	}

	int nIndex = 0;
	char c = 0;
	do 
	{
		c = m_ResponseHeader[m_nCurIndex++];
		pLine[nIndex++] = c;
	} while(c != '\n' && m_nCurIndex < m_nResponseHeaderSize && nIndex < nMaxLength);
	
	return nIndex;
}

int CHttpSocket::GetField(const char *szSession, char *szValue, int nMaxLength)
{
	//ȡ��ĳ����ֵ
	if(!m_bResponsed) return -1;
	
	CString strRespons;
	strRespons = m_ResponseHeader;
	int nPos = -1;
	nPos = strRespons.Find(szSession,0);
	if(nPos != -1)
	{
		nPos += strlen(szSession);
		nPos += 2;
		int nCr = strRespons.Find("\r\n",nPos);
		CString strValue = strRespons.Mid(nPos,nCr - nPos);
		strcpy(szValue,strValue);
		return (nCr - nPos);
	}
	else
	{
		return -1;
	}
}


int CHttpSocket::GetReturn(const char *szString, char *szStartValue,char *szEndValue,char *szValue)
{

	int nStart = -1,nEnd = -1;
	CString strRespons;
    strRespons = szString;
	nStart = strRespons.Find(szStartValue,0);
	if(nStart != -1)
	{
		nStart += strlen(szStartValue);
		int nEnd = strRespons.Find(szEndValue,nStart);
		CString strValue = strRespons.Mid(nStart,nEnd - nStart);
		strcpy(szValue,strValue);
		return (nEnd - nStart);
	}
	else
	{
		return -1;
	}
}


int CHttpSocket::GetServerState()
{
	//��û��ȡ����Ӧͷ,����ʧ��
	if(!m_bResponsed) return -1;
	
	char szState[3];
	szState[0] = m_ResponseHeader[9];
	szState[1] = m_ResponseHeader[10];
	szState[2] = m_ResponseHeader[11];

	return atoi(szState);
}

int  CHttpSocket::StartAuthClient(char* ip,char* certid,char* certdata,char* signdata,char* randomdata,char *port,char * sessionid){
	int ret=-1;
	
	BOOL bRet=false; 

	CString strServer,strObject;
	unsigned short nPort=80;
    nPort=atoi(port);
	DWORD dwServiceType=AFX_INET_SERVICE_HTTP;
	long nLength;
	const char *pRequestHeader = NULL;
	CString strContentValue;
    strServer=ip;
	strObject="/soap/soaps.php";
	strContentValue+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	strContentValue+="<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" ";
	strContentValue+="xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ";
    strContentValue+="xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" ";
    strContentValue+="xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
    strContentValue+="xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">";
	strContentValue+="<SOAP-ENV:Body> ";
	strContentValue+="<authentication>";
	strContentValue+="<certid xsi:type=\"xsd:string\">";
	strContentValue+=certid;
	strContentValue+= "</certid>";
	strContentValue+="<randomdata xsi:type=\"xsd:string\">";
    strContentValue+=randomdata;
	strContentValue+="</randomdata>";
	strContentValue+="<certdata xsi:type=\"xsd:string\">";
	strContentValue+="datea";
	strContentValue+="</certdata>";
	strContentValue+="<signdata xsi:type=\"xsd:string\">";
	strContentValue+=signdata;
	strContentValue+="</signdata>";
	//strContentValue+="<clientip xsi:type=\"xsd:string\">192.168.0.1</clientip>";
	strContentValue+="<clientip xsi:type=\"xsd:string\">130.103.1.102</clientip>";
	strContentValue+="</authentication></SOAP-ENV:Body></SOAP-ENV:Envelope>";

	pRequestHeader =FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength,(LPTSTR)(LPCTSTR)strContentValue);	
	bRet=Socket();
	if(!bRet)
	{  
		ret=-1001;
		return ret; 
	}

	bRet=Connect((LPTSTR)(LPCTSTR)strServer,nPort);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
	bRet=SendRequest();
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
    bRet=SetTimeout(100000,0);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}

/*
	int nSize;
	HttpSocket.GetResponseHeader(nSize);*/


	int nLineSize = 0;
	char szLine[256];
	while(nLineSize != -1)
	{
		nLineSize = GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
		}
	}
	char szValue[30];
	GetField("Content-Length",szValue,30);
	int nSvrState = GetServerState();
	int nFileSize = atoi(szValue);
    //nFileSize=10;

	int nCompletedSize = 0;


	char pData[1024];
	int nReceSize = 0;
    CString strReceiveData;
    DWORD dwStartTime,dwEndTime;
	while(nCompletedSize < nFileSize)
	{
		dwStartTime = GetTickCount();
		nReceSize = Receive(pData,1024);
		if(nReceSize == 0)
		{
			//AfxMessageBox("�������Ѿ��ر�����.");
			CloseSocket();
			ret=-1001;
			break;
		}
		if(nReceSize == -1)
		{
			AfxMessageBox("�������ݳ�ʱ.");
			CloseSocket();
			ret=1007;
			break;
		}
		strReceiveData=pData;
		nCompletedSize += nReceSize;

	}
	dwEndTime = GetTickCount();
	CString strRetrun;
	GetReturn(strReceiveData,"<return xsi:type=\"xsd:string\">","</return>",(LPTSTR)(LPCTSTR)strRetrun);
	if(strRetrun=="")
		   ret=-1;
	else{
		   ret=atoi(strRetrun);
		 }
	strcpy(sessionid,   strRetrun); 
	CloseSocket();//�ر�socket
    return ret;
}


int  CHttpSocket::StartAuthClient(char* ip,char* username,char* password,char *port,char * sessionid){
	int ret=-1;
	
	BOOL bRet=false; 

	CString strServer,strObject;
	unsigned short nPort=80;
    nPort=atoi(port);
	DWORD dwServiceType=AFX_INET_SERVICE_HTTP;
	long nLength;
	const char *pRequestHeader = NULL;
	CString strContentValue;
    strServer=ip;
	strObject="/soap/soaps.php";
	strContentValue+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	strContentValue+="<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" ";
	strContentValue+="xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ";
    strContentValue+="xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" ";
    strContentValue+="xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
    strContentValue+="xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">";
	strContentValue+="<SOAP-ENV:Body> ";
	strContentValue+="<authusername>";
	strContentValue+="<username xsi:type=\"xsd:string\">";
	strContentValue+=username;
	strContentValue+= "</username>";
	strContentValue+="<password xsi:type=\"xsd:string\">";
    strContentValue+=password;
	strContentValue+="</password>";
	strContentValue+="<clientip xsi:type=\"xsd:string\">130.103.1.102</clientip>";
	strContentValue+="</authusername></SOAP-ENV:Body></SOAP-ENV:Envelope>";

	pRequestHeader =FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength,(LPTSTR)(LPCTSTR)strContentValue);	
	bRet=Socket();
	if(!bRet)
	{  
		ret=-1001;
		return ret; 
	}

	bRet=Connect((LPTSTR)(LPCTSTR)strServer,nPort);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
	bRet=SendRequest();
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
    bRet=SetTimeout(100000,0);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}

/*
	int nSize;
	HttpSocket.GetResponseHeader(nSize);*/


	int nLineSize = 0;
	char szLine[256];
	while(nLineSize != -1)
	{
		nLineSize = GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
		}
	}
	char szValue[30];
	GetField("Content-Length",szValue,30);
	int nSvrState = GetServerState();
	int nFileSize = atoi(szValue);
    //nFileSize=10;

	int nCompletedSize = 0;


	char pData[1024];
	int nReceSize = 0;
    CString strReceiveData;
    DWORD dwStartTime,dwEndTime;
	while(nCompletedSize < nFileSize)
	{
		dwStartTime = GetTickCount();
		nReceSize = Receive(pData,1024);
		if(nReceSize == 0)
		{
			//AfxMessageBox("�������Ѿ��ر�����.");
			CloseSocket();
			ret=-1001;
			break;
		}
		if(nReceSize == -1)
		{
			AfxMessageBox("�������ݳ�ʱ.");
			CloseSocket();
			ret=1007;
			break;
		}
		strReceiveData=pData;
		nCompletedSize += nReceSize;

	}
	dwEndTime = GetTickCount();
	CString strRetrun;
	GetReturn(strReceiveData,"<return xsi:type=\"xsd:string\">","</return>",(LPTSTR)(LPCTSTR)strRetrun);
	if(strRetrun=="")
		   ret=-1;
	else{
		   ret=atoi(strRetrun);
		 }
	strcpy(sessionid,   strRetrun); 
	CloseSocket();//�ر�socket
    return ret;
}

int  CHttpSocket::StartAuthClient(char* ip,char* hardware,char *port,char * sessionid){
	int ret=-1;
	
	BOOL bRet=false; 

	CString strServer,strObject;
	unsigned short nPort=80;
    nPort=atoi(port);
	DWORD dwServiceType=AFX_INET_SERVICE_HTTP;
	long nLength;
	const char *pRequestHeader = NULL;
	CString strContentValue;
    strServer=ip;
	strObject="/soap/soaps.php";
	strContentValue+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	strContentValue+="<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" ";
	strContentValue+="xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ";
    strContentValue+="xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" ";
    strContentValue+="xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
    strContentValue+="xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">";
	strContentValue+="<SOAP-ENV:Body> ";
	strContentValue+="<authhardware>";
	strContentValue+="<hardware xsi:type=\"xsd:string\">";
	strContentValue+=hardware;
	strContentValue+= "</hardware>";
	strContentValue+="<clientip xsi:type=\"xsd:string\">130.103.1.102</clientip>";
	strContentValue+="</authhardware></SOAP-ENV:Body></SOAP-ENV:Envelope>";

	pRequestHeader =FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength,(LPTSTR)(LPCTSTR)strContentValue);	
	bRet=Socket();
	if(!bRet)
	{  
		ret=-1001;
		return ret; 
	}

	bRet=Connect((LPTSTR)(LPCTSTR)strServer,nPort);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
	bRet=SendRequest();
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}
    bRet=SetTimeout(100000,0);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		return ret; 
	}

/*
	int nSize;
	HttpSocket.GetResponseHeader(nSize);*/


	int nLineSize = 0;
	char szLine[256];
	while(nLineSize != -1)
	{
		nLineSize = GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
		}
	}
	char szValue[30];
	GetField("Content-Length",szValue,30);
	int nSvrState = GetServerState();
	int nFileSize = atoi(szValue);
    //nFileSize=10;

	int nCompletedSize = 0;


	char pData[1024];
	int nReceSize = 0;
    CString strReceiveData;
    DWORD dwStartTime,dwEndTime;
	while(nCompletedSize < nFileSize)
	{
		dwStartTime = GetTickCount();
		nReceSize = Receive(pData,1024);
		if(nReceSize == 0)
		{
			//AfxMessageBox("�������Ѿ��ر�����.");
			CloseSocket();
			ret=-1001;
			break;
		}
		if(nReceSize == -1)
		{
			AfxMessageBox("�������ݳ�ʱ.");
			CloseSocket();
			ret=1007;
			break;
		}
		strReceiveData=pData;
		nCompletedSize += nReceSize;

	}
	dwEndTime = GetTickCount();
	CString strRetrun;
	GetReturn(strReceiveData,"<return xsi:type=\"xsd:string\">","</return>",(LPTSTR)(LPCTSTR)strRetrun);
	if(strRetrun=="")
		   ret=-1;
	else{
		   ret=atoi(strRetrun);
		 }
	strcpy(sessionid,   strRetrun); 
	CloseSocket();//�ر�socket
    return ret;
}

int CHttpSocket::EndAuthClient(char* ip,char* certid,char* certdata,char *port){
	int ret=-1;
	
	CString strServer,strObject;

	unsigned short nPort=80;
    nPort=atoi(port);
	DWORD dwServiceType=AFX_INET_SERVICE_HTTP;
	long nLength;
	const char *pRequestHeader = NULL;
	CString strContentValue;
    strServer=ip;
	strObject="/soap/soaps.php";
	strContentValue+="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	strContentValue+="<SOAP-ENV:Envelope SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" ";
	strContentValue+="xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" ";
    strContentValue+="xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" ";
    strContentValue+="xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
    strContentValue+="xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">";
	strContentValue+="<SOAP-ENV:Body> ";
	strContentValue+="<disconnect>";
	strContentValue+="<certid xsi:type=\"xsd:string\">";
	strContentValue+=certid;
	strContentValue+= "</certid>";
	strContentValue+="<certdata xsi:type=\"xsd:string\"></certdata>";
	strContentValue+="</disconnect></SOAP-ENV:Body></SOAP-ENV:Envelope>";

	pRequestHeader = FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength,(LPTSTR)(LPCTSTR)strContentValue);	
	Socket();
	Connect((LPTSTR)(LPCTSTR)strServer,nPort);
	SendRequest();
	SetTimeout(10000,0);
/*
	int nSize;
	HttpSocket.GetResponseHeader(nSize);*/


	int nLineSize = 0;
	char szLine[256];
	while(nLineSize != -1)
	{
		nLineSize = GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
		}
	}
	char szValue[30];
	GetField("Content-Length",szValue,30);
	int nSvrState = GetServerState();
	int nFileSize = atoi(szValue);
    //nFileSize=10;

	int nCompletedSize = 0;


	char pData[1024];
	int nReceSize = 0;
    CString strReceiveData;
    DWORD dwStartTime,dwEndTime;
	while(nCompletedSize < nFileSize)
	{
		dwStartTime = GetTickCount();
		nReceSize = Receive(pData,1024);
		if(nReceSize == 0)
		{
			AfxMessageBox("�������Ѿ��ر�����.");
			ret=1001;
			break;
		}
		if(nReceSize == -1)
		{
			AfxMessageBox("�������ݳ�ʱ.");
			ret=1007;
			break;
		}
		strReceiveData=pData;
		nCompletedSize += nReceSize;
	}
		dwEndTime = GetTickCount();
		CString strRetrun;
		GetReturn(strReceiveData,"<return xsi:type=\"xsd:string\">","</return>",(LPTSTR)(LPCTSTR)strRetrun);
		if(strRetrun=="0")
			ret=0;
		else{
		   ret=atoi(strRetrun);
		 }

	CloseSocket();
   return ret;
}

int  CHttpSocket::initSocket()
{
		///��ʼ��Socket������
	int err;
	WORD wVersion;
	WSADATA WSAData;

	wVersion = MAKEWORD(2,0);
	err = WSAStartup(wVersion,&WSAData);
	if(err != 0)
	{
		err = WSAGetLastError();
	}
	
	return err;
}

void CHttpSocket::endSocket()
{
	///���Socket��
	WSACleanup();
}


CString CHttpSocket::UTF8Convert(CString &str,int sourceCodepage,int targetCodepage)
{
	int len=str.GetLength(); 

	int unicodeLen=MultiByteToWideChar(sourceCodepage,0,str,-1,NULL,0); 

	wchar_t * pUnicode; 
	pUnicode=new wchar_t[unicodeLen+1]; 

	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 


	MultiByteToWideChar(sourceCodepage,0,str,-1,(LPWSTR)pUnicode,unicodeLen); 

	BYTE * pTargetData=NULL; 
	int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL); 

	pTargetData=new BYTE[targetLen+1]; 
	memset(pTargetData,0,targetLen+1); 

	WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL); 

	CString rt; 
	rt.Format("%s",pTargetData); 

	delete pUnicode; 
	delete pTargetData; 
	return rt; 
} 


int  CHttpSocket::StartClient(char* ip, int nPort,LPCTSTR senddata, PKI_DATA *receivedata,LPCTSTR object)
{
	if(receivedata->value == NULL)
	{
		receivedata->size = 81920;
	    return 0;
	}
	int ret=-1;
	BOOL bRet=false; 

	CString strServer,strObject;
	DWORD dwServiceType=AFX_INET_SERVICE_HTTP;
	long nLength;
	const char *pRequestHeader = NULL;
	CString strContentValue;
    strServer=ip;
	strObject=object;//RA��URL
	strContentValue+=senddata;

	pRequestHeader =FormatRequestHeader((LPTSTR)(LPCTSTR)strServer,(LPTSTR)(LPCTSTR)strObject,nLength,(LPTSTR)(LPCTSTR)strContentValue);	
	bRet=initSocket();
	if(bRet != 0)
	{  
		ret=-1001;
		endSocket();
		return ret; 
	}

	bRet=Socket();
	if(!bRet)
	{  
		ret=-1001;
		endSocket();
		return ret; 
	}

	bRet=Connect((LPTSTR)(LPCTSTR)strServer,nPort);
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		endSocket();
		return ret; 
	}
	bRet=SendRequest();
	if(!bRet)
	{  
		ret=-1001;
		CloseSocket();
		endSocket();
		return ret; 
	}

	char pData[81920];
	int nReceSize = 0;
    //CString strReceiveData;
	//Sleep(1000);

	nReceSize = Receive(pData,81920);

	if(nReceSize == 0)
	{
		CloseSocket();
		endSocket();
		ret=-1001;	
	}
	if(nReceSize == -1)
	{
		AfxMessageBox("�������ݳ�ʱ.");
		CloseSocket();
		endSocket();
		ret=1007;
			
	}
	//strReceiveData=pData;
	
	receivedata->size = nReceSize;
	memcpy(receivedata->value,pData,receivedata->size);
	//receivedata = strReceiveData;
	endSocket();
	CloseSocket();//�ر�socket
    return 0;
}