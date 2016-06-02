#pragma once


// CUpdateSetMngr dialog

class CUpdateSetMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSetMngr)

public:
	CUpdateSetMngr(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUpdateSetMngr();

// Dialog Data
	enum { IDD = IDD_UPDATE_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
