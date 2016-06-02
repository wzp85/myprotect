// DevKeyFirBac.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevKeyFirBac.h"
#include "afxdialogex.h"

#include "DevkeyBACKUP.h"
#include "KeyDAO.h"
// CDevKeyFirBac 对话框
BYTE app_bkRand_1[32]={0x00};
BYTE app_bkRand_2[32]={0x00};

BYTE key_i_random[32]={0x00};

IMPLEMENT_DYNAMIC(CDevKeyFirBac, CDialogEx)

CDevKeyFirBac::CDevKeyFirBac(int Count,CString dataIn,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevKeyFirBac::IDD, pParent)
	, m_line1(_T(""))
	, m_line2(_T(""))
	, m_usrPIN(_T(""))
{
	kCount = Count;

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
    "宋体"));                 // lpszFacename
	m_line2 = dataIn;
}

CDevKeyFirBac::~CDevKeyFirBac()
{
}

void CDevKeyFirBac::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE1_STATIC, m_line1);
	CWnd *cWnd = GetDlgItem(IDC_LINE1_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("读取密钥备份密钥");
	DDX_Text(pDX, IDC_LINE2_STATIC, m_line2);
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetWindowText(m_line2);
	DDX_Text(pDX, IDC_PIN_EDIT, m_usrPIN);
}


BEGIN_MESSAGE_MAP(CDevKeyFirBac, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDevKeyFirBac::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDevKeyFirBac::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDevKeyFirBac 消息处理程序

void CDevKeyFirBac::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//校验PIN码
	UpdateData(TRUE);

	CKeyDao keyDao;
	DEVHANDLE phDev;
	char appName[32]={0};
	LPSTR appName_lps = appName;
	ULONG pulSize = sizeof(appName);
	HAPPLICATION happlication;
	ULONG type = USER_TYPE;
	char userPin[32]={0};
	LPSTR szUserPin  = userPin;
	memcpy(szUserPin,m_usrPIN,sizeof(userPin));
	ULONG pulRetryCount = 0;

	if(!keyDao.OpenDevice(&phDev))
	{
		MessageBox("打开设备失败,请确认key是否插好！","提示",MB_ICONEXCLAMATION|MB_OK);
		return;
	}
	if(!keyDao.EnumApplication(phDev,appName_lps,&pulSize))
	{
		MessageBox("枚举应用失败","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(!keyDao.OpenApplication(phDev,appName_lps,&happlication))
	{
		MessageBox("打开应用失败","提示",MB_ICONEXCLAMATION);
		return;
	}

	if(!keyDao.VerifyPIN(happlication,type,szUserPin,&pulRetryCount))
	{
		MessageBox("PIN码错误","提示");
		return;
	}
	
	//读取LBL_CERT_backupRandom等标签
	BYTE pbOutData[256]={0x00};
	ULONG pulOutLen = sizeof(pbOutData);
	FILEATTRIBUTE fileattribute={0x00};
	LPSTR szFile = "LBL_OTHER_LAB_USERNAME";
	if(!keyDao.GetFileInfo(happlication,szFile,&fileattribute))
	{
		//MessageBox("获取文件信息失败");
		MessageBox("您插入的是空key或不是本系统key，请确认插入密钥备份密钥key！","提示",MB_ICONEXCLAMATION);
		return;
	}
	pulOutLen = fileattribute.FileSize;
	if(!keyDao.ReadFile(happlication,szFile,0,fileattribute.FileSize,pbOutData,&pulOutLen))
	{
		MessageBox("读取文件失败");
		return;
	}
	char src[128]={0x00};
	memcpy(src,pbOutData,pulOutLen);
	if(strncmp(src,"密钥备份密钥",12) && !strncmp(src,"设备管理员",10))
	{
		MessageBox("您插入的是设备管理员key，请插入密钥备份密钥key继续！","提示",MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	BYTE *out_data=NULL;
	ULONG out_data_len = 0;
	szFile = "LBL_CERT_backup";
	if(!keyDao.GetFileInfo(happlication,szFile,&fileattribute))
	{
		MessageBox("获取文件信息失败");
		return;
	}
	out_data_len = fileattribute.FileSize;
	out_data = new BYTE[out_data_len];
	memset(out_data,0,out_data_len);
	if(!keyDao.ReadFile(happlication,szFile,0,fileattribute.FileSize,out_data,&out_data_len))
	{
		MessageBox("读取文件失败--------------------LBL_CERT_backup");
		delete out_data;
		return;
	}
	//keyDao.ReadFile(happlication,"LBL_CERT_backupRandom",0,16,out_data,&out_data_len);
	if(1 == kCount) memcpy(app_bkRand_1,out_data,16);
	if(2 == kCount) 
	{
		if(strncmp((const char*)app_bkRand_1,(const char*)out_data,16))
			memcpy(app_bkRand_2,out_data,16);
		else
		{
			MessageBox("该份密钥备份密钥已经读取，请勿重复使用！\n\r请按照提示插入下一个密钥备份密钥key！","提示",MB_ICONEXCLAMATION|MB_OK);
			return;
		}
	}
	if(3 == kCount)
	{
		if(!strncmp((const char*)app_bkRand_1,(const char*)out_data,16) || !strncmp((const char*)app_bkRand_2,(const char*)out_data,16))
		{
			MessageBox("该份密钥备份密钥已经读取，请勿重复使用！\n\r请按照提示插入下一个密钥备份密钥key！","提示",MB_ICONEXCLAMATION|MB_OK);
	/*		if(!keyDao.CloseDevice(phDev))
			{
				MessageBox("断开设备失败");
			}*/
			//this->OnOK();
			//CString kCount_cs = "三";
			//CDevKeyFirBac devKeyFirBacDlg1(kCount,_T("请插入第"+kCount_cs+"份密钥备份密钥，输入PIN码！"));
			//devKeyFirBacDlg1.DoModal();
			return;
		}
	}
	memset(key_sys,0,257);
	key_sys_len = out_data_len;
	memcpy(key_sys,out_data,key_sys_len);
	
	LPSTR szMark = "LBL_CERT_symmKey";
	if(!keyDao.GetFileInfo(happlication,szMark,&fileattribute))
	{
		MessageBox("获取文件信息失败");
		return;
	}
	
	ULONG uiSymmKeyLen=fileattribute.FileSize;
	BYTE  pucSymmKey[32]={0x00};

	if(!keyDao.ReadFile(happlication,szMark,0,fileattribute.FileSize,pucSymmKey,&uiSymmKeyLen))
	{
		MessageBox("读取文件失败--------------------LBL_CERT_symmKey");
		return;
	}
	memset(keykek,0,257);
	keykek_len = uiSymmKeyLen;
	memcpy(keykek,pucSymmKey,keykek_len);

	delete out_data;

	//char lll[1024]={0x00};
	//ULONG  sizePul = 1024;
	//keyDao.EnumFiles(happlication,lll,&sizePul);
	LPSTR szFile_RD = "LBL_CERT_backupRandom";
	if(!keyDao.GetFileInfo(happlication,szFile_RD,&fileattribute))
	{
		MessageBox("获取文件信息失败");
		return;
	}
	ULONG out_data_iRand_len = fileattribute.FileSize;
	BYTE *out_data_iRand = new BYTE[out_data_iRand_len];
	memset(out_data_iRand,0,out_data_iRand_len);
	if(!keyDao.ReadFile(happlication,"LBL_CERT_backupRandom",0,fileattribute.FileSize,out_data_iRand,&out_data_iRand_len))
	{
		 //MessageBox("读取本套key随机数标签文件失败-----1LBL_CERT_backupRandom");
		delete out_data_iRand;
		return;
	}
	//BOOL isZero = TRUE;
	//for(int i = 0;i < 32;i++)
	//{
	//	if(key_i_random[i] != 0)
	//	{
	//		isZero = FALSE;
	//		break;
	//	}	
	//}
	if(1 == kCount)
		memcpy(key_i_random,out_data_iRand,18);

	memset(kk_rand,0x00,32);
	memcpy(kk_rand,out_data_iRand,out_data_iRand_len);
	leng_kk_rand = out_data_iRand_len;

//	BOOL isClear = FALSE;
	if(1<kCount && memcmp((const char*)key_i_random,(const char*)out_data_iRand,18))
	{
		MessageBox("该密钥备份密钥Key与刚才使用的密钥备份密钥key不是同一套，请确认插入同一套Key继续!","提示",MB_ICONEXCLAMATION);
		//isClear = TRUE;memset(key_i_random,0,32);
		delete out_data_iRand;
		return;
	}
	

	delete out_data_iRand;


	if(!keyDao.Logout(happlication))
	{
		MessageBox("关闭应用失败 ");
		return;
	}

	if(!keyDao.CloseDevice(phDev))
	{
		MessageBox("断开设备失败");
		return;
	}
	CDialogEx::OnOK();
}


void CDevKeyFirBac::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	this->OnCancel();
	/*CDevkeyBACKUP devkeyBackupDlg;
	devkeyBackupDlg.DoModal();*/
}

void CDevKeyFirBac::GetRandomInKey(unsigned char *k_rand)
{
	memset(k_rand,0x00,32);
	memcpy(k_rand,kk_rand,leng_kk_rand);
}

void CDevKeyFirBac::ResetKIR()
{
	memset(key_i_random,0x00,32);
}


BOOL CDevKeyFirBac::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*memset(app_bkRand_1,0x00,32);
	memset(app_bkRand_2,0x00,32);
	memset(key_i_random,0x00,32);*/

	CWnd *cWnd = GetDlgItem(IDC_PIN_EDIT);
	cWnd->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
