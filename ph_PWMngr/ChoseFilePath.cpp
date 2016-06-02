// ChoseFilePath.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ChoseFilePath.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDAO.h"
// CChoseFilePath 对话框

IMPLEMENT_DYNAMIC(CChoseFilePath, CDialogEx)

CChoseFilePath::CChoseFilePath(unsigned char *rand_in_p,CString ifSingleBackup,unsigned char *k,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,int type,void *phSession,CWnd* pParent /*=NULL*/)
	: CDialogEx(CChoseFilePath::IDD, pParent)
	, m_filepath_withoutclick(_T(""))
{
	ctrlsName_ifSingle = ifSingleBackup;
	/*index = keyIndex_i;*/
	isSingleChoice = uiKeyIndexNum;
	//in_KeyIndex = puiKeyIndex;
	memset(in_KeyIndex,0,257);
	memcpy(in_KeyIndex,puiKeyIndex,uiKeyIndexNum*sizeof(unsigned int));
	handle = phSession;
	type_Backup = type;

	if(rand_in_p != NULL)
	{
		memset(rand_in,0x00,32);
		memcpy(rand_in,rand_in_p,18);//用于验证备份文件与备份密钥是否匹配
	}

	if(k != NULL)
	{
		memset(in_pucKeyBackupKey,0,17);
		memcpy(in_pucKeyBackupKey,k,16);
	}
}

CChoseFilePath::~CChoseFilePath()
{
}

void CChoseFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH_EDIT, m_filepath_withoutclick);
}


BEGIN_MESSAGE_MAP(CChoseFilePath, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChoseFilePath::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChoseFilePath::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CChoseFilePath::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChoseFilePath 消息处理程序
BOOL CChoseFilePath::OnInitDialog()
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
	CWnd *cWnd = GetDlgItem(IDC_FILEPATH_EDIT);
	cWnd->SetFocus();

	if(APP_BACKUP == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\APPkey-file.backup"); 
	if(ENC_BACKUP == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\KEKkey-file.backup");   
	if(DEV_BACKUP == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\DEVkey-file.backup");  
	if(ADM_BACKUP == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\ADMkey-file.backup");
	if(SIG_CACERTBAK == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\CACert-file.backup");
	if(SIG_RTCERTBAK == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\RTCert-file.backup");//add by syc
	if(SIG_SERVICELOGBAK == type_Backup)
		SetDlgItemText(IDC_FILEPATH_EDIT, "C:\\SERVICELog-file.backup");//add by syc
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChoseFilePath::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//写文件
	CDialogEx::OnOK();
	int ret = 0; 
	void * hSessionHandle = handle;//密码机会话句柄
	unsigned int uiAlgo = SGD_SM1_ECB;//对称密钥算法标识 SM1_ECB
	unsigned int uiKeyIndexNum = isSingleChoice;//是否多选
	unsigned int puiKeyIndex[256] ={0} ;/*in_KeyIndex*//*_ttoi(index)*///密钥索引
	memcpy(puiKeyIndex,in_KeyIndex,uiKeyIndexNum*sizeof(unsigned int));
	unsigned char pucKeyBackupKey[16]={0};/*{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};*///对称密钥 暂时用16位随机数代替（0820）
	memcpy(pucKeyBackupKey,in_pucKeyBackupKey,16);
	unsigned int uiKeyBackupKeyLength=16;//对称密钥长度

	//unsigned int uiAdminIndexNum;
	//unsigned int puiAdminIndex;

	unsigned char *pucKeyBak = NULL;//备份文件
	unsigned int puiKeyBakLength;//备份文件长度
	char outErr[100]={0x00};

	if(APP_BACKUP == type_Backup)
	{
		ret = Km_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("应用密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("应用密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(ENC_BACKUP == type_Backup)
	{
		ret = Km_KeyEncKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("密钥加密密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_KeyEncKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("密钥加密密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(DEV_BACKUP == type_Backup)
	{
		ret = Km_DevKeyBackup(hSessionHandle,uiAlgo,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("设备钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_DevKeyBackup(hSessionHandle,uiAlgo,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("设备密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(ADM_BACKUP == type_Backup)
	{
		ret = Km_AdminBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("管理员备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_AdminBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("管理员备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(SIG_APPBAK == type_Backup)
	{
		ret = Sig_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("签名服务器应用密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("签名服务器应用密钥备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(SIG_CACERTBAK == type_Backup)
	{
		ret = Sig_CACertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("签名服务器CA证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_CACertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("签名服务器CA证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	/**************RooTCert************/
	else if(SIG_RTCERTBAK==type_Backup)
	{
		ret = Sig_RTCertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("根证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_RTCertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("根证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	/*******************服务日志的备份********************************/
	else if(SIG_SERVICELOGBAK==type_Backup)
	{	
		ret = Sig_ServiceLogBackup( hSessionHandle, uiKeyIndexNum,puiKeyIndex,pucKeyBak, &puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("根证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_ServiceLogBackup( hSessionHandle, uiKeyIndexNum,puiKeyIndex,pucKeyBak, &puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("根证书备份失败！"+(CString)outErr,"提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	if(0 == ret)
	{
		CString tip;
		char *filename;
		if(!filePath.IsEmpty())
		{
			filename = (LPSTR)(LPCTSTR)filePath;
			tip = filePath;
		}
		else
		{
			filename = (LPSTR)(LPCTSTR)m_filepath_withoutclick;
			tip = m_filepath_withoutclick;
		}
		if(NULL == filename)
		{
			MessageBox("路径为空","提示");
			return;
		}
		//对密钥备份密钥key中共享标签做B64编码后写入备份文件
		if(ADM_BACKUP != type_Backup && SIG_CACERTBAK!=type_Backup && SIG_RTCERTBAK!=type_Backup && SIG_SERVICELOGBAK!=type_Backup)
		{
			char BsRd[32]={0x00};
			char *str_find = strstr((char*)pucKeyBak,"ODc2NTQzODc2NTQzODc2NTQz");
			int leng_rd = Km_Encode((char *)rand_in,18,BsRd);
			memcpy(str_find,BsRd,leng_rd);
		}
		CMyUtil::Write2File(filename,pucKeyBak,puiKeyBakLength);
		if(0 != ret)
		{
			MessageBox("写入文件失败","提示");
			delete []pucKeyBak;
			return;
		}
		MessageBox("备份成功，备份文件保存在"+tip,"提示");
	}

	delete []pucKeyBak;

}


void CChoseFilePath::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CChoseFilePath::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器
    TCHAR szFilter[] = _T("文本文件(*.backup)|*.backup|所有文件(*.*)|*.*||");   
    // 构造保存文件对话框
	CString fileName,index_cs;
	if(1 == isSingleChoice)
	{
		index_cs.Format("%d",isSingleChoice);
		fileName = index_cs + "--" + ctrlsName_ifSingle;
	}
	//else if(1 == isSingleChoice && ENC_BACKUP == type_Backup)
	//{
	//	index_cs.Format("%d",isSingleChoice);
	//	fileName = index_cs + "--" + ctrlsName_ifSingle;
	//}
	//else if(1 == isSingleChoice && DEV_BACKUP == type_Backup)
	//{
	//	index_cs.Format("%d",isSingleChoice);
	//	fileName = index_cs + "--" + ctrlsName_ifSingle;
	//}
	//else if(1 == isSingleChoice && ADM_BACKUP == type_Backup)
	//{
	//	index_cs.Format("%d",isSingleChoice);
	//	fileName = index_cs + "--" + ctrlsName_ifSingle;
	//}
	//else if(1 == isSingleChoice && SIG_CACERTBAK == type_Backup)
	//{
	//	index_cs.Format("%d",isSingleChoice);
	//	fileName = index_cs + "--" + ctrlsName_ifSingle;
	//}
	//else if(1 == isSingleChoice && SIG_SERVICELOGBAK == type_Backup)
	//{
	//	index_cs.Format("%d",isSingleChoice);
	//	fileName = index_cs + "--" + ctrlsName_ifSingle;
	//}
	else if(1 != isSingleChoice && SIG_SERVICELOGBAK == type_Backup)
	{
		fileName = "ALL-SERVICELOG";
	}
	else if(1 != isSingleChoice && SIG_CACERTBAK == type_Backup)
	{
		fileName = "ALL-CA";
	}
	/***********rootCert***************/
	else if(1 != isSingleChoice && SIG_RTCERTBAK == type_Backup)
	{
		fileName = "ALL-RT";
	}
	else if(1 != isSingleChoice && APP_BACKUP == type_Backup)
	{
		fileName = "ALL-APP";
	}
	else if(1 != isSingleChoice && ENC_BACKUP == type_Backup)
	{
		fileName = "ALL-KEK";
	}
	else if(1 != isSingleChoice && DEV_BACKUP == type_Backup)
	{
		fileName = "ALL-DEV";
	}
	else if(1 != isSingleChoice && ADM_BACKUP == type_Backup)
	{
		fileName = "ALL-ADM";
	}
    CFileDialog fileDlg(FALSE, _T("backup"),fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
  
    // 显示保存文件对话框  
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
		filePath = strFilePath;
        SetDlgItemText(IDC_FILEPATH_EDIT, strFilePath);   
    }   

}
