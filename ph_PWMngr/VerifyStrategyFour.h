#pragma once
#include "afxwin.h"


// CVerifyStrategyFour 对话框

class CVerifyStrategyFour : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStrategyFour)

public:
	CVerifyStrategyFour(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVerifyStrategyFour();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CAADD_VS4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonvs41();
	CString m_ip_vs4;
	CString m_url_vs4;

	CString	ip_vs4;
	CString	url_vs4;
	CString port_vs4;
	unsigned int certstand;
	unsigned int talktype;
	int GetDataVS4();
	int GetIpUrlVS4(unsigned char *ip,unsigned int *iplen,unsigned char *url,unsigned int *urllen,
		unsigned char *port,unsigned int *portlen,unsigned int *Certstand,unsigned int *Talktype);
	void SetIpUrlVs(unsigned char *ip,unsigned char *port,unsigned char *url,unsigned int certstandd,unsigned int talktypee);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	CString m_port_vs4;
	CEdit m_VS4ip_Control;
	CEdit m_VS4port_Control;
	CEdit m_VS4url_Control;
	
	CButton m_RADIO_GUOMI_Control;
	CButton m_RADIO_SHUIZ_Control;
	CButton m_RADIO_Socket_Control;
	CButton m_RADIO_Web_Control;

	unsigned int CertStand  ;
	unsigned int talkType ;
	
};
