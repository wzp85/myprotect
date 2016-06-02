// VerifyStrategyOne.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyOne.h"
#include "afxdialogex.h"

#include "MyUtil.h"
// CVerifyStrategyOne �Ի���

IMPLEMENT_DYNAMIC(CVerifyStrategyOne, CDialogEx)

CVerifyStrategyOne::CVerifyStrategyOne(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVerifyStrategyOne::IDD, pParent)
	, m_crlPath_cs(_T(""))
{

}

CVerifyStrategyOne::~CVerifyStrategyOne()
{
}

void CVerifyStrategyOne::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_vs1_crlfilepath, m_crlPath_cs);
}


BEGIN_MESSAGE_MAP(CVerifyStrategyOne, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_vs1_1, &CVerifyStrategyOne::OnBnClickedButtonvs11)
	ON_BN_CLICKED(IDC_BUTTON_vs1_browse, &CVerifyStrategyOne::OnBnClickedButtonvs1browse)
END_MESSAGE_MAP()


// CVerifyStrategyOne ��Ϣ�������


BOOL CVerifyStrategyOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CVerifyStrategyOne::OnBnClickedButtonvs11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_crlPath_cs.IsEmpty())
	{
		MessageBox("��ѡ��CRL�ļ���","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	crl_path = m_crlPath_cs;
}
int  CVerifyStrategyOne::GetDataVS1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	/*if(m_crlPath_cs.IsEmpty())
	{
		MessageBox("��ѡ��CRL�ļ���","��ʾ",MB_ICONEXCLAMATION);
		return -1;
	}*/
	crl_path = m_crlPath_cs;
	return 0;
}

int CVerifyStrategyOne::GetCRLpath_vs1(unsigned char *pathorData,unsigned int *pathlen)
{
	//----------------------------------��ȡ������Ϣ
	CVerifyStrategyOne::GetDataVS1();
	//------------------------------------
	/*if(crl_path.IsEmpty())
	{
		MessageBox("��ѡ��CRL�ļ���","��ʾ",MB_ICONEXCLAMATION);
		return -1;
	}*/
	unsigned char *pData=NULL;
	int  length=0;
	if(crl_path.IsEmpty())
	{
		*pathlen = 0;
	}
	else{
		CMyUtil::ReadData((LPSTR)(LPCTSTR)crl_path,pData,&length);
		*pathlen = length;
	}
	if(pathorData != NULL)
	{
		pData = new unsigned char[length+1];
		memset(pData,0x00,length+1);
		CMyUtil::ReadData((LPSTR)(LPCTSTR)crl_path,pData,&length);
		memcpy(pathorData,pData,length);
		delete []pData;
	}
	return 0;
}

void CVerifyStrategyOne::SetCRLpath_vs1(unsigned char *path)
{
	if(path != NULL)
		SetDlgItemText(IDC_EDIT_vs1_crlfilepath,CString(path)); 
}

void CVerifyStrategyOne::OnBnClickedButtonvs1browse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����  
    TCHAR szFilter[] = _T("(*.crl)|*.crl|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���  
    CFileDialog fileDlg(TRUE, _T("crl"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���  
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();  
//		crl_path = strFilePath;
        SetDlgItemText(IDC_EDIT_vs1_crlfilepath, strFilePath);   
    } 
}
