#pragma once


// CFifthBackupKey �Ի���

class CFifthBackupKey : public CDialogEx
{
	DECLARE_DYNAMIC(CFifthBackupKey)

public:
	CFifthBackupKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFifthBackupKey();

// �Ի�������
	enum { IDD = IDD_FIFTHPWD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_fifthpwd;
	int m_fifthconpwd;
};
