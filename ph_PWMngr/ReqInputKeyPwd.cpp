// ReqInputKeyPwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ReqInputKeyPwd.h"
#include "afxdialogex.h"


// CReqInputKeyPwd �Ի���

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


// CReqInputKeyPwd ��Ϣ�������


void CReqInputKeyPwd::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(m_req_pinf.IsEmpty())
	{
		MessageBox("˽Կʹ����Ȩ�벻��Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(m_req_pinf != m_req_pins)
	{
		MessageBox("�������벻һ�£�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	memcpy(kpwd,m_req_pinf.GetBuffer(),m_req_pinf.GetLength());
	klen=m_req_pinf.GetLength();
	CDialogEx::OnOK();
}


void CReqInputKeyPwd::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CReqInputKeyPwd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CWnd *cWnd = GetDlgItem(IDC_EDIT_REQPWDF);
	cWnd->SetFocus();
	memset(kpwd,0x00,32);
	klen=0;

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CReqInputKeyPwd::GetKeyPassword(unsigned char *word,unsigned int *len)
{
	if(NULL != word)
		memcpy(word,kpwd,strlen((char*)kpwd));
	*len =klen; 
}