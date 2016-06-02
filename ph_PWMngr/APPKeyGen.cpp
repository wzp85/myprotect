// APPKeyGen.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "APPKeyGen.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
#include "APPKeyMngr.h"
#define APPKEY_UPDATA   0x09
// CAPPKeyGen 对话框
int isUp = -1;
IMPLEMENT_DYNAMIC(CAPPKeyGen, CDialogEx)

CAPPKeyGen::CAPPKeyGen(BOOL isUpdate,void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPKeyGen::IDD, pParent)
{
	phHandle = handle;

	if(isUpdate)
		isUp = 1;
	else 
		isUp = 0;
	//pWnd = hwnd;
//	listctrl_appGen = m_listCtrlAppkey;
}
CAPPKeyGen::CAPPKeyGen(BOOL isUpdate,void *hSessionHandle,LPCTSTR keyIndex,LPCTSTR appName,LPCTSTR algId,LPCTSTR keyType,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPKeyGen::IDD, pParent)
	, m_appName(_T(""))
	, m_algid_cs(_T(""))
	, m_keyindex(_T(""))
	, m_keyType_cs(_T(""))
	, m_keyPin(_T(""))
	, m_keyPinCon(_T(""))
{
	phHandle = hSessionHandle;
	keyIndex_max = _ttoi(keyIndex);
	m_algid_cs = algId;
	m_keyType_cs = keyType;

	if(isUpdate)
		isUp = 1;//1表示该cpp做更新显示、完成更新功能
	else 
		isUp = 0;//0表示该cpp做生成显示、完成生成功能
}

CAPPKeyGen::~CAPPKeyGen()
{
}

void CAPPKeyGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALGID_COMBO, m_algId);
	DDX_Control(pDX, IDC_KEYINDEX_COMBO, m_keyIndex);
	DDX_Control(pDX, IDC_APPTYPE_COMBO, m_appType);
	DDX_Control(pDX, IDC_KEYTYPE_COMBO, m_keyType);
	DDX_Text(pDX, IDC_APPNAME_EDIT, m_appName);
	DDX_CBString(pDX, IDC_ALGID_COMBO, m_algid_cs);
	DDX_CBString(pDX, IDC_KEYINDEX_COMBO, m_keyindex);
	DDX_CBString(pDX, IDC_KEYTYPE_COMBO, m_keyType_cs);
	DDX_Text(pDX, IDC_KEYPIN_EDIT, m_keyPin);
	DDX_Text(pDX, IDC_KEYPINCON_EDIT, m_keyPinCon);
}

BOOL CAPPKeyGen::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
	CDialogEx::OnInitDialog();
  
    // Add "About..." menu item to system menu. 
	if(isUp)
	{
		this->SetWindowText("应用密钥更新");
		SetDlgItemText(IDC_HEADLINE_STATIC,"应用密钥更新");
	}
 
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
	CWnd *cWnd = GetDlgItem(IDC_APPNAME_EDIT);
	cWnd->SetFocus();

	int one = keyIndex_max;
	CString cs_keyIndex;
	CString index;
	index.Format("%d",one);
	cs_keyIndex = "00"+index;//数据的格式化操作，需要再写一个新的方法 
	SetDlgItemText(IDC_KEYINDEX_COMBO,cs_keyIndex);

	if(APPKEY_UPDATA == index_array[0][0])
	{
		m_algId.AddString(m_algid_cs);
		SetDlgItemText(IDC_ALGID_COMBO,m_algid_cs); 
		m_appType.AddString(_T("应用非对称密钥"));
		SetDlgItemText(IDC_APPTYPE_COMBO, _T("应用非对称密钥"));
		m_keyType.AddString(_T("签名密钥"));
		m_keyType.AddString(_T("加密密钥"));
		m_keyType.AddString(_T("签名、加密共用密钥"));
		m_keyType.AddString(_T("签名、加密不共用密钥"));
		SetDlgItemText(IDC_KEYTYPE_COMBO,m_keyType_cs);
		return TRUE;
	}
	int data = 0;
	for(int i=0;i<256;i++)
	{
		if(1 == index_array[i][1])
		{
			data = index_array[i][0];
			index.Format("%d",data);
			cs_keyIndex = "00"+index;
			m_keyIndex.AddString(cs_keyIndex);
		}
	}

	m_algId.AddString(_T("RSA 1024"));   
    // 为组合框控件的列表框添加列表项“RSA 2048”   
    m_algId.AddString(_T("RSA 2048")); 
	m_algId.AddString(_T("SM2"));

    // 编辑框中默认显示第一项的文字“RSA 1024”   
    SetDlgItemText(IDC_ALGID_COMBO, _T("SM2"));  

	m_appType.AddString(_T("应用非对称密钥"));

	//m_backupCatge.AddString(_T(""));
	SetDlgItemText(IDC_APPTYPE_COMBO, _T("应用非对称密钥"));

	m_keyType.AddString(_T("签名密钥"));
	m_keyType.AddString(_T("加密密钥"));
	m_keyType.AddString(_T("签名、加密共用密钥"));
	m_keyType.AddString(_T("签名、加密不共用密钥"));

	SetDlgItemText(IDC_KEYTYPE_COMBO, _T("签名、加密共用密钥"));

    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CAPPKeyGen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAPPKeyGen::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CAPPKeyGen::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_ALGID_COMBO, &CAPPKeyGen::OnCbnSelchangeAlgidCombo)
	ON_BN_CLICKED(IDOK, &CAPPKeyGen::OnBnClickedOk)
END_MESSAGE_MAP()


// CAPPKeyGen 消息处理程序


void CAPPKeyGen::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("已生成！"));
}


void CAPPKeyGen::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CAPPKeyGen::OnCbnSelchangeAlgidCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWeb;   
    int nSel;     
	// 获取组合框控件的列表框中选中项的索引  
    nSel = m_algId.GetCurSel();   
    // 根据选中项索引获取该项字符串  
    m_algId.GetLBText(nSel, strWeb);   
    // 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中  
    //SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);  
//	MessageBox(_T("选择的算法是："+strWeb));
}


void CAPPKeyGen::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);

	isReallyUpdated = 1;

	if(m_appName.IsEmpty())
	{
		MessageBox("应用名称不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_appName.GetLength() > 20)
	{
		MessageBox("应用名称长度不能大于20！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_keyPin.GetLength()<8)
	{
		MessageBox("PIN码长度不能小于8位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_keyPin != m_keyPinCon)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_keyPin))
	{
		MessageBox("PIN码不能全是数字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	void * hSessionHandle = phHandle;

	//ret = Km_AppKeyDestroy(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	if(isUp)
	{
		ret = Km_AppKeyDestroy(hSessionHandle,0,uig.index_uig,&uig.index_uig_num);
		if(0 != ret)
		{
			char outApkd[100]={0x00};
			retValueParse(ret,outApkd);
			CString index_uig_num_cs;
			index_uig_num_cs.Format("%d",uig.index_uig_num);
			MessageBox("销毁第"+index_uig_num_cs+ "号应用密钥失败！错误码："+(CString)outApkd,"提示");
			return;
		}
	}

	unsigned int uikeyIndex = _ttoi(m_keyindex);
	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	if(m_algid_cs == "RSA 1024")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 1024;
	}
	if(m_algid_cs == "RSA 2048")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 2048;
	}
	if(m_algid_cs == "SM2")
	{
		uiAlgo = SGD_SM2_1;
		uiKeyLength = 256; 
	}
	unsigned char pucKeyPasswd[32]={0x00};
	memcpy(pucKeyPasswd,m_keyPin,m_keyPin.GetLength());
	unsigned int uiKeyPasswdLength = m_keyPin.GetLength();
	unsigned char pucAppName[32]={0x00};
	memcpy(pucAppName,m_appName,m_appName.GetLength());
	unsigned int uiAppNameLength = m_appName.GetLength();
	unsigned int uiKeyType;
	if(m_keyType_cs == "签名、加密共用密钥")
		uiKeyType = 2;
	if(m_keyType_cs == "签名、加密不共用密钥")
		uiKeyType = 3;
	if(m_keyType_cs == "签名密钥")
		uiKeyType = 0;
	if(m_keyType_cs == "加密密钥")
		uiKeyType = 1;
	ret = Km_GenAppKey(hSessionHandle,uikeyIndex,uiAlgo,uiKeyLength,pucKeyPasswd,uiKeyPasswdLength,pucAppName,uiAppNameLength,uiKeyType);
	if(0 == ret && 0 == isUp)
	{
		CDialogEx::OnOK();
		MessageBox("    添加成功","提示");
	}
	else if(0 != ret && 0 == isUp)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		CDialogEx::OnOK();
		MessageBox("    添加失败"+(CString)outGapk,"提示");
	}
	else if(0 == ret && 0 != isUp)
		this->OnOK();
}

void CAPPKeyGen::GetisReallyUpdated(int *x)
{
	*x = isReallyUpdated;
}
