// ChangeInitPin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ChangeInitPin.h"
#include "afxdialogex.h"

#include "ph_PWMngrDlg.h"
#include "ph_km.h"
#include "SystemSmartKey.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ")
// CChangeInitPin �Ի���

IMPLEMENT_DYNAMIC(CChangeInitPin, CDialogEx)

CChangeInitPin::CChangeInitPin(int isRs,char *ip,CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeInitPin::IDD, pParent)
	, m_username(_T(""))
	, m_usrOldPin(_T(""))
	, m_usrNewPin(_T(""))
{
	isRs_ChangePin = isRs;

	memset(ip_in,0x00,32);
	memcpy(ip_in,ip,32);
}

CChangeInitPin::~CChangeInitPin()
{
}

void CChangeInitPin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_usrOldPin);
	DDX_Text(pDX, IDC_EDIT3, m_usrNewPin);
}


BEGIN_MESSAGE_MAP(CChangeInitPin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangeInitPin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChangeInitPin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChangeInitPin ��Ϣ�������


void CChangeInitPin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	int ret = 0;

	if(m_username.IsEmpty())
	{
		MessageBox("�������û���","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrOldPin.IsEmpty())
	{
		MessageBox("������PIN��","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrNewPin.IsEmpty())
	{
		MessageBox("�������µ�PIN��","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(6<m_usrNewPin.GetLength() && m_usrNewPin.GetLength() >12)
	{
		MessageBox("�µ�PIN�볤�ȱ�����6~12λ֮��","",MB_ICONWARNING | MB_OK);
		return;
	}

	void * phSessionHandle=NULL;
	char uiIP[32]={0x00};
	memcpy(uiIP,ip_in,32);
	unsigned char ucName[32]={0x00};
	unsigned int uiNameLength = m_username.GetLength();
	memcpy(ucName,m_username.GetBuffer(),uiNameLength);

	unsigned char ucOldPasswordHash[32]={0x00};
	unsigned int uiOldPasswordHashLength=m_usrOldPin.GetLength();
	memcpy(ucOldPasswordHash,m_usrOldPin.GetBuffer(),uiOldPasswordHashLength);

	unsigned char ucNewPasswordHash[32]={0x00};
	unsigned int uiNewPasswordHashLength=m_usrNewPin.GetLength();
	memcpy(ucNewPasswordHash,m_usrNewPin.GetBuffer(),uiNewPasswordHashLength);

	ret = Km_ModifyInitPasswd (&phSessionHandle,uiIP,ucName,uiNameLength,ucOldPasswordHash,uiOldPasswordHashLength,ucNewPasswordHash,uiNewPasswordHashLength);
	if(0 != ret && KM_WRONGNAMEPASSWD != ret)
	{
		char outMip[100]={0x00};
		retValueParse(ret,outMip);
		MessageBox("�޸�ʧ��"+(CString)outMip,"",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(0 != ret && KM_WRONGNAMEPASSWD == ret)
	{
		MessageBox("�������","",MB_ICONWARNING | MB_OK);
		return;
	}
	else 
	{
		MessageBox("�޸ĳɹ�","",MB_ICONWARNING | MB_OK);
		CDialogEx::OnOK();
	}
	CSystemSmartKey syssckeyDlg(isRs_ChangePin);
	syssckeyDlg.DoModal();
	/*Cph_PWMngrDlg m_ph_PWMngrDlg(1,NULL,NULL,NULL,PWMMNGR_CAPTION);
	m_ph_PWMngrDlg.DoModal();*/
}


void CChangeInitPin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	CSystemSmartKey syssckeyDlg(isRs_ChangePin);
	syssckeyDlg.DoModal();
}


BOOL CChangeInitPin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
