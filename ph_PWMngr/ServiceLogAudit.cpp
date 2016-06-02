// ServiceLogAudit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ServiceLogAudit.h"
#include "afxdialogex.h"


// CServiceLogAudit �Ի���

IMPLEMENT_DYNAMIC(CServiceLogAudit, CDialogEx)

CServiceLogAudit::CServiceLogAudit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServiceLogAudit::IDD, pParent)
{

}

CServiceLogAudit::~CServiceLogAudit()
{
}

void CServiceLogAudit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_serviceLog_shenji, m_slaudit_listctrl);
}


BEGIN_MESSAGE_MAP(CServiceLogAudit, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_sla_search, &CServiceLogAudit::OnBnClickedButtonslasearch)
	ON_BN_CLICKED(IDC_BUTTON_sla_firstpage, &CServiceLogAudit::OnBnClickedButtonslafirstpage)
	ON_BN_CLICKED(IDC_BUTTON_sla_prepage, &CServiceLogAudit::OnBnClickedButtonslaprepage)
	ON_BN_CLICKED(IDC_BUTTON_sla_nextpage, &CServiceLogAudit::OnBnClickedButtonslanextpage)
	ON_BN_CLICKED(IDC_BUTTON_sla_lastpage, &CServiceLogAudit::OnBnClickedButtonslalastpage)
END_MESSAGE_MAP()


// CServiceLogAudit ��Ϣ�������


void CServiceLogAudit::OnBnClickedButtonslasearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServiceLogAudit::OnBnClickedButtonslafirstpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServiceLogAudit::OnBnClickedButtonslaprepage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServiceLogAudit::OnBnClickedButtonslanextpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServiceLogAudit::OnBnClickedButtonslalastpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CServiceLogAudit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;   
    m_slaudit_listctrl.GetClientRect(&rect);   
    m_slaudit_listctrl.SetExtendedStyle(m_slaudit_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_slaudit_listctrl.SetImageList(&img_list,LVSIL_SMALL); 
  
	m_slaudit_listctrl.InsertColumn(1, _T("����ģ��"), LVCFMT_CENTER, rect.Width()/5, 1);   
    m_slaudit_listctrl.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rect.Width()/5, 2);   
    m_slaudit_listctrl.InsertColumn(3, _T("��������"), LVCFMT_CENTER, rect.Width()/5, 3); 
	m_slaudit_listctrl.InsertColumn(4, _T("�������"), LVCFMT_CENTER, rect.Width()/5, 4);
	m_slaudit_listctrl.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect.Width()/5, 5); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
