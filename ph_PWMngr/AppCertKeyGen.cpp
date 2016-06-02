// AppCertKeyGen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertKeyGen.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"

// CAppCertKeyGen �Ի���
  

IMPLEMENT_DYNAMIC(CAppCertKeyGen, CDialogEx)

CAppCertKeyGen::CAppCertKeyGen(void *handle,int isUpDate,CString certname,CString city,CString nation,CString area,CString organization,CString email,CString organizationUnite,CString keyIndex,CString algid,CString keyType,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppCertKeyGen::IDD, pParent)
	, m_ac_appName(_T(""))
	, m_ac_alg_cs(_T(""))
	, m_ac_index_cs(_T(""))
	, m_ac_appType_cs(_T(""))
	, m_ac_keyType_cs(_T(""))
	, m_ac_pinf(_T(""))
	, m_ac_pins(_T(""))
	, m_ac_cnName(_T(""))
	, m_ac_cityName_cs(_T(""))
	, m_ac_atName(_T(""))
	, m_ac_areaName_cs(_T(""))
	, m_ac_eMail(_T(""))
	, m_ac_OUvalue(_T(""))
{
	isUp = isUpDate;//1�����ɣ�0�Ǹ���
	phHandle_appCertMngr = handle;

	in_certname=certname;
	in_city=city;
	in_nation=nation;
	in_area=area;
	in_organization=organization;
	in_email=email;
	in_organizationUnite=organizationUnite;
	in_keyIndex=keyIndex;
	in_algid=algid;
	in_keyType=keyType;

}

CAppCertKeyGen::CAppCertKeyGen(void *handle,int isUpDate,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppCertKeyGen::IDD, pParent)
	, m_ac_appName(_T(""))
	, m_ac_alg_cs(_T(""))
	, m_ac_index_cs(_T(""))
	, m_ac_appType_cs(_T(""))
	, m_ac_keyType_cs(_T(""))
	, m_ac_pinf(_T(""))
	, m_ac_pins(_T(""))
	, m_ac_cnName(_T(""))
	, m_ac_cityName_cs(_T(""))
	, m_ac_atName(_T(""))
	, m_ac_areaName_cs(_T(""))
	, m_ac_eMail(_T(""))
	, m_ac_OUvalue(_T(""))
{
	isUp = isUpDate;//1�����ɣ�0�Ǹ���
	phHandle_appCertMngr = handle;
}

CAppCertKeyGen::~CAppCertKeyGen()
{
}

void CAppCertKeyGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AC_apname, m_ac_appName);
	DDX_Control(pDX, IDC_COMBO_AC_alg, m_ac_alg);
	DDX_CBString(pDX, IDC_COMBO_AC_alg, m_ac_alg_cs);
	DDX_Control(pDX, IDC_COMBO_AC_index, m_ac_index);
	DDX_CBString(pDX, IDC_COMBO_AC_index, m_ac_index_cs);
	DDX_Control(pDX, IDC_COMBO_AC_apType, m_ac_appType);
	DDX_CBString(pDX, IDC_COMBO_AC_apType, m_ac_appType_cs);
	DDX_Control(pDX, IDC_COMBO_AC_keyType, m_ac_keyType);
	DDX_CBString(pDX, IDC_COMBO_AC_keyType, m_ac_keyType_cs);
	DDX_Text(pDX, IDC_EDIT_AC_pinf, m_ac_pinf);
	DDX_Text(pDX, IDC_EDIT_AC_pins, m_ac_pins);
	DDX_Text(pDX, IDC_EDIT_AC_cnName, m_ac_cnName);
	DDX_Control(pDX, IDC_COMBO_AC_cityName, m_ac_cityName);
	DDX_CBString(pDX, IDC_COMBO_AC_cityName, m_ac_cityName_cs);
	DDX_Text(pDX, IDC_EDIT_AC_atName, m_ac_atName);
	DDX_Control(pDX, IDC_COMBO_AC_areaName, m_ac_areaName);
	DDX_CBString(pDX, IDC_COMBO_AC_areaName, m_ac_areaName_cs);
	//	DDX_Text(pDX, IDC_EDIT_AC_atUnitName, m_atUnitName);
	DDX_Text(pDX, IDC_EDIT_AC_eMail, m_ac_eMail);
	DDX_Text(pDX, IDC_EDIT_APPCERT_OU, m_ac_OUvalue);
}


BEGIN_MESSAGE_MAP(CAppCertKeyGen, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAppCertKeyGen::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAppCertKeyGen::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_AC_cityName, &CAppCertKeyGen::OnCbnSelchangeComboAccityname)
	//ON_CBN_SELCHANGE(IDC_COMBO_AC_index, &CAppCertKeyGen::OnCbnSelchangeComboAcindex)
END_MESSAGE_MAP()


// CAppCertKeyGen ��Ϣ�������
BOOL CAppCertKeyGen::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)  
	{
		if(GetFocus()->GetDlgCtrlID()==IDOK)//���»س��������ǰ���������Լ������Ŀؼ���
        {                                           
            CAppCertKeyGen::OnBnClickedOk();//����Լ��Ĵ������
        }
		if(GetFocus()->GetDlgCtrlID()==IDCANCEL)//���»س��������ǰ���������Լ������Ŀؼ���
        {                                           
            CAppCertKeyGen::OnBnClickedCancel();//����Լ��Ĵ������
        }
        return TRUE;
	}
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CAppCertKeyGen::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = 0;
	UpdateData(TRUE);

	if(m_ac_appName.IsEmpty())
	{
		MessageBox("Ӧ�����Ʋ���Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_appName.GetLength()>20)
	{
		MessageBox("Ӧ�����Ʋ��ܳ���20���ַ���","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_cityName_cs.IsEmpty())
	{
		MessageBox("��ѡ��ʡ�ݻ�ֱϽ�У�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_areaName_cs.IsEmpty())
	{
		MessageBox("��ѡ����л����أ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_cnName.IsEmpty())
	{
		MessageBox("������������ƣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_atName.IsEmpty())
	{
		MessageBox("������������ƣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_eMail.IsEmpty())
	{
		MessageBox("������������䣡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_pinf.GetLength()<8)
	{
		MessageBox("PIN�볤�Ȳ���С��8λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_pinf != m_ac_pins)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_ac_pinf))
	{
		MessageBox("PIN�벻��ȫ�����֣�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}


	void * hSessionHandle = phHandle_appCertMngr;

	if(0 == isUp)
	{
		unsigned int index_del=atoi((LPSTR)(LPCTSTR)in_keyIndex);
		INT_PTR nRes = 0x00;
		nRes = MessageBox("ȷ��Ҫ���¸���Կ��Ϣ��","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
		{
			return;
		}
		ret = Km_AppKeyDestroy(hSessionHandle,1,1,&index_del);
		if(0 != ret)
		{
			char outApkd[100]={0x00};
			retValueParse(ret,outApkd);
			CString index_uig_num_cs;
			index_uig_num_cs.Format("%d",index_del);
			MessageBox("���ٵ�"+index_uig_num_cs+ "��Ӧ����Կʧ�ܣ������룺"+(CString)outApkd,"��ʾ");
			return;
		}
	}



	unsigned char pucIndex[32]={0x00};
	unsigned int uiIndexLength = m_ac_index_cs.GetLength();
	memcpy(pucIndex,m_ac_index_cs.GetBuffer(),m_ac_index_cs.GetLength());
	unsigned int uikeyIndex = atoi(m_ac_index_cs);
	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	unsigned int uiHashAlgo;

	if(m_ac_alg_cs == "RSA 1024")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 1024;
		uiHashAlgo = SGD_SHA1;
	}
	if(m_ac_alg_cs == "RSA 2048")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 2048;
		uiHashAlgo = SGD_SHA1;
	}
	if(m_ac_alg_cs == "SM2")
	{
		uiAlgo = SGD_SM2_1;
		uiKeyLength = 256; 
		uiHashAlgo = SGD_SM3;
	}
	
	unsigned char pucKeyPasswd[32]={0x00};
	memcpy(pucKeyPasswd,m_ac_pinf.GetBuffer(),m_ac_pinf.GetLength());
	unsigned int uiKeyPasswdLength = m_ac_pinf.GetLength();
	unsigned char pucAppName[50]={0x00};
	memcpy(pucAppName,m_ac_appName.GetBuffer(),m_ac_appName.GetLength());
	unsigned int uiAppNameLength = m_ac_appName.GetLength(); 
	unsigned int uiKeyType;
	if(m_ac_keyType_cs == "ǩ�������ܹ�����Կ")
		uiKeyType = 2;
	if(m_ac_keyType_cs == "ǩ�������ܲ�������Կ")
		uiKeyType = 3;
	if(m_ac_keyType_cs == "ǩ����Կ")
		uiKeyType = 0;
	if(m_ac_keyType_cs == "������Կ")
		uiKeyType = 1;
	unsigned char pucCityName[50]={0x00};
	memcpy(pucCityName,m_ac_cityName_cs.GetBuffer(),m_ac_cityName_cs.GetLength());
	unsigned int uiCityNameLength = m_ac_cityName_cs.GetLength();
	unsigned char pucCNName[50]={0x00};
	memcpy(pucCNName,m_ac_cnName.GetBuffer(),m_ac_cnName.GetLength());
	unsigned int uiCNNameLength = m_ac_cnName.GetLength();
	unsigned char pucAreaName[50]={0x00};
	memcpy(pucAreaName,m_ac_areaName_cs.GetBuffer(),m_ac_areaName_cs.GetLength());
	unsigned int uiAreaNameLength = m_ac_areaName_cs.GetLength();
	unsigned char pucAtName[50]={0x00};
	memcpy(pucAtName,m_ac_atName.GetBuffer(),m_ac_atName.GetLength());
	unsigned int uiAtNameLength = m_ac_atName.GetLength();
	unsigned char pucEmail[50]={0x00};
	memcpy(pucEmail,m_ac_eMail.GetBuffer(),m_ac_eMail.GetLength());
	unsigned int uiEmailLength = m_ac_eMail.GetLength();

	unsigned char pucOUValue[50]={0x00};
	unsigned int uiOUValueLength = m_ac_OUvalue.GetLength();
	memcpy(pucOUValue,m_ac_OUvalue.GetBuffer(),m_ac_OUvalue.GetLength());
	

	ret = Km_GenAppKey_SIG(hSessionHandle,uikeyIndex,uiAlgo,uiKeyLength,pucKeyPasswd,uiKeyPasswdLength,pucAppName,uiAppNameLength,
		uiKeyType,pucCityName,uiCityNameLength,pucCNName,uiCNNameLength,pucAreaName,uiAreaNameLength,pucAtName,uiAtNameLength,
		pucEmail,uiEmailLength,pucOUValue,uiOUValueLength);
	if(0 == ret && 1 == isUp)
	{
		this->OnOK();
		INT_PTR nRes;
		
		/*MessageBox("    ��ӳɹ�","��ʾ");*/
		nRes = MessageBox("��ӳɹ�,�Ƿ�Ҫ��������֤������","",MB_ICONQUESTION|MB_OKCANCEL);
		if(nRes == IDOK)
		{
			//-------------------------�������������֤������ӿ�------------------------
			//(unsigned char *)"C=CN,S=�Ϻ�,L=�Ϻ�,O=�ջ�,OU=�з���,CN=����֤��1,E=asdfg@qq.com",
			unsigned char pucRequest[1024]={0x00};
			memcpy(pucRequest,"C=",strlen("C="));
			strncat((char*)pucRequest,m_ac_cnName,m_ac_cnName.GetLength());
			strncat((char*)pucRequest,",S=",strlen(",S="));
			strncat((char*)pucRequest,m_ac_cityName_cs,m_ac_cityName_cs.GetLength());
			strncat((char*)pucRequest,",L=",strlen(",L="));
			strncat((char*)pucRequest,m_ac_areaName_cs,m_ac_areaName_cs.GetLength());
			strncat((char*)pucRequest,",O=",strlen(",O="));
			strncat((char*)pucRequest,m_ac_atName,m_ac_atName.GetLength());
			strncat((char*)pucRequest,",OU=",strlen(",OU="));
			strncat((char*)pucRequest,m_ac_OUvalue,m_ac_OUvalue.GetLength());
			strncat((char*)pucRequest,",CN=",strlen(",CN="));
			strncat((char*)pucRequest,m_ac_appName,m_ac_appName.GetLength());
			strncat((char*)pucRequest,",E=",strlen(",E="));
			strncat((char*)pucRequest,m_ac_eMail,m_ac_eMail.GetLength());
			//printf("pucRequest == %s\n",pucRequest);
			unsigned int uiRequestLength = strlen((char*)pucRequest);
			unsigned char pucB64Req[2048]={0x00};
			unsigned char pucReq[1024]={0x00};
			ret = Sig_GenCertRequest(hSessionHandle,26115,uiHashAlgo,uiAlgo,uiIndexLength,pucIndex,uiKeyPasswdLength,pucKeyPasswd,
									uiRequestLength,pucRequest,pucB64Req,pucReq);
			if(0 == ret)
			{
				//д�ļ�
				CMyUtil::Write2File("C:\\pucB64Req.txt",pucB64Req,strlen((char*)pucB64Req));
				//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pucReq.txt",pucReq,strlen((char*)pucReq));
				MessageBox("֤���������ɳɹ����ļ�������C:\\pucB64Req.txt��","��ʾ",MB_ICONEXCLAMATION);
			}
			else if(0 != ret)
			{
				char outGapkReq[100]={0x00};
				retValueParse(ret,outGapkReq);
				MessageBox("    ֤����������ʧ��"+(CString)outGapkReq,"��ʾ");
			}
		}
		//CDialogEx::OnOK();
		
	}
	else if(0 != ret && 1 == isUp)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		//CDialogEx::OnOK();
		this->OnCancel();
		MessageBox("    ���ʧ��"+(CString)outGapk,"��ʾ");
	}
	else if(0 == ret && 0 == isUp)
	{
		MessageBox("�����ɹ���","��ʾ",MB_ICONEXCLAMATION);
		this->OnOK();
	}

}


void CAppCertKeyGen::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CAppCertKeyGen::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/****************����CComBox������Ϊֻ����ֹ�û��Լ�������ɲ���Ҫ�Ĵ���******************************/
	CAppCertKeyGen:: SetReadOnly();
	/***********************************************/
	CWnd *cWnd = GetDlgItem(IDC_STATIC_AC_TITLE);
	if(isUp)
	{
		this->SetWindowText("Ӧ����Կ����");
		cWnd->SetWindowText("Ӧ����Կ����");
	
	
		// TODO:  �ڴ���Ӷ���ĳ�ʼ��
		int one = acKeyIndex;
		CString cs_keyIndex;
		CString index;
		index.Format("%d",one);
		cs_keyIndex = "00"+index;//���ݵĸ�ʽ����������Ҫ��дһ���µķ��� 
		SetDlgItemText(IDC_COMBO_AC_index,cs_keyIndex);

		int data = 0;
		for(int i=0;i<256;i++)
		{
			if(1 == acKeyIndex_array[i][1])
			{
				data = acKeyIndex_array[i][0];
				index.Format("%d",data);
				cs_keyIndex = "00"+index;
				m_ac_index.AddString(cs_keyIndex);
			}
		}


		cWnd = GetDlgItem(IDC_EDIT_AC_apname);//���۽���Ӧ������
		cWnd->SetFocus();
		SetDlgItemText(IDC_EDIT_AC_cnName,"CN");
		//SetDlgItemText(IDC_COMBO_AC_alg, _T("SM2"));  
		SetDlgItemText(IDC_COMBO_AC_alg, _T("RSA 1024"));
		SetDlgItemText(IDC_COMBO_AC_keyType, _T("ǩ�������ܹ�����Կ"));
	}
	else if(!isUp)
	{
		this->SetWindowText("Ӧ����Կ����");
		cWnd->SetWindowText("Ӧ����Կ����");

		SetDlgItemText(IDC_EDIT_AC_apname,in_certname);
		SetDlgItemText(IDC_COMBO_AC_cityName,in_city);
		SetDlgItemText(IDC_EDIT_AC_cnName,in_nation);
		
		SetDlgItemText(IDC_EDIT_AC_atName,in_organization);
		SetDlgItemText(IDC_EDIT_AC_eMail,in_email);
		SetDlgItemText(IDC_EDIT_APPCERT_OU,in_organizationUnite);
		SetDlgItemText(IDC_COMBO_AC_index,in_keyIndex);
		

		SetDlgItemText(IDC_COMBO_AC_alg,in_algid);
		SetDlgItemText(IDC_COMBO_AC_keyType,in_keyType);

		int num=0;
		CAppCertKeyGen::GetCityInUpdate(in_city,&num);
		CAppCertKeyGen::ShowCityInfo(num);

		SetDlgItemText(IDC_COMBO_AC_areaName,in_area);
	}


	m_ac_alg.AddString(_T("RSA 1024"));     
	m_ac_alg.AddString(_T("RSA 2048")); 
	m_ac_alg.AddString(_T("SM2"));

	m_ac_appType.AddString(_T("Ӧ�÷ǶԳ���Կ"));
	SetDlgItemText(IDC_COMBO_AC_apType, _T("Ӧ�÷ǶԳ���Կ"));

	//m_ac_keyType.AddString(_T("ǩ����Կ"));
	//m_ac_keyType.AddString(_T("������Կ"));
	m_ac_keyType.AddString(_T("ǩ�������ܹ�����Կ"));
	m_ac_keyType.AddString(_T("ǩ�������ܲ�������Կ"));

	CAppCertKeyGen::WriteCityInfo();

	m_ac_cityName.AddString(_T("������"));
	m_ac_cityName.AddString(_T("�Ϻ���"));
	m_ac_cityName.AddString(_T("�����"));
	m_ac_cityName.AddString(_T("������"));
	m_ac_cityName.AddString(_T("�ӱ�ʡ"));
	m_ac_cityName.AddString(_T("ɽ��ʡ"));
	m_ac_cityName.AddString(_T("̨��ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("������ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("�㽭ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("ɽ��ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("�㶫ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("�Ĵ�ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("�ຣʡ"));
	m_ac_cityName.AddString(_T("����ʡ"));
	m_ac_cityName.AddString(_T("����׳��������"));
	m_ac_cityName.AddString(_T("����������"));
	m_ac_cityName.AddString(_T("���Ļ���������"));
	m_ac_cityName.AddString(_T("�½�ά���������"));
	m_ac_cityName.AddString(_T("���ɹ�������"));
	m_ac_cityName.AddString(_T("�����ر�������"));
	m_ac_cityName.AddString(_T("����ر�������"));
	SetDlgItemText(IDC_COMBO_AC_cityName, _T("����"));
	SetDlgItemText(IDC_COMBO_AC_areaName, _T("������"));

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAppCertKeyGen::OnCbnSelchangeComboAccityname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel; 
    nSel = m_ac_cityName.GetCurSel();   

	CAppCertKeyGen::ShowCityInfo(nSel);
}

void CAppCertKeyGen::WriteCityInfo()
{
	char ShangHai[][50]={"������","¬����","�����","������","������","������","բ����","�����","������","������","��ɽ��","�ζ���","�ֶ�����"
							,"��ɽ��","�ɽ���","������","�ϻ���","������","������"};
	CAppCertKeyGen::WriteProviceInfo("�Ϻ���",(char *)ShangHai,19);

	char BeiJing[][50]={"������","������","������","������","������","��̨��","ʯ��ɽ��","������","��ͷ����","��ɽ��","ͨ����","˳����"
						,"��ƽ��","������","������","ƽ����","������","������"};
	CAppCertKeyGen::WriteProviceInfo("������",(char *)BeiJing,18);

	char TianJin[][50]={"��ƽ��","�Ӷ���","������","�Ͽ���","�ӱ���","������","������","������","�����","������","������","������","������"
						,"������","������","������","������","������"};
	CAppCertKeyGen::WriteProviceInfo("�����",(char *)TianJin,18);

	char ChongQing[][50]={"������","������","������","��ɿ���","������","ɳƺ����","��������","�ϰ���","������","��ʢ��","˫����","�山��"
							,"������","ǭ����","������","�뽭��","������","ͭ����","������","�ٲ���","�ɽ��","��ƽ��","�ǿ���","�ᶼ��"
							,"�潭��","��¡��","�ҡ���","������","������","�����","��ɽ��","��Ϫ��","ʯ��������������"
						,"��ɽ����������������","��������������������","��ˮ����������������"};
	CAppCertKeyGen::WriteProviceInfo("������",(char *)ChongQing,36);

	char HeBei[][50]={"ʯ��ׯ��","��ɽ��","�ػʵ���","������","��̨��","������","�żҿ���","�е���","������","�ȷ���","��ˮ��"};
	CAppCertKeyGen::WriteProviceInfo("�ӱ�ʡ",(char *)HeBei,11);

	char ShanXi[][50]={"̫ԭ��","��ͬ��","��Ȫ��","������","������","˷����","������","�˳���","������","�ٷ���","������"};
	CAppCertKeyGen::WriteProviceInfo("ɽ��ʡ",(char *)ShanXi,11);

	char TaiWan[][50]={"̨����","������","��¡��","̨����","̨����","������","������","̨����","������","��԰��","������","������","̨����"
						,"�û���","��Ͷ��","������","������","̨����","������","������","�����","̨����","������"};
	CAppCertKeyGen::WriteProviceInfo("̨��ʡ",(char *)TaiWan,23);

	char LiaoNing[][50]={"������","������","��ɽ��","��˳��","��Ϫ��","������","������","Ӫ����","������","������","�̽���","������"
						,"������","��«����"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)LiaoNing,14);

	char JiLin[][50]={"������","������","��ƽ��","��Դ��","ͨ����","��ɽ��","��ԭ��","�׳���","�ӱ߳�����������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)JiLin,9);

	char HeiLongJiang[][50]={"��������","���������","�׸���","˫Ѽɽ��","������","������","������","ĵ������","��ľ˹��","��̨����"
							,"�ں���","�绯��","���˰������"};
	CAppCertKeyGen::WriteProviceInfo("������ʡ",(char *)HeiLongJiang,13);

	char JiangSu[][50]={"�Ͼ���","������","������","������","������","��ͨ��","���Ƹ���","������","�γ���","������","����","̩����"
						,"��Ǩ��"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)JiangSu,13);

	char ZheJiang[][50]={"������","������","������","������","������","������","����","������","��ɽ��","̨����","��ˮ��"};
	CAppCertKeyGen::WriteProviceInfo("�㽭ʡ",(char *)ZheJiang,11);

	char AnHui[][50]={"�Ϸ���","�ߺ���","������","������","��ɽ��","������","ͭ����","������","��ɽ��","������","������","������"
						,"������","������","������","������","������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)AnHui,17);

	char FuJian[][50]={"������","������","������","������","Ȫ����","������","��ƽ��","������","������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)FuJian,9);

	char JiangXi[][50]={"�ϲ���","��������","Ƽ����","�Ž���","������","ӥ̶��","������","������","�˴���","������","������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)JiangXi,11);

	char ShanDong[][50]={"������","�ൺ��","�Ͳ���","��ׯ��","��Ӫ��","��̨��","Ϋ����","������","̩����","������","������","������"
						,"������","������","�ĳ���","������","������"};
	CAppCertKeyGen::WriteProviceInfo("ɽ��ʡ",(char *)ShanDong,17);

	char HeNan[][50]={"֣����","������","������","ƽ��ɽ��","������","�ױ���","������","������","�����","�����","�����","����Ͽ��"
						,"������","������","������","�ܿ���","פ�����","��Դ��"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)HeNan,18);

	char HuBei[][50]={"�人��","��ʯ��","ʮ����","������","�˲���","�差��","������","������","Т����","�Ƹ���","������","������","������"
						,"������","Ǳ����","��ũ������","��ʩ����������������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)HuBei,17);

	char HuNan[][50]={"��ɳ��","������","��̶��","������","������","������","������","�żҽ���","������","������","������","������"
						,"¦����","��������������������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)HuNan,14);

	char GuangDong[][50]={"������","������","�麣��","��ͷ��","�ع���","��ɽ��","������","տ����","ï����","������","������","÷����"
							,"��β��","��Դ��","������","��Զ��","��ݸ��","��ɽ��","������","������","�Ƹ���"};
	CAppCertKeyGen::WriteProviceInfo("�㶫ʡ",(char *)GuangDong,21);

	char GanSu[][50]={"������","�����","������","��ˮ��","��������","������","��Ҵ��","ƽ����","��Ȫ��","������","������","¤����"
					,"���Ļ���������","���ϲ���������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)GanSu,14);

	char SiChuan[][50]={"�ɶ���","�Թ���","��֦����","������","������","������","��Ԫ��","������","�ڽ���","��ɽ��","�ϳ���","üɽ��"
						,"�˱���","�㰲��","������","�Ű���","������","������","���Ӳ���Ǽ��������","���β���������","��ɽ����������"};
	CAppCertKeyGen::WriteProviceInfo("�Ĵ�ʡ",(char *)SiChuan,21);

	char GuiZhou[][50]={"������","����ˮ��","������","��˳��","ͭ�ʵ���","�Ͻڵ���","ǭ���ϲ���������������","ǭ�������嶱��������"
						,"ǭ�ϲ���������������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)GuiZhou,9);

	char HaiNan[][50]={"������","������","��ָɽ��","����","������","�Ĳ���","������","������","������","������","�Ͳ���","�ٸ���"
						,"��ɳ����������","��������������","�ֶ�����������","��ˮ����������","��ͤ��������������","������������������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)HaiNan,18);

	char YunNan[][50]={"������","������","��Ϫ��","��ɽ��","��ͨ��","������","˼é��","�ٲ���","��ɽ׳������������","��ӹ���������������"
						,"��˫���ɴ���������","��������������","�������������","�º���徰����������","ŭ��������������","�������������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)YunNan,16);

	char QingHai[][50]={"������","��������","��������������","���ϲ���������","���ϲ���������","�������������","��������������","�����ɹ������������"};
	CAppCertKeyGen::WriteProviceInfo("�ຣʡ",(char *)QingHai,8);

	char ShanXi_2[][50]={"������","ͭ����","������","������","μ����","�Ӱ���","������","������","������","������"};
	CAppCertKeyGen::WriteProviceInfo("����ʡ",(char *)ShanXi_2,10);

	char GuangXi[][50]={"������","������","������","������","������","���Ǹ���","������","�����","������","��ɫ��","������","�ӳ���"
						,"������","������"};
	CAppCertKeyGen::WriteProviceInfo("����׳��������",(char *)GuangXi,14);

	char XiZang[][50]={"������","��������","��������","ɽ�ϵ���","�տ������","�������","��֥����"};
	CAppCertKeyGen::WriteProviceInfo("����������",(char *)XiZang,7);

	char NingXia[][50]={"������","ʯ��ɽ��","������","��ԭ��","������"};
	CAppCertKeyGen::WriteProviceInfo("���Ļ���������",(char *)NingXia,5);

	char XinJiang[][50]={"��³ľ����","����������","ʯ������","��������","ͼľ�����","�������","��³����","��������","��ʲ��","������"
						,"������","��ͼʲ��","�������","������","������","��Ȫ��","������","������","������","������","������","����̩��"};
	CAppCertKeyGen::WriteProviceInfo("�½�ά���������",(char *)XinJiang,22);

	char NeiMengGu[][50]={"���ͺ�����","��ͷ��","�ں���","�����","ͨ����","������˹��","���ױ�����","�����׶���","�����첼��","���ֹ�����"
							,"�˰���","��������"};
	CAppCertKeyGen::WriteProviceInfo("���ɹ�������",(char *)NeiMengGu,12);

	char AoMen[][50]={"�����ر�������"};
	CAppCertKeyGen::WriteProviceInfo("�����ر�������",(char *)AoMen,1);

	char HongKong[][50]={"����ر�������"};
	CAppCertKeyGen::WriteProviceInfo("����ر�������",(char *)HongKong,1);
}

void CAppCertKeyGen::WriteProviceInfo(CString ProName,char *city,int num)
{
	if(city==NULL)
		return;
	for(int i =0;i<num;i++)
	{
		CString iii;
		iii.Format("%d",i);
		::WritePrivateProfileString("ProviceName",ProName+iii,(LPCSTR)&(city)[i*50],"c://city.ini");
	}
	CString i_num;
	i_num.Format("%d",num);
	::WritePrivateProfileString("ProviceName",ProName+(CString)"����",i_num,"c://city.ini");
}

void CAppCertKeyGen::ReadProviceInfo(CString proName)
{
	CString cityName;
	int Count = 0;
	Count = GetPrivateProfileInt("ProviceName",proName+(CString)"����",0,"c://city.ini");
	for(int i=0;i<Count;i++)
	{
		CString ii;
		ii.Format("%d",i);
		GetPrivateProfileString("ProviceName",proName+ii,"Ĭ������",cityName.GetBuffer(MAX_PATH),MAX_PATH,"c://city.ini");
		m_ac_areaName.AddString(cityName);
	}
}

void CAppCertKeyGen::ShowCityInfo(int num)
{
	m_ac_areaName.ResetContent();

	switch(num)
	{
	case 0:
		CAppCertKeyGen::ReadProviceInfo("������");
		break;
	case 1:
		CAppCertKeyGen::ReadProviceInfo("�Ϻ���");
		break;
	case 2:
		CAppCertKeyGen::ReadProviceInfo("�����");
		break;
	case 3:
		CAppCertKeyGen::ReadProviceInfo("������");
		break;
	case 4:
		CAppCertKeyGen::ReadProviceInfo("�ӱ�ʡ");
		break;
	case 5:
		CAppCertKeyGen::ReadProviceInfo("ɽ��ʡ");
		break;
	case 6:
		CAppCertKeyGen::ReadProviceInfo("̨��ʡ");
		break;
	case 7:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 8:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 9:
		CAppCertKeyGen::ReadProviceInfo("������ʡ");
		break;
	case 10:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 11:
		CAppCertKeyGen::ReadProviceInfo("�㽭ʡ");
		break;
	case 12:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 13:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 14:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 15:
		CAppCertKeyGen::ReadProviceInfo("ɽ��ʡ");
		break;
	case 16:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 17:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 18:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 19:
		CAppCertKeyGen::ReadProviceInfo("�㶫ʡ");
		break;
	case 20:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 21:
		CAppCertKeyGen::ReadProviceInfo("�Ĵ�ʡ");
		break;
	case 22:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 23:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 24:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 25:
		CAppCertKeyGen::ReadProviceInfo("�ຣʡ");
		break;
	case 26:
		CAppCertKeyGen::ReadProviceInfo("����ʡ");
		break;
	case 27:
		CAppCertKeyGen::ReadProviceInfo("����׳��������");
		break;
	case 28:
		CAppCertKeyGen::ReadProviceInfo("����������");
		break;
	case 29:
		CAppCertKeyGen::ReadProviceInfo("���Ļ���������");
		break;
	case 30:
		CAppCertKeyGen::ReadProviceInfo("�½�ά���������");
		break;
	case 31:
		CAppCertKeyGen::ReadProviceInfo("���ɹ�������");
		break;
	case 32:
		CAppCertKeyGen::ReadProviceInfo("�����ر�������");
		break;
	case 33:
		CAppCertKeyGen::ReadProviceInfo("����ر�������");
		break;
	}
}

void CAppCertKeyGen::GetCityInUpdate(CString city,int *num)
{
	if(city=="������")
		*num = 0;
	else if(city=="�Ϻ���")
		*num = 1;
	else if(city=="�����")
		*num = 2;
	else if(city=="������")
		*num = 3;
	else if(city=="�ӱ�ʡ")
		*num = 4;
	else if(city=="ɽ��ʡ")
		*num = 5;
	else if(city=="̨��ʡ")
		*num = 6;
	else if(city=="����ʡ")
		*num = 7;
	else if(city=="����ʡ")
		*num = 8;
	else if(city=="������ʡ")
		*num = 9;
	else if(city=="����ʡ")
		*num = 10;
	else if(city=="�㽭ʡ")
		*num = 11;
	else if(city=="����ʡ")
		*num = 12;
	else if(city=="����ʡ")
		*num = 13;
	else if(city=="����ʡ")
		*num = 14;
	else if(city=="ɽ��ʡ")
		*num = 15;
	else if(city=="����ʡ")
		*num = 16;
	else if(city=="����ʡ")
		*num = 17;
	else if(city=="����ʡ")
		*num = 18;
	else if(city=="�㶫ʡ")
		*num = 19;
	else if(city=="����ʡ")
		*num = 20;
	else if(city=="�Ĵ�ʡ")
		*num = 21;
	else if(city=="����ʡ")
		*num = 22;
	else if(city=="����ʡ")
		*num = 23;
	else if(city=="����ʡ")
		*num = 24;
	else if(city=="�ຣʡ")
		*num = 25;
	else if(city=="����ʡ")
		*num = 26;
	else if(city=="����׳��������")
		*num = 27;
	else if(city=="����������")
		*num = 28;
	else if(city=="���Ļ���������")
		*num = 29;
	else if(city=="�½�ά���������")
		*num = 30;
	else if(city=="���ɹ�������")
		*num = 31;
	else if(city=="�����ر�������")
		*num = 32;
	else if(city=="����ر�������")
		*num = 33;
}


void CAppCertKeyGen:: SetReadOnly()
{
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_index))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit2 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_cityName))->GetWindow(GW_CHILD));	
	pEdit2->SetReadOnly(TRUE);
	CEdit* pEdit3 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_areaName))->GetWindow(GW_CHILD));	
	pEdit3->SetReadOnly(TRUE);
	CEdit* pEdit4 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_alg))->GetWindow(GW_CHILD));	
	pEdit4->SetReadOnly(TRUE);
	CEdit* pEdit5 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_keyType))->GetWindow(GW_CHILD));	
	pEdit5->SetReadOnly(TRUE);
	CEdit* pEdit6 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_apType))->GetWindow(GW_CHILD));	
	pEdit6->SetReadOnly(TRUE);
	return ;
}