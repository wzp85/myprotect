#pragma once


// CDevKeyMngr �Ի���

class CDevKeyMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevKeyMngr)

public:
	CDevKeyMngr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDevKeyMngr();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
