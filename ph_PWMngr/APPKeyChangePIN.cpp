// APPKeyChangePIN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "APPKeyChangePIN.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
// CAPPKeyChangePIN �Ի���

IMPLEMENT_DYNAMIC(CAPPKeyChangePIN, CDialogEx)

CAPPKeyChangePIN::CAPPKeyChangePIN(void *handle,CString index,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPKeyChangePIN::IDD, pParent)
	, m_currentpin(_T(""))
	, m_newpin(_T(""))
	, m_newpincon(_T(""))
{
	phHandle = handle;
	key_index_ch = index;
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
    "����"));                 // lpszFacename
}

CAPPKeyChangePIN::~CAPPKeyChangePIN()
{
}

void CAPPKeyChangePIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THELINE1_STATIC, m_line1);
	DDX_Text(pDX, IDC_CURRENTPIN_EDIT, m_currentpin);
	DDX_Text(pDX, IDC_NEWPIN_EDIT, m_newpin);
	DDX_Text(pDX, IDC_NEWPINCON_EDIT, m_newpincon);
	CWnd *cWnd = GetDlgItem(IDC_THELINE1_STATIC);
    cWnd->SetFont(&line1);
	cWnd->SetWindowText("�޸�˽Կʹ����Ȩ��");
}


BEGIN_MESSAGE_MAP(CAPPKeyChangePIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAPPKeyChangePIN::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAPPKeyChangePIN::OnBnClickedOk)
END_MESSAGE_MAP()


// CAPPKeyChangePIN ��Ϣ�������


void CAPPKeyChangePIN::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("�������޸ģ�"));
}

void CAPPKeyChangePIN::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(m_newpin.GetLength()<8)
	{
		MessageBox("PIN�볤�Ȳ���С��8λ��","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_newpin != m_newpincon)
	{
		MessageBox("����PIN�����벻һ�£�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_newpin))
	{
		MessageBox("PIN�벻��ȫ�����֣�","��ʾ",MB_ICONWARNING | MB_OK);
		return;
	}

	int ret = 0;
	void * hSessionHandle = phHandle;
	unsigned int uikeyIndex = atoi(key_index_ch);

	unsigned char pucOldKeyPasswd[32]={0};
	unsigned int uiOldKeyPasswdLength;
	int length = m_currentpin.GetLength();
	uiOldKeyPasswdLength = length;
	memcpy(pucOldKeyPasswd,m_currentpin.GetBuffer(),length);

	unsigned char pucNewKeyPasswd[32]={0};
	unsigned int uiNewKeyPasswdLength;
	length = m_newpin.GetLength();
	uiNewKeyPasswdLength = length;
	memcpy(pucNewKeyPasswd,m_newpin.GetBuffer(),length);

	ret = Km_AppKeyModPasswd(hSessionHandle,uikeyIndex,pucOldKeyPasswd,uiOldKeyPasswdLength,pucNewKeyPasswd,uiNewKeyPasswdLength);
	if(!ret)
	{
		MessageBox("  �޸Ŀ���ɹ�","��ʾ");
		this->OnOK();
		return;
	}
	else
	{
		char outAkmp[100]={0x00};
		retValueParse(ret,outAkmp);
		MessageBox("�޸Ŀ���ʧ�ܣ�"+(CString)outAkmp,"",MB_ICONEXCLAMATION);
		return ;
	}
	/*if(0x00090147 == ret)
	{
		MessageBox("  �û�������� ","",MB_ICONEXCLAMATION);
		return;
	}*/
	MessageBox(_T("�޸ĳɹ�"));
	CDialogEx::OnOK();
	
}
