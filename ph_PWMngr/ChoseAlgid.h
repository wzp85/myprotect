#pragma once
#include "afxwin.h"


// CChoseAlgid �Ի���

class CChoseAlgid : public CDialogEx
{
	DECLARE_DYNAMIC(CChoseAlgid)

public:
	CFont font;
	/*void OnInitDialog();*/
	CChoseAlgid(void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChoseAlgid();

// �Ի�������
	enum { IDD = IDD_CHOSEALG_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_chosedAlgId;
	afx_msg void OnCbnSelchangeAlgidCombo();
	afx_msg void OnBnClickedOk();
	CString m_title;
	void *phSHandle;
	void *key_phSHandle;
	//CString algid;
	unsigned int m_algId;
	CString m_algid_cs;
};
