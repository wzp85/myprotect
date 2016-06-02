#pragma once
#include "afxwin.h"


// CDevKeyFirResume 对话框

class CDevKeyFirResume : public CDialogEx
{
	DECLARE_DYNAMIC(CDevKeyFirResume)

public:
	CFont fontFirstResume;
	CFont fontLine2;
	CDevKeyFirResume(int isAdm,void *handle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevKeyFirResume();

// 对话框数据
	enum { IDD = IDD_DEV_FIRSTRESUME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBrowseButton();
	CButton m_browseFile;
	CString m_firstResume;
	CString m_usrpin;
	CString m_usrpincon;
	CString m_line2;
	CString m_browsefile;
	void *phHandle_devRsu;

	unsigned char sys_Key_1_Rsu_dev[256];
	unsigned char sys_Key_2_Rsu_dev[256];
	unsigned char sys_Key_3_Rsu_dev[256];

	int isAdmDev;//2是管理员
	int isRecoveryOK;
	void GetRecoverState(int *rc_state);
	CEdit m_usrpinF;
	CEdit m_usrpinS;
	virtual BOOL OnInitDialog();
};
