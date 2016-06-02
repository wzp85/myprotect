#pragma once
#include "afxwin.h"


// CIsInit 对话框

class CIsInit : public CDialogEx
{
	DECLARE_DYNAMIC(CIsInit)

public:
	CFont font;
	CFont font_lineWord;
	CIsInit(void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIsInit();

// 对话框数据
	enum { IDD = IDD_ISINITCON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_line1;
	void *phSHandle;
	void *key_phSHandle;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) ;
	CStatic m_isInitCon;
	CStatic m_lineWord;
};
