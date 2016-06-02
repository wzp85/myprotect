// FifthBackupKey.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "FifthBackupKey.h"
#include "afxdialogex.h"

#include "SignPWMAdmin.h"

// CFifthBackupKey �Ի���

IMPLEMENT_DYNAMIC(CFifthBackupKey, CDialogEx)

CFifthBackupKey::CFifthBackupKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFifthBackupKey::IDD, pParent)
	, m_fifthpwd(0)
	, m_fifthconpwd(0)
{

}

CFifthBackupKey::~CFifthBackupKey()
{
}

void CFifthBackupKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIFTHPWD_EDIT, m_fifthpwd);
	DDX_Text(pDX, IDC_FIFCONTHCON_EDIT, m_fifthconpwd);
}


BEGIN_MESSAGE_MAP(CFifthBackupKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFifthBackupKey::OnBnClickedOk)
END_MESSAGE_MAP()


// CFifthBackupKey ��Ϣ�������


void CFifthBackupKey::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	this->OnOK();
	CSignPWMAdmin signPWMAdminDlg;
	signPWMAdminDlg.DoModal();
}
