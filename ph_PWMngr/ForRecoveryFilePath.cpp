// ForRecoveryFilePath.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ForRecoveryFilePath.h"
#include "afxdialogex.h"


// CForRecoveryFilePath 对话框

IMPLEMENT_DYNAMIC(CForRecoveryFilePath, CDialogEx)

CForRecoveryFilePath::CForRecoveryFilePath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CForRecoveryFilePath::IDD, pParent)
	, m_filepath_recoveryfile(_T(""))
{

}

CForRecoveryFilePath::~CForRecoveryFilePath()
{
}

void CForRecoveryFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_for_recovery_fp, m_filepath_recoveryfile);
}


BEGIN_MESSAGE_MAP(CForRecoveryFilePath, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_frll, &CForRecoveryFilePath::OnBnClickedButtonfrll)
	ON_BN_CLICKED(IDOK, &CForRecoveryFilePath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CForRecoveryFilePath::OnBnClickedCancel)
END_MESSAGE_MAP()


// CForRecoveryFilePath 消息处理程序


void CForRecoveryFilePath::OnBnClickedButtonfrll()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("(*.backup)|*.backup|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("backup"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框  
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        SetDlgItemText(IDC_EDIT_for_recovery_fp, strFilePath);   
    } 
}


void CForRecoveryFilePath::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("恢复成功！","提示",MB_ICONEXCLAMATION);
	UpdateData(TRUE);

	if(m_filepath_recoveryfile.IsEmpty())
	{
		MessageBox("请选择要恢复的备份文件！","",MB_ICONEXCLAMATION);
		return;
	}

	CDialogEx::OnOK();
}


void CForRecoveryFilePath::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CForRecoveryFilePath::GetRecoveryFilePath(char *path,int *pathLen)
{
	*pathLen=m_filepath_recoveryfile.GetLength();
	if(path!=NULL)
		memcpy(path,m_filepath_recoveryfile.GetBuffer(),m_filepath_recoveryfile.GetLength());
}