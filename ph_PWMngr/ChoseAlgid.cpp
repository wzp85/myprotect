// ChoseAlgid.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ChoseAlgid.h"
#include "afxdialogex.h"

#include "InitDevInfo.h"
#include "ph_km.h"
// CChoseAlgid �Ի���

IMPLEMENT_DYNAMIC(CChoseAlgid, CDialogEx)

CChoseAlgid::CChoseAlgid(void *key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CChoseAlgid::IDD, pParent)
	, m_title(_T(""))
	, m_algid_cs(_T(""))
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
    "����"));                 // lpszFacename
	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
}

CChoseAlgid::~CChoseAlgid()
{
}

void CChoseAlgid::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALGID_COMBO, m_chosedAlgId);
	DDX_Text(pDX, IDC_THEFIRSTLINE_STATIC, m_title);
	CWnd *cWnd = GetDlgItem(IDC_THEFIRSTLINE_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("��ѡ����Ҫ������Կ������Կ���㷨������������ɡ�");
	DDX_CBString(pDX, IDC_ALGID_COMBO, m_algid_cs);
}
BOOL CChoseAlgid::OnInitDialog()
{
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
  
    // TODO: Add extra initialization here   
    // Ϊ��Ͽ�ؼ����б������б��SM1��   
    m_chosedAlgId.AddString(_T("SM1"));   
    // Ϊ��Ͽ�ؼ����б������б��SSF33��   
    m_chosedAlgId.AddString(_T("SSF33"));   
   
   /* m_chosedAlgId.InsertString(1, _T("SMS4"));*/
	m_chosedAlgId.AddString(_T("SMS4"));   
  
    // Ĭ��ѡ���һ��  
    /*m_chosedAlgId.SetCurSel(0); */  
    // �༭����Ĭ����ʾ��һ������֡�SM1��   
    SetDlgItemText(IDC_ALGID_COMBO, _T("SM1"));   
 
    return TRUE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CChoseAlgid, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ALGID_COMBO, &CChoseAlgid::OnCbnSelchangeAlgidCombo)
	ON_BN_CLICKED(IDOK, &CChoseAlgid::OnBnClickedOk)
END_MESSAGE_MAP()


// CChoseAlgid ��Ϣ�������


void CChoseAlgid::OnCbnSelchangeAlgidCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;   
    int nSel;   
  
    // ��ȡ��Ͽ�ؼ����б����ѡ���������  
    nSel = m_chosedAlgId.GetCurSel();   
    // ����ѡ����������ȡ�����ַ���  
    m_chosedAlgId.GetLBText(nSel, strWeb);   
    // ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����  
    //SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb); 
//	MessageBox(_T("ѡ����㷨�ǣ�") + strWeb);
	m_algid_cs = strWeb;
	/*TraceMsg("ѡ����㷨�ǣ�"+strWeb);*/

}


void CChoseAlgid::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	this->OnOK();
	UpdateData(TRUE);
	int ret = 0;
	if(m_algid_cs == "SM1")
		m_algId = SGD_SM1_ECB;
	if(m_algid_cs == "SSF33")
		m_algId = SGD_SSF33_ECB;
	if(m_algid_cs == "SMS4")
		m_algId = SGD_SMS4_ECB;
	ret = Km_GenKeyProKey(phSHandle,m_algId);
	if(0 == ret)
	{
		CInitDevInfo initdevinfoDlg(key_phSHandle,phSHandle);
		initdevinfoDlg.DoModal();
	}
	else if(0 != ret)
	{
		char outGkpk[100]={0x00};
		retValueParse(ret,outGkpk);
		MessageBox("������Կ������Կʧ�ܣ�"+(CString)outGkpk,"��ʾ",MB_ICONEXCLAMATION);
	}
}
