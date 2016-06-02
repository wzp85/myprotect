// VerifyStrategyFive.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyFive.h"
#include "afxdialogex.h"


// CVerifyStrategyFive 对话框

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


// CVerifyStrategyFive 消息处理程序


BOOL CVerifyStrategyFive::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CVerifyStrategyFive::OnBnClickedButtonvs51()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_vs5_ocsp.IsEmpty())
	{
		MessageBox("请输入相关信息！","提示",MB_ICONEXCLAMATION);
		return ;
	}
	vs5_ocsp = m_vs5_ocsp;

}

int CVerifyStrategyFive::GetDataVS5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/*if(m_vs5_ocsp.IsEmpty())
	{
		MessageBox("请输入相关信息！","提示",MB_ICONEXCLAMATION);
		return -1;
	}*/
	vs5_ocsp = m_vs5_ocsp;
	return 0;

}
int CVerifyStrategyFive::GetVs5_ocsp(unsigned char *pucdata,unsigned int *pucdatalen)
{
	//-----------------------------------获取数据信息
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
