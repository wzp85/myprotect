#pragma once


// CSysSmartKey �Ի���

class CSysSmartKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSysSmartKey)

public:
	CSysSmartKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysSmartKey();

// �Ի�������
	enum { IDD = IDD_INSERTSC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
