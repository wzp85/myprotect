
// ph_PWMngrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ph_PWMngrDlg.h"
#include "afxdialogex.h"

#include "MainMenuDlg.h"
#include "SystemSmartKey.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ Version 2.0.0.0")
#define PWMMNGR_CAPTION_SIG _T("�Ϻ��ջ�ǩ������������ϵͳ Version 2.0.0.0")

#include "KeyDAO.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "code.h"
//#include "DAI.h"
#include "misc.h"
#define PORT  6788



char adm_k_Num_1[16]={0x00};
char adm_k_Num_2[16]={0x00};
char adm_k_Num_3[16]={0x00};
char adm_k_Num_4[16]={0x00};
char adm_k_Num_5[16]={0x00};

int adm_index_for_enable = 0;
int ip_Count = 0;//�����ļ���IP����

//BYTE config_USERNAMEtext[10]={0x00};
BYTE config_IPtext[10][32]={0x00};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cph_PWMngrDlg �Ի���




Cph_PWMngrDlg::Cph_PWMngrDlg(CString iip,int i,void *hSessionHandle,void *key_handle,void *containerHandle,LPCTSTR szCaption,CWnd* pParent /*=NULL*/)
	: CDialogEx(Cph_PWMngrDlg::IDD, pParent)
	, m_loginPINedit(_T(""))
	, m_ip(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_szCaption = szCaption;
	if(hSessionHandle != NULL)
		phSHandle = hSessionHandle;
	if(key_handle != NULL)
		key_phSHandle = key_handle;
//	key_containerHandle = containerHandle;
	i_adm = i;

	if(iip.IsEmpty())
		ip = iip;
}

void Cph_PWMngrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGIN_PIN_EDIT, m_loginPINedit);
//	DDX_Control(pDX, IDC_MNGRPORT_IPADDRESS, m_ipAddress);
	DDX_Control(pDX, IDC_IP_LOG_COMBO, m_ip_log);
	DDX_CBString(pDX, IDC_IP_LOG_COMBO, m_ip);
}

BEGIN_MESSAGE_MAP(Cph_PWMngrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cph_PWMngrDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cph_PWMngrDlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_INIT_BUTTON, &Cph_PWMngrDlg::OnBnClickedInitButton)
ON_STN_CLICKED(IDC_SYSINIT_STATIC, &Cph_PWMngrDlg::OnClickedSysinitStatic)
ON_STN_CLICKED(IDC_STATIC_RESIGADMIN, &Cph_PWMngrDlg::OnStnClickedStaticResigadmin)
ON_WM_TIMER()
END_MESSAGE_MAP()


// Cph_PWMngrDlg ��Ϣ�������

BOOL Cph_PWMngrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	this->SetWindowText(m_szCaption);

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
	memset(uiIP,0x00,32);
//	m_ipAddress.SetAddress(127,0,0,1);

	char cur_temp[500]={0x00};
	GetCurrentDirectory(500,cur_temp);
	CString CurrentPath;
	CurrentPath.Format("%s",cur_temp);
	SetCurrentDirectory(CurrentPath);


	//int length=0;
	//char *data=NULL;
	//CFile mFile("config.txt",CFile::modeRead);
	//
	//data = new char[mFile.GetLength()];

	//mFile.Read(data,length);
	//length=mFile.GetLength();
	//mFile.Close();


	int length=0;

	CMyUtil::ReadData("./config.txt",NULL,&length);
	BYTE *data = new BYTE[length+1];
	memset(data,0x00,length+1);
	CMyUtil::ReadData("./config.txt",data,&length);


	char *pIP = (char *)data;
	char *str = strstr(pIP,"IP=");
	char *start,*end;
	int ipBufLength=0;
	start = str + sizeof("IP=") - 1;
	char ipBuf[32]={0x00};
	char ipCache[32] = {0x00};

	for(int i=0;i<10;i++)
	{
		memset(ipBuf,0x00,32);

		end=strstr(start,"|");
		if(end==NULL)
			break;
		ipBufLength=end-start;
		memcpy(ipBuf,start,ipBufLength);
		memcpy(ipCache,ipBuf,ipBufLength);
		start=end+strlen("|");
		
		memcpy(config_IPtext[i],ipBuf,strlen(ipBuf));
		m_ip_log.AddString(CString(ipBuf));
		m_ip_log.SetCurSel(5);
		ip_Count++;
	}

	delete data;

	if(!ip.IsEmpty())
		SetDlgItemText(IDC_IP_LOG_COMBO,ip);

	//m_ipAddress.SetFieldRange(0,0,192);
	//m_ipAddress.SetFieldRange(1,0,168);
	//m_ipAddress.SetFieldRange(3,0,255);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cph_PWMngrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cph_PWMngrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cph_PWMngrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cph_PWMngrDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	/*int ret = 0;*/
	/*ret = LoadPkiServerDll("SKF_APP.dll");*/
	/*INT_PTR nRes;*/
	/*BYTE i1,i2,i3,i4;
	CString ip1,ip2,ip3,ip4,ip;
	m_ipAddress.GetAddress(i1,i2,i3,i4);
	ip1.Format(_T("%d"),i1);
	ip2.Format(_T("%d"),i2);
	ip3.Format(_T("%d"),i3);
	ip4.Format(_T("%d"),i4);
	ip = ip1 + "." + ip2 + "." + ip3 + "." + ip4;*/
	/*nRes = MessageBox(_T("����ǰʹ��IP��ַΪ��" + ip),_T("��ʾ"),MB_OKCANCEL | MB_ICONINFORMATION);
	if(IDCANCEL == nRes)
		return;*/

	BOOL isWriteOK = TRUE;
	if(m_loginPINedit.IsEmpty())
	{
		MessageBox("PIN�벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ip.IsEmpty())
	{
		MessageBox("IP��ַ����Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	//�������IP��ַ�������ļ���û����д���ļ�
	/*for(int i = 0;i < 10;i++)
	{
		if(!strcmp(m_ip,(const char*)config_IPtext[i]))
			isWriteOK = FALSE;
	}
	if(isWriteOK && ip_Count<10)
	{
		char *filePath = "config.txt";
		CString ip = "IP="+m_ip+"\n";
		CMyUtil::Write2FileAppend(filePath,(unsigned char*)ip.GetBuffer(),ip.GetLength());
	}*/
	CKeyDao keyDao;

	char label[32]={0x00};
	int nRes = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(nRes)
	{
		MessageBox("û�м�⵽��ϵͳ֧�ֵ�key����ȷ��key�Ƿ��û������Ƿ��Ǳ�ϵͳ֧�ֵ�key","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"��Կ������Կ",12))
	{
		MessageBox("�����������Կ������Կkey����ȷ�ϲ������Աkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"��Կ��ȨԱ",10))
	{
		MessageBox("�����������Կ����Աkey��Ҫ��¼ϵͳ������豸����Աkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"�豸����Ա",10))
	{
		type_mnger = 0;
	}
	if(!strncmp(label,"��ȫ���Ա",10))
	{
		type_mnger = 1;
	}
	DEVHANDLE smart_DeviceHandle = 0;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		MessageBox("���豸ʧ��,��ȷ���Ƿ����key","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	//key_phSHandle = smart_DeviceHandle;
	LPSTR szAppName = "wellhope";
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szAppName,&phApplication))
	{
		MessageBox("��Ӧ��ʧ��","");
		return;
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userPin[32] = {0x00};
	LPSTR szUserPin = userPin;
	strcpy(szUserPin,m_loginPINedit);
	if(!keyDao.VerifyPIN(phApplication,type,szUserPin,&pulRetryCount))
	{
		MessageBox("PIN�����","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	/****************�������϶�����֤������ǲ��Ƕ�Ӧ��Key*********************/
	BYTE random[16]={0x00};
	if(!keyDao.GenRandom(smart_DeviceHandle,random,16))
	{
		MessageBox("���������ʧ��","");
		return;
	}
	LPSTR szContainerName = "LAB_USERCERT";
	HCONTAINER hcontainer;
	if(!keyDao.OpenContainer(phApplication,szContainerName,&hcontainer))
	{
		MessageBox("������ʧ��","");
		return;
	}
	ULONG pulContainerType=0;	
	if(!keyDao.GetContainerType(hcontainer,&pulContainerType))
	{				
		MessageBox("��ȡ��������ʧ�ܣ�","");
		return;
	}
	int  uiHashAlgo = 0;
	int seH = 0;
	HANDLE pHash = (void *)&seH;
	if(pulContainerType == 1)
	{
		uiHashAlgo = SGD_SHA1;
	}
	else if(pulContainerType == 2)
	{
		uiHashAlgo = SGD_SM3;
	}
	else
	{
		MessageBox("��ȡ��������ʧ�ܣ�","");
		return;
	}
	if(!keyDao.DigestInit(smart_DeviceHandle,uiHashAlgo/*ALG_SHA1*/,NULL,NULL,0,&pHash))
	{
		MessageBox("��ϣ��ʼ��ʧ��","");
		return;
	}
	BYTE pbHashData[32]={0x00};
	ULONG pulHashLen=sizeof(pbHashData);
	if(!keyDao.Digest(pHash,random,16,pbHashData,&pulHashLen))
	{
		MessageBox("��ϣʧ��","");
		return;
	}
	
	BYTE pbSignature[1024]={0x00};
	ULONG pulSignLen = sizeof(pbSignature);
	ECCSIGNATUREBLOB eccsignatureblob={0x00};
	if(pulContainerType == 1)
	{
		if(!keyDao.RSASignData(hcontainer,pbHashData,pulHashLen,pbSignature,&pulSignLen))
		{
			MessageBox("ǩ��ʧ��","");
			return;
		}
	}
	else if(pulContainerType == 2)
	{
		if(!keyDao.ECCSignData(hcontainer,pbHashData,pulHashLen,&eccsignatureblob))
		{
			MessageBox("ǩ��ʧ��","");
			return;
		}
	}
	else
	{
		MessageBox("��ȡ��������ʧ�ܣ�","");
		return;
	}

	FILEATTRIBUTE fileattribute={0x00};
	LPSTR szFile = "LBL_CERT_admin";
	if(!keyDao.GetFileInfo(phApplication,szFile,&fileattribute))
	{
		MessageBox("��ȡ�ļ���Ϣʧ��","");
		return;
	}
	BYTE pbOutData[1024]={0x00};
	ULONG pulOutLen = sizeof(pbOutData);
	//pbOutData = new BYTE[pulOutLen];
	if(!keyDao.ReadFile(phApplication,szFile,0,fileattribute.FileSize,pbOutData,&pulOutLen))
	{
		MessageBox("��ȡǩ��ֵʧ��","");
		return;
	}
	int ret = 0;
	int hand = 12;
	void * phSessionHandle = (void *)hand;

	memcpy(uiIP,m_ip,m_ip.GetLength());

	BYTE ind[256]={0x00};
	ULONG len = sizeof(ind);
	szFile = "LBL_CERT_adminIndex";
	if(!keyDao.GetFileInfo(phApplication,szFile,&fileattribute))
	{
		MessageBox("��ȡ�ļ���Ϣʧ��","");
		return;
	}
	if(!keyDao.ReadFile(phApplication,szFile,0,fileattribute.FileSize,ind,&len))
//	if(!keyDao.ReadFile(phApplication,"LBL_CERT_adminIndex",0,10,ind,&len))
	{
		MessageBox("��ȡ����Ա���к�ʧ��","");
		return;
	}
	keyDao.Logout(phApplication);
	keyDao.CloseDevice(smart_DeviceHandle);

	adm_index_for_enable = atoi((const char*)ind);//��󲻿ɲ����Ǹ����־ʹ����ﴫ��
	int equal1 = -1,equal2 = -1;
	if(1 == i_adm) memcpy(adm_k_Num_1,ind,1);
	if(2 == i_adm) 
	{
		memcpy(adm_k_Num_2,ind,1);
		equal1 = strncmp(adm_k_Num_1,adm_k_Num_2,1);
	}
	if(3 == i_adm)
	{
		memcpy(adm_k_Num_3,ind,1);
		equal1 = strncmp(adm_k_Num_1,adm_k_Num_3,1);
		equal2 = strncmp(adm_k_Num_2,adm_k_Num_3,1);
	}
	if(2 == i_adm && !equal1 || 3 == i_adm && (!equal2 || !equal1))
	{
		MessageBox("�ù���Ա�Ѿ���¼���������һ������Աkey��","",MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	char index[10]={0x00};
	memcpy(index,ind,10);
	unsigned int uiAdminId = atoi(index);//Ӧ���Ƕ��ļ��ķ�ʽ������ǩ���ֵ

	//unsigned int uiHashAlgo = SGD_SHA1;
	unsigned int uiSignAlgo = 0;
	if(pulContainerType == 1)
		uiSignAlgo = SGD_RSA;
	else if(pulContainerType == 2)
		uiSignAlgo = SGD_SM2_1;
	unsigned char pucRandom[32] = {0x00};
	memcpy(pucRandom,random,sizeof(random));
	unsigned int uiRandomLength = sizeof(random);
	unsigned char pucRandomSign[1024] = {0x00};
	unsigned int uiRandomSignLength = 0;
	if(pulContainerType == 1)
	{
		memcpy(pucRandomSign,pbSignature,pulSignLen);
		uiRandomSignLength = pulSignLen;
	}
	else if(pulContainerType == 2)
	{
		memcpy(pucRandomSign,eccsignatureblob.r,64);
		memcpy(pucRandomSign+64,eccsignatureblob.s,64);
		uiRandomSignLength = sizeof(ECCSIGNATUREBLOB);
	}
	unsigned char pucDevSign[1024]={0x00};
	memcpy(pucDevSign,pbOutData,pulOutLen);
	unsigned int uiDevSignLength = pulOutLen;
	ret = Km_LoginIn (&phSessionHandle,uiIP,uiAdminId,uiHashAlgo,uiSignAlgo,pucRandom,uiRandomLength,pucRandomSign,uiRandomSignLength,pucDevSign,uiDevSignLength);
	if(0 != ret)
	{
		memset(uiIP,0x00,32);
		char outLi[100]={0x00};
		retValueParse(ret,outLi);
		MessageBox(outLi,"��¼ʧ��",MB_ICONEXCLAMATION|MB_OK);
		return;
	}

	/***************���ö�ʱ��1����һ���������ӣ������쳣����ת����¼����*****************/

	SetTimer(1,3000,NULL);

	
	

	/******************************************************/

	//��ȡ�ͻ������ͣ������������ϵͳ��ҳ����ǩ����������ҳ
	//��ʱ����һ������˽ӿڷ��صĳ��Σ�������ʱ�������ļ��������������ҳ����ʾ
	int mngrTtype = 0;
	Cph_PWMngrDlg::GetMngrType(&mngrTtype);
	CString the_MainTitle;
	if(1 == mngrTtype)
		the_MainTitle = PWMMNGR_CAPTION_SIG;
	else if(0 == mngrTtype)
		the_MainTitle = PWMMNGR_CAPTION;

	BOOL isLoginOK = FALSE;
	int admMax_forLogin = 0;
	if(0 == ret)
	{
		phSHandle = phSessionHandle;//������Ự�������
		DEVKEYINFO devInfo={0x00};
		ret = Km_GetDevKeyInfo(phSHandle,&devInfo);                                                                   
		admMax_forLogin = devInfo.uiBakTotalKey;
	}
	double i_adm_log_num = 0.5*admMax_forLogin+1;
	if(0 == ret && 1 == admMax_forLogin)
	{
		this->OnOK();
		//CMainMenuDlg mainmenudlg(mngrTtype,type_mnger,admMax_forLogin,adm_index_for_enable,phSHandle,the_MainTitle);
		CMainMenuDlg mainmenudlg(mngrTtype,type_mnger,admMax_forLogin,adm_index_for_enable,phSHandle,the_MainTitle,uiIP);
		mainmenudlg.DoModal();
		return;
	}
	if(0 == ret && 1 < admMax_forLogin)
	{
		CString cur_adm,cur_adm_1;
		if(i_adm < i_adm_log_num)
		{
			cur_adm.Format("%d",i_adm);
			cur_adm_1.Format("%d",i_adm+1);
			MessageBox("��"+cur_adm+"����Ա��¼�ɹ�!���¼��"+cur_adm_1+"������Ա","��ʾ");
		}
		i_adm++;
		this->OnOK();
		if(i_adm <= i_adm_log_num)
		{
			Cph_PWMngrDlg loginDlg(uiIP,i_adm,NULL,NULL,NULL,"�Ϻ��ջ�����ϵͳ  Version 2.0");
			loginDlg.DoModal();
		}
		else
			isLoginOK = TRUE;
	}
	else
	{
		
		MessageBox(_T("�������"),_T(""));
		return;
	}
	if(isLoginOK)
	{
		this->OnOK();
		//MessageBox("ȫ������Ա��¼�ɹ�","��ʾ");
		//CMainMenuDlg mainmenudlg(mngrTtype,type_mnger,admMax_forLogin,adm_index_for_enable,phSHandle,the_MainTitle);
		CMainMenuDlg mainmenudlg(mngrTtype,type_mnger,admMax_forLogin,adm_index_for_enable,phSHandle,the_MainTitle,uiIP);
		mainmenudlg.DoModal();
		return;
	}
}


void Cph_PWMngrDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void Cph_PWMngrDlg::GetMaxAdminLogin(double *num)
{
	int ret;
	if(num == NULL)
		return;
	DEVKEYINFO devInfo={0x00};
	ret = Km_GetDevKeyInfo(phSHandle,&devInfo);
	if(0 != ret)
	{
		MessageBox("��ȡ������Ա��ʧ��","");
		return;
	}
	*num = 0.5*devInfo.uiBakTotalKey+1;
}


void Cph_PWMngrDlg::OnClickedSysinitStatic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������ʼ����
	this->OnOK();
	CSystemSmartKey syssckeyDlg(0);
	syssckeyDlg.DoModal();
	
}

void Cph_PWMngrDlg::GetMngrType(int *num)
{
	int length=0;

	CMyUtil::ReadData("./config.txt",NULL,&length);
	BYTE *data = new BYTE[length+1];
	memset(data,0x00,length+1);
	CMyUtil::ReadData("./config.txt",data,&length);

	char *str = strstr((char *)data,"MNGR_TYPE=");
	char *str2 = strstr(str,"\n");
	char *str3 = str + sizeof("MNGR_TYPE=") - 1;
	char buf[32]={0x00};
	memcpy(buf,str3,1);
	*num = atoi(buf);
}



void Cph_PWMngrDlg::OnStnClickedStaticResigadmin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ˡ�����ǩ������Ա��
	this->OnOK();
	CSystemSmartKey syssckeyDlg(1);
	syssckeyDlg.DoModal();
}
BOOL ConnectStatus=FALSE;//�ж������������

void Cph_PWMngrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	UpdateData(TRUE);
	int ret = 0;
	char IP[32] = {0x00};
	int port = PORT;
	memcpy(IP,m_ip,m_ip.GetLength());
	int sockfd = -1;
	void *phSessionHandle = phSHandle;

	
	/*********************ͨ����־״̬������״̬�ж�ʲôʱ����ת��¼����*******************************/
	ret = socket_conn(IP,port,&sockfd);
	if(0 == ret)
	{
		//�ر��׽���
		socket_close(sockfd);
		ConnectStatus = TRUE;
	}
	else if(TRUE == ConnectStatus && 0 != ret)//------
	{
		//�ر��׽���
		ConnectStatus = FALSE;
		//-----------------�رյ�ǰ����
		//closeWindows();
		
		//��ת����¼����
		Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
			
		if(IDOK != ph_PWMMngrDlg.DoModal())
		{
		
			return;
		}
		
		
	}
	/************************************************************************************************/
	CDialogEx::OnTimer(nIDEvent);
}

void Cph_PWMngrDlg::closeWindows()
{
	//this->OnOK();
	//OnBnClickedCancel();
		//AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);//�ر����Ի���
		//CWnd* pOldWnd = CWnd::FromHandle(GetActiveWindow ());//��õ�ǰ�����,���Ϊ������,����!
		//CWnd *pWnd = CWnd::GetActiveWindow();
		//HWND hWnd = ::FindWindowA(NULL,NULL);
		//HWND hWnd = ::GetForegroundWindow();
		HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();  //��������ڵľ��
		::DestroyWindow(hwnd);    // 
		//SendMessageA(WM_CLOSE,NULL,NULL);
	/*AfxGetMainWnd()->m_hWnd;
	::SendMessageA(AfxGetMainWnd()->m_hWnd,WM_CLOSE,0,NULL);*/
		// ::PostMessage(hwnd,WM_CLOSE, NULL, NULL);
		 // EndDialog(0);
		 // CDialog::OnClose(); //�رմ��� 

		 
		//AfxGetMainWnd()->SendMessage(WM_CLOSE);// �˳�������
		//DestroyWindow();//�رյ�ǰ������
		//EndDialog(0);//�ر�ģʽ�Ի�����


}
