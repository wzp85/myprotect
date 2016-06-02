// UpdateSetMngr.cpp : implementation file
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "UpdateSetMngr.h"
#include "afxdialogex.h"


// CUpdateSetMngr dialog

IMPLEMENT_DYNAMIC(CUpdateSetMngr, CDialogEx)

CUpdateSetMngr::CUpdateSetMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateSetMngr::IDD, pParent)
{

}

CUpdateSetMngr::~CUpdateSetMngr()
{
}

void CUpdateSetMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUpdateSetMngr, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CUpdateSetMngr::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CUpdateSetMngr::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CUpdateSetMngr message handlers


void CUpdateSetMngr::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here

	GetDlgItem(IDC_DATE_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATE_DATETIMEPICKER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIME_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIME_DATETIMEPICKER)->ShowWindow(SW_HIDE);

    GetDlgItem(IDC_UPDATE_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_UPDTE_EDIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SOURCE_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SOURCE_COMBO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK_BUTTON)->ShowWindow(SW_SHOW);
}


void CUpdateSetMngr::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_UPDATE_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_UPDTE_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SOURCE_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SOURCE_COMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_BUTTON)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_DATE_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATE_DATETIMEPICKER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_TIME_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_TIME_DATETIMEPICKER)->ShowWindow(SW_SHOW);
	
}
