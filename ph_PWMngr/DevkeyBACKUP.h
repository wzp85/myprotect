#pragma once
#include "afxwin.h"


// CDevkeyBACKUP �Ի���

class CDevkeyBACKUP : public CPropertyPage
{
	DECLARE_DYNAMIC(CDevkeyBACKUP)

public:
	CDevkeyBACKUP();
	virtual ~CDevkeyBACKUP();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGE };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnSetActive();
	CString m_devName;
	CComboBox m_isBackup;
	CComboBox m_backupCatge;
	CComboBox m_algId;

	void *phHandle_dev;
	CString m_isBackup_int;
	CString m_algId_int;
	CString m_modifyTime;

	unsigned char sys_Key_1_dev[257];
	unsigned char sys_Key_2_dev[257];
	unsigned char sys_Key_3_dev[257];

	void ShowDevInfo();
	BOOL PreTranslateMessage(MSG* pMsg);
};
