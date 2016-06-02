// VerifyStrategyFour.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStrategyFour.h"
#include "afxdialogex.h"


// CVerifyStrategyFour 对话框


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


// CVerifyStrategyFour 消息处理程序


BOOL CVerifyStrategyFour::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//------------------其他按钮变灰
	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);

	// TODO:  在此添加额外的初始化
	//unsigned int CertStand_vs4 = 0;
	//unsigned int talkType_vs4 = 0;
	//CString IP_vs4;
	//CString Port_vs4;
	//CString Url_vs4;
	////-------------------通过服务端接口获取上次选择的标准，通讯方式，ip url 端口号并显示

	//
	//if( 1== CertStand_vs4)//------------国密标准
	//{
	//	CheckDlgButton(IDC_RADIO1, 1);
	//	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);//IDC_XXX为你想变灰的按钮的ID
	//	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	//	if(talkType_vs4  == 4)//-------------Socket通讯
	//	{
	//		CheckDlgButton(IDC_RADIO4, 4);
	//		m_VS4ip_Control.EnableWindow(TRUE);
	//		m_VS4port_Control.EnableWindow(TRUE);
	//		m_VS4url_Control.EnableWindow(FALSE);
	//		SetDlgItemText(IDC_EDIT_vs4_ip,IP_vs4);
	//		SetDlgItemText(IDC_EDIT_vs4Port, Port_vs4);
	//	}
	//	else if(talkType_vs4  == 5)//------------Webservice通讯
	//	{
	//		CheckDlgButton(IDC_RADIO5, 5);
	//		m_VS4ip_Control.EnableWindow(FALSE);
	//		m_VS4port_Control.EnableWindow(FALSE);
	//		m_VS4url_Control.EnableWindow(TRUE);
	//		SetDlgItemText(IDC_EDIT_url_vs4,Url_vs4);
	//	}
	//}
	//else if(2 == CertStand_vs4)//----------------税务标准
	//{
	//	CheckDlgButton(IDC_RADIO1, 1);
	//	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXX为你想变灰的按钮的ID
	//	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	//	if(talkType_vs4  == 4)//-------------Socket通讯
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
	// 异常: OCX 属性页应返回 FALSE
}


void CVerifyStrategyFour::OnBnClickedButtonvs41()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	if( 1== CertStand)//------------国密标准
	{
		
		if(talkType  == 4)//-------------Socket通讯
		{
			if(m_ip_vs4.IsEmpty())
			{
				MessageBox("请输入IP地址！","提示",MB_ICONEXCLAMATION);
				return;
			}
			if(m_port_vs4.IsEmpty())
			{
				MessageBox("请输入端口号地址！","提示",MB_ICONEXCLAMATION);
				return;
			}
		}
	
		 if(talkType  == 5)//------------Webservice通讯
		{
			if(m_url_vs4.IsEmpty())
			{
				MessageBox("请输入网络地址！","提示",MB_ICONEXCLAMATION);
				return;
			}
		}
	}
	else if(2 == CertStand)//----------------税总标准
	{
		
		if(talkType == 4)//-------------Socket通讯
		{
			if(m_ip_vs4.IsEmpty())
			{
				MessageBox("请输入IP地址！","提示",MB_ICONEXCLAMATION);
				return;
			}
			if(m_port_vs4.IsEmpty())
			{
				MessageBox("请输入端口号地址！","提示",MB_ICONEXCLAMATION);
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
	// TODO: 在此添加控件通知处理程序代码
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
		if( 1== CertStand)//------------国密标准
		{
		
			if(talkType  == 4)//-------------Socket通讯
			{
				if(m_ip_vs4.IsEmpty())
				{
					MessageBox("请输入IP地址！","提示",MB_ICONEXCLAMATION);
					return -1;
				}
				if(m_port_vs4.IsEmpty())
				{
					MessageBox("请输入端口号地址！","提示",MB_ICONEXCLAMATION);
					return -1;
				}
			}
	
			 if(talkType  == 5)//------------Webservice通讯
			{
				if(m_url_vs4.IsEmpty())
				{
					MessageBox("请输入网络地址！","提示",MB_ICONEXCLAMATION);
					return -1;
				}
			}
		}
		else if(2 == CertStand)//----------------税总标准
		{
		
			if(talkType == 4)//-------------Socket通讯
			{
				if(m_ip_vs4.IsEmpty())
				{
					MessageBox("请输入IP地址！","提示",MB_ICONEXCLAMATION);
					return -1;
				}
				if(m_port_vs4.IsEmpty())
				{
					MessageBox("请输入端口号地址！","提示",MB_ICONEXCLAMATION);
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
	
	//-----------------------------获取数据
	
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
		CertStand = 2;//------------税务标准
		GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXX为你想变灰的按钮的ID
		//---------------------选择税总标准直接显示socket通讯形式
		talkType = 4;//--------------socket通讯
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
		talkType = 4;//--------------socket通讯
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
		talkType = 5;//--------------WebService通讯
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
	// TODO: 在此添加控件通知处理程序代码
	CertStand = 1;//------------国密标准
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);//IDC_XXX为你想变灰的按钮的ID
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);

}


void CVerifyStrategyFour::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	CertStand = 2;//------------税务标准
	/*m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);*/
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);//IDC_XXX为你想变灰的按钮的ID
	//---------------------选择税总标准直接显示socket通讯形式
	talkType = 4;//--------------socket通讯
	CheckDlgButton(IDC_RADIO4, 4);
	m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);
}


void CVerifyStrategyFour::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码

	/*m_VS4ip_Control.EnableWindow(FALSE);
	m_VS4port_Control.EnableWindow(FALSE);
	m_VS4url_Control.EnableWindow(FALSE);*/
}


void CVerifyStrategyFour::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	talkType = 4;//--------------socket通讯
	m_VS4ip_Control.EnableWindow(TRUE);
	m_VS4port_Control.EnableWindow(TRUE);
	m_VS4url_Control.EnableWindow(FALSE);
}


void CVerifyStrategyFour::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	talkType = 5;//--------------WebService通讯
	m_VS4ip_Control.EnableWindow(FALSE);
	m_VS4port_Control.EnableWindow(FALSE);
	m_VS4url_Control.EnableWindow(TRUE);
}


void CVerifyStrategyFour::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
}
