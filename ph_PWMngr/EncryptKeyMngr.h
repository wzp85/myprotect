#pragma once
#include "afxcmn.h"

#include "EncryptKeyGen.h"
#include "EncryptKeyResume.h"

// CEncryptKeyMngr 对话框

class CEncryptKeyMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryptKeyMngr)

public:
	typedef struct EncKeyInfo_Search
	{
		int index;
		char kekName[64];
		char algId[32];
		char ifBack[32];
		char keyTime[32];
	}EKISH;
	CEncryptKeyMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncryptKeyMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGEENCRYPT };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtrlEncryptKey;
	afx_msg void OnBnClickedEncryptsearchButton();
	afx_msg void OnRclickEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSAddek();
	afx_msg void OnUpdateek();
	afx_msg void OnDistroyek();
	afx_msg void OnBackupek();
	afx_msg void OnResumeek();
	void ShowEncryptKeyInfo();
	void ShowEncryptKeyInfo_Search(CString appName,CString keyIndex);

	void *phHandle_ek;
	int index_max_ek;
	int keyIndex_ek[256][2];
	CString m_keyIndex_ek;
	CString m_kekName_ek;

	unsigned char sys_Key_1_ek[256];
	unsigned char sys_Key_2_ek[256];
	unsigned char sys_Key_3_ek[256];

	BOOL isCheckbox_ek;
	int check_ek[256];
	int i_checked_ek;

	int nId_row;
	int nId_row_mux_ek[256];
	afx_msg void OnLvnItemchangedEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);
	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);
	afx_msg void OnItemstateiconclickEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL PreTranslateMessage(MSG* pMsg);
};
