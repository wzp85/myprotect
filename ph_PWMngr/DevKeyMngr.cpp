// DevKeyMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevKeyMngr.h"
#include "afxdialogex.h"


// CDevKeyMngr �Ի���

IMPLEMENT_DYNAMIC(CDevKeyMngr, CDialogEx)

CDevKeyMngr::CDevKeyMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevKeyMngr::IDD, pParent)
{

}

CDevKeyMngr::~CDevKeyMngr()
{
}

void CDevKeyMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevKeyMngr, CDialogEx)
END_MESSAGE_MAP()


// CDevKeyMngr ��Ϣ�������
