// DevKeyFirBac.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevKeyFirBac.h"
#include "afxdialogex.h"

#include "DevkeyBACKUP.h"
#include "KeyDAO.h"
// CDevKeyFirBac �Ի���
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
    "����"));                 // lpszFacename
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
	cWnd->SetWindowText("��ȡ��Կ������Կ");
	DDX_Text(pDX, IDC_LINE2_STATIC, m_line2);
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetWindowText(m_line2);
	DDX_Text(pDX, IDC_PIN_EDIT, m_usrPIN);
}


BEGIN_MESSAGE_MAP(CDevKeyFirBac, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDevKeyFirBac::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDevKeyFirBac::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDevKeyFirBac ��Ϣ�������

void CDevKeyFirBac::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//У��PIN��
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
		MessageBox("���豸ʧ��,��ȷ��key�Ƿ��ã�","��ʾ",MB_ICONEXCLAMATION|MB_OK);
		return;
	}
	if(!keyDao.EnumApplication(phDev,appName_lps,&pulSize))
	{
		MessageBox("ö��Ӧ��ʧ��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(!keyDao.OpenApplication(phDev,appName_lps,&happlication))
	{
		MessageBox("��Ӧ��ʧ��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}

	if(!keyDao.VerifyPIN(happlication,type,szUserPin,&pulRetryCount))
	{
		MessageBox("PIN�����","��ʾ");
		return;
	}
	
	//��ȡLBL_CERT_backupRandom�ȱ�ǩ
	BYTE pbOutData[256]={0x00};
	ULONG pulOutLen = sizeof(pbOutData);
	FILEATTRIBUTE fileattribute={0x00};
	LPSTR szFile = "LBL_OTHER_LAB_USERNAME";
	if(!keyDao.GetFileInfo(happlication,szFile,&fileattribute))
	{
		//MessageBox("��ȡ�ļ���Ϣʧ��");
		MessageBox("��������ǿ�key���Ǳ�ϵͳkey����ȷ�ϲ�����Կ������Կkey��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	pulOutLen = fileattribute.FileSize;
	if(!keyDao.ReadFile(happlication,szFile,0,fileattribute.FileSize,pbOutData,&pulOutLen))
	{
		MessageBox("��ȡ�ļ�ʧ��");
		return;
	}
	char src[128]={0x00};
	memcpy(src,pbOutData,pulOutLen);
	if(strncmp(src,"��Կ������Կ",12) && !strncmp(src,"�豸����Ա",10))
	{
		MessageBox("����������豸����Աkey���������Կ������Կkey������","��ʾ",MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	BYTE *out_data=NULL;
	ULONG out_data_len = 0;
	szFile = "LBL_CERT_backup";
	if(!keyDao.GetFileInfo(happlication,szFile,&fileattribute))
	{
		MessageBox("��ȡ�ļ���Ϣʧ��");
		return;
	}
	out_data_len = fileattribute.FileSize;
	out_data = new BYTE[out_data_len];
	memset(out_data,0,out_data_len);
	if(!keyDao.ReadFile(happlication,szFile,0,fileattribute.FileSize,out_data,&out_data_len))
	{
		MessageBox("��ȡ�ļ�ʧ��--------------------LBL_CERT_backup");
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
			MessageBox("�÷���Կ������Կ�Ѿ���ȡ�������ظ�ʹ�ã�\n\r�밴����ʾ������һ����Կ������Կkey��","��ʾ",MB_ICONEXCLAMATION|MB_OK);
			return;
		}
	}
	if(3 == kCount)
	{
		if(!strncmp((const char*)app_bkRand_1,(const char*)out_data,16) || !strncmp((const char*)app_bkRand_2,(const char*)out_data,16))
		{
			MessageBox("�÷���Կ������Կ�Ѿ���ȡ�������ظ�ʹ�ã�\n\r�밴����ʾ������һ����Կ������Կkey��","��ʾ",MB_ICONEXCLAMATION|MB_OK);
	/*		if(!keyDao.CloseDevice(phDev))
			{
				MessageBox("�Ͽ��豸ʧ��");
			}*/
			//this->OnOK();
			//CString kCount_cs = "��";
			//CDevKeyFirBac devKeyFirBacDlg1(kCount,_T("������"+kCount_cs+"����Կ������Կ������PIN�룡"));
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
		MessageBox("��ȡ�ļ���Ϣʧ��");
		return;
	}
	
	ULONG uiSymmKeyLen=fileattribute.FileSize;
	BYTE  pucSymmKey[32]={0x00};

	if(!keyDao.ReadFile(happlication,szMark,0,fileattribute.FileSize,pucSymmKey,&uiSymmKeyLen))
	{
		MessageBox("��ȡ�ļ�ʧ��--------------------LBL_CERT_symmKey");
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
		MessageBox("��ȡ�ļ���Ϣʧ��");
		return;
	}
	ULONG out_data_iRand_len = fileattribute.FileSize;
	BYTE *out_data_iRand = new BYTE[out_data_iRand_len];
	memset(out_data_iRand,0,out_data_iRand_len);
	if(!keyDao.ReadFile(happlication,"LBL_CERT_backupRandom",0,fileattribute.FileSize,out_data_iRand,&out_data_iRand_len))
	{
		 //MessageBox("��ȡ����key�������ǩ�ļ�ʧ��-----1LBL_CERT_backupRandom");
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
		MessageBox("����Կ������ԿKey��ղ�ʹ�õ���Կ������Կkey����ͬһ�ף���ȷ�ϲ���ͬһ��Key����!","��ʾ",MB_ICONEXCLAMATION);
		//isClear = TRUE;memset(key_i_random,0,32);
		delete out_data_iRand;
		return;
	}
	

	delete out_data_iRand;


	if(!keyDao.Logout(happlication))
	{
		MessageBox("�ر�Ӧ��ʧ�� ");
		return;
	}

	if(!keyDao.CloseDevice(phDev))
	{
		MessageBox("�Ͽ��豸ʧ��");
		return;
	}
	CDialogEx::OnOK();
}


void CDevKeyFirBac::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*memset(app_bkRand_1,0x00,32);
	memset(app_bkRand_2,0x00,32);
	memset(key_i_random,0x00,32);*/

	CWnd *cWnd = GetDlgItem(IDC_PIN_EDIT);
	cWnd->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
