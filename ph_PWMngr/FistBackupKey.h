#pragma once
#include "afxwin.h"


// CFistBackupKey 对话框

class CFistBackupKey : public CDialogEx
{
	DECLARE_DYNAMIC(CFistBackupKey)

public:
	CFont line1;
	CFistBackupKey(BYTE *iRand,BYTE *backRand,BYTE *SymmKey,unsigned char *k,int k_len,int i_Count,CString in_data,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFistBackupKey();

// 对话框数据
	enum { IDD = IDD_FIRSTPWD_DIALOG };

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_firstkeypwd;
	CString m_firstkeyconpwd;
	CString m_line1;

	unsigned char ucSymmkey[16];

	unsigned char Sysmk[256];
	unsigned int Sysmk_len_in;
	int tCount;

	BYTE *sign_random[5];
	int isGen;//1表示生成
	BYTE i_random[19];
	//BOOL isFirstGenKey;
};
