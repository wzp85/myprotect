// ForRecoveryFilePath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ForRecoveryFilePath.h"
#include "afxdialogex.h"


// CForRecoveryFilePath �Ի���

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


// CForRecoveryFilePath ��Ϣ�������


void CForRecoveryFilePath::OnBnClickedButtonfrll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("(*.backup)|*.backup|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("backup"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���  
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        SetDlgItemText(IDC_EDIT_for_recovery_fp, strFilePath);   
    } 
}


void CForRecoveryFilePath::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("�ָ��ɹ���","��ʾ",MB_ICONEXCLAMATION);
	UpdateData(TRUE);

	if(m_filepath_recoveryfile.IsEmpty())
	{
		MessageBox("��ѡ��Ҫ�ָ��ı����ļ���","",MB_ICONEXCLAMATION);
		return;
	}

	CDialogEx::OnOK();
}


void CForRecoveryFilePath::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CForRecoveryFilePath::GetRecoveryFilePath(char *path,int *pathLen)
{
	*pathLen=m_filepath_recoveryfile.GetLength();
	if(path!=NULL)
		memcpy(path,m_filepath_recoveryfile.GetBuffer(),m_filepath_recoveryfile.GetLength());
}