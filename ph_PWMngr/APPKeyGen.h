#pragma once
#include "afxwin.h"


// CAPPKeyGen �Ի���

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
	CAPPKeyGen(BOOL isUpdate,void *handle,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAPPKeyGen();

// �Ի�������
	enum { IDD = IDD_APPKEY_GEN_DIALOG };

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

	int keyIndex_max;//�������ý��������ŵ�Ĭ����ʾֵ
	int index_array[256][2];//�ɹ�ѡ�������������
	//HWND pWnd;
	//CListCtrl* listctrl_appGen;

	UIG uig;
	int isReallyUpdated;
	void GetisReallyUpdated(int *x);
};
