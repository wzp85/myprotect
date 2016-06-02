// SecBackupKey.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SecBackupKey.h"
#include "afxdialogex.h"

// CSecBackupKey 对话框

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


// CSecBackupKey 消息处理程序


void CSecBackupKey::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	this->OnOK();

	
}
