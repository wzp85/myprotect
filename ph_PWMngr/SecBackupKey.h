#pragma once


// CSecBackupKey 对话框

class CSecBackupKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSecBackupKey)

public:
	CSecBackupKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSecBackupKey();

// 对话框数据
	enum { IDD = IDD_SECPWD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_secpwdedit;
	int m_secpwdconedit;
};
