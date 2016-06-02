// AppCertKeySet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertKeySet.h"
#include "afxdialogex.h"
#include "Resource.h"


#include "ph_km.h"
// CAppCertKeySet �Ի���
unsigned int KeysetType = 0;
unsigned int Keyindex = 0;//��Կѡ������

unsigned int Type = 0;//-------���ڸ�����ʾ
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


// CAppCertKeySet ��Ϣ�������


void CAppCertKeySet::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ֻ��������ǩ��
	KeysetType = 1;

	keyIndex=0;

	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ǩ��ʱ�������
	KeysetType = 2;
	keyIndex=0;
	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ǩ��ʱ���������
	KeysetType = 3;
	m_TimeSeriNum_CBOX.EnableWindow(TRUE);
	CString KeyIndex;
		CString index;
		index.Format("%d",1);
		KeyIndex = "00"+index;//���ݵĸ�ʽ����������Ҫ��дһ���µķ��� 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ֻ����ʱ���
	KeysetType = 4;
	keyIndex=0;
	SetDlgItemText(IDC_COMBO_TimeSeriNum," ");
	m_TimeSeriNum_CBOX.EnableWindow(FALSE);
}


void CAppCertKeySet::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel; 
    nSel =m_TimeSeriNum_CBOX.GetCurSel(); //��ȡ��Ͽ�ؼ��б����ѡ��������
	keyIndex=nSel+1;

	m_TimeSeriNum_CS.Format("%d", (nSel+1));
	m_TimeSeriNum_CBOX.GetLBText(nSel,m_TimeSeriNum_CS);
}


void CAppCertKeySet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	/******************��ȡ��Կ���Լ���Ӧ������*********************************/
	CString TimeSerinum;
	unsigned int KeyType = 0;
	unsigned int keyIndex1 = 0;
	KeyType = KeysetType;//��Կ����
	TimeSerinum = m_TimeSeriNum_CS;//��Ӧ������
	
	keyIndex1 = Keyindex;
	void * hSessionHandle = phHandle_appCertMngr;
	int ret = Sig_AppCertKeySet(hSessionHandle,Keyindex,&KeyType,(unsigned int *)&keyIndex,1); //1��ʾ����
	Type = KeyType;//---��ȡ�ӿڷ��ص�ֵ
	index = keyIndex;
	CDialogEx::OnOK();
}


void CAppCertKeySet::OnCbnSelchangeComboTimeserinum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int nSel; 
 //   nSel =m_TimeSeriNum_CBOX.GetCurSel(); //��ȡ��Ͽ�ؼ��б����ѡ��������
	//m_TimeSeriNum_CS.Format("%d", (nSel+1));
	//m_TimeSeriNum_CBOX.GetLBText(nSel,m_TimeSeriNum_CS);//����������ȡ��Ӧ�ַ���
}


BOOL CAppCertKeySet::OnInitDialog()
{
	int KeyType=0;
	 keyIndex=0;
	
	void * hSessionHandle = phHandle_appCertMngr;


	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_TimeSeriNum))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CWnd *cWnd = GetDlgItem(IDC_STATIC_AppKeySet);

	//int ret = Sig_AppCertKeySet(hSessionHandle,Keyindex,(unsigned int *)&KeyType,(unsigned int *)&keyIndex,0); //1��ʾ����
	//Type = KeyType;//---��ȡ�ӿڷ��ص�ֵ
	
	if(isType == 1)
	{
		this->SetWindowText("��Կ���Ե�����");
		cWnd->SetWindowText("��Կ���Ե�����");
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
		this->SetWindowText("��Կ���Եĸ���");
		cWnd->SetWindowText("��Կ���Եĸ���");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
