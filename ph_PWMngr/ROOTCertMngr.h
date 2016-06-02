#pragma once
#include "afxcmn.h"


// CROOTCertMngr 对话框

class CROOTCertMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CROOTCertMngr)

public:
	typedef struct
	{
		unsigned char		name[50];
		unsigned char		index[50];
		unsigned char		algid[50];
		unsigned char		atName[50];
		unsigned char       hostName[50];
		unsigned char		hostPhone[50];
	}RCISH;
	CROOTCertMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CROOTCertMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ROOTCERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ROOTCert;
	afx_msg void OnBnClickedRootcertSearchcertlistButton();

	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);
	afx_msg void OnLvnItemchangedRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemStateIconClickRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRootcertAdd();
	afx_msg void OnRootcertUpdate();
	afx_msg void OnRootcertDel();
	afx_msg void OnRootcertExport();
	BOOL PreTranslateMessage(MSG* pMsg);
	void *phHandle;
	void ShowRootCertInfo();
	void ShowRootCertInfo_Search(CString index,CString name,CString algid,CString atName);

	BOOL isCheckbox_rc;
	int check_rc[256];
	int i_checked_rc;
	int certIndex_rtCert_max;
	int certIndex_rtCert[256][2];

	int nId_row_rc;
	int nId_row_mux_rc[256];
	//------------for--查询变量------
	CString m_rtCertIndex_cs;
	CString m_rtCertName_cs;
	CString m_rtCertAlgid_cs;
	CString m_rtCertAtName_cs;
	afx_msg void OnRtcertBackup();
	afx_msg void OnRtcertRecovery();
};
