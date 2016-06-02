// EncryptKeyResume.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "EncryptKeyResume.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "MyUtil.h"
#include "ph_km.h"
#include "KeyDevide.h"
// CEncryptKeyResume 对话框

IMPLEMENT_DYNAMIC(CEncryptKeyResume, CDialogEx)

CEncryptKeyResume::CEncryptKeyResume(void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncryptKeyResume::IDD, pParent)
	, m_filepath(_T(""))
{
	phHandle_ek = handle;

	VERIFY(line1.CreateFont(
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

	VERIFY(line2.CreateFont(
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

CEncryptKeyResume::~CEncryptKeyResume()
{
}

void CEncryptKeyResume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH_EDIT, m_filepath);
	DDX_Control(pDX, IDC_LINEONE_STATIC, m_line1);
	DDX_Control(pDX, IDC_LINETWO_STATIC, m_line2);
	CWnd *cWnd = GetDlgItem(IDC_LINEONE_STATIC);
	cWnd->SetFont(&line1);
	cWnd->SetWindowText("读取密钥加密密钥备份文件");
	cWnd = GetDlgItem(IDC_LINETWO_STATIC);
	cWnd->SetFont(&line2);
	cWnd->SetWindowText("请选择需要恢复的密钥加密密钥备份文件！");
}


BEGIN_MESSAGE_MAP(CEncryptKeyResume, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CEncryptKeyResume::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CEncryptKeyResume::OnBnClickedOk)
END_MESSAGE_MAP()


// CEncryptKeyResume 消息处理程序


void CEncryptKeyResume::OnBnClickedButton1()
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
	   m_filepath = strFilePath;
       SetDlgItemText(IDC_FILEPATH_EDIT, strFilePath);   
    }   

}


void CEncryptKeyResume::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_filepath.IsEmpty())
	{
		MessageBox("请选择要恢复的备份文件！","提示",MB_ICONEXCLAMATION);
		return;
	}

	char *fileName = (LPSTR)(LPCTSTR)m_filepath;
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
//	MessageBox("密钥加密密钥备份文件"+(CString)ch_last);
	int ch_last_in = atoi(&ch_last);
	//if(3 != ch_last_in)
	if(0x33!=ch_last)
	{
		MessageBox("您选择的不是密钥加密密钥备份文件，请选择密钥加密密钥的备份文件进行恢复！","备份文件类型错误",MB_ICONEXCLAMATION);
		delete data_read;
		return;
	}
	delete data_read;


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

	Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_ekRsu,0,256);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_ekRsu);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("请插入第二份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	//memset(sys_Key_2_ekRsu,0,256);
	//int len_2 = devKeyFirBacDlg2.key_sys_len;
	//memcpy(sys_Key_2_ekRsu,devKeyFirBacDlg2.key_sys,len_2);
	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_ekRsu,0,256);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_ekRsu);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("请插入第三份密钥备份密钥"));
	if(devKeyFirBacDlg3.DoModal() == IDOK)
	{
		//memset(sys_Key_3_ekRsu,0,256);
		//int len_3 = devKeyFirBacDlg3.key_sys_len;
		//memcpy(sys_Key_3_ekRsu,devKeyFirBacDlg3.key_sys,len_3);
		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_ekRsu,0,256);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_ekRsu);

		unsigned char sysKey_for_in[256]={0};
		unsigned int sysKey_for_in_len = 0;
		int ret = 0;
		ret = KeyMerge(sys_Key_1_ekRsu,len_1,sys_Key_2_ekRsu,len_2,sys_Key_3_ekRsu,len_3,sysKey_for_in,&sysKey_for_in_len);
		if(0 != ret || 16 != sysKey_for_in_len)
		{
			MessageBox("密钥合并出错！","提示");
			return;
		}
		void *hSessionHandle = phHandle_ek;
		unsigned int uiAlgo = SGD_SM1_ECB;

		unsigned char pucKeyBackupKey[16]={0};/*={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};*/
		memcpy(pucKeyBackupKey,sysKey_for_in,16);
		unsigned int uiKeyBackupKeyLength=16;
		unsigned char *pucKeyBak=NULL;
		unsigned int uiKeyBakLength;

		/*CKeyDao  keyDao;
		DEVHANDLE handle;
		keyDao.OpenDevice(&handle);
		keyDao.GenRandom(handle,pucKeyBackupKey,uiKeyBackupKeyLength);*/
		int length = 0;
		char *filename = (LPSTR)(LPCTSTR)m_filepath;
		CMyUtil::ReadData(filename,pucKeyBak,&length);
		pucKeyBak = new unsigned char[length];
		CMyUtil::ReadData(filename,pucKeyBak,&length);
		uiKeyBakLength = length;

		ret = Km_KeyEncRecovery(hSessionHandle,uiAlgo,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,uiKeyBakLength);
		if(0 == ret)
		{
			MessageBox("恢复成功","提示");
		}
		if(0 != ret)
		{
			char outKer[100]={0x00};
			retValueParse(ret,outKer);
			MessageBox("恢复失败"+(CString)outKer,"提示");
			return;
		}
	/*	keyDao.CloseDevice(handle);*/
		delete pucKeyBak;
	}
	CDialogEx::OnOK();
}
