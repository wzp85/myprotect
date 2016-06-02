#pragma once


// CTIPDistroy 对话框

class CTIPDistroy : public CDialogEx
{
	DECLARE_DYNAMIC(CTIPDistroy)

public:
	CTIPDistroy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTIPDistroy();

// 对话框数据
	enum { IDD = IDD_TIP_DISTROY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
