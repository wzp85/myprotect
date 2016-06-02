#pragma once


// CSysSmartKey 对话框

class CSysSmartKey : public CDialogEx
{
	DECLARE_DYNAMIC(CSysSmartKey)

public:
	CSysSmartKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysSmartKey();

// 对话框数据
	enum { IDD = IDD_INSERTSC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
