// VerifyStrategyFive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyFive.h"
#include "afxdialogex.h"


// CVerifyStrategyFive �Ի���

IMPLEMENT_DYNAMIC(CVerifyStrategyFive, CDialogEx)

CVerifyStrategyFive::CVerifyStrategyFive(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVerifyStrategyFive::IDD, pParent)
	, m_vs5_ocsp(_T(""))
{

}

CVerifyStrategyFive::~CVerifyStrategyFive()
{
}

void CVerifyStrategyFive::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_vs5_OCSP,m_vs5_ocsp );

}


BEGIN_MESSAGE_MAP(CVerifyStrategyFive, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_vs5_1, &CVerifyStrategyFive::OnBnClickedButtonvs51)
END_MESSAGE_MAP()


// CVerifyStrategyFive ��Ϣ�������


BOOL CVerifyStrategyFive::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CVerifyStrategyFive::OnBnClickedButtonvs51()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_vs5_ocsp.IsEmpty())
	{
		MessageBox("�����������Ϣ��","��ʾ",MB_ICONEXCLAMATION);
		return ;
	}
	vs5_ocsp = m_vs5_ocsp;

}

int CVerifyStrategyFive::GetDataVS5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	/*if(m_vs5_ocsp.IsEmpty())
	{
		MessageBox("�����������Ϣ��","��ʾ",MB_ICONEXCLAMATION);
		return -1;
	}*/
	vs5_ocsp = m_vs5_ocsp;
	return 0;

}
int CVerifyStrategyFive::GetVs5_ocsp(unsigned char *pucdata,unsigned int *pucdatalen)
{
	//-----------------------------------��ȡ������Ϣ
	CVerifyStrategyFive::GetDataVS5();
	//--------------------------------------
	if(vs5_ocsp.IsEmpty())
	{
		*pucdatalen = 0;
	}
	else{
		*pucdatalen = vs5_ocsp.GetLength();//add by syc
		if(pucdata != NULL)
			memcpy(pucdata,vs5_ocsp.GetBuffer(),vs5_ocsp.GetLength());
	}	
		
		return 0;
}

void CVerifyStrategyFive::SetVs5_ocsp(unsigned char *pucdata)
{
	if(pucdata != NULL)
		SetDlgItemText(IDC_EDIT_vs5_OCSP,CString(pucdata));
}
