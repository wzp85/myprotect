#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMngrLogAudit �Ի���

class CMngrLogAudit : public CDialogEx
{
	DECLARE_DYNAMIC(CMngrLogAudit)

public:
	CMngrLogAudit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMngrLogAudit();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MLOG_SHENJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonmlssearch();
	virtual BOOL OnInitDialog();

	void *phHandle_mla;
	CListCtrl m_mngrLog_listctrl;
	CComboBox m_mngrLogAudit_option;
	CComboBox m_mngrLogAudit_optype;
	CComboBox m_mngrLogAudit_opresult;
	CString m_mla_starttime;
	CString m_mla_endtime;
	afx_msg void OnCbnSelchangeCombomlsoption();
	CString m_mla_option_cs;
	CString m_mla_optype_cs;
	CString m_mla_opresult_cs;
};
