#pragma once
#include "afxwin.h"


// CUserCertImport 对话框

class CUserCertImport : public CDialogEx
{
	DECLARE_DYNAMIC(CUserCertImport)

public:
	CUserCertImport(void *hand,int keyindex,int keyType,int AsymmAlgo,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserCertImport();

// 对话框数据
	enum { IDD = IDD_DIALOG_IMPORT_USRCERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CString m_certname_uc;
	CString m_algid_uc;
	CString m_certserial_uc;
	CString m_certserial2_uc;
	CString m_atname_uc;
	CString m_hostname_uc;
	CString m_hostphone_uc;
	CString m_usercertpath;
	CComboBox m_cacert;
	CString m_cacert_indexname;
	CComboBox m_algid_cbox;
	afx_msg void OnBnClickedImusrButton();

	void *phHandle_usrCertAdd;
	int appKeyType;
	int appkeyindex;
	int asymmAlgo;
	CString m_sigcert_usradd;
	afx_msg void OnBnClickedUsrsigcertImportButton();
	CString m_uc_pin_f;
	CString m_uc_pin_s;
	afx_msg void OnBnClickedUseraddEncryfileImportButton();
};
