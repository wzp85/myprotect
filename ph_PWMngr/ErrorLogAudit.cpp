// ErrorLogAudit.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ErrorLogAudit.h"
#include "afxdialogex.h"


// CErrorLogAudit 对话框

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


// CErrorLogAudit 消息处理程序


BOOL CErrorLogAudit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;   
    m_errorlogaudit_listctrl.GetClientRect(&rect);   
    m_errorlogaudit_listctrl.SetExtendedStyle(m_errorlogaudit_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	//设置行高！
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_errorlogaudit_listctrl.SetImageList(&img_list,LVSIL_SMALL); 
  
	m_errorlogaudit_listctrl.InsertColumn(1, _T("错误模块"), LVCFMT_CENTER, rect.Width()/5, 1);   
    m_errorlogaudit_listctrl.InsertColumn(2, _T("错误函数"), LVCFMT_CENTER, rect.Width()/5, 2);   
    m_errorlogaudit_listctrl.InsertColumn(3, _T("错误句柄"), LVCFMT_CENTER, rect.Width()/5, 3); 
	m_errorlogaudit_listctrl.InsertColumn(4, _T("错误文件"), LVCFMT_CENTER, rect.Width()/5, 4);
	m_errorlogaudit_listctrl.InsertColumn(5, _T("操作时间"), LVCFMT_CENTER, rect.Width()/5, 5); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
