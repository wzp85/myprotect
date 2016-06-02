#pragma once
#include "afxwin.h"


// CAPPKeyChangePIN 对话框

class CAPPKeyChangePIN : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPKeyChangePIN)

public:
	CFont line1;
	CAPPKeyChangePIN(void *handle,CString index,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAPPKeyChangePIN();

// 对话框数据
	enum { IDD = IDD_APPKEY_CHANGEPIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
