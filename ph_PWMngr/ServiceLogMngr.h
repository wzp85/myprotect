#pragma once
#include "afxwin.h"
#include "ph_km.h"
#include "afxcmn.h"

// CServiceLogMngr 对话框

class CServiceLogMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceLogMngr)

public:
	typedef struct
	{
		unsigned char		index[32];
		unsigned char		ip[32];
		unsigned char		opt_kind[32];
		unsigned char		opt_result[32];
		unsigned char       oper_ID[32];
		unsigned char		opt_time[32];
		unsigned char		cert_SN[32];
		unsigned char		cert_DN[32];
	}SLOGITEM;
	/*************此操作防止因为原文密文太长导致堆栈溢出************/
	typedef struct{
		int size;
		char* value;
	}Datil_DATA;
	/*************************************************************/
	CServiceLogMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServiceLogMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SERVICELOG_MNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void *phHandle_slm;
	afx_msg void OnBnClickedButtonxmlok();
	CButton m_check_sign;
	CButton m_check_verify;
	CButton m_check_envelop;
	CButton m_check_openevvelop;
	CButton m_check_checkcert;
	afx_msg void OnBnClickedRadionorecord();
	afx_msg void OnBnClickedRadiorecordpart();
	afx_msg void OnBnClickedRadiorecordwithcert();
	afx_msg void OnBnClickedRadiorecordwithoutcert();
	afx_msg void OnBnClickedRadionorecordsp();
	afx_msg void OnBnClickedRadiorecordlocalsp();
	afx_msg void OnBnClickedRadiorecordsyslogsp();
	afx_msg void OnBnClickedRadiorecordwebsp();


	unsigned int logContentType;
	unsigned int logPolicyType;
	void calcuSLR(unsigned int *SLRvalue);


	CListCtrl m_slm_listctrl;

	BOOL isCheckbox_log_slm;
	int check_log_slm[256];
	int i_checked_log_slm;
	int nId_row_log_slm;
	int nId_row_mux_log_slm[256];

	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);
	afx_msg void OnLvnItemchangedListslm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemStateIconClickListslm(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDelSlm();
	afx_msg void OnBackSlm();
	afx_msg void OnRecoverSlm();
	afx_msg void OnDetailSlm();
	afx_msg void OnNMRClickListslm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonslmsearch();
	afx_msg void OnBnClickedButtonslmfirstpage();
	afx_msg void OnBnClickedButtonslmprepage();
	afx_msg void OnBnClickedButtonnextpage();
	afx_msg void OnBnClickedButtonlastpage();

	SLOGITEM slogitem[100];
	
	void ServiceLogStringGetAndParse();
	void ServiceLogShowFromCache(unsigned int current_page);
	void ServiceLogStringGetAndParse_search(CString Logstarttime_SLM,CString Logendtime_SLM,CString Logoptkind_SLM);
	//afx_msg void OnBnClickedChecksign();
	//afx_msg void OnBnClickedCheckverify();
	CEdit m_sylogaddres;
	CEdit m_webUrl;
	CString m_syslog_cstring;
	CString m_weburl_cstring;
	CButton m_getcertinfo;
	CButton m_open_sign_envelop;
	CButton m_sign_envelop;
	CString m_time_start;//搜索条件
	CString m_time_end;
	CString m_opt_kind;

	CComboBox m_optkind_CBox;
	afx_msg void OnCbnSelchangeComboOptkind();
	//afx_msg void OnBnClickedChecksign();
	CComboBox m_LogSaveCCBoX;
	afx_msg void OnCbnSelchangeLgsavecombo2();
	CString m_LogSaveCS;
};
