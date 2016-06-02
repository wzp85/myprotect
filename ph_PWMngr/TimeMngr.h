#pragma once


#include "afxcmn.h"
#include "afxwin.h"
// CAPPKeyMngr 对话框

class CTimeMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeMngr)

public:
	/*int chose;*/
	//	CRect tabRect;

	//CAPPKeyBackup appKeyBackup;
	//CAPPKeyUpdate m_appKeyUpdate;
	//CAPPKeyResume m_appKeyResume;
	//CAPPKeyDistroy m_appKeyDistroy;
	//CAPPKeyChangePIN m_appKeyChangePIN;

	typedef struct KeyInfo_Search
	{
		int index;
		char appName[32];
		char algId[32];
		char keyLength[32];
		char keyType[32];
		char ifBack[32];
		char modifyTime[32];
	}KISH;
	CTimeMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeMngr();

	// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGETIME };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//	afx_msg void OnTcnSelchangeAppkeymngrTab(NMHDR *pNMHDR, LRESULT *pResult);
	//	CTabCtrl m_tab;
	CListCtrl m_listCtrlAppkey;
	//	afx_msg void OnNMDblclkAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdate();
	afx_msg void OnBackup();
	afx_msg void OnResume();
	afx_msg void OnDistroy();
	
	//	afx_msg void OnSeedetail();
	afx_msg void OnAddappkey();
	void setIndex(int index);

	void *phHandle;
	int index_max;
	int keyIndex[256][2];//

	afx_msg void OnBnClickedSearchkeylistButton();
	void ShowAppKeyInfo();
	void ShowAppKeyInfo_Search(CString appName,CString keyIndex);
	CString m_key_index;
	CString m_key_appName;

	unsigned char sys_Key_1[256];
	unsigned char sys_Key_2[256];
	unsigned char sys_Key_3[256];
	afx_msg void OnLvnItemchangedAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL isCheckbox;
	int check[256];
	int i_checked;
	afx_msg void OnItemstateiconclickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult);
	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);

	int nId_row;
	int nId_row_mux[256];
	BOOL PreTranslateMessage(MSG* pMsg);
};
