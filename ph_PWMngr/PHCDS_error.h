/**************************************************************
**  �ļ�����
**  Copyright ? 2000  Shanghai XXX Co. Ltd.  ����������
**  All right reserved.
**  �����ˣ�
**  �ա��ڣ�
**  �޸��ˣ�
**  �ա��ڣ�
**  �衡����
**  �桡����
***************************************************************/

#ifndef _PHCDS_ERROR_H
#define _PHCDS_ERROR_H



#define SDR_OK	                                0x00000000

#define SDR_BSAE	                            0x00090000

#define PHCDS_SESSIONHANDLE_CLOSED            	SDR_BSAE+0x00000100  /*���壺����ִ�й����У��ûỰ�Ѿ��رա�*/

#define PHCDS_SESSIONHANDLE_COUNT             	SDR_BSAE+0x00000101  /*���壺�򿪵ĻỰ̫�ࡣ*/

#define PHCDS_SESSIONHANDLE_INVALID           	SDR_BSAE+0x00000102  /*���壺ָ���ĻỰ�����Ч��*/

#define PHCDS_LOGIN_FAILED  		      	SDR_BSAE+0x00000103  /*���壺��ȡ˽Կʹ��Ȩ��ʧ�ܡ�*/

#define PHCDS_LOGIN_REPEAT      	      	SDR_BSAE+0x00000104  /*���壺��ȡ˽Կʹ��Ȩ���ظ���*/

#define PHCDS_NOT_LOGIN       	    	      	SDR_BSAE+0x00000105  /*���壺˽Կʹ��Ȩ��δ��ȡ��*/

#define PHCDS_INPUT_LEN_ERROR                 	SDR_BSAE+0x00000106  /*���壺�����������ָʾ����*/

#define PHCDS_KEYID_INVALID           	      	SDR_BSAE+0x00000107  /*���壺ָ������Կ�ŷǷ���*/

#define PHCDS_ALGID_INVALID                   	SDR_BSAE+0x00000108  /*���壺�㷨��ʶ��Ч��*/

#define PHCDS_NOT_INITIALIZED         	      	SDR_BSAE+0x00000109  /*���壺δ���ó�ʼ����*/

#define PHCDS_ALREADY_INITIALIZED      	   	SDR_BSAE+0x00000110  /*���壺��ʼ���ѵ��á�*/

#define PHCDS_DEVICEHANDLE_INVALID           	SDR_BSAE+0x00000111  /*�豸�����Ч*/

#define PHCDS_OPENDEVICE_ERROR          	SDR_BSAE+0x00000112	/*���豸����*/

#define PHCDS_CLOSEDEVICE_ERROR           	SDR_BSAE+0x00000113	/*�ر��豸����*/

#define PHCDS_OPENSESSION_ERROR           	SDR_BSAE+0x00000114	/*�򿪻Ự����*/

#define PHCDS_CLOSESESSION_ERROR           	SDR_BSAE+0x00000115	/*�رջỰ����*/

#define PHCDS_GenerateRandom_ERROR           	SDR_BSAE+0x00000116	/*�������������*/

#define PHCDS_GenerateKeyPair_RSA_ERROR       	SDR_BSAE+0x00000117  /*����RSA��Կ�Դ���*/

#define PHCDS_ExternalPublicKeyOperation_ERROR  SDR_BSAE+0x00000118 /*�ⲿ��Կ���ܴ���*/

#define PHCDS_ExternalPrivateKeyOperation_ERROR SDR_BSAE+0x00000119 /*�ⲿ˽Կ���ܴ���*/

#define PHCDS_ImportKey_ERROR 			SDR_BSAE+0x00000120 /*�ⲿ����Գ���Կ����*/

#define PHCDS_Encrypt_ERROR			SDR_BSAE+0x00000121  /*�ԳƼ��ܴ���*/

#define PHCDS_Decrypt_ERROR			SDR_BSAE+0x00000122 /*�Գƽ��ܴ���*/

#define PHCDS_CalculateMAC_ERROR		SDR_BSAE+0x00000123 /*MAC�������*/

#define PHCDS_DestoryKey_ERROR			SDR_BSAE+0x00000124 /*�������뿨�ϵĻỰ��Կ����*/

#define  PHCDS_HashInit_ERROR			SDR_BSAE+0x00000125 /*HASH��ʼ������*/

#define  PHCDS_HashUpdate_ERROR			SDR_BSAE+0x00000126 /*HASH�������*/

#define  PHCDS_HashFinal_ERROR			SDR_BSAE+0x00000127 /*HASH�����������*/

#define PHCDS_PARAMETER_INVALID     		SDR_BSAE+0x00000128    /*���壺���������Ч��*/

#define PHCDS_SESSIONLIST_INVALID     		SDR_BSAE+0x00000129 /*���壺SESSION����Ϊ�ա�*/

#define PHCDS_SESSIONID_INVALID     		SDR_BSAE+0x00000130  /*���壺SESSION������û��SESSIONIDָʾ�ĻỰ��*/

#define PHCDS_SESSIONSTAT_INVALID    		SDR_BSAE+0x00000131 /*���壺SESSIONSTAT״̬�쳣����0��1����*/

#define PHCDS_KEYCONTAINER_INVALID   		SDR_BSAE+0x00000132 /*���壺��Կ��������Ϊ�ա�*/

#define PHCDS_KEYRECORD_INVALID     		SDR_BSAE+0x00000133 /*���壺��Կ����������û��ָ������Կ��*/

#define PHCDS_KEYRECORDVALUETYPE_INVALID     	SDR_BSAE+0x00000134 /*���壺��Կ���ݵ�����ֵ��Ч��*/

#define PHCDS_USERKEYLIST_INVALID     		SDR_BSAE+0x00000135  /*���壺��Կ������Կ����Ϊ�ա�*/

#define PHCDS_USERKEY_INVALID     		SDR_BSAE+0x00000136 /*���壺��Կ������Կ������û��ָ������Կ��*/

#define PHCDS_USERKEYVALUETYPE_INVALID     	SDR_BSAE+0x00000137 /*���壺��Կ���ݵ�����ֵ��Ч��*/

#define PHCDS_FILETYPE_INVALID      		SDR_BSAE+0x00000138  //��Ч�ļ�����

#define PHCDS_PARAMNAME_INVALID      		SDR_BSAE+0x00000139 //��Ч��������

#define PHCDS_PARAMNAMELEN_INVALID      	SDR_BSAE+0x00000140 //��Ч�������Ƴ���

#define PHCDS_OPENFILE_ERROR      		SDR_BSAE+0x00000141 //���ļ�ʧ��

#define PHCDS_CREATFILE_ERROR      		SDR_BSAE+0x00000142//�����ļ�ʧ��

#define PHCDS_WRITEFILE_ERROR	  		SDR_BSAE+0x00000143//д�ļ�ʧ��

#define PHCDS_CLOSEFILE_ERROR	   		SDR_BSAE+0x00000144//�ر��ļ�ʧ��

#define PHCDS_FSEEK_ERROR          		SDR_BSAE+0x00000145//�ı��ļ�ָ��ʧ��

#define PHCDS_PAD_ERROR		   		SDR_BSAE+0x00000146 /*�ԳƼӽ��ܲ�λ����*/

#define PHCDS_USEPIN_ERROR			SDR_BSAE+0x00000147  /*�û�PIN����*/

#define PHCDS_KEYTYPE_INVALID   	        SDR_BSAE+0x00000148  /*���壺��Կ������Ч��*/

#define PHCDS_PRIVATEKEY_DECRYPT_ERROR    	SDR_BSAE+0x00000149  /*���壺˽Կ����ʧ�ܡ�*/

#define PHCDS_ERROR_DLL_LOAD_ERROR   		SDR_BSAE+0x00000150    //���ؼ��ܿ���ʧ��

#define PHCDS_MEMALLOC_ERROR  	    		SDR_BSAE+0x00000151     //�ڴ�������

#define PHCDS_DELETE_DIR_ERROR	   		SDR_BSAE+0x00000152//ɾ���ļ�ʧ��

#define PHCDS_EXPORT_KEY_LENGTH_ERROR	   	SDR_BSAE+0x00000153//������Կ�ĳ�������

#define PHCDS_NO_KEY				SDR_BSAE+0x00000154 //�޴���Կ

#define PHCDS_CARD_FLAG_ERROR				   	SDR_BSAE+0x00000155 //���ܿ���ʶ��������

#define PHCDS_NO_CARD_SESSION_ERROR				SDR_BSAE+0x00000156 //û�м��ܿ��Ự

#define PHCDS_SOCKET_SERVER_RECV_ERROR				SDR_BSAE+0x00000157 //������������ݴ���

#define PHCDS_SOCKET_SERVER_PACKET_ERROR				SDR_BSAE+0x00000158 //������������ݴ���

#define PHCDS_SESSIONKEY_INVALID				SDR_BSAE+0x00000159 //�Ự��Կ����

#define PHCDS_CONFIGFILE_INVALID				SDR_BSAE+0x00000160 //�����ļ�����

#define PHCDS_INDATA_MAXDATA				SDR_BSAE+0x00000161 //�����������ֵ

#define PHCDS_SESSIONKEYHANDLE_MAX               SDR_BSAE+0x00000162 //�Ự��Կ����������ֵ

#define PHCDS_NOSUPPORT_ALGID               SDR_BSAE+0x00000163 //��֧�ֵ��㷨

#define PHCDS_HASH_MAXCOUNT               SDR_BSAE+0x00000164 //����hash��

#define PHCDS_AGREEMENTHANDLE_MAX               SDR_BSAE+0x00000165 //Э�̲�������������ֵ

#define PHCDS_KEY_ERROR               SDR_BSAE+0x00000166 //��Կ��ʽ����

#define PHCDS_KEYLENGTH_ERROR               SDR_BSAE+0x00000167 //��Կ���ȴ���

#define PHCDS_LOADKPKEY_ERROR               SDR_BSAE+0x00000168 //װ����Կ������Կ����

#define PHCDS_VERIFYAPPKEY_ERROR            SDR_BSAE+0x00000169 //��Կ����ʱ��֤��Կ����

#endif

