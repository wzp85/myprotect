#pragma once
#include "afxcmn.h"


// CAppCertNtfIp �Ի���

class CAppCertNtfIp : public CDialogEx
{
	DECLARE_DYNAMIC(CAppCertNtfIp)

public:
	CAppCertNtfIp(CWnd* pParent = NULL);   // ��׼���캯��
	CAppCertNtfIp(void *handle,CWnd* pParent = NULL);// ��׼���캯��
	virtual ~CAppCertNtfIp();
	void *phHandle_NtfIp;
// �Ի�������
	enum { IDD = IDD_APPCERT_NTF_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ConfigIP;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	int GetValue();	
};
