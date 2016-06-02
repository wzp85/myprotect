// FistBackupKey.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "FistBackupKey.h"
#include "afxdialogex.h"

#include "SecBackupKey.h"
#include "KeyDAO.h"
#include "ph_km.h"
#include "MyUtil.h"
#define FILESIZE_SIGDEVADMIN 1024
// CFistBackupKey 对话框
BYTE bkRand_1[32]={0x00};
BYTE bkRand_2[32]={0x00};
BYTE bkRand_3[32]={0x00};
BYTE bkRand_4[32]={0x00};
BYTE bkRand_5[32]={0x00};
BOOL isFirstGenKey;

IMPLEMENT_DYNAMIC(CFistBackupKey, CDialogEx)

CFistBackupKey::CFistBackupKey(BYTE *iRand,BYTE *backRand,BYTE *SymmKey,unsigned char *k,int k_len,int i_Count,CString in_data,CWnd* pParent /*=NULL*/)
	: CDialogEx(CFistBackupKey::IDD, pParent)
	, m_firstkeypwd(_T(""))
	, m_firstkeyconpwd(_T(""))
{
	memset(i_random,0,18);
	memcpy(i_random,iRand,18);//传进同一套key共享的标签

	memset(Sysmk,0,256);
	memcpy(Sysmk,k,k_len);
	Sysmk_len_in = k_len;
	tCount = i_Count;
//	isGen = isGenerate;

	memcpy(ucSymmkey,SymmKey,16);
	
	sign_random[i_Count-1] = (unsigned char *)calloc(16,sizeof(unsigned char));
	memcpy(sign_random[i_Count-1],backRand,16);

	VERIFY(line1.CreateFont(
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
	m_line1 = in_data;
}

CFistBackupKey::~CFistBackupKey()
{
}

void CFistBackupKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIRSTPWD_EDIT, m_firstkeypwd);
	DDX_Text(pDX, IDC_FIRSTCON_EDIT, m_firstkeyconpwd);
	DDX_Text(pDX, IDC_LINEFIRST_STATIC, m_line1);
	CWnd *cWnd = GetDlgItem(IDC_LINEFIRST_STATIC);
	cWnd->SetFont(&line1);
	cWnd->SetWindowText(m_line1);
}


BEGIN_MESSAGE_MAP(CFistBackupKey, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFistBackupKey::OnBnClickedOk)
END_MESSAGE_MAP()


// CFistBackupKey 消息处理程序
BOOL CFistBackupKey::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	CWnd *cWnd = GetDlgItem(IDC_FIRSTPWD_EDIT);
	cWnd->SetFocus();

	isFirstGenKey = FALSE;

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFistBackupKey::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	int ret = 0;
	INT_PTR nRes;

	if(m_firstkeypwd.GetLength()<8)
	{
		MessageBox("PIN码长度不得小于8位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_firstkeypwd != m_firstkeyconpwd)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		//this->OnOK();
		//CString tCount_cs;
		///*tCount_cs.Format("%d",tCount);*/
		//if(1 == tCount) tCount_cs = "一";
		//if(2 == tCount) tCount_cs = "二";
		//if(3 == tCount) tCount_cs = "三";
		//if(4 == tCount) tCount_cs = "四";
		//if(5 == tCount) tCount_cs = "五";
		//CFistBackupKey fistBackupKeyDlg(isGen,sign_random[tCount - 1],Sysmk,tCount,"请插入密钥备份密钥的第"+tCount_cs+"个智能密码钥匙，生成密钥备份密钥");
		//fistBackupKeyDlg.DoModal();
		return;
	}
	
	BYTE *out_data=NULL;
	ULONG pul_Size = 0;
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(0 != ret)
	{
		nRes = MessageBox("该操作将会格式化key，确定要继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strncmp("密钥备份密钥",label,12)/* && !isFirstGenKey*/)
	{     
		MessageBox("密钥备份密钥key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION);
			return;
		/*isFirstGenKey = TRUE;*/
	}
	if(!strncmp("设备管理员",label,10)/* && !isFirstGenKey*/)
	{     
		MessageBox("设备管理员key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION/* | MB_OKCANCEL*/);
		//if(nRes != IDOK)
			return;
	}
/*	else if(strcmp("密钥备份密钥",src))
	{
		MessageBox("请确定插入密钥备份密钥key！","提示",MB_ICONEXCLAMATION|MB_OK);
		this->OnOK();
		CString tCount_cs;
		if(1 == tCount) tCount_cs = "一";
		if(2 == tCount) tCount_cs = "二";
		if(3 == tCount) tCount_cs = "三";
		if(4 == tCount) tCount_cs = "四";
		if(5 == tCount) tCount_cs = "五";
		CFistBackupKey fistBackupKeyDlg(isGen,sign_random[tCount - 1],Sysmk,tCount,"请插入密钥备份密钥的第"+tCount_cs+"个智能密码钥匙，生成密钥备份密钥");
		fistBackupKeyDlg.DoModal();
		return;
	}*/
	memset(label,0,32);
	ret = CMyUtil::ReadLabel("LBL_CERT_backupRandom",label);

	//key访问控制
	int isEqual,isEqual1,isEqual2,isEqual3,isEqual4;
	if(2 == tCount) isEqual = strncmp((const char*)(bkRand_1),(const char*)label,16);
	if(3 == tCount) 
	{
		isEqual1 = strncmp((const char*)(bkRand_2),(const char*)label,16);
		isEqual2 = strncmp((const char*)(bkRand_1),(const char*)label,16);
		if(!isEqual1 || !isEqual2)
			isEqual = 0;
		else
			isEqual = 1;
	}
	if(4 == tCount) 
	{
		isEqual1 = strncmp((const char*)(bkRand_3),(const char*)label,16);
		isEqual2 = strncmp((const char*)(bkRand_1),(const char*)label,16);
		isEqual3 = strncmp((const char*)(bkRand_2),(const char*)label,16);
		if(!isEqual1 || !isEqual2 || !isEqual3)
			isEqual = 0;
		else
			isEqual = 1;
	}
	if(5 == tCount) 
	{
		isEqual1 = strncmp((const char*)(bkRand_4),(const char*)label,16);
		isEqual2 = strncmp((const char*)(bkRand_1),(const char*)label,16);
		isEqual3 = strncmp((const char*)(bkRand_2),(const char*)label,16);
		isEqual4 = strncmp((const char*)(bkRand_3),(const char*)label,16);
		if(!isEqual1 || !isEqual2 || !isEqual3 || !isEqual4)
			isEqual = 0;
		else
			isEqual = 1;
	}

	if(tCount > 1&& !isEqual)//这里要判断插入的是不是刚刚写过的key。如果,则提示用户重复插入了key
	{
		MessageBox("请勿重复插入同一个key！否认将会覆盖已经写入的密钥备份密钥！\n\r请按照提示插入下一个密钥备份密钥key！","提示",MB_ICONEXCLAMATION|MB_OK);
		/*this->OnOK();
		CString tCount_cs;
		if(1 == tCount) tCount_cs = "一";
		if(2 == tCount) tCount_cs = "二";
		if(3 == tCount) tCount_cs = "三";
		if(4 == tCount) tCount_cs = "四";
		if(5 == tCount) tCount_cs = "五";
		BYTE rd[16];
		memset(rd,0,16);
		Km_Random(rd,16);
		CFistBackupKey fistBackupKeyDlg(i_random,rd,Sysmk,tCount,"请插入密钥备份密钥的第"+tCount_cs+"个智能密码钥匙，生成密钥备份密钥");
		fistBackupKeyDlg.DoModal();*/
		return;
	}

	ret = CMyUtil::KeyInit((LPSTR)(LPCTSTR)m_firstkeypwd);
	if(0 != ret)
	{
		MessageBox("初始化失败！","提示");
		return;
	}
	//通过写文件的方式把传进来的密钥--字符数组Sysmk--->写入key
	LPSTR szFileName_userName = "LBL_OTHER_LAB_USERNAME";
	LPSTR szFileName_backRand = "LBL_CERT_backupRandom";//同一套密钥备份密钥key，此标签相同
	LPSTR szFileName_backupKey = "LBL_CERT_backup";
//	LPSTR szFileName_iRand = "LBL_CERT_iRand";//同一套密钥备份密钥key，此标签相同
//	写入密钥备份密钥标识
	//ret = CMyUtil::WriteLabel(szFileName_userName,(BYTE *)"密钥备份密钥",12);
	ret = CMyUtil::WriteLabelEx(szFileName_userName,(BYTE *)"密钥备份密钥",12,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入密钥备份密钥标识失败！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
//	写入随机数
	//先编码再写入文件
	ret = CMyUtil::WriteLabelEx(szFileName_backRand,i_random/*sign_random[tCount - 1]*/,18,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入随机数失败！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	/*if(1 == tCount)	memcpy(bkRand_1,sign_random[tCount - 1],16);
	if(2 == tCount)	memcpy(bkRand_2,sign_random[tCount - 1],16);
	if(3 == tCount)	memcpy(bkRand_3,sign_random[tCount - 1],16);
	if(4 == tCount)	memcpy(bkRand_4,sign_random[tCount - 1],16);
	if(5 == tCount)	memcpy(bkRand_5,sign_random[tCount - 1],16);*/
//	写入备份密钥
	ret = CMyUtil::WriteLabelEx(szFileName_backupKey,Sysmk,Sysmk_len_in,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入密钥失败！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	LPSTR szFileName_symmKey = "LBL_CERT_symmKey";
	ret = CMyUtil::WriteLabelEx(szFileName_symmKey,ucSymmkey,16,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入对称密钥失败！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	if(1 == tCount)	memcpy(bkRand_1,Sysmk,16);
	if(2 == tCount)	memcpy(bkRand_2,Sysmk,16);
	if(3 == tCount)	memcpy(bkRand_3,Sysmk,16);
	if(4 == tCount)	memcpy(bkRand_4,Sysmk,16);
	if(5 == tCount)	memcpy(bkRand_5,Sysmk,16);
	//写入一套key共享标签
	/*ret = CMyUtil::WriteLabel(szFileName_iRand,i_random,16);
	if(0 != ret)
	{
		MessageBox("写入随机数标签失败！","提示",MB_ICONWARNING | MB_OK);
		return;
	}*/
	CDialogEx::OnOK();
}
