#pragma once
#include "afxwin.h"


// CSystemSmartKey 对话框

class CSystemSmartKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSmartKey)

public:
	CFont font;
	CSystemSmartKey(int isResig,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemSmartKey();

// 对话框数据
	enum { IDD = IDD_INSERTSC_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//CString m_line1;
	//CString m_usrName;
	afx_msg void OnClickedChangeInitpinStatic();
	//afx_msg void OnEnableChangeInitpinStatic();
	CComboBox m_usrName;
	//CString usrName;
	CComboBox m_mngrIP;
	CString mngrIP;
	CString m_usrPwd;
	/*afx_msg void OnCbnSelchangeUsrnameCombo();
	afx_msg void OnCbnEditchangeUsrnameCombo();*/
	CString m_sUserName;
	CString m_sMngrIp;

	char ip[32];
	
	int isReSig;//该项为0表示为正常初始化，为1表示重新签发管理员
};
