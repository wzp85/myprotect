#pragma once
#include "afxwin.h"


// CIsInit �Ի���

class CIsInit : public CDialogEx
{
	DECLARE_DYNAMIC(CIsInit)

public:
	CFont font;
	CFont font_lineWord;
	CIsInit(void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIsInit();

// �Ի�������
	enum { IDD = IDD_ISINITCON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
