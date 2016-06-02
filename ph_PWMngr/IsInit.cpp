// IsInit.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "IsInit.h"
#include "afxdialogex.h"

#include "ChoseAlgid.h"
#include "ph_PWMngrDlg.h"
#define PWMMNGR_CAPTION _T("上海普华密码机管理系统 Version 2.0")

#include "ph_km.h"

// CIsInit 对话框

IMPLEMENT_DYNAMIC(CIsInit, CDialogEx)

CIsInit::CIsInit(void *key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CIsInit::IDD, pParent)
	, m_line1(_T(""))
{
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
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
    "宋体"));                 // lpszFacename

	VERIFY(font_lineWord.CreateFont(
    15,                        // nHeight
    8,                         // nWidth
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
    "宋体"));                 // lpszFacename

	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
}

CIsInit::~CIsInit()
{
}

void CIsInit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ISINITCON_STATIC, m_line1);
	CWnd *cWnd = GetDlgItem(IDC_ISINITCON_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("验证口令成功！系统已经初始化，是否重新初始化？");

	cWnd = GetDlgItem(IDC_LINEWORD_STATIC);
	cWnd->SetFont(&font_lineWord);
	cWnd->SetWindowText("  注：重新初始化将会销毁密码机所管理的密钥。如果密码机所保存的密钥以后还需要继续使用，请确认本机的应用密钥、密钥加密密钥已经备份，如果没有备份，需要备份，否则无法恢复。");
	
	DDX_Control(pDX, IDC_ISINITCON_STATIC, m_isInitCon);
	DDX_Control(pDX, IDC_LINEWORD_STATIC, m_lineWord);
}


BEGIN_MESSAGE_MAP(CIsInit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIsInit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CIsInit::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CIsInit 消息处理程序
HBRUSH CIsInit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_isInitCon.m_hWnd == pWnd->m_hWnd)
	{
	   //pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&font);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //返回空画刷，这一步是去掉背景色的
		//return m_brush;
	}
	if(m_lineWord.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&font_lineWord);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextCharacterExtra(1);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //返回空画刷，这一步是去掉背景色的
	}

	return hbr;
}


void CIsInit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	INT_PTR nRes;   
  
    // 显示消息对话框  
    nRes = MessageBox(_T("本操作将会清空密码机所管理的密钥，请确认是否已经备份密钥"),_T("提示"), MB_OKCANCEL | MB_ICONQUESTION);   
    // 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行  
    if (IDCANCEL == nRes)   
        return; 
	nRes = MessageBox(_T("请点击“确定”生成主密钥"),_T("提示"),MB_OKCANCEL | MB_ICONWARNING);
	if(IDOK != nRes)
		return;
	this->OnOK();
	//----------------调用生成主密钥接口------------------------//
	int ret = 0;
	//void ** phSessionHandle;
	//phSessionHandle = m_phSessionHandle;
	ret = Km_GenMainKey(phSHandle);
	if(!ret)
	{
		CChoseAlgid choseAlgidDlg(key_phSHandle,phSHandle);
		choseAlgidDlg.DoModal();
	}
	else
	{
		char outGmk[100]={0x00};
		retValueParse(ret,outGmk);
		MessageBox("生成主密钥失败"+(CString)outGmk);
		return;
	}
}


void CIsInit::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	Cph_PWMngrDlg ph_PWMngrDlg(NULL,1,NULL,NULL,NULL,PWMMNGR_CAPTION);
	ph_PWMngrDlg.DoModal();
}
