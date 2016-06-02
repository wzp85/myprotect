#pragma once

#include "ph_km.h"
#include "afxcmn.h"
// CDevIPMngr 对话框

class CDevIPMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevIPMngr)

public:
	CDevIPMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevIPMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGE_DEVIPMNGR };

protected:
	HICON m_hIcon;
	int  selectType;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_line1_static;
	CString m_line2_static;
	CString m_line3_static;
	CString m_line4_static;
	CString m_line5_static;
	afx_msg void OnBnClickedAppRadio();
	afx_msg void OnBnClickedMngrRadio();
	int m_MngrRadio;
	int m_AppRadio;
	CIPAddressCtrl m_NetConfig1;
	CIPAddressCtrl m_NetConfig2;
	CIPAddressCtrl m_NetConfig3;
	CIPAddressCtrl m_NetConfig4;
	CIPAddressCtrl m_NetConfig5;



	CString StrMngConfig1;
	CString StrMngConfig2;
	CString StrMngConfig3;
	CString StrMngConfig4;
	CString StrMngConfig5;
	
	CString StrAppConfig1;	
	CString StrAppConfig2;
	CString StrAppConfig3;
	CString StrAppConfig4;
	CString StrAppConfig5;
	int m_Radio;
	void *phHandle_ip;
	DWORD m_Mask;
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
};
