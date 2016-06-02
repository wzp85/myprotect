#pragma once
#include "afxwin.h"



// CEncryptKeyGen 对话框

class CEncryptKeyGen : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryptKeyGen)

public:
	typedef struct UpdateInGen
	{
		unsigned int index;
		unsigned int index_num;
	}UIG_EK;
	CFont line1;
	CEncryptKeyGen(void *hSessionHandle,LPCTSTR keyIndex,LPCTSTR algId,CWnd* pParent = NULL);
	CEncryptKeyGen(void *handle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncryptKeyGen();

// 对话框数据
	enum { IDD = IDD_ENCRYPTKEY_GEN_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CString m_keyDiscription;
	CComboBox m_thealgId;
	CComboBox m_theKeyIndex;
	CStatic m_theline1;
	afx_msg void OnCbnSelchangeThealgidCombo();
	afx_msg void OnBnClickedCancel();

	void *phHandle;
	int keyIndex_max_ek;//
	//CString keyIndex_max_ek_lztocs;
	int index_array_ek[256][2];
	CString m_algId;
	CString m_index_ek;

	UIG_EK uig_ek;
};
