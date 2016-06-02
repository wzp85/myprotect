// VerifyStrategyOne.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyOne.h"
#include "afxdialogex.h"

#include "MyUtil.h"
// CVerifyStrategyOne 对话框

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


// CVerifyStrategyOne 消息处理程序


BOOL CVerifyStrategyOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CVerifyStrategyOne::OnBnClickedButtonvs11()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_crlPath_cs.IsEmpty())
	{
		MessageBox("请选择CRL文件！","提示",MB_ICONEXCLAMATION);
		return;
	}
	crl_path = m_crlPath_cs;
}
int  CVerifyStrategyOne::GetDataVS1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/*if(m_crlPath_cs.IsEmpty())
	{
		MessageBox("请选择CRL文件！","提示",MB_ICONEXCLAMATION);
		return -1;
	}*/
	crl_path = m_crlPath_cs;
	return 0;
}

int CVerifyStrategyOne::GetCRLpath_vs1(unsigned char *pathorData,unsigned int *pathlen)
{
	//----------------------------------获取界面信息
	CVerifyStrategyOne::GetDataVS1();
	//------------------------------------
	/*if(crl_path.IsEmpty())
	{
		MessageBox("请选择CRL文件！","提示",MB_ICONEXCLAMATION);
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
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("(*.crl)|*.crl|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("crl"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框  
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
//		crl_path = strFilePath;
        SetDlgItemText(IDC_EDIT_vs1_crlfilepath, strFilePath);   
    } 
}
