#pragma once


// CDevAdminKeyMngr 对话框

class CDevAdminKeyMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevAdminKeyMngr)

public:
	CFont font;
	CDevAdminKeyMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevAdminKeyMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE_CARRIERMNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CString m_title;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CString m_adminpin_unlock;
	CString m_admin_login;
	CString m_adminpin_old;
	CString m_adminpin_new;

	BOOL PreTranslateMessage(MSG* pMsg);
};
