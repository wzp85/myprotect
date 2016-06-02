#pragma once


// CReqInputKeyPwd 对话框

class CReqInputKeyPwd : public CDialogEx
{
	DECLARE_DYNAMIC(CReqInputKeyPwd)

public:
	CReqInputKeyPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReqInputKeyPwd();

// 对话框数据
	enum { IDD = IDD_REQ_INPUT_KEYPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_req_pinf;
	CString m_req_pins;
	virtual BOOL OnInitDialog();

	unsigned char kpwd[32];
	unsigned int klen;
	void GetKeyPassword(unsigned char *word,unsigned int *len);

};
