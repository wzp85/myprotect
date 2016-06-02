// CheckKeyManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "CheckKeyManager.h"
#include "afxdialogex.h"
#include "Myutil.h"
#include "keyDao.h"

// CCheckKeyManager �Ի���

IMPLEMENT_DYNAMIC(CCheckKeyManager, CDialogEx)

CCheckKeyManager::CCheckKeyManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckKeyManager::IDD, pParent)
	, m_ckmPINedit(_T(""))
	, m_ckmPIN_edit(_T(""))
{

}

CCheckKeyManager::~CCheckKeyManager()
{
}

void CCheckKeyManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ckm_pin, m_ckm_pin);

	DDX_Text(pDX, IDC_EDIT_ckm_pin, m_ckmPIN_edit);
}


BEGIN_MESSAGE_MAP(CCheckKeyManager, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCheckKeyManager::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCheckKeyManager::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCheckKeyManager ��Ϣ�������


void CCheckKeyManager::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	/***********�ȴ������ļ����ȡǩ��ǩ����Կ��ȨԱ����ǩ������Ҫ��֤**************/
	int length = 0;
	int KMnger = 0;
	/*CMyUtil::ReadData("./config.txt",NULL,&length);
	if(length==0)
	{
		MessageBox("��ȡ�ļ�ʧ�ܣ���رչ����������ԣ�","��ʾ",MB_ICONWARNING | MB_OK);
	   return ;
	}
	BYTE *data = new BYTE[length + 1];
	memset(data,0x00,length + 1);
	CMyUtil::ReadData("./config.txt",data,&length);
	
	char *source = (char*)data;
	*/
	char *source = (char*)pConfigData;
	char *str = strstr(source,"KEY_MANAGER_SQ=");
	char *tem = str + strlen("KEY_MANAGER_SQ=");
	char *end = strstr(tem,"\n");
	char kmnger_buf[32] = {0x00};
	memcpy(kmnger_buf,tem,end-tem);
	KMnger = atoi(kmnger_buf);
	if(1 != KMnger)
	{
		return ;
	}
	
	//��֤����PIN���ʽ�Ƿ�Ϊ��
	UpdateData(TRUE);

	if(m_ckmPIN_edit.IsEmpty())
	{
		MessageBox("PIN�벻��Ϊ�գ�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	
	//����ǩ�ж��ǲ�����Կ��ȨԱ��key

	CKeyDao keyDao;
	char label[32] = {0x00};
	int nRes = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(nRes)
	{
		MessageBox("û�м�⵽��ϵͳ֧�ֵ�key����ȷ��key�Ƿ��û������Ƿ��Ǳ�ϵͳ֧�ֵ�key","��ʾ",MB_ICONWARNING | MB_OK);
	}
	
	if(!strncmp(label,"��ȫ���Ա",12))
	{
		MessageBox("��������ǰ�ȫ���Աkey����ȷ�ϲ�����Կ��ȨԱkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"�豸����Ա",10))
	{
		MessageBox("����������豸����Աkey����ȷ�ϲ�����Կ��ȨԱkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strncmp(label,"��Կ������Կ",12))
	{
		MessageBox("�����������Կ������Կkey����ȷ�ϲ�����Կ��ȨԱkey��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	DEVHANDLE smart_DeviceHandle = 0;
	if(!keyDao.OpenDevice(&smart_DeviceHandle))
	{
		MessageBox("���豸ʧ��,��ȷ���Ƿ����key","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	
	LPSTR szAppName = "wellhope";
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(smart_DeviceHandle,szAppName,&phApplication))
	{
		MessageBox("��Ӧ��ʧ��");
		return;
	}
	
	ULONG pulRetryCount = 0;
	ULONG type = USER_TYPE;
	char userPin[32] = {0x00};
	LPSTR szUserPin = userPin;
	strcpy(szUserPin,m_ckmPIN_edit);
	if(!keyDao.VerifyPIN(phApplication,type,szUserPin,&pulRetryCount))
	{
		MessageBox("PIN�����","��ʾ",MB_ICONWARNING | MB_OK);
		return ;
	}
	MessageBox("��Կ��֤�ɹ�","��ʾ",MB_ICONWARNING | MB_OK);
	CDialogEx::OnOK();
}


void CCheckKeyManager::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	checkState=1;
	CDialogEx::OnCancel();
}

void CCheckKeyManager::getCheckState(int *state)
{
	*state=checkState;
}


BOOL CCheckKeyManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	checkState=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
