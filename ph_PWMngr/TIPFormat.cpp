// TIPFormat.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "TIPFormat.h"
#include "afxdialogex.h"


// CTIPFormat 对话框

IMPLEMENT_DYNAMIC(CTIPFormat, CDialogEx)

CTIPFormat::CTIPFormat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTIPFormat::IDD, pParent)
	, m_myStatic_line1(_T(""))
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
    "宋体"));                 // lpszFacename
}

CTIPFormat::~CTIPFormat()
{
}

void CTIPFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYCOLORFONT_STATIC, m_myStatic);
	DDX_Text(pDX, IDC_MYCOLORFONT_STATIC, m_myStatic_line1);
	CWnd *cWnd = GetDlgItem(IDC_MYCOLORFONT_STATIC);
	cWnd->SetFont(&m_font);
	cWnd->SetWindowText("您插入的是密钥备份密钥key，请确认是否要格式化，如果格式化，经该key备份过的密钥将无法恢复！");
}

BOOL CTIPFormat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//m_font.CreatePointFont(130,_T("宋体"));
	//m_brush.CreateSolidBrush(RGB(0,0,0));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CTIPFormat, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTIPFormat 消息处理程序
HBRUSH CTIPFormat::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_myStatic.m_hWnd == pWnd->m_hWnd)
	{
	   //pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //返回空画刷，这一步是去掉背景色的
		//return m_brush;
	}
	return hbr;
}