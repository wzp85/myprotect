// TIPDistroy.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "TIPDistroy.h"
#include "afxdialogex.h"


// CTIPDistroy 对话框

IMPLEMENT_DYNAMIC(CTIPDistroy, CDialogEx)

CTIPDistroy::CTIPDistroy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTIPDistroy::IDD, pParent)
{

}

CTIPDistroy::~CTIPDistroy()
{
}

void CTIPDistroy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTIPDistroy, CDialogEx)
END_MESSAGE_MAP()


// CTIPDistroy 消息处理程序
