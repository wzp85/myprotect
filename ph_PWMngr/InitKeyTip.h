#pragma once


// CInitKeyTip �Ի���

class CInitKeyTip : public CDialogEx
{
	DECLARE_DYNAMIC(CInitKeyTip)

public:
	CInitKeyTip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitKeyTip();

// �Ի�������
	enum { IDD = IDD_TIP_INITKEY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
