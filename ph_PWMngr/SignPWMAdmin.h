#pragma once
#include "afxwin.h"

//extern DEVHANDLE smart_DeviceHandle;
// CSignPWMAdmin �Ի���

class CSignPWMAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CSignPWMAdmin)

public:
	//1 ��ʾ����Կ����Ա,0��ʾ���豸����Ա��2��ʾ�ǰ�ȫ���Ա
	CSignPWMAdmin(int isOneToMore,int isKeyManager,int keyManagerNum,int isReSig,int keylen,int n_Count,CString data,void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSignPWMAdmin();

// �Ի�������
	enum { IDD = IDD_SIGPWDADMIN_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_adminName;
	CString m_adminPhonenumber;
	CString m_adminPaperNum;
	CString m_adminPwd;
	CString m_adminConPwd;
	CString m_maxAdminNum;
	CComboBox m_paperType;
	afx_msg void OnCbnSelchangePapertypeCombo();
	void *phSHandle;
	void *key_phSHandle;
	CString m_paperType_CS;

	BOOL isReadOnly;
	int admin_count;
//	CString szData_Caption;
	CString m_caption;
	CEdit m_adminCount;
	int adminNum;

	int num_adm_max;
	void GetMaxAdminNum(int *num);
	int key_length;

	int isTwoPro;
	void GetTwoSigState(int *x);

	int isReSigAdmin;//0��ʾ����ǩ����1��ʾ����ǩ��

	int isKMer;
	int KMerNumber;

	int isOneToMore_kmer;//�����һ��ʱ���¼��ǰ�ǵڼ�����Կ����Ա
};
