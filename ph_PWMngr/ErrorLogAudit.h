#pragma once
#include "afxcmn.h"


// CErrorLogAudit 对话框

class CErrorLogAudit : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorLogAudit)

public:
	CErrorLogAudit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CErrorLogAudit();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ERRORLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void *phHandle_ela;
	CListCtrl m_errorlogaudit_listctrl;
};
