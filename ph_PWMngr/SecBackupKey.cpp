// SecBackupKey.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SecBackupKey.h"
#include "afxdialogex.h"

// CSecBackupKey �Ի���

IMPLEMENT_DYNAMIC(CSecBackupKey, CDialogEx)

CSecBackupKey::CSecBackupKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSecBackupKey::IDD, pParent)
	, m_secpwdedit(0)
	, m_secpwdconedit(0)
{

}

CSecBackupKey::~CSecBackupKey()
{
}

void CSecBackupKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SECPWD_EDIT, m_secpwdedit);
	DDX_Text(pDX, IDC_SECCON_EDIT, m_secpwdconedit);
}


BEGIN_MESSAGE_MAP(CSecBackupKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSecBackupKey::OnBnClickedOk)
END_MESSAGE_MAP()


// CSecBackupKey ��Ϣ�������


void CSecBackupKey::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	this->OnOK();

	
}
