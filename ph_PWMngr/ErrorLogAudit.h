#pragma once
#include "afxcmn.h"


// CErrorLogAudit �Ի���

class CErrorLogAudit : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorLogAudit)

public:
	CErrorLogAudit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CErrorLogAudit();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ERRORLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void *phHandle_ela;
	CListCtrl m_errorlogaudit_listctrl;
};
