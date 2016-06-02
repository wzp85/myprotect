#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "VerifyStrategyOne.h"
#include "VerifyStragegyTwo.h"
#include "VerifyStragegyThree.h"
#include "VerifyStrategyFour.h"
#include "VerifyStrategyFive.h"

// CCACertAdd 对话框

class CCACertAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CCACertAdd)

public:
	CRect tabRect;

	CVerifyStrategyOne vsOneDlg;
	CVerifyStragegyTwo vsTwoDlg;
	CVerifyStragegyThree vsThreeDlg;
	CVerifyStrategyFour vsFourDlg;
	CVerifyStrategyFive vsFiveDlg;
	CCACertAdd(void *handle,int isUp,unsigned int uiRtCertType,unsigned int uiRtCertIndex,CString ca_index,VerifyPriorityStrategy vs,CString index,CString name,CString algId,CString atName,CString hostName,CString hostPhone,CWnd* pParent = NULL); 
	CCACertAdd(void *handle,int isUp,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCACertAdd();

// 对话框数据
	enum { IDD = IDD_CACERT_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int isUp_CA;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedImcaButton();

	afx_msg void OnBnClickedImtruchainButton();

	BOOL PreTranslateMessage(MSG* pMsg);

	//afx_msg void OnBnClickedRadiovs1();
	//afx_msg void OnBnClickedRadiovs2();
	//afx_msg void OnBnClickedRadiovs3();
	//afx_msg void OnBnClickedRadiovs4();
	//afx_msg void OnBnClickedRadiovs5();


	void *phHandle_CACertAdd;
	CString m_CAcert_path;
	int caAddIndex;
	int caAddIndex_array[256][2];

	unsigned int index_rt_forshow;
	unsigned int rt_type;
	CString index_ca_fordel;
	//-----------------用于测试
	//VerifyStrategy   CAvs;
	//----------------
	VerifyPriorityStrategy CApvs;//------包含策略优先级的结构体

	CString m_CAADD_certName_cs;
	CString m_CAADD_certAlg_cs;
	CComboBox m_CAADD_certAlg;
	CString m_CAADD_certIndex_cs;
	CString m_CAADD_atName_cs;
	CString m_CAADD_hostName;
	CString m_CAADD_phone_cs;
	CString m_CA_certImp_cs;
	CString m_CA_truchain_Imp_cs;
	CString m_rootCert_CAA;
	CComboBox m_rootCert_choseCAA;
	CString m_CaCertSeriNum_CS;
	CComboBox m_CaAdd_index_CCobox;
	CString m_CaAdd_index_CS;
	afx_msg void OnBnClickedRadiovs6();
	afx_msg void OnBnClickedCheckVs1();
	afx_msg void OnBnClickedCheckVs2();
	afx_msg void OnBnClickedCheckVs3();
	afx_msg void OnBnClickedCheckVs4();
	afx_msg void OnBnClickedCheckVs5();
	afx_msg void OnBnClickedCheckVs6();
	
	CButton m_check1;
	CButton m_check2;
	CButton m_check3;
	CButton m_check4;
	CButton m_check5;
	CButton m_check6;
	CString m_VS1_priority;
	CString m_VS2_priority;
	CString m_VS3_priority;
	CString m_VS4_priority;
	CString m_VS5_priority;
	CEdit m_VS1_CN;
	CEdit m_VS2_CN;
	CEdit m_VS3_CN;
	CEdit m_VS4_CN;
	CEdit m_VS5_CN;
};
