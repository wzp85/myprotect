#pragma once
#include "afxwin.h"


// CCheckKeyManager 对话框

class CCheckKeyManager : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckKeyManager)

public:
	CCheckKeyManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckKeyManager();

// 对话框数据
	enum { IDD = IDD_CHECK_KEY_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void getCheckState(int *state);
	int checkState;
	virtual BOOL OnInitDialog();
	CEdit m_ckm_pin;
	CString m_ckmPINedit;
	CString m_ckmPIN_edit;
	BYTE * pConfigData ;
};
