#pragma once
#include "afxwin.h"


// CAppCertKeySet �Ի���

class CAppCertKeySet : public CDialogEx
{
	DECLARE_DYNAMIC(CAppCertKeySet)

public:
	CAppCertKeySet(CWnd* pParent = NULL);
	CAppCertKeySet(void *handle,int isUpDate,int KeyIndex,CWnd* pParent = NULL);// ��׼���캯��
	virtual ~CAppCertKeySet();
	void *phHandle_appCertMngr;
// �Ի�������
	enum { IDD = IDD_APPCERT_KEYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	CComboBox m_TimeSeriNum_CBOX;
	CString m_TimeSeriNum_CS;
	afx_msg void OnCbnSelchangeComboTimeserinum();
	void showTimeSeriNum(CString Number);//��ʾ���к�
	int isType;
	int keyIndex;
	virtual BOOL OnInitDialog();
};
