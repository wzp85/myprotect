#pragma once
#include "afxwin.h"


// CAPPKeyGen 对话框

class CAPPKeyGen : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPKeyGen)

public:
	typedef struct UpdateInGen
	{
		unsigned int index_uig_num;
		unsigned int index_uig;
	}UIG;

	CAPPKeyGen(BOOL isUpdate,void *hSessionHandle,LPCTSTR keyIndex,LPCTSTR appName,LPCTSTR algId,LPCTSTR keyType,CWnd* pParent = NULL);
	CAPPKeyGen(BOOL isUpdate,void *handle,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAPPKeyGen();

// 对话框数据
	enum { IDD = IDD_APPKEY_GEN_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	CComboBox m_algId;

	CComboBox m_keyIndex;
	CComboBox m_appType;
	CComboBox m_keyType;

	afx_msg void OnCbnSelchangeAlgidCombo();
	afx_msg void OnBnClickedOk();

	void *phHandle;
	CString m_appName;
	CString m_algid_cs;
	CString m_keyindex;
	CString m_keyType_cs;
	CString m_keyPin;
	CString m_keyPinCon;

	int keyIndex_max;//用于设置界面索引号的默认显示值
	int index_array[256][2];//可供选择的索引号数组
	//HWND pWnd;
	//CListCtrl* listctrl_appGen;

	UIG uig;
	int isReallyUpdated;
	void GetisReallyUpdated(int *x);
};
