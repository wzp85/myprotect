// SeeLogDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SeeLogDetail.h"
#include "afxdialogex.h"


// CSeeLogDetail 对话框

IMPLEMENT_DYNAMIC(CSeeLogDetail, CDialogEx)

CSeeLogDetail::CSeeLogDetail(CString logid,CString admid,CString opk,CString opd,CString oper,CString opre,CString opdetail,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeeLogDetail::IDD, pParent)
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

	param_logid=logid;
	param_admid=admid;
	param_opk=opk;
	param_opd=opd;
	param_oper=oper;
	param_opre=opre;
	param_opdetail=opdetail;
}

CSeeLogDetail::~CSeeLogDetail()
{
}

void CSeeLogDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_logdetail, m_lgd_title);
	CWnd *cWnd = GetDlgItem(IDC_STATIC_logdetail);
	cWnd->SetFont(&m_font);
	cWnd->SetWindowText("日志详情");
}


BEGIN_MESSAGE_MAP(CSeeLogDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSeeLogDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSeeLogDetail::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSeeLogDetail 消息处理程序


BOOL CSeeLogDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_lgd_lgid,param_logid);
	SetDlgItemText(IDC_EDIT_lgd_admid,param_admid);
	SetDlgItemText(IDC_EDIT_lgd_opk,param_opk);
	SetDlgItemText(IDC_EDIT_lgd_opd,param_opd);
	SetDlgItemText(IDC_EDIT_lgd_oper,param_oper);
	SetDlgItemText(IDC_EDIT_lgd_opr,param_opre);
	SetDlgItemText(IDC_EDIT_lgd_lgdetail,param_opdetail);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSeeLogDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CSeeLogDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

HBRUSH CSeeLogDetail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_lgd_title.m_hWnd == pWnd->m_hWnd)
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