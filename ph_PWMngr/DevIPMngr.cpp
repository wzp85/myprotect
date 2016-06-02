// DevIPMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevIPMngr.h"
#include "afxdialogex.h"
#include<math.h>
#include "ph_PWMngrDlg.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ����������ϵͳ Version 2.0")
// CDevIPMngr �Ի���

IMPLEMENT_DYNAMIC(CDevIPMngr, CDialogEx)

CDevIPMngr::CDevIPMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevIPMngr::IDD, pParent)
	, m_line1_static(_T(""))
	, m_line2_static(_T(""))
	, m_line3_static(_T(""))
	//, m_line4_static(_T(""))
	, m_line5_static(_T(""))
	, m_Mask(0)
{

}

CDevIPMngr::~CDevIPMngr()
{
}

void CDevIPMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE1_STATIC, m_line1_static);
	DDX_Text(pDX, IDC_LINE2_STATIC, m_line2_static);
	DDX_Text(pDX, IDC_LINE3_STATIC, m_line3_static);
	//DDX_Text(pDX, IDC_LINE4_STATIC, m_line4_static);
	DDX_Text(pDX, IDC_LINE5_STATIC, m_line5_static);
	DDX_Control(pDX, IDC_IPADDRESS1, m_NetConfig1);
	DDX_Control(pDX, IDC_IPADDRESS2, m_NetConfig2);
	DDX_Control(pDX, IDC_IPADDRESS3, m_NetConfig3);
	//DDX_Control(pDX, IDC_IPADDRESS4, m_NetConfig4);
	DDX_Control(pDX, IDC_IPADDRESS5, m_NetConfig5);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, m_Mask);
}
int powex(int x,int y)
{
	int a=x;
	int b=x;
	int i=0;
	if( 0 == y){
		return 1;
	}
	for(i=0;i<y-1;i++)
	{
		b=b*a;
	}

	return b;
}

int DottedDecimal(unsigned int ulAddr,char * pAddr)
{
	int i = 0;
    char szAddr[16] = {0x00};
	unsigned int ulMask[4] = { 0xFF000000,0x00FF0000,0x0000FF00,0x000000FF };

    for (i = 0; i < 4; i++)
    {
		int l = (ulAddr & ulMask[i]) >> ((3-i) * 8);

		sprintf(szAddr + strlen(szAddr),"%d",l);
		if (i != 3)
			strcat(szAddr, ".");

		printf("szAddr=%s\n",szAddr);
    }
	strcpy(pAddr,szAddr);
	return 0;
}

int GetValue(unsigned char * buff,unsigned int bufflen,char * type,int typelen,unsigned char * typevalue,unsigned int *typevaluelen)
{
	char * pBegin=NULL;
	char * pEnd=NULL;
	pBegin=strstr((char *)buff,type);
	if(NULL==pBegin)
		return -1;

	pBegin+=typelen;
	pEnd=strstr((char *)pBegin,"\n");
	
	*typevaluelen=pEnd-pBegin;
	if(NULL!=typevalue)
		memcpy(typevalue,pBegin,pEnd-pBegin);

	return 0;
}


BOOL CDevIPMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);	

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// Ĭ��ѡ�С�Ӧ�ö˿ڡ���ѡ��ť  
	selectType=2;
    CheckDlgButton(IDC_MNGR_RADIO, 1);   

	OnBnClickedMngrRadio();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDevIPMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDevIPMngr::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDevIPMngr::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_APP_RADIO, &CDevIPMngr::OnBnClickedAppRadio)
	ON_BN_CLICKED(IDC_MNGR_RADIO, &CDevIPMngr::OnBnClickedMngrRadio)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CDevIPMngr::OnIpnFieldchangedIpaddress1)
END_MESSAGE_MAP()


// CDevIPMngr ��Ϣ�������

//����IP����
void CDevIPMngr::OnBnClickedButton1()
{

	int ret=0;
		
	//char *pNet1="BOOTPROTO=static||IPADDR=192.168.100.119||NETMASK=255.255.255.0||GATEWAY=192.168.100.254";

	//char *pNet1="SERVICE=ipv4-static||IP=192.168.1.1||PREFIX=24||GATEWAY=192.168.1.2||BROADCAST=192.168.1.255";


	CString IPControl="SERVICE=ipv4-static";


	CString strm_NetConfig1;

	m_NetConfig1.GetWindowTextA(strm_NetConfig1);

	if(0 == strcmp(strm_NetConfig1,"0.0.0.0"))
	{
		MessageBox("������IP��ַ","��ʾ");
		return;
	}
	else
	{
		IPControl.Append("||IP=");
		IPControl.Append(strm_NetConfig1);
	}


	CString strm_NetConfig2;
	m_NetConfig2.GetWindowTextA(strm_NetConfig2);

	if(0 == strcmp(strm_NetConfig2,"0.0.0.0"))
	{
		MessageBox("��������������","��ʾ");
		return;
	}
	else
	{		
		UpdateData(TRUE);
		unsigned int i=0;
		unsigned int a=0xFFFFFFFF;
		char strMask[64]={0x00};
		
		IPControl.Append("||PREFIX=");	

		for(i=0 ;i<32 ;i++)
		{
			if(a==m_Mask)
				break;
			else
				a=a<<1;
			
		}
		itoa(32-i,strMask,10);

		IPControl.Append(strMask);
	}


	CString strm_NetConfig3;
	m_NetConfig3.GetWindowTextA(strm_NetConfig3);

	if(0 == strcmp(strm_NetConfig3,"0.0.0.0")&&selectType==1)
	{
		MessageBox("���������ص�ַ","��ʾ");
		return;
	}
	else
	{
		IPControl.Append("||GATEWAY=");
		IPControl.Append(strm_NetConfig3);
	}

	CString strm_NetConfig5;
	m_NetConfig5.GetWindowTextA(strm_NetConfig5);

	if(0 != strcmp(strm_NetConfig5,"0.0.0.0"))
	{
		IPControl.Append("||BROADCAST=");
		IPControl.Append(strm_NetConfig5);
		IPControl.Append("||");
	}


	if(1==m_Radio)
	{
		ret=Km_ManagerNetModify(phHandle_ip,(unsigned char *)IPControl.GetBuffer(),IPControl.GetLength());
		if(0==ret)
			MessageBox(_T("�޸ĳɹ�"),"");
		else
		{
			char outMnm[100]={0x00};
			retValueParse(ret,outMnm);
			MessageBox("�޸�ʧ��"+(CString)outMnm,"");
		}
	}
	else if(0==m_Radio)
	{
		ret=Km_AppNetModify(phHandle_ip,(unsigned char *)IPControl.GetBuffer(),IPControl.GetLength());
		if(0==ret)
			MessageBox(_T("�޸ĳɹ�"),"");
		else
		{
			char outMnm[100]={0x00};
			retValueParse(ret,outMnm);
			MessageBox("�޸�ʧ��"+(CString)outMnm,"");
		}
	}
	else
	{
		MessageBox(_T("�ڲ������޸�ʧ��"),"");
	}
	
	return;

}


//��������
void CDevIPMngr::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes = 0;
/*	nRes = MessageBox(_T("�ò������޸��������������,���޸�ʧ��,���ָ������һ����ȷ������,�Ƿ������"),"ע��",MB_ICONWARNING | MB_OKCANCEL);
	if(IDOK != nRes)
		return;
*/
	if(0==m_Radio)
	{
		MessageBox(_T("����Ϊ�����������"),"");
		int ret=Km_NetRestart(phHandle_ip,0);	
		ExitProcess(0);
	}
	else if(1==m_Radio)
	{
		MessageBox(_T("����Ϊ�����������"),"");
		
		int ret=Km_NetRestart(phHandle_ip,1);
		ExitProcess(0);

	}
}

//��ȡӦ�ÿ�IP
void CDevIPMngr::OnBnClickedAppRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *cWnd = GetDlgItem(IDC_LINE1_STATIC);
	cWnd->SetWindowText("Ӧ�ö˿�IP��ַ");
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetWindowText("Ӧ�ö˿���������");
	cWnd = GetDlgItem(IDC_LINE3_STATIC);
	cWnd->SetWindowText("Ӧ�ö˿�Ĭ������");
	cWnd = GetDlgItem(IDC_LINE5_STATIC);
	cWnd->SetWindowText("Ӧ�ö˿ڹ㲥��ַ");


	int ret=0;
	
	unsigned int Netbufflen=0;
	unsigned char Netbuff[1024]={0x00};
	
	unsigned int bufflen=0;
	unsigned char buff[32]={0x00};

	//��ȡӦ�ÿ�IP����
	selectType=1;
	ret=Km_GetNetConfig(phHandle_ip,0,Netbuff,&Netbufflen);

	if(ret!=0)
	{
		StrAppConfig1.Format("%s","0.0.0.0");
		StrAppConfig2.Format("%s","0.0.0.0");
		StrAppConfig3.Format("%s","0.0.0.0");
		StrAppConfig5.Format("%s","0.0.0.0");
	}
	else
	{
		//MessageBox((LPCTSTR)Netbuff,"CONFIG",MB_OK);
	
		ret=GetValue(Netbuff,Netbufflen,"IP=",strlen("IP="),buff,&bufflen);
		if(0 == ret)
		{
			StrAppConfig1.Format("%s",buff);
		}
	
		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"PREFIX=",strlen("PREFIX="),buff,&bufflen);
		if(0 == ret)
		{
			int a=atoi((char *)buff);

			char strmask[64]={0x00};

			DottedDecimal(powex(2,32)-powex(2,32-a),strmask);

			StrAppConfig2=strmask;
		}

		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"GATEWAY=",strlen("GATEWAY="),buff,&bufflen);
		if(0 == ret)
		{
			StrAppConfig3.Format("%s",buff);
		}
	
		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"BROADCAST=",strlen("BROADCAST="),buff,&bufflen);
		if(0 == ret)
		{
			StrAppConfig5.Format("%s",buff);
		}	
		else
		{
			StrAppConfig5.Format("%s","0.0.0.0");
		}	
	}
	UpdateData(TRUE);


	m_NetConfig1.SetWindowText(StrAppConfig1);
	m_NetConfig2.SetWindowText(StrAppConfig2);
	m_NetConfig3.SetWindowText(StrAppConfig3);
	m_NetConfig5.SetWindowText(StrAppConfig5);

	m_Radio=0;
}

//��ȡ�����IP
void CDevIPMngr::OnBnClickedMngrRadio()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *cWnd = GetDlgItem(IDC_LINE1_STATIC);
	cWnd->SetWindowText("����˿�IP��ַ");
	cWnd = GetDlgItem(IDC_LINE2_STATIC);
	cWnd->SetWindowText("����˿���������");
	cWnd = GetDlgItem(IDC_LINE3_STATIC);
	cWnd->SetWindowText("����˿�Ĭ������");
	cWnd = GetDlgItem(IDC_LINE5_STATIC);
	cWnd->SetWindowText("����˿ڹ㲥��ַ");


	int ret=0;


	unsigned int Netbufflen=0;
	unsigned char Netbuff[1024]={0x00};
	
	unsigned int bufflen=0;
	unsigned char buff[32]={0x00};
	selectType=2;
	//��ȡ�����IP����
	ret=Km_GetNetConfig(phHandle_ip,1,Netbuff,&Netbufflen);
	if(ret!=0)
	{
		StrMngConfig1.Format("%s","0.0.0.0");
		StrMngConfig2.Format("%s","0.0.0.0");
		StrMngConfig3.Format("%s","0.0.0.0");
		StrMngConfig5.Format("%s","0.0.0.0");

	}
	else{
		//MessageBox((LPCTSTR)Netbuff,"CONFIG",MB_OK);

		ret=GetValue(Netbuff,Netbufflen,"IP=",strlen("IP="),buff,&bufflen);
		if(0 == ret)
		{
			StrMngConfig1.Format("%s",buff);
		}
	
		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"PREFIX=",strlen("PREFIX="),buff,&bufflen);
		if(0 == ret)
		{	
			int a=atoi((char *)buff);

			char strmask[64]={0x00};

			DottedDecimal(powex(2,32)-powex(2,32-a),strmask);

			StrMngConfig2=strmask;

		}
	
		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"GATEWAY=",strlen("GATEWAY="),buff,&bufflen);
		if(0 == ret)
		{
			StrMngConfig3.Format("%s",buff);
		}
	
		memset(buff,0x00,32);
		ret=GetValue(Netbuff,Netbufflen,"BROADCAST=",strlen("BROADCAST="),buff,&bufflen);
		if(0 == ret)
		{
			StrMngConfig5.Format("%s",buff);
		}	
		else
		{
			StrMngConfig5.Format("%s","0.0.0.0");
		}
	}


	m_NetConfig1.SetWindowText(StrMngConfig1);
	m_NetConfig2.SetWindowText(StrMngConfig2);
	m_NetConfig3.SetWindowText(StrMngConfig3);
	m_NetConfig5.SetWindowText(StrMngConfig5);

	m_Radio=1;
}


void CDevIPMngr::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
