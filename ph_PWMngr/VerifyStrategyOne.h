#pragma once


// CVerifyStrategyOne �Ի���

class CVerifyStrategyOne : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStrategyOne)

public:
	CVerifyStrategyOne(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVerifyStrategyOne();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CAADD_VS1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
