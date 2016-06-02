// EncryptKeyGen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "EncryptKeyGen.h"
#include "afxdialogex.h"

#include "ph_km.h"
#define EK_UPDATA 888
// CEncryptKeyGen �Ի���

IMPLEMENT_DYNAMIC(CEncryptKeyGen, CDialogEx)

CEncryptKeyGen::CEncryptKeyGen(void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncryptKeyGen::IDD, pParent)
	, m_keyDiscription(_T(""))
	, m_algId(_T(""))
	, m_index_ek(_T(""))
{
	phHandle = handle;

	VERIFY(line1.CreateFont(
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
}

CEncryptKeyGen::CEncryptKeyGen(void *hSessionHandle,LPCTSTR keyIndex,LPCTSTR algId,CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncryptKeyGen::IDD, pParent)
	, m_keyDiscription(_T(""))
	, m_algId(_T(""))
	, m_index_ek(_T(""))
{
	phHandle = hSessionHandle;
	keyIndex_max_ek = _ttoi(keyIndex);
	//keyIndex_max_ek_lztocs = keyIndex;
	m_algId = algId;
}

CEncryptKeyGen::~CEncryptKeyGen()
{
}

void CEncryptKeyGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEY_DISCRIPTION_EDIT, m_keyDiscription);
	DDX_Control(pDX, IDC_THEALGID_COMBO, m_thealgId);
	DDX_Control(pDX, IDC_THEKEYINDEX_COMBO, m_theKeyIndex);
	DDX_Control(pDX, IDC_HEADLINE_STATIC, m_theline1);
	CWnd *cWnd = GetDlgItem(IDC_HEADLINE_STATIC);
	cWnd->SetFont(&line1);
	if(EK_UPDATA != index_array_ek[0][0])
		cWnd->SetWindowText("��Կ������Կ����");
	else if(EK_UPDATA == index_array_ek[0][0])
		cWnd->SetWindowText("��Կ������Կ����");
	DDX_CBString(pDX, IDC_THEALGID_COMBO, m_algId);
	DDX_CBString(pDX, IDC_THEKEYINDEX_COMBO, m_index_ek);
}

BOOL CEncryptKeyGen::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
	CDialogEx::OnInitDialog();
  
    // Add "About..." menu item to system menu.   
	if(EK_UPDATA == index_array_ek[0][0])
		this->SetWindowTextA("��Կ������Կ����");
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
	CWnd *cWnd = GetDlgItem(IDC_KEY_DISCRIPTION_EDIT);
	cWnd->SetFocus();

	int one = keyIndex_max_ek;
	CString cs_keyIndex;
	CString index;
	index.Format("%d",one);
	cs_keyIndex = "00"+index;//���ݵĸ�ʽ����������Ҫ��дһ���µķ��� 
	SetDlgItemText(IDC_THEKEYINDEX_COMBO,cs_keyIndex);

	if(EK_UPDATA == index_array_ek[0][0])
	{
		m_thealgId.AddString(m_algId);
		SetDlgItemText(IDC_ALGID_COMBO,m_algId); 
		m_theKeyIndex.AddString(cs_keyIndex);
		return TRUE;
	}

	int data = 0;
	for(int i=0;i<256;i++)
	{
		if(1 == index_array_ek[i][1])
		{
			data = index_array_ek[i][0];
			index.Format("%d",data);
			cs_keyIndex = "00"+index;
			m_theKeyIndex.AddString(cs_keyIndex);
		}
	}
	m_thealgId.AddString(_T("SSF33"));    
    m_thealgId.AddString(_T("SM4")); 
	m_thealgId.AddString(_T("SM1")); 
  
    SetDlgItemText(IDC_THEALGID_COMBO, _T("SM1"));   

    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CEncryptKeyGen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEncryptKeyGen::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CEncryptKeyGen::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_THEALGID_COMBO, &CEncryptKeyGen::OnCbnSelchangeThealgidCombo)
	ON_BN_CLICKED(IDCANCEL, &CEncryptKeyGen::OnBnClickedCancel)
END_MESSAGE_MAP()


// CEncryptKeyGen ��Ϣ�������


void CEncryptKeyGen::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("������"));
}


void CEncryptKeyGen::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	if(m_keyDiscription.IsEmpty())
	{
		MessageBox("��Կ��������Ϊ�գ�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(m_keyDiscription.GetLength()>20)
	{
		MessageBox("��Կ�������Ȳ��ܳ���20���ֽڣ�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	int ret = 0;
	void * hSessionHandle = phHandle;

	if(EK_UPDATA == index_array_ek[0][0])
	{
		ret = Km_KeyEncDestroy(hSessionHandle,uig_ek.index_num,&uig_ek.index);
		if(0 != ret)
		{
			char outKed[100]={0x00};
			retValueParse(ret,outKed);
			CString index_uig_num_cs;
			index_uig_num_cs.Format("%d",uig_ek.index);
			MessageBox("���ٵ�"+index_uig_num_cs+ "����Կ������Կʧ�ܣ�"+(CString)outKed,"��ʾ");
			return;
		}
	}

	unsigned int uikeyLabel = _ttoi(m_index_ek);//��Կ����
	unsigned int uiAlgo;
	if("SSF33" == m_algId)
		uiAlgo = SGD_SSF33_ECB;
	else if("SM4" == m_algId)
		uiAlgo = SGD_SMS4_ECB;
	else if("SM1" == m_algId)
		uiAlgo = SGD_SM1_ECB;
	unsigned char pucEncKeyName[64]={0};
	unsigned int uiEncKeyNameLength;
	uiEncKeyNameLength = m_keyDiscription.GetLength();
	memcpy(pucEncKeyName,m_keyDiscription.GetBuffer(),uiEncKeyNameLength);
	ret = Km_GenKeyEncKey(hSessionHandle,uikeyLabel,uiAlgo,pucEncKeyName,uiEncKeyNameLength);
	if(0 == ret && EK_UPDATA != index_array_ek[0][0])
	{
		//MessageBox(_T("��ӳɹ�"),"");
		//return;
	}
	else if(0 != ret && EK_UPDATA != index_array_ek[0][0])
	{
		MessageBox("���ʧ��","");
		this->OnOK();
		return;
	}
	else if(0 != ret && EK_UPDATA == index_array_ek[0][0])
	{
		char outGkek[100]={0x00};
		retValueParse(ret,outGkek);
		CString index_uig_num_cs_g;
		index_uig_num_cs_g.Format("%d",uig_ek.index);
		MessageBox("�������ɵ�"+index_uig_num_cs_g+ "����Կ������Կʧ�ܣ�"+(CString)outGkek,"��ʾ");
		this->OnOK();
		return;
	}
	CDialogEx::OnOK();
}


void CEncryptKeyGen::OnCbnSelchangeThealgidCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strWeb;   
    int nSel;     
	// ��ȡ��Ͽ�ؼ����б����ѡ���������  
    nSel = m_thealgId.GetCurSel();   
    // ����ѡ����������ȡ�����ַ���  
    m_thealgId.GetLBText(nSel, strWeb);   
    // ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����  
    //SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);  
//	MessageBox(_T("ѡ����㷨�ǣ�"+strWeb));
}


void CEncryptKeyGen::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
