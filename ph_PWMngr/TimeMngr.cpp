// APPKeyMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"

#include "afxdialogex.h"
#include "TimeMngr.h"

#include "SeeDetail.h"

#include "ph_km.h"
#include "MyUtil.h"
#include "TIPDistroy.h"
#include "DevKeyFirBac.h"
#include "ChoseFilePath.h"
#include "APPKeyChangePIN.h"
#include "KeyDevide.h"
#define APPKEY_UPDATA   0x09
// CTimeMngr �Ի���

IMPLEMENT_DYNAMIC(CTimeMngr, CDialogEx)

CTimeMngr::CTimeMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeMngr::IDD, pParent)
	, m_key_index(_T(""))
	, m_key_appName(_T(""))
{
	index_max = 0;
}

CTimeMngr::~CTimeMngr()
{
}

void CTimeMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_APPKEYMNGR_TAB, m_tab);
	DDX_Control(pDX, IDC_APPKEYMNGR_LIST, m_listCtrlAppkey);
	//	DDX_Control(pDX, IDC_RIGHTCLICK_LIST, m_rightList);
	DDX_Text(pDX, IDC_KEYINDEXFORS_EDIT, m_key_index);
	DDX_Text(pDX, IDC_APPNAMEFORS_EDIT, m_key_appName);
}

BOOL CTimeMngr::OnInitDialog()
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
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	memset(nId_row_mux,0,256);
//----ListCtrl����------------------------------------------------------------------------------------------//

	CRect rect;   
  
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
    m_listCtrlAppkey.GetClientRect(&rect);   
  
	
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
    m_listCtrlAppkey.SetExtendedStyle(m_listCtrlAppkey.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_listCtrlAppkey.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,780,400);   
	m_listCtrlAppkey.SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
  
	//m_listCtrlAppkey.InsertColumn(0,NULL,LVCFMT_CENTER,30);        //����б���
 //   m_listCtrlAppkey.InsertColumn(1, _T("����"), LVCFMT_CENTER, 70, 1);   
 //   m_listCtrlAppkey.InsertColumn(2, _T("��Ȩ����"), LVCFMT_CENTER, 200, 2);   
 //   m_listCtrlAppkey.InsertColumn(3, _T("IP��ַ"), LVCFMT_CENTER, 240, 3);  
	//m_listCtrlAppkey.InsertColumn(7, _T("����޸�ʱ��"), LVCFMT_CENTER, 240, 4); 
	m_listCtrlAppkey.InsertColumn(0,NULL,LVCFMT_CENTER,25);        //����б���
	m_listCtrlAppkey.InsertColumn(1, _T("����"), LVCFMT_CENTER,(rect.Width()-50)/5-50, 1);   
	m_listCtrlAppkey.InsertColumn(2, _T("���ʱ��"), LVCFMT_CENTER,(rect.Width()-50)/5, 2); 
	m_listCtrlAppkey.InsertColumn(3, _T("���к�"), LVCFMT_CENTER,(rect.Width()-50)/5, 3); 
	m_listCtrlAppkey.InsertColumn(4, _T("�Ƿ񱸷�"), LVCFMT_CENTER,(rect.Width()-50)/5+50, 4);  
	m_listCtrlAppkey.InsertColumn(5, _T("�Ƿ���ȷ"), LVCFMT_CENTER, (rect.Width()-50)/5+50, 5);   
	m_listCtrlAppkey.InsertColumn(6, _T("��������"), LVCFMT_CENTER, (rect.Width()-50)/5+50, 6); 
//------------------------------------------------------------------------------------------------------------//
	//�б�ͷ���checkbox
	// Here's where we can add the checkbox to the column header
	// First, we need to snag the header control and give it the
	// HDS_CHECKBOXES style since the list view doesn't do this for us
	HWND header = ListView_GetHeader(m_listCtrlAppkey);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle |= HDS_CHECKBOXES;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	// Store the ID of the header control so we can handle its notification by ID
	int m_HeaderId = ::GetDlgCtrlID(header);

	// Now, we can update the format for the first header item,
	// which corresponds to the first column
	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header, 0, &hdi);
	hdi.fmt |= HDF_CHECKBOX | HDF_FIXEDWIDTH;
	Header_SetItem(header, 0, &hdi);
//-------------------------------------------------------------------------------------------------------------//
	CTimeMngr::ShowAppKeyInfo();

	isCheckbox = FALSE;
	memset(check,0,256);
	i_checked = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CTimeMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeMngr::OnBnClickedButton1)
	ON_NOTIFY(NM_RCLICK, IDC_APPKEYMNGR_LIST, &CTimeMngr::OnNMRClickAppkeymngrList)
	ON_COMMAND(ID__UPDATE, &CTimeMngr::OnUpdate)
	ON_COMMAND(ID__BACKUP, &CTimeMngr::OnBackup)
	ON_COMMAND(ID__RESUME, &CTimeMngr::OnResume)
	ON_COMMAND(ID__DISTROY, &CTimeMngr::OnDistroy)
	//ON_COMMAND(ID__CHANGEPIN, &CTimeMngr::OnChangepin)
	ON_COMMAND(ID__addAppKey, &CTimeMngr::OnAddappkey)
	ON_BN_CLICKED(IDC_SEARCHKEYLIST_BUTTON, &CTimeMngr::OnBnClickedSearchkeylistButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_APPKEYMNGR_LIST, &CTimeMngr::OnLvnItemchangedAppkeymngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CTimeMngr::OnItemstateiconclickAppkeymngrList)
END_MESSAGE_MAP()

// CTimeMngr ��Ϣ�������
BOOL CTimeMngr::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CTimeMngr::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*MessageBox(_T("��Կ������"));*/
}


void CTimeMngr::OnNMRClickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_RCLICK));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ�� 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}

//��Ӧ�˵���
void CTimeMngr::OnUpdate()
{
	// TODO: �ڴ���������������


	
}


void CTimeMngr::OnBackup()
{
	// TODO: �ڴ���������������
	
}


void CTimeMngr::OnResume()
{
	// TODO: �ڴ���������������


	//isCheckbox = FALSE;
}


void CTimeMngr::OnDistroy()
{
	// TODO: �ڴ���������������
	
}

void CTimeMngr::OnAddappkey()
{
	// TODO: �ڴ���������������


}

void CTimeMngr::setIndex(int index)
{
	index_max = index;
}

void CTimeMngr::OnBnClickedSearchkeylistButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	CString appName = m_key_appName;
	CString keyIndex = m_key_index;
	if(appName.IsEmpty() && keyIndex.IsEmpty())
	{
		CTimeMngr::ShowAppKeyInfo();
	}
	else
	{
		CTimeMngr::ShowAppKeyInfo_Search(appName,keyIndex);
	}
}

void CTimeMngr::ShowAppKeyInfo()
{
	m_listCtrlAppkey.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Km_AppKeyGetList(phHandle,0,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡӦ����Կ�б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_AppKeyGetList(phHandle,0,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡӦ����Կ�б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	if(0 == puiKeyListLen)
		return;
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	int appKey_index[256][2]={0};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
	//��ʼ��Ӧ����Կ�������飬Ĭ�ϵڶ��о�Ϊ1����ʾ��һ�е������Ŷ�����ʹ��
	for(int j = 0;j < 2;j++)
	{
		for(int i = 1;i < 257;i++)
		{
			if(0 == j)
				appKey_index[i-1][j] = i;
			else
				appKey_index[i-1][j] = 1;
		}
	}
	int time = 0;
	int nCount = 0;
	for(int i=0;i<256;i++)
	{
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;
//		MessageBox(str1);

		time++;
//		id.Format("%d",i);
//		int nCount = m_listCtrlAppkey.GetItemCount();
		m_listCtrlAppkey.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};
		char *str_appName = strstr(str2,"|");
		if(str_appName == NULL)
		{
			//MessageBox("str_appName==��");
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
		m_listCtrlAppkey.SetItemText(nCount, 2,appNameBuf);   
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(keyIndexBuf,str3,str_keyIndex-str3);
		m_listCtrlAppkey.SetItemText(nCount, 1,keyIndexBuf); 
		//keyIndex[i] = atoi(keyIndexBuf);//---------------------�ѽ���������Կ������������
		for(int z=0;z<256;z++)
		{
			if(appKey_index[z][0] == atoi(keyIndexBuf))
				appKey_index[z][1]=0; //-------------------------���Ѿ����õ���Կ�����ű��Ϊ0����ʾ������
		}

		char *str4 = str3 + strlen(keyIndexBuf) + 1;
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(algIdBuf,str4,str_algId-str4);
		CString alg;
		
		char *str5 = str4 + strlen(algIdBuf) + 1;

		char keyLengthBuf[32]={0x00};
		char *str_keyLength = strstr(str5,"|");
		memcpy(keyLengthBuf,str5,str_keyLength-str5);
		m_listCtrlAppkey.SetItemText(nCount, 4,keyLengthBuf);
		if(0 == strcmp(algIdBuf,"65536") && 1024 == atoi(keyLengthBuf))
			alg = "RSA 1024";
		if(0 == strcmp(algIdBuf,"65536") && 2048 == atoi(keyLengthBuf))
			alg = "RSA 2048";
		if(0 == strcmp(algIdBuf,"131328"))
			alg = "SM2";
		m_listCtrlAppkey.SetItemText(nCount, 3,alg);
		char *str6 = str5 + strlen(keyLengthBuf) + 1;

		char keyType[1]={0x00};
		//char *str_keyType = strstr(str6,"|");
		memcpy(keyType,str6,/*str_keyType-str6*/1);
		//char key_type = keyTypeBuf[0];
		//MessageBox(keyType);
		if(!strncmp("2",keyType,1))
			m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܹ�����Կ"));
		if(!strncmp("3",keyType,1))
			m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܲ�������Կ"));
		if(!strncmp("1",keyType,1))
			m_listCtrlAppkey.SetItemText(nCount, 5, _T("������Կ"));
		if(!strncmp("0",keyType,1))
			m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ����Կ"));

		char *str7 = str6 + 2;

		char ifBackBuf[1]={0x00};
		memcpy(ifBackBuf,str7,1);
		if(0 == atoi(ifBackBuf))
		{
			m_listCtrlAppkey.SetItemText(nCount, 6, _T("δ����"));
		}
		else if(1 == atoi(ifBackBuf))
		{
			m_listCtrlAppkey.SetItemText(nCount, 6, _T("�ѱ���"));
		}
		char *str8 = str7 + 2;

		char timeBuf[32]={0x00};
		char *str_time = strstr(str8,"|");
		//if(NULL == str_time || 1 == time )
		memcpy(timeBuf,str8,20);
		//else
		//	memcpy(timeBuf,str8,/*str_time-str8-2*/);
		m_listCtrlAppkey.SetItemText(nCount,7,timeBuf);
		char *str9 = str8 + strlen(timeBuf);

		nCount++;
		source = str9;
//		MessageBox(source);
	}
	delete puiKeyList;

	m_listCtrlAppkey.Scroll( CSize( 0, 100000 ) );
//	m_listCtrlAppkey.SetItemState(m_listCtrlAppkey.GetItemCount()�C1,LVIS_ACTIVATING | LVIS_FOCUSED | LVIS_SELECTED,LVIS_SELECTED | LVIS_FOCUSED );
	//��������漰��Ӵ�������� ��Կ��������ʾ
	memcpy(keyIndex,appKey_index,sizeof(appKey_index));//��ʱ����Կ��������appKey_index�Ѿ��ɼ���ÿһ�������ŵĿ���״̬,����������keyIndex������
	//����Կ���������� ���õĵ�һ������  ��ֵ��index_max--->�����������ɽ����Ĭ��ֵ
	for(int i=0;i<256;i++)
	{
		if(1 == appKey_index[i][1])
		{
			index_max = appKey_index[i][0];
			break;
		}
	}
	
}

void CTimeMngr::ShowAppKeyInfo_Search(CString appName,CString keyIndex_cs)
{
	m_listCtrlAppkey.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Km_AppKeyGetList(phHandle,0,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡӦ����Կ�б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_AppKeyGetList(phHandle,0,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡӦ����Կ�б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	if(0 == puiKeyListLen)
	{
		//MessageBox("","",MB_ICONEXCLAMATION);
		return;
	}
	KISH kish[256]={0};
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	
	CString id;
	int time = 0;
	int nCount = 0;
	for(int i=0;i,256;i++)
	{
//		if((int)source - (int)puiKeyList > puiKeyListLen)
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		//MessageBox("str1--------"+(CString)str1);
		if(str1 == NULL)
			break;

		time++;
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		//MessageBox("idBuf------------->"+(CString)idBuf);
		char *str2 = source + len + 1;
		//MessageBox("str2------------"+(CString)str2);

		char appNameBuf[128]={0x00};
		char *str_appName = strstr(str2,"|");
		//MessageBox("str_appName---------"+(CString)str_appName);
		if(str_appName == NULL)
		{
			//MessageBox("str_appName==��");
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
		//MessageBox("appNameBuf------------->"+(CString)appNameBuf);
		//m_listCtrlAppkey.SetItemText(nCount, 2,appNameBuf);

		memset(kish[i].appName,0x00,32);
		memcpy(kish[i].appName,appNameBuf,strlen(appNameBuf));//----------------------Ӧ������
		//MessageBox("kish[i].appName------------->"+(CString)kish[i].appName);
		char *str3 = str2 + strlen(appNameBuf) + 1;
		//MessageBox("str3----"+(CString)str3);

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		//MessageBox("str_keyIndex----"+(CString)str_keyIndex);
		memcpy(keyIndexBuf,str3,str_keyIndex-str3);
		//m_listCtrlAppkey.SetItemText(nCount, 1,keyIndexBuf); 
		kish[i].index = atoi(keyIndexBuf);//---------------------�ѽ���������Կ������������
		char *str4 = str3 + strlen(keyIndexBuf) + 1;
		//MessageBox("str4----"+(CString)str4);
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		//MessageBox("str_algId----"+(CString)str_algId);
		memcpy(algIdBuf,str4,str_algId-str4);
		//MessageBox("algIdBuf----"+(CString)algIdBuf);
		memcpy(kish[i].algId,algIdBuf,strlen(algIdBuf)); //----------------------------------�㷨
		

		//m_listCtrlAppkey.SetItemText(nCount, 3,alg);
		char *str5 = str4 + strlen(algIdBuf) + 1;

		char keyLengthBuf[32]={0x00};
		char *str_keyLength = strstr(str5,"|");
		memcpy(keyLengthBuf,str5,str_keyLength-str5);
		memcpy(kish[i].keyLength,keyLengthBuf,strlen(keyLengthBuf));//-------------------------��Կ����

		CString alg;
		if(0 == strcmp(algIdBuf,"65536") && 1024 == atoi(keyLengthBuf))
			alg = "RSA 1024";
		if(0 == strcmp(algIdBuf,"65536") && 2048 == atoi(keyLengthBuf))
			alg = "RSA 2048";
		if(0 == strcmp(algIdBuf,"131328"))
			alg = "SM2";
		//m_listCtrlAppkey.SetItemText(nCount, 4,keyLengthBuf);
		char *str6 = str5 + strlen(keyLengthBuf) + 1;

		char keyType[32]={0x00};
		char *str_keyType = strstr(str6,"|");
		memcpy(keyType,str6,str_keyType-str6);
		memcpy(kish[i].keyType,keyType,str_keyType-str6);//---------------------------��Կ����
		char *str7 = str6 + strlen(keyType) + 1;

		char ifBackBuf[32]={0x00};
		char *str_ifBack = strstr(str7,"|");
		memcpy(ifBackBuf,str7,str_ifBack-str7);
		memcpy(kish[i].ifBack,ifBackBuf,str_ifBack-str7);
		char *str8 = str7 + strlen(ifBackBuf) + 1;

		char timeBuf[32]={0x00};
		char *str_time = strstr(str8,"|");
		/*if(NULL == str_time || 1 == time )
		{*/
			memcpy(timeBuf,str8,20);
			memcpy(kish[i].modifyTime,timeBuf,20);
	/*	}
		else
		{
			memcpy(timeBuf,str8,str_time-str8-2);
			memcpy(kish[i].modifyTime,timeBuf,str_time-str8-2);
		}*/
		//m_listCtrlAppkey.SetItemText(nCount,7,timeBuf);
		char *str9 = str8 + strlen(timeBuf);
		
		nCount++;
		source = str9;
	}
	delete puiKeyList;

	//������Կ������ѯ
	CString k = 0;	
	nCount = 0;
	CString alg_cs;
	int kkkkkkey_index = _ttoi(keyIndex_cs);
	if(appName.IsEmpty() && !keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(kkkkkkey_index == kish[i].index)
			{
				//id.Format("%d",1);
				m_listCtrlAppkey.InsertItem(0,0); 
				k.Format("%d",kish[i].index);
				m_listCtrlAppkey.SetItemText(0, 1,k);
				//MessageBox(kish[i].appName);
				m_listCtrlAppkey.SetItemText(0, 2,kish[i].appName);
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(kish[i].algId,"131328"))
					alg_cs = "SM2";
				m_listCtrlAppkey.SetItemText(0, 3,alg_cs);

				m_listCtrlAppkey.SetItemText(0, 4,kish[i].keyLength);

				/*if(atoi(kish[i].keyType)== 2)
					m_listCtrlAppkey.SetItemText(0, 5, _T("ǩ�������ܹ�����Կ"));*/
				if(!strncmp("2",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܹ�����Կ"));
				if(!strncmp("3",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܲ�������Կ"));
				if(!strncmp("1",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("������Կ"));
				if(!strncmp("0",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ����Կ"));

				if(0 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(0, 6,_T("δ����"));
				else if(1 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(0, 6,_T("�ѱ���"));

				m_listCtrlAppkey.SetItemText(0,7,kish[i].modifyTime);
				break;
			}
		}
	}
	//����Ӧ�����Ʋ�ѯ
	int id_int = 0;
	if(keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			//if(!strcmp(kish[i].appName,appName))
			if(NULL != strstr(kish[i].appName,appName))
			{
				//id.Format("%d",id_int);
				m_listCtrlAppkey.InsertItem(nCount,0); 
				k.Format("%d",kish[i].index);
				m_listCtrlAppkey.SetItemText(nCount, 1,k);
				m_listCtrlAppkey.SetItemText(nCount, 2,kish[i].appName);
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(kish[i].algId,"131328"))
					alg_cs = "SM2";
				m_listCtrlAppkey.SetItemText(nCount, 3,alg_cs);
				m_listCtrlAppkey.SetItemText(nCount, 4,kish[i].keyLength);

				if(!strncmp("2",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܹ�����Կ"));
				if(!strncmp("3",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܲ�������Կ"));
				if(!strncmp("1",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("������Կ"));
				if(!strncmp("0",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ����Կ"));

				if(0 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(nCount, 6,_T("δ����"));
				else if(1 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(nCount, 6,_T("�ѱ���"));

				m_listCtrlAppkey.SetItemText(nCount,7,kish[i].modifyTime);

				id_int++;
				nCount++;
			}
		}
	}
	BOOL isSearched = FALSE;
	//����û�ͬʱ��������Կ������Ӧ�����ƣ�ȴ��ƥ��
	if(!keyIndex_cs.IsEmpty() && !appName.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(!strcmp(kish[i].appName,appName) && kkkkkkey_index == kish[i].index)
			{
				id.Format("%d",1);
				m_listCtrlAppkey.InsertItem(0,0); 
				k.Format("%d",kish[i].index);
				m_listCtrlAppkey.SetItemText(0, 1,k);
				m_listCtrlAppkey.SetItemText(0, 2,kish[i].appName);
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(kish[i].algId,"65536") && !strcmp(kish[i].keyLength,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(kish[i].algId,"131328"))
					alg_cs = "SM2";
				m_listCtrlAppkey.SetItemText(0, 3,alg_cs);

				m_listCtrlAppkey.SetItemText(0, 4,kish[i].keyLength);

				if(!strncmp("2",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܹ�����Կ"));
				if(!strncmp("3",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ�������ܲ�������Կ"));
				if(!strncmp("1",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("������Կ"));
				if(!strncmp("0",kish[i].keyType,1))
					m_listCtrlAppkey.SetItemText(nCount, 5, _T("ǩ����Կ"));

				if(0 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(0, 6,_T("δ����"));
				else if(1 == atoi(kish[i].ifBack))
					m_listCtrlAppkey.SetItemText(0, 6,_T("�ѱ���"));

				m_listCtrlAppkey.SetItemText(0,7,kish[i].modifyTime);

				isSearched = TRUE;
				break;
			}
		}
		if(!isSearched)
		{
			MessageBox("��ѯ������ƥ����������û�д�����Ϣ�������������ѯ����","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
	}
}

void CTimeMngr::OnLvnItemchangedAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox = TRUE;
		i_checked++;
		CString str1,str2,str3;
		nId_row = pNMLV->iItem;
		nId_row_mux[i_checked] = pNMLV->iItem;
		str2=m_listCtrlAppkey.GetItemText(pNMLV->iItem,1);//��ѡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked;i++)
		{
			if(check[i] == 0)
				check[i] = atoi(str2);
		}
		m_listCtrlAppkey.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//ѡ���������ʾ
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row = 0;
		
		str=m_listCtrlAppkey.GetItemText(pNMLV->iItem,1);//��ѡ��ȡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked;i++)
		{
			if(check[i] == atoi(str))
				check[i] = 0;
		}
		i_checked--;
		if(i_checked != 0)
			isCheckbox = TRUE;
		else if(i_checked == 0)
			isCheckbox = FALSE;
		m_listCtrlAppkey.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//ȡ��ѡ�У���ȡ��������ʾ
	} 
	//else 
	//{ 
	//  /*TRACE("Item %d does't change the check-status\n", pNMLV->iItem); */
	//	MessageBox("  ��������","û��ѡ��");
	//} 
}

void CTimeMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlAppkey); nItem++) 
	{
		ListView_SetCheckState(m_listCtrlAppkey, nItem, fChecked);
	}
}

void CTimeMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlAppkey); nItem++) 
	{
		if (!ListView_GetCheckState(m_listCtrlAppkey, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_listCtrlAppkey);
	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header, 0, &hdi);
	if (fChecked) 
	{
		hdi.fmt |= HDF_CHECKED;
	} else 
	{
		hdi.fmt &= ~HDF_CHECKED;
	}
	Header_SetItem(header, 0, &hdi);
}

void CTimeMngr::OnItemstateiconclickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	NMHEADER *pnmHeader = (NMHEADER *)pNMHDR;
	if (pnmHeader->pitem->mask & HDI_FORMAT && pnmHeader->pitem->fmt & HDF_CHECKBOX) 
	{
			CheckAllItems(!(pnmHeader->pitem->fmt & HDF_CHECKED));
			SetHeaderCheckbox();
	}
}
