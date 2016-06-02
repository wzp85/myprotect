// DevInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevInfo.h"
#include "afxdialogex.h"

#include "ph_km.h"
// CDevInfo 对话框

IMPLEMENT_DYNAMIC(CDevInfo, CPropertyPage)

CDevInfo::CDevInfo()
	: CPropertyPage(CDevInfo::IDD)
	, m_devMactuName(_T(""))
	, m_devName(_T(""))
	, m_devSerial(_T(""))
	, m_devVersion(_T(""))
	, m_symmAlgid(_T(""))
	, m_asymmAlgid(_T(""))
	, m_hashAlgid(_T(""))
	, m_maxSize(_T(""))
	, m_stdVersion(_T(""))
{

}

BOOL CDevInfo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

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
	int ret = 0;
	void * hSessionHandle = phHandle;
	DEVICEINFO DevInfo={0x00};
	ret = Km_GetDeviceInfo(hSessionHandle,&DevInfo);
	if(ret)
	{
		char outGdi[100]={0x00};
		retValueParse(ret,outGdi);
		MessageBox(outGdi);
		return TRUE;
	}

	SetDlgItemText(IDC_MACTUNAME_EDIT,(LPCTSTR)DevInfo.IssuerName);   
	SetDlgItemText(IDC_DEVNAME_EDIT,(LPCTSTR)DevInfo.DeviceName);
	
	char serial[20]={0x00};
	memcpy(serial,DevInfo.DeviceSerial,16);

//	SetDlgItemText(IDC_DEVSERIAL_EDIT,(LPCTSTR)DevInfo.DeviceSerial);
	SetDlgItemText(IDC_DEVSERIAL_EDIT,(LPCTSTR)serial);

	CString devInfo_version;
	devInfo_version.Format("%ld",DevInfo.DeviceVersion);
	SetDlgItemText(IDC_DEVVERSION_EDIT,devInfo_version); 

	unsigned int algId[35]={SGD_3DES_ECB,SGD_3DES_CBC,SGD_3DES_CFB,SGD_3DES_OFB,SGD_3DES_MAC,SGD_SM1_ECB,SGD_SM1_CBC,SGD_SM1_CFB,SGD_SM1_OFB,SGD_SM1_MAC
		,SGD_SSF33_ECB,SGD_SSF33_CBC,SGD_SSF33_CFB,SGD_SSF33_OFB,SGD_SSF33_MAC,SGD_SMS4_ECB,SGD_SMS4_CBC,SGD_SMS4_CFB,SGD_SMS4_OFB,SGD_SMS4_MAC
		,SGD_RC2_ECB,SGD_RC2_CBC,SGD_RC2_CFB,SGD_RC2_OFB,SGD_RC2_MAC,SGD_RC4_ECB,SGD_RC4_CBC,SGD_RC4_CFB,SGD_RC4_OFB,SGD_RC4_MAC,SGD_AES_ECB,
		SGD_AES_CBC,SGD_AES_CFB,SGD_AES_OFB,SGD_AES_MAC};
	CString algId_ch[35]={"3DES、","3DES、","3DES、","3DES、","3DES、","SM1、","SM1、","SM1、","SM1、","SM1、","SSF33、","SSF33、"
		,"SSF33、","SSF33、","SSF33、","SM4、","SM4、","SM4、","SM4、","SM4、","RC2、","RC2、","RC2、","RC2、","RC2、","RC4、","RC4、"
		,"RC4、","RC4、","RC4、","AES、","AES、","AES、","AES、","AES、"};

	//获取对称算法标识
	CString devInfo_symmalg;
	CString alg;
	for(int i = 0;i < 35;i++)
	{
		if(algId[i] == (DevInfo.SymAlgAbility & algId[i]))
		{
			alg.Format("%ld",algId[i]);
			if(i == 0)
				devInfo_symmalg += algId_ch[i];
			else if(i > 0)
			{
				if(algId_ch[i] != algId_ch[i-1])
					devInfo_symmalg += algId_ch[i];
			}
		}
	}
	BYTE symm_SHOW[512]={0x00};
	memcpy(symm_SHOW,devInfo_symmalg.GetBuffer(),devInfo_symmalg.GetLength()-2);
	SetDlgItemText(IDC_SYMMALG_EDIT,(LPCTSTR)symm_SHOW);

	//获取非对称算法标识
	unsigned int algId_as[4]={SGD_RSA,SGD_SM2_1,SGD_SM2_2,SGD_SM2_3};
	CString algId_cs[4] = {"RSA、","SM2、","SM2、","SM2、"};
	CString devInfo_asymmalg,devInfo_asymmalg_1,devInfo_asymmalg_2;
	for(int i = 0;i < 4;i++)
	{
		if(algId_as[i] == (DevInfo.AsymAlgAbility[0] & algId_as[i]))
		{
			alg.Format("%ld",algId_as[i]);
			if(i == 0)
				devInfo_asymmalg_1 += algId_cs[i];
			else if(i > 0)
			{
				if(algId_cs[i] != algId_cs[i-1])
					devInfo_asymmalg_1 += algId_cs[i];
			}
		}
	}
	for(int i = 0;i < 4;i++)
	{
		if(algId_as[i] == (DevInfo.AsymAlgAbility[1] & algId_as[i]))
		{
			alg.Format("%ld",algId_as[i]);
			if(-1 != devInfo_asymmalg_1.Find(algId_cs[i]))
				break;
			if(i == 0)
			{
				devInfo_asymmalg_2 += algId_cs[i];
			}
			else if(i > 0)
			{
				if(algId_ch[i] != algId_cs[i-1])
					devInfo_asymmalg_2 += algId_cs[i];
			}
		}
	}
	devInfo_asymmalg = devInfo_asymmalg_1 + devInfo_asymmalg_2;
	BYTE asym_SHOW[512]={0x00};
	memcpy(asym_SHOW,devInfo_asymmalg.GetBuffer(),devInfo_asymmalg.GetLength()-2);
	SetDlgItemText(IDC_ASYMMALG_EDIT,(LPCTSTR)asym_SHOW);

	//获取哈希标识
	CString devInfo_hashalg; 
	unsigned int alg_hash[4]={SGD_SM3,SGD_SHA1,SGD_SHA256,SGD_MD5};
	CString alg_hash_cs[4]={"SM3、","SHA1、","SHA256、","MD5"};
	for(int i = 0;i < 4;i++)
	{
		if(alg_hash[i] == (DevInfo.HashAlgAbility & alg_hash[i]))
		{
			alg.Format("%ld",alg_hash[i]);
			devInfo_hashalg += alg_hash_cs[i];
		}
	}
	SetDlgItemText(IDC_HASHALG_EDIT,devInfo_hashalg);   

	CString devInfo_buffersize;
	unsigned int bufferSize = (DevInfo.BufferSize)/1024/1024;
	devInfo_buffersize.Format("%ld",bufferSize);
	SetDlgItemText(IDC_MAXSIZE_EDIT,devInfo_buffersize+"M");

	CString devInfo_stdversion;
	devInfo_stdversion.Format("%ld",DevInfo.StandardVersion);
	SetDlgItemText(IDC_STDVERSION_EDIT,devInfo_stdversion);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

CDevInfo::~CDevInfo()
{
}

void CDevInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MACTUNAME_EDIT, m_devMactuName);
	DDX_Text(pDX, IDC_DEVNAME_EDIT, m_devName);
	DDX_Text(pDX, IDC_DEVSERIAL_EDIT, m_devSerial);
	DDX_Text(pDX, IDC_DEVVERSION_EDIT, m_devVersion);
	DDX_Text(pDX, IDC_SYMMALG_EDIT, m_symmAlgid);
	DDX_Text(pDX, IDC_ASYMMALG_EDIT, m_asymmAlgid);
	DDX_Text(pDX, IDC_HASHALG_EDIT, m_hashAlgid);
	DDX_Text(pDX, IDC_MAXSIZE_EDIT, m_maxSize);
	DDX_Text(pDX, IDC_STDVERSION_EDIT, m_stdVersion);
}


BEGIN_MESSAGE_MAP(CDevInfo, CPropertyPage)
	
END_MESSAGE_MAP()


// CDevInfo 消息处理程序
BOOL CDevInfo::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

