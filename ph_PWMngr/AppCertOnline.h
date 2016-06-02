#pragma once
#include "afxwin.h"


// CAppCertOnline 对话框

class CAppCertOnline : public CDialogEx
{
	DECLARE_DYNAMIC(CAppCertOnline)

public:
	CAppCertOnline(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppCertOnline();

// 对话框数据
	enum { IDD = IDD_APPCERT_ONLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_certStandrd;
	CEdit m_certUrl;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboCertstand();
	virtual BOOL OnInitDialog();
    int GetURLandType(unsigned char*Stand_Type,unsigned int*StandTpeLength,unsigned char*Cert_Url,
	unsigned int*CertUrlLength,unsigned char*Cert_Ip,unsigned int*CertIpLength,unsigned char *Cert_Port,unsigned int*CertPortLength,unsigned int*type);

	CString m_CS_certUrl;
	CEdit m_certip;
	CString m_certIP_CS;
	CEdit m_certPort;
	CString m_certPort_CS;
	
};
