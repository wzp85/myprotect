#pragma once
#include "afxcmn.h"


// CSysLogQuery 对话框

class CSysLogQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CSysLogQuery)

public:
	typedef struct
	{
		unsigned char  timestmp[32];
		unsigned char  hostname[32];
		unsigned char  message[56];
	}LOGITEM;
	CSysLogQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysLogQuery();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SYSLOGAUDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonsyslogsearch();
	void *phHandle_slq;
	afx_msg void OnBnClickedButtonfirstpage();
	afx_msg void OnBnClickedButtonprepage();
	afx_msg void OnBnClickedButtonnextpage();
	afx_msg void OnBnClickedButtonlastpage();
	//CListCtrl m_syslog_query;
	CListCtrl m_Syslog_query;
	afx_msg void OnNMRClickSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult);
	void CSysLogQuery::CheckAllItems(BOOL fChecked);
	void CSysLogQuery::SetHeaderCheckbox(void);
	void CSysLogQuery::LogStringGetAndParse();
	afx_msg void OnLvnItemchangedSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemStateIconClickSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult);
	//char* Pub_MemSearch(char * mem,int memLen,char * subMem,int subMemLen);
	void GetStringFromCacheAndShow(unsigned int current_page);
	BOOL isCheckbox_log;//序列号操作
	int check_log[256];
	int i_checked_log;
	int nId_row_log;
	int nId_row_mux_log[256];
	unsigned int page;//用缓存实现，代表第几次查询
	unsigned int current_page;
	unsigned int totalItem;//总的记录条数
	CString LogContentCache;//日志缓存

	LOGITEM logitem[100];


};
