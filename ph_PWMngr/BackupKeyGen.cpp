// BackupKeyGen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "BackupKeyGen.h"
#include "afxdialogex.h"

#include "FistBackupKey.h"
#include "ph_km.h"
// CBackupKeyGen �Ի���
#include "KeyDevide.h"
#include "MyUtil.h"
#pragma comment(lib, "KeyDevideDll.lib" )

IMPLEMENT_DYNAMIC(CBackupKeyGen, CPropertyPage)

CBackupKeyGen::CBackupKeyGen()
	: CPropertyPage(CBackupKeyGen::IDD)
{
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
    "����"));                 // lpszFacename
}

CBackupKeyGen::~CBackupKeyGen()
{
}

void CBackupKeyGen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLELINE_STATIC, m_titleline);
	CWnd *cWnd = GetDlgItem(IDC_TITLELINE_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("��Կ������Կ����");
}


BEGIN_MESSAGE_MAP(CBackupKeyGen, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CBackupKeyGen::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBackupKeyGen ��Ϣ�������
BOOL CBackupKeyGen::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CBackupKeyGen::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char *k[5]={0};
	unsigned int k_len[5];
	for(int i = 0;i < 5;i++)
	{
		k[i]=(unsigned char *)calloc(256,sizeof(unsigned char));
	}

	
	int ret = 0;
	BYTE random_iRand[18]={0x00};//ͬһ��key����ǩ������ͬ 
	BYTE random_symmKey[16]={0x00};//�Գ���Կ-->��Ӧ��ǩ��symmKey
	BYTE random_backupRandom[16]={0x00};//�����-->��Ӧ��ǩ��backupRandom
	ret = Km_Random(random_iRand,18);
	ret = Km_Random(random_symmKey,16);
	ret = Km_Random(random_backupRandom,16);

	unsigned char *originK[5]={0};
	unsigned int originK_len[5];
	for(int i = 0;i < 5;i++)
	{
		originK[i]=(unsigned char *)calloc(256,sizeof(unsigned char));
	}

	KeyDevide(random_symmKey,16,originK,originK_len);//k��Ӧbackup��Ӧ�����ݵ�ԭ��


	unsigned char buff[192]={0x00};
	unsigned int buff_len=0;

	

	unsigned char symmkey1[16]={0x00};
	unsigned char symmkey2[16]={0x00};
	unsigned char symmkey3[16]={0x00};
	unsigned char symmkey4[16]={0x00};
	unsigned char symmkey5[16]={0x00};

	unsigned char *symmkey[5]={symmkey1,symmkey2,symmkey3,symmkey4,symmkey5};

	for(int i = 0;i < 5;i++)
	{
		memset(buff,0x10,192);		//������Ϊbase64�������Ϊ130*4/3==176���ֽڣ���Ҫ��λ16���ֽں����ԳƼӽ���
		buff_len = Km_Encode((char *)originK[i],originK_len[i],(char *)buff);
		buff_len+=16;

		if(buff_len!=192)
		{
			char outGkek1[100]={0x00};
			retValueParse(ret,outGkek1);
			MessageBox("������Կ������Կʧ��"+(CString)outGkek1,"��ʾ");
			return ;
		}

		ret = Km_Random(symmkey[i],16);
		if(ret!=0)
		{
			char outGkek2[100]={0x00};
			retValueParse(ret,outGkek2);
			MessageBox("������Կ������Կʧ��"+(CString)outGkek2,"��ʾ");
			return ;
		}

		ret =Km_SymmCrypt(phHandle_bkg,0,0,symmkey[i],16,buff,buff_len,k[i],&k_len[i]);
		if(ret!=0)
		{
			char outGkek3[100]={0x00};
			retValueParse(ret,outGkek3);
			MessageBox("������Կ������Կʧ��"+(CString)outGkek3,"��ʾ");
			return ;
		}
	}

	//���Դ���
//	char *path="C:\\key_befor_devide.txt";
//	CMyUtil::Write2File(path,random_symmKey,16);

//	char *path1="C:\\1.txt";
//	CMyUtil::Write2File(path1,k[0],k_len[0]);

	CFistBackupKey m_firstBackupKeyDlg1(random_iRand,random_backupRandom,symmkey[0],k[0],k_len[0],1,_T("�������Կ������Կ�ĵ�һ����������Կ�ף�������Կ������Կ"));
	if(IDOK != m_firstBackupKeyDlg1.DoModal())
		return;

//	char *path2="C:\\2.txt";
//	CMyUtil::Write2File(path2,k[1],k_len[1]);

	memset(random_backupRandom,0,16);
	ret = Km_Random(random_backupRandom,16);
	CFistBackupKey m_firstBackupKeyDlg2(random_iRand,random_backupRandom,symmkey[1],k[1],k_len[1],2,_T("�������Կ������Կ�ĵڶ�����������Կ�ף�������Կ������Կ"));
	if(IDOK != m_firstBackupKeyDlg2.DoModal())
		return;
//	char *path3="C:\\3.txt";
//	CMyUtil::Write2File(path3,k[2],k_len[2]);

	memset(random_backupRandom,0,16);
	ret = Km_Random(random_backupRandom,16);
	CFistBackupKey m_firstBackupKeyDlg3(random_iRand,random_backupRandom,symmkey[2],k[2],k_len[2],3,_T("�������Կ������Կ�ĵ�������������Կ�ף�������Կ������Կ"));
	if(IDOK != m_firstBackupKeyDlg3.DoModal())
		return;

//	char *path4="C:\\4.txt";
//	CMyUtil::Write2File(path4,k[3],k_len[3]);

	memset(random_backupRandom,0,16);
	ret = Km_Random(random_backupRandom,16);
	CFistBackupKey m_firstBackupKeyDlg4(random_iRand,random_backupRandom,symmkey[3],k[3],k_len[3],4,_T("�������Կ������Կ�ĵ��ĸ���������Կ�ף�������Կ������Կ"));
	if(IDOK != m_firstBackupKeyDlg4.DoModal())
		return;

//	char *path5="C:\\5.txt";
//	CMyUtil::Write2File(path5,k[4],k_len[4]);

	memset(random_backupRandom,0,16);
	ret = Km_Random(random_backupRandom,16);
	CFistBackupKey m_firstBackupKeyDlg5(random_iRand,random_backupRandom,symmkey[4],k[4],k_len[4],5,_T("�������Կ������Կ�ĵ������������Կ�ף�������Կ������Կ"));
	if(IDOK == m_firstBackupKeyDlg5.DoModal())
	{
		MessageBox(_T("������һ���µ���Կ������Կ"),"��ʾ");
	}
	for(int i = 0;i < 5;i++)
	{
		free(k[i]);
	}

}
