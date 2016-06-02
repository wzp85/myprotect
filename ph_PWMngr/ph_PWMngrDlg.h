
// ph_PWMngrDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cph_PWMngrDlg 对话框
class Cph_PWMngrDlg : public CDialogEx
{
// 构造
public:
	CString m_szCaption;
	Cph_PWMngrDlg(CString ip,int i,void *phSHandle,void *key_phSHandle,void *containerHandle,LPCTSTR szCaption,CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PH_PWMNGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_loginPINedit;
	afx_msg void OnBnClickedCancel();
	//afx_msg void OnBnClickedInitButton();
	CIPAddressCtrl m_ipAddress;
	
	void *phSHandle;
	void *key_phSHandle;
	void *key_containerHandle;
	afx_msg void OnClickedSysinitStatic();
	CComboBox m_ip_log;
	CString m_ip;

	void GetMaxAdminLogin(double *num);
	int adm_Num_log;
	int i_adm;
	int type_mnger;//三员分立判断设备管理员或审计员
	ULONG uiKeyLen;
	CString ip;
	char uiIP[32];

	void GetMngrType(int *num);
	afx_msg void OnStnClickedStaticResigadmin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void closeWindows();
};
