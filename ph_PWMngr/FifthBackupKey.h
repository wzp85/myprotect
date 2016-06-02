#pragma once


// CFifthBackupKey 对话框

class CFifthBackupKey : public CDialogEx
{
	DECLARE_DYNAMIC(CFifthBackupKey)

public:
	CFifthBackupKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFifthBackupKey();

// 对话框数据
	enum { IDD = IDD_FIFTHPWD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_fifthpwd;
	int m_fifthconpwd;
};
