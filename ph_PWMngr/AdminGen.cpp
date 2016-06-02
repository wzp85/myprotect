// AdminGen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AdminGen.h"
#include "afxdialogex.h"

#include "InitKeyTip.h"
#include "ph_km.h"
#include "KeyDAO.h"
#include "MyUtil.h"
#define FILESIZE_SIGDEVADMIN 1024
#define ADM_UPDATA 777
int i_adm_log_num = 0;
unsigned int algID = 0;
unsigned int keyLength = 0;
// CAdminGen �Ի���

IMPLEMENT_DYNAMIC(CAdminGen, CDialogEx)

CAdminGen::CAdminGen(int num,void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminGen::IDD, pParent)
	, m_adminname(_T(""))
	, m_phoneNumber(_T(""))
	, m_paperNumber(_T(""))
	, m_adminpin(_T(""))
	, m_adminpincon(_T(""))
	, m_adminMaxCount(_T(""))
	, m_paperType_cs(_T("")/*)
	, m_adminType_cs(_T("")*/)
{
	phHandle = handle;
	admCountInGen = num;
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "����"));                 // lpszFacename
}

CAdminGen::CAdminGen(CString adm_name,CString adm_index,CString adm_maxNum,CString adm_phoneNum,CString adm_paperType,CString adm_paperNum,void *handle,CWnd* pParent/* = NULL*/)
		: CDialogEx(CAdminGen::IDD, pParent)
	, m_adminname(_T(""))
	, m_phoneNumber(_T(""))
	, m_paperNumber(_T(""))
	, m_adminpin(_T(""))
	, m_adminpincon(_T(""))
	, m_adminMaxCount(_T(""))
	, m_paperType_cs(_T("")/*)
	, m_adminType_cs(_T("")*/)
{
	phHandle = handle;
	adm_name_cs = adm_name;
	adm_index_in = atoi(adm_index);
	adm_maxNum_cs = adm_maxNum;
	adm_phoneNum_cs = adm_phoneNum;
	adm_paperType_cs = adm_paperType;
	adm_paperNum_cs = adm_paperNum;

	//memset(admin_keyIndex,0x00,);
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "����"));                 // lpszFacename
}

CAdminGen::~CAdminGen()
{
}

void CAdminGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THETITLE_STATIC, m_titleline);
	DDX_Text(pDX, IDC_ADMINNAME_EDIT, m_adminname);//-------����Ա��
	DDX_Text(pDX, IDC_ADMINPHONE_EDIT, m_phoneNumber);
	DDX_Control(pDX, IDC_PAPERTYPE_COMBO, m_papertype);
	DDX_Text(pDX, IDC_PHONENUMBER_EDIT, m_paperNumber);
	DDX_Text(pDX, IDC_ADMINPIN_EDIT, m_adminpin);
	DDX_Text(pDX, IDC_ADMINPINCON_EDIT, m_adminpincon);
	DDX_Text(pDX, IDC_ADMINMAXCOUNT_EDIT, m_adminMaxCount);
	//	DDX_Control(pDX, IDC_ADMINTYPE_COMBO, m_adminType);
	DDX_CBString(pDX, IDC_PAPERTYPE_COMBO, m_paperType_cs);
	//	DDX_CBString(pDX, IDC_ADMINTYPE_COMBO, m_adminType_cs);
	DDX_Control(pDX, IDC_ADMINMAXCOUNT_EDIT, m_adm_max_count);
	DDX_Control(pDX, IDC_ADMINTYPE_COMBO, m_adminType);
	DDX_CBString(pDX,IDC_ADMINTYPE_COMBO, m_adminType_cs);
}

BOOL CAdminGen::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
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
	//����CComBox������Ϊֻ����ֹ�û��Լ�������ɲ���Ҫ�Ĵ���
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_ADMINTYPE_COMBO))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit1 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_PAPERTYPE_COMBO))->GetWindow(GW_CHILD));	
	pEdit1->SetReadOnly(TRUE);


	CWnd *cWnd = GetDlgItem(IDC_THETITLE_STATIC);
	cWnd->SetFont(&font);
	if(adm_index_array[0][0] == ADM_UPDATA)
	{
		cWnd->SetWindowText("���¹���Ա");
		SetDlgItemText(IDC_ADMINNAME_EDIT, m_adminname); 
		SetDlgItemText(IDC_ADMINPHONE_EDIT,adm_phoneNum_cs); 
		SetDlgItemText(IDC_PHONENUMBER_EDIT,adm_paperNum_cs); 
		SetDlgItemText(IDC_PAPERTYPE_COMBO,adm_paperType_cs); 
		SetDlgItemText(IDC_ADMINMAXCOUNT_EDIT,adm_maxNum_cs); 
		SetDlgItemText(IDC_ADMINTYPE_COMBO, _T("�豸����Ա"));
		m_adm_max_count.SetReadOnly(TRUE);
	}
	else
	{
		cWnd->SetWindowText("��ӹ���Ա");
		SetDlgItemText(IDC_PAPERTYPE_COMBO, _T("���֤"));
		SetDlgItemText(IDC_ADMINTYPE_COMBO, _T("�豸����Ա"));
		
	}
		
	 m_papertype.AddString(_T("���֤"));     
	 m_papertype.AddString(_T("����")); 

	m_adminType.AddString(_T("�豸����Ա"));
	m_adminType.AddString(_T("��Կ��ȨԱ"));
	m_adminType.AddString(_T("��ȫ���Ա"));

	//��ȡ������Ա��
	int ret = 0;
	DEVKEYINFO devInfo={0x00};
	char outString[100]={0x00};
	ret = Km_GetDevKeyInfo(phHandle,&devInfo);
	if(0 != ret)
	{
		retValueParse(ret,outString);
		MessageBox("��ȡ�豸��Կ��Ϣʧ�ܣ������룺"+(CString)outString,"��ʾ",MB_ICONEXCLAMATION);
		return TRUE;
	}
	algID = devInfo.uiAlgo;
	keyLength = devInfo.uiKeyLen;
	if(keyLength == 2048)
		keyLength = 1024;
	isAddOK = TRUE;
//	int admMax_forLogin = devInfo.uiBakTotalKey;
	i_adm_log_num = admCountInGen;
//	int i_adm_log_num = 0.5*admMax_forLogin+1;
	if(1 <= admCountInGen)
	{
		CString admz_num;
		admz_num.Format("%d",admCountInGen);
		SetDlgItemText(IDC_ADMINMAXCOUNT_EDIT,admz_num);
		m_adm_max_count.SetReadOnly(TRUE);
	}
//	if(i_adm_log_num >= admMax_forLogin)
		//isAddOK = FALSE;
    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CAdminGen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminGen::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAdminGen::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAdminGen::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAdminGen ��Ϣ�������


void CAdminGen::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("������"));
}


void CAdminGen::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	//����У�鲿��
	if(m_adminname.IsEmpty())
	{
		MessageBox("��������Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminname.GetLength() >= 20)
	{
		MessageBox("����̫���ˣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if( m_phoneNumber.IsEmpty())
	{
		MessageBox("�绰���벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_phoneNumber.GetLength() >= 20)
	{
		MessageBox("�绰���볤�Ȳ��ܳ���20λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperNumber.IsEmpty())
	{
		MessageBox("֤�����벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperNumber.GetLength() >= 24)
	{
		MessageBox("֤������̫���ˣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperType_cs == "���֤"
		&& m_paperNumber.GetLength()!=18 
		&& m_paperNumber.GetLength() != 15)
	{
		MessageBox("���֤���볤��Ϊ15��18λ��������Ϸ������֤���룡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin.IsEmpty())
	{
		MessageBox("���������ԱPIN�룡","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin.GetLength()<6)
	{
		MessageBox("����ԱPIN�벻��С��6λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin != m_adminpincon)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminMaxCount.IsEmpty())
	{
		MessageBox("������������Ա����","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}

	
	//---------��ʽ����ʾ----------//
	INT_PTR nRes = 0;  
	int ret = 0;
	
	void * phSessionHandle = phHandle;//������Ự������� 
	ADMININFO AdminInfo = {0};
	if(adm_index_array[0][0] == ADM_UPDATA)
	{
		char outStrDelAdm[100]={0x00};
		ret = Km_DelAdmin(phSessionHandle,adm_index_in);
		if(0 != ret)
		{
			retValueParse(ret,outStrDelAdm);
			CString kkkk;
			kkkk.Format("%d",adm_index_in);
			MessageBox("���ٵ�"+kkkk+ "�Ź���Աʧ�ܣ������룺"+(CString)outStrDelAdm,"��ʾ");
			return;
		}
	}
	int id_adm = 0;
	int num_adm = 0;
	ret = CMyUtil::GetAdminID(phSessionHandle,&id_adm,&num_adm);
	//CString iiiiiiiii;
	//iiiiiiiii.Format("%d",id_adm+1);
	//MessageBox("��---------4++++++++++++++"+iiiiiiiii,"");
	if(!ret)
		AdminInfo.iAdminId = id_adm + 1;
	else
	{
		char outGetAdmList[100]={0x00};
		retValueParse(ret,outGetAdmList);
		MessageBox("��ȡ����Ա���к�ʧ��,�����룺"+(CString)outGetAdmList,"��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	//if(!isAddOK)
	if(1 != i_adm_log_num && num_adm == i_adm_log_num)
	{
		MessageBox("����ϵͳ����Ա�������ܳ���������Ա������","��ʾ",MB_ICONEXCLAMATION);
		this->OnOK();
		return;
	}
	//����ǩ�жϹ���Ա����
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(ret)
	{
		nRes = MessageBox("�ò��������ʽ��KEY���Ƿ������","��ʾ",MB_ICONEXCLAMATION|MB_OK);
		if(nRes == IDCANCEL)
			return;
	}
	if(!strcmp(label,"�豸����Ա"))
	{
		/*nRes = */MessageBox("�豸����Աkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(!strcmp(label,"��Կ��ȨԱ"))
	{
		/*nRes = */MessageBox("��Կ��ȨԱkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(!strcmp(label,"��ȫ���Ա"))
	{
		/*nRes = */MessageBox("��ȫ���Աkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(/*strcmp(label,"�豸����Ա") && */!strcmp(label,"��Կ������Կ"))
	{
		MessageBox("��Կ������Կkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION);
		return;
	}

	unsigned int uiAdminNum = atoi(m_adminMaxCount);
	unsigned char *pucPubKey = NULL;
	unsigned int uiPubKeyLen = 0;
	unsigned char pucSignValue[1024]={0x00};
	unsigned int puiSignValueLen = sizeof(pucSignValue);

	//��ʽ������ȡ��Կ
	HAPPLICATION application;	
	RSAPUBLICKEYBLOB pBlob={0x00};
	ECCPUBLICKEYBLOB epPubKey={0x00};
	
	if(algID == SGD_RSA)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminpin,&application,&pBlob,NULL,keyLength);
	}
	else if(algID == SGD_SM2_1)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminpin,&application,NULL,&epPubKey,keyLength);
	}
	
	if(0 != ret && ret != SAR_NOTSUPPORTKEYTYPE)
	{
		MessageBox("���ɹ�Կʧ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret)
	{
		MessageBox("����ǰ����ʹ�õ�KEY��֧��SM2�㷨�������KEY���Ի��˳�ϵͳ���³�ʼ����","��⵽��֧��",MB_ICONWARNING | MB_OK);
		return;
	}
	//else
	//{
	//	MessageBox("��Կ���ɳɹ�");
	//}

	if(m_paperType_cs == "���֤")
		AdminInfo.iPaperType = 1;
	if(m_paperType_cs == "����")
		AdminInfo.iPaperType = 0;

	AdminInfo.uiNameLen =m_adminname.GetLength();
	memset(AdminInfo.ucName,0x00,sizeof(AdminInfo.ucName));
	memcpy(AdminInfo.ucName,m_adminname.GetBuffer(),AdminInfo.uiNameLen);

	AdminInfo.uiTelephoneLen = m_phoneNumber.GetLength();
	memset(AdminInfo.ucTelephone,0x00,sizeof(AdminInfo.ucTelephone));
	memcpy(AdminInfo.ucTelephone,m_phoneNumber.GetBuffer(),AdminInfo.uiTelephoneLen);

	AdminInfo.uiPaperNumLen = m_paperNumber.GetLength();
	memset(AdminInfo.ucPaperNum,0x00,sizeof(AdminInfo.ucPaperNum));
	memcpy(AdminInfo.ucPaperNum,m_paperNumber.GetBuffer(),AdminInfo.uiPaperNumLen);

	unsigned int adminType = 0;//---------------------�жϹ���Ա����

	if(m_adminType_cs == "�豸����Ա")
	{
		adminType = 0;
	}
	if(m_adminType_cs == "��Կ��ȨԱ")
	{
		adminType = 1;
	}
	if(m_adminType_cs == "��ȫ���Ա")
	{
		adminType = 2;
	}


	if(algID == SGD_RSA)
	{
		/*pucPubKey =(unsigned char *)&pBlob;*/
		uiPubKeyLen = sizeof(RSAPUBLICKEYBLOB);
		pucPubKey = new unsigned char[uiPubKeyLen+1];
		memset(pucPubKey,0x00,uiPubKeyLen+1);
		memcpy(pucPubKey,(unsigned char *)&pBlob,uiPubKeyLen);
	}
	else if(algID == SGD_SM2_1)
	{
		//pucPubKey =(unsigned char *)&epPubKey;
		uiPubKeyLen = sizeof(ECCPUBLICKEYBLOB);
		pucPubKey = new unsigned char[uiPubKeyLen+1];
		memset(pucPubKey,0x00,uiPubKeyLen+1);
		memcpy(pucPubKey,(unsigned char *)&epPubKey,uiPubKeyLen);
	}

	ret = Km_GenAdmin(phSessionHandle,&AdminInfo,adminType,uiAdminNum,pucPubKey,uiPubKeyLen,pucSignValue,&puiSignValueLen);
	if(ret)
	{
		char outGenAdm[100]={0x00};
		retValueParse(ret,outGenAdm);
		MessageBox("���������󡣴����룺"+(CString)outGenAdm,"");
		return;
	}
	//д��ǩ
	LPSTR szFileName_admin = "LBL_CERT_admin";
	//ret = CMyUtil::WriteLabel(szFileName_admin,pucSignValue,puiSignValueLen);
	ret = CMyUtil::WriteLabelEx(szFileName_admin,pucSignValue,puiSignValueLen,(char *)m_adminpin.GetString());
	if(ret)
	{
		MessageBox("д��ǩ��ֵʧ��","��ʾ");
		return;
	}

	//д�����Ա���к�
	LPSTR szFileName_adminIndex = "LBL_CERT_adminIndex";
	CString adminID;
	adminID.Format("%d",AdminInfo.iAdminId);
	BYTE data_in[256]={0x00};
	memcpy(data_in,adminID.GetBuffer(),adminID.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_adminIndex,data_in,adminID.GetLength());
	ret = CMyUtil::WriteLabelEx(szFileName_adminIndex,data_in,adminID.GetLength(),(char *)m_adminpin.GetString());
	if(ret)
	{
		MessageBox("д�����Ա���к�ʧ��","��ʾ");
		return;
	}

	//д�����Ա��ǩ
	LPSTR szFileName_USERNAME = "LBL_OTHER_LAB_USERNAME";
	CString adminLabel = m_adminType_cs;/*"�豸����Ա";*/
	BYTE data_in_label[256]={0x00};
	memcpy(data_in_label,adminLabel.GetBuffer(),adminLabel.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_USERNAME,data_in_label,12);
	ret = CMyUtil::WriteLabelEx(szFileName_USERNAME,data_in_label,12,(char *)m_adminpin.GetString());
	if(0 != ret)
	{
		MessageBox("д�����Ա��ǩʧ��","��ʾ");
		return;
	}
	else if(0 == ret && adm_index_array[0][0] != ADM_UPDATA)
	{
		MessageBox(_T("��ӳɹ���"),_T(""));
	}
	CDialogEx::OnOK();
}


void CAdminGen::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
