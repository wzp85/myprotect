#pragma once


// CSecBackupKey �Ի���

class CSecBackupKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSecBackupKey)

public:
	CSecBackupKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSecBackupKey();

// �Ի�������
	enum { IDD = IDD_SECPWD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_secpwdedit;
	int m_secpwdconedit;
};
