// SeeLogDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SeeLogDetail.h"
#include "afxdialogex.h"


// CSeeLogDetail �Ի���

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
    "����"));  

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
	cWnd->SetWindowText("��־����");
}


BEGIN_MESSAGE_MAP(CSeeLogDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSeeLogDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSeeLogDetail::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSeeLogDetail ��Ϣ�������


BOOL CSeeLogDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT_lgd_lgid,param_logid);
	SetDlgItemText(IDC_EDIT_lgd_admid,param_admid);
	SetDlgItemText(IDC_EDIT_lgd_opk,param_opk);
	SetDlgItemText(IDC_EDIT_lgd_opd,param_opd);
	SetDlgItemText(IDC_EDIT_lgd_oper,param_oper);
	SetDlgItemText(IDC_EDIT_lgd_opr,param_opre);
	SetDlgItemText(IDC_EDIT_lgd_lgdetail,param_opdetail);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSeeLogDetail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CSeeLogDetail::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //���ؿջ�ˢ����һ����ȥ������ɫ��
		//return m_brush;
	}
	return hbr;
}