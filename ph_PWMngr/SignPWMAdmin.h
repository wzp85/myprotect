#pragma once
#include "afxwin.h"

//extern DEVHANDLE smart_DeviceHandle;
// CSignPWMAdmin 对话框

class CSignPWMAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CSignPWMAdmin)

public:
	//1 表示是密钥管理员,0表示是设备管理员，2表示是安全审计员
	CSignPWMAdmin(int isOneToMore,int isKeyManager,int keyManagerNum,int isReSig,int keylen,int n_Count,CString data,void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSignPWMAdmin();

// 对话框数据
	enum { IDD = IDD_SIGPWDADMIN_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

	int isReSigAdmin;//0表示正常签发，1表示重新签发

	int isKMer;
	int KMerNumber;

	int isOneToMore_kmer;//当多对一的时候记录当前是第几个密钥管理员
};
