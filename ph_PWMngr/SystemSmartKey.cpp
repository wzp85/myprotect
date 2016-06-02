// SystemSmartKey.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SystemSmartKey.h"
#include "afxdialogex.h"

//#include "ChoseAlgid.h"
#include "ChangeInitPin.h"
#include "IsInit.h"
#include "ChoseAlgid.h"
#include "ph_PWMngrDlg.h"
#include "SignPWMAdmin.h"
#include "InitDevInfo.h"
#define PWMMNGR_CAPTION  "上海普华密码机管理系统 Version 2.0"

//#include "DAI.h"
#include "KeyDAO.h"
#include "MyUtil.h"
#include "string.h"

#include "ph_km.h"
#include "autonk.h"
BYTE config_IPtext_init[10][32]={0x00};
int ip_Count_init = 0;
// CSystemSmartKey 对话框

IMPLEMENT_DYNAMIC(CSystemSmartKey, CDialogEx)

CSystemSmartKey::CSystemSmartKey(int isResig,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSmartKey::IDD, pParent)
	/*, m_line1(_T(""))
	, m_usrName(_T(""))*/
	, m_usrPwd(_T(""))
	, m_sUserName(_T(""))
	, m_sMngrIp(_T(""))
{
	isReSig = isResig;

	VERIFY(font.CreateFont(
    14,                        // nHeight
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
}

CSystemSmartKey::~CSystemSmartKey()
{
}

void CSystemSmartKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_FIRSTLINE_STATIC, m_line1);
	CWnd *cWnd = GetDlgItem(IDC_FIRSTLINE_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowTextW(L"请插入系统智能密码钥匙，并点击确定！");*/
	/*DDX_Text(pDX, IDC_EDIT1, m_usrName);*/
	DDX_Control(pDX, IDC_USRNAME_COMBO, m_usrName);
	DDX_Control(pDX, IDC_MNGRIP_COMBO, m_mngrIP);
	DDX_Text(pDX, IDC_USRPWD_EDIT, m_usrPwd);
	DDX_CBString(pDX, IDC_USRNAME_COMBO, m_sUserName);
	DDX_CBString(pDX, IDC_MNGRIP_COMBO, m_sMngrIp);
}

BOOL CSystemSmartKey::OnInitDialog()
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
	CWnd *cWnd = GetDlgItem(IDC_USRPWD_EDIT);
	cWnd->SetFocus();

	memset(ip,0x00,32);
	//读文件！
	char *fileName="config.txt";
	int length=0;
	BYTE *data = NULL;
	CMyUtil::ReadData(fileName,data,&length);
	data = new BYTE[length];
	CMyUtil::ReadData(fileName,data,&length);

	char * pBeign=(char *)data;
	char usrNameBuf[32]={0x00};

	for(int i=0;i<10;i++)//读配置文件里的用户名，并确定root为用户名显示在combox控件上
	{
		memset(usrNameBuf,0x00,32);
		char *str1 = strstr(pBeign,"USERNAME=");
		if(str1==NULL)
			break;
		char *str2 = strstr(pBeign,"\n");
		if(str2==NULL)
			break;

		char *begin=str1+sizeof("USERNAME=")-1;
		memcpy(usrNameBuf,begin,str2-str1-sizeof("USERNAME")-1);

	//	m_usrName.AddString((CString)usrNameBuf);  
		m_usrName.AddString(CString(usrNameBuf)); 
		if(0 == strcmp(usrNameBuf,"root"))
		{
			SetDlgItemText(IDC_USRNAME_COMBO,"root");   
		}
		pBeign=str2+1;
	}

	char *pIP = (char *)data;
	char *str = strstr(pIP,"IP=");
	char *start,*end;
	int ipBufLength=0;
	start = str + sizeof("IP=") - 1;
	char ipBuf[32]={0x00};
	

	for(int i=0;i<10;i++)//将配置文件里的ip地址读出来在combox里全部显示
	{
		memset(ipBuf,0x00,32);

		end=strstr(start,"|");
		if(end==NULL)
			break;
		ipBufLength=end-start;
		memcpy(ipBuf,start,ipBufLength);
		start=end+strlen("|");
		
		memcpy(config_IPtext_init[i],ipBuf,strlen(ipBuf));
		m_mngrIP.AddString(CString(ipBuf));
		ip_Count_init++;
	}
 
	delete data;
    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CSystemSmartKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSystemSmartKey::OnBnClickedOk)
	ON_STN_CLICKED(IDC_CHANGE_INITPIN_STATIC, &CSystemSmartKey::OnClickedChangeInitpinStatic)
	/*ON_STN_ENABLE(IDC_CHANGE_INITPIN_STATIC, &CSystemSmartKey::OnEnableChangeInitpinStatic)*/
	//ON_CBN_SELCHANGE(IDC_USRNAME_COMBO, &CSystemSmartKey::OnCbnSelchangeUsrnameCombo)
	//ON_CBN_EDITCHANGE(IDC_USRNAME_COMBO, &CSystemSmartKey::OnCbnEditchangeUsrnameCombo)
END_MESSAGE_MAP()


// CSystemSmartKey 消息处理程序

void CSystemSmartKey::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CDialogEx::OnOK();*/
	
	UpdateData(TRUE);

	if(m_sUserName.IsEmpty())
	{
		MessageBox("用户名不能为空","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrPwd.IsEmpty())
	{
		MessageBox("请输入口令","",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_sMngrIp.IsEmpty())
	{
		MessageBox("请输入IP地址","",MB_ICONWARNING | MB_OK);
		return;
	}

	BYTE *pbData = NULL;
	int ulDataLen = m_usrPwd.GetLength();
	pbData = new BYTE[ulDataLen];
	int ret = 0;

	CKeyDao keyDao;

	void *hSessionHandle = NULL;
	unsigned int uiNameLength;
	unsigned int uiPasswdHashLength;
	unsigned int status = 0;
	
	uiNameLength = m_sUserName.GetLength();
	unsigned char ucName[32] = {0x00};
	memcpy(ucName,m_sUserName.GetBuffer(),uiNameLength);

	int ip_leng = m_sMngrIp.GetLength();
	char uiIP[32] = {0x00};
	memcpy(uiIP,m_sMngrIp.GetBuffer(),ip_leng);
	memcpy(ip,m_sMngrIp.GetBuffer(),ip_leng);

	uiPasswdHashLength = m_usrPwd.GetLength();
	unsigned char ucPasswdHash[32] = {0x00};
	memcpy(ucPasswdHash,m_usrPwd.GetBuffer(),uiPasswdHashLength);

	ret = Km_CheckInitPasswd(&hSessionHandle,uiIP,ucName,uiNameLength,ucPasswdHash,uiPasswdHashLength,&status);

	if(0 != ret)
	{
		char outCip[100]={0x00};
		retValueParse(ret,outCip);
		MessageBox(outCip,"登录失败",MB_ICONEXCLAMATION|MB_OK);
		return ;
	}
	if(status==0 && 0 == isReSig )//为0表示正常初始化
	{
		BOOL isWriteOK = TRUE;
		for(int i = 0;i < 10;i++)
		{
			if(!strcmp(m_sMngrIp,(const char*)config_IPtext_init[i]))
				isWriteOK = FALSE;
		}
		if(isWriteOK && ip_Count_init<10)
		{
			char *filePath = "config.txt";
			CString ip = m_sMngrIp+"|";
			CMyUtil::Write2FileAppend(filePath,(unsigned char*)ip.GetBuffer(),ip.GetLength());
		}
		INT_PTR nRes;   
		/*MessageBox("系统未初始化","提示");*/
		nRes = MessageBox(_T("请点击“确定”生成主密钥"),_T("提示"),MB_OKCANCEL | MB_ICONWARNING);
		if(IDOK != nRes)
			return;
		this->OnOK();
		//----------------调用生成主密钥接口------------------------//
		int ret = 0;
		ret = Km_GenMainKey(hSessionHandle);
		if(!ret)
		{
			CChoseAlgid choseAlgidDlg(NULL,hSessionHandle);
			choseAlgidDlg.DoModal();
		}
		else
		{
			MessageBox("生成主密钥失败");
			return;
		}
	}
	else if(status != 0 && 0 == isReSig)
	{
		/*MessageBox("系统已初始化","系统已初始化");*/
		//新输入的IP地址若配置文件中没有则写入文件
		BOOL isWriteOK = TRUE;
		for(int i = 0;i < 10;i++)
		{
			if(!strcmp(m_sMngrIp,(const char*)config_IPtext_init[i]))
				isWriteOK = FALSE;
		}
		if(isWriteOK && ip_Count_init<10)
		{
			char *filePath = "config.txt";
			CString ip = m_sMngrIp+"|";
			CMyUtil::Write2FileAppend(filePath,(unsigned char*)ip.GetBuffer(),ip.GetLength());
		}
		this->OnOK();
		CIsInit isInitDlg(NULL,hSessionHandle);
		isInitDlg.DoModal();
	}
	else if(0 == ret && 1 == isReSig)//为1表示重新初始化,若口令验证成功，则跳到签发管理员界面
	{
		this->OnOK();
		INT_PTR nRes = 0;
		CSignPWMAdmin signPWMAdminDlg(0,0,0,1,0,1,NULL,NULL,hSessionHandle);
		nRes = signPWMAdminDlg.DoModal();
		if(IDOK != nRes)
			return;
		int adm_Count;
		int sigState = 0;
		signPWMAdminDlg.GetMaxAdminNum(&adm_Count);
		signPWMAdminDlg.GetTwoSigState(&sigState);
		if(sigState == 2)
		{
			CInitDevInfo initDevInfoDlg(NULL,hSessionHandle);
			initDevInfoDlg.DoModal();
			return;
		}
		if(1 < adm_Count)
		{
			int adm_Count_forset = adm_Count; 
			int i = 1;
			int state = 0;
			CString i_Count_dlg;
			while(1 < adm_Count && state == 0)
			{
				state = 0;
				i++;
				i_Count_dlg.Format("%d",i);
				CSignPWMAdmin signPWMAdminDlg(0,0,0,0,0,i,"签发第"+i_Count_dlg+"个设备管理员",NULL,hSessionHandle);
				signPWMAdminDlg.admin_count = adm_Count_forset;//设置只读属性框的最大管理员数
				signPWMAdminDlg.isReadOnly = TRUE;
				if(IDOK != signPWMAdminDlg.DoModal())
					break;
				
				signPWMAdminDlg.GetTwoSigState(&state);
				adm_Count--;
			}
			if(1 == state)
			{
				CIsInit isInitDlg(NULL,hSessionHandle);
				isInitDlg.DoModal();
				return;
			}
			Cph_PWMngrDlg ph_PWMMngrDlg( m_sMngrIp,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
			ph_PWMMngrDlg.uiKeyLen = 0;
			ph_PWMMngrDlg.DoModal();
		}
	}
}


void CSystemSmartKey::OnClickedChangeInitpinStatic()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	//if(m_sUserName.IsEmpty())
	//{
	//	MessageBox("用户名不能为空","",MB_ICONWARNING | MB_OK);
	//	return;
	//}
	//if(m_usrPwd.IsEmpty())
	//{
	//	MessageBox("请输入口令","",MB_ICONWARNING | MB_OK);
	//	return;
	//}
	if(m_sMngrIp.IsEmpty())
	{
		MessageBox("请输入IP地址","",MB_ICONWARNING | MB_OK);
		return;
	}
	this->OnOK();
	int ip_leng = m_sMngrIp.GetLength();
	memcpy(ip,m_sMngrIp.GetBuffer(),ip_leng);
	CChangeInitPin changeInitPinDlg(isReSig,ip);
	changeInitPinDlg.DoModal();

}


//void CSystemSmartKey::OnEnableChangeInitpinStatic()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(_T("激活成功"));
//}


//void CSystemSmartKey::OnCbnSelchangeUsrnameCombo()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString strWeb;   
//    int nSel;   
//  
//    // 获取组合框控件的列表框中选中项的索引  
//    nSel = m_usrName.GetCurSel();   
//    // 根据选中项索引获取该项字符串  
//    m_usrName.GetLBText(nSel, strWeb);  
//
//	usrName = strWeb;
//
//}


//void CSystemSmartKey::OnCbnEditchangeUsrnameCombo()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString str;
////	m_usrName.GetDlgItemTextW(IDC_USRNAME_COMBO,str);
//}
