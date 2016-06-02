// DevKeyFirResume.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevKeyFirResume.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDevide.h"
// CDevKeyFirResume 对话框

IMPLEMENT_DYNAMIC(CDevKeyFirResume, CDialogEx)

CDevKeyFirResume::CDevKeyFirResume(int isAdm,void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevKeyFirResume::IDD, pParent)
	, m_firstResume(_T(""))
	, m_usrpin(_T(""))
	, m_usrpincon(_T(""))
	, m_line2(_T(""))
	, m_browsefile(_T(""))
{
	phHandle_devRsu = handle;
	isAdmDev = isAdm;

	VERIFY(fontFirstResume.CreateFont(
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

	VERIFY(fontLine2.CreateFont(
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

CDevKeyFirResume::~CDevKeyFirResume()
{
}

void CDevKeyFirResume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BROWSE_BUTTON, m_browseFile);
	DDX_Text(pDX, IDC_FIRSTRESUME_STATIC, m_firstResume);
	DDX_Text(pDX, IDC_USRPIN_EDIT, m_usrpin);
	DDX_Text(pDX, IDC_USRPINCON_EDIT, m_usrpincon);
	DDX_Text(pDX, IDC_LINE2_STATIC, m_line2);
	CWnd *cWnd = GetDlgItem(IDC_FIRSTRESUME_STATIC);
	cWnd->SetFont(&fontFirstResume);
	if(1 == isAdmDev)
		cWnd->SetWindowText("读取设备密钥备份文件");
	else if(2 == isAdmDev)
		cWnd->SetWindowText("读取设备管理员备份文件");
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetFont(&fontLine2);
	if(1 == isAdmDev)
		cWnd->SetWindowText("请选择要恢复的设备密钥备份文件！并输入新的私钥使用授权码！");
	else if(2 == isAdmDev)
		cWnd->SetWindowText("           请选择要恢复的设备管理员备份文件！");

	if(1 == isAdmDev)
	{
		cWnd = GetDlgItem(IDC_EDONE_STATIC);
		cWnd->SetWindowText("私钥使用授权码");
		cWnd = GetDlgItem(IDC_EDTWO_STATIC);
		cWnd->SetWindowText("私钥使用授权码（确认）：");
	}
	else if(2 == isAdmDev)
	{
		cWnd = GetDlgItem(IDC_EDONE_STATIC);
		cWnd->SetWindowText("");
		cWnd = GetDlgItem(IDC_EDTWO_STATIC);
		cWnd->SetWindowText("");
		cWnd = GetDlgItem(IDC_USRPIN_EDIT);
		cWnd->ShowWindow(FALSE);
		cWnd = GetDlgItem(IDC_USRPINCON_EDIT);
		cWnd->ShowWindow(FALSE);
	//	m_usrpinS.ShowWindow(FALSE);
	//	m_usrpinF.ShowWindow(FALSE);
	}
	DDX_Text(pDX, IDC_BROWSE_EDIT, m_browsefile);
	DDX_Control(pDX, IDC_USRPIN_EDIT, m_usrpinF);
	DDX_Control(pDX, IDC_USRPINCON_EDIT, m_usrpinS);
}


BEGIN_MESSAGE_MAP(CDevKeyFirResume, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDevKeyFirResume::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, &CDevKeyFirResume::OnBnClickedBrowseButton)
END_MESSAGE_MAP()


// CDevKeyFirResume 消息处理程序


void CDevKeyFirResume::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if(m_browsefile.IsEmpty())
	{
		MessageBox("请选择要恢复的备份文件！","确认选择文件",MB_ICONEXCLAMATION);
		return;
	}

	//恢复管理员
	if(2 == isAdmDev)
	{
		int ret = 0;
		void *hSessionHandle = phHandle_devRsu;
		unsigned char *pucAdminBackup=NULL;
		unsigned int uiAdminBackupLength=0;

		int length_adm = 0;
		char *filename_adm = (LPSTR)(LPCTSTR)m_browsefile;
		CMyUtil::ReadData(filename_adm,pucAdminBackup,&length_adm);
		pucAdminBackup = new unsigned char[length_adm];
		CMyUtil::ReadData(filename_adm,pucAdminBackup,&length_adm);
		uiAdminBackupLength = length_adm;
		char ch_last=pucAdminBackup[length_adm-1];
		int ch_last_in = atoi(&ch_last);
		if(0x34 != ch_last)
		{
			MessageBox("您选择的不是管理员密钥备份文件，请选择管理员密钥的备份文件进行恢复！","备份文件类型错误",MB_ICONEXCLAMATION);
			delete pucAdminBackup;
			return;
		}
		ret = Km_AdminRecovery(hSessionHandle,pucAdminBackup,uiAdminBackupLength);
		if(0 != ret)
		{
			char outAr[100]={0x00};
			retValueParse(ret,outAr);
			MessageBox("管理员恢复失败","恢复失败"+(CString)outAr,MB_ICONWARNING | MB_OK);
			isRecoveryOK = 0;
			delete  []pucAdminBackup;
			return;
		}
		else if(0 == ret)
		{
			MessageBox("管理员恢复成功","恢复成功",MB_ICONINFORMATION|MB_OK);
			isRecoveryOK = 2;
		}
		delete  pucAdminBackup;
		this->OnOK();
		return;
	}

	void *hSessionHandle = phHandle_devRsu;
	unsigned int uiAlgo = SGD_SM1_ECB;

	unsigned char pucAdminPin[32]={0};
	

	unsigned char pucKeyBackupKey[256]={0};
	unsigned int uiKeyBackupKeyLength=16;
	unsigned char *pucKeyBak=NULL;
	unsigned int uiKeyBakLength;

	int data_len = 0;
	char *filename = (LPSTR)(LPCTSTR)m_browsefile;
	CMyUtil::ReadData(filename,pucKeyBak,&data_len);
	pucKeyBak = new unsigned char[data_len];
	CMyUtil::ReadData(filename,pucKeyBak,&data_len);
	uiKeyBakLength = data_len;
	//判断备份文件类型是否正确
	char ch_last=pucKeyBak[data_len-1];
	int ch_last_in = atoi(&ch_last);
	//获取最后的随机数，用于判断备份key与备份文件是否匹配
	char rd_last[32]={0x00};
	memcpy(rd_last,&pucKeyBak[data_len-27],24);
	char rd_deco[32]={0x00};

	int len_deco = Km_Decode(rd_last,24,rd_deco);

	if(0x31 != ch_last)
	{
		MessageBox("您选择的不是设备密钥备份文件，请选择设备密钥的备份文件进行恢复！","备份文件类型错误",MB_ICONEXCLAMATION);
		delete pucKeyBak;
		return;
	}

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

	Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_Rsu_dev,0,257);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_Rsu_dev);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("请插入第二份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_Rsu_dev,0,257);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_Rsu_dev);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("请插入第三份密钥备份密钥"));
	if(IDOK == devKeyFirBacDlg3.DoModal())
	{
		//此处该调用恢复接口phHandle_devRsu
		int ret = 0;

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle_devRsu,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_Rsu_dev,0,257);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_Rsu_dev);

		unsigned char sysKey_for_in[256]={0};
		unsigned int sysKey_for_in_len = 0;
		ret = KeyMerge(sys_Key_1_Rsu_dev,len_1,sys_Key_2_Rsu_dev,len_2,sys_Key_3_Rsu_dev,len_3,sysKey_for_in,&sysKey_for_in_len);
		if(0 != ret || 16 != sysKey_for_in_len)
		{
			MessageBox("密钥合并出错！","提示");
			return;
		}
		/*{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};*/
		memcpy(pucKeyBackupKey,sysKey_for_in,16);
		
		int length = m_usrpin.GetLength();
		memcpy(pucAdminPin,m_usrpin.GetBuffer(),length);
		unsigned int uiAdminPinLength = length;

		ret = Km_DevKeyRecovery(hSessionHandle,uiAlgo,pucAdminPin,uiAdminPinLength,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,uiKeyBakLength);
		if(0 == ret)
		{
			MessageBox("恢复设备密钥成功","提示",MB_ICONINFORMATION|MB_OK);
			isRecoveryOK = 2;
		}
		else if(0 != ret)
		{
			char outDkr[100]={0x00};
			retValueParse(ret,outDkr);
			MessageBox("恢复设备密钥失败"+(CString)outDkr,"提示",MB_ICONWARNING|MB_OK);
			isRecoveryOK = 1;
		}
		delete pucKeyBak;
	}
	this->OnOK();
}

void CDevKeyFirResume::GetRecoverState(int *rc_state)
{
	*rc_state = isRecoveryOK;
}

void CDevKeyFirResume::OnBnClickedBrowseButton()
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
        SetDlgItemText(IDC_BROWSE_EDIT, strFilePath);   
    }   
}   


BOOL CDevKeyFirResume::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 定位光标  
	CWnd *cWnd = GetDlgItem(IDC_BROWSE_EDIT);
	cWnd->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
