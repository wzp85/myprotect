#pragma once
#include "afxcmn.h"


// CAppCertNtfIp 对话框

class CAppCertNtfIp : public CDialogEx
{
	DECLARE_DYNAMIC(CAppCertNtfIp)

public:
	CAppCertNtfIp(CWnd* pParent = NULL);   // 标准构造函数
	CAppCertNtfIp(void *handle,CWnd* pParent = NULL);// 标准构造函数
	virtual ~CAppCertNtfIp();
	void *phHandle_NtfIp;
// 对话框数据
	enum { IDD = IDD_APPCERT_NTF_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ConfigIP;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	int GetValue();	
};
