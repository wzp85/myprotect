#pragma once
#include "afxwin.h"


// CTIPFormat 对话框

class CTIPFormat : public CDialogEx
{
	DECLARE_DYNAMIC(CTIPFormat)

public:
	CBrush m_brush;
	CFont m_font;
	CTIPFormat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTIPFormat();

// 对话框数据
	enum { IDD = IDD_TIP_FORMAT_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_myStatic;
	CString m_myStatic_line1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) ;
};
