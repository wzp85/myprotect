
// ph_PWMngrDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cph_PWMngrDlg �Ի���
class Cph_PWMngrDlg : public CDialogEx
{
// ����
public:
	CString m_szCaption;
	Cph_PWMngrDlg(CString ip,int i,void *phSHandle,void *key_phSHandle,void *containerHandle,LPCTSTR szCaption,CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PH_PWMNGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_loginPINedit;
	afx_msg void OnBnClickedCancel();
	//afx_msg void OnBnClickedInitButton();
	CIPAddressCtrl m_ipAddress;
	
	void *phSHandle;
	void *key_phSHandle;
	void *key_containerHandle;
	afx_msg void OnClickedSysinitStatic();
	CComboBox m_ip_log;
	CString m_ip;

	void GetMaxAdminLogin(double *num);
	int adm_Num_log;
	int i_adm;
	int type_mnger;//��Ա�����ж��豸����Ա�����Ա
	ULONG uiKeyLen;
	CString ip;
	char uiIP[32];

	void GetMngrType(int *num);
	afx_msg void OnStnClickedStaticResigadmin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void closeWindows();
};
