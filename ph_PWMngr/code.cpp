#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef PHLINUX
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <errno.h>
#else
	#include <winsock2.h>
#endif

#include "code.h"

/*------------------------------------管理系统定义------------------------------------------------*/

bool_t int_proc( char *result, int *num, enum x_op op_type )
{
	int n;

	switch (op_type)
	{
		case X_ENCODE:
			n = *num;
			n = htonl(n);
			// bcopy((void *)&n,result,sizeof(int));
			memcpy(result,(void *)&n,sizeof(int));
			break;
		case X_DECODE:
			// bcopy(result,(void *)&n,sizeof(int));
			memcpy((void *)&n,result,sizeof(int));
			*num = ntohl(n);
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

bool_t byte_array_proc( char *result, char *src, int length, enum x_op op_type )
{
	switch (op_type)
	{
		case X_ENCODE:
			// bcopy(src,result,length);
			memmove(result,src,length);
			break;
		case X_DECODE:
			if (result == NULL)
			{
				return FALSE;
			}
			if (src == NULL)
			{
				return FALSE;
			}
			// bcopy(result,src,length);
			memmove(src,result,length);
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

bool_t packet_proc( packetInfo *pkt, char *result, enum x_op op_type )
{
	int n;
	char *p;
	int counter;

	counter = 0;
	p = result;
	switch (op_type)
	{
		case X_ENCODE:
			n = (pkt->packetlen);
			if (!int_proc(p,&n,op_type))
			{
			return FALSE;
			}
			counter = counter + sizeof(int);
			p = result + counter;
			n = (pkt->func_num);
			if (!int_proc(p,&n,op_type))
			{
			return FALSE;
			}      
			break;
		case X_DECODE:
			if (!int_proc(p,&n,op_type))
			{
			return FALSE;
			}
			pkt->packetlen = n;
			counter = counter + sizeof(int);
			p = result + counter;
			if (!int_proc(p,&n,op_type))
			{
			return FALSE;
			}
			pkt->func_num = n;
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

/*------------------------------------管理系统定义------------------------------------------------*/

int packet_len(packetInfo pkt)
{
    int result = 0; 
    result = result + sizeof(int);
    result = result + sizeof(int);
    return result;
}

int PKI_DATA_len(PKI_DATA pki_data)
{
    int result = 0;
    result = result + sizeof(pki_data.size);
    result = result + pki_data.size;
    return result;
}


void PKI_DATA_free(PKI_DATA *pki_data)
{
    if (pki_data == NULL)
    {
        return;
    }
    if (pki_data->value != NULL)
    {
        free(pki_data->value);
        pki_data->value = NULL;
    }   
}

void returnPKI_free(returnPKI *retv)
{
    if (retv == NULL)
    {
        return;
    }
    PKI_DATA_free(&retv->o_outData);
}


bool_t PKI_DATA_proc( PKI_DATA *pki_data, char *result, enum x_op op_type )
{
	int n;
	char *p;
	int counter;

	counter = 0;
	p = result;
	switch(op_type)
	{
		case X_ENCODE:
			n = (pki_data->size);    
			if (!int_proc(p,&n,op_type))    
			{
				return FALSE;
			}
			counter = counter + sizeof(int);
			p = result + counter;
			if (!byte_array_proc(p, (char *)pki_data->value, pki_data->size, op_type))
			{
				return FALSE;
			}
			break;
		case X_DECODE:
			if (!int_proc(p,&n,op_type))
			{
				return FALSE;
			}
			pki_data->size = n;
			counter = counter + sizeof(int);
			p = result + counter;
			if (pki_data->size != 0)
			{
				if (pki_data->value == NULL)
				{
					pki_data->value = (unsigned char *)malloc(pki_data->size);
				}
				if (pki_data->value == NULL)
				{
					return FALSE;
				}
				memset(pki_data->value,0,pki_data->size);

				if (!byte_array_proc(p,(char *)pki_data->value,pki_data->size,op_type))
				{
					return FALSE;
				}
			}
			else
			{
				pki_data->size = 0;
				pki_data->value = NULL;
			}
			break;
		default:
			return FALSE;
	}    
	return TRUE;
}

bool_t returnPKI_proc( returnPKI *retv, char *result, enum x_op op_type, int validata_len )
{
	int n;
	char *p;
	int counter ;

	p = result;
	counter = 0;

	switch (op_type)
	{
		case X_ENCODE:
			//------------------------------------------
			//For member (int  status)
			n=(retv->status);
			if (!int_proc(p,&n,op_type))
			{				
				return FALSE;
			}
			counter = counter + sizeof(int);
			p = result + counter;
			//-----------------------------------------
			//For member (struct PKI_DATA  o_outData)
			if (!PKI_DATA_proc(&retv->o_outData,p,op_type))
			{
				return FALSE;
			}
			break;
		case X_DECODE:
			//------------------------------------------
			//For member (int  status)
			if (!int_proc(p,&n,op_type))
			{				
				return FALSE;
			}
			retv->status = n;
			counter = counter + sizeof(int);
			p = result + counter;
			//-----------------------------------------
			//For member (struct PKI_DATA  o_outData)
			memset( &retv->o_outData, 0, sizeof(retv->o_outData) );
			if (!PKI_DATA_proc(&retv->o_outData,p,op_type))
			{
				
				return FALSE;
			}
			break;
		default:
			return FALSE;   
	}
	return TRUE;
}

/*------------------------------------管理系统定义------------------------------------------------*/

int data_proc_len(void *retv,enum d_op *op_list,int op_num)
{
	int i=0;
	int add=0;
	int counter = 0;

	if (retv == NULL)
    {
        return 0;
    }	

	for(i=0;i<op_num;i++)
	{
		if(op_list[i]==D_INT)
		{
			
			counter = counter +sizeof(int);
			add = add +sizeof(int);
		}
		else if(op_list[i]==D_CHAR_LEN)
		{

			counter = counter +(*(int *)((int)retv+add));
			counter = counter +sizeof(int);
			
			add = add +sizeof(int);
			add = add +sizeof(unsigned char *);

		}	
		else if(op_list[i]==D_INT_LEN)
		{

			counter = counter +(*(int *)((int)retv+add))*sizeof(int);
			counter = counter +sizeof(int);
			
			add = add +sizeof(int);
			add = add +sizeof(int *);

		}
	}

	return counter;

}

void data_proc_free(void *argv ,enum d_op *op_list,int op_num)
{
	int i=0;
	int counter = 0;
	char *p=NULL;
	int *pint;
	if (argv == NULL)
    {
        return;
    }	

	for(i=0;i<op_num;i++)
	{
		if(op_list[i]==D_INT)
		{
			counter = counter +sizeof(int);
		}
		else if(op_list[i]==D_CHAR_LEN)
		{
			counter = counter +sizeof(int);

			p=(char *)(*(int *)((int)argv+counter));

			free(p);

			counter = counter +sizeof(unsigned char *);
		}
		else if(op_list[i]==D_INT_LEN)
		{
			counter = counter +sizeof(int);

			pint=(int *)(*(int *)((int)argv+counter));

			free(pint);

			counter = counter +sizeof(int *);
		}
	}

	return ;

}

bool_t data_proc(void *argv ,char * result,enum x_op op_type,enum d_op *op_list,int op_num)
{
	int n,m;
	int i,j;
	char *p;
	
	int add=0;
	int counter=0;

	p = result;

	switch (op_type)
	{
		case X_ENCODE:
			for(i=0;i<op_num;i++)
			{
				if(op_list[i]==D_INT)
				{
					n=*(int *)((int)argv+add);
					if (!int_proc(p,&n,op_type))
					{ 
						return FALSE;
					}
					add = add + sizeof(int);
					counter = counter + sizeof(int);					
					p = result + counter;				
				
				
				}
				else if(op_list[i]==D_CHAR_LEN)
				{
					n=*(int *)((int)argv+add);
					if (!int_proc(p,&n,op_type))
					{ 
						return FALSE;
					}
					add = add + sizeof(int);
					counter = counter + sizeof(int);
					p = result + counter;				
				
			
					if (!byte_array_proc(p,(char *)(*(int *)((int)argv+add)),n,op_type))
					{
						return FALSE;
					}
					add = add + sizeof(char *);
					counter = counter + n;
					p = result + counter;				
				
				
				}else if(op_list[i]==D_INT_LEN)
				{
					n=*(int *)((int)argv+add);
					if (!int_proc(p,&n,op_type))
					{ 
						return FALSE;
					}
					add = add + sizeof(int);
					counter = counter + sizeof(int);
					p = result + counter;	

					for(j=0;j<n;j++ )
					{
						if (!int_proc(p,(int *)(*(int *)((int)argv+add)+j*sizeof(int)),op_type))
						{ 
							return FALSE;
						}
						
						counter = counter + sizeof(int);					
						p = result + counter;					
					}
					add = add + sizeof(int);
				
				}		
			}

			break;
		case X_DECODE:  

			for(i=0;i<op_num;i++)
			{
				if(op_list[i]==D_INT)
				{
					if (!int_proc(p,&n,op_type))
					{
						return FALSE;
					}

					*(int *)((int)argv+add) = n;

					add = add + sizeof(int);
					counter = counter + sizeof(int);
					p = result + counter;
				}
				else if(op_list[i]==D_CHAR_LEN)
				{
					if (!int_proc(p,&n,op_type))
					{
						return FALSE;
					}

					*(int *)((int)argv+add) = n;

					add = add + sizeof(int);
					counter = counter + sizeof(int);
					p = result + counter;


					if ( ( *(char **)((int)argv+add) = (char *)calloc(n+1,sizeof(char)) ) ==NULL)
					{
						return FALSE;
					}
					if (!byte_array_proc(p,*(char **)((int)argv+add),n,op_type))
					{
						return FALSE;
					}

					add = add + sizeof(char *);
					counter = counter + n;
					p = result + counter;				
				}	
				else if(op_list[i]==D_INT_LEN)
				{
					if (!int_proc(p,&n,op_type))
					{
						return FALSE;
					}

					*(int *)((int)argv+add) = n;

					add = add + sizeof(int);
					counter = counter + sizeof(int);
					p = result + counter;


					if ( ( *(int **)((int)argv+add) = (int *)calloc(n+1,sizeof(int)) ) ==NULL)
					{
						return FALSE;
					}
					for(j=0;j<n;j++)
					{
						if (!int_proc(p,&m,op_type))
						{
							return FALSE;
						}
						*(int *)(*(int *)((int)argv+add)+j*sizeof(int))=m;
						
						counter = counter + sizeof(int);
						p = result + counter;				
					}
					add = add + sizeof(int);
				
				}

			}

			break;

		default:
			return FALSE;   
	}
	return TRUE;



}

//int Write2File(char * filename, unsigned char* pbData,unsigned int nDataLen)
//{	
//	FILE *stream;
//	if( ( stream = fopen( filename, "wb" ) ) == NULL )
//		return -1;
//	stream = fopen( filename, "wb" );
//	fwrite(pbData, 1, nDataLen, stream);
//	fclose( stream );
//	return 0;
//}


/*------------------------------------管理系统定义------------------------------------------------*/


long int encode( char *src,long int src_len, char *dst)  
{  
           
    long int i = 0, j = 0;  
           
    char base64_map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
           
    for (; i < src_len - src_len % 3; i += 3) {  
           
        dst[j++] = base64_map[(src[i] >> 2) & 0x3F];  
           
        dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];  
       
        dst[j++] = base64_map[((src[i + 1] << 2) & 0x3C) + ((src[i + 2] >> 6) & 0x3)];  
       
        dst[j++] = base64_map[src[i + 2] & 0x3F];  
    }  
           
    if (src_len % 3 == 1) {  
           
        dst[j++] = base64_map[(src[i] >> 2) & 0x3F];  
           
        dst[j++] = base64_map[(src[i] << 4) & 0x30];  
           
        dst[j++] = '=';  
           
        dst[j++] = '=';  
           
    }else if (src_len % 3 == 2) {  
           
        dst[j++] = base64_map[(src[i] >> 2) & 0x3F];  
           
        dst[j++] = base64_map[((src[i] << 4) & 0x30) + ((src[i + 1] >> 4) & 0xF)];  
           
        dst[j++] = base64_map[(src[i + 1] << 2) & 0x3C];  
           
        dst[j++] = '=';  
           
    }  
         
    printf("Encode length: %d\n",j);  
    return j;  
           
}   

long int decode(char *src, long int src_len, char *dst)  
{  
    
    long    int i = 0, j = 0;  
       
    unsigned char base64_decode_map[256] = {  

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62,  255, 255, 255, 63,

		52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  255, 255, 255, 255, 255, 255,

		255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,

		15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  255, 255, 255, 255, 255,

		255, 26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,

		41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  255, 255, 255, 255, 255

	};  

    for (; i < src_len - 4; i += 4) {  
           
        dst[j++] = base64_decode_map[src[i]] << 2 |  
               
            base64_decode_map[src[i + 1]] >> 4;  
           
        dst[j++] = base64_decode_map[src[i + 1]] << 4 |  
               
            base64_decode_map[src[i + 2]] >> 2;  
           
        dst[j++] = base64_decode_map[src[i + 2]] << 6 |  
               
            base64_decode_map[src[i + 3]];  
           
    } 

    dst[j++] = base64_decode_map[src[i]] << 2 |  
               
		base64_decode_map[src[i + 1]] >> 4;  
		
		
	if(src[i + 2] != '='){

		dst[j++] = base64_decode_map[src[i + 1]] << 4 |  
               
			base64_decode_map[src[i + 2]] >> 2;  
           
	}

	if(src[i + 3] != '='){

        dst[j++] = base64_decode_map[src[i + 2]] << 6 |  
               
            base64_decode_map[src[i + 3]];  
           
	}

    printf("Decode length: %d\n",j);  
    return j;  
               
}  

void Transform(char * pdata, int len)
{
	int k=0;

	int i=0, j=len-1;

	char temp=0;

	while (i<j)
	{
		temp=pdata[i];
		pdata[i]=pdata[j];
		pdata[j]=temp;
		i++;	
		j--;
	}


	//每位与当前位置异或
	for(k=0;k<len;k++)
	{
		pdata[k]^=k;
	}

}