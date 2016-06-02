#pragma once


// CChoseFilePath 对话框
#define APP_BACKUP			0
#define ENC_BACKUP			1
#define DEV_BACKUP			2
#define ADM_BACKUP			3

#define SIG_APPBAK			4
#define SIG_CACERTBAK		5
#define SIG_RTCERTBAK		6
#define SIG_SERVICELOGBAK	8

class CChoseFilePath : public CDialogEx
{
	DECLARE_DYNAMIC(CChoseFilePath)

public:
	CChoseFilePath(unsigned char *rand_in,CString ifSingleBackup,unsigned char *k,unsigned int uiKeyIndexNum,unsigned int *puiKeyIndex,int type,void *phSession,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChoseFilePath();

// 对话框数据
	enum { IDD = IDD_CHOSEFILEPATH_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	CString filePath;
	void *handle;
	CString index;
	unsigned int isSingleChoice;
	CString ctrlsName_ifSingle;
	unsigned int in_KeyIndex[257];
	int type_Backup;
	unsigned char in_pucKeyBackupKey[17];
	CString m_filepath_withoutclick;

	unsigned char rand_in[32];
};
