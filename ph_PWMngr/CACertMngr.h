#pragma once
#include "afxcmn.h"


// CCACertMngr 对话框

class CCACertMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CCACertMngr)

public:
	typedef struct
	{
		unsigned char		name[50];
		unsigned char		index[50];
		unsigned char		algid[50];
		unsigned char		atName[50];
		unsigned char       hostName[50];
		unsigned char		hostPhone[50];
	}CAISH;
	CCACertMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCACertMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CACERTMNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CACert;
	CButton m_btnSlect;
	afx_msg void OnBnClickedCacertSearchcertlistButton();
	CString m_CA_CertIndex_fors;
	CString m_CA_CertName_fors;
	CString m_CA_Alg_fors;
	CString m_CA_atName_fors;

	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);
	afx_msg void OnNMRClickCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemStateIconClickCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCacertAdd();
	afx_msg void OnCacertUpdate();
	afx_msg void OnCacertDel();
	afx_msg void OnCacertExport();

	void *phHandle;
	void ShowCACertInfo();
	void ShowCACertInfo_Search(CString index,CString name,CString algid,CString atName);

	BOOL isCheckbox_cc;
	int check_cc[256];
	int i_checked_cc;

	int nId_row_cc;
	int nId_row_mux_cc[256];

	afx_msg void OnCacertBackup();
	afx_msg void OnCacertRecovery();

	int certIndex_caCert_max;
	int certIndex_caCert[256][2];

};
