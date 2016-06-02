#pragma once
#include "afxwin.h"


// CBackupKeyGen 对话框

class CBackupKeyGen : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackupKeyGen)

public:
	CFont font;
	CBackupKeyGen();
	virtual ~CBackupKeyGen();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGEBACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic m_titleline;

	void *phHandle_bkg;
	BOOL PreTranslateMessage(MSG* pMsg);
};
