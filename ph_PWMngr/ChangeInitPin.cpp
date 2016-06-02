// ChangeInitPin.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ChangeInitPin.h"
#include "afxdialogex.h"

#include "ph_PWMngrDlg.h"
#include "ph_km.h"
#include "SystemSmartKey.h"
#define PWMMNGR_CAPTION _T("上海普华密码机管理系统")
// CChangeInitPin 对话框

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


// CChangeInitPin 消息处理程序


void CChangeInitPin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	int ret = 0;

	if(m_username.IsEmpty())
	{
		MessageBox("请输入用户名","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrOldPin.IsEmpty())
	{
		MessageBox("请输入PIN码","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrNewPin.IsEmpty())
	{
		MessageBox("请输入新的PIN码","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(6<m_usrNewPin.GetLength() && m_usrNewPin.GetLength() >12)
	{
		MessageBox("新的PIN码长度必须在6~12位之间","",MB_ICONWARNING | MB_OK);
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
		MessageBox("修改失败"+(CString)outMip,"",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(0 != ret && KM_WRONGNAMEPASSWD == ret)
	{
		MessageBox("口令错误","",MB_ICONWARNING | MB_OK);
		return;
	}
	else 
	{
		MessageBox("修改成功","",MB_ICONWARNING | MB_OK);
		CDialogEx::OnOK();
	}
	CSystemSmartKey syssckeyDlg(isRs_ChangePin);
	syssckeyDlg.DoModal();
	/*Cph_PWMngrDlg m_ph_PWMngrDlg(1,NULL,NULL,NULL,PWMMNGR_CAPTION);
	m_ph_PWMngrDlg.DoModal();*/
}


void CChangeInitPin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	CSystemSmartKey syssckeyDlg(isRs_ChangePin);
	syssckeyDlg.DoModal();
}


BOOL CChangeInitPin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
