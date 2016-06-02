// AppCertKeySet.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertKeySet.h"
#include "afxdialogex.h"
#include "Resource.h"


#include "ph_km.h"
// CAppCertKeySet 对话框
unsigned int KeysetType = 0;
unsigned int Keyindex = 0;//密钥选中索引

unsigned int Type = 0;//-------用于更新显示
unsigned int index = 0;
CString Number;
IMPLEMENT_DYNAMIC(CAppCertKeySet, CDialogEx)

CAppCertKeySet::CAppCertKeySet(void *handle,int isUpDate,int puiKeyIndex,CWnd* pParent  /*=NULL*/)
	: CDialogEx(CAppCertKeySet::IDD, pParent)
	, m_TimeSeriNum_CS(_T(""))
{
	phHandle_appCertMngr = handle;
	isType = isUpDate;
	Keyindex = puiKeyIndex;
}

CAppCertKeySet::~CAppCertKeySet()
{
}

void CAppCertKeySet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TimeSeriNum, m_TimeSeriNum_CBOX);
}


BEGIN_MESSAGE_MAP(CAppCertKeySet, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CAppCertKeySet::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAppCertKeySet::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CAppCertKeySet::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CAppCertKeySet::OnBnClickedRadio4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAppCertKeySet::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CAppCertKeySet::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_TimeSeriNum, &CAppCertKeySet::OnCbnSelchangeComboTimeserinum)
END_MESSAGE_MAP()


// CAppCertKeySet 消息处理程序


void CAppCertKeySet::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	//只用于数字签名
	KeysetType = 1;

	keyIndex=0;

	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	//数字签名时间戳公用
	KeysetType = 2;
	keyIndex=0;
	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	//数字签名时间戳不共用
	KeysetType = 3;
	m_TimeSeriNum_CBOX.EnableWindow(TRUE);
	CString KeyIndex;
		CString index;
		index.Format("%d",1);
		KeyIndex = "00"+index;//数据的格式化操作，需要再写一个新的方法 
		SetDlgItemText(IDC_COMBO_TimeSeriNum,KeyIndex);

		int data = 0;
		for( int i=1;i<100;i++)
		{
				//data = i;
				index.Format("%d",i);
				KeyIndex = "00"+index;
				//m_TimeSeriNum_CBOX.AddString(keyIndex);
				m_TimeSeriNum_CBOX.InsertString(i-1,_T(KeyIndex));
			
		}
	keyIndex=1;
}
void CAppCertKeySet::showTimeSeriNum(CString Number)
{
		CString KeyIndex;
		CString index;
		
		SetDlgItemText(IDC_COMBO_TimeSeriNum,Number);

		int data = 0;
		for( int i=1;i<100;i++)
		{
				//data = i;
				index.Format("%d",i);
				KeyIndex = "00"+index;
				//m_TimeSeriNum_CBOX.AddString(keyIndex);
				m_TimeSeriNum_CBOX.InsertString(i-1,_T(KeyIndex));
			
		}
	keyIndex=1;
}

void CAppCertKeySet::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	//只用于时间戳
	KeysetType = 4;
	keyIndex=0;
	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel; 
    nSel =m_TimeSeriNum_CBOX.GetCurSel(); //获取组合框控件列表里的选中项索引
	keyIndex=nSel+1;

	m_TimeSeriNum_CS.Format("%d", (nSel+1));
	m_TimeSeriNum_CBOX.GetLBText(nSel,m_TimeSeriNum_CS);
}


void CAppCertKeySet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/******************获取密钥属性及对应索引号*********************************/
	CString TimeSerinum;
	unsigned int KeyType = 0;
	unsigned int keyIndex1 = 0;
	KeyType = KeysetType;//密钥属性
	TimeSerinum = m_TimeSeriNum_CS;//对应索引号
	
	keyIndex1 = Keyindex;
	void * hSessionHandle = phHandle_appCertMngr;
	int ret = Sig_AppCertKeySet(hSessionHandle,Keyindex,&KeyType,(unsigned int *)&keyIndex,1); //1表示设置
	Type = KeyType;//---获取接口返回的值
	index = keyIndex;
	CDialogEx::OnOK();
}


void CAppCertKeySet::OnCbnSelchangeComboTimeserinum()
{
	// TODO: 在此添加控件通知处理程序代码
	//int nSel; 
 //   nSel =m_TimeSeriNum_CBOX.GetCurSel(); //获取组合框控件列表里的选中项索引
	//m_TimeSeriNum_CS.Format("%d", (nSel+1));
	//m_TimeSeriNum_CBOX.GetLBText(nSel,m_TimeSeriNum_CS);//根据索引获取对应字符串
}


BOOL CAppCertKeySet::OnInitDialog()
{
	int KeyType=0;
	 keyIndex=0;
	
	void * hSessionHandle = phHandle_appCertMngr;


	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_TimeSeriNum))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CWnd *cWnd = GetDlgItem(IDC_STATIC_AppKeySet);

	//int ret = Sig_AppCertKeySet(hSessionHandle,Keyindex,(unsigned int *)&KeyType,(unsigned int *)&keyIndex,0); //1表示设置
	//Type = KeyType;//---获取接口返回的值
	
	if(isType == 1)
	{
		this->SetWindowText("密钥属性的设置");
		cWnd->SetWindowText("密钥属性的设置");
		CString index_cs;
		index_cs.Format("%d",index);
		Number = "00"+index_cs;

		switch(Type)
		{
		case 2:
			CheckDlgButton(IDC_RADIO2,2);
			break;
		case 3:
			CheckDlgButton(IDC_RADIO3,3);
			showTimeSeriNum(Number);
		default:
			break;
		}
	
	}
	if(isType == 2)
	{
		this->SetWindowText("密钥属性的更新");
		cWnd->SetWindowText("密钥属性的更新");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
