// VerifyStragegyTwo.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStragegyTwo.h"
#include "afxdialogex.h"


// CVerifyStragegyTwo 对话框
//unsigned int TypeVS2 = 0;
IMPLEMENT_DYNAMIC(CVerifyStragegyTwo, CDialogEx)

CVerifyStragegyTwo::CVerifyStragegyTwo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVerifyStragegyTwo::IDD, pParent)
	, m_LDAP_address(_T(""))
	, m_LDAP_port(_T(""))
	/*, m_LDAP_usrname(_T(""))
	, m_LDAP_pwd(_T(""))*/
	, m_timeinterval_vs2(_T(""))
	, m_timeinterval_hour_vs2(_T(""))
	, m_timeinterval_minute_vs2(_T(""))
	, m_timeinterval_second_vs2(_T(""))
	, m_LDAP_crlpath(_T(""))
	, m_Http_urlpath(_T(""))
	, m_httptimeterval_vs2(_T(""))
	, m_httptimetervar_minute_vs2(_T(""))
	, m_httptimetervar_second_vs2(_T(""))
	, m_httptimeterval_hour_vs2(_T(""))
{

}

CVerifyStragegyTwo::~CVerifyStragegyTwo()
{
}

void CVerifyStragegyTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_vs2_LDAPaddress, m_LDAP_address);//CString 变量获取控件信息
	DDX_Text(pDX, IDC_EDIT_vs2_Port, m_LDAP_port);
	/*DDX_Text(pDX, IDC_EDIT_vs2_USRNAME, m_LDAP_usrname);
	DDX_Text(pDX, IDC_EDIT_vs2_pwd, m_LDAP_pwd);*/
	DDX_Text(pDX, IDC_EDIT_CRLREL_vs2, m_timeinterval_vs2);
	DDX_Text(pDX, IDC_EDIT_HOUR_vs2, m_timeinterval_hour_vs2);
	DDX_Text(pDX, IDC_EDIT_MINUTE_vs3, m_timeinterval_minute_vs2);
	DDX_Text(pDX, IDC_EDIT_SECOND_vs2, m_timeinterval_second_vs2);
	DDX_Text(pDX, IDC_EDIT_vs2_crlpath, m_LDAP_crlpath);
	/*************http************/
	DDX_Text(pDX, IDC_EDIT_vs2_HTTP_URLPATH, m_Http_urlpath);
	DDX_Text(pDX, IDC_EDIT_HTTP_CRLREL_vs2, m_httptimeterval_vs2);
	DDX_Text(pDX, IDC_EDIT_HTTP_HOUR_vs2, m_httptimeterval_hour_vs2);
	DDX_Text(pDX, IDC_EDIT_HTTP_MINUTE_vs2, m_httptimetervar_minute_vs2);
	DDX_Text(pDX, IDC_EDIT_HTTP_SECOND_vs2, m_httptimetervar_second_vs2);
	/***************控件变量*************************/
	DDX_Control(pDX, IDC_EDIT_CRLREL_vs2, m_crlrel);//控件变量对控件变灰操作
	DDX_Control(pDX, IDC_EDIT_vs2_HTTP_URLPATH, m_vs2_http_urlpath);
	DDX_Control(pDX, IDC_EDIT_HTTP_CRLREL_vs2, m_http_day);
	DDX_Control(pDX, IDC_EDIT_HTTP_HOUR_vs2, m_http_hour);
	DDX_Control(pDX, IDC_EDIT_HTTP_MINUTE_vs2, m_http_minute);
	DDX_Control(pDX, IDC_EDIT_HTTP_SECOND_vs2, m_http_second);
	DDX_Control(pDX, IDC_EDIT_vs2_LDAPaddress, m_ldapaddress);
	DDX_Control(pDX, IDC_EDIT_vs2_Port, m_ldapPort);
	/*DDX_Control(pDX, IDC_EDIT_vs2_USRNAME, m_ldapUsername);
	DDX_Control(pDX, IDC_EDIT_vs2_pwd, m_ldpa_pwd);*/
	DDX_Control(pDX, IDC_EDIT_vs2_crlpath, m_ldapurlpath);
	DDX_Control(pDX, IDC_EDIT_HOUR_vs2, m_ldapHour);
	DDX_Control(pDX, IDC_EDIT_MINUTE_vs3, m_ldapMinute);
	DDX_Control(pDX, IDC_EDIT_SECOND_vs2, m_ldapSecond);
	/*DDX_Control(pDX, IDC_BUTTON_vs2_1, m_ldap);
	DDX_Control(pDX, IDC_BUTTON_vs2_1, m_ldap_radio);*/

	DDX_Control(pDX, IDC_RADIO_HTTP, m_http_radio);
	DDX_Control(pDX, IDC_RADIO_LDAP, m_ldap_radio);
}


BEGIN_MESSAGE_MAP(CVerifyStragegyTwo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_vs2_1, &CVerifyStragegyTwo::OnBnClickedButtonvs21)
//	ON_EN_CHANGE(IDC_EDIT_HTTP_HOUR_vs2, &CVerifyStragegyTwo::OnEnChangeEditHttpHourvs2)
	ON_BN_CLICKED(IDC_RADIO_HTTP, &CVerifyStragegyTwo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO_LDAP, &CVerifyStragegyTwo::OnBnClickedRadio1)
//	ON_EN_CHANGE(IDC_EDIT_vs2_LDAPaddress, &CVerifyStragegyTwo::OnEnChangeEditvs2Ldapaddress)
END_MESSAGE_MAP()


// CVerifyStragegyTwo 消息处理程序


BOOL CVerifyStragegyTwo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	TypeVS2 = 0;
		//CheckDlgButton(IDC_RADIO_LDAP, 1);
	//m_http_day.EnableWindow(FALSE);
	//m_vs2_http_urlpath.EnableWindow(FALSE);
	//m_http_minute.EnableWindow(FALSE);
	//m_http_second.EnableWindow(FALSE);
	//m_http_hour.EnableWindow(FALSE);


	//m_ldapaddress.EnableWindow(TRUE);
	//m_ldapPort.EnableWindow(TRUE);
	///*m_ldapUsername.EnableWindow(TRUE);
	//m_ldpa_pwd.EnableWindow(TRUE);*/
	//m_ldapurlpath.EnableWindow(TRUE);
	//m_crlrel.EnableWindow(TRUE);//这是ldap的天数控件变量
	//m_ldapHour.EnableWindow(TRUE);
	//m_ldapMinute.EnableWindow(TRUE);
	//m_ldapSecond.EnableWindow(TRUE);
	//CVerifyStragegyTwo::OnBnClickedRadio1();
	 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CVerifyStragegyTwo::OnBnClickedButtonvs21()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int	days=0;
	unsigned int	hour=0;
	unsigned int	minute=0;
	unsigned int	second=0;
	
	unsigned int	http_days=0;
	unsigned int	http_hour=0;
	unsigned int	http_minute=0;
	unsigned int	http_second=0;
	UpdateData(TRUE);
	if(1 == TypeVS2)//Ldap信息获取
	{
			if(m_LDAP_address.IsEmpty())//LDAP
		{
			MessageBox("请输入服务器地址！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(m_LDAP_port.IsEmpty())
		{
			MessageBox("请输入服务器端口号！","提示",MB_ICONEXCLAMATION);
			return;
		}
		/*if(!m_LDAP_usrname.IsEmpty() && m_LDAP_usrname.GetLength()>20)
		{
			MessageBox("用户名不能超过20个字符！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(!m_LDAP_pwd.IsEmpty() && m_LDAP_pwd.GetLength()>20)
		{
			MessageBox("口令不能超过20个字符！","提示",MB_ICONEXCLAMATION);
			return;
		}*/
		if(m_LDAP_crlpath.IsEmpty())
		{
			MessageBox("请输入crl路径！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(m_LDAP_crlpath.IsEmpty() && m_LDAP_crlpath.GetLength()>100)
		{
			MessageBox("crl路径不能超过100个字符！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(m_timeinterval_vs2.IsEmpty() && m_timeinterval_hour_vs2.IsEmpty() && m_timeinterval_minute_vs2.IsEmpty() && m_timeinterval_second_vs2.IsEmpty())
		{
			MessageBox("请设置时间间隔！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(!m_LDAP_address.IsEmpty())//LDAP
			address = m_LDAP_address;
		if(!m_LDAP_port.IsEmpty())
			port = m_LDAP_port;
		/*if(!m_LDAP_usrname.IsEmpty())
			name = m_LDAP_usrname;
		if(m_LDAP_usrname.IsEmpty())
			name = "NONAME";
		if(!m_LDAP_pwd.IsEmpty())
			pwd = m_LDAP_pwd;
		if(m_LDAP_pwd.IsEmpty())
			pwd = "NONAME";*/
		if(!m_LDAP_crlpath.IsEmpty())
			crlpath=m_LDAP_crlpath;

		if(!m_timeinterval_vs2.IsEmpty())
		{
			t_day_cache=m_timeinterval_vs2;
			http_days = atoi(m_timeinterval_vs2);
		}
		if(!m_timeinterval_hour_vs2.IsEmpty())
		{
			hour = atoi(m_timeinterval_hour_vs2);
			t_hour_cache = m_timeinterval_hour_vs2;
		}
		if(!m_timeinterval_minute_vs2.IsEmpty())
		{
			minute = atoi(m_timeinterval_minute_vs2);
			t_minute_cache = m_timeinterval_minute_vs2;
		}
		if(!m_timeinterval_second_vs2.IsEmpty())
		{
			second = atoi(m_timeinterval_second_vs2);
			t_second_cache = m_timeinterval_second_vs2;
		}
		timeinterval=days*24*60*60 + hour*60*60 + minute*60 + second;

	}
	
	/***************http信息获取*********************************/
	if(2 == TypeVS2)
	{
		if(m_Http_urlpath.IsEmpty())
		{
			MessageBox("请输入url路径！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(m_Http_urlpath.IsEmpty() && m_Http_urlpath.GetLength()>100)
		{
			MessageBox("url路径不能超过100个字符！","提示",MB_ICONEXCLAMATION);
			return;
		}
		if(m_httptimeterval_vs2.IsEmpty() && m_httptimeterval_hour_vs2.IsEmpty() && m_httptimetervar_minute_vs2.IsEmpty() && m_httptimetervar_second_vs2.IsEmpty())
		{
			MessageBox("请设置时间间隔！","提示",MB_ICONEXCLAMATION);
			return;
		}
	
		/*****************htttp路径时间间隔判断*********************************/
		if(!m_Http_urlpath.IsEmpty())
			http_urlpath=m_Http_urlpath;

		if(!m_httptimeterval_vs2.IsEmpty())
		{
			http_day_cache=m_httptimeterval_vs2;
			http_days = atoi(m_httptimeterval_vs2);
		}
		if(!m_httptimeterval_hour_vs2.IsEmpty())
		{
			http_hour = atoi(m_httptimeterval_hour_vs2);
			http_hour_cache =m_httptimeterval_hour_vs2;
		}
		if(!m_httptimetervar_minute_vs2.IsEmpty())
		{
			http_minute = atoi(m_httptimetervar_minute_vs2);
			http_minute_cache = m_httptimetervar_minute_vs2;
		}
		if(!m_httptimetervar_second_vs2.IsEmpty())
		{
			http_second = atoi(m_httptimetervar_second_vs2);
			http_second_cache = m_httptimetervar_second_vs2;
		}
		httptimeterval=http_days*24*60*60 + http_hour*60*60 + http_minute*60 + http_second;

	}

}

int CVerifyStragegyTwo::GetDataVS2()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int	days=0;
	unsigned int	hour=0;
	unsigned int	minute=0;
	unsigned int	second=0;
	
	unsigned int	http_days=0;
	unsigned int	http_hour=0;
	unsigned int	http_minute=0;
	unsigned int	http_second=0;
	UpdateData(TRUE);
	if(1 == m_ldap_radio.GetCheck())
	{
		TypeVS2 = 1;
	}
	else if(1 == m_http_radio.GetCheck())
	{ 
		TypeVS2 = 2;
	}
	if(0 != TypeVS2)
	{
		if(1 == TypeVS2)//Ldap信息获取
		{
				if(m_LDAP_address.IsEmpty())//LDAP
			{
				MessageBox("请输入服务器地址！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			if(m_LDAP_port.IsEmpty())
			{
				MessageBox("请输入服务器端口号！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			/*if(!m_LDAP_usrname.IsEmpty() && m_LDAP_usrname.GetLength()>20)
			{
				MessageBox("用户名不能超过20个字符！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			if(!m_LDAP_pwd.IsEmpty() && m_LDAP_pwd.GetLength()>20)
			{
				MessageBox("口令不能超过20个字符！","提示",MB_ICONEXCLAMATION);
				return -1;
			}*/
			if(m_LDAP_crlpath.IsEmpty())
			{
				MessageBox("请输入crl路径！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			if(m_LDAP_crlpath.IsEmpty() && m_LDAP_crlpath.GetLength()>100)
			{
				MessageBox("crl路径不能超过100个字符！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			if(m_timeinterval_vs2.IsEmpty() && m_timeinterval_hour_vs2.IsEmpty() && m_timeinterval_minute_vs2.IsEmpty() && m_timeinterval_second_vs2.IsEmpty())
			{
				MessageBox("请设置时间间隔！","提示",MB_ICONEXCLAMATION);
				return -1;
			}
			if(!m_LDAP_address.IsEmpty())//LDAP
				address = m_LDAP_address;
			if(!m_LDAP_port.IsEmpty())
				port = m_LDAP_port;
			/*if(!m_LDAP_usrname.IsEmpty())
				name = m_LDAP_usrname;
			if(m_LDAP_usrname.IsEmpty())
				name = "NONAME";
			if(!m_LDAP_pwd.IsEmpty())
				pwd = m_LDAP_pwd;
			if(m_LDAP_pwd.IsEmpty())
				pwd = "NONAME";*/
			if(!m_LDAP_crlpath.IsEmpty())
				crlpath=m_LDAP_crlpath;

			if(!m_timeinterval_vs2.IsEmpty())
			{
				t_day_cache=m_timeinterval_vs2;
				http_days = atoi(m_timeinterval_vs2);
			}
			if(!m_timeinterval_hour_vs2.IsEmpty())
			{
				hour = atoi(m_timeinterval_hour_vs2);
				t_hour_cache = m_timeinterval_hour_vs2;
			}
			if(!m_timeinterval_minute_vs2.IsEmpty())
			{
				minute = atoi(m_timeinterval_minute_vs2);
				t_minute_cache = m_timeinterval_minute_vs2;
			}
			if(!m_timeinterval_second_vs2.IsEmpty())
			{
				second = atoi(m_timeinterval_second_vs2);
				t_second_cache = m_timeinterval_second_vs2;
			}
			timeinterval=http_days*24*60*60 + hour*60*60 + minute*60 + second;

	}
	
	/***************http信息获取*********************************/
	if(2 == TypeVS2)
	{
		if(m_Http_urlpath.IsEmpty())
		{
			MessageBox("请输入url路径！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		if(m_Http_urlpath.IsEmpty() && m_Http_urlpath.GetLength()>100)
		{
			MessageBox("url路径不能超过100个字符！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		if(m_httptimeterval_vs2.IsEmpty() && m_httptimeterval_hour_vs2.IsEmpty() && m_httptimetervar_minute_vs2.IsEmpty() && m_httptimetervar_second_vs2.IsEmpty())
		{
			MessageBox("请设置时间间隔！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
	
		/*****************htttp路径时间间隔判断*********************************/
		if(!m_Http_urlpath.IsEmpty())
			http_urlpath=m_Http_urlpath;

		if(!m_httptimeterval_vs2.IsEmpty())
		{
			http_day_cache=m_httptimeterval_vs2;
			http_days = atoi(m_httptimeterval_vs2);
		}
		if(!m_httptimeterval_hour_vs2.IsEmpty())
		{
			http_hour = atoi(m_httptimeterval_hour_vs2);
			http_hour_cache =m_httptimeterval_hour_vs2;
		}
		if(!m_httptimetervar_minute_vs2.IsEmpty())
		{
			http_minute = atoi(m_httptimetervar_minute_vs2);
			http_minute_cache = m_httptimetervar_minute_vs2;
		}
		if(!m_httptimetervar_second_vs2.IsEmpty())
		{
			http_second = atoi(m_httptimetervar_second_vs2);
			http_second_cache = m_httptimetervar_second_vs2;
		}
		httptimeterval=http_days*24*60*60 + http_hour*60*60 + http_minute*60 + http_second;

	}
	}
	return 0;

}
int CVerifyStragegyTwo::GetVS2(unsigned char *ldapaddr,unsigned int *ldapaddrlen,unsigned char *ldapport,unsigned int *ldapportlen,
								/*unsigned char *ldapname,unsigned int *ldapnamelen,unsigned char *ldappwd,unsigned int *ldappwdlen,*/
								unsigned char *ldapcrlpath,unsigned int *ldapcrlpathlen,unsigned int *timeinterval_ldap,unsigned char *httpcrlpath,
				unsigned int *httpcrlpathlen,unsigned int *timeinterval_HTTP,unsigned int *  oType)
{
	//--------------------------------获取界面信息
	CVerifyStragegyTwo::GetDataVS2();
	//-------------------------------------------
	
	if(1 == m_ldap_radio.GetCheck())
	{
		TypeVS2 = 1;
	}
	else if(1 == m_http_radio.GetCheck())
	{ 
		TypeVS2 = 2;
	}
	if( 1==TypeVS2)
	{
		if(address.IsEmpty())
		{
			MessageBox("请输入服务器地址！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		if(port.IsEmpty())
		{

			MessageBox("请输入服务器端口号！","提示",MB_ICONEXCLAMATION);
			return -1;
		}
		*ldapaddrlen = address.GetLength();//add by syc
		if(ldapaddr != NULL)
			memcpy(ldapaddr,address.GetBuffer(),address.GetLength());
		*ldapportlen = port.GetLength();
		if(ldapport != NULL)
			memcpy(ldapport,port.GetBuffer(),port.GetLength());

		/*if(!name.IsEmpty())
		{
			*ldapnamelen = name.GetLength();
			if(ldapname != NULL)
				memcpy(ldapname,name.GetBuffer(),name.GetLength());
		}
		if(name.IsEmpty())
		{
			*ldapnamelen = 10;
			if(ldapname != NULL)
				memcpy(ldapname,"NONAME",sizeof("NONAME"));
		}
		if(!pwd.IsEmpty())
		{
			*ldappwdlen = pwd.GetLength();
			if(ldappwd != NULL)
				memcpy(ldappwd,pwd.GetBuffer(),pwd.GetLength());
		}
		if(pwd.IsEmpty())
		{
			*ldappwdlen = 10;
			if(ldappwd != NULL)
				memcpy(ldappwd,"NONAME",sizeof("NONAME"));
		}*/
		if(!crlpath.IsEmpty())
		{
			*ldapcrlpathlen=crlpath.GetLength();
			if(ldapcrlpath!=NULL)
				memcpy(ldapcrlpath,crlpath.GetBuffer(),crlpath.GetLength());
		}
		*timeinterval_ldap=timeinterval;
	}
	if( 2==TypeVS2)
	{

		if(m_Http_urlpath.IsEmpty())
		{
			MessageBox("请输入URL地址！","提示",MB_ICONEXCLAMATION);
			return -1;
		}

	  *httpcrlpathlen = m_Http_urlpath.GetLength();
		if(httpcrlpath != NULL)
			memcpy(httpcrlpath,m_Http_urlpath.GetBuffer(),m_Http_urlpath.GetLength());
	  *timeinterval_HTTP=httptimeterval;
	}
	*oType=TypeVS2;
	return 0;
}


void CVerifyStragegyTwo::SetLdap(unsigned char *addr,unsigned char *port,unsigned char *ldapcrlpath,unsigned int timeinterval_in,unsigned char* httpurlpath,unsigned int timeinterval_hp, unsigned int oTypeVS2)
{
	if(1 == oTypeVS2)//-----------LADP方式显示
	{
		
		m_ldap_radio.SetCheck(1);

		//Ldap方式
		m_http_day.EnableWindow(FALSE);
		m_vs2_http_urlpath.EnableWindow(FALSE);
		m_http_minute.EnableWindow(FALSE);
		m_http_second.EnableWindow(FALSE);
		m_http_hour.EnableWindow(FALSE);


		m_ldapaddress.EnableWindow(TRUE);
		m_ldapPort.EnableWindow(TRUE);
		/*m_ldapUsername.EnableWindow(TRUE);
		m_ldpa_pwd.EnableWindow(TRUE);*/
		m_ldapurlpath.EnableWindow(TRUE);
		m_crlrel.EnableWindow(TRUE);//这是ldap的天数控件变量
		m_ldapHour.EnableWindow(TRUE);
		m_ldapMinute.EnableWindow(TRUE);
		m_ldapSecond.EnableWindow(TRUE);
		TypeVS2 = 1;
		if(addr != NULL)
			SetDlgItemText(IDC_EDIT_vs2_LDAPaddress,CString(addr)); 
		if(port != NULL)
			SetDlgItemText(IDC_EDIT_vs2_Port,CString(port)); 
		/*if(name != NULL && strncmp((char*)name,"NONAME",6))
			SetDlgItemText(IDC_EDIT_vs2_USRNAME,CString(name)); 
		if(pwd != NULL  && strncmp((char*)pwd,"NONAME",6))
			SetDlgItemText(IDC_EDIT_vs2_pwd,CString(pwd)); */
		if(ldapcrlpath!=NULL)
			SetDlgItemText(IDC_EDIT_vs2_crlpath,CString(ldapcrlpath)); 

		int in_day1=0,in_hour1=0,in_minute1=0,in_second1=0;
		CString cs_day1,cs_hour1,cs_minute1,cs_second1;
		in_day1 = timeinterval_in/(24*60*60);


		if(in_day1 > 0)
		{
			cs_day1.Format("%d",in_day1);
			in_hour1 = (timeinterval_in-in_day1*24*60*60)/(60*60);
			if(in_hour1>0)
			{
				cs_hour1.Format("%d",in_hour1);
				in_minute1 = (timeinterval_in-in_day1*24*60*60-in_hour1*60*60)/(60);
				if(in_minute1>0)
				{
					cs_minute1.Format("%d",in_minute1);
					in_second1 = timeinterval_in-in_day1*24*60*60-in_hour1*60*60-in_minute1*60;
					cs_second1.Format("%d",in_second1);
				}
				else 
				{
					cs_minute1 = "0";
					in_second1 = timeinterval_in-in_day1*24*60*60-in_hour1*60*60;
					cs_second1.Format("%d",in_second1);
				}
			}
			else
			{
				cs_hour1 = "0";
				in_minute1 = (timeinterval_in-in_day1*24*60*60)/(60);
				if(in_minute1>0)
				{
					cs_minute1.Format("%d",in_minute1);
					in_second1=timeinterval_in-in_day1*24*60*60-in_hour1*60*60-in_minute1*60;
					cs_second1.Format("%d",in_second1);
				}
				else 
				{
					cs_minute1 = "0";
					in_second1 = timeinterval_in-in_day1*24*60*60;
					cs_second1.Format("%d",in_second1);
				}
			}
		}
		else
		{
			cs_day1 = "0";
			in_hour1 = timeinterval_in/(60*60);
			if(in_hour1>0)
			{
				cs_hour1.Format("%d",in_hour1);
				in_minute1 = (timeinterval_in-in_hour1*60*60)/(60);
				if(in_minute1>0)
				{
					cs_minute1.Format("%d",in_minute1);
					in_second1 = timeinterval_in-in_hour1*60*60-in_minute1*60;
					cs_second1.Format("%d",in_second1);
				}
				else 
				{
					cs_minute1 = "0";
					in_second1 = timeinterval_in-in_hour1*60*60;
					cs_second1.Format("%d",in_second1);
				}
			}
			else
			{
				cs_hour1 = "0";
				in_minute1 = timeinterval_in/60;
				if(in_minute1>0)
				{
					cs_minute1.Format("%d",in_minute1);
					in_second1=timeinterval_in-in_minute1*60;
					cs_second1.Format("%d",in_second1);
				}
				else 
				{
					cs_minute1 = "0";
					in_second1 = timeinterval_in;
					cs_second1.Format("%d",in_second1);
				}
			}
		}

		SetDlgItemText(IDC_EDIT_CRLREL_vs2,cs_day1); 
		SetDlgItemText(IDC_EDIT_HOUR_vs2,cs_hour1); 
		SetDlgItemText(IDC_EDIT_MINUTE_vs3,cs_minute1); 
		SetDlgItemText(IDC_EDIT_SECOND_vs2,cs_second1);
	}
	else if(2 == oTypeVS2)
	{//----------------http方式显示
		m_http_radio.SetCheck(1);
		// TODO: 在此添加控件通知处理程序代码
		//http方式
		m_ldapaddress.EnableWindow(FALSE);
		m_ldapPort.EnableWindow(FALSE);
		/*m_ldapUsername.EnableWindow(FALSE);
		m_ldpa_pwd.EnableWindow(FALSE);*/
		m_ldapurlpath.EnableWindow(FALSE);
		m_crlrel.EnableWindow(FALSE);//这是ldap的天数控件变量
		m_ldapHour.EnableWindow(FALSE);
		m_ldapMinute.EnableWindow(FALSE);
		m_ldapSecond.EnableWindow(FALSE);


		m_http_day.EnableWindow(TRUE);
		m_vs2_http_urlpath.EnableWindow(TRUE);
		m_http_minute.EnableWindow(TRUE);
		m_http_second.EnableWindow(TRUE);
		m_http_hour.EnableWindow(TRUE);
		TypeVS2 = 2;
		if(httpurlpath!=NULL)
			SetDlgItemText(IDC_EDIT_vs2_HTTP_URLPATH,CString(httpurlpath)); 

		int in_day2=0,in_hour2=0,in_minute2=0,in_second2=0;
		CString cs_day2,cs_hour2,cs_minute2,cs_second2;
		in_day2 = timeinterval_hp/(24*60*60);


		if(in_day2 > 0)
		{
			cs_day2.Format("%d",in_day2);
			in_hour2 = (timeinterval_hp-in_day2*24*60*60)/(60*60);
			if(in_hour2>0)
			{
				cs_hour2.Format("%d",in_hour2);
				in_minute2 = (timeinterval_hp-in_day2*24*60*60-in_hour2*60*60)/(60);
				if(in_minute2>0)
				{
					cs_minute2.Format("%d",in_minute2);
					in_second2 = timeinterval_hp-in_day2*24*60*60-in_hour2*60*60-in_minute2*60;
					cs_second2.Format("%d",in_second2);
				}
				else 
				{
					cs_minute2 = "0";
					in_second2 = timeinterval_hp-in_day2*24*60*60-in_hour2*60*60;
					cs_second2.Format("%d",in_second2);
				}
			}
			else
			{
				cs_hour2 = "0";
				in_minute2 = (timeinterval_hp-in_day2*24*60*60)/(60);
				if(in_minute2>0)
				{
					cs_minute2.Format("%d",in_minute2);
					in_second2=timeinterval_hp-in_day2*24*60*60-in_hour2*60*60-in_minute2*60;
					cs_second2.Format("%d",in_second2);
				}
				else 
				{
					cs_minute2 = "0";
					in_second2 = timeinterval_hp-in_day2*24*60*60;
					cs_second2.Format("%d",in_second2);
				}
			}
		}
		else
		{
			cs_day2 = "0";
			in_hour2 = timeinterval_hp/(60*60);
			if(in_hour2>0)
			{
				cs_hour2.Format("%d",in_hour2);
				in_minute2 = (timeinterval_hp-in_hour2*60*60)/(60);
				if(in_minute2>0)
				{
					cs_minute2.Format("%d",in_minute2);
					in_second2 = timeinterval_hp-in_hour2*60*60-in_minute2*60;
					cs_second2.Format("%d",in_second2);
				}
				else 
				{
					cs_minute2 = "0";
					in_second2 = timeinterval_hp-in_hour2*60*60;
					cs_second2.Format("%d",in_second2);
				}
			}
			else
			{
				cs_hour2 = "0";
				in_minute2 = timeinterval_hp/60;
				if(in_minute2>0)
				{
					cs_minute2.Format("%d",in_minute2);
					in_second2=timeinterval_hp-in_minute2*60;
					cs_second2.Format("%d",in_second2);
				}
				else 
				{
					cs_minute2 = "0";
					in_second2 = timeinterval_hp;
					cs_second2.Format("%d",in_second2);
				}
			}
		}

		SetDlgItemText(IDC_EDIT_HTTP_CRLREL_vs2,cs_day2); 
		SetDlgItemText(IDC_EDIT_HTTP_HOUR_vs2,cs_hour2); 
		SetDlgItemText(IDC_EDIT_HTTP_MINUTE_vs2,cs_minute2); 
		SetDlgItemText(IDC_EDIT_HTTP_SECOND_vs2,cs_second2);
	}
}




void CVerifyStragegyTwo::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	//http方式
	m_ldapaddress.EnableWindow(FALSE);
	m_ldapPort.EnableWindow(FALSE);
	/*m_ldapUsername.EnableWindow(FALSE);
	m_ldpa_pwd.EnableWindow(FALSE);*/
	m_ldapurlpath.EnableWindow(FALSE);
	m_crlrel.EnableWindow(FALSE);//这是ldap的天数控件变量
	m_ldapHour.EnableWindow(FALSE);
	m_ldapMinute.EnableWindow(FALSE);
	m_ldapSecond.EnableWindow(FALSE);


	m_http_day.EnableWindow(TRUE);
	m_vs2_http_urlpath.EnableWindow(TRUE);
	m_http_minute.EnableWindow(TRUE);
	m_http_second.EnableWindow(TRUE);
	m_http_hour.EnableWindow(TRUE);
	TypeVS2 = 2;
}


void CVerifyStragegyTwo::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	//Ldap方式
	m_http_day.EnableWindow(FALSE);
	m_vs2_http_urlpath.EnableWindow(FALSE);
	m_http_minute.EnableWindow(FALSE);
	m_http_second.EnableWindow(FALSE);
	m_http_hour.EnableWindow(FALSE);


	m_ldapaddress.EnableWindow(TRUE);
	m_ldapPort.EnableWindow(TRUE);
	/*m_ldapUsername.EnableWindow(TRUE);
	m_ldpa_pwd.EnableWindow(TRUE);*/
	m_ldapurlpath.EnableWindow(TRUE);
	m_crlrel.EnableWindow(TRUE);//这是ldap的天数控件变量
	m_ldapHour.EnableWindow(TRUE);
	m_ldapMinute.EnableWindow(TRUE);
	m_ldapSecond.EnableWindow(TRUE);
	TypeVS2 = 1;
}