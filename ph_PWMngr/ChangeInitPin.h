#pragma once


// CChangeInitPin 对话框

class CChangeInitPin : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeInitPin)

public:
	CChangeInitPin(int isRs,char *ip,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeInitPin();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
