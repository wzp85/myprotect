#pragma once

#include "ph_km.h"
#include "afxcmn.h"
#include "KeyDAO.h"
#include "MyUtil.h"
#include "SeeLogDetail.h"
#include "afxwin.h"
// CLogQuery 对话框

class CLogQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CLogQuery)

public:
	typedef struct
	{
		unsigned char		index[32];
		unsigned char		opt[32];
		unsigned char		opt_kind[32];
		unsigned char		opt_result[32];
		unsigned char		opt_time[32];
	}LOGITEM;
	CLogQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogQuery();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void *phHandle_log;
	//afx_msg void OnBnClickedRadiologtime();
	//afx_msg void OnBnClickedRadiologadmname();
	CListCtrl m_lc_log;
	afx_msg void OnBnClickedButtonfirstpage();
	afx_msg void OnBnClickedButtonprepage();
	afx_msg void OnBnClickedButtonnextpage();
	afx_msg void OnBnClickedButtonlastpage();
	afx_msg void OnBnClickedButtonserchlog();

	void LogStringGetAndParse();
//	void LogStringParse();
	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);

	afx_msg void OnLvnItemchangedListlog(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL isCheckbox_log;
	int check_log[256];
	int i_checked_log;
	int nId_row_log;
	int nId_row_mux_log[256];
	afx_msg void OnHdnItemStateIconClickListlog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLogDetail();
	afx_msg void OnNMRClickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);


	
//	unsigned char LogContentCache;
	RSAPUBLICKEYBLOB rsaPubKeyCache;

	void LogStringParseAndShow(unsigned int current_page);
	void LogStringGetAndParse_Search(CString Logstartime,CString Logendtime,CString Logoptkind);
	LOGITEM logitem[100];
	void ReverseData(unsigned char * pdata, unsigned int len);
	
	CEdit m_timeStart;
	CEdit m_timeEnd;
	//CEdit m_optKind;
	CString m_timeStart_cs;//搜索条件
	CString m_timeEnd_cs;
	CString m_optKind_cs;
	CComboBox m_optresult_CBox;
	afx_msg void OnCbnSelchangeComboOptresult();
	afx_msg void OnCbnDblclkComboOptresult();
};
