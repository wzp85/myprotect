#pragma once


// CChangeInitPin �Ի���

class CChangeInitPin : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeInitPin)

public:
	CChangeInitPin(int isRs,char *ip,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeInitPin();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_username;
	CString m_usrOldPin;
	CString m_usrNewPin;

	char ip_in[32];
	virtual BOOL OnInitDialog();

	int isRs_ChangePin;
};
