#pragma once


// CVerifyStragegyThree �Ի���

class CVerifyStragegyThree : public CDialogEx
{
	DECLARE_DYNAMIC(CVerifyStragegyThree)

public:
	CVerifyStragegyThree(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVerifyStragegyThree();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CAADD_VS3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonvs31();
	CString m_day;
	CString m_hour;
	CString m_minute;
	CString m_second;
	unsigned int upTime;

	CString t_day;
	CString t_hour;
	CString t_minute;
	CString t_second;
	int GetDataVS3();
	int GetVS3Time(unsigned int *updateTsime);
	void SetVS3_Time(unsigned int vs_time);
};
