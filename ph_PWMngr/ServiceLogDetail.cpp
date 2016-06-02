// ServiceLogDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ServiceLogDetail.h"
#include "afxdialogex.h"
#include "ph_km.h"

// CServiceLogDetail 对话框

IMPLEMENT_DYNAMIC(CServiceLogDetail, CDialogEx)

CServiceLogDetail::CServiceLogDetail(void *phHandle,int nId,CString name,CString sn,CString hashalgid,CString symmalgid,CString plaindata,CString cipherdata,CString cert,CWnd* pParent /*=NULL*/)
	: CDialogEx(CServiceLogDetail::IDD, pParent)
{
	VERIFY(m_font.CreateFont(
    22,                        // nHeight
    10,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "楷体"));  

	in_name=name;
	in_sn=sn;
	in_hashalgid=hashalgid;
	in_symmalgid=symmalgid;
	in_plaindata=plaindata;
	in_cipherdata=cipherdata;
	in_cert=cert;
	in_id=nId;
	in_phHandle=phHandle;
}

CServiceLogDetail::~CServiceLogDetail()
{
}

void CServiceLogDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_sldetail_title, m_sld_title);
	CWnd *cWnd = GetDlgItem(IDC_STATIC_sldetail_title);
	cWnd->SetFont(&m_font);
	cWnd->SetWindowText("服务日志详情");
}


BEGIN_MESSAGE_MAP(CServiceLogDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CServiceLogDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CServiceLogDetail::OnBnClickedCheckLOG)
	ON_BN_CLICKED(IDCANCEL, &CServiceLogDetail::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CServiceLogDetail 消息处理程序


BOOL CServiceLogDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CString hashalg;
	if(!strncmp("2",in_hashalgid,2))
	{
		hashalg = "SHA1";
		SetDlgItemText(IDC_EDIT_sld_hashalgid,hashalg);
	}
	else if(!strncmp("4",in_hashalgid,2))
	{
		hashalg = "SHA256";
		SetDlgItemText(IDC_EDIT_sld_hashalgid,hashalg);
	}
	else if(!strncmp("1",in_hashalgid,2))
	{
		hashalg = "SM3";
		SetDlgItemText(IDC_EDIT_sld_hashalgid,hashalg);
	}
	else 
	{
		CString Hashalgid = " ";//-------------不在以上判断之内的算法显示空
		SetDlgItemText(IDC_EDIT_sld_hashalgid, Hashalgid);
	}
	SetDlgItemText(IDC_EDIT_sld_name,in_name);
	SetDlgItemText(IDC_EDIT_sld_serialn,in_sn);
	//SetDlgItemText(IDC_EDIT_sld_hashalgid,in_hashalgid);
	//SetDlgItemText(IDC_EDIT_sld_hashalgid,hashalg);
	SetDlgItemText(IDC_EDIT_sld_symmalgid,in_symmalgid);
	SetDlgItemText(IDC_EDIT_sld_plaindata,in_plaindata);
	SetDlgItemText(IDC_EDIT_sld_cipherdata,in_cipherdata);
	SetDlgItemText(IDC_EDIT_sld_cert,in_cert);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CServiceLogDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CServiceLogDetail::OnBnClickedCheckLOG()
{
	// TODO: 在此添加控件通知处理程序代码
	

	int ret=0;
	ret=Sig_CheckServiceLog(in_phHandle,in_id);
	if(ret==0)
		MessageBox("验证日志信息成功","验证日志信息成功",MB_ICONEXCLAMATION);
	else
		MessageBox("验证日志信息失败","验证日志信息失败",MB_ICONEXCLAMATION);
}

void CServiceLogDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


HBRUSH CServiceLogDetail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_sld_title.m_hWnd == pWnd->m_hWnd)
	{
	   //pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //返回空画刷，这一步是去掉背景色的
		//return m_brush;
	}
	return hbr;
}
