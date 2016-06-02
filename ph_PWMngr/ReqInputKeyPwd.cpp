// ReqInputKeyPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ReqInputKeyPwd.h"
#include "afxdialogex.h"


// CReqInputKeyPwd 对话框

IMPLEMENT_DYNAMIC(CReqInputKeyPwd, CDialogEx)

CReqInputKeyPwd::CReqInputKeyPwd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReqInputKeyPwd::IDD, pParent)
	, m_req_pinf(_T(""))
	, m_req_pins(_T(""))
{

}

CReqInputKeyPwd::~CReqInputKeyPwd()
{
}

void CReqInputKeyPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REQPWDF, m_req_pinf);
	DDX_Text(pDX, IDC_EDIT_REQPWDS, m_req_pins);
}


BEGIN_MESSAGE_MAP(CReqInputKeyPwd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CReqInputKeyPwd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReqInputKeyPwd::OnBnClickedCancel)
END_MESSAGE_MAP()


// CReqInputKeyPwd 消息处理程序


void CReqInputKeyPwd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_req_pinf.IsEmpty())
	{
		MessageBox("私钥使用授权码不能为空！","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(m_req_pinf != m_req_pins)
	{
		MessageBox("两次输入不一致！","提示",MB_ICONEXCLAMATION);
		return;
	}
	memcpy(kpwd,m_req_pinf.GetBuffer(),m_req_pinf.GetLength());
	klen=m_req_pinf.GetLength();
	CDialogEx::OnOK();
}


void CReqInputKeyPwd::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CReqInputKeyPwd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd *cWnd = GetDlgItem(IDC_EDIT_REQPWDF);
	cWnd->SetFocus();
	memset(kpwd,0x00,32);
	klen=0;

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReqInputKeyPwd::GetKeyPassword(unsigned char *word,unsigned int *len)
{
	if(NULL != word)
		memcpy(word,kpwd,strlen((char*)kpwd));
	*len =klen; 
}