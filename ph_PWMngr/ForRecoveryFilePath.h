#pragma once


// CForRecoveryFilePath �Ի���

class CForRecoveryFilePath : public CDialogEx
{
	DECLARE_DYNAMIC(CForRecoveryFilePath)

public:
	CForRecoveryFilePath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CForRecoveryFilePath();

// �Ի�������
	enum { IDD = IDD_FOR_RECOVERY_OPENFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonfrll();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_filepath_recoveryfile;

	void GetRecoveryFilePath(char *path,int *pathLen);
};
