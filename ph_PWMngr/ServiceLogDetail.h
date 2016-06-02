#pragma once
#include "afxwin.h"


// CServiceLogDetail 对话框

class CServiceLogDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceLogDetail)

public:
	CBrush m_brush;
	CFont m_font;
	CServiceLogDetail(void *phHandle,int ID,CString name,CString sn,CString hashalgid,CString symmalgid,CString plaindata,CString cipherdata,CString cert,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServiceLogDetail();

// 对话框数据
	enum { IDD = IDD_DIALOG_sl_detail };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckLOG();
	afx_msg void OnBnClickedCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) ;
	CStatic m_sld_title;

	CString in_name;
	CString in_sn;
	CString in_hashalgid;
	CString in_symmalgid;
	CString in_plaindata;
	CString in_cipherdata;
	CString in_cert;
	int in_id;
	void *in_phHandle;
};
