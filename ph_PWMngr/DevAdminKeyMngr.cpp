// DevAdminKeyMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevAdminKeyMngr.h"
#include "afxdialogex.h"

#include "TIPFormat.h"
#include "MyUtil.h"
#include "KeyDAO.h"

// CDevAdminKeyMngr 对话框

IMPLEMENT_DYNAMIC(CDevAdminKeyMngr, CDialogEx)

CDevAdminKeyMngr::CDevAdminKeyMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevAdminKeyMngr::IDD, pParent)
	, m_title(_T(""))
	, m_adminpin_unlock(_T(""))
	, m_admin_login(_T(""))
	, m_adminpin_old(_T(""))
	, m_adminpin_new(_T(""))
{
	VERIFY(font.CreateFont(
    15,                        // nHeight
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

CDevAdminKeyMngr::~CDevAdminKeyMngr()
{
}

void CDevAdminKeyMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CARRIERMNGR_TITLE_STATIC, m_title);
	CWnd *cWnd = GetDlgItem(IDC_CARRIERMNGR_TITLE_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("管理员KEY管理");

	DDX_Text(pDX, IDC_EDIT1, m_adminpin_unlock);
	DDX_Text(pDX, IDC_EDIT2, m_admin_login);
	DDX_Text(pDX, IDC_EDIT5, m_adminpin_old);
	DDX_Text(pDX, IDC_EDIT6, m_adminpin_new);
}


BEGIN_MESSAGE_MAP(CDevAdminKeyMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDevAdminKeyMngr::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDevAdminKeyMngr::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDevAdminKeyMngr::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDevAdminKeyMngr::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDevAdminKeyMngr 消息处理程序
BOOL CDevAdminKeyMngr::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CDevAdminKeyMngr::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isEmptyKey = FALSE;
	INT_PTR nRes=IDOK;             // 用于保存DoModal函数的返回值  
	int ret = 0;
	CTIPFormat tipFormatDlg;

	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(1 == ret)
	{
		MessageBox("打开设备失败，请确定key是否插好！","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(0 != ret && 1 != ret)
	{
		//MessageBox("读标签错误","提示");
		//MessageBox("您插入的是空key，","提示");
		//return;
		isEmptyKey = TRUE;
	}
	if(!strcmp(label,"设备管理员"))
	{
		nRes = MessageBox("您插入的是设备管理员key，确定要格式化？","提示",MB_ICONWARNING | MB_OKCANCEL);
	}
	else if(!strncmp(label,"密钥备份密钥",12))
	{
		//nRes = MessageBox("您插入的是密钥备份密钥key，请确认是否要格式化，如果格\n\r式化，经该key备份过的密钥将无法恢复！是否继续？","提示",MB_ICONEXCLAMATION|MB_OKCANCEL);
		nRes = tipFormatDlg.DoModal();
	}
	//else
	//{
	//	nRes = MessageBox("您插入的是空key，确定要格式化？","提示",MB_ICONWARNING | MB_OKCANCEL);
	//}
	if(!isEmptyKey && nRes != IDOK)
		return;
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{

	}
	if(!keyDao.DevAuth(smart_DeviceHandle))
	{
		MessageBox("格式化失败","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	LPSTR szAppName = "wellhope";
	LPSTR szAdminPin = "123456";
	DWORD dwAdminPinRetryCount = 6;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,"12345678");
	DWORD dwUserPinRetryCount = 10;
	DWORD dwCreateFileRights = SECURE_EVERYONE_ACCOUNT;
	HAPPLICATION application;	

	char appName[32]={0x00};
	LPSTR appNameLS = appName;
	ULONG handSize = 0;
	ULONG *thepulSize = &handSize;

	if(!keyDao.CreateApplication(smart_DeviceHandle,szAppName,szAdminPin,dwAdminPinRetryCount,szUserPin,dwUserPinRetryCount,dwCreateFileRights,&application))
	{
		MessageBox("格式化失败","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		MessageBox("格式化失败","提示",MB_ICONWARNING|MB_OK);
		return;
	}

	MessageBox("格式化成功","提示");
}


void CDevAdminKeyMngr::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_admin_login.IsEmpty())
	{
		MessageBox("PIN码不能为空！","",MB_ICONEXCLAMATION);
		return;
	}

	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,m_admin_login);
	if(!keyDao.VerifyPIN(phApplication,USER_TYPE,szUserPin,&pulRetryCount))
	{
		MessageBox("登录失败！","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("登录成功！","提示");
}


void CDevAdminKeyMngr::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("    解锁","");
	UpdateData(TRUE);
	
	if(m_adminpin_unlock.IsEmpty())
	{
		MessageBox("PIN码不能为空！","",MB_ICONEXCLAMATION);
		return;
	}

	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = ADMIN_TYPE;
	char userPin[32]={0x00};
	LPSTR szAdminPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szAdminPin,m_adminpin_unlock);
	if(!keyDao.VerifyPIN(phApplication,type,szAdminPin,&pulRetryCount))
	{
		MessageBox("获取管理员权限失败！将无法完成解锁！","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	pulRetryCount = 0;
	if(!keyDao.UnblockPIN(phApplication,szAdminPin,"12345678",&pulRetryCount))
	{
		MessageBox("获取管理员权限成功，但重置用户PIN失败！","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("解锁PIN成功，新的PIN码为12345678，请尽快修改！","提示",MB_ICONWARNING|MB_OK);
}


void CDevAdminKeyMngr::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("    修改成功","");
	UpdateData(TRUE);
	
	if(m_adminpin_old.IsEmpty() || m_adminpin_new.IsEmpty())
	{
		MessageBox("PIN码不能为空！","",MB_ICONEXCLAMATION);
		return;
	}
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userOldPin[32]={0x00};
	LPSTR szUserOldPin = userOldPin;
	strcpy(szUserOldPin,m_adminpin_old);
	char userNewPin[32]={0x00};
	LPSTR szUserNewPin = userNewPin;
	strcpy(szUserNewPin,m_adminpin_new);
	if(!keyDao.ChangePIN(phApplication,USER_TYPE,szUserOldPin,szUserNewPin,&pulRetryCount))
	{
		MessageBox("修改PIN码失败","提示",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("修改PIN码成功","提示");
}
