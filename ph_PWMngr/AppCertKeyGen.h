#pragma once
#include "afxwin.h"


// CAppCertKeyGen 对话框

class CAppCertKeyGen : public CDialogEx
{
	DECLARE_DYNAMIC(CAppCertKeyGen)

public:
	CAppCertKeyGen(void *handle,int isUpDate,CString certname,CString city,CString nation,CString area,CString organization,CString email,CString organizationUnite,CString keyIndex,CString algid,CString keyType,CWnd* pParent = NULL);   // 标准构造函数
	CAppCertKeyGen(void *handle,int isUpDate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppCertKeyGen();

// 对话框数据
	enum { IDD = IDD_APPCERT_KEY_GEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CString m_ac_appName;
	CComboBox m_ac_alg;
	CString m_ac_alg_cs;
	CComboBox m_ac_index;
	CString m_ac_index_cs;
	CComboBox m_ac_appType;
	CString m_ac_appType_cs;
	CComboBox m_ac_keyType;
	CString m_ac_keyType_cs;
	CString m_ac_pinf;
	CString m_ac_pins;
	CString m_ac_cnName;
	CComboBox m_ac_cityName;
	CString m_ac_cityName_cs;
	CString m_ac_atName;
	CComboBox m_ac_areaName;
	CString m_ac_areaName_cs;
//	CString m_atUnitName;
	CString m_ac_eMail;
	afx_msg void OnCbnSelchangeComboAccityname();

	void WriteCityInfo();
	void ShowCityInfo(int num);
	void WriteProviceInfo(CString ProName,char *city,int num);
	void ReadProviceInfo(CString ProName);
	void SetReadOnly();
	int isUp;//是更新还是生成,0是更新
	BOOL PreTranslateMessage(MSG* pMsg);// 屏蔽ESC和enter键

	void *phHandle_appCertMngr;
	int acKeyIndex;
	int acKeyIndex_array[256][2];
	CString m_ac_OUvalue;


	CString in_certname;
	CString in_city;
	CString in_nation;
	CString in_area;
	CString in_organization;
	CString in_email;
	CString in_organizationUnite;
	CString in_keyIndex;
	CString in_algid;
	CString in_keyType;

	void GetCityInUpdate(CString city,int *num);
	afx_msg void OnCbnSelchangeComboAcindex();
};
