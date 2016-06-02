#ifndef _MISC_H_
#define _MISC_H_

#include <time.h>
#include "code.h"


int socket_conn( char *hostName, int port, int *sockfd );
int socket_send( int sockfd, char *argV, int len );
int socket_recv( int sockfd, char *argR, int len );
int socket_close( int sockfd );

int call_require( int conn_fd, char *send_data, packetInfo *pkt );
int call_response_header( int conn_fd, unsigned int *precv_datalen );
int call_response_data( int conn_fd, unsigned int recv_datalen, char *recv_data );

#endif
