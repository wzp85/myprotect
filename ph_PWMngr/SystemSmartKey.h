#pragma once
#include "afxwin.h"


// CSystemSmartKey �Ի���

class CSystemSmartKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSmartKey)

public:
	CFont font;
	CSystemSmartKey(int isResig,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemSmartKey();

// �Ի�������
	enum { IDD = IDD_INSERTSC_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	
	int isReSig;//����Ϊ0��ʾΪ������ʼ����Ϊ1��ʾ����ǩ������Ա
};
