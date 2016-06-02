#pragma once


// CVerifyStrategyOne 对话框

class CVerifyStrategyOne : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStrategyOne)

public:
	CVerifyStrategyOne(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVerifyStrategyOne();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CAADD_VS1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonvs11();
	afx_msg void OnBnClickedButtonvs1browse();


	CString m_crlPath_cs;
	CString crl_path;
	int GetDataVS1();
	int GetCRLpath_vs1(unsigned char *pathorData,unsigned int *pathlen);
	void SetCRLpath_vs1(unsigned char *path);
};
