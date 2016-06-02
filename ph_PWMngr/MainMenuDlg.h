#pragma once


// CMainMenuDlg �Ի���

#include "DevkeyBACKUP.h"
#include "APPKeyMngr.h"
#include "EncryptKeyMngr.h"
#include "BackupKeyGen.h"
#include "DevAdminMngr.h"
#include "DevInfo.h"
#include "DevIPMngr.h"
#include "DevAdminKeyMngr.h"
#include "afxcmn.h"
#include "AppCertMngr.h"
#include "CACertMngr.h"
#include "ROOTCertMngr.h"
#include "LogQuery.h"
#include "ServiceLogMngr.h"
#include "AppIpMngr.h"
#include "MngrLogAudit.h"
#include "ServiceLogAudit.h"
#include "ErrorLogAudit.h"
#include "SysLogQuery.h"
#include "TimeMngr.h"
#include "UpdateSetMngr.h"

class CMainMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainMenuDlg)

public:
	CRect tabRect;
	CString m_szCaption;

	CDevkeyBACKUP devkeyBACKUP;
	CAPPKeyMngr appkeyMngr;
	CEncryptKeyMngr encryptkeyMngr;
	CBackupKeyGen backkeyGen;
	CDevAdminMngr devadminMngr;
	CDevInfo devInfo;
	CDevIPMngr devIPMngr;
	CDevAdminKeyMngr devAdminKeyMngr;

	 CTimeMngr timeMngr;
	CAppCertMngr appCertMngr;
	CCACertMngr CACertMngr;
	CROOTCertMngr rootCertMngr;
	CUpdateSetMngr  updateSetMngr;
	CLogQuery logQueryDlg;
	CServiceLogMngr serviceLogMngr;

	CAppIpMngr appIpMngr;
	CMngrLogAudit mngrLogAudit;
	CServiceLogAudit serviceLogAudit;
	CErrorLogAudit errorLogAudit;
	CSysLogQuery sysLogQuery;

	CMainMenuDlg(int MngrType,int TypeofMnger,int admCount,int adm,void *km_sessionhandle,LPCTSTR szCaption,LPCTSTR szIP,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainMenuDlg();

// �Ի�������
	enum { IDD = IDD_MAINMENU_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_mainMenuTab;
	void *phHandle;

	int Mngr_Type;
	int mnger_type;
	BYTE * pConfigData ;//add by syc
};
