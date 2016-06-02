#pragma once
#include "afxwin.h"


// CSeeDetail �Ի���

class CSeeDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CSeeDetail)

public:
	CSeeDetail(LPCTSTR keyIndex,LPCTSTR appName,LPCTSTR algId,LPCTSTR keyType,CWnd* pParent = NULL);
	CSeeDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSeeDetail();

// �Ի�������
	enum { IDD = IDD_SEEDETAIL_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_appName;
	CComboBox m_algId;
	CString m_algId_show;
	CComboBox m_keyIndex;
	CString m_keyIndex_show;
	CComboBox m_appType;
	CComboBox m_keyType;
	CString m_keyType_show;
};
