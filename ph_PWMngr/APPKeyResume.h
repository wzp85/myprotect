#pragma once
#include "afxwin.h"


// CAPPKeyResume �Ի���

class CAPPKeyResume : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPKeyResume)

public:
	CFont font_line1;
	CFont font_line2;
	CAPPKeyResume(void *handle,int isSig,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAPPKeyResume();

// �Ի�������
	enum { IDD = IDD_APPKEY_RESUME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBrowseButton();
	CButton m_browse;
	CString m_browsefile;
	CString m_usrpin;
	CString m_usrpincon;
	CStatic m_title;
	CStatic m_line2;
	CString m_filePath;
	void *phHandle;
	unsigned char sys_Key_1_Rsu[256];
	unsigned char sys_Key_2_Rsu[256];
	unsigned char sys_Key_3_Rsu[256];

	int isSigServer;//1��ʾ����ǩ��������
};
