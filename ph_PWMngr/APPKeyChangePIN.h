#pragma once
#include "afxwin.h"


// CAPPKeyChangePIN �Ի���

class CAPPKeyChangePIN : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPKeyChangePIN)

public:
	CFont line1;
	CAPPKeyChangePIN(void *handle,CString index,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAPPKeyChangePIN();

// �Ի�������
	enum { IDD = IDD_APPKEY_CHANGEPIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CStatic m_line1;
	CString m_currentpin;
	CString m_newpin;
	CString m_newpincon;
	void *phHandle;
	CString key_index_ch;
};
