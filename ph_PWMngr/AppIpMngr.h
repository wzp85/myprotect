#pragma once
#include "afxwin.h"


// CAppIpMngr �Ի���

class CAppIpMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CAppIpMngr)

public:
//	CBrush m_brush;
	CFont m_font;
	CAppIpMngr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppIpMngr();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_APPIP_MNGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonappipmngr();
	void *phHandle_aim;
	virtual BOOL OnInitDialog();
	CStatic m_aim_title;
	afx_msg void OnBnClickedRadioaimopen();
	afx_msg void OnBnClickedRadioaimopenarea();
	afx_msg void OnBnClickedRadioaimopenonly();
	CEdit m_aim_area_edit;
	CEdit m_aim_only_edit;
};
