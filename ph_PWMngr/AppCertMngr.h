#pragma once
#include "afxcmn.h"


// CAppCertMngr 对话框

class CAppCertMngr : public CPropertyPage
{
	DECLARE_DYNAMIC(CAppCertMngr)

public:
	
	typedef struct
	{
		char		appName[64];
		char		algid[32];
		char		keyLen[32];
		char		keyType[32];
		char		optime[32];
		int			index;
	}ACSINFO;
	CAppCertMngr();
	virtual ~CAppCertMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_APPCERTMNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearchcertlistButton();
	CListCtrl m_AppCert;

	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);
	afx_msg void OnNMRClickAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAppcertAdk();
	afx_msg void OnAppcertGreq();
	afx_msg void OnAppcertImport();
	afx_msg void OnAppcertBackup();
	afx_msg void OnAppcertUpdate();
	afx_msg void OnAppcertResume();
	afx_msg void OnAppcertDistroy();
	afx_msg void OnAppcertChangepin();
	afx_msg void OnAppcertExport();
	afx_msg void OnLvnItemchangedAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemStateIconClickAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_AppCert_index_fors;
	CString m_AppCert_apname_fors;

	void *phHandle;
	LPCTSTR szIP;
	BYTE * pConfigData ;
	void ShowAppCertKeyInfo();
	void ShowAppCertKeyInfo_Search(CString appName,CString keyIndex_cs);

	int keyIndex_appCert_max;
	int keyIndex_appCert[256][2];

	BOOL isCheckbox_ac;
	int check_ac[256];
	int i_checked_ac;

	int nId_row_ac;
	int nId_row_mux_ac[256];

	unsigned char sys_Key_1[256];
	unsigned char sys_Key_2[256];
	unsigned char sys_Key_3[256];

	void checkKeyManager(int *status,BYTE * pConfigData );
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnAppcertOnline();//添加的在线证书请求
	afx_msg void OnAppkeyset();
	afx_msg void OnAppcertNtf();
	unsigned char standard_type[32];
	unsigned int standardtypeLength;
	unsigned char cert_url[32];
	unsigned int certurllength;
	unsigned char certip[32];
	unsigned int certiplength;
	unsigned char certport[32];
	unsigned int certportlength;
	unsigned int type;
	afx_msg void OnAppkeyupdate();
};
