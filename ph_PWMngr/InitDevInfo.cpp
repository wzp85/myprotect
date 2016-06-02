// InitDevInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "InitDevInfo.h"
#include "afxdialogex.h"

#include "SignPWMAdmin.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "ph_PWMngrDlg.h"
#include "DevKeyFirResume.h"
#include "IsInit.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ")
// CInitDevInfo �Ի���

IMPLEMENT_DYNAMIC(CInitDevInfo, CDialogEx)

CInitDevInfo::CInitDevInfo(void * key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitDevInfo::IDD, pParent)
	, m_devName(_T(""))
	, m_algID_devInfo(_T(""))
	, m_devPIN(_T(""))
	, m_devPINcon(_T(""))
{
	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
}

CInitDevInfo::~CInitDevInfo()
{
}

void CInitDevInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALG_COMBO, m_algedit);
	DDX_Text(pDX, IDC_DEVNAME_EDIT, m_devName);
	DDX_CBString(pDX, IDC_ALG_COMBO, m_algID_devInfo);
	DDX_Text(pDX, IDC_DEVPIN_EDIT, m_devPIN);
	DDX_Text(pDX, IDC_DEVPINCON_EDIT, m_devPINcon);
}

BOOL CInitDevInfo::OnInitDialog()
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
	m_algedit.AddString(_T("RSA2048"));
    m_algedit.AddString(_T("RSA1024"));
	m_algedit.AddString(_T("SM2"));
  
    SetDlgItemText(IDC_ALG_COMBO, _T("RSA1024"));   
 
    return TRUE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CInitDevInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInitDevInfo::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInitDevInfo::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_ALG_COMBO, &CInitDevInfo::OnCbnSelchangeAlgCombo)
END_MESSAGE_MAP()


// CInitDevInfo ��Ϣ�������
BOOL CInitDevInfo::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN )     
    {
        if(GetFocus()->GetDlgCtrlID()==IDC_BUTTON1)//���»س��������ǰ���������Լ������Ŀؼ���
        {                                           
            CInitDevInfo::OnBnClickedButton1();//����Լ��Ĵ������
        }
		else if(GetFocus()->GetDlgCtrlID()==IDC_BUTTON2)
		{
			CInitDevInfo::OnBnClickedButton2();
		}
         return TRUE;
    } 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CInitDevInfo::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����"����"��ť����ʼ�����豸��Կ
	int ret = 0;
	UpdateData(TRUE);

	unsigned int uiDevNameLength;
	unsigned int iASymmAlgo;
	unsigned int uiKeyLen;
	unsigned int ucDevKeyPinLength;

	uiDevNameLength = m_devName.GetLength();
	unsigned char pucDevName[32] = {0x00};
	memcpy(pucDevName,m_devName.GetBuffer(),uiDevNameLength);

	if(m_algID_devInfo == "RSA2048")
	{
		uiKeyLen = 2048;
		iASymmAlgo = SGD_RSA;
	}
	if(m_algID_devInfo == "RSA1024")
	{
		uiKeyLen = 1024;
		iASymmAlgo = SGD_RSA;
	}
	if(m_algID_devInfo == "SM2")
	{
		uiKeyLen = 256;
		iASymmAlgo = SGD_SM2_1;
	}
	//�˴���һ���豸PIN�������У��
	if(m_devName.IsEmpty())
	{
		MessageBox("�豸���Ʋ���Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_devPIN.GetLength()<8)
	{
		MessageBox("PIN�볤�Ȳ���С��8λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_devPIN != m_devPINcon)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_devPIN))
	{
		MessageBox("PIN�벻��ȫ�����֣�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	
	ucDevKeyPinLength = m_devPIN.GetLength();
	unsigned char pucDevKeyPin[32] = {0x00};
	memcpy(pucDevKeyPin,m_devPIN.GetBuffer(),ucDevKeyPinLength);

	ret = Km_GenDevKey(phSHandle,pucDevName,uiDevNameLength,iASymmAlgo,uiKeyLen,pucDevKeyPin,ucDevKeyPinLength);
	if(!ret)
	{
		this->OnOK();
		INT_PTR nRes = 0;
		//����豸��Կ��ת��ǩ������ԱSignPWAdmin.cpp�н�������ǩ������
		CSignPWMAdmin signPWMAdminDlg(0,0,0,0,uiKeyLen,1,NULL,phSHandle,phSHandle);
		nRes = signPWMAdminDlg.DoModal();
		if(IDOK != nRes)
			return;
		int adm_Count;
		int sigState = 0;
		signPWMAdminDlg.GetMaxAdminNum(&adm_Count);
		signPWMAdminDlg.GetTwoSigState(&sigState);
		if(sigState == 2)
		{
			CInitDevInfo initDevInfoDlg(NULL,phSHandle);
			initDevInfoDlg.DoModal();
			return;
		}
		if(1 < adm_Count)
		{
			int adm_Count_forset = adm_Count; 
			int i = 1;
			int state = 0;
			CString i_Count_dlg;
			while(1 < adm_Count && state == 0)
			{
				state = 0;
				i++;
				i_Count_dlg.Format("%d",i);
				CSignPWMAdmin signPWMAdminDlg(0,0,0,0,uiKeyLen,i,"ǩ����"+i_Count_dlg+"���豸����Ա",key_phSHandle,phSHandle);
				signPWMAdminDlg.admin_count = adm_Count_forset;//����ֻ�����Կ��������Ա��
				signPWMAdminDlg.isReadOnly = TRUE;
				if(IDOK != signPWMAdminDlg.DoModal())
					break;
				
				signPWMAdminDlg.GetTwoSigState(&state);
				adm_Count--;
			}
			if(1 == state)
			{
				CIsInit isInitDlg(NULL,phSHandle);
				isInitDlg.DoModal();
				return;
			}
			//�����config.txt����Ч��������SignPWAmin.cppһ�ξͽ�������ǩ�����̣���ȨԱ���Ա��SignPWAmin.cpp���Ѿ��ж�ǩ������
			//�����˼·��������SignPWAmin.cpp���Ӧ��ȨԱ��ǩ������
			int length=0;
			int KeyMnGer=0;

			CMyUtil::ReadData("./config.txt",NULL,&length);
			BYTE *data = new BYTE[length+1];
			memset(data,0x00,length+1);
			CMyUtil::ReadData("./config.txt",data,&length);

			/*********************��Կ��ȨԱ**********************/
			char *source=(char*)data;
			char *str=strstr(source,"KEY_MANAGER_SQ=");//�ж��Ƿ�ǩ����Կ��ȨԱ����Կ��ȨԱ�̶�һ����
			char *tem=str+strlen("KEY_MANAGER_SQ=");
			char *end=strstr(tem,"\n");
			char num_buf[32]={0x00};
			memcpy(num_buf,tem,end-tem);
			KeyMnGer=atoi(num_buf);
			if(1 != KeyMnGer)//�ж��Ƿ�ǩ����Կ��ȨԱ
			{
				return ;
			}

			CSignPWMAdmin signPWMAdminDlg(0,KeyMnGer,1,0,uiKeyLen,1,"ǩ����Կ��ȨԱ",phSHandle,phSHandle);
			nRes = signPWMAdminDlg.DoModal();
			if(IDOK != nRes)
				return;
			//int adm_Count_km=0;
			//int sigState_km=0;
			//signPWMAdminDlg.GetMaxAdminNum(&adm_Count_km);
			//signPWMAdminDlg.GetTwoSigState(&sigState_km);
			//if(sigState_km == 2)
			//{
			//	CInitDevInfo initDevInfoDlg(NULL,phSHandle);
			//	initDevInfoDlg.DoModal();
			//	return;
			//}
			//if(1 < adm_Count_km)
			//{
			//	int adm_Count_forset = adm_Count_km; 
			//	int i_km = 1;
			//	int state_km = 0;
			//	CString i_Count_dlg_km;
			//	while(1 < adm_Count_km && state_km == 0)
			//	{
			//		state_km = 0;
			//		i_km++;
			//		i_Count_dlg_km.Format("%d",i_km);
			//		CSignPWMAdmin signPWMAdminDlg(0,1,0,0,uiKeyLen,i_km,"ǩ����"+i_Count_dlg_km+"����Կ����Ա",key_phSHandle,phSHandle);
			//		signPWMAdminDlg.admin_count = adm_Count_forset;//����ֻ�����Կ��������Ա��
			//		signPWMAdminDlg.isReadOnly = TRUE;
			//		if(IDOK != signPWMAdminDlg.DoModal())
			//			break;
			//	
			//		signPWMAdminDlg.GetTwoSigState(&state_km);
			//		adm_Count_km--;
			//	}
			//	if(1 == state_km)
			//	{
			//		CIsInit isInitDlg(NULL,phSHandle);
			//		isInitDlg.DoModal();
			//		return;
			//	}

				/*CSignPWMAdmin signPWMAdminDlg(0,2,0,0,uiKeyLen,0,"ǩ����ȫ���Ա",key_phSHandle,phSHandle);
				if(IDOK != signPWMAdminDlg.DoModal())
					return;*/

				//Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
				//ph_PWMMngrDlg.uiKeyLen = uiKeyLen;
				//ph_PWMMngrDlg.DoModal();
			/*}*/
		}
	}
	else
	{
		char outGdevk[100]={0x00};
		retValueParse(ret,outGdevk);
		MessageBox("�����豸��Կʧ��"+(CString)outGdevk,"��ʾ",MB_ICONEXCLAMATION);
		this->OnOK();
		return;
	}
	
}


void CInitDevInfo::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char cur_temp[500]={0x00};
	GetCurrentDirectory(500,cur_temp);
	CString CurrentPath;
	CurrentPath.Format("%s",cur_temp);

	this->OnOK();

	int state = 0;
	

	CDevKeyFirResume devKeyFirResumeDlg1(1,phSHandle);
	if(IDOK!=devKeyFirResumeDlg1.DoModal())
		return;
	devKeyFirResumeDlg1.GetRecoverState(&state);
	if(2 != state)
		return;

	//�ָ�����Ա
	CDevKeyFirResume devKeyFirResumeDlg2(2,phSHandle);
	if(IDOK!=devKeyFirResumeDlg2.DoModal())
		return;
	devKeyFirResumeDlg2.GetRecoverState(&state);
	if(2 != state)
		return;


	SetCurrentDirectory(CurrentPath);

	int numclosed = _fcloseall( );
   
	Cph_PWMngrDlg phDlg(NULL,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
	phDlg.DoModal();
}


void CInitDevInfo::OnCbnSelchangeAlgCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;   
	int nSel;         
	nSel = m_algedit.GetCurSel();       
    m_algedit.GetLBText(nSel, strWeb);   
	if(strWeb  == "SM2")
		MessageBox("��ѡ�����SM2�㷨�����㷨������һ������ǩ������Աʹ�ã���ȷ������KEY����֧��SM2�㷨��","��ʾ",MB_ICONEXCLAMATION);
}
