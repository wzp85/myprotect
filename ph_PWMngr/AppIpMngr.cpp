// AppIpMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppIpMngr.h"
#include "afxdialogex.h"


// CAppIpMngr �Ի���

IMPLEMENT_DYNAMIC(CAppIpMngr, CDialogEx)

CAppIpMngr::CAppIpMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppIpMngr::IDD, pParent)
{
	VERIFY(m_font.CreateFont(
    20,                        // nHeight
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
}

CAppIpMngr::~CAppIpMngr()
{
}

void CAppIpMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_appip_title, m_aim_title);
	CWnd *cWnd = GetDlgItem(IDC_STATIC_appip_title);
	cWnd->SetFont(&m_font);
	cWnd->SetWindowText("Ӧ��IP��ַ����");
	DDX_Control(pDX, IDC_EDIT_aim_iparea, m_aim_area_edit);
	DDX_Control(pDX, IDC_EDIT_aim_ipaddress, m_aim_only_edit);
}


BEGIN_MESSAGE_MAP(CAppIpMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_appipmngr, &CAppIpMngr::OnBnClickedButtonappipmngr)
	ON_BN_CLICKED(IDC_RADIO_aim_open, &CAppIpMngr::OnBnClickedRadioaimopen)
	ON_BN_CLICKED(IDC_RADIO_aim_openarea, &CAppIpMngr::OnBnClickedRadioaimopenarea)
	ON_BN_CLICKED(IDC_RADIO_aim_openonly, &CAppIpMngr::OnBnClickedRadioaimopenonly)
END_MESSAGE_MAP()


// CAppIpMngr ��Ϣ�������


void CAppIpMngr::OnBnClickedButtonappipmngr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("Ӧ��IP���ñ���ɹ���","",MB_ICONEXCLAMATION);
}


BOOL CAppIpMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAppIpMngr::OnBnClickedRadioaimopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_aim_area_edit.SetReadOnly(TRUE);
	m_aim_only_edit.SetReadOnly(TRUE);
}


void CAppIpMngr::OnBnClickedRadioaimopenarea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_aim_area_edit.SetReadOnly(FALSE);
	m_aim_only_edit.SetReadOnly(TRUE);
}


void CAppIpMngr::OnBnClickedRadioaimopenonly()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_aim_area_edit.SetReadOnly(TRUE);
	m_aim_only_edit.SetReadOnly(FALSE);
}
