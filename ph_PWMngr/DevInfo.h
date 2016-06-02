#pragma once


// CDevInfo 对话框

class CDevInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CDevInfo)

public:
	CDevInfo();
	virtual ~CDevInfo();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LARGEDEVINFO };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString m_devMactuName;
	CString m_devName;
	CString m_devSerial;
	CString m_devVersion;
	CString m_symmAlgid;
	CString m_asymmAlgid;
	CString m_hashAlgid;
	CString m_maxSize;
	CString m_stdVersion;

	void *phHandle;
	BOOL PreTranslateMessage(MSG* pMsg);
};
