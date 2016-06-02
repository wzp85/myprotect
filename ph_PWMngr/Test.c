#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ph_km.h"



char ip[32]={0x00};

int  ReadData(char * FilePath, unsigned char *FileData, unsigned int * FileDataLen)
{
	FILE *stream=NULL;
	char buf[100]={0};
	int count=0,nLen=0;

	if(NULL==FilePath)
		return -1;

	if(FileData==NULL)
	{
		stream=fopen(FilePath,"rb");
		if(stream==NULL)
			return -1;
		while(!feof(stream))
		{
			count=fread(buf,sizeof(char),100,stream);
			nLen+=count;		
		}
		fclose(stream);
		*FileDataLen =nLen;	
	}
	else
	{
		stream=fopen(FilePath,"rb");
		if(stream==NULL)
			return -1;
		while(!feof(stream))
		{
			count=fread(buf,sizeof(char),100,stream);
			memcpy(FileData+nLen,buf,count);
			nLen+=count;
		}
		fclose(stream);
		*FileDataLen =nLen;	
	}
	return 0;
}
int  WtFile(char * filename, unsigned char* pbData,unsigned int nDataLen)
{	
	FILE *stream;

	if( ( stream = fopen( filename, "wb" ) ) == NULL )
		return -1;
	fwrite(pbData, 1, nDataLen, stream);
	fclose( stream );
	return 0;
}


int main(int argc, char **argv)
{
	int ret=0;
	int i=0;
	void *hSessionHandle=NULL;
	unsigned int uiInitStatus=0;
	int num;

	struct ADMININFO adi;
	
	


	unsigned char pucDevKeyBak[20480]={0x00};
	unsigned int uiDevKeyBakLength=0;

	unsigned char pucAppKeyBak[20480]={0x00};
	unsigned int uiAppKeyBakLength=0;

	unsigned char pucKEKKeyBak[20480]={0x00};
	unsigned int uiKEKKeyBakLength=0;

	for(i=0;i<100;i++)
	{
		printf("\n\n");
		printf("--------------------------Test KM-----------------------------\n");
		printf("\t01、Km_LoginIn                        02、Km_LoginOut \n");
		printf("\t03、Km_CheckInitPasswd                04、Km_ModifyInitPasswd\n");
		printf("                  --------------------------                  \n");
		printf("\t05、Km_GenMainKey                     06、Km_GenKeyProKey\n");
		printf("\t07、Km_GenDevKey                      08、Km_GenAdmin\n");
		printf("                  --------------------------                  \n");
		printf("\t09、Km_GetDevKeyInfo                  10、Km_DevKeyBackup\n");

		printf("\t11、Km_DevKeyRecovery                 12、Km_GenAppKey\n");
		printf("\t13、Km_AppKeyModPasswd                14、Km_AppKeyBackup\n");
		printf("\t15、Km_AppKeyRecovery                 16、Km_AppKeyDestroy\n");

		printf("\t17、Km_AppKeyGetList                  18、Km_GenKeyEncKey\n");
		printf("\t19、Km_KeyEncKeyBackup                20、Km_KeyEncRecovery\n");
		printf("\t21、Km_KeyEncDestroy                  22、Km_KeyEncKeyGetList\n");
		printf("                  --------------------------                  \n");
		printf("\t23、Km_DelAdmin                       24、Km_GetAdminList \n");
		printf("                  --------------------------                  \n");
		printf("\t25、Km_ManagerNetModify               26、Km_AppNetModify \n");
		printf("\t27、Km_NetRestart                     28、Km_GetDeviceInfo\n");
		printf("---------------------------------------------------------------\n");

		printf("Please input your select:\n");
		scanf("%d",&num);

		switch(num)
		{

		case 1:
			{
				printf("Please input the manager IP:\n");	
				scanf("%s",ip);
				if(0==strcmp(ip,"1"))
					strcpy(ip,"127.0.0.1");
				else if(0==strcmp(ip,"2"))
					strcpy(ip,"192.168.1.223");

				ret= Km_LoginIn(&hSessionHandle,ip,1,1,1,(unsigned char *)"root", sizeof("root")-1,
					(unsigned char *)"cntrust123", sizeof("cntrust123")-1,(unsigned char *)"root", sizeof("root")-1);
				printf("Km_LoginIn ret=%08x \n",ret);
			break;
			}
		case 2:
			ret=Km_LoginOut(hSessionHandle);
			printf("Km_LoginOut ret=%08x \n",ret);
			break;


		case 3:
			{
				unsigned char name[32]={0x00};
				unsigned char passwd[32]={0x00};

				printf("Please input your name:\n");				
				scanf("%s",name);

				printf("Please input your passwd:\n");				
				scanf("%s",passwd);

				ret=Km_CheckInitPasswd(&hSessionHandle,ip,name, strlen((char *)name),
					passwd, strlen((char *)passwd),&uiInitStatus);

				printf("Km_CheckInitPasswd ret=%08x uiInitStatus=%d\n",ret,uiInitStatus);
				break;
			}
		case 4:
			{
				unsigned char name[32]={0x00};
				unsigned char oldpasswd[32]={0x00};
				unsigned char newpasswd[32]={0x00};

				printf("Please input your name:\n");
				scanf("%s",name);

				printf("Please input your oldpasswd:\n");			
				scanf("%s",oldpasswd);

				printf("Please input your newpasswd:\n");				
				scanf("%s",newpasswd);

				ret=Km_ModifyInitPasswd (&hSessionHandle,ip,name, strlen((char *)name),
					oldpasswd, strlen((char *)oldpasswd),
					newpasswd, strlen((char *)newpasswd));
				printf("Km_ModifyInitPasswd ret=%08x \n",ret);		
				break;
			}
		case 5:
			ret= Km_GenMainKey(hSessionHandle);
			printf("Km_GenMainKey ret=%08x \n",ret);
			break;

		case 6:
			ret= Km_GenKeyProKey(hSessionHandle,SGD_SM1_ECB);
			printf("Km_GenKeyProKey ret=%08x \n",ret);
			break;

		case 7:
			ret= Km_GenDevKey(hSessionHandle,(unsigned char *)"DevTest",strlen("DevTest"),
				SGD_RSA,1024,(unsigned char *)"1234567a",strlen("1234567a"));

			printf("Km_GenDevKey ret=%08x \n",ret);
			break;

			
		case 8:
			{

				unsigned int uiSignValueLen=0;
				unsigned char pucSignValue[256]={0x00};

				unsigned char pucPubKey[256]={0x01};

				adi.iPaperType=0;
			
				memcpy(adi.ucName,"Test",sizeof("Test"));
				memcpy(adi.ucPaperNum,"410328198906021031",sizeof("410328198906021031"));
				memcpy(adi.ucTelephone,"18321809715",sizeof("18321809715"));

				adi.uiNameLen=sizeof("Test")-1;
				adi.uiPaperNumLen=sizeof("410328198906021031")-1;
				adi.uiTelephoneLen=sizeof("18321809715")-1;

				printf("Please input the uiAdminId:\n");
				scanf("%d",&adi.iAdminId);

				ret= Km_GenAdmin(hSessionHandle,&adi,1,pucPubKey,256,pucSignValue,&uiSignValueLen);

				printf("Km_GenAdmin ret=%08x \n",ret);

				break;
			}
		case 9:
			{
				struct DEVKEYINFO devi;
				memset(&devi ,0x00,sizeof(DEVKEYINFO));
				ret= Km_GetDevKeyInfo(hSessionHandle,&devi);

				printf("备份时间：%s\n设备名称：%s\n算法标识：%d\n密钥长度：%d\n是否备份：%d\n管理员策略%d\\%d\n",devi.ucBakTime,devi.ucDevName,devi.uiAlgo,devi.uiKeyLen,devi.uiIfBak,devi.uiBakTotalKey,devi.uiBakChooseKey);


				printf("Km_GetDevKeyInfo ret=%08x \n",ret);
				break;
			}
		case 10:
			{
			/*	unsigned char pucKeyBackupKey[24]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
			*/	
				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
				unsigned int uiKeyBackupKeyLength=16;

				ret= Km_DevKeyBackup (hSessionHandle,SGD_SM1_ECB,pucKeyBackupKey,uiKeyBackupKeyLength,pucDevKeyBak, &uiDevKeyBakLength);
				WtFile("DevKeyBak",pucDevKeyBak,uiDevKeyBakLength);

				printf("Km_DevKeyBackup ret=%08x uiKeyBakLength=%d\n",ret,uiDevKeyBakLength);
				break;
			}
		case 11:
			{
			/*	unsigned char pucKeyBackupKey[24]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

			*/	
				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

				unsigned int uiKeyBackupKeyLength=16;

				ReadData("DevKeyBak",pucDevKeyBak,&uiDevKeyBakLength);
				ret= Km_DevKeyRecovery (hSessionHandle,SGD_SM1_ECB,(unsigned char *)"1234567a",strlen("1234567a"),pucKeyBackupKey,uiKeyBackupKeyLength,pucDevKeyBak,uiDevKeyBakLength);
				printf("Km_DevKeyRecovery ret=%08x \n",ret);
				break;
			}
		case 12:
			{
				unsigned int keyIndex=0;
				unsigned char passwd[32]={0x00};
				unsigned char keyname[32]={0x00};
				printf("Please input the keyIndex:\n");
				scanf("%d",&keyIndex);

				printf("Please input your passwd:\n");				
				scanf("%s",passwd);
				printf("Please input your keyname:\n");				
				scanf("%s",keyname);

				ret= Km_GenAppKey(hSessionHandle, keyIndex, SGD_RSA ,1024,passwd, strlen((char *)passwd), keyname, strlen((char *)keyname), 2);
				printf("Km_GenAppKey ret=%08x \n",ret);
				break;
			}
		case 13:
			{
				unsigned int keyIndex=0;
				unsigned char oldpasswd[32]={0x00};
				unsigned char newpasswd[32]={0x00};

				printf("Please input the keyIndex:\n");
				scanf("%d",&keyIndex);

				printf("Please input your oldpasswd:\n");			
				scanf("%s",oldpasswd);

				printf("Please input your newpasswd:\n");				
				scanf("%s",newpasswd);

				ret= Km_AppKeyModPasswd(hSessionHandle,keyIndex,oldpasswd, strlen((char *)oldpasswd),newpasswd, strlen((char *)newpasswd));
				printf("Km_AppKeyModPasswd ret=%08x \n",ret);
				break;
			}
		case 14:
			{
				//unsigned char pucKeyBackupKey[24]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
				//								0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
				//								0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
				//unsigned int uiKeyBackupKeyLength=24;

				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

				unsigned int uiKeyBackupKeyLength=16;				

				unsigned int puiKeyIndex[2]={21,22};

				ret= Km_AppKeyBackup(hSessionHandle,SGD_SM1_ECB,2,puiKeyIndex,pucKeyBackupKey, 24,pucAppKeyBak, &uiAppKeyBakLength);
				printf("Km_AppKeyBackup ret=%08x uiKeyBakLength=%d\n",ret,uiAppKeyBakLength);

				WtFile("AppKeyBak",pucAppKeyBak,uiAppKeyBakLength);
				break;
			}
		case 15:
			{
				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

				unsigned int uiKeyBackupKeyLength=16;	

				ReadData("AppKeyBak",pucAppKeyBak,&uiAppKeyBakLength);

				ret= Km_AppKeyRecovery (hSessionHandle,SGD_SM1_ECB,(unsigned char *)"1234567a",strlen("1234567a"),pucKeyBackupKey,uiKeyBackupKeyLength,pucAppKeyBak, uiAppKeyBakLength);
				printf("Km_AppKeyRecovery ret=%08x \n",ret);
				break;
			}
		case 16:{
				unsigned int puiKeyIndex[1]={0};

				printf("Please input the keyIndex:\n");
				scanf("%d",&puiKeyIndex[0]);

				ret= Km_AppKeyDestroy(hSessionHandle,2,puiKeyIndex);
				printf("Km_AppKeyDestroy ret=%08x \n",ret);
				break;
			}
		case 17:{

				unsigned char puiAppKeyList[5120]={0x00};
				unsigned int uiAppKeyListLen=0;
				ret= Km_AppKeyGetList(hSessionHandle,puiAppKeyList,&uiAppKeyListLen);
				printf("puiAppKeyList:\n%s \n",puiAppKeyList);
				printf("Km_AppKeyGetList ret=%08x \n",ret);
				break;
				}
		case 18:
			{
				unsigned int keyIndex=0;
				unsigned char keyname[32]={0x00};

				printf("Please input the keyIndex:\n");
				scanf("%d",&keyIndex);

				printf("Please input your keyname:\n");				
				scanf("%s",keyname);

				ret= Km_GenKeyEncKey(hSessionHandle, keyIndex, SGD_SM1_ECB ,keyname, strlen((char *)keyname));
				printf("Km_GenKeyEncKey ret=%08x \n",ret);
				break;		
			}
		case 19:
			{
				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

				unsigned int uiKeyBackupKeyLength=16;				

				unsigned int puiKeyIndex[2]={21,22};


				ret= Km_KeyEncKeyBackup(hSessionHandle,SGD_SM1_ECB, 2,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKEKKeyBak, &uiKEKKeyBakLength);
				printf("Km_KeyEncKeyBackup ret=%08x uiKEKKeyBakLength=%d\n",ret,uiKEKKeyBakLength);
				WtFile("KEKKeyBak",pucKEKKeyBak,uiKEKKeyBakLength);
				break;
			}
		case 20:
			{
				unsigned char pucKeyBackupKey[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
												0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

				unsigned int uiKeyBackupKeyLength=16;	

				ReadData("KEKKeyBak",pucKEKKeyBak,&uiKEKKeyBakLength);


				ret= Km_KeyEncRecovery (hSessionHandle,SGD_SM1_ECB,pucKeyBackupKey,uiKeyBackupKeyLength,pucKEKKeyBak, uiKEKKeyBakLength);
				printf("Km_KeyEncRecovery ret=%08x \n",ret);
			}
			break;

		case 21:
			{
				unsigned int puiKeyIndex[1]={21};

				printf("Please input the keyIndex:\n");
				scanf("%d",&puiKeyIndex[0]);


				ret= Km_KeyEncDestroy(hSessionHandle,1,puiKeyIndex);
				printf("Km_KeyEncDestroy ret=%08x \n",ret);
				break;
			}
		case 22:
			{
				unsigned char puiKEKeyList[5120]={0x00};
				unsigned int uiKEKeyListLen=0;
				ret= Km_KeyEncKeyGetList(hSessionHandle,puiKEKeyList,&uiKEKeyListLen);
				printf("puiKEKeyList:\n%s \n",puiKEKeyList);
				printf("Km_KeyEncKeyGetList ret=%08x \n",ret);
				break;
			}

		case 23:
			{
				unsigned int keyIndex=0;
				printf("Please input the keyIndex:\n");
				scanf("%d",&keyIndex);

				ret=Km_DelAdmin(hSessionHandle,	keyIndex);
				printf("Km_DelAdmin ret=%08x \n",ret);
				break;
			}
		case 24:
			{
				unsigned char puiAdminList[5120]={0x00};
				unsigned int uiAdminListLen=0;

				ret=Km_GetAdminList(hSessionHandle, puiAdminList,&uiAdminListLen);
				printf("puiAdminList:\n%s \n",puiAdminList);
				printf("Km_GetAdminList ret=%08x \n",ret);
				break;

			}
		case 25:
			{
				char *pNet1="BOOTPROTO=static||ONBOOT=yes||IPADDR=192.168.100.119||NETMASK=255.255.255.0||GETEWAY=192.168.100.254";

				char *pNet2="BOOTPROTO=dhcp";

				ret=Km_ManagerNetModify(hSessionHandle,(unsigned char *)pNet1,strlen(pNet1));
				printf("Km_ManagerNetModify ret=%08x \n",ret);
				break;
			}
		case 26:
			{
				ret=Km_AppNetModify(hSessionHandle,(unsigned char *)"127.0.0.1",sizeof("127.0.0.1"));
				printf("Km_AppNetModify ret=%08x \n",ret);
				break;
			}

		case 27:
			ret=Km_NetRestart(hSessionHandle,0);
			printf("Km_NetRestart ret=%08x \n",ret);
			break;

		case 28:
			{
				DEVICEINFO stDeviceInfo;
				memset(&stDeviceInfo,0x00,sizeof(stDeviceInfo));
				ret=Km_GetDeviceInfo(hSessionHandle,&stDeviceInfo);	

				printf("生产厂商：    %s\n",stDeviceInfo.IssuerName);
				printf("设备型号：    %s\n",stDeviceInfo.DeviceName);
				printf("设备序列号：  %s\n",stDeviceInfo.DeviceSerial);
				printf("设备版本：    V%d\n",stDeviceInfo.DeviceVersion);
				printf("支持标准版本：V%d\n",stDeviceInfo.StandardVersion);
				printf("支持公钥算法：0x%08x|0x%08x\n",stDeviceInfo.AsymAlgAbility[0],stDeviceInfo.AsymAlgAbility[1]);
				printf("支持对称算法：0x%08x\n",stDeviceInfo.SymAlgAbility);
				printf("支持杂凑算法：0x%08x\n",stDeviceInfo.HashAlgAbility);
				printf("用户存储空间：%d\n",stDeviceInfo.BufferSize);

				printf("Km_GetDeviceInfo ret=%08x \n",ret);
				break;
			}

		default:
			TestBase64();
			break;
		}

	}

	return 0;
}