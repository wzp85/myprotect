// ServiceLogDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ServiceLogDetail.h"
#include "afxdialogex.h"
#include "ph_km.h"

// CServiceLogDetail �Ի���

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
    "����"));  

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
	cWnd->SetWindowText("������־����");
}


BEGIN_MESSAGE_MAP(CServiceLogDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CServiceLogDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CServiceLogDetail::OnBnClickedCheckLOG)
	ON_BN_CLICKED(IDCANCEL, &CServiceLogDetail::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CServiceLogDetail ��Ϣ�������


BOOL CServiceLogDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
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
		CString Hashalgid = " ";//-------------���������ж�֮�ڵ��㷨��ʾ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CServiceLogDetail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CServiceLogDetail::OnBnClickedCheckLOG()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	

	int ret=0;
	ret=Sig_CheckServiceLog(in_phHandle,in_id);
	if(ret==0)
		MessageBox("��֤��־��Ϣ�ɹ�","��֤��־��Ϣ�ɹ�",MB_ICONEXCLAMATION);
	else
		MessageBox("��֤��־��Ϣʧ��","��֤��־��Ϣʧ��",MB_ICONEXCLAMATION);
}

void CServiceLogDetail::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //���ؿջ�ˢ����һ����ȥ������ɫ��
		//return m_brush;
	}
	return hbr;
}
