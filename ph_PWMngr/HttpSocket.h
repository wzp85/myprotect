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
	int				GetServerState();						//返回服务器状态码 -1表示不成功
	int				GetField(const char* szSession,char *szValue,int nMaxLength);	//返回某个域值,-1表示不成功

	int				GetReturn(const char *szString, char *szStartValue,char *szEndValue,char *szValue);	//返回某个域值,-1表示不成功
	int				GetResponseLine(char *pLine,int nMaxLength);				//获取返回头的一行
	const char*		GetResponseHeader(int &Length);								//获取完整的返回头
	const char *	FormatRequestHeader(char *pServer,char *pObject,long &Length,char *pContentValue=NULL,
						char* pCookie=NULL,char *pReferer=NULL,
						long nFrom=0,long nTo=0,
						int nServerType=0 );									//格式化请求头
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
	char m_requestheader[4096];		//请求头
	char m_ResponseHeader[4096];	//回应头
	int m_port;						//端口
	char m_ipaddr[256];				//IP地址
	BOOL m_bConnected;
	SOCKET m_s;
	hostent *m_phostent;

	int m_nCurIndex;				//GetResponsLine()函数的游标记录
	BOOL m_bResponsed;				//是否已经取得了返回头
	int m_nResponseHeaderSize;		//回应头的大小
/*
	int m_nBufferSize;
	char *m_pBuffer;*/

};

#endif // !defined(AFX_HTTPSOCKET_H__F49A8F82_A933_41A8_AF47_68FBCAC4ADA6__INCLUDED_)
