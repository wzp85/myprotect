#pragma once


// CDevAdminKeyMngr �Ի���

class CDevAdminKeyMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevAdminKeyMngr)

public:
	CFont font;
	CDevAdminKeyMngr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDevAdminKeyMngr();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LARGE_CARRIERMNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
