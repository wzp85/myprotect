// CheckKeyManager.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "CheckKeyManager.h"
#include "afxdialogex.h"
#include "Myutil.h"
#include "keyDao.h"

// CCheckKeyManager 对话框

IMPLEMENT_DYNAMIC(CCheckKeyManager, CDialogEx)

CCheckKeyManager::CCheckKeyManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckKeyManager::IDD, pParent)
	, m_ckmPINedit(_T(""))
	, m_ckmPIN_edit(_T(""))
{

}

CCheckKeyManager::~CCheckKeyManager()
{
}

void CCheckKeyManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ckm_pin, m_ckm_pin);

	DDX_Text(pDX, IDC_EDIT_ckm_pin, m_ckmPIN_edit);
}


BEGIN_MESSAGE_MAP(CCheckKeyManager, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCheckKeyManager::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCheckKeyManager::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCheckKeyManager 消息处理程序


void CCheckKeyManager::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	/***********先从配置文件里读取签不签发密钥授权员，不签发不需要验证**************/
	int length = 0;
	int KMnger = 0;
	/*CMyUtil::ReadData("./config.txt",NULL,&length);
	if(length==0)
	{
		MessageBox("读取文件失败，请关闭管理程序后重试！","提示",MB_ICONWARNING | MB_OK);
	   return ;
	}
	BYTE *data = new BYTE[length + 1];
	memset(data,0x00,length + 1);
	CMyUtil::ReadData("./config.txt",data,&length);
	
	char *source = (char*)data;
	*/
	char *source = (char*)pConfigData;
	char *str = strstr(source,"KEY_MANAGER_SQ=");
	char *tem = str + strlen("KEY_MANAGER_SQ=");
	char *end = strstr(tem,"\n");
	char kmnger_buf[32] = {0x00};
	memcpy(kmnger_buf,tem,end-tem);
	KMnger = atoi(kmnger_buf);
	if(1 != KMnger)
	{
		return ;
	}
	
	//验证输入PIN码格式是否为空
	UpdateData(TRUE);

	if(m_ckmPIN_edit.IsEmpty())
	{
		MessageBox("PIN码不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	
	//读标签判断是不是密钥授权员的key

	CKeyDao keyDao;
	char label[32] = {0x00};
	int nRes = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(nRes)
	{
		MessageBox("没有检测到本系统支持的key，请确认key是否插好或插入的是否是本系统支持的key","提示",MB_ICONWARNING | MB_OK);
	}
	
	if(!strncmp(label,"安全审计员",12))
	{
		MessageBox("您插入的是安全审计员key，请确认插入密钥授权员key！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"设备管理员",10))
	{
		MessageBox("您插入的是设备管理员key，请确认插入密钥授权员key！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"密钥备份密钥",12))
	{
		MessageBox("您插入的是密钥备份密钥key，请确认插入密钥授权员key！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	DEVHANDLE smart_DeviceHandle = 0;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		MessageBox("打开设备失败,请确认是否插入key","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	
	LPSTR szAppName = "wellhope";
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szAppName,&phApplication))
	{
		MessageBox("打开应用失败");
		return;
	}
	
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userPin[32] = {0x00};
	LPSTR szUserPin = userPin;
	strcpy(szUserPin,m_ckmPIN_edit);
	if(!keyDao.VerifyPIN(phApplication,type,szUserPin,&pulRetryCount))
	{
		MessageBox("PIN码错误！","提示",MB_ICONWARNING | MB_OK);
		return ;
	}
	MessageBox("密钥验证成功","提示",MB_ICONWARNING | MB_OK);
	CDialogEx::OnOK();
}


void CCheckKeyManager::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	checkState=1;
	CDialogEx::OnCancel();
}

void CCheckKeyManager::getCheckState(int *state)
{
	*state=checkState;
}


BOOL CCheckKeyManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	checkState=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
