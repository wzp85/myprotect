#pragma once
#include "afxwin.h"


// CChoseAlgid 对话框

class CChoseAlgid : public CDialogEx
{
	DECLARE_DYNAMIC(CChoseAlgid)

public:
	CFont font;
	/*void OnInitDialog();*/
	CChoseAlgid(void *key_handle,void *hSessionHandle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChoseAlgid();

// 对话框数据
	enum { IDD = IDD_CHOSEALG_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
