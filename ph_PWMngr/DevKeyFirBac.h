#pragma once

//#include "aknutils.h"
// CDevKeyFirBac 对话框

class CDevKeyFirBac : public CDialogEx
{
	DECLARE_DYNAMIC(CDevKeyFirBac)

public:
	CFont font;
	CDevKeyFirBac(int Count,CString dataIn,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevKeyFirBac();

// 对话框数据
	enum { IDD = IDD_DEV_FIRSTBACKUP_DIALOG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_line1;
	CString m_line2;
	CString m_usrPIN;

	unsigned char key_sys[257];
	unsigned int key_sys_len;

	unsigned char keykek[257];
	unsigned int keykek_len;

	int kCount;

	unsigned char kk_rand[32];
	int leng_kk_rand;
	void GetRandomInKey(unsigned char *k_rand);
	void ResetKIR();
	
	virtual BOOL OnInitDialog();

	//BYTE app_bkRand_1[32];
	//BYTE app_bkRand_2[32];

	//BYTE key_i_random[32];
};
