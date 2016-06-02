// DevAdminKeyMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevAdminKeyMngr.h"
#include "afxdialogex.h"

#include "TIPFormat.h"
#include "MyUtil.h"
#include "KeyDAO.h"

// CDevAdminKeyMngr �Ի���

IMPLEMENT_DYNAMIC(CDevAdminKeyMngr, CDialogEx)

CDevAdminKeyMngr::CDevAdminKeyMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevAdminKeyMngr::IDD, pParent)
	, m_title(_T(""))
	, m_adminpin_unlock(_T(""))
	, m_admin_login(_T(""))
	, m_adminpin_old(_T(""))
	, m_adminpin_new(_T(""))
{
	VERIFY(font.CreateFont(
    15,                        // nHeight
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

CDevAdminKeyMngr::~CDevAdminKeyMngr()
{
}

void CDevAdminKeyMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CARRIERMNGR_TITLE_STATIC, m_title);
	CWnd *cWnd = GetDlgItem(IDC_CARRIERMNGR_TITLE_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("����ԱKEY����");

	DDX_Text(pDX, IDC_EDIT1, m_adminpin_unlock);
	DDX_Text(pDX, IDC_EDIT2, m_admin_login);
	DDX_Text(pDX, IDC_EDIT5, m_adminpin_old);
	DDX_Text(pDX, IDC_EDIT6, m_adminpin_new);
}


BEGIN_MESSAGE_MAP(CDevAdminKeyMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDevAdminKeyMngr::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDevAdminKeyMngr::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDevAdminKeyMngr::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDevAdminKeyMngr::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDevAdminKeyMngr ��Ϣ�������
BOOL CDevAdminKeyMngr::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CDevAdminKeyMngr::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isEmptyKey = FALSE;
	INT_PTR nRes=IDOK;             // ���ڱ���DoModal�����ķ���ֵ  
	int ret = 0;
	CTIPFormat tipFormatDlg;

	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(1 == ret)
	{
		MessageBox("���豸ʧ�ܣ���ȷ��key�Ƿ��ã�","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if(0 != ret && 1 != ret)
	{
		//MessageBox("����ǩ����","��ʾ");
		//MessageBox("��������ǿ�key��","��ʾ");
		//return;
		isEmptyKey = TRUE;
	}
	if(!strcmp(label,"�豸����Ա"))
	{
		nRes = MessageBox("����������豸����Աkey��ȷ��Ҫ��ʽ����","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
	}
	else if(!strncmp(label,"��Կ������Կ",12))
	{
		//nRes = MessageBox("�����������Կ������Կkey����ȷ���Ƿ�Ҫ��ʽ���������\n\rʽ��������key���ݹ�����Կ���޷��ָ����Ƿ������","��ʾ",MB_ICONEXCLAMATION|MB_OKCANCEL);
		nRes = tipFormatDlg.DoModal();
	}
	//else
	//{
	//	nRes = MessageBox("��������ǿ�key��ȷ��Ҫ��ʽ����","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
	//}
	if(!isEmptyKey && nRes != IDOK)
		return;
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{

	}
	if(!keyDao.DevAuth(smart_DeviceHandle))
	{
		MessageBox("��ʽ��ʧ��","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	LPSTR szAppName = "wellhope";
	LPSTR szAdminPin = "123456";
	DWORD dwAdminPinRetryCount = 6;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,"12345678");
	DWORD dwUserPinRetryCount = 10;
	DWORD dwCreateFileRights = SECURE_EVERYONE_ACCOUNT;
	HAPPLICATION application;	

	char appName[32]={0x00};
	LPSTR appNameLS = appName;
	ULONG handSize = 0;
	ULONG *thepulSize = &handSize;

	if(!keyDao.CreateApplication(smart_DeviceHandle,szAppName,szAdminPin,dwAdminPinRetryCount,szUserPin,dwUserPinRetryCount,dwCreateFileRights,&application))
	{
		MessageBox("��ʽ��ʧ��","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	
	if(!keyDao.CloseDevice(smart_DeviceHandle))
	{
		MessageBox("��ʽ��ʧ��","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}

	MessageBox("��ʽ���ɹ�","��ʾ");
}


void CDevAdminKeyMngr::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(m_admin_login.IsEmpty())
	{
		MessageBox("PIN�벻��Ϊ�գ�","",MB_ICONEXCLAMATION);
		return;
	}

	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userPin[32]={0x00};
	LPSTR szUserPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szUserPin,m_admin_login);
	if(!keyDao.VerifyPIN(phApplication,USER_TYPE,szUserPin,&pulRetryCount))
	{
		MessageBox("��¼ʧ�ܣ�","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("��¼�ɹ���","��ʾ");
}


void CDevAdminKeyMngr::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("    ����","");
	UpdateData(TRUE);
	
	if(m_adminpin_unlock.IsEmpty())
	{
		MessageBox("PIN�벻��Ϊ�գ�","",MB_ICONEXCLAMATION);
		return;
	}

	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = ADMIN_TYPE;
	char userPin[32]={0x00};
	LPSTR szAdminPin = userPin;
//	int size = m_adminPwd.GetLength();
	strcpy(szAdminPin,m_adminpin_unlock);
	if(!keyDao.VerifyPIN(phApplication,type,szAdminPin,&pulRetryCount))
	{
		MessageBox("��ȡ����ԱȨ��ʧ�ܣ����޷���ɽ�����","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	pulRetryCount = 0;
	if(!keyDao.UnblockPIN(phApplication,szAdminPin,"12345678",&pulRetryCount))
	{
		MessageBox("��ȡ����ԱȨ�޳ɹ����������û�PINʧ�ܣ�","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("����PIN�ɹ����µ�PIN��Ϊ12345678���뾡���޸ģ�","��ʾ",MB_ICONWARNING|MB_OK);
}


void CDevAdminKeyMngr::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("    �޸ĳɹ�","");
	UpdateData(TRUE);
	
	if(m_adminpin_old.IsEmpty() || m_adminpin_new.IsEmpty())
	{
		MessageBox("PIN�벻��Ϊ�գ�","",MB_ICONEXCLAMATION);
		return;
	}
	CKeyDao keyDao;
	DEVHANDLE smart_DeviceHandle;
	keyDao.OpenDevice(&smart_DeviceHandle);
	char name[256]={0x00};
	LPSTR szappName = name;
	ULONG sseH = sizeof(name);
	ULONG *pulSize = &sseH;
	keyDao.EnumApplication(smart_DeviceHandle,szappName,pulSize);
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szappName,&phApplication))
	{
		
	}
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userOldPin[32]={0x00};
	LPSTR szUserOldPin = userOldPin;
	strcpy(szUserOldPin,m_adminpin_old);
	char userNewPin[32]={0x00};
	LPSTR szUserNewPin = userNewPin;
	strcpy(szUserNewPin,m_adminpin_new);
	if(!keyDao.ChangePIN(phApplication,USER_TYPE,szUserOldPin,szUserNewPin,&pulRetryCount))
	{
		MessageBox("�޸�PIN��ʧ��","��ʾ",MB_ICONWARNING|MB_OK);
		return;
	}
	MessageBox("�޸�PIN��ɹ�","��ʾ");
}
