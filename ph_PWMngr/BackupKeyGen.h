#pragma once
#include "afxwin.h"


// CBackupKeyGen �Ի���

class CBackupKeyGen : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackupKeyGen)

public:
	CFont font;
	CBackupKeyGen();
	virtual ~CBackupKeyGen();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGEBACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic m_titleline;

	void *phHandle_bkg;
	BOOL PreTranslateMessage(MSG* pMsg);
};
