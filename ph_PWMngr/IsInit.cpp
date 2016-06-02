// IsInit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "IsInit.h"
#include "afxdialogex.h"

#include "ChoseAlgid.h"
#include "ph_PWMngrDlg.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ Version 2.0")

#include "ph_km.h"

// CIsInit �Ի���

IMPLEMENT_DYNAMIC(CIsInit, CDialogEx)

CIsInit::CIsInit(void *key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CIsInit::IDD, pParent)
	, m_line1(_T(""))
{
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "����"));                 // lpszFacename

	VERIFY(font_lineWord.CreateFont(
    15,                        // nHeight
    8,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "����"));                 // lpszFacename

	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
}

CIsInit::~CIsInit()
{
}

void CIsInit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ISINITCON_STATIC, m_line1);
	CWnd *cWnd = GetDlgItem(IDC_ISINITCON_STATIC);
	cWnd->SetFont(&font);
	cWnd->SetWindowText("��֤����ɹ���ϵͳ�Ѿ���ʼ�����Ƿ����³�ʼ����");

	cWnd = GetDlgItem(IDC_LINEWORD_STATIC);
	cWnd->SetFont(&font_lineWord);
	cWnd->SetWindowText("  ע�����³�ʼ������������������������Կ�������������������Կ�Ժ���Ҫ����ʹ�ã���ȷ�ϱ�����Ӧ����Կ����Կ������Կ�Ѿ����ݣ����û�б��ݣ���Ҫ���ݣ������޷��ָ���");
	
	DDX_Control(pDX, IDC_ISINITCON_STATIC, m_isInitCon);
	DDX_Control(pDX, IDC_LINEWORD_STATIC, m_lineWord);
}


BEGIN_MESSAGE_MAP(CIsInit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIsInit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CIsInit::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CIsInit ��Ϣ�������
HBRUSH CIsInit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(m_isInitCon.m_hWnd == pWnd->m_hWnd)
	{
	   //pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&font);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //���ؿջ�ˢ����һ����ȥ������ɫ��
		//return m_brush;
	}
	if(m_lineWord.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&font_lineWord);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextCharacterExtra(1);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //���ؿջ�ˢ����һ����ȥ������ɫ��
	}

	return hbr;
}


void CIsInit::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	INT_PTR nRes;   
  
    // ��ʾ��Ϣ�Ի���  
    nRes = MessageBox(_T("���������������������������Կ����ȷ���Ƿ��Ѿ�������Կ"),_T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��  
    if (IDCANCEL == nRes)   
        return; 
	nRes = MessageBox(_T("������ȷ������������Կ"),_T("��ʾ"),MB_OKCANCEL | MB_ICONWARNING);
	if(IDOK != nRes)
		return;
	this->OnOK();
	//----------------������������Կ�ӿ�------------------------//
	int ret = 0;
	//void ** phSessionHandle;
	//phSessionHandle = m_phSessionHandle;
	ret = Km_GenMainKey(phSHandle);
	if(!ret)
	{
		CChoseAlgid choseAlgidDlg(key_phSHandle,phSHandle);
		choseAlgidDlg.DoModal();
	}
	else
	{
		char outGmk[100]={0x00};
		retValueParse(ret,outGmk);
		MessageBox("��������Կʧ��"+(CString)outGmk);
		return;
	}
}


void CIsInit::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	Cph_PWMngrDlg ph_PWMngrDlg(NULL,1,NULL,NULL,NULL,PWMMNGR_CAPTION);
	ph_PWMngrDlg.DoModal();
}
