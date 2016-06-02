// VerifyStrategyFour.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyFour.h"
#include "afxdialogex.h"


// CVerifyStrategyFour �Ի���


//unsigned int CertStand = 0 ;
//unsigned int talkType = 0;
IMPLEMENT_DYNAMIC(CVerifyStrategyFour, CDialogEx)

CVerifyStrategyFour::CVerifyStrategyFour(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVerifyStrategyFour::IDD, pParent)
	, m_ip_vs4(_T(""))
	, m_url_vs4(_T(""))
	, m_port_vs4(_T(""))
{

}

CVerifyStrategyFour::~CVerifyStrategyFour()
{
}

void CVerifyStrategyFour::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_vs4_ip, m_ip_vs4);
	DDX_Text(pDX, IDC_EDIT_url_vs4, m_url_vs4);
	DDX_Text(pDX, IDC_EDIT_vs4Port,m_port_vs4);
	DDX_Control(pDX, IDC_EDIT_vs4_ip, m_VS4ip_Control);
	DDX_Control(pDX, IDC_EDIT_vs4Port, m_VS4port_Control);
	DDX_Control(pDX, IDC_EDIT_url_vs4, m_VS4url_Control);
	DDX_Control(pDX, IDC_RADIO1, m_RADIO_GUOMI_Control);
	DDX_Control(pDX, IDC_RADIO2, m_RADIO_SHUIZ_Control);
	DDX_Control(pDX, IDC_RADIO4, m_RADIO_Socket_Control);
	DDX_Control(pDX, IDC_RADIO5, m_RADIO_Web_Control);
	//DDX_Control(pDX, IDC_BUTTON_vs4_1, m_RADIO_Web_Control);
}


BEGIN_MESSAGE_MAP(CVerifyStrategyFour, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_vs4_1, &CVerifyStrategyFour::OnBnClickedButtonvs41)
	ON_BN_CLICKED(IDC_RADIO1, &CVerifyStrategyFour::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CVerifyStrategyFour::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CVerifyStrategyFour::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CVerifyStrategyFour::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CVerifyStrategyFour::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CVerifyStrategyFour::OnBnClickedRadio6)
END_MESSAGE_MAP()


// CVerifyStrategyFour ��Ϣ�������


BOOL CVerifyStrategyFour::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//------------------������ť���
	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//unsigned int CertStand_vs4 = 0;
	//unsigned int talkType_vs4 = 0;
	//CString IP_vs4;
	//CString Port_vs4;
	//CString Url_vs4;
	////-------------------ͨ������˽ӿڻ�ȡ�ϴ�ѡ��ı�׼��ͨѶ��ʽ��ip url �˿ںŲ���ʾ

	//
	//if( 1== CertStand_vs4)//------------���ܱ�׼
	//{
	//	CheckDlgButton(IDC_RADIO1, 1);
	//	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);//IDC_XXXΪ�����ҵİ�ť��ID
	//	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	//	if(talkType_vs4  == 4)//-------------SocketͨѶ
	//	{
	//		CheckDlgButton(IDC_RADIO4, 4);
	//		m_VS4ip_Control.EnableWindow(TRUE);
	//		m_VS4port_Control.EnableWindow(TRUE);
	//		m_VS4url_Control.EnableWindow(FALSE);
	//		SetDlgItemText(IDC_EDIT_vs4_ip,IP_vs4);
	//		SetDlgItemText(IDC_EDIT_vs4Port, Port_vs4);
	//	}
	//	else if(talkType_vs4  == 5)//------------WebserviceͨѶ
	//	{
	//		CheckDlgButton(IDC_RADIO5, 5);
	//		m_VS4ip_Control.EnableWindow(FALSE);
	//		m_VS4port_Control.EnableWindow(FALSE);
	//		m_VS4url_Control.EnableWindow(TRUE);
	//		SetDlgItemText(IDC_EDIT_url_vs4,Url_vs4);
	//	}
	//}
	//else if(2 == CertStand_vs4)//----------------˰���׼
	//{
	//	CheckDlgButton(IDC_RADIO1, 1);
	//	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXXΪ�����ҵİ�ť��ID
	//	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	//	if(talkType_vs4  == 4)//-------------SocketͨѶ
	//	{
	//		CheckDlgButton(IDC_RADIO4, 4);
	//		m_VS4ip_Control.EnableWindow(TRUE);
	//		m_VS4port_Control.EnableWindow(TRUE);
	//		m_VS4url_Control.EnableWindow(FALSE);
	//		SetDlgItemText(IDC_EDIT_vs4_ip,IP_vs4);
	//		SetDlgItemText(IDC_EDIT_vs4Port,Port_vs4);
	//	}
	//}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CVerifyStrategyFour::OnBnClickedButtonvs41()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	if( 1== CertStand)//------------���ܱ�׼
	{
		
		if(talkType  == 4)//-------------SocketͨѶ
		{
			if(m_ip_vs4.IsEmpty())
			{
				MessageBox("������IP��ַ��","��ʾ",MB_ICONEXCLAMATION);
				return;
			}
			if(m_port_vs4.IsEmpty())
			{
				MessageBox("������˿ںŵ�ַ��","��ʾ",MB_ICONEXCLAMATION);
				return;
			}
		}
	
		 if(talkType  == 5)//------------WebserviceͨѶ
		{
			if(m_url_vs4.IsEmpty())
			{
				MessageBox("�����������ַ��","��ʾ",MB_ICONEXCLAMATION);
				return;
			}
		}
	}
	else if(2 == CertStand)//----------------˰�ܱ�׼
	{
		
		if(talkType == 4)//-------------SocketͨѶ
		{
			if(m_ip_vs4.IsEmpty())
			{
				MessageBox("������IP��ַ��","��ʾ",MB_ICONEXCLAMATION);
				return;
			}
			if(m_port_vs4.IsEmpty())
			{
				MessageBox("������˿ںŵ�ַ��","��ʾ",MB_ICONEXCLAMATION);
				return;
			}
		}
	}



	ip_vs4 = m_ip_vs4;
	url_vs4 = m_url_vs4;
	port_vs4 = m_port_vs4;
	certstand = CertStand;
	talktype = talkType;
}
int CVerifyStrategyFour::GetDataVS4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(1 == m_RADIO_GUOMI_Control.GetCheck())
	{
		CertStand = 1;
	}
	else if(1 == m_RADIO_SHUIZ_Control.GetCheck())
	{ 
		CertStand = 2;
	}
	if(1 == m_RADIO_Socket_Control.GetCheck())
	{
		talkType = 4;
	}
	else if(1 == m_RADIO_Web_Control.GetCheck())
	{ 
		talkType = 5;
	}

	if(0 != CertStand)
	{
		if( 1== CertStand)//------------���ܱ�׼
		{
		
			if(talkType  == 4)//-------------SocketͨѶ
			{
				if(m_ip_vs4.IsEmpty())
				{
					MessageBox("������IP��ַ��","��ʾ",MB_ICONEXCLAMATION);
					return -1;
				}
				if(m_port_vs4.IsEmpty())
				{
					MessageBox("������˿ںŵ�ַ��","��ʾ",MB_ICONEXCLAMATION);
					return -1;
				}
			}
	
			 if(talkType  == 5)//------------WebserviceͨѶ
			{
				if(m_url_vs4.IsEmpty())
				{
					MessageBox("�����������ַ��","��ʾ",MB_ICONEXCLAMATION);
					return -1;
				}
			}
		}
		else if(2 == CertStand)//----------------˰�ܱ�׼
		{
		
			if(talkType == 4)//-------------SocketͨѶ
			{
				if(m_ip_vs4.IsEmpty())
				{
					MessageBox("������IP��ַ��","��ʾ",MB_ICONEXCLAMATION);
					return -1;
				}
				if(m_port_vs4.IsEmpty())
				{
					MessageBox("������˿ںŵ�ַ��","��ʾ",MB_ICONEXCLAMATION);
					return-1;
				}
			}
		}
		ip_vs4 = m_ip_vs4;
		url_vs4 = m_url_vs4;
		port_vs4 = m_port_vs4;
		certstand = CertStand;
		talktype = talkType;
	}
	else{
		certstand = CertStand;
		talktype = talkType;
	}
	return 0;
}

int CVerifyStrategyFour::GetIpUrlVS4(unsigned char *ip,unsigned int *iplen,unsigned char *url,unsigned int *urllen,
	unsigned char *port,unsigned int *portlen,
	unsigned int *Certstand,unsigned int *Talktype)
{
	
	//-----------------------------��ȡ����
	
	int ret=0;
	ret=CVerifyStrategyFour::GetDataVS4();

	//----------------------------------
	
		*iplen = ip_vs4.GetLength();
		if(ip != NULL)
			memcpy(ip,ip_vs4.GetBuffer(),ip_vs4.GetLength());
		*urllen = url_vs4.GetLength();
		if(url != NULL)
			memcpy(url,url_vs4.GetBuffer(),url_vs4.GetLength());
		*portlen = port_vs4.GetLength();
		if(port != NULL)
		{
			memcpy(port,port_vs4.GetBuffer(),port_vs4.GetLength());
		}
	
	*Talktype = talktype;
	*Certstand = certstand;

	return ret;
}


void CVerifyStrategyFour::SetIpUrlVs(unsigned char *ip,unsigned char *port,unsigned char *url,unsigned int talktypee,unsigned int certstandd)
{
	if((certstandd == 2)&&(talktypee == 4))
	{
		m_RADIO_SHUIZ_Control.SetCheck(1);
		m_RADIO_Socket_Control.SetCheck(1);
		CertStand = 2;//------------˰���׼
		GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXXΪ�����ҵİ�ť��ID
		//---------------------ѡ��˰�ܱ�׼ֱ����ʾsocketͨѶ��ʽ
		talkType = 4;//--------------socketͨѶ
		m_VS4ip_Control.EnableWindow(TRUE);
		m_VS4port_Control.EnableWindow(TRUE);
		m_VS4url_Control.EnableWindow(FALSE);
		
		if(ip != NULL)
			SetDlgItemText(IDC_EDIT_vs4_ip,CString(ip));
		if(port != NULL)
			SetDlgItemText(IDC_EDIT_vs4Port,CString(port));
	}
	if((certstandd == 1)&&(talktypee == 4))
	{
		m_RADIO_GUOMI_Control.SetCheck(1);
		m_RADIO_Socket_Control.SetCheck(1);
		CertStand = 1;
		talkType = 4;//--------------socketͨѶ
		m_VS4ip_Control.EnableWindow(TRUE);
		m_VS4port_Control.EnableWindow(TRUE);
		m_VS4url_Control.EnableWindow(FALSE);
		if(ip != NULL)
			SetDlgItemText(IDC_EDIT_vs4_ip,CString(ip));
		if(port != NULL)
			SetDlgItemText(IDC_EDIT_vs4Port,CString(port));
	}
	if((certstandd == 1)&&(talktypee == 5))
	{
		CertStand = 1;
		talkType = 5;//--------------WebServiceͨѶ
		m_VS4ip_Control.EnableWindow(FALSE);
		m_VS4port_Control.EnableWindow(FALSE);
		m_VS4url_Control.EnableWindow(TRUE);
		m_RADIO_GUOMI_Control.SetCheck(1);
		m_RADIO_Web_Control.SetCheck(1);	
		if(url != NULL)
			SetDlgItemText(IDC_EDIT_url_vs4,CString(url));
	}
}



void CVerifyStrategyFour::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CertStand = 1;//------------���ܱ�׼
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);//IDC_XXXΪ�����ҵİ�ť��ID
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);

}


void CVerifyStrategyFour::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CertStand = 2;//------------˰���׼
	/*m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);*/
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXXΪ�����ҵİ�ť��ID
	//---------------------ѡ��˰�ܱ�׼ֱ����ʾsocketͨѶ��ʽ
	talkType = 4;//--------------socketͨѶ
	CheckDlgButton(IDC_RADIO4, 4);
	m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);
}


void CVerifyStrategyFour::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*m_VS4ip_Control.EnableWindow(FALSE);
	m_VS4port_Control.EnableWindow(FALSE);
	m_VS4url_Control.EnableWindow(FALSE);*/
}


void CVerifyStrategyFour::OnBnClickedRadio4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	talkType = 4;//--------------socketͨѶ
	m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);
}


void CVerifyStrategyFour::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	talkType = 5;//--------------WebServiceͨѶ
	m_VS4ip_Control.EnableWindow(FALSE);
	m_VS4port_Control.EnableWindow(FALSE);
	m_VS4url_Control.EnableWindow(TRUE);
}


void CVerifyStrategyFour::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
