#pragma once
#include "afxwin.h"


// CTIPFormat �Ի���

class CTIPFormat : public CDialogEx
{
	DECLARE_DYNAMIC(CTIPFormat)

public:
	CBrush m_brush;
	CFont m_font;
	CTIPFormat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTIPFormat();

// �Ի�������
	enum { IDD = IDD_TIP_FORMAT_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_myStatic;
	CString m_myStatic_line1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) ;
};
