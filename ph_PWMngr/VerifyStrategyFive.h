#pragma once


// CVerifyStrategyFive 对话框

class CVerifyStrategyFive : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStrategyFive)

public:
	CVerifyStrategyFive(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVerifyStrategyFive();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CAADD_VS5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonvs51();
	int GetDataVS5();
	int GetVs5_ocsp(unsigned char *pucdata,unsigned int *pucdatalen);
	void SetVs5_ocsp(unsigned char *pucdata);
	CString m_vs5_ocsp;
	CString vs5_ocsp;

};
