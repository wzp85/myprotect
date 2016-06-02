#pragma once
#include "afxwin.h"


// CVerifyStragegyTwo 对话框

class CVerifyStragegyTwo : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStragegyTwo)

public:
	//typedef struct
	//{
	//	unsigned char	address[100];
	//	unsigned char	port[32];
	//	unsigned char	name[32];
	//	unsigned char	pwd[32];
	//}VerifyStragegy2,*VerifyStragegy2Ptr;

	CVerifyStragegyTwo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVerifyStragegyTwo();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CAADD_VS2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonvs21();
	CString m_LDAP_address;
	CString m_LDAP_port;
	CString m_LDAP_usrname;
	CString m_LDAP_pwd;

	//VerifyStragegy2 vs2;
	CString	address;
	CString	port;
	CString	name;
	CString	pwd;
	CString crlpath;
	int GetDataVS2();
	int GetVS2(unsigned char *ldapaddr,unsigned int *ldapaddrlen,unsigned char *ldapport,unsigned int *ldapportlen,
				unsigned char *ldapcrlpath,unsigned int *ldapcrlpathlen,unsigned int *timeinterval_ldap,unsigned char *httpcrlpath,
				unsigned int *httpcrlpathlen,unsigned int *timeinterval_HTTP,unsigned int *  oType);

	void SetLdap(unsigned char *addr,unsigned char *port,unsigned char *ldapcrlpath,unsigned int timeinterval_in,unsigned char* httpurlpath,unsigned int timeinterval_hp,unsigned int oTypeVS2);
	CString m_timeinterval_vs2;
	CString m_timeinterval_hour_vs2;
	CString m_timeinterval_minute_vs2;
	CString m_timeinterval_second_vs2;

	CString t_day_cache;
	CString t_hour_cache;
	CString t_minute_cache;
	CString t_second_cache;

	unsigned int timeinterval;
	CString m_LDAP_crlpath;

	/**************http*************/
	unsigned int httptimeterval;
	CString http_urlpath;

	CString http_day_cache;
	CString http_hour_cache;
	CString http_minute_cache;
	CString http_second_cache;

	CString m_Http_urlpath;
	CString m_httptimeterval_vs2;
	CString m_httptimetervar_minute_vs2;
	CString m_httptimetervar_second_vs2;
	CString m_httptimeterval_hour_vs2;
	
	//afx_msg void OnEnChangeEditHttpHourvs2();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	//afx_msg void OnEnChangeEditvs2Ldapaddress();
	CEdit m_crlrel;
	CEdit m_vs2_http_urlpath;
	CEdit m_http_day;
	CEdit m_http_hour;
	CEdit m_http_minute;
	CEdit m_http_second;
	CEdit m_ldapaddress;
	CEdit m_ldapPort;
	CEdit m_ldapUsername;
	CEdit m_ldpa_pwd;
	CEdit m_ldapurlpath;
	CEdit m_ldapHour;
	CEdit m_ldapMinute;
	CEdit m_ldapSecond;
	
	CButton m_http_radio;
	CButton m_ldap_radio;

	unsigned int TypeVS2 ;
};
