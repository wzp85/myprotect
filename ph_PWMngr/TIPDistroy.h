#pragma once


// CTIPDistroy �Ի���

class CTIPDistroy : public CDialogEx
{
	DECLARE_DYNAMIC(CTIPDistroy)

public:
	CTIPDistroy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTIPDistroy();

// �Ի�������
	enum { IDD = IDD_TIP_DISTROY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
