#pragma once
#include "afxwin.h"


// CCheckKeyManager �Ի���

class CCheckKeyManager : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckKeyManager)

public:
	CCheckKeyManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckKeyManager();

// �Ի�������
	enum { IDD = IDD_CHECK_KEY_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
