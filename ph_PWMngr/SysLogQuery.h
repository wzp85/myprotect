#pragma once
#include "afxcmn.h"


// CSysLogQuery �Ի���

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
	CSysLogQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysLogQuery();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SYSLOGAUDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	BOOL isCheckbox_log;//���кŲ���
	int check_log[256];
	int i_checked_log;
	int nId_row_log;
	int nId_row_mux_log[256];
	unsigned int page;//�û���ʵ�֣�����ڼ��β�ѯ
	unsigned int current_page;
	unsigned int totalItem;//�ܵļ�¼����
	CString LogContentCache;//��־����

	LOGITEM logitem[100];


};
