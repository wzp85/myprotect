#pragma once
#include "afxwin.h"


// CRTCertAdd 对话框

class CRTCertAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CRTCertAdd)

public:
	CRTCertAdd(void *handle,int isUp,CString name,CString algid,CString index,CString atName,CString hostName,CString hostPhone,CString keyIndex,CWnd* pParent =NULL);
	CRTCertAdd(void *handle,int isUp,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRTCertAdd();

// 对话框数据
	enum { IDD = IDD_RTCERT_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

	int isUp_rt;
	afx_msg void OnBnClickedImrtcButton();

	BOOL PreTranslateMessage(MSG* pMsg);
	CString m_RTADD_certName_cs;
	CString m_RTADD_certAlg_cs;
	CComboBox m_RTADD_certAlg;
	
	CString m_RTADD_atName_cs;
	CString m_RTADD_hostName_cs;
	CString m_RTADD_phone_cs;
	CString m_RTADD_rootCert_cs;
	CString m_RTADD_certindex_cs;
	CString m_RTADD_certSN_cs;

	void *phHandle_RtCertAdd;
	CString certFilePath;
	int rtAddIndex;
	int rtAddIndex_array[256][2];
	CComboBox m_rt_index;
	CString m_rt_index_cs;
	afx_msg void OnCbnSelchangeRtcertIndexCombo();
};
