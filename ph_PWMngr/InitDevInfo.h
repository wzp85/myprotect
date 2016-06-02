#pragma once
#include "afxwin.h"


// CInitDevInfo �Ի���

class CInitDevInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CInitDevInfo)

public:
	CInitDevInfo(void * key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitDevInfo();

// �Ի�������
	enum { IDD = IDD_INIT_DEVINFO_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_algedit;
	CString m_devName;
	CString m_algID_devInfo;
	CString m_devPIN;
	CString m_devPINcon;
	void *phSHandle;
	void *key_phSHandle;
	afx_msg void OnBnClickedButton2();

	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeAlgCombo();
};
