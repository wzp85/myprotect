#pragma once


// CDevKeyMngr 对话框

class CDevKeyMngr : public CDialogEx
{
	DECLARE_DYNAMIC(CDevKeyMngr)

public:
	CDevKeyMngr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevKeyMngr();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
