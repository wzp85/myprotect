#pragma once
#include "afxcmn.h"


// CServiceLogAudit 对话框

class CServiceLogAudit : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceLogAudit)

public:
	CServiceLogAudit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServiceLogAudit();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SLOG_AUDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonslasearch();
	afx_msg void OnBnClickedButtonslafirstpage();
	afx_msg void OnBnClickedButtonslaprepage();
	afx_msg void OnBnClickedButtonslanextpage();
	afx_msg void OnBnClickedButtonslalastpage();
	virtual BOOL OnInitDialog();

	void *phHandle_sla;
	CListCtrl m_slaudit_listctrl;
};
