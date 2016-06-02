#pragma once
#include "afxwin.h"


// CAdminGen 对话框

class CAdminGen : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminGen)

public:
	CFont font;
	CAdminGen(int num,void *handle,CWnd* pParent = NULL);   // 标准构造函数
	CAdminGen(CString adm_name,CString adm_index,CString adm_maxNum,CString adm_phoneNum,CString adm_paperType,CString adm_paperNum,void *handle,CWnd* pParent = NULL);
	virtual ~CAdminGen();

// 对话框数据
	enum { IDD = IDD_ADMIN_GEN_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CStatic m_titleline;
	CString m_adminname;
	CString m_phoneNumber;
	CComboBox m_papertype;
	CString m_paperNumber;
	CString m_adminpin;
	CString m_adminpincon;
	CString m_adminMaxCount;
	CComboBox m_adminType;
	CString m_paperType_cs;
	CString m_adminType_cs;

	void *phHandle;
	void *key_phHandle;
	int adm_key_index_max;
	int adm_index_array[16][2];
	afx_msg void OnBnClickedCancel();

	int isUp;

	BOOL isAddOK;
	CEdit m_adm_max_count;

	int admCountInGen;

	int adm_index_in;
	CString adm_name_cs;
	CString adm_maxNum_cs;
	CString adm_phoneNum_cs;
	CString adm_paperType_cs;
	CString adm_paperNum_cs;
	//CComboBox m_adminname_CM;
};
