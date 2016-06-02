// DevkeyBACKUP.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevkeyBACKUP.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "DevKeyFirResume.h"
#include "ChoseFilePath.h"
#include "ph_km.h"
#include "KeyDevide.h"
#include "MyUtil.h"
// CDevkeyBACKUP 对话框

IMPLEMENT_DYNAMIC(CDevkeyBACKUP, CPropertyPage)

CDevkeyBACKUP::CDevkeyBACKUP()
	: CPropertyPage(CDevkeyBACKUP::IDD)
	, m_devName(_T(""))
	, m_isBackup_int(_T(""))
	, m_algId_int(_T(""))
	, m_modifyTime(_T(""))
{
	//m_devName = devName;
}

CDevkeyBACKUP::~CDevkeyBACKUP()
{
}

void CDevkeyBACKUP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DEVNAME_EDIT, m_devName);
	DDX_Control(pDX, IDC_ISBACKUP_COMBO, m_isBackup);
	DDX_Control(pDX, IDC_BACKUPCATGE_COMBO, m_backupCatge);
	DDX_Control(pDX, IDC_ALGID_COMBO, m_algId);
	DDX_CBString(pDX, IDC_ISBACKUP_COMBO, m_isBackup_int);
	DDX_CBString(pDX, IDC_ALGID_COMBO, m_algId_int);
	DDX_Text(pDX, IDC_FINALTIME_EDIT, m_modifyTime);
}

BOOL CDevkeyBACKUP::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
	CPropertyPage::OnInitDialog();
  
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
	CDevkeyBACKUP::ShowDevInfo();

    return TRUE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CDevkeyBACKUP, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CDevkeyBACKUP::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDevkeyBACKUP::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDevkeyBACKUP 消息处理程序
BOOL CDevkeyBACKUP::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CDevkeyBACKUP::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码-----------------点击备份按钮
	CDevKeyFirBac devKeyFirBacDlg1(1,_T("请插入第一份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg1.DoModal())
		return;

	unsigned int B64KeyLen1=0;
	unsigned char B64Key1[256]={0x00};

	Km_SymmCrypt(phHandle_dev,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_dev,0,257);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_dev);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("请插入第二份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;
	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle_dev,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_dev,0,257);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_dev);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("请插入第三份密钥备份密钥"));
	if(devKeyFirBacDlg3.DoModal() == IDOK)
	{
		unsigned char key_in[32]={0x00};
		devKeyFirBacDlg3.GetRandomInKey(key_in);//得到key中的用于判断备份文件与备份密钥是否匹配的随机数

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle_dev,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_dev,0,257);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_dev);

		int ret = 0;
		unsigned char sysKey_for_in[257]={0};
		unsigned int sysKey_for_in_len = 0;
		ret = KeyMerge(sys_Key_1_dev,len_1,sys_Key_2_dev,len_2,sys_Key_3_dev,len_3,sysKey_for_in,&sysKey_for_in_len);
//		char *path="C:\\key_after_merge_dev.txt";
//		CMyUtil::Write2File(path,sysKey_for_in,sysKey_for_in_len);
		if(0 != ret || 16 != sysKey_for_in_len)
		{
			MessageBox("密钥合并出错！","提示");
			return;
		}
		CChoseFilePath choseFilePathDlg(key_in,m_devName,sysKey_for_in,0,NULL,DEV_BACKUP,phHandle_dev);
		choseFilePathDlg.DoModal();
	}
	CDevkeyBACKUP::ShowDevInfo();
}


void CDevkeyBACKUP::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码---------------------------点击恢复按钮
	/*CDevKeyFirResume devKeyFirResumeDlg(phHandle_dev);
	devKeyFirResumeDlg.DoModal();*/
}

void CDevkeyBACKUP::ShowDevInfo()
{
	int ret = 0;
	void * hSessionHandle = phHandle_dev;
	DEVKEYINFO pDevKeyInfo={0};
	ret = Km_GetDevKeyInfo(hSessionHandle,&pDevKeyInfo);
	if(ret)
	{
		char outGdki[100]={0x00};
		retValueParse(ret,outGdki);
		MessageBox(outGdki);
	}

	m_devName = pDevKeyInfo.ucDevName;
	SetDlgItemText(IDC_DEVNAME_EDIT,m_devName);
   
	if(1 == pDevKeyInfo.uiIfBak)
		m_isBackup_int = "已备份";
	else if(0 == pDevKeyInfo.uiIfBak)
		m_isBackup_int = "未备份";
    SetDlgItemText(IDC_ISBACKUP_COMBO,m_isBackup_int);   

	if(65536 == pDevKeyInfo.uiAlgo && 1024 == pDevKeyInfo.uiKeyLen)
		m_algId_int ="RSA 1024";
	else if(65536 == pDevKeyInfo.uiAlgo && 2048 == pDevKeyInfo.uiKeyLen)
		m_algId_int ="RSA 2048";
	else if(SGD_SM2_1 == pDevKeyInfo.uiAlgo || SGD_SM2_2 == pDevKeyInfo.uiAlgo || SGD_SM2_3 == pDevKeyInfo.uiAlgo)
	{
		m_algId_int ="SM2";
	}
	SetDlgItemText(IDC_ALGID_COMBO,m_algId_int);

	SetDlgItemText(IDC_BACKUPCATGE_COMBO,"五选三");

	m_modifyTime = pDevKeyInfo.ucBakTime;
	SetDlgItemText(IDC_FINALTIME_EDIT,m_modifyTime);
}



BOOL CDevkeyBACKUP::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();   
    //设置属性表只有“完成”按钮  
    psheet->SetFinishText(_T("完成")); 

	return CPropertyPage::OnSetActive();
}
