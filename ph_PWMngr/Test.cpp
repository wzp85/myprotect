#include <stdlib.h>
#include <stdio.h>
#include "ph_km.h"


int main(int argc, char **argv)
{
	int ret=0;
	int i=0;
	void *hSessionHandle=NULL;
	unsigned int uiInitStatus=0;
	for(i=0;i<100;i++)
	{
		system("pause");
/*
		ret=Km_CheckInitPasswd(&hSessionHandle,"127.0.0.1",(unsigned char *)"root", sizeof("root")-1,
			(unsigned char *)"cntrust123", sizeof("cntrust123")-1,&uiInitStatus);

		printf("Km_CheckInitPasswd ret=%d uiInitStatus=%d\n",ret,uiInitStatus);
*/
		


		ret=Km_ModifyInitPasswd (&hSessionHandle,"192.168.1.228",(unsigned char *)"root",sizeof("root")-1,
			(unsigned char *)"cntrust123", sizeof("cntrust123")-1,
			(unsigned char *)"cntrust132", sizeof("cntrust132")-1);
		printf("Km_ModifyInitPasswd ret=%d \n",ret);
		

		ret= Km_GenMainKey(hSessionHandle);
	}
	return 0;
}