// AppCertOnline.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertOnline.h"
#include "afxdialogex.h"
#include "AppCertMngr.h"

// CAppCertOnline �Ի���


unsigned int StandardType;
CString strCertStandard;
CString CertPort;
CString StanType;
CString CertUrl;
CString CertIP;

IMPLEMENT_DYNAMIC(CAppCertOnline, CDialogEx)

CAppCertOnline::CAppCertOnline(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppCertOnline::IDD, pParent)
	, m_CS_certUrl(_T(""))
	, m_certIP_CS(_T(""))
	, m_certPort_CS(_T(""))
{

}

CAppCertOnline::~CAppCertOnline()
{
}

void CAppCertOnline::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CERTSTAND, m_certStandrd);
	DDX_Control(pDX, IDC_EDIT_CERT_URL, m_certUrl);

	DDX_Text(pDX, IDC_EDIT_CERT_URL, m_CS_certUrl);
	DDX_Text(pDX, IDC_EDIT_CertIP, m_certIP_CS);
	DDX_Text(pDX, IDC_EDIT_CertPort, m_certPort_CS);
	DDX_Control(pDX, IDC_EDIT_CertIP, m_certip);
	DDX_Control(pDX, IDC_EDIT_CertPort, m_certPort);
}


BEGIN_MESSAGE_MAP(CAppCertOnline, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAppCertOnline::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_CERTSTAND, &CAppCertOnline::OnCbnSelchangeComboCertstand)
END_MESSAGE_MAP()


// CAppCertOnline ��Ϣ�������


void CAppCertOnline::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(0 == StandardType)//��ȡ
	{
		if(m_CS_certUrl.IsEmpty())
		{
			MessageBox(_T("URL���Ϊ�գ�"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		CertUrl = m_CS_certUrl;
		StanType = strCertStandard;
	}
	else{//��ȡ�������ӿ�ip��ַ���˿ں�
		if(m_certIP_CS.IsEmpty())
		{
			MessageBox(_T("ip��ַ����Ϊ�գ�"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		if(m_certPort_CS.IsEmpty())
		{
			MessageBox(_T("�˿ںŲ���Ϊ�գ�"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		CertIP = m_certIP_CS;//ip��ַ
		CertPort =m_certPort_CS;//�˿ں�
		StanType = strCertStandard;//������׼
	}

	CDialogEx::OnOK();
}


void CAppCertOnline::OnCbnSelchangeComboCertstand()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int nSel; 
    nSel =m_certStandrd.GetCurSel(); //��ȡ��Ͽ�ؼ��б����ѡ��������
	m_certStandrd.GetLBText(nSel,strCertStandard);//����������ȡ��Ӧ�ַ���
	if(strCertStandard == "����RA��׼")
	{
		StandardType = 1;
		m_certip.EnableWindow(TRUE);
		m_certPort.EnableWindow(TRUE);

		SetDlgItemText(IDC_EDIT_CertIP ,(LPCTSTR)"172.2.63.187");  
		SetDlgItemText(IDC_EDIT_CertPort ,(LPCTSTR)"40625");  



		m_certUrl.EnableWindow(FALSE);
	}
	else{
		StandardType = 0;
		m_certip.EnableWindow(FALSE);
		m_certPort.EnableWindow(FALSE);
		m_certUrl.EnableWindow(TRUE);
	}
	
}



BOOL CAppCertOnline::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_CERTSTAND))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_certStandrd.AddString(_T("�ջ�RA��׼"));//�ؼ��б��һ��
	m_certStandrd.InsertString(1,_T("����RA��׼"));
	m_certStandrd.InsertString(2,_T("˰��RA��׼"));
	SetDlgItemText(IDC_COMBO_CERTSTAND, _T("�ջ�RA��׼"));
	StandardType = 0;//��������1��������0
	m_certip.EnableWindow(FALSE);

	m_certPort.EnableWindow(FALSE);
	m_certUrl.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


int CAppCertOnline:: GetURLandType(unsigned char*Stand_Type,unsigned int*StandTpeLength,unsigned char*Cert_Url,
	unsigned int*CertUrlLength,unsigned char*Cert_Ip,unsigned int*CertIpLength,unsigned char *Cert_Port,unsigned int*CertPortLength,unsigned int*type)
{
	if(0 == StandardType)//��������1��������0
	{
		if(CertUrl.IsEmpty())
		{
			MessageBox("URL���Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
			return -1;
		}
		*CertUrlLength = CertUrl.GetLength();
		if(Cert_Url != NULL)
		{
			memcpy(Cert_Url,CertUrl.GetBuffer(),CertUrl.GetLength());
		}

		if(StanType.IsEmpty())
		{
			MessageBox("֤���׼����Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
			return -1;
		}
		*StandTpeLength = StanType.GetLength();
		if(Stand_Type != NULL)
		{
			memcpy(Stand_Type,StanType.GetBuffer(),StanType.GetLength());
		}
	}
	else
	{
		if(CertIP.IsEmpty())
		{
			MessageBox("ip��ַ����Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
			return -1;
		}
		*CertIpLength = CertIP.GetLength();
		if(Cert_Ip != NULL)
		{
			memcpy(Cert_Ip,CertIP.GetBuffer(),CertIP.GetLength());
		}
		if(StanType.IsEmpty())
		{
			MessageBox("֤���׼����Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
			return -1;
		}
		*StandTpeLength = StanType.GetLength();
		if(Stand_Type != NULL)
		{
			memcpy(Stand_Type,StanType.GetBuffer(),StanType.GetLength());
		}
		*CertPortLength = CertPort.GetLength();
		if(Cert_Port != NULL)
		{
			memcpy(Cert_Port,CertPort.GetBuffer(),CertPort.GetLength());
		}
		//*Cert_Port = CertPort;//�˿ں�
	}
	*type = StandardType;
	return 0;
}