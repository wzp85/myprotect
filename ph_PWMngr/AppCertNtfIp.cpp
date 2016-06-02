// AppCertNtfIp.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertNtfIp.h"
#include "afxdialogex.h"
#include "ph_km.h"


// CAppCertNtfIp 对话框

IMPLEMENT_DYNAMIC(CAppCertNtfIp, CDialogEx)

CAppCertNtfIp::CAppCertNtfIp(void *handle,CWnd* pParent  /*=NULL*/)
	: CDialogEx(CAppCertNtfIp::IDD, pParent)
{
	phHandle_NtfIp = handle;
}

CAppCertNtfIp::~CAppCertNtfIp()
{
}

void CAppCertNtfIp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ConfigIP);
}


BEGIN_MESSAGE_MAP(CAppCertNtfIp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAppCertNtfIp::OnBnClickedOk)
END_MESSAGE_MAP()


// CAppCertNtfIp 消息处理程序
int  CAppCertNtfIp::GetValue()
{
	/**********获得ip地址************/
	/*CString AppCondfigIp;
	AppCondfigIp.Format("%s","192.168.1.111");
	m_ConfigIP.SetWindowTextA(AppCondfigIp);*/

	CString NTP_CS;
	
	char temp[100]={0x0};
	int len=0;
	Sig_NTPAddrSet(phHandle_NtfIp,(unsigned int *)&len ,(unsigned char *)temp);
	NTP_CS.Format("%s",temp);
	m_ConfigIP.SetWindowTextA(NTP_CS);


	return 0;
}

void CAppCertNtfIp::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strm_NetConfig1;

	m_ConfigIP.GetWindowTextA(strm_NetConfig1);
	if(0 == strcmp(strm_NetConfig1,"0.0.0.0"))
	{
		MessageBox("请输入IP地址","提示");
		return;
	}

	char *temp=(LPSTR)(LPCSTR)strm_NetConfig1;
	//char *temp="192.168.2.2";
	int len=strlen(temp);
	Sig_NTPAddrSet(phHandle_NtfIp,(unsigned int *)&len ,(unsigned char *)temp);



	CDialogEx::OnOK();
}


BOOL CAppCertNtfIp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetValue();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
