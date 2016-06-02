#pragma once
#include "afxwin.h"


// CEncryptKeyResume 对话框

class CEncryptKeyResume : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryptKeyResume)

public:
	CFont line1;
	CFont line2;
	CEncryptKeyResume(void *handle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncryptKeyResume();

// 对话框数据
	enum { IDD = IDD_ENCRYPTKEY_RESUME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CString m_filepath;
	CStatic m_line1;
	CStatic m_line2;
	void *phHandle_ek;

	unsigned char sys_Key_1_ekRsu[256];
	unsigned char sys_Key_2_ekRsu[256];
	unsigned char sys_Key_3_ekRsu[256];
};
