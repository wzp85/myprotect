#pragma once


// CForRecoveryFilePath 对话框

class CForRecoveryFilePath : public CDialogEx
{
	DECLARE_DYNAMIC(CForRecoveryFilePath)

public:
	CForRecoveryFilePath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CForRecoveryFilePath();

// 对话框数据
	enum { IDD = IDD_FOR_RECOVERY_OPENFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonfrll();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_filepath_recoveryfile;

	void GetRecoveryFilePath(char *path,int *pathLen);
};
