// InitKeyTip.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "InitKeyTip.h"
#include "afxdialogex.h"


// CInitKeyTip 对话框

IMPLEMENT_DYNAMIC(CInitKeyTip, CDialogEx)

CInitKeyTip::CInitKeyTip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitKeyTip::IDD, pParent)
{

}

CInitKeyTip::~CInitKeyTip()
{
}

void CInitKeyTip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInitKeyTip, CDialogEx)
END_MESSAGE_MAP()


// CInitKeyTip 消息处理程序
