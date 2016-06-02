#pragma once
#include "afxcmn.h"

#include "AdminGen.h"

// CDevAdminMngr 对话框

class CDevAdminMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevAdminMngr)

public:
	typedef struct AdmInfo_Search
	{
		int index;
		char name[32];
		char phone[32];
		int paperType;
		char paperNunber[32];
		int max;
	}AISH;
	CDevAdminMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevAdminMngr();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGEADMINMNGR };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdminsearchButton();
	CString m_adminIndex_sh;
	CString m_adminName_sh;
	CListCtrl m_listCtrlAdminMngr;
	void *phHandle_adm;

	void ShowAdminInfo();
	void ShowAdminInfo_Search(CString admName,CString admIndex);
	afx_msg void OnNMRClickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddadm();
	afx_msg void OnUpdateadm();
	afx_msg void OnDeladm();

	int admin_index_max;
	int admin_keyIndex[16][2];
	afx_msg void OnLvnItemchangedDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemstateiconclickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult);
	void CheckAllItems(BOOL fChecked);
	void SetHeaderCheckbox(void);

	BOOL isCheckbox_adm;
	int check_adm[256];
	int i_checked_adm;

	int nId_row_adm;
	int nId_row_adm_mux[256];

	int adm_ind;
	int nID;
	int admCountInShow;

	afx_msg void OnNMClickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL m_bHit;
	int m_itemSel;
	afx_msg void OnBackupadm();
	BOOL PreTranslateMessage(MSG* pMsg);
};
