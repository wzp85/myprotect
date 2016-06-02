// TIPFormat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "TIPFormat.h"
#include "afxdialogex.h"


// CTIPFormat �Ի���

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
    "����"));                 // lpszFacename
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
	cWnd->SetWindowText("�����������Կ������Կkey����ȷ���Ƿ�Ҫ��ʽ���������ʽ��������key���ݹ�����Կ���޷��ָ���");
}

BOOL CTIPFormat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//m_font.CreatePointFont(130,_T("����"));
	//m_brush.CreateSolidBrush(RGB(0,0,0));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CTIPFormat, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTIPFormat ��Ϣ�������
HBRUSH CTIPFormat::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_myStatic.m_hWnd == pWnd->m_hWnd)
	{
	   //pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //���ؿջ�ˢ����һ����ȥ������ɫ��
		//return m_brush;
	}
	return hbr;
}