// CACertAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "CACertAdd.h"
#include "afxdialogex.h"

#include "MyUtil.h"
#include "ph_km.h"
// CCACertAdd �Ի���

IMPLEMENT_DYNAMIC(CCACertAdd, CDialogEx)

//BOOL isVS1;
//BOOL isVS2;
//BOOL isVS3;
//BOOL isVS4;
//BOOL isVS5;
//BOOL isVS6;
unsigned int type_VS = 0x00000;//------0x00001��ʾ����1,0x00011��ʾͬʱ���ò���1��2��������
CCACertAdd::CCACertAdd(void *handle,int isUp,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCACertAdd::IDD, pParent)
	, m_CAADD_certName_cs(_T(""))
	, m_CAADD_certAlg_cs(_T(""))
	, m_CAADD_certIndex_cs(_T(""))
	, m_CAADD_atName_cs(_T(""))
	, m_CAADD_hostName(_T(""))
	, m_CAADD_phone_cs(_T(""))
	, m_CA_certImp_cs(_T(""))
	, m_CA_truchain_Imp_cs(_T(""))
	, m_rootCert_CAA(_T(""))
{
	phHandle_CACertAdd = handle;
	isUp_CA = isUp;
}

CCACertAdd::CCACertAdd(void *handle,int isUp,unsigned int uiRtCertType,unsigned int uiRtCertIndex,CString ca_index,VerifyPriorityStrategy vs,CString index,CString name,CString algId,CString atName,CString hostName,CString hostPhone,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCACertAdd::IDD, pParent)
	, m_CAADD_certName_cs(_T(""))
	, m_CAADD_certAlg_cs(_T(""))
	, m_CAADD_certIndex_cs(_T(""))
	, m_CAADD_atName_cs(_T(""))
	, m_CAADD_hostName(_T(""))
	, m_CAADD_phone_cs(_T(""))
	, m_CA_certImp_cs(_T(""))
	, m_CA_truchain_Imp_cs(_T(""))
	, m_rootCert_CAA(_T(""))
	//, m_CaCertSeriNum_CS(_T(""))
	, m_CaAdd_index_CS(_T(""))
	
	, m_VS1_priority(_T(""))
	, m_VS2_priority(_T(""))
	, m_VS3_priority(_T(""))
	, m_VS4_priority(_T(""))
	, m_VS5_priority(_T(""))
{
	phHandle_CACertAdd = handle;
	isUp_CA = isUp;

	index_rt_forshow = uiRtCertIndex;
	rt_type = uiRtCertType;
	index_ca_fordel = index;

	m_CAADD_certName_cs = name;
	m_CAADD_certAlg_cs = algId;
	m_CAADD_certIndex_cs = ca_index;
	m_CAADD_atName_cs = atName;
	m_CAADD_hostName = hostName;
	m_CAADD_phone_cs = hostPhone;


	CApvs.option = 0x00000;
	CApvs.CRLhandLen = 100;
	CApvs.CRLhand = (unsigned char*)calloc(CApvs.CRLhandLen,sizeof(unsigned char));
	CApvs.autoCRLipLen = 100;
	CApvs.autoCRLip = (unsigned char*)calloc(CApvs.autoCRLipLen,sizeof(unsigned char));
	CApvs.autoCRLportLen = 100;
	CApvs.autoCRLport = (unsigned char*)calloc(CApvs.autoCRLportLen,sizeof(unsigned char));
	/*vs.autoCRLnameLen = 10;
	vs.autoCRLname = (unsigned char *)calloc(vs.autoCRLnameLen,sizeof(unsigned char));
	vs.autoCRLpwdLen = 10;
	vs.autoCRLpwd = (unsigned char *)calloc(vs.autoCRLpwdLen,sizeof(unsigned char));*/
	CApvs.autoCRLurlLen = 100;
	CApvs.autoCRLurl = (unsigned char*)calloc(CApvs.autoCRLurlLen,sizeof(unsigned char));
	CApvs.autoFromHTTPurlLen = 100;
	CApvs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen,sizeof(unsigned char));
	CApvs.OCSPipLen = 100;
	CApvs.OCSPip = (unsigned char*)calloc(CApvs.OCSPipLen,sizeof(unsigned char));
	CApvs.OCSPprotLen = 100;
	CApvs.OCSPport = (unsigned char*)calloc(CApvs.OCSPprotLen,sizeof(unsigned char));
	CApvs.OCSPurlLen = 100;
	CApvs.OCSPurl =(unsigned char*)calloc(CApvs.OCSPurlLen,sizeof(unsigned char));
	CApvs.OCSPverifyLen = 100;
	CApvs.OCSPverify = (unsigned char*)calloc(CApvs.OCSPverifyLen,sizeof(unsigned char));
	//---------------------------------
	CApvs = vs;





}

CCACertAdd::~CCACertAdd()
{
}

void CCACertAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAADD_CERTNAME_EDIT, m_CAADD_certName_cs);
	DDX_CBString(pDX, IDC_COMBO_CAADD_ALG, m_CAADD_certAlg_cs);
	DDX_Control(pDX, IDC_COMBO_CAADD_ALG, m_CAADD_certAlg);
	DDX_Text(pDX, IDC_CAADD_CERTINDEX_EDIT, m_CAADD_certIndex_cs);
	DDX_Text(pDX, IDC_CAADD_ATNAME_EDIT, m_CAADD_atName_cs);
	DDX_Text(pDX, IDC_CAADD_HOST_EDIT, m_CAADD_hostName);
	DDX_Text(pDX, IDC_CAADD_PHONE_EDIT, m_CAADD_phone_cs);
	DDX_Text(pDX, IDC_CAADD_IMCAPATH_EDIT, m_CA_certImp_cs);
	DDX_Text(pDX, IDC_CAADD_TRUCHAINPATH_EDIT, m_CA_truchain_Imp_cs);
	DDX_Text(pDX, IDC_EDIT_VS1, m_VS1_priority);
	DDX_Text(pDX, IDC_EDIT_VS2, m_VS2_priority);
	DDX_Text(pDX, IDC_EDIT_VS3, m_VS3_priority);
	DDX_Text(pDX, IDC_EDIT_VS4, m_VS4_priority);
	DDX_Text(pDX, IDC_EDIT_VS5, m_VS5_priority);


	DDX_CBString(pDX, IDC_COMBO_CAADD_ROOTCERT, m_rootCert_CAA);
	DDX_Control(pDX, IDC_COMBO_CAADD_ROOTCERT, m_rootCert_choseCAA);
	DDX_Control(pDX, IDC_CAADD_CERTINDEX1_COMBO1, m_CaAdd_index_CCobox);
	DDX_CBString(pDX, IDC_CAADD_CERTINDEX1_COMBO1, m_CaAdd_index_CS);
	DDX_Control(pDX, IDC_CHECK_VS1, m_check1);
	DDX_Control(pDX, IDC_CHECK_VS2, m_check2);
	DDX_Control(pDX, IDC_CHECK_VS3, m_check3);
	DDX_Control(pDX, IDC_CHECK_VS4, m_check4);
	DDX_Control(pDX, IDC_CHECK_VS5, m_check5);
	DDX_Control(pDX, IDC_CHECK_VS6, m_check6);
	DDX_Control(pDX, IDC_EDIT_VS1, m_VS1_CN);
	DDX_Control(pDX, IDC_EDIT_VS2, m_VS2_CN);
	DDX_Control(pDX, IDC_EDIT_VS3, m_VS3_CN);
	DDX_Control(pDX, IDC_EDIT_VS4, m_VS4_CN);
	DDX_Control(pDX, IDC_EDIT_VS5, m_VS5_CN);
}


BEGIN_MESSAGE_MAP(CCACertAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCACertAdd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCACertAdd::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_IMCA_BUTTON, &CCACertAdd::OnBnClickedImcaButton)
	ON_BN_CLICKED(IDC_IMTRUCHAIN_BUTTON, &CCACertAdd::OnBnClickedImtruchainButton)
	ON_BN_CLICKED(IDC_CHECK_VS1, &CCACertAdd::OnBnClickedCheckVs1)
	ON_BN_CLICKED(IDC_CHECK_VS2, &CCACertAdd::OnBnClickedCheckVs2)
	ON_BN_CLICKED(IDC_CHECK_VS3, &CCACertAdd::OnBnClickedCheckVs3)
	ON_BN_CLICKED(IDC_CHECK_VS4, &CCACertAdd::OnBnClickedCheckVs4)
	ON_BN_CLICKED(IDC_CHECK_VS5, &CCACertAdd::OnBnClickedCheckVs5)
	ON_BN_CLICKED(IDC_CHECK_VS6, &CCACertAdd::OnBnClickedCheckVs6)
END_MESSAGE_MAP()


// CCACertAdd ��Ϣ�������
BOOL CCACertAdd::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
    {
		if(GetFocus()->GetDlgCtrlID()==IDOK)//���»س��������ǰ���������Լ������Ŀؼ���
        {                                           
            CCACertAdd::OnBnClickedOk();//����Լ��Ĵ������
        }
		if(GetFocus()->GetDlgCtrlID()==IDCANCEL)//���»س��������ǰ���������Լ������Ŀؼ���
        {                                           
            CCACertAdd::OnBnClickedCancel();//����Լ��Ĵ������
        }
        return TRUE; 
	}
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CCACertAdd::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = 0;
	UpdateData(TRUE);
	if(m_CAADD_certName_cs.IsEmpty())
	{
		MessageBox("������֤�����ƣ�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(m_CAADD_certName_cs.GetLength()>50)
	{
		MessageBox("֤������̫���ˣ�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(m_CAADD_certIndex_cs.IsEmpty())
	{
		MessageBox("֤�����кŲ���Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_certIndex_cs.GetLength()>32)
	{
		MessageBox("֤�����к��������32λ������","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_atName_cs.IsEmpty())
	{
		MessageBox("�������Ʋ���Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_atName_cs.GetLength()>40)
	{
		MessageBox("�����������Ϊ20�����֣�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_hostName.IsEmpty())
	{
		MessageBox("��ϵ�˲���Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_hostName.GetLength()>20)
	{
		MessageBox("���������ϵ������̫���ˣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_phone_cs.IsEmpty())
	{
		MessageBox("��ϵ�绰����Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_CAADD_phone_cs.GetLength()>20)
	{
		MessageBox("�绰����̫���ˣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	
	if(m_CA_certImp_cs.IsEmpty())
	{
		MessageBox("�뵼����ӦCA֤�飡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}

	if(m_rootCert_CAA.IsEmpty())
	{
		MessageBox("��ѡ���֤�飡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	
	//������Ϣ������ȡ
	void *hSessionHandle;
	hSessionHandle = phHandle_CACertAdd;
	unsigned int uiRtCertIndex;
	unsigned int uiRtCertType;
	unsigned int uiCACertIndex;
	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	unsigned int uiCertIndexLength;
	unsigned char putCertIndex[32]={0x00};
	unsigned int uiCertNameLength;
	unsigned char pucCertName[50]={0x00};
	unsigned int uiAtNameLength;
	unsigned char pucAtName[50]={0x00};
	unsigned int uiHostLength;
	unsigned char pucHost[32]={0x00};
	unsigned int uiPhoneLength;
	unsigned char pucPhone[32]={0x00};
	unsigned int uiCACertLength=0;
	unsigned char *pucCACert=NULL;
	unsigned int uiTrustChainLength=0;
	unsigned char *pucTrustChain=NULL;
	VerifyPriorityStrategy vs;//----------------�����ȼ���CA������֤�ṹ��

	if(!isUp_CA)
	{
		unsigned int ind_ca = atoi((LPSTR)(LPCTSTR)index_ca_fordel);
		ret = Sig_CACertDel(hSessionHandle,1,&ind_ca);
		if(0 != ret)
		{
			char outAkd[100]={0x00};
			retValueParse(ret,outAkd);
			MessageBox("ɾ��ʧ��"+(CString)outAkd,"��ʾ");
			this->OnCancel();
			return;
		}
	}


	if(m_CAADD_certAlg_cs == "SM2 256")
	{
		uiAlgo = SGD_SM2_1;
		uiKeyLength = 256;
	}
	if(m_CAADD_certAlg_cs == "RSA 1024")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 1024;
	}
	if(m_CAADD_certAlg_cs == "RSA 2048")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 2048;
	}

	char indexBuf[32]={0x00};
	if(m_rootCert_CAA != "ϵͳ��δ�����֤�飡")
		memcpy(indexBuf,m_rootCert_CAA.GetBuffer(),1);
	uiRtCertIndex = atoi(indexBuf);//notice
	char typeBuf[32] = {0x00};
	//1_RtCert.cer_RSA1024
	memcpy(typeBuf,m_rootCert_CAA.GetBuffer(),12);
	if(strstr(typeBuf+2,"RtCert")!=NULL)
	{
		uiRtCertType = 1;
	}
	if(strstr(typeBuf+2,"CaCert")!=NULL)
	{
		uiRtCertType = 2;
	}



	uiCertIndexLength = m_CAADD_certIndex_cs.GetLength();
	memcpy(putCertIndex,m_CAADD_certIndex_cs.GetBuffer(),m_CAADD_certIndex_cs.GetLength());//notice

	uiCertNameLength = m_CAADD_certName_cs.GetLength();
	memcpy(pucCertName,m_CAADD_certName_cs.GetBuffer(),m_CAADD_certName_cs.GetLength());

	uiAtNameLength = m_CAADD_atName_cs.GetLength();
	memcpy(pucAtName,m_CAADD_atName_cs.GetBuffer(),m_CAADD_atName_cs.GetLength());

	uiHostLength = m_CAADD_hostName.GetLength();
	memcpy(pucHost,m_CAADD_hostName.GetBuffer(),m_CAADD_hostName.GetLength());

	uiPhoneLength = m_CAADD_phone_cs.GetLength();
	memcpy(pucPhone,m_CAADD_phone_cs.GetBuffer(),m_CAADD_phone_cs.GetLength());

	//��CA֤���ļ�
	int len = 0;
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_CA_certImp_cs,pucCACert,&len);
	uiCACertLength = len;
	pucCACert = new unsigned char[len+1];
	memset(pucCACert,0x00,len+1);
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_CA_certImp_cs,pucCACert,&len);

	unsigned char in_data[2048]={0x00};
	unsigned int  in_data_len=0;

	unsigned char in_data_tc[2048]={0x00};
	unsigned int  in_data_tc_len=0;

	char to_cmp[2]={0x30,0x82};


	if(strncmp(to_cmp,(char*)pucCACert,2) && !strncmp("M",(char*)pucCACert,1))
	{
		//B64���룬������B64��ʽ��֤���ļ�
		char dst[4096]={0x00};
		int length = 0;
		length = Km_Decode((char*)pucCACert,len,dst);
		memcpy(in_data,dst,length);
		in_data_len = length;
	}
	else if(!strncmp(to_cmp,(char*)pucCACert,2) && strncmp("M",(char*)pucCACert,1))
	{
		//ֱ�Ӵ���������DER��ʽ��֤���ļ�
		memcpy(in_data,pucCACert,len);
		in_data_len = len;
	}
	else if(strstr((char*)pucCACert,"BEGIN CERTIFICATE"))
	{
		//���ܣ���pem��ʽ��֤���ļ�
		PKI_DATA in_cert,out_cert;
		in_cert.size = len;
		out_cert.size=0;
		out_cert.value = new unsigned char[2048];
		in_cert.value = new unsigned char[len+1];
		memset(in_cert.value,0x00,len+1);
		memcpy(in_cert.value,pucCACert,len);
		pkiBase64Decode(in_cert,&out_cert);
		memcpy(in_data,out_cert.value,out_cert.size);
		in_data_len = out_cert.size;
	}
	else
	{
		MessageBox("��ȷ�ϵ������֤���ļ���","���ݸ�ʽ����",MB_ICONWARNING);
		return;
	}



	if(!m_CA_truchain_Imp_cs.IsEmpty())
	{
		int len_chain=0;
		CMyUtil::ReadData((LPSTR)(LPCTSTR)m_CA_truchain_Imp_cs,pucTrustChain,&len_chain);
		uiTrustChainLength = len_chain;
		pucTrustChain = new unsigned char[len_chain+1];
		memset(pucTrustChain,0x00,len_chain+1);
		CMyUtil::ReadData((LPSTR)(LPCTSTR)m_CA_truchain_Imp_cs,pucTrustChain,&len_chain);

		char to_cmp[2]={0x30,0x82};

		if(strncmp(to_cmp,(char*)pucTrustChain,2) && !strncmp("M",(char*)pucTrustChain,1))
		{
			//B64���룬������B64��ʽ���������ļ�
			char dst[4096]={0x00};
			int length = 0;
			length = Km_Decode((char*)pucTrustChain,len,dst);
			memcpy(in_data_tc,dst,length);
			in_data_tc_len = length;
		}
		else if(!strncmp(to_cmp,(char*)pucTrustChain,2) && strncmp("M",(char*)pucTrustChain,1))
		{
			//ֱ�Ӵ���������DER��ʽ���������ļ�
			memcpy(in_data_tc,pucTrustChain,len);
			in_data_tc_len = len;
		}
		else
		{
			MessageBox("��ȷ�ϵ������֤���ļ���","���ݸ�ʽ����",MB_ICONWARNING);
			return;
		}
	}
	else if(m_CA_truchain_Imp_cs.IsEmpty())
	{
		pucTrustChain=new unsigned char[10];
		uiTrustChainLength = 10;
		memset(pucTrustChain,0x00,10);
	}
	unsigned int type_VS1 = 0x00000;
	//----������������֤�������ȼ�������
	//----ͨ��0x00000�����ƽ���ÿһλ����һ�ֲ��ԣ�����0��ʾѡ�У�1��2��3�ֱ��ʾ���ȼ�1��2��3
	//----��0x01230��ʾ�ֱ�ѡ���Զ�ͬ��CRL�б����ء�CRL��������֤��OCSP��֤�������ֲ��ԣ���Ӧ���ȼ���1��2��3��ʾ
	if(/*!m_VS1_priority.IsEmpty() && (*/0x00001 == (type_VS & 0x00001)/*)*/)
	{
		if((m_VS1_priority.IsEmpty())||(3 < atoi(m_VS1_priority)))
		{
			MessageBox("���������һ�����ȼ���������3����","��ʾ",MB_ICONWARNING);
			return ;
		}
		else{
			if(m_VS1_priority == "1")//--------------����һ�����ȼ����ã��˴�Ϊ���ȼ�Ϊ1
			{
				type_VS1 = type_VS1 + 0x00001;
			}
			if(m_VS1_priority == "2")
			{
				type_VS1 = type_VS1 + 0x00002;
			} 
			if(m_VS1_priority == "3")
			{
				type_VS1 = type_VS1 + 0x00003;
			}
		
		}
		
	}
	if(/*!m_VS2_priority.IsEmpty() && (*/0x00010 == (type_VS & 0x00010)/*)*/)//---���ж��Ƿ�ѡ�д˲���
	{
		
		if((m_VS2_priority.IsEmpty())|| (3 < atoi(m_VS2_priority)))//-------���ж����ȼ��Ƿ����ã�δ������ʾ
		{
			MessageBox("��������Զ������ȼ���������3����","��ʾ",MB_ICONWARNING);
			return ;
		}
		else{
			if(m_VS2_priority == "1")//--------------���Զ������ȼ����ã��˴�Ϊ���ȼ�Ϊ1
			{
				type_VS1 = type_VS1 + 0x00010;
			}
			if(m_VS2_priority == "2")
			{
				type_VS1 = type_VS1 + 0x00020;
			} 
			if(m_VS2_priority == "3")
			{
				type_VS1 = type_VS1 + 0x00030;
			}
		
		}
		
	}
	if(/*!m_VS3_priority.IsEmpty() && (*/0x00100 == (type_VS & 0x00100)/*)*/)
	{
		if((m_VS3_priority.IsEmpty())||(3 < atoi(m_VS3_priority)))
		{
			MessageBox("����������������ȼ���������3����","��ʾ",MB_ICONWARNING);
			return ;
		}
		else{
			if(m_VS3_priority == "1")//--------------�����������ȼ����ã��˴�Ϊ���ȼ�Ϊ1
			{
				type_VS1 = type_VS1 + 0x00100;
			}
			if(m_VS3_priority == "2")
			{
				type_VS1 = type_VS1 + 0x00200;
			} 
			if(m_VS3_priority == "3")
			{
				type_VS1 = type_VS1 + 0x00300;
			}
		}
		
	}
	if(/*!m_VS4_priority.IsEmpty() && (*/0x01000 == (type_VS & 0x01000)/*)*/)
	{

		if((m_VS4_priority.IsEmpty())||(3 < atoi(m_VS4_priority)))
		{
			MessageBox("����������ĵ����ȼ���������3����","��ʾ",MB_ICONWARNING);
			return ;
		}
		else{
			if(m_VS4_priority == "1")//--------------�����ĵ����ȼ����ã��˴�Ϊ���ȼ�Ϊ1
			{
				type_VS1 = type_VS1 + 0x01000;
			}
			if(m_VS4_priority == "2")
			{
				type_VS1 = type_VS1 + 0x02000;
			} 
			if(m_VS4_priority == "3")
			{
				type_VS1 = type_VS1 + 0x03000;
			}
		}
		
	}
	if(/*!m_VS5_priority.IsEmpty() && (*/0x10000 == (type_VS & 0x10000)/*)*/)
	{
		if((m_VS5_priority.IsEmpty())||(3 < atoi(m_VS5_priority)))
		{
			MessageBox("���������������ȼ���������3����","��ʾ",MB_ICONWARNING);
			return ;
		}
		else{
			if(m_VS5_priority == "1")//--------------����������ȼ����ã��˴�Ϊ���ȼ�Ϊ1
			{
				type_VS1 = type_VS1 + 0x10000;
			}
			if(m_VS5_priority == "2")
			{
				type_VS1 = type_VS1 + 0x20000;
			} 
			if(m_VS5_priority == "3")
			{
				type_VS1 = type_VS1 + 0x30000;
			}
		}
		
	}
	//---------------------------��֤���Խṹ���Ա�ĳ�ʼ��
	vs.CRLhand = NULL;//------------------����1
	vs.autoCRLip = NULL;//---------------����2
	vs.autoCRLport = NULL;//--from ldap
	vs.autoCRLurl = NULL;
	/*vs.autoCRLname = NULL;
	vs.autoCRLpwd = NULL;*/
	vs.autoCRLtime = 0;
	vs.autoFromHTTPurl = NULL;//--from http
	vs.autoFromHTTPtime = 0;
	vs.autoCRLtype = 0;
	vs.CRLverifyTime = 0;//------------����3
	vs.OCSPip = NULL;//----------------����4
	vs.OCSPport = NULL;
	vs.OCSPurl = NULL;
	vs.OCSPcertstand = 0;
	vs.OCSPtalktype = 0;
	vs.OCSPverify = NULL;//-------------����5
	
	//-----�����ǻ�ȡ���Եķ�ʽ���ֱ��ǲ���֤����֤
	//-----����֤vs.option = 0x00000���������ı䣬�ɷ�����ж�
	//-----��֤���������֣�ͨ��0x00000�ж����ͺ����ȼ���ÿһ�ζ���ȡ������Ե��������ݣ����������ÿգ���������ˣ��ɷ�����ж���һ������

	if(type_VS1 == 0x00000)//---------------����֤CRL��OCSP
	{
		vs.option = type_VS1;
		vs.CRLhandLen = 10;
		vs.CRLhand = (unsigned char*)calloc(vs.CRLhandLen,sizeof(unsigned char));
		vs.autoCRLipLen = 10;
		vs.autoCRLip = (unsigned char*)calloc(vs.autoCRLipLen,sizeof(unsigned char));
		vs.autoCRLportLen = 10;
		vs.autoCRLport = (unsigned char*)calloc(vs.autoCRLportLen,sizeof(unsigned char));
		
		vs.autoCRLurlLen = 10;
		vs.autoCRLurl = (unsigned char*)calloc(vs.autoCRLurlLen,sizeof(unsigned char));
		vs.autoFromHTTPurlLen = 10;
		vs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen,sizeof(unsigned char));
		vs.OCSPipLen = 10;
		vs.OCSPip = (unsigned char*)calloc(vs.OCSPipLen,sizeof(unsigned char));
		vs.OCSPprotLen = 10;
		vs.OCSPport = (unsigned char*)calloc(vs.OCSPprotLen,sizeof(unsigned char));
		vs.OCSPurlLen = 10;
		vs.OCSPurl =(unsigned char*)calloc(vs.OCSPurlLen,sizeof(unsigned char));
		vs.OCSPverifyLen = 10;
		vs.OCSPverify = (unsigned char*)calloc(vs.OCSPverifyLen,sizeof(unsigned char));
		/*MessageBox("����֤CRL��OCSP","��ʾ",MB_ICONWARNING|MB_OK);
		return ;*/
	}
	else{
		vs.option = type_VS1;
		//---------------------------����һ�ֶ�����CRL�б�
		ret = vsOneDlg.GetCRLpath_vs1(vs.CRLhand,&vs.CRLhandLen);
		if(0 != ret)
			return;
		if(vs.CRLhandLen == 0)
		{
			if(vs.CRLhandLen==0&&type_VS & 0x00001)
			{
			  MessageBox("��ѡ��CRL�ļ���","��ʾ",MB_ICONEXCLAMATION);
			  return ;
			}	
			vs.CRLhandLen = 10;
			vs.CRLhand = (unsigned char*)calloc(vs.CRLhandLen,sizeof(unsigned char));
		}
		else{
			
			vs.CRLhand = (unsigned char*)calloc(vs.CRLhandLen+32,sizeof(unsigned char));
			vsOneDlg.GetCRLpath_vs1(vs.CRLhand,&vs.CRLhandLen);
		}

		//--------------------------���Զ�ͬ��CRL�б�����
		ret = vsTwoDlg.GetVS2(vs.autoCRLip,&vs.autoCRLipLen,vs.autoCRLport,&vs.autoCRLportLen,vs.autoCRLurl,&vs.autoCRLurlLen,&vs.autoCRLtime,
								  vs.autoFromHTTPurl,&vs.autoFromHTTPurlLen,&vs.autoFromHTTPtime,&vs.autoCRLtype);
		if(ret!=0)
			return;
		if( 0 == vs.autoCRLtype)
		{
			if(vs.autoCRLtype==0&&type_VS & 0x00010)
			{
			  MessageBox("��ѡ��ͬ��CRL���������ͣ�","��ʾ",MB_ICONEXCLAMATION);
			  return ;
			}	
			vs.autoCRLipLen = 10;
			vs.autoCRLip = (unsigned char*)calloc(vs.autoCRLipLen,sizeof(unsigned char));
			vs.autoCRLportLen = 10;
			vs.autoCRLport = (unsigned char*)calloc(vs.autoCRLportLen,sizeof(unsigned char));
			/*vs.autoCRLnameLen = 10;
			vs.autoCRLname = (unsigned char *)calloc(vs.autoCRLnameLen,sizeof(unsigned char));
			vs.autoCRLpwdLen = 10;
			vs.autoCRLpwd = (unsigned char *)calloc(vs.autoCRLpwdLen,sizeof(unsigned char));*/
			vs.autoCRLurlLen = 10;
			vs.autoCRLurl = (unsigned char*)calloc(vs.autoCRLurlLen,sizeof(unsigned char));
			vs.autoFromHTTPurlLen = 10;
			vs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen,sizeof(unsigned char));
		}
		else{
			
			//�����http��ʽ
			if(vs.autoCRLtype == 2)
			{
				vs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen+32,sizeof(unsigned char));
				vsTwoDlg.GetVS2(vs.autoCRLip,&vs.autoCRLipLen,vs.autoCRLport,&vs.autoCRLportLen,vs.autoCRLurl,&vs.autoCRLurlLen,&vs.autoCRLtime,
								  vs.autoFromHTTPurl,&vs.autoFromHTTPurlLen,&vs.autoFromHTTPtime,&vs.autoCRLtype);
				vs.autoCRLipLen = 10;
				vs.autoCRLip = (unsigned char*)calloc(vs.autoCRLipLen,sizeof(unsigned char));
				vs.autoCRLportLen = 10;
				vs.autoCRLport = (unsigned char*)calloc(vs.autoCRLportLen,sizeof(unsigned char));
				vs.autoCRLurlLen = 10;
				vs.autoCRLurl = (unsigned char*)calloc(vs.autoCRLurlLen,sizeof(unsigned char));
				
			}
			//�����LDAP��ʽ
			else{
				vs.autoCRLip = (unsigned char*)calloc(vs.autoCRLipLen+32,sizeof(unsigned char));
				vs.autoCRLport = (unsigned char*)calloc(vs.autoCRLportLen+32,sizeof(unsigned char));
				vs.autoCRLurl = (unsigned char*)calloc(vs.autoCRLurlLen+32,sizeof(unsigned char));
				/*vs.autoCRLname = (unsigned char *)calloc(vs.autoCRLnameLen + 32,sizeof(unsigned char));
				vs.autoCRLpwd = (unsigned char *)calloc(vs.autoCRLpwdLen + 32,sizeof(unsigned char));*/
				vsTwoDlg.GetVS2(vs.autoCRLip,&vs.autoCRLipLen,vs.autoCRLport,&vs.autoCRLportLen,vs.autoCRLurl,&vs.autoCRLurlLen,&vs.autoCRLtime,
								  vs.autoFromHTTPurl,&vs.autoFromHTTPurlLen,&vs.autoFromHTTPtime,&vs.autoCRLtype);
				vs.autoFromHTTPurlLen = 10;
				vs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen,sizeof(unsigned char));

			}
		}
		
		
	    //-------------------------������CRL��������֤

		ret = vsThreeDlg.GetVS3Time(&vs.CRLverifyTime);
		if(0 != ret)
			return;
		if(vs.CRLverifyTime==0&&type_VS & 0x00100)
			{
			  MessageBox("������CRL�ڵ���֤ʱ������","��ʾ",MB_ICONEXCLAMATION);
			  return ;
			}
		//--------------------------������OCSP��֤
		
		ret = vsFourDlg.GetIpUrlVS4(vs.OCSPip,&vs.OCSPipLen,vs.OCSPurl,&vs.OCSPurlLen,vs.OCSPport,&vs.OCSPprotLen,&vs.OCSPtalktype,&vs.OCSPcertstand);
		if(0 != ret)
			return;
		if( vs.OCSPcertstand == 0 )
		{
			if(vs.OCSPcertstand==0&&type_VS & 0x01000)
			{
			  MessageBox("������OCSP��֤���ͣ�","��ʾ",MB_ICONEXCLAMATION);
			  return ;
			}
			vs.OCSPipLen = 10;
			vs.OCSPip = (unsigned char*)calloc(vs.OCSPipLen,sizeof(unsigned char));
			vs.OCSPprotLen = 10;
			vs.OCSPport = (unsigned char*)calloc(vs.OCSPprotLen,sizeof(unsigned char));
			vs.OCSPurlLen = 10;
			vs.OCSPurl =(unsigned char*)calloc(vs.OCSPurlLen,sizeof(unsigned char));	
		}
		else{
			vs.OCSPip = (unsigned char*)calloc(vs.OCSPipLen+32,sizeof(unsigned char));
			vs.OCSPport = (unsigned char*)calloc(vs.OCSPprotLen+32,sizeof(unsigned char));
			vs.OCSPurl =(unsigned char*)calloc(vs.OCSPurlLen +32,sizeof(unsigned char));
			ret = vsFourDlg.GetIpUrlVS4(vs.OCSPip,&vs.OCSPipLen,vs.OCSPurl,&vs.OCSPurlLen,vs.OCSPport,&vs.OCSPprotLen,&vs.OCSPtalktype,&vs.OCSPcertstand);

		}
		
		//-----------------------������OCSP��������֤

		ret = vsFiveDlg.GetVs5_ocsp(vs.OCSPverify,&vs.OCSPverifyLen);
		if(0 != ret)
			return;
		if(vs.OCSPverifyLen == 0)
		{
			if(vs.OCSPverifyLen==0&&type_VS & 0x10000)
			{
			  MessageBox("������OCSP�����㣡","��ʾ",MB_ICONEXCLAMATION);
			  return ;
			}
			vs.OCSPverifyLen = 10;
			vs.OCSPverify = (unsigned char*)calloc(vs.OCSPverifyLen,sizeof(unsigned char));
		}
		else{
			vs.OCSPverify = (unsigned char*)calloc(vs.OCSPverifyLen+32,sizeof(unsigned char));
			ret = vsFiveDlg.GetVs5_ocsp(vs.OCSPverify,&vs.OCSPverifyLen);
		}
		
	
	}

	uiCACertIndex = atoi(m_CaAdd_index_CS);
	
	ret = Sig_CACertAdd(hSessionHandle,uiRtCertIndex,uiRtCertType,uiCACertIndex,uiAlgo,uiKeyLength,uiCertIndexLength,putCertIndex,uiCertNameLength,pucCertName,
						uiAtNameLength,pucAtName,uiHostLength,pucHost,uiPhoneLength,pucPhone,in_data_len,in_data,in_data_tc_len,
						in_data_tc,vs);
	if(0 == ret)
	{
		MessageBox("�����ɹ���","�ɹ�",MB_ICONEXCLAMATION);
	}
	else if(0 != ret)
	{
		char outCACertAddError[100]={0x00};
		retValueParse(ret,outCACertAddError);
		MessageBox("    ����ʧ��"+(CString)outCACertAddError,"��ʾ");
		delete []pucCACert;
		delete []pucTrustChain;

		free(vs.CRLhand);
		free(vs.autoCRLip);
		free(vs.autoCRLport);
		free(vs.autoCRLurl);
		/*free(vs.autoCRLname);
		free(vs.autoCRLpwd);*/
		free(vs.OCSPip);
		free(vs.OCSPport);
		free(vs.OCSPurl);
		free(vs.OCSPverify);
		
		return;
	}
	//�ͷ��ڴ�ռ�
	delete []pucCACert;
	delete []pucTrustChain;

	free(vs.CRLhand);
	free(vs.autoCRLip);
	free(vs.autoCRLport);
	free(vs.autoCRLurl);
	/*free(vs.autoCRLname);
	free(vs.autoCRLpwd);*/
	free(vs.OCSPip);
	free(vs.OCSPport);
	free(vs.OCSPurl);
	free(vs.OCSPverify);

	CDialogEx::OnOK();
}


void CCACertAdd::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CCACertAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	unsigned int RtindexSet[256] = {0};
	unsigned int Rtnum = 0;
	unsigned int RtalgTemp[256] = {0};

	unsigned int CAindexSet[256] = {0};
	unsigned int CAnum = 0;
	unsigned int CAalgTemp[256] = {0};
	//����CComBox������Ϊֻ����ֹ�û��Լ�������ɲ���Ҫ�Ĵ���
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_CAADD_ALG))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit1 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_CAADD_CERTINDEX1_COMBO1))->GetWindow(GW_CHILD));	
	pEdit1->SetReadOnly(TRUE);

	//----------------------------------

	CWnd *cWnd = GetDlgItem(IDC_CACERT_TITLE_STATIC);
	if(isUp_CA)
	{
		this->SetWindowText("���CA֤��");
		cWnd->SetWindowText("���CA֤��");
		//SetDlgItemText(IDC_COMBO_CAADD_ALG, _T("SM2 256"));
		 //TODO:  �ڴ���Ӷ���ĳ�ʼ��
		int one = caAddIndex;
		CString cs_certIndex;
		CString index;
		index.Format("%3d",one);
		cs_certIndex = index;//���ݵĸ�ʽ����������Ҫ��дһ���µķ��� 
		SetDlgItemText(IDC_CAADD_CERTINDEX1_COMBO1,cs_certIndex);

		int data = 0;
		for(int i=0;i<256;i++)
		{
			if(1 == caAddIndex_array[i][1])
			{
				data = caAddIndex_array[i][0];
				index.Format("%3d",data);
				cs_certIndex = index;
				m_CaAdd_index_CCobox.AddString(cs_certIndex);
				//m_rt_index.InsertString(i,cs_certIndex);
				//m_rt_index.InsertString(i-1,_T(cs_certIndex));
			}
		}
	}
	else if(!isUp_CA)
	{
		this->SetWindowText("����CA֤��");
		cWnd->SetWindowText("����CA֤��");
		SetDlgItemText(IDC_CAADD_CERTNAME_EDIT,m_CAADD_certName_cs); 
		SetDlgItemText(IDC_COMBO_CAADD_ALG,m_CAADD_certAlg_cs); 
		SetDlgItemText(IDC_CAADD_CERTINDEX_EDIT,m_CAADD_certIndex_cs); 
		SetDlgItemText(IDC_CAADD_ATNAME_EDIT,m_CAADD_atName_cs); 
		SetDlgItemText(IDC_CAADD_HOST_EDIT,m_CAADD_hostName); 
		SetDlgItemText(IDC_CAADD_PHONE_EDIT,m_CAADD_phone_cs); 
		SetDlgItemText(IDC_CAADD_CERTINDEX1_COMBO1,index_ca_fordel); 
		CString indrt;
		indrt.Format("%d",index_rt_forshow);
		if (1 == rt_type)
		{
			SetDlgItemText(IDC_COMBO_CAADD_ROOTCERT,indrt+"_RtCert.cer"); 
		}
		if (2 == rt_type)
		{
			SetDlgItemText(IDC_COMBO_CAADD_ROOTCERT,indrt+"_CaCert.cer"); 
		}
	}
	

	CMyUtil::GetRtCertIndexSet(phHandle_CACertAdd,&Rtnum,RtindexSet,RtalgTemp);
	if(0 != Rtnum)
	{
		for(unsigned int i=0;i<Rtnum;i++)
		{
			CString ind,alg;
			ind.Format("%d",RtindexSet[i]);
			//m_rootCert_choseCAA.AddString(ind+"_RootCert.cer");
			if(2048 == RtalgTemp[i])
			{
				alg.Format("%d",RtalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_RtCert.cer"+"_RSA"+alg);
			}
			if(1024 == RtalgTemp[i])
			{
				alg.Format("%d",RtalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_RtCert.cer"+"_RSA"+alg);
			}
			if(256 == RtalgTemp[i])
			{
				alg.Format("%d",RtalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_RtCert.cer"+"_SM2"+alg);
			}
		}
	}
	else
	{
		SetDlgItemText(IDC_COMBO_CAADD_ROOTCERT, _T("ϵͳ��δ�����Root֤�飡")); 
	}
	//-----------------------�˴�������ڶ༶CA
	CMyUtil::GetCACertIndexSet(phHandle_CACertAdd,&CAnum,CAindexSet,CAalgTemp);
	
	if(0 != CAnum)
	{
		for(unsigned int i=0;i<CAnum;i++)
		{
			CString ind,alg;
			ind.Format("%d",CAindexSet[i]);
			//m_rootCert_choseCAA.AddString(ind+"_RootCert.cer");
			if(2048 == CAalgTemp[i])
			{
				alg.Format("%d",CAalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_CaCert.cer"+"_RSA"+alg);
			}
			if(1024 == CAalgTemp[i])
			{
				alg.Format("%d",CAalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_CaCert.cer"+"_RSA"+alg);
			}
			if(256 == CAalgTemp[i])
			{
				alg.Format("%d",CAalgTemp[i]);
				m_rootCert_choseCAA.AddString(ind+"_CaCert.cer"+"_SM2"+alg);
			}
		}
	}
	else
	{
		SetDlgItemText(IDC_COMBO_CAADD_ROOTCERT, _T("ϵͳ��δ�����CA֤�飡")); 
	}
	vsOneDlg.Create(IDD_PROPPAGE_CAADD_VS1,this/*GetDlgItem(IDD_CACERT_ADD)*/);
	vsTwoDlg.Create(IDD_PROPPAGE_CAADD_VS2,this);
	vsThreeDlg.Create(IDD_PROPPAGE_CAADD_VS3,this);
	vsFourDlg.Create(IDD_PROPPAGE_CAADD_VS4,this);
	vsFiveDlg.Create(IDD_PROPPAGE_CAADD_VS5,this);
	
	//----------------------------------��ӻ����CA֤��ʱ����֤���Ե���ʾ����

	if(isUp_CA)//-----���CA֤�飬����ģ����ʾ
	{
		CheckDlgButton(IDC_CHECK_VS6,6);
		CCACertAdd::OnBnClickedCheckVs6();
		vsTwoDlg.TypeVS2 = 0;
		vsFourDlg.CertStand = 0;
		vsFourDlg.talkType = 0;
	}
	else if(!isUp_CA)//-----------����֤�飬����ģ����ʾ
	{
		//0x3201�ж����ȼ���ʾ
		char coption[8] = {0x00};
		char *vs = NULL;
		if (0 == CApvs.option)//CA���Բ���֤
		{
			CheckDlgButton(IDC_CHECK_VS6,6);
		}
		else{
			itoa(CApvs.option,coption,10);
			int num = strlen(coption);
			CMyUtil::RevStr(coption);
			if(('0' != coption[0]) || ('\0' == coption[0]))
			{
				if('1' == coption[0])
				{
					SetDlgItemTextA(IDC_EDIT_VS1,"1");
				}
				else if('2' == coption[0])
				{
					SetDlgItemTextA(IDC_EDIT_VS1,"2");
				}
				else if('3' == coption[0])
				{
					SetDlgItemTextA(IDC_EDIT_VS1,"3");
				}
				else if('4' == coption[0])
				{
					SetDlgItemTextA(IDC_EDIT_VS1,"4");
				}
			}

			if(('0' != coption[1]) || ('\0'  == coption[1]))
			{
				if('1' == coption[1])
				{
					SetDlgItemTextA(IDC_EDIT_VS2,"1");
				}
				else if('2' == coption[1])
				{
					SetDlgItemTextA(IDC_EDIT_VS2,"2");
				}
				else if('3' == coption[1])
				{
					SetDlgItemTextA(IDC_EDIT_VS2,"3");
				}
				else if('4' == coption[1])
				{
					SetDlgItemTextA(IDC_EDIT_VS2,"4");
				}
			}
			if(('0' != coption[2]) || ('\0'  == coption[2]))
			{
				if('1' == coption[2])
				{
					SetDlgItemTextA(IDC_EDIT_VS3,"1");
				}
				else if('2' == coption[2])
				{
					SetDlgItemTextA(IDC_EDIT_VS3,"2");
				}
				else if('3' == coption[2])
				{
					SetDlgItemTextA(IDC_EDIT_VS3,"3");
				}
				else if('4' == coption[2])
				{
					SetDlgItemTextA(IDC_EDIT_VS3,"4");
				}
			}

			if(('0' != coption[3]) || ('\0'  == coption[3]))
			{
				if('1' == coption[3])
				{
					SetDlgItemTextA(IDC_EDIT_VS4,"1");
				}
				else if('2' == coption[3])
				{
					SetDlgItemTextA(IDC_EDIT_VS4,"2");
				}
				else if('3' == coption[3])
				{
					SetDlgItemTextA(IDC_EDIT_VS4,"3");
				}
				else if('4' == coption[3])
				{
					SetDlgItemTextA(IDC_EDIT_VS4,"4");
				}
			}
			if(('0' != coption[4]) || ('\0'  == coption[4]))
			{
				if('1' == coption[4])
				{
					SetDlgItemTextA(IDC_EDIT_VS5,"1");
				}
				else if('2' == coption[4])
				{
					SetDlgItemTextA(IDC_EDIT_VS5,"2");
				}
				else if('3' == coption[4])
				{
					SetDlgItemTextA(IDC_EDIT_VS5,"3");
				}
				else if('4' == coption[4])
				{
					SetDlgItemTextA(IDC_EDIT_VS5,"4");
				}
			}

		}
		
	
		//----------Ĭ������ʾ����
		CCACertAdd::OnBnClickedCheckVs6();
		vsOneDlg.SetCRLpath_vs1(CApvs.CRLhand);//������һ�����ݷ��õ�����
		vsTwoDlg.SetLdap(CApvs.autoCRLip,CApvs.autoCRLport,CApvs.autoCRLurl,CApvs.autoCRLtime,CApvs.autoFromHTTPurl,CApvs.autoFromHTTPtime,CApvs.autoCRLtype);//----�����Զ������ݷ��õ�����
		vsThreeDlg.SetVS3_Time(CApvs.CRLverifyTime);//----�������������ݷ��õ�����
		vsFourDlg.SetIpUrlVs(CApvs.OCSPip,CApvs.OCSPport,CApvs.OCSPurl,CApvs.OCSPcertstand,CApvs.OCSPtalktype);//----�������ĵ����ݷ��õ�����
		//vsFourDlg.GetIpUrlVS4(vs.,&vs.OCSPipLen,vs.,&vs.OCSPprotLen,vs.OCSPurl,&vs.OCSPurlLen,&vs.OCSPtalktype,&vs.OCSPcertstand);
		vsFiveDlg.SetVs5_ocsp(CApvs.OCSPverify);//----������������ݷ��õ�����
		
	}
//--------------------------------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/*
void CCACertAdd::OnBnClickedImcaButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("(*.cer)|*.cer|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("cer"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���  
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        SetDlgItemText(IDC_CAADD_IMCAPATH_EDIT, strFilePath);   
    } 
}*/


void CCACertAdd::OnBnClickedImcaButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("(*.cer)|*.cer|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("cer"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
	int ret;
	unsigned char *pucCaCert_File=NULL;   //�մ��ļ��ж�����֤������
	unsigned int uiCaCert_FileLength=0;     

	unsigned char *pucCaCert=NULL;    //ת�����֤������
	unsigned int uiRtCertLength=0;
	void * hSessionHandle = phHandle_CACertAdd;
	unsigned int  o_publicKeyLen = 0;
	unsigned char * o_publicKey = NULL;



	unsigned char ucnode[1024]={0x00};
	unsigned int  uinode_len = 0;
	unsigned char ucItemValue[100]={0x00};
	unsigned int  uiItemValue_len;
	CString cert_sn;
	CString dn_cn;
	CString algId;
	CString dn_o;

	unsigned int  o_certInfoLen;
	unsigned char * o_certInfo;

    // ��ʾ���ļ��Ի���  
    if (IDOK != fileDlg.DoModal())   
    {   
        //// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        // strFilePath = fileDlg.GetPathName();  
        //SetDlgItemText(IDC_CAADD_IMCAPATH_EDIT, strFilePath);   
		return;
    } 
	else{
		  // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
         strFilePath = fileDlg.GetPathName();  
        SetDlgItemText(IDC_CAADD_IMCAPATH_EDIT, strFilePath);   
	}
	
	//��ȡ֤���ļ�
	char *filename = (LPSTR)(LPCTSTR)strFilePath;
	CMyUtil::ReadData(filename,pucCaCert_File,(int *)&uiCaCert_FileLength);
	pucCaCert_File = new unsigned char[uiCaCert_FileLength];
	CMyUtil::ReadData(filename,pucCaCert_File,(int *)&uiCaCert_FileLength);
	


	//�������ݸ�ʽ�ж� �������B64�������PEM���� ��ȫ��ת���ɶ����Ƹ�ʽ
	ret = CMyUtil::Cert2Dercert(pucCaCert_File,uiCaCert_FileLength,NULL,&uiRtCertLength);
	if (ret<0)
	{
	   MessageBox("��ȷ�ϵ������֤���ļ���","���ݸ�ʽ����",MB_ICONWARNING);
	   delete []pucCaCert_File;
	   return ;
	}
	else
	{  
		pucCaCert = new unsigned char[uiCaCert_FileLength+1];
		ret =  CMyUtil::Cert2Dercert(pucCaCert_File,uiCaCert_FileLength,pucCaCert,&uiRtCertLength);
		if (ret<0)
		{
		   MessageBox("��ȷ�ϵ������֤���ļ���","���ݸ�ʽ����",MB_ICONWARNING);
		   delete []pucCaCert_File;
		   delete []pucCaCert;
		   return ;
		}
	}
	//����֤��

	ret = PKI_GetXMLCertInfo(hSessionHandle,uiRtCertLength,pucCaCert, &o_certInfoLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("����֤��ʧ��"+(CString)outGapk,"��ʾ",MB_ICONEXCLAMATION);
		delete []pucCaCert_File;
		delete []pucCaCert;
		return;
	}
	o_certInfo  = new unsigned char[o_certInfoLen];
	ret = PKI_GetXMLCertInfo(hSessionHandle,uiRtCertLength,pucCaCert,&o_certInfoLen,o_certInfo);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("����֤��ʧ��"+(CString)outGapk,"��ʾ",MB_ICONEXCLAMATION);
		delete []pucCaCert_File;
		delete []pucCaCert;
		delete []o_certInfo;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\o_certInfo.txt",o_certInfo,o_certInfoLen);

	



	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"subject",ucnode,&uinode_len);  //ȡ�������������
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_o",ucItemValue,&uiItemValue_len);  //ȡ��O������
	SetDlgItemText(IDC_CAADD_ATNAME_EDIT,(LPCTSTR)ucItemValue);  
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_cn",ucItemValue,&uiItemValue_len);  //ȡ��������
	SetDlgItemText(IDC_CAADD_CERTNAME_EDIT,(LPCTSTR)ucItemValue);
	
	
	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"serialnum",ucItemValue,&uiItemValue_len);
	SetDlgItemText(IDC_CAADD_CERTINDEX_EDIT,(LPCTSTR)ucItemValue);  

	//----��ȡ֤���㷨
	ret = PKI_GetPublicKeyFromCert(hSessionHandle,uiRtCertLength,pucCaCert, &o_publicKeyLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("��ȡ�㷨��ʶʧ��"+(CString)outGapk,"��ʾ",MB_ICONEXCLAMATION);
		delete []pucCaCert_File;
		delete []pucCaCert;
		return;
	}
	o_publicKey  = new unsigned char[o_publicKeyLen];
	ret = PKI_GetPublicKeyFromCert(hSessionHandle,uiRtCertLength,pucCaCert,&o_publicKeyLen,o_publicKey);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("��ȡ�㷨��ʶʧ��"+(CString)outGapk,"��ʾ",MB_ICONEXCLAMATION);
		delete []pucCaCert_File;
		delete []pucCaCert;
		delete []o_publicKey;
		return;
	}
	SetDlgItemText(IDC_COMBO_CAADD_ALG,(LPCTSTR)o_publicKey); 


	delete []pucCaCert;
	delete []o_certInfo;
	delete []o_publicKey;
}

void CCACertAdd::OnBnClickedImtruchainButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("(*.p7b)|*.p7b|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("p7b"), NULL, 0, szFilter, this);   
    CString strFilePath;   
	
	if(IDOK != fileDlg.DoModal())
	{
		return ;
	}
    // ��ʾ���ļ��Ի���  
	else    
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_CAADD_TRUCHAINPATH_EDIT, strFilePath); 
    } 

	int ret = 0;
	unsigned char *pucCaCert_File=NULL;   //�մ��ļ��ж�����֤������
	unsigned int uiCaCert_FileLength=0; 


	//��ȡ֤���ļ�
	char *filename = (LPSTR)(LPCTSTR)strFilePath;
	CMyUtil::ReadData(filename,pucCaCert_File,(int *)&uiCaCert_FileLength);
	pucCaCert_File = new unsigned char[uiCaCert_FileLength];
	CMyUtil::ReadData(filename,pucCaCert_File,(int *)&uiCaCert_FileLength);

	return ;

}


void CCACertAdd::OnBnClickedCheckVs1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(1 == m_check1.GetCheck())
	{
		
		vsOneDlg.ShowWindow(SW_SHOWNORMAL);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check2.EnableWindow(FALSE);
		m_VS2_CN.EnableWindow(FALSE);
		type_VS = type_VS | 0x00001;//--------ѡ����һλ��1
	}
	else{
		vsOneDlg.ShowWindow(SW_SHOWNORMAL);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check2.EnableWindow(TRUE);
		m_VS2_CN.EnableWindow(TRUE);
		type_VS = type_VS ^ 0x00001;//-------ȡ����һλ��0
		//�������
		vsOneDlg.SetDlgItemTextA(IDC_EDIT_vs1_crlfilepath,"");
		SetDlgItemTextA(IDC_EDIT_VS1,"");
	}
}


void CCACertAdd::OnBnClickedCheckVs2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(1 == m_check2.GetCheck())
	{
		
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(SW_SHOWNORMAL);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check1.EnableWindow(FALSE);
		m_VS1_CN.EnableWindow(FALSE);
		type_VS = type_VS | 0x00010;
		vsTwoDlg.TypeVS2 = 0;
	}
	else{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(SW_SHOWNORMAL);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check1.EnableWindow(TRUE);
		m_VS1_CN.EnableWindow(TRUE);
		type_VS = type_VS ^ 0x00010;
		//�������
		vsTwoDlg.m_http_radio.SetCheck(0);
		vsTwoDlg.m_ldap_radio.SetCheck(0);
		vsTwoDlg.TypeVS2 = 0;
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_vs2_HTTP_URLPATH,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_HTTP_CRLREL_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_HTTP_HOUR_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_HTTP_MINUTE_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_HTTP_SECOND_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_vs2_LDAPaddress,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_vs2_Port,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_CRLREL_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_HOUR_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_MINUTE_vs3,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_SECOND_vs2,"");
		vsTwoDlg.SetDlgItemTextA(IDC_EDIT_vs2_crlpath,"");
		SetDlgItemTextA(IDC_EDIT_VS2,"");

	}
}


void CCACertAdd::OnBnClickedCheckVs3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if(1 == m_check3.GetCheck())
	{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(SW_SHOWNORMAL);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		type_VS = type_VS | 0x00100;
	}
	else{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(SW_SHOWNORMAL);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		type_VS = type_VS ^ 0x00100;
		//�������
		vsThreeDlg.SetDlgItemTextA(IDC_EDIT_CRLREL,"");
		vsThreeDlg.SetDlgItemTextA(IDC_EDIT_HOUR,"");
		vsThreeDlg.SetDlgItemTextA(IDC_EDIT_MINUTE,"");
		vsThreeDlg.SetDlgItemTextA(IDC_EDIT_SECOND,"");
		SetDlgItemTextA(IDC_EDIT_VS3,"");
	}
}


void CCACertAdd::OnBnClickedCheckVs4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(1 == m_check4.GetCheck())
	{
	
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(SW_SHOWNORMAL);
		vsFiveDlg.ShowWindow(FALSE);
		m_check5.EnableWindow(FALSE);
		m_VS5_CN.EnableWindow(FALSE);
		type_VS = type_VS | 0x01000;
		vsFourDlg.CertStand = 0;
		vsFourDlg.talkType = 0;
	}
	else{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(SW_SHOWNORMAL);
		vsFiveDlg.ShowWindow(FALSE);
		m_check5.EnableWindow(TRUE);
		m_VS5_CN.EnableWindow(TRUE);
		type_VS = type_VS ^ 0x01000;
		//�������
		vsFourDlg.m_RADIO_GUOMI_Control.SetCheck(0);
		vsFourDlg.m_RADIO_SHUIZ_Control.SetCheck(0);
		vsFourDlg.m_RADIO_Socket_Control.SetCheck(0);
		vsFourDlg.m_RADIO_Web_Control.SetCheck(0);
		vsFourDlg.CertStand = 0;
		vsFourDlg.talkType = 0;
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_vs4_ip,"");
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_url_vs4,"");
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_vs4Port,"");
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_vs4_ip,"");
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_vs4Port,"");
		vsFourDlg.SetDlgItemTextA(IDC_EDIT_url_vs4,"");
		SetDlgItemTextA(IDC_EDIT_VS4,"");
	}
}


void CCACertAdd::OnBnClickedCheckVs5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//	MessageBox("��ѡ����OCSP��������֤���ԣ�");
	if(1 == m_check5.GetCheck())
	{
	
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(SW_SHOWNORMAL);
		m_check4.EnableWindow(FALSE);
		m_VS4_CN.EnableWindow(FALSE);
		type_VS = type_VS |0x10000;
	}
	else{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(SW_SHOWNORMAL);
		m_check4.EnableWindow(TRUE);
		m_VS4_CN.EnableWindow(TRUE);
		type_VS = type_VS ^ 0x10000;
		//�������
		vsFiveDlg.SetDlgItemTextA(IDC_EDIT_vs5_OCSP,"");
		SetDlgItemTextA(IDC_EDIT_VS5,"");
	}
}


void CCACertAdd::OnBnClickedCheckVs6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(1 == m_check6.GetCheck())
	{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check1.EnableWindow(FALSE);
		m_check2.EnableWindow(FALSE);
		m_check3.EnableWindow(FALSE);
		m_check4.EnableWindow(FALSE);
		m_check5.EnableWindow(FALSE);
		type_VS = 0x00000;
	}
	else{
		vsOneDlg.ShowWindow(FALSE);
		vsTwoDlg.ShowWindow(FALSE);
		vsThreeDlg.ShowWindow(FALSE);
		vsFourDlg.ShowWindow(FALSE);
		vsFiveDlg.ShowWindow(FALSE);
		m_check1.EnableWindow(TRUE);
		m_check2.EnableWindow(TRUE);
		m_check3.EnableWindow(TRUE);
		m_check4.EnableWindow(TRUE);
		m_check5.EnableWindow(TRUE);
		//type_VS = type_VS ^ 0x00000;
		SetDlgItemTextA(IDC_EDIT_VS6,"");
	}
}
