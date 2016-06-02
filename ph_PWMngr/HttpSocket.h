// HttpSocket.h: interface for the CHttpSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPSOCKET_H__F49A8F82_A933_41A8_AF47_68FBCAC4ADA6__INCLUDED_)
#define AFX_HTTPSOCKET_H__F49A8F82_A933_41A8_AF47_68FBCAC4ADA6__INCLUDED_


#include "winsock2.h"
#include <afxinet.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class  CHttpSocket  
{
public:
	int				GetServerState();						//���ط�����״̬�� -1��ʾ���ɹ�
	int				GetField(const char* szSession,char *szValue,int nMaxLength);	//����ĳ����ֵ,-1��ʾ���ɹ�

	int				GetReturn(const char *szString, char *szStartValue,char *szEndValue,char *szValue);	//����ĳ����ֵ,-1��ʾ���ɹ�
	int				GetResponseLine(char *pLine,int nMaxLength);				//��ȡ����ͷ��һ��
	const char*		GetResponseHeader(int &Length);								//��ȡ�����ķ���ͷ
	const char *	FormatRequestHeader(char *pServer,char *pObject,long &Length,char *pContentValue=NULL,
						char* pCookie=NULL,char *pReferer=NULL,
						long nFrom=0,long nTo=0,
						int nServerType=0 );									//��ʽ������ͷ
	int				GetRequestHeader(char *pHeader,int nMaxLength) const;
	BOOL			SendRequest(const char* pRequestHeader = NULL,long Length = 0);

	int  StartAuthClient(char* ip,char* certid,char* certdata,char* signdata,char* randomdata,char *port,char * sessionid);
	int  StartAuthClient(char* ip,char* username,char* password,char *port,char * sessionid);
	int  StartAuthClient(char* ip,char* hardware,char *port,char * sessionid);
	//int  StartClient(char* ip, int nPort,LPCTSTR senddata,CString& receivedata);
	int  StartClient(char* ip, int nPort,LPCTSTR senddata,PKI_DATA *receivedata,LPCTSTR strObject);
	
	//int  LinkSoap(char* ip, int nPort, LPCTSTR url, LPCTSTR sendSysID, LPCTSTR TarSysID, LPCTSTR	requestType, LPCTSTR messageID, LPCTSTR senddata, CString& receivedata);
	int  initSocket();
	void endSocket();

	int  EndAuthClient(char* ip,char* certid,char* certdata,char *port);

	CString	UTF8Convert(CString &str,int sourceCodepage,int targetCodepage);

	CHttpSocket();
	virtual ~CHttpSocket();

	BOOL			SetTimeout(int nTime,int nType=0);
	long			Receive(char* pBuffer,long nMaxLength);
	BOOL			Connect(char* szHostName,int nPort=80);
	BOOL			Socket();
	BOOL			CloseSocket();
	


protected:	
	char m_requestheader[4096];		//����ͷ
	char m_ResponseHeader[4096];	//��Ӧͷ
	int m_port;						//�˿�
	char m_ipaddr[256];				//IP��ַ
	BOOL m_bConnected;
	SOCKET m_s;
	hostent *m_phostent;

	int m_nCurIndex;				//GetResponsLine()�������α��¼
	BOOL m_bResponsed;				//�Ƿ��Ѿ�ȡ���˷���ͷ
	int m_nResponseHeaderSize;		//��Ӧͷ�Ĵ�С
/*
	int m_nBufferSize;
	char *m_pBuffer;*/

};

#endif // !defined(AFX_HTTPSOCKET_H__F49A8F82_A933_41A8_AF47_68FBCAC4ADA6__INCLUDED_)
