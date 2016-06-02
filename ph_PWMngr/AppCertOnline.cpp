// AppCertOnline.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertOnline.h"
#include "afxdialogex.h"
#include "AppCertMngr.h"

// CAppCertOnline 对话框


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


// CAppCertOnline 消息处理程序


void CAppCertOnline::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(0 == StandardType)//获取
	{
		if(m_CS_certUrl.IsEmpty())
		{
			MessageBox(_T("URL项不能为空！"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		CertUrl = m_CS_certUrl;
		StanType = strCertStandard;
	}
	else{//获取财政部接口ip地址，端口号
		if(m_certIP_CS.IsEmpty())
		{
			MessageBox(_T("ip地址不能为空！"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		if(m_certPort_CS.IsEmpty())
		{
			MessageBox(_T("端口号不能为空！"),_T(""),MB_ICONEXCLAMATION);
			return;
		}
		CertIP = m_certIP_CS;//ip地址
		CertPort =m_certPort_CS;//端口号
		StanType = strCertStandard;//财政标准
	}

	CDialogEx::OnOK();
}


void CAppCertOnline::OnCbnSelchangeComboCertstand()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int nSel; 
    nSel =m_certStandrd.GetCurSel(); //获取组合框控件列表里的选中项索引
	m_certStandrd.GetLBText(nSel,strCertStandard);//根据索引获取对应字符串
	if(strCertStandard == "财政RA标准")
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
	// TODO:  在此添加额外的初始化
	m_certStandrd.AddString(_T("普华RA标准"));//控件列表第一个
	m_certStandrd.InsertString(1,_T("财政RA标准"));
	m_certStandrd.InsertString(2,_T("税务RA标准"));
	SetDlgItemText(IDC_COMBO_CERTSTAND, _T("普华RA标准"));
	StandardType = 0;//财政部是1，其他是0
	m_certip.EnableWindow(FALSE);

	m_certPort.EnableWindow(FALSE);
	m_certUrl.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int CAppCertOnline:: GetURLandType(unsigned char*Stand_Type,unsigned int*StandTpeLength,unsigned char*Cert_Url,
	unsigned int*CertUrlLength,unsigned char*Cert_Ip,unsigned int*CertIpLength,unsigned char *Cert_Port,unsigned int*CertPortLength,unsigned int*type)
{
	if(0 == StandardType)//财政部是1，其他是0
	{
		if(CertUrl.IsEmpty())
		{
			MessageBox("URL项不能为空！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		*CertUrlLength = CertUrl.GetLength();
		if(Cert_Url != NULL)
		{
			memcpy(Cert_Url,CertUrl.GetBuffer(),CertUrl.GetLength());
		}

		if(StanType.IsEmpty())
		{
			MessageBox("证书标准不能为空！","提示",MB_ICONEXCLAMATION);
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
			MessageBox("ip地址不能为空！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		*CertIpLength = CertIP.GetLength();
		if(Cert_Ip != NULL)
		{
			memcpy(Cert_Ip,CertIP.GetBuffer(),CertIP.GetLength());
		}
		if(StanType.IsEmpty())
		{
			MessageBox("证书标准不能为空！","提示",MB_ICONEXCLAMATION);
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
		//*Cert_Port = CertPort;//端口号
	}
	*type = StandardType;
	return 0;
}