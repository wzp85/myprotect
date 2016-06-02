// SignPWMAdmin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SignPWMAdmin.h"
#include "afxdialogex.h"

#include "InitKeyTip.h"
#include "ph_PWMngrDlg.h"
#include "DAI.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ")
#define FILESIZE_SIGDEVADMIN 1024
#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDAO.h"
#include "InitDevInfo.h"
#include "IsInit.h"


// CSignPWMAdmin �Ի���

BYTE adm_bkRand_1[32]={0x00};
BYTE adm_bkRand_2[32]={0x00};
BYTE adm_bkRand_3[32]={0x00};
BYTE adm_bkRand_4[32]={0x00};
BYTE adm_bkRand_5[32]={0x00};

int KeyMnGer_SQ=0;//�ж�config.txt���Ƿ�ǩ����ȨԱ
int KeyMnGer_AQ=0;//�ж�config.txt���Ƿ�ǩ����ȫ���Ա
IMPLEMENT_DYNAMIC(CSignPWMAdmin, CDialogEx)

CSignPWMAdmin::CSignPWMAdmin(int isOneToMore,int isKeyManager,int keyManagerNum,int isReSig,int keylen,int n_Count,CString data,void *key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSignPWMAdmin::IDD, pParent)
	, m_adminName(_T(""))
	, m_adminPhonenumber(_T(""))
	, m_adminPaperNum(_T(""))
	, m_adminPwd(_T(""))
	, m_adminConPwd(_T(""))
	, m_maxAdminNum(_T(""))
	, m_paperType_CS(_T(""))
	, m_caption(_T(""))
{
	isKMer=isKeyManager;
	KMerNumber=keyManagerNum;
	isReSigAdmin = isReSig;
	isOneToMore_kmer=isOneToMore;//�ñ��������ж��Ƿ�����1�Զ����

	isReadOnly = FALSE;
	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
	if(!data.IsEmpty())
		m_caption = data;
	else
		m_caption = "ǩ������Ա";
	admin_count = 0;
	adminNum = n_Count;
	key_length = keylen;
}

CSignPWMAdmin::~CSignPWMAdmin()
{
}

void CSignPWMAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADMINNAME_EDIT, m_adminName);
	DDX_Text(pDX, IDC_ADMINPHONE_EDIT, m_adminPhonenumber);
	DDX_Text(pDX, IDC_ADMINPAPNUM_EDIT, m_adminPaperNum);
	DDX_Text(pDX, IDC_ADMINPWD_EDIT, m_adminPwd);
	DDX_Text(pDX, IDC_ADMINCONPWD_EDIT, m_adminConPwd);
	DDX_Text(pDX, IDC_MAXADMINCOUNT_EDIT, m_maxAdminNum);
	DDX_Control(pDX, IDC_PAPERTYPE_COMBO, m_paperType);
	DDX_CBString(pDX, IDC_PAPERTYPE_COMBO, m_paperType_CS);
	DDX_Text(pDX, IDC_STATIC_adm, m_caption);
	DDX_Control(pDX, IDC_MAXADMINCOUNT_EDIT, m_adminCount);
}

BOOL CSignPWMAdmin::OnInitDialog()
{
	CDialogEx::OnInitDialog();   
  
    // Add "About..." menu item to system menu.   
 
    // IDM_ABOUTBOX must be in the system command range.   
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);   
    ASSERT(IDM_ABOUTBOX < 0xF000);   

    CMenu* pSysMenu = GetSystemMenu(FALSE);   
    if (pSysMenu != NULL)   
    {   
        BOOL bNameValid;   
        CString strAboutMenu;   
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);   
        ASSERT(bNameValid);   
        if (!strAboutMenu.IsEmpty())   
        {   
            pSysMenu->AppendMenu(MF_SEPARATOR);   
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);   
        }   
    }   
  
    // Set the icon for this dialog.  The framework does this automatically   
    //  when the application's main window is not a dialog   
    SetIcon(m_hIcon, TRUE);         // Set big icon   
    SetIcon(m_hIcon, FALSE);        // Set small icon   
  
    // TODO: Add extra initialization here   
	CWnd *cWnd = GetDlgItem(IDC_ADMINNAME_EDIT);
	cWnd->SetFocus();

	isTwoPro = 0;

    m_paperType.AddString(_T("���֤"));       
    m_paperType.AddString(_T("����"));   
 
    SetDlgItemText(IDC_PAPERTYPE_COMBO, _T("���֤"));  
	if(!m_caption.IsEmpty())
		SetDlgItemText(IDC_STATIC_adm,m_caption);

	if(isKMer==0)//�豸����Ա��ʾ
	{
		CString admin_count_cs;
		if(0 != admin_count)
		{
			admin_count_cs.Format("%d",admin_count);
			SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,admin_count_cs);
			m_adminCount.SetReadOnly(isReadOnly);
		}
		else
		{
			admin_count_cs.Format("%d",1);
			SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,admin_count_cs);
		}
		/***********�豸����Ա����ǩ�����ڴ˴��ж��Ƿ�ǩ����ȨԱ�����Ա������ȫ�ֱ�������ʽ�޶������ǩ��״̬**********************/

			int length=0;
			//int KeyMnGer_SQ=0;
			
			CMyUtil::ReadData("./config.txt",NULL,&length);
			BYTE *data = new BYTE[length+1];
			memset(data,0x00,length+1);
			CMyUtil::ReadData("./config.txt",data,&length);

			/*********************��Կ��ȨԱ**********************/
			char *source=(char*)data;
			char *str_SQ=strstr(source,"KEY_MANAGER_SQ=");//�ж��Ƿ�ǩ����Կ��ȨԱ����Կ��ȨԱ�̶�һ����
			char *tem_SQ=str_SQ+strlen("KEY_MANAGER_SQ=");
			char *end_SQ=strstr(tem_SQ,"\n");
			char num_buf_SQ[32]={0x00};
			memcpy(num_buf_SQ,tem_SQ,end_SQ-tem_SQ);
			KeyMnGer_SQ=atoi(num_buf_SQ);

			char *str_AQ=strstr(source,"KEY_MANAGER_AQ=");//�ж��Ƿ�ǩ����ȫ���Ա���̶�һ����
			char *tem_AQ=str_AQ+strlen("KEY_MANAGER_AQ=");
			char *end_AQ=strstr(tem_AQ,"\n");
			char num_buf_AQ[32]={0x00};
			memcpy(num_buf_AQ,tem_AQ,end_AQ-tem_AQ);
			KeyMnGer_AQ=atoi(num_buf_AQ);
			
		}




	else if(isKMer==2)//ǩ����ȫ���Ա��ȡ�����ļ��ж���Ŀ
	{
		//�������ļ���ȡ��ȫ���Ա���������,������ʾ
		int length=0;
//		int KMerNumber=0;

		CMyUtil::ReadData("./config.txt",NULL,&length);
		BYTE *data = new BYTE[length+1];
		memset(data,0x00,length+1);
		CMyUtil::ReadData("./config.txt",data,&length);
	

		char *source=(char*)data;
		char *str=strstr(source,"KEY_MANAGER_AQ_NUM=");
		char *tem=str+strlen("KEY_MANAGER_AQ_NUM=");
		char *end=strstr(str,"\n");
		char num_buf[32]={0x00};
		memcpy(num_buf,tem,end-tem);
//		KMerNumber=atoi(num_buf);
		SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,num_buf);
	}
	else if(isKMer==1)//ǩ����Կ��ȨԱ��ȡ�����ļ��ж���Ŀ
	{
		//�������ļ���ȡ��Կ��ȨԱ���������,������ʾ
		int length=0;
//		int KMerNumber=0;

		CMyUtil::ReadData("./config.txt",NULL,&length);
		BYTE *data = new BYTE[length+1];
		memset(data,0x00,length+1);
		CMyUtil::ReadData("./config.txt",data,&length);


		char *source=(char*)data;
		char *str=strstr(source,"KEY_MANAGER_SQ_NUM=");
		char *tem=str+strlen("KEY_MANAGER_SQ_NUM=");
		char *end=strstr(str,"\n");
		char num_buf[32]={0x00};
		memcpy(num_buf,tem,end-tem);
//		KMerNumber=atoi(num_buf);
		SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,num_buf);
	}
 
    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CSignPWMAdmin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSignPWMAdmin::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_PAPERTYPE_COMBO, &CSignPWMAdmin::OnCbnSelchangePapertypeCombo)
END_MESSAGE_MAP()


// CSignPWMAdmin ��Ϣ�������


void CSignPWMAdmin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	void * phSessionHandle = phSHandle;//������Ự������� 
	ADMININFO AdminInfo = {0};
	unsigned int uiAdminNum = atoi(m_maxAdminNum);
//	adm_Count = uiAdminNum;
	num_adm_max = atoi(m_maxAdminNum);
	if(num_adm_max>1)
		isOneToMore_kmer=1;
	unsigned char *pucPubKey;
	unsigned int uiPubKeyLen;
	unsigned char pucSignValue[1024]={0x00};
	unsigned int puiSignValueLen = 1024;

	//����У�鲿��
	if(m_adminName.IsEmpty())
	{
		MessageBox("��������Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminName.GetLength() >= 20)
	{
		MessageBox("����������20���ַ���","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPhonenumber.IsEmpty())
	{
		MessageBox("�绰���벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPhonenumber.GetLength() >= 20)
	{
		MessageBox("�绰���볤�Ȳ��ܳ���20λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPaperNum.IsEmpty())
	{
		MessageBox("֤�����벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPaperNum.GetLength() >= 24)
	{
		MessageBox("֤�����벻����20���ַ���","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperType_CS == "���֤"
		&& m_adminPaperNum.GetLength() != 18 
		&& m_adminPaperNum.GetLength() != 15)
	{
		MessageBox("���֤���볤��Ϊ15��18λ��������Ϸ������֤���룡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd.IsEmpty())
	{
		MessageBox("���������ԱPIN�룡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd.GetLength()<6)
	{
		MessageBox("����ԱPIN�벻��С��6λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd != m_adminConPwd)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_maxAdminNum.IsEmpty())
	{
		MessageBox("������������Ա����","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	//---------��ʽ����ʾ----------//
	INT_PTR nRes;               

	int ret = 0;
	//����ǩ
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(1 == ret)
	{
		MessageBox("���豸ʧ�ܣ���ȷ��key�Ƿ��ã�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	else if(3 == ret)
	{
		nRes = MessageBox("�ò��������ʽ��key��ȷ��Ҫ��ʽ����","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"��Կ������Կ"))
	{
		MessageBox("�����������Կ������Կkey����key���ܱ���ʽ������ȷ�ϲ������Աkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strcmp(label,"�豸����Ա"))
	{
		nRes = MessageBox("��key���豸����Աkey��ȷ��Ҫ��ʽ�����������ɣ�","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"��Կ��ȨԱ"))
	{
		nRes = MessageBox("��key����Կ��ȨԱkey��ȷ��Ҫ��ʽ�����������ɣ�","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"��ȫ���Ա"))
	{
		nRes = MessageBox("��key�ǰ�ȫ���Աkey��ȷ��Ҫ��ʽ�����������ɣ�","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	//��ǩ���������Ա���˴������жϲ�����ǲ����Ѿ�д����Ĺ���Աkey
	BOOL isReWrite = FALSE;
	if(1 < uiAdminNum && 1 < adminNum)
	{
		char label_admin_signText[17]={0x00};
		ret = CMyUtil::ReadLabel("LBL_CERT_admin_RANDOM",label_admin_signText);
		if(0 != ret)
		{
			nRes = MessageBox("������Ĳ��Ǳ�ϵͳkey��ȷ��Ҫ��ʽ����","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
			if(nRes != IDOK)
				return;
		}
		if(2 == adminNum && !strncmp(label_admin_signText,(const char*)adm_bkRand_1,16))
		{
			isReWrite = TRUE;
		}
		if(3 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)))
		{
			isReWrite = TRUE;
		}
		if(4 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_3,16)))
		{
			isReWrite = TRUE;
		}
		if(5 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_3,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_4,16)))
		{	
			isReWrite = TRUE;
		}
		if(isReWrite)
		{
			MessageBox("��������Ǹո�д����Ĺ���Աkey���뻻��һ������Աkey������","",MB_ICONEXCLAMATION);
			return;
		}
	}

	//��ȡ����Ա��Ϣ�б���ȷ���ù���Ա�����к�
	int id_adm = 0;
	int num_adm = 0;
	ret = CMyUtil::GetAdminID(phSessionHandle,&id_adm,&num_adm);
	if(0 == ret)
		AdminInfo.iAdminId = id_adm + 1;
	else
	{
		char outGAI[100]={0x00};
		retValueParse(ret,outGAI);
		MessageBox("��ȡ����Ա���к�ʧ��"+(CString)outGAI,"��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	//����ǩ��ʱɾ���Ѿ����ڵĹ���Ա
	if(1 == isReSigAdmin)
	{
		while(0 < id_adm)
		{
			ret = Km_DelAdmin(phSessionHandle,id_adm);
			if(0 != ret)
			{
				char outDA[100]={0x00};
				retValueParse(ret,outDA);
				MessageBox("ɾ������Աʧ��"+(CString)outDA,"��ʾ",MB_ICONWARNING | MB_OK);
			}
			id_adm--;
		}
		AdminInfo.iAdminId = 1;
	}
	
	//��ȡ��Կ
	unsigned int algId_DevKey;
	HAPPLICATION application;	
	RSAPUBLICKEYBLOB pBlob={0x00};
	ECCPUBLICKEYBLOB epPubKey={0x00};
	DEVKEYINFO devInfo={0x00};
	ret = Km_GetDevKeyInfo(phSessionHandle,&devInfo);
	if(0 != ret)
	{
		char outGdki[100]={0x00};
		retValueParse(ret,outGdki);
		MessageBox("��ȡ�豸��Կ��Ϣʧ�ܣ��޷�ǩ������Ա��"+(CString)outGdki,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	algId_DevKey = devInfo.uiAlgo;
	key_length = devInfo.uiKeyLen;
	if(key_length == 2048)
		key_length = 1024;
	if(SGD_RSA == algId_DevKey)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminPwd,&application,&pBlob,NULL,key_length);
		//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_4.txt",(unsigned char*)&pBlob,sizeof(RSAPUBLICKEYBLOB));
	}
	else if(SGD_SM2_1 == algId_DevKey)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminPwd,&application,NULL,&epPubKey,key_length);
	}
	if(0 != ret && ret != SAR_NOTSUPPORTKEYTYPE)
	{
		MessageBox("���ɹ�Կʧ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret && 1 == adminNum)
	{
		this->OnOK();
		MessageBox("����ǰ����ʹ�õ�KEY��֧��SM2�㷨�����������豸��Կ����ѡ��RSA�㷨������ǩ���˹���Ա��","��⵽��֧��",MB_ICONINFORMATION | MB_OK);
		isTwoPro = 2;
		/*CInitDevInfo initDevInfoDlg(NULL,NULL);
		initDevInfoDlg.DoModal();*/
		return;
		
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret && 1 < adminNum)
	{
		INT_PTR nRes = 0;
		nRes = MessageBox("�ܱ�Ǹ������ǰ����ʹ�õ�KEY֧�ֵ��㷨���豸��Կ���㷨��һ�¡���ѡ���Ƿ�Ҫ���»�KEY�Լ������ɴ˹���Ա��ѡ��ȡ�����������³�ʼ��","��⵽��֧��",MB_ICONEXCLAMATION | MB_OKCANCEL);
		if(nRes == IDOK)
			isTwoPro = 0;
		else if(nRes != IDOK)
			isTwoPro = 1;
		return;
	}

	if(m_paperType_CS == "���֤")
		AdminInfo.iPaperType = 1;
	if(m_paperType_CS == "����")
		AdminInfo.iPaperType = 0;

	AdminInfo.uiNameLen = m_adminName.GetLength();
	memset(AdminInfo.ucName,0x00,sizeof(AdminInfo.ucName));
	memcpy(AdminInfo.ucName,m_adminName.GetBuffer(),AdminInfo.uiNameLen);

	AdminInfo.uiTelephoneLen = m_adminPhonenumber.GetLength();
	memset(AdminInfo.ucTelephone,0x00,sizeof(AdminInfo.ucTelephone));
	memcpy(AdminInfo.ucTelephone,m_adminPhonenumber.GetBuffer(),AdminInfo.uiTelephoneLen);

	AdminInfo.uiPaperNumLen = m_adminPaperNum.GetLength();
	memset(AdminInfo.ucPaperNum,0x00,sizeof(AdminInfo.ucPaperNum));
	memcpy(AdminInfo.ucPaperNum,m_adminPaperNum.GetBuffer(),AdminInfo.uiPaperNumLen);


	unsigned int adminType;
	if(isKMer==0)
		adminType=0;//0��ʾ�豸����Ա
	else if(isKMer==1)
		adminType=1;//1��ʾ��Կ��ȨԱ
	else if(isKMer==2)
		adminType=2;//2��ʾ��ȫ���Ա

	if(SGD_RSA == algId_DevKey)
	{
		pucPubKey =(unsigned char *)&pBlob;
		uiPubKeyLen = sizeof(RSAPUBLICKEYBLOB);
	}
	else if(SGD_SM2_1 == algId_DevKey)
	{
		pucPubKey = (unsigned char *)&epPubKey;
		uiPubKeyLen = sizeof(ECCPUBLICKEYBLOB);
	}

	ret = Km_GenAdmin(phSessionHandle,&AdminInfo,adminType,uiAdminNum,pucPubKey,uiPubKeyLen,pucSignValue,&puiSignValueLen);
	if(0 != ret)
	{
		char outGa[100]={0x00};
		retValueParse(ret,outGa);
		MessageBox("�����ǩ������Աʧ��"+(CString)outGa);
		return;
	}

    LPSTR szFileName_admin = "LBL_CERT_admin";
	//ret = CMyUtil::WriteLabel(szFileName_admin,pucSignValue,puiSignValueLen);
	ret = CMyUtil::WriteLabelEx(szFileName_admin,pucSignValue,puiSignValueLen,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		CString str_ret;
		str_ret.Format("%d",ret);
		MessageBox("д��ǩ��ֵʧ��:=="+str_ret,"��ʾ");
		return;
	}

	unsigned char random[256]={0x00};
	ret = Km_Random(random,16);

	LPSTR szFileName_admin_RANDOM = "LBL_CERT_admin_RANDOM";
	//ret = CMyUtil::WriteLabel(szFileName_admin_RANDOM,random,16);
	ret = CMyUtil::WriteLabelEx(szFileName_admin_RANDOM,random,16,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("д�����Ա�������ǩʧ��","��ʾ");
		return;
	}
	//���ɵ��������ǩ���뻺��
	if(1 < uiAdminNum)
	{
		if(1 == adminNum) memcpy(adm_bkRand_1,random,16);
		if(2 == adminNum) memcpy(adm_bkRand_2,random,16);
		if(3 == adminNum) memcpy(adm_bkRand_3,random,16);
		if(4 == adminNum) memcpy(adm_bkRand_4,random,16);
		if(5 == adminNum) memcpy(adm_bkRand_5,random,16);
	}

	//д�����Ա���к�
	LPSTR szFileName_adminIndex = "LBL_CERT_adminIndex";
	CString adminID;
	adminID.Format("%d",AdminInfo.iAdminId);
	BYTE data_in[256]={0x00};
	memcpy(data_in,adminID.GetBuffer(),adminID.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_adminIndex,data_in,adminID.GetLength());
	ret = CMyUtil::WriteLabelEx(szFileName_adminIndex,data_in,adminID.GetLength(),(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("д�����Ա���к�ʧ��","��ʾ");
		return;
	}

	CString adminLabel;
	if(isKMer==0)
		adminLabel= "�豸����Ա";
	else if(isKMer==1)
		adminLabel= "��Կ��ȨԱ";
	else if(isKMer==2)
		adminLabel= "��ȫ���Ա";
	//д�����Ա��ǩ
	LPSTR szFileName_USERNAME = "LBL_OTHER_LAB_USERNAME";
	
	BYTE data_in_label[256]={0x00};
	memcpy(data_in_label,adminLabel.GetBuffer(),adminLabel.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_USERNAME,data_in_label,12);
	ret = CMyUtil::WriteLabelEx(szFileName_USERNAME,data_in_label,12,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("д�����Ա��ǩʧ��","��ʾ");
		return;
	}
	
	if(0 == ret && 1 == uiAdminNum)
	{
		MessageBox(_T("����Ա���ɳɹ���"),_T(""));
		this->OnOK();
		if(isKMer==1)//ǩ����ȫ���Ա
		{
			if(KeyMnGer_AQ==1)//��config.txt�ж��Ƿ�ǩ����ȫ���Ա
			{
				CSignPWMAdmin signPWMAdminDlg(0,2,uiAdminNum,0,key_length,1,"ǩ����ȫ���Ա",phSHandle,phSHandle);
				signPWMAdminDlg.DoModal();
				return ;
			}
			else//��ǩ����ȫ���Աֱ����ת�ĵ�¼����
				{
					Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
					if(IDOK != ph_PWMMngrDlg.DoModal())
					return;
				}
		}
		else if(isKMer==2)//��ת����¼����
		{
			Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
			if(IDOK != ph_PWMMngrDlg.DoModal())
				return;
		}
		else if(isKMer==0 )//ǩ����ȨԱ
		{
			if(KeyMnGer_SQ==1)//��ȡconfig.txt�ж��Ƿ���Ҫǩ����ȨԱ 
			{
				int state_km_iskm=0;
				CSignPWMAdmin signPWMAdminDlg(0,1,uiAdminNum,0,key_length,1,"ǩ����Կ��ȨԱ",phSHandle,phSHandle);
				signPWMAdminDlg.DoModal();
				signPWMAdminDlg.GetTwoSigState(&state_km_iskm);
				if(state_km_iskm==1)
				{
					CIsInit isInitDlg(NULL,phSHandle);
					isInitDlg.DoModal();
					return;
				}
				return;
			}
			else//����Ҫǩ����ȨԱֱ����ת�����Աǩ������
			{
				if(KeyMnGer_AQ==1)//�ж��Ƿ�ǩ����ȫ���Ա
				{
					CSignPWMAdmin signPWMAdminDlg(0,2,uiAdminNum,0,key_length,1,"ǩ����ȫ���Ա",phSHandle,phSHandle);
					signPWMAdminDlg.DoModal();
					return ;
				}
				else//��ǩ����ȫ���Աֱ����ת�ĵ�¼����
				{
					Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
					if(IDOK != ph_PWMMngrDlg.DoModal())
					return;
				}
			}
			
		}
		
	}
	else if(0 == ret && 1 < uiAdminNum)
	{
		switch(adminNum)
		{
		case 1:
			MessageBox(_T("��1������Ա���ɳɹ���"),_T(""));
			break;
		case 2:
			if(adminNum != num_adm_max)
				MessageBox(_T("��2������Ա���ɳɹ���"),_T(""));
			else
				MessageBox(_T("ȫ������Ա���ɳɹ���"),_T(""));
			break;
		case 3:
			if(adminNum != num_adm_max)
				MessageBox(_T("��3������Ա���ɳɹ���"),_T(""));
			else
				MessageBox(_T("ȫ������Ա���ɳɹ���"),_T(""));
			break;
		case 4:
			if(adminNum != num_adm_max)
				MessageBox(_T("��4������Ա���ɳɹ���"),_T(""));
			else
				MessageBox(_T("ȫ������Ա���ɳɹ���"),_T(""));
			break;
		case 5:
			if(adminNum != num_adm_max)
				MessageBox(_T("��5������Ա���ɳɹ���"),_T(""));
			else
				MessageBox(_T("ȫ������Ա���ɳɹ���"),_T(""));
			break;
		default:
			MessageBox(_T("���ɳɹ���"),_T(""));
			break;
		}
		
		if(adminNum <= num_adm_max && isOneToMore_kmer==1 && isKMer==1)
		{
			this->OnOK();
			int adm_Count_forset = num_adm_max; 
			
			int state_km = 0;
			CString i_Count_dlg_km;
			/*while(1 < num_adm_max && state_km == 0)
			{*/
			//state_km = 0;
			//i_km++;
			adminNum++;
			if(adminNum<=num_adm_max)
			{
				i_Count_dlg_km.Format("%d",adminNum);
				CSignPWMAdmin signPWMAdminDlg(1,1,0,0,key_length,adminNum,"ǩ����"+i_Count_dlg_km+"����Կ��ȨԱ",key_phSHandle,phSHandle);
				signPWMAdminDlg.admin_count = adm_Count_forset;//����ֻ�����Կ��������Ա��
				signPWMAdminDlg.isReadOnly = TRUE;
				if(IDOK != signPWMAdminDlg.DoModal())
					//break;
					return;
				
				signPWMAdminDlg.GetTwoSigState(&state_km);
				//num_adm_max--;
				/*}*/
				if(1 == state_km)
				{
					CIsInit isInitDlg(NULL,phSHandle);
					isInitDlg.DoModal();
					return;
				}

				if(adminNum == num_adm_max)
				{
					CSignPWMAdmin signPWMAdminDlg(0,2,0,0,key_length,0,"ǩ����ȫ���Ա",key_phSHandle,phSHandle);
					if(IDOK != signPWMAdminDlg.DoModal())
						return;
					//Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
					//ph_PWMMngrDlg.uiKeyLen = key_length;
					//ph_PWMMngrDlg.DoModal();
					//return;
				}
			}
		}
		this->OnOK();
	}
	
}

void CSignPWMAdmin::OnCbnSelchangePapertypeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;   
    int nSel;   
  
    // ��ȡ��Ͽ�ؼ����б����ѡ���������  
    nSel = m_paperType.GetCurSel();   
    // ����ѡ����������ȡ�����ַ���  
    m_paperType.GetLBText(nSel, strWeb);   
    // ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����  
    //SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb); 
//	MessageBox(_T("ѡ��������ǣ�") + strWeb);
}

void CSignPWMAdmin::GetMaxAdminNum(int *num)
{
	*num = num_adm_max;
}

void CSignPWMAdmin::GetTwoSigState(int *x)
{
	*x = isTwoPro;
}