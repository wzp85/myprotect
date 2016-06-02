#pragma once
#include "afxwin.h"


// CSeeLogDetail �Ի���

class CSeeLogDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CSeeLogDetail)

public:
	CBrush m_brush;
	CFont m_font;
	CSeeLogDetail(CString logid,CString admid,CString opk,CString opd,CString oper,CString opre,CString opdetail,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSeeLogDetail();

// �Ի�������
	enum { IDD = IDD_LOG_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CString param_logid;
	CString param_admid;
	CString param_opk;
	CString param_opd;
	CString param_oper;
	CString param_opre;
	CString param_opdetail;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) ;
	CStatic m_lgd_title;
};
