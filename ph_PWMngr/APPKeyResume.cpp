// APPKeyResume.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "APPKeyResume.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDAO.h"
#include "KeyDevide.h"
// CAPPKeyResume 对话框

IMPLEMENT_DYNAMIC(CAPPKeyResume, CDialogEx)

CAPPKeyResume::CAPPKeyResume(void *handle,int isSig,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPKeyResume::IDD, pParent)
	, m_browsefile(_T(""))
	, m_usrpin(_T(""))
	, m_usrpincon(_T(""))
{
	phHandle = handle;
	isSigServer = isSig;
	VERIFY(font_line1.CreateFont(
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

	VERIFY(font_line2.CreateFont(
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

CAPPKeyResume::~CAPPKeyResume()
{
}

void CAPPKeyResume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSE_BUTTON, m_browse);
	DDX_Text(pDX, IDC_BROWSE_EDIT, m_browsefile);
	DDX_Text(pDX, IDC_USRPIN_EDIT, m_usrpin);
	DDX_Text(pDX, IDC_USRPINCON_EDIT, m_usrpincon);
	DDX_Control(pDX, IDC_FIRSTRESUME_STATIC, m_title);
	DDX_Control(pDX, IDC_LINE2_STATIC, m_line2);
	CWnd *cWnd = GetDlgItem(IDC_FIRSTRESUME_STATIC);
	cWnd->SetFont(&font_line1);
	cWnd->SetWindowText("读取应用密钥备份文件");
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetFont(&font_line2);
	cWnd->SetWindowText("请选择要恢复的应用密钥备份文件！并输入新的私钥使用授权码！");
}


BEGIN_MESSAGE_MAP(CAPPKeyResume, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAPPKeyResume::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAPPKeyResume::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, &CAPPKeyResume::OnBnClickedBrowseButton)
END_MESSAGE_MAP()


// CAPPKeyResume 消息处理程序


void CAPPKeyResume::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("已恢复"));
}


void CAPPKeyResume::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->OnOK();---------------------------------------恢复之后tab里的恢复主页是否消失
	UpdateData(TRUE);

	//判断选的是不是对应类型的备份文件
	if(m_filePath.IsEmpty())
	{
		MessageBox("请选择要恢复的备份文件！","提示",MB_ICONEXCLAMATION);
		return;
	}

	char *fileName = (LPSTR)(LPCTSTR)m_filePath;
	BYTE *data_read = NULL;
	int data_read_len = 0;
	CMyUtil::ReadData(fileName,data_read,&data_read_len);
	data_read = new BYTE[data_read_len];
	CMyUtil::ReadData(fileName,data_read,&data_read_len);

	char rd_last[32]={0x00};
	memcpy(rd_last,&data_read[data_read_len-27],24);
	char rd_deco[32]={0x00};
	int len_deco = Km_Decode(rd_last,24,rd_deco);

	char ch_last=data_read[data_read_len-1];
	int ch_last_in = atoi(&ch_last);

	if(0x32 != ch_last)
	{
		MessageBox("您选择的不是应用密钥备份文件，请选择应用密钥的备份文件进行恢复！","备份文件类型错误",MB_ICONEXCLAMATION);
		delete data_read;
		return;
	}
	delete data_read;

	if(m_usrpin.GetLength()<8)
	{
		MessageBox("PIN码长度不能小于8位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_usrpin != m_usrpincon)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_usrpin))
	{
		MessageBox("PIN码不能全是数字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	//-----------------------------------------校验输入pin码是否正确add by syc 2/13


	/*************************************/

	CDevKeyFirBac devKeyFirBacDlg1(1,_T("请插入第一份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg1.DoModal())
		return;

	unsigned char ch_cmp[32]={0x00};
	devKeyFirBacDlg1.GetRandomInKey(ch_cmp);
	if(strncmp(rd_deco,(const char*)ch_cmp,len_deco))
	{
		MessageBox("您选择的备份文件与备份密钥key不匹配！","检测到不匹配",MB_ICONEXCLAMATION);
		devKeyFirBacDlg1.ResetKIR();
		return;
	}
	unsigned int B64KeyLen1=0;
	unsigned char B64Key1[256]={0x00};

	Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_Rsu,0,256);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_Rsu);

	//此处用devKeyFirBacDlg1.GetRandomInKey(xx)方法把key中随的机数读取出来,同备份文件末尾的随机数做比较，如果相同则备份文件与备份key匹配,不同则不匹配，并就此返回

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("请插入第二份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_Rsu,0,256);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_Rsu);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("请插入第三份密钥备份密钥"));
	if(devKeyFirBacDlg3.DoModal() == IDOK)
	{

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_Rsu,0,256);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_Rsu);

		int ret = 0;
		unsigned char Keydata[256]={0};
		unsigned int Keydata_len = 0;
		ret = KeyMerge(sys_Key_1_Rsu,len_1,sys_Key_2_Rsu,len_2,sys_Key_3_Rsu,len_3,Keydata,&Keydata_len);
		if(0 != ret || 16 != Keydata_len)
		{
			MessageBox("密钥合并出错！","提示");
			return;
		}
		void *hSessionHandle = phHandle;
		unsigned int uiAlgo = SGD_SM1_ECB;

		unsigned char pucAdminPin[32]={0};
		int length = m_usrpin.GetLength();
		memcpy(pucAdminPin,m_usrpin.GetBuffer(),length);
		unsigned int uiAdminPinLength = length;

		unsigned char pucKeyBackupKey[16]={0}/*{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08}*/;
		memcpy(pucKeyBackupKey,Keydata,16);
		unsigned int uiKeyBackupKeyLength=16;
		unsigned char *pucKeyBak=NULL;
		unsigned int uiKeyBakLength;

		/*CKeyDao  keyDao;
		DEVHANDLE handle;
		keyDao.OpenDevice(&handle);
		keyDao.GenRandom(handle,pucKeyBackupKey,uiKeyBackupKeyLength);*/

		char *filename = (LPSTR)(LPCTSTR)m_filePath;
		CMyUtil::ReadData(filename,pucKeyBak,&length);
		pucKeyBak = new unsigned char[length];
		CMyUtil::ReadData(filename,pucKeyBak,&length);
		uiKeyBakLength = length;

		if(!isSigServer)
		{
			ret = Km_AppKeyRecovery(hSessionHandle,uiAlgo,pucAdminPin,uiAdminPinLength,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,uiKeyBakLength);
			if(0 == ret)
			{
				MessageBox("恢复成功","提示");
			}
			else
			{
				char outAkr[100]={0x00};
				retValueParse(ret,outAkr);
				MessageBox("恢复失败"+(CString)outAkr,"提示");
			}
		}
		else if(isSigServer)
		{
			ret = Sig_AppKeyRecovery(hSessionHandle,uiAlgo,pucAdminPin,uiAdminPinLength,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,uiKeyBakLength);
			if(0 == ret)
			{
				MessageBox("恢复成功","提示");
			}
			else
			{
				char outAkr[100]={0x00};
				retValueParse(ret,outAkr);
				MessageBox("恢复失败"+(CString)outAkr,"提示");
			}
		}
	/*	keyDao.CloseDevice(handle);*/
		delete pucKeyBak;
	}
	CDialogEx::OnOK();
}


void CAPPKeyResume::OnBnClickedBrowseButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("文本文件(*.backup)|*.backup|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("backup"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框  
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();   
		m_filePath = strFilePath;
        SetDlgItemText(IDC_BROWSE_EDIT, strFilePath);   
    }   
}
