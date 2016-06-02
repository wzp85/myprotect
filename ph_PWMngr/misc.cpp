#include <stdlib.h>
#include <stdio.h>

#ifdef PHLINUX
	#include <sys/types.h>
	#include <sys/socket.h>
    #include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <asm/ioctls.h>
#else
	#include <winsock2.h>
	#include <windef.h>
#endif

#include <time.h>
#include "Km_Error.h"
#include "misc.h"

#define TIME 6

/*----------------------------------------------------------------------------------------*/
int socket_conn( char *hostName, int port, int *sockfd )
{
    int ret;
	unsigned long ul = 1;
	
	fd_set fds,rfds;
	struct timeval timeout ;

#ifdef PHLINUX
	int flags;
#endif	


#ifndef PHLINUX
	
	int err;
	WORD wVersionRequested;
	
	struct WSAData wsaData;
#endif

    struct sockaddr_in server_addr;
    
    if(hostName == NULL)
    {        
        return SDR_NULLHOSTNAME;
    }
	
#ifndef PHLINUX
	wVersionRequested = MAKEWORD( 1, 1 );	
	err = WSAStartup( wVersionRequested, &wsaData );	
	if ( err != 0 )
	{		
		return -1;		
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||		
		HIBYTE( wsaData.wVersion ) != 1 )		
	{		
		WSACleanup( );		
		return 0;		
	}
	
	err = WSAStartup( 0x0202, &wsaData );	
	if ( err != 0 )
	{
		return -1;
	}
#endif		
	
	
	*sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( *sockfd == -1 )
	{
#ifdef PHLINUX
		printf("Socket errno:%d,Error info:%s\a\n",errno, strerror(errno));
#else
		printf("connect error hostname = %s,ret=%d\n",hostName,WSAGetLastError());
#endif	
        
        return SDR_SOCKETCREAT;
    }

   // bzero(&server_addr, sizeof(server_addr));
#ifdef PHLINUX
	bzero(&server_addr, sizeof(server_addr));
#else
	memset(&server_addr,0,sizeof(server_addr));
#endif
	
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
	
	//printf("inet_adde------------%s\n",hostName);
#ifdef PHLINUX
    if(inet_aton(hostName, &server_addr.sin_addr) == 0)
    {
        return SDR_GETHOSTNAME;
    }
#else
    if(inet_addr(hostName) == 0)
    {
        return SDR_GETHOSTNAME;
    }

	server_addr.sin_addr.S_un.S_addr=inet_addr(hostName);
#endif


	//������ģʽ
#ifdef PHLINUX
	flags  = fcntl(*sockfd,F_GETFL,0);
    ret = fcntl(*sockfd,   F_SETFL,   flags   |   O_NONBLOCK);
#else
	ret = ioctlsocket(*sockfd, FIONBIO, (unsigned long*)&ul);
#endif



	printf("��ʼ���ӹ���ϵͳ����� ���Ӷ˿� =%d\n",port);

	//���ﲻ��Ҫ�ж�connect�����ķ���ֵ
	//�ڷ�����ģʽ��ret����ֵ����-1
    ret = connect( *sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr) );


	FD_ZERO(&fds);

	FD_ZERO(&rfds);
	
	FD_SET(*sockfd, &fds);
	FD_SET(*sockfd, &rfds);

	timeout.tv_sec = TIME;		//���ӳ�ʱʱ��
	timeout.tv_usec =0;


	ret = select(*sockfd+1,&rfds, &fds, NULL, &timeout);
	if( ret == -1|| ret==0)		//0������ʱ��-1��������
    {
        socket_close(*sockfd);
        return SDR_SOCKETCONN;
    }


	//�ж������Ƿ������ɹ� added by gxj at 2013.06.09 
	if (FD_ISSET(*sockfd,&fds)  &&  FD_ISSET(*sockfd,&rfds))
    {
        socket_close(*sockfd);
        return SDR_SOCKETCONN;
    }
	//added end



	//����ģʽ
#ifdef PHLINUX
	flags  = fcntl(*sockfd,F_GETFL,0);
    ret = fcntl(*sockfd,F_SETFL,flags&~O_NONBLOCK);	
#else
	ul = 0;
	ret = ioctlsocket(*sockfd, FIONBIO, (unsigned long*)&ul);
#endif
    if( ret == -1 )
    {  
#ifdef PHLINUX
		printf("Socket connect errno:%d,Error info:%s\a\n",errno, strerror(errno));
#else
		printf("connect error hostname= %s ,ret=%d\n",hostName,WSAGetLastError());
#endif		
        socket_close(*sockfd);
        return SDR_SOCKETCONN;
    }
    return ret;
}

/*----------------------------------------------------------------------------------------*/
int socket_send( int sockfd, char *argV, int len )
{
    char  *buf;
    int sendLen, sendBytes;
	int nNodelay;
    buf = argV;
    sendLen = len;

	nNodelay = 1 ;

	//----------------ȷ������ͨ�Ų������Ĵ�������-----------------

	Transform(argV,len);

	//----------------ȷ������ͨ�Ų������Ĵ�������-----------------

	setsockopt(sockfd,IPPROTO_TCP,1,(const char*)&nNodelay,sizeof(int));   //���ò�������SOCKETÿ��ҵ�����ݰ����з��ͣ��ӿ�ͨѶ�ٶ�

    while( sendLen > 0 )
    {
        sendBytes = send( sockfd, buf, sendLen, 0 );
        if( sendBytes <= 0 )
        {
#ifdef PHLINUX
			printf("Socket send errno:%d,Error info:%s\a\n",errno, strerror(errno));
#else
			printf("socket_send error code=%d\n",WSAGetLastError());
#endif
			return SDR_SOCKETSEND;
        }
        buf += sendBytes;
        sendLen -= sendBytes;
    }
    return SDR_OK;
}

/*----------------------------------------------------------------------------------------*/
int socket_recv( int sockfd, char *argR, int len )
{
	int ret=0;
    char *buf=NULL;
    int recvLen=0, recvBytes=0;


    buf = argR;
    recvLen = len;

    while( recvLen > 0 )
    {

        recvBytes = recv( sockfd, buf, recvLen, 0 );

//		printf("recv sockfd==%d len ==%d recvBytes ==%d\n",sockfd,len,recvBytes);

        if( recvBytes <= 0 )
        {
#ifdef PHLINUX
		printf("Socket recv errno:%d,Error info:%s\a\n",errno, strerror(errno));
#else
		printf("socket recv error code=%d\n",WSAGetLastError());
#endif
            return SDR_SOCKETRECV;
        }
        buf += recvBytes;
        recvLen -= recvBytes;
    }

	//----------------������������ת��Ϊ����-----------------

	Transform(argR,len);

	//----------------������������ת��Ϊ����-----------------
    return SDR_OK;
}

/*----------------------------------------------------------------------------------------*/
int socket_close( int sockfd )
{
#ifdef PHLINUX
	close(sockfd);
#else	
	closesocket(sockfd);
#endif
	
    return SDR_OK;
}

/*----------------------------------------------------------------------------------------*/
int call_require( int conn_fd, char *send_data, packetInfo *pkt )
{
    int pkt_len;
    char *p;
    int ret;

    pkt_len = packet_len(*pkt);
    p = (char *)malloc(pkt_len);
    if ( p == NULL )
    {
        return SDR_MEMALLOC;
    }
    // Encode HeadInfo
    if (!packet_proc(pkt, p, X_ENCODE))
    {
        free(p);
        p = NULL;
        return SDR_HEADENCODE;
    }
    // Send HeadInfo
    ret = socket_send( conn_fd, p, pkt_len );
    if ( ret != 0 )
    {
        goto End;
    }
	
	// Send DataInfo
    ret = socket_send( conn_fd,send_data, pkt->packetlen );
    if ( ret != 0 )
    {
        goto End;
    }
End:
    free(p);
    p = NULL;
    return ret;
}

/*----------------------------------------------------------------------------------------*/
int call_response_header( int conn_fd, unsigned int *precv_datalen )
{
    int pkt_len=0;
    packetInfo pkt;
    char *p;
    int ret;
    char *recv_data;
	
	//printf("socket_recv HeadInfo ");

    recv_data = NULL;

	pkt.func_num = 0;
	pkt.packetlen = 0;
    pkt_len = packet_len(pkt);
    p = (char *)malloc(pkt_len);
    if ( p == NULL )
    {
        return SDR_MEMALLOC;
    }

    // Recv HeadInfo
    ret = socket_recv( conn_fd, p, pkt_len );
    if ( ret == 0 )
    {
        // Decode HeadInfo
        if ( !packet_proc(&pkt,p,X_DECODE) )
        {
            free(p);
            p = NULL;
            return SDR_HEADDECODE;
        }
		
		*precv_datalen=pkt.packetlen;
	}
    if ( p != NULL )
    {
        free(p);
        p = NULL;
    }
    return ret;
}

/*----------------------------------------------------------------------------------------*/
int call_response_data( int conn_fd, unsigned int recv_datalen, char *recv_data )
{
    // Recv RespData
	printf("socket_recv DataInfo ");
    return socket_recv( conn_fd, recv_data, recv_datalen );

}