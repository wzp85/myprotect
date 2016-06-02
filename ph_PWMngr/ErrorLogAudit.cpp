// ErrorLogAudit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ErrorLogAudit.h"
#include "afxdialogex.h"


// CErrorLogAudit �Ի���

IMPLEMENT_DYNAMIC(CErrorLogAudit, CDialogEx)

CErrorLogAudit::CErrorLogAudit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorLogAudit::IDD, pParent)
{

}

CErrorLogAudit::~CErrorLogAudit()
{
}

void CErrorLogAudit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_errorLog_shenji, m_errorlogaudit_listctrl);
}


BEGIN_MESSAGE_MAP(CErrorLogAudit, CDialogEx)
END_MESSAGE_MAP()


// CErrorLogAudit ��Ϣ�������


BOOL CErrorLogAudit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;   
    m_errorlogaudit_listctrl.GetClientRect(&rect);   
    m_errorlogaudit_listctrl.SetExtendedStyle(m_errorlogaudit_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_errorlogaudit_listctrl.SetImageList(&img_list,LVSIL_SMALL); 
  
	m_errorlogaudit_listctrl.InsertColumn(1, _T("����ģ��"), LVCFMT_CENTER, rect.Width()/5, 1);   
    m_errorlogaudit_listctrl.InsertColumn(2, _T("������"), LVCFMT_CENTER, rect.Width()/5, 2);   
    m_errorlogaudit_listctrl.InsertColumn(3, _T("������"), LVCFMT_CENTER, rect.Width()/5, 3); 
	m_errorlogaudit_listctrl.InsertColumn(4, _T("�����ļ�"), LVCFMT_CENTER, rect.Width()/5, 4);
	m_errorlogaudit_listctrl.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect.Width()/5, 5); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
