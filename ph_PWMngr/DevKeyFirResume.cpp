// DevKeyFirResume.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevKeyFirResume.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDevide.h"
// CDevKeyFirResume �Ի���

IMPLEMENT_DYNAMIC(CDevKeyFirResume, CDialogEx)

CDevKeyFirResume::CDevKeyFirResume(int isAdm,void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevKeyFirResume::IDD, pParent)
	, m_firstResume(_T(""))
	, m_usrpin(_T(""))
	, m_usrpincon(_T(""))
	, m_line2(_T(""))
	, m_browsefile(_T(""))
{
	phHandle_devRsu = handle;
	isAdmDev = isAdm;

	VERIFY(fontFirstResume.CreateFont(
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

	VERIFY(fontLine2.CreateFont(
    14,                        // nHeight
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

CDevKeyFirResume::~CDevKeyFirResume()
{
}

void CDevKeyFirResume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSE_BUTTON, m_browseFile);
	DDX_Text(pDX, IDC_FIRSTRESUME_STATIC, m_firstResume);
	DDX_Text(pDX, IDC_USRPIN_EDIT, m_usrpin);
	DDX_Text(pDX, IDC_USRPINCON_EDIT, m_usrpincon);
	DDX_Text(pDX, IDC_LINE2_STATIC, m_line2);
	CWnd *cWnd = GetDlgItem(IDC_FIRSTRESUME_STATIC);
	cWnd->SetFont(&fontFirstResume);
	if(1 == isAdmDev)
		cWnd->SetWindowText("��ȡ�豸��Կ�����ļ�");
	else if(2 == isAdmDev)
		cWnd->SetWindowText("��ȡ�豸����Ա�����ļ�");
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetFont(&fontLine2);
	if(1 == isAdmDev)
		cWnd->SetWindowText("��ѡ��Ҫ�ָ����豸��Կ�����ļ����������µ�˽Կʹ����Ȩ�룡");
	else if(2 == isAdmDev)
		cWnd->SetWindowText("           ��ѡ��Ҫ�ָ����豸����Ա�����ļ���");

	if(1 == isAdmDev)
	{
		cWnd = GetDlgItem(IDC_EDONE_STATIC);
		cWnd->SetWindowText("˽Կʹ����Ȩ��");
		cWnd = GetDlgItem(IDC_EDTWO_STATIC);
		cWnd->SetWindowText("˽Կʹ����Ȩ�루ȷ�ϣ���");
	}
	else if(2 == isAdmDev)
	{
		cWnd = GetDlgItem(IDC_EDONE_STATIC);
		cWnd->SetWindowText("");
		cWnd = GetDlgItem(IDC_EDTWO_STATIC);
		cWnd->SetWindowText("");
		cWnd = GetDlgItem(IDC_USRPIN_EDIT);
		cWnd->ShowWindow(FALSE);
		cWnd = GetDlgItem(IDC_USRPINCON_EDIT);
		cWnd->ShowWindow(FALSE);
	//	m_usrpinS.ShowWindow(FALSE);
	//	m_usrpinF.ShowWindow(FALSE);
	}
	DDX_Text(pDX, IDC_BROWSE_EDIT, m_browsefile);
	DDX_Control(pDX, IDC_USRPIN_EDIT, m_usrpinF);
	DDX_Control(pDX, IDC_USRPINCON_EDIT, m_usrpinS);
}


BEGIN_MESSAGE_MAP(CDevKeyFirResume, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDevKeyFirResume::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, &CDevKeyFirResume::OnBnClickedBrowseButton)
END_MESSAGE_MAP()


// CDevKeyFirResume ��Ϣ�������


void CDevKeyFirResume::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);

	if(m_browsefile.IsEmpty())
	{
		MessageBox("��ѡ��Ҫ�ָ��ı����ļ���","ȷ��ѡ���ļ�",MB_ICONEXCLAMATION);
		return;
	}

	//�ָ�����Ա
	if(2 == isAdmDev)
	{
		int ret = 0;
		void *hSessionHandle = phHandle_devRsu;
		unsigned char *pucAdminBackup=NULL;
		unsigned int uiAdminBackupLength=0;

		int length_adm = 0;
		char *filename_adm = (LPSTR)(LPCTSTR)m_browsefile;
		CMyUtil::ReadData(filename_adm,pucAdminBackup,&length_adm);
		pucAdminBackup = new unsigned char[length_adm];
		CMyUtil::ReadData(filename_adm,pucAdminBackup,&length_adm);
		uiAdminBackupLength = length_adm;
		char ch_last=pucAdminBackup[length_adm-1];
		int ch_last_in = atoi(&ch_last);
		if(0x34 != ch_last)
		{
			MessageBox("��ѡ��Ĳ��ǹ���Ա��Կ�����ļ�����ѡ�����Ա��Կ�ı����ļ����лָ���","�����ļ����ʹ���",MB_ICONEXCLAMATION);
			delete pucAdminBackup;
			return;
		}
		ret = Km_AdminRecovery(hSessionHandle,pucAdminBackup,uiAdminBackupLength);
		if(0 != ret)
		{
			char outAr[100]={0x00};
			retValueParse(ret,outAr);
			MessageBox("����Ա�ָ�ʧ��","�ָ�ʧ��"+(CString)outAr,MB_ICONWARNING | MB_OK);
			isRecoveryOK = 0;
			delete  []pucAdminBackup;
			return;
		}
		else if(0 == ret)
		{
			MessageBox("����Ա�ָ��ɹ�","�ָ��ɹ�",MB_ICONINFORMATION|MB_OK);
			isRecoveryOK = 2;
		}
		delete  pucAdminBackup;
		this->OnOK();
		return;
	}

	void *hSessionHandle = phHandle_devRsu;
	unsigned int uiAlgo = SGD_SM1_ECB;

	unsigned char pucAdminPin[32]={0};
	

	unsigned char pucKeyBackupKey[256]={0};
	unsigned int uiKeyBackupKeyLength=16;
	unsigned char *pucKeyBak=NULL;
	unsigned int uiKeyBakLength;

	int data_len = 0;
	char *filename = (LPSTR)(LPCTSTR)m_browsefile;
	CMyUtil::ReadData(filename,pucKeyBak,&data_len);
	pucKeyBak = new unsigned char[data_len];
	CMyUtil::ReadData(filename,pucKeyBak,&data_len);
	uiKeyBakLength = data_len;
	//�жϱ����ļ������Ƿ���ȷ
	char ch_last=pucKeyBak[data_len-1];
	int ch_last_in = atoi(&ch_last);
	//��ȡ����������������жϱ���key�뱸���ļ��Ƿ�ƥ��
	char rd_last[32]={0x00};
	memcpy(rd_last,&pucKeyBak[data_len-27],24);
	char rd_deco[32]={0x00};

	int len_deco = Km_Decode(rd_last,24,rd_deco);

	if(0x31 != ch_last)
	{
		MessageBox("��ѡ��Ĳ����豸��Կ�����ļ�����ѡ���豸��Կ�ı����ļ����лָ���","�����ļ����ʹ���",MB_ICONEXCLAMATION);
		delete pucKeyBak;
		return;
	}

	if(m_usrpin.GetLength()<8)
	{
		MessageBox("PIN�볤�Ȳ���С��8λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrpin != m_usrpincon)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_usrpin))
	{
		MessageBox("PIN�벻��ȫ�����֣�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	CDevKeyFirBac devKeyFirBacDlg1(1,_T("������һ����Կ������Կ"));
	if(IDOK != devKeyFirBacDlg1.DoModal())
		return;

	unsigned char ch_cmp[32]={0x00};
	devKeyFirBacDlg1.GetRandomInKey(ch_cmp);
	if(strncmp(rd_deco,(const char*)ch_cmp,len_deco))
	{
		MessageBox("��ѡ��ı����ļ��뱸����Կkey��ƥ�䣡","��⵽��ƥ��",MB_ICONEXCLAMATION);
		devKeyFirBacDlg1.ResetKIR();
		return;
	}
	unsigned int B64KeyLen1=0;
	unsigned char B64Key1[256]={0x00};

	Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_Rsu_dev,0,257);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_Rsu_dev);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("�����ڶ�����Կ������Կ"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_Rsu_dev,0,257);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_Rsu_dev);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("������������Կ������Կ"));
	if(IDOK == devKeyFirBacDlg3.DoModal())
	{
		//�˴��õ��ûָ��ӿ�phHandle_devRsu
		int ret = 0;

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_Rsu_dev,0,257);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_Rsu_dev);

		unsigned char sysKey_for_in[256]={0};
		unsigned int sysKey_for_in_len = 0;
		ret = KeyMerge(sys_Key_1_Rsu_dev,len_1,sys_Key_2_Rsu_dev,len_2,sys_Key_3_Rsu_dev,len_3,sysKey_for_in,&sysKey_for_in_len);
		if(0 != ret || 16 != sysKey_for_in_len)
		{
			MessageBox("��Կ�ϲ�����","��ʾ");
			return;
		}
		/*{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};*/
		memcpy(pucKeyBackupKey,sysKey_for_in,16);
		
		int length = m_usrpin.GetLength();
		memcpy(pucAdminPin,m_usrpin.GetBuffer(),length);
		unsigned int uiAdminPinLength = length;

		ret = Km_DevKeyRecovery(hSessionHandle,uiAlgo,pucAdminPin,uiAdminPinLength,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,uiKeyBakLength);
		if(0 == ret)
		{
			MessageBox("�ָ��豸��Կ�ɹ�","��ʾ",MB_ICONINFORMATION|MB_OK);
			isRecoveryOK = 2;
		}
		else if(0 != ret)
		{
			char outDkr[100]={0x00};
			retValueParse(ret,outDkr);
			MessageBox("�ָ��豸��Կʧ��"+(CString)outDkr,"��ʾ",MB_ICONWARNING|MB_OK);
			isRecoveryOK = 1;
		}
		delete pucKeyBak;
	}
	this->OnOK();
}

void CDevKeyFirResume::GetRecoverState(int *rc_state)
{
	*rc_state = isRecoveryOK;
}

void CDevKeyFirResume::OnBnClickedBrowseButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("�ı��ļ�(*.backup)|*.backup|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("backup"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���  
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_BROWSE_EDIT, strFilePath);   
    }   
}   


BOOL CDevKeyFirResume::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ��λ���  
	CWnd *cWnd = GetDlgItem(IDC_BROWSE_EDIT);
	cWnd->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
