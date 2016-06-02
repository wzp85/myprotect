// SeeDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SeeDetail.h"
#include "afxdialogex.h"


// CSeeDetail 对话框

IMPLEMENT_DYNAMIC(CSeeDetail, CDialogEx)

CSeeDetail::CSeeDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeeDetail::IDD, pParent)
	, m_appName(_T(""))
{

}

CSeeDetail::CSeeDetail(LPCTSTR appName,LPCTSTR keyIndex,LPCTSTR algId,LPCTSTR keyType,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeeDetail::IDD, pParent)
	,m_appName(_T(""))
{
	m_appName = appName;
	m_keyIndex_show = keyIndex;
	m_algId_show = algId;
	m_keyType_show = keyType;
}

CSeeDetail::~CSeeDetail()
{
}

void CSeeDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_APPNAME_EDIT, m_appName);
	DDX_Control(pDX, IDC_ALGID_COMBO, m_algId);
	DDX_Control(pDX, IDC_KEYINDEX_COMBO, m_keyIndex);
	DDX_Control(pDX, IDC_APPTYPE_COMBO, m_appType);
	DDX_Control(pDX, IDC_KEYTYPE_COMBO, m_keyType);
}

BOOL CSeeDetail::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
	CDialogEx::OnInitDialog();
  
    // Add "About..." menu item to system menu.   
 
    // IDM_ABOUTBOX must be in the system command range.   
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
  
    // Set the icon for this dialog.  The framework does this automatically   
    //  when the application's main window is not a dialog   
    SetIcon(m_hIcon, TRUE);         // Set big icon   
    SetIcon(m_hIcon, FALSE);        // Set small icon   
  

	SetDlgItemText(IDC_APPNAME_EDIT,m_appName);

	m_algId.AddString(m_algId_show); 
	SetDlgItemText(IDC_ALGID_COMBO, m_algId_show);

	m_keyIndex.AddString(m_keyIndex_show);
	SetDlgItemText(IDC_KEYINDEX_COMBO, m_keyIndex_show);

	m_keyType.AddString(m_keyType_show);
	SetDlgItemText(IDC_KEYTYPE_COMBO,m_keyType_show);

	m_appType.AddString(_T("应用非对称密钥"));
	SetDlgItemText(IDC_APPTYPE_COMBO, _T("应用非对称密钥"));

	return TRUE;
}
BEGIN_MESSAGE_MAP(CSeeDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSeeDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSeeDetail::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSeeDetail 消息处理程序


void CSeeDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CSeeDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
