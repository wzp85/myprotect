// ChoseFilePath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ChoseFilePath.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDAO.h"
// CChoseFilePath �Ի���

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
		memcpy(rand_in,rand_in_p,18);//������֤�����ļ��뱸����Կ�Ƿ�ƥ��
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


// CChoseFilePath ��Ϣ�������
BOOL CChoseFilePath::OnInitDialog()
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
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChoseFilePath::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//д�ļ�
	CDialogEx::OnOK();
	int ret = 0; 
	void * hSessionHandle = handle;//������Ự���
	unsigned int uiAlgo = SGD_SM1_ECB;//�Գ���Կ�㷨��ʶ SM1_ECB
	unsigned int uiKeyIndexNum = isSingleChoice;//�Ƿ��ѡ
	unsigned int puiKeyIndex[256] ={0} ;/*in_KeyIndex*//*_ttoi(index)*///��Կ����
	memcpy(puiKeyIndex,in_KeyIndex,uiKeyIndexNum*sizeof(unsigned int));
	unsigned char pucKeyBackupKey[16]={0};/*{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};*///�Գ���Կ ��ʱ��16λ��������棨0820��
	memcpy(pucKeyBackupKey,in_pucKeyBackupKey,16);
	unsigned int uiKeyBackupKeyLength=16;//�Գ���Կ����

	//unsigned int uiAdminIndexNum;
	//unsigned int puiAdminIndex;

	unsigned char *pucKeyBak = NULL;//�����ļ�
	unsigned int puiKeyBakLength;//�����ļ�����
	char outErr[100]={0x00};

	if(APP_BACKUP == type_Backup)
	{
		ret = Km_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("Ӧ����Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("Ӧ����Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(ENC_BACKUP == type_Backup)
	{
		ret = Km_KeyEncKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("��Կ������Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_KeyEncKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("��Կ������Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(DEV_BACKUP == type_Backup)
	{
		ret = Km_DevKeyBackup(hSessionHandle,uiAlgo,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("�豸Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_DevKeyBackup(hSessionHandle,uiAlgo,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("�豸��Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(ADM_BACKUP == type_Backup)
	{
		ret = Km_AdminBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("����Ա����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Km_AdminBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("����Ա����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(SIG_APPBAK == type_Backup)
	{
		ret = Sig_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("ǩ��������Ӧ����Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_AppKeyBackup(hSessionHandle,uiAlgo,uiKeyIndexNum,puiKeyIndex,pucKeyBackupKey,uiKeyBackupKeyLength,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("ǩ��������Ӧ����Կ����ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	else if(SIG_CACERTBAK == type_Backup)
	{
		ret = Sig_CACertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("ǩ��������CA֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_CACertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("ǩ��������CA֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
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
			MessageBox("��֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_RTCertBackup(hSessionHandle,uiKeyIndexNum,puiKeyIndex,pucKeyBak,&puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("��֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
	/*******************������־�ı���********************************/
	else if(SIG_SERVICELOGBAK==type_Backup)
	{	
		ret = Sig_ServiceLogBackup( hSessionHandle, uiKeyIndexNum,puiKeyIndex,pucKeyBak, &puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			MessageBox("��֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		pucKeyBak = new unsigned char[puiKeyBakLength+512];
		ret = Sig_ServiceLogBackup( hSessionHandle, uiKeyIndexNum,puiKeyIndex,pucKeyBak, &puiKeyBakLength);
		if(0 != ret)
		{
			retValueParse(ret,outErr);
			delete []pucKeyBak;
			MessageBox("��֤�鱸��ʧ�ܣ�"+(CString)outErr,"��ʾ",MB_ICONEXCLAMATION);
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
			MessageBox("·��Ϊ��","��ʾ");
			return;
		}
		//����Կ������Կkey�й����ǩ��B64�����д�뱸���ļ�
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
			MessageBox("д���ļ�ʧ��","��ʾ");
			delete []pucKeyBak;
			return;
		}
		MessageBox("���ݳɹ��������ļ�������"+tip,"��ʾ");
	}

	delete []pucKeyBak;

}


void CChoseFilePath::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CChoseFilePath::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����
    TCHAR szFilter[] = _T("�ı��ļ�(*.backup)|*.backup|�����ļ�(*.*)|*.*||");   
    // ���챣���ļ��Ի���
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
  
    // ��ʾ�����ļ��Ի���  
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����  
        strFilePath = fileDlg.GetPathName();  
		filePath = strFilePath;
        SetDlgItemText(IDC_FILEPATH_EDIT, strFilePath);   
    }   

}
