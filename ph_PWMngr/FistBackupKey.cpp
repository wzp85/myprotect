// FistBackupKey.cpp : ʵ���ļ�
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
// CFistBackupKey �Ի���
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
	memcpy(i_random,iRand,18);//����ͬһ��key����ı�ǩ

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
    "����"));                 // lpszFacename
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


// CFistBackupKey ��Ϣ�������
BOOL CFistBackupKey::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CWnd *cWnd = GetDlgItem(IDC_FIRSTPWD_EDIT);
	cWnd->SetFocus();

	isFirstGenKey = FALSE;

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFistBackupKey::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	int ret = 0;
	INT_PTR nRes;

	if(m_firstkeypwd.GetLength()<8)
	{
		MessageBox("PIN�볤�Ȳ���С��8λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_firstkeypwd != m_firstkeyconpwd)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		//this->OnOK();
		//CString tCount_cs;
		///*tCount_cs.Format("%d",tCount);*/
		//if(1 == tCount) tCount_cs = "һ";
		//if(2 == tCount) tCount_cs = "��";
		//if(3 == tCount) tCount_cs = "��";
		//if(4 == tCount) tCount_cs = "��";
		//if(5 == tCount) tCount_cs = "��";
		//CFistBackupKey fistBackupKeyDlg(isGen,sign_random[tCount - 1],Sysmk,tCount,"�������Կ������Կ�ĵ�"+tCount_cs+"����������Կ�ף�������Կ������Կ");
		//fistBackupKeyDlg.DoModal();
		return;
	}
	
	BYTE *out_data=NULL;
	ULONG pul_Size = 0;
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(0 != ret)
	{
		nRes = MessageBox("�ò��������ʽ��key��ȷ��Ҫ������","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strncmp("��Կ������Կ",label,12)/* && !isFirstGenKey*/)
	{     
		MessageBox("��Կ������Կkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION);
			return;
		/*isFirstGenKey = TRUE;*/
	}
	if(!strncmp("�豸����Ա",label,10)/* && !isFirstGenKey*/)
	{     
		MessageBox("�豸����Աkey���ܱ���ʽ�������Ҫ��ʽ�����뵽�������ģ�����˲�����","��ʾ",MB_ICONEXCLAMATION/* | MB_OKCANCEL*/);
		//if(nRes != IDOK)
			return;
	}
/*	else if(strcmp("��Կ������Կ",src))
	{
		MessageBox("��ȷ��������Կ������Կkey��","��ʾ",MB_ICONEXCLAMATION|MB_OK);
		this->OnOK();
		CString tCount_cs;
		if(1 == tCount) tCount_cs = "һ";
		if(2 == tCount) tCount_cs = "��";
		if(3 == tCount) tCount_cs = "��";
		if(4 == tCount) tCount_cs = "��";
		if(5 == tCount) tCount_cs = "��";
		CFistBackupKey fistBackupKeyDlg(isGen,sign_random[tCount - 1],Sysmk,tCount,"�������Կ������Կ�ĵ�"+tCount_cs+"����������Կ�ף�������Կ������Կ");
		fistBackupKeyDlg.DoModal();
		return;
	}*/
	memset(label,0,32);
	ret = CMyUtil::ReadLabel("LBL_CERT_backupRandom",label);

	//key���ʿ���
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

	if(tCount > 1&& !isEqual)//����Ҫ�жϲ�����ǲ��Ǹո�д����key�����,����ʾ�û��ظ�������key
	{
		MessageBox("�����ظ�����ͬһ��key�����Ͻ��Ḳ���Ѿ�д�����Կ������Կ��\n\r�밴����ʾ������һ����Կ������Կkey��","��ʾ",MB_ICONEXCLAMATION|MB_OK);
		/*this->OnOK();
		CString tCount_cs;
		if(1 == tCount) tCount_cs = "һ";
		if(2 == tCount) tCount_cs = "��";
		if(3 == tCount) tCount_cs = "��";
		if(4 == tCount) tCount_cs = "��";
		if(5 == tCount) tCount_cs = "��";
		BYTE rd[16];
		memset(rd,0,16);
		Km_Random(rd,16);
		CFistBackupKey fistBackupKeyDlg(i_random,rd,Sysmk,tCount,"�������Կ������Կ�ĵ�"+tCount_cs+"����������Կ�ף�������Կ������Կ");
		fistBackupKeyDlg.DoModal();*/
		return;
	}

	ret = CMyUtil::KeyInit((LPSTR)(LPCTSTR)m_firstkeypwd);
	if(0 != ret)
	{
		MessageBox("��ʼ��ʧ�ܣ�","��ʾ");
		return;
	}
	//ͨ��д�ļ��ķ�ʽ�Ѵ���������Կ--�ַ�����Sysmk--->д��key
	LPSTR szFileName_userName = "LBL_OTHER_LAB_USERNAME";
	LPSTR szFileName_backRand = "LBL_CERT_backupRandom";//ͬһ����Կ������Կkey���˱�ǩ��ͬ
	LPSTR szFileName_backupKey = "LBL_CERT_backup";
//	LPSTR szFileName_iRand = "LBL_CERT_iRand";//ͬһ����Կ������Կkey���˱�ǩ��ͬ
//	д����Կ������Կ��ʶ
	//ret = CMyUtil::WriteLabel(szFileName_userName,(BYTE *)"��Կ������Կ",12);
	ret = CMyUtil::WriteLabelEx(szFileName_userName,(BYTE *)"��Կ������Կ",12,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("д����Կ������Կ��ʶʧ�ܣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
//	д�������
	//�ȱ�����д���ļ�
	ret = CMyUtil::WriteLabelEx(szFileName_backRand,i_random/*sign_random[tCount - 1]*/,18,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("д�������ʧ�ܣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	/*if(1 == tCount)	memcpy(bkRand_1,sign_random[tCount - 1],16);
	if(2 == tCount)	memcpy(bkRand_2,sign_random[tCount - 1],16);
	if(3 == tCount)	memcpy(bkRand_3,sign_random[tCount - 1],16);
	if(4 == tCount)	memcpy(bkRand_4,sign_random[tCount - 1],16);
	if(5 == tCount)	memcpy(bkRand_5,sign_random[tCount - 1],16);*/
//	д�뱸����Կ
	ret = CMyUtil::WriteLabelEx(szFileName_backupKey,Sysmk,Sysmk_len_in,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("д����Կʧ�ܣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}

	LPSTR szFileName_symmKey = "LBL_CERT_symmKey";
	ret = CMyUtil::WriteLabelEx(szFileName_symmKey,ucSymmkey,16,(char *)m_firstkeypwd.GetString());
	if(0 != ret)
	{
		MessageBox("д��Գ���Կʧ�ܣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}

	if(1 == tCount)	memcpy(bkRand_1,Sysmk,16);
	if(2 == tCount)	memcpy(bkRand_2,Sysmk,16);
	if(3 == tCount)	memcpy(bkRand_3,Sysmk,16);
	if(4 == tCount)	memcpy(bkRand_4,Sysmk,16);
	if(5 == tCount)	memcpy(bkRand_5,Sysmk,16);
	//д��һ��key�����ǩ
	/*ret = CMyUtil::WriteLabel(szFileName_iRand,i_random,16);
	if(0 != ret)
	{
		MessageBox("д���������ǩʧ�ܣ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}*/
	CDialogEx::OnOK();
}
