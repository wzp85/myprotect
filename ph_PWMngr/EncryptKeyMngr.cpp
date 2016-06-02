// EncryptKeyMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "EncryptKeyMngr.h"
#include "afxdialogex.h"

#include "DevKeyFirBac.h"
#include "EncryptKeyGen.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "ChoseFilePath.h"
#define EK_UPDATA 888
#include "KeyDevide.h"
// CEncryptKeyMngr �Ի���

IMPLEMENT_DYNAMIC(CEncryptKeyMngr, CDialogEx)

CEncryptKeyMngr::CEncryptKeyMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncryptKeyMngr::IDD, pParent)
	, m_keyIndex_ek(_T(""))
	, m_kekName_ek(_T(""))
{
	index_max_ek = 0;
}

CEncryptKeyMngr::~CEncryptKeyMngr()
{
}

void CEncryptKeyMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_TAB1, m_tabEncrypt);
	DDX_Control(pDX, IDC_ENCRYPTKEYMNGR_LIST, m_listCtrlEncryptKey);
	DDX_Text(pDX, IDC_KEYINDEX_EDIT, m_keyIndex_ek);
	DDX_Text(pDX, IDC_KEYDES_EDIT, m_kekName_ek);
}

BOOL CEncryptKeyMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0x00F0) == IDM_ABOUTBOX);
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
	CRect rect;   
  
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
    m_listCtrlEncryptKey.GetClientRect(&rect);   
  
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
    m_listCtrlEncryptKey.SetExtendedStyle(m_listCtrlEncryptKey.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_listCtrlEncryptKey.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,780,400);   
	m_listCtrlEncryptKey.SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
  
	m_listCtrlEncryptKey.InsertColumn(0,NULL,LVCFMT_CENTER,30);        //����б���
    m_listCtrlEncryptKey.InsertColumn(1, _T("��Կ����"), LVCFMT_CENTER, 78, 1);   
    m_listCtrlEncryptKey.InsertColumn(2, _T("��Կ����"), LVCFMT_CENTER, 180, 2);   
    m_listCtrlEncryptKey.InsertColumn(3, _T("�㷨"), LVCFMT_CENTER, 150, 3); 
	m_listCtrlEncryptKey.InsertColumn(4, _T("�Ƿ��ѱ���"), LVCFMT_CENTER, 120, 4); 
	m_listCtrlEncryptKey.InsertColumn(5, _T("����/��������"), LVCFMT_CENTER, 200, 5);

	HWND header = ListView_GetHeader(m_listCtrlEncryptKey);
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

	//�����ʾ����
//	MessageBox("��1","");
	CEncryptKeyMngr::ShowEncryptKeyInfo();
//	MessageBox("��2","");

	isCheckbox_ek = FALSE;
	memset(check_ek,0,256);
	i_checked_ek = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CEncryptKeyMngr, CDialogEx)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CEncryptKeyMngr::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_ENCRYPTSEARCH_BUTTON, &CEncryptKeyMngr::OnBnClickedEncryptsearchButton)
	ON_NOTIFY(NM_RCLICK, IDC_ENCRYPTKEYMNGR_LIST, &CEncryptKeyMngr::OnRclickEncryptkeymngrList)
	ON_COMMAND(ID_S_ADDek, &CEncryptKeyMngr::OnSAddek)
	ON_COMMAND(ID__UPDATEek, &CEncryptKeyMngr::OnUpdateek)
	ON_COMMAND(ID__DISTROYek, &CEncryptKeyMngr::OnDistroyek)
	ON_COMMAND(ID__BACKUPek, &CEncryptKeyMngr::OnBackupek)
	ON_COMMAND(ID__RESUMEek, &CEncryptKeyMngr::OnResumeek)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ENCRYPTKEYMNGR_LIST, &CEncryptKeyMngr::OnLvnItemchangedEncryptkeymngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CEncryptKeyMngr::OnItemstateiconclickEncryptkeymngrList)
END_MESSAGE_MAP()


BOOL CEncryptKeyMngr::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CEncryptKeyMngr::OnBnClickedEncryptsearchButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	CString kekName = m_kekName_ek;
	CString keyIndex = m_keyIndex_ek;
	if(kekName.IsEmpty() && keyIndex.IsEmpty())
	{
		CEncryptKeyMngr::ShowEncryptKeyInfo();
	}
	else
	{
		CEncryptKeyMngr::ShowEncryptKeyInfo_Search(kekName,keyIndex);
	}
}


void CEncryptKeyMngr::OnRclickEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_RCLICK_ek));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ�� 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);

}


void CEncryptKeyMngr::OnSAddek()
{
	// TODO: �ڴ���������������
	CEncryptKeyGen encryptKeyGen(phHandle_ek);
	if(0 == index_max_ek)//���û���Ѿ�ռ�õ�������@
	{
		encryptKeyGen.keyIndex_max_ek = 1;
		int appKey_index[256][2]={0};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
		for(int j = 0;j < 2;j++)
		{
			for(int i = 1;i < 257;i++)
			{
				if(0 == j)
					appKey_index[i-1][j] = i;
				else
					appKey_index[i-1][j] = 1;//@���ʾÿһ�������Ŷ�����
			}
		}
		memcpy(keyIndex_ek,appKey_index,sizeof(appKey_index));
		memcpy(encryptKeyGen.index_array_ek,keyIndex_ek,sizeof(keyIndex_ek));//�Ѹ����鴫�ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	else//����Ѿ�����ռ�õ�
	{
		encryptKeyGen.keyIndex_max_ek = index_max_ek;//���˴�����BUG���ѿ��õĵ�һ����������������ʾĬ��ֵ�ı���
		memcpy(encryptKeyGen.index_array_ek,keyIndex_ek,sizeof(keyIndex_ek));//�ѿ��õ��������� ���ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	if(IDOK == encryptKeyGen.DoModal())
	{
		index_max_ek++;
		MessageBox("��ӳɹ�","");
		CEncryptKeyMngr::ShowEncryptKeyInfo();
	}
	//else
	//{
	//	memset(check_ek,0,256);
	//	i_checked_ek = 0;
	//	isCheckbox_ek = FALSE;
	//}
	
	
}


void CEncryptKeyMngr::OnUpdateek()
{
	// TODO: �ڴ���������������
	//MessageBox("�Ѹ���","");
	CString ek_Name;
	CString ek_keyIndex;
	CString ek_algId;
	int nId;
	//��ȡ��ǰѡ����
	/*POSITION pos=m_listCtrlEncryptKey.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		isCheckbox_ek = FALSE;
		nId=(int)m_listCtrlEncryptKey.GetNextSelectedItem(pos);
	}*/
	if(/*pos==NULL && */!isCheckbox_ek)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*pos == NULL && */isCheckbox_ek)
	{
		if(i_checked_ek > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row;
		}
	}
	//��ȡ��ǰѡ����ÿ����Ϣ
	ek_keyIndex = m_listCtrlEncryptKey.GetItemText(nId,1);
	ek_algId = m_listCtrlEncryptKey.GetItemText(nId,3);

	void * hSessionHandle = phHandle_ek;
	unsigned int uiKeyIndexNum = 1;//1����ѡ
	unsigned int puiKeyIndex = atoi(ek_keyIndex);
	INT_PTR nRes = 0x00;
	nRes = MessageBox("ȷ��Ҫ���¸���Կ��Ϣ��","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
	{
		/*memset(check_ek,0,256);
		i_checked_ek = 0;
		isCheckbox_ek = FALSE;*/
		return;
	}

	CEncryptKeyGen encryptKeyGen(hSessionHandle,ek_keyIndex,ek_algId);
	//appKeyGen.keyIndex_max = index_max;//BUG���ڣ�
	keyIndex_ek[0][0] = EK_UPDATA;
	encryptKeyGen.uig_ek.index = atoi(ek_keyIndex);
	encryptKeyGen.uig_ek.index_num = 1;
	memcpy(encryptKeyGen.index_array_ek,keyIndex_ek,sizeof(keyIndex_ek));
	if(IDOK == encryptKeyGen.DoModal())
	{
		MessageBox("�����ɹ�","��ʾ");
		CEncryptKeyMngr::ShowEncryptKeyInfo();

		memset(check_ek,0,256);
		i_checked_ek = 0;
		isCheckbox_ek = FALSE;
	}
	
}


void CEncryptKeyMngr::OnDistroyek()
{
	// TODO: �ڴ���������������
	INT_PTR nRes;
	int ret = 0;
	BOOL isSingle = FALSE;

	void * hSessionHandle = phHandle_ek;
	unsigned int uiKeyIndexNum;//1����ѡ
	unsigned int puiKeyIndex/* = atoi(keyIndex)*/;
	CString keyIndex_cs;
//	POSITION  pos;
	unsigned int key_index_int[256]={0};
//	int nId;
	//int count;
	//count = m_listCtrlEncryptKey.GetSelectedCount();
	//if(0 != count)//����Ҽ��͸�ѡ��ͬʱ�����������Ҽ�Ϊ׼
	//	isCheckbox_ek = FALSE;
	if(/*!count && */!isCheckbox_ek)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*!count && */isCheckbox_ek)
	{
		if(1 == i_checked_ek)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_ek[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_ek)
		{
			uiKeyIndexNum = i_checked_ek;
			memcpy(key_index_int,check_ek,i_checked_ek*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	//else if(1 == count)
	//{
	//	pos=m_listCtrlEncryptKey.GetFirstSelectedItemPosition();
	//	nId=(int)m_listCtrlEncryptKey.GetNextSelectedItem(pos);
	//	//��ȡ��ǰѡ����ÿ����Ϣ
	//	keyIndex_cs = m_listCtrlEncryptKey.GetItemText(nId,1);
	//	uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
	//	puiKeyIndex = atoi(keyIndex_cs);
	//	isSingle = TRUE;
	//}
	//else if(count > 1)
	//{
	//	uiKeyIndexNum = count;
	//	pos=m_listCtrlEncryptKey.GetFirstSelectedItemPosition();
	//	int i = 0;
	//	while(pos != NULL)
	//	{
	//		nId=(int)m_listCtrlEncryptKey.GetNextSelectedItem(pos);
	//		key_index_int[i] = atoi(m_listCtrlEncryptKey.GetItemText(nId,1));
	//		i++;
	//	}
	//	isSingle = FALSE;
	//}
	nRes = MessageBox("�ò��������棬���ٺ�����ݽ��޷��ָ�����ȷ���Ƿ������","��ʾ",MB_ICONWARNING | MB_OKCANCEL);;
	if(nRes != IDOK)
		return;
	if(isSingle)
		ret = Km_KeyEncDestroy(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	else if(!isSingle)	
		ret = Km_KeyEncDestroy(hSessionHandle,uiKeyIndexNum,key_index_int);
	if(ret)
	{
		char outKed[100]={0x00};
		retValueParse(ret,outKed);
		MessageBox("ɾ��ʧ��"+(CString)outKed,"");
	}
	else
	{
		MessageBox("�����ɹ���","��ʾ");
		memset(check_ek,0,256);
		i_checked_ek = 0;

		isCheckbox_ek = FALSE;
	}
	CEncryptKeyMngr::ShowEncryptKeyInfo();
	
}


void CEncryptKeyMngr::OnBackupek()
{
	// TODO: �ڴ���������������

	BOOL isSingle = FALSE;
	int nId = 0;
	nId = nId_row;
//	int count = 0;
//	POSITION  pos;
	CString keyIndex_i;
	CString encDes_i;
	unsigned int uiKeyIndexNum;//1����ѡ
	unsigned int puiKeyIndex;
	unsigned int key_index_int[256]={0};
	//count = m_listCtrlEncryptKey.GetSelectedCount();
	//if(0 != count)//����Ҽ��͸�ѡ��ͬʱ�����������Ҽ�Ϊ׼
	//	isCheckbox_ek = FALSE;
	if(/*!count && */!isCheckbox_ek)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*!count && */isCheckbox_ek)
	{
		if(1 == i_checked_ek)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_ek[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_ek)
		{
			uiKeyIndexNum = i_checked_ek;
			memcpy(key_index_int,check_ek,i_checked_ek*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}

	CDevKeyFirBac devKeyFirBacDlg1(1,_T("������һ����Կ������Կ"));
	if(IDOK != devKeyFirBacDlg1.DoModal())
		return;
	unsigned int B64KeyLen1=0;
	unsigned char B64Key1[256]={0x00};

	Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1_ek,0,256);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1_ek);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("�����ڶ�����Կ������Կ"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2_ek,0,256);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2_ek);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("������������Կ������Կ"));
	if(devKeyFirBacDlg3.DoModal() == IDOK)
	{
		unsigned char key_in[32]={0x00};
		devKeyFirBacDlg3.GetRandomInKey(key_in);//�õ�key�е������жϱ����ļ��뱸����Կ�Ƿ�ƥ��������

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle_ek,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3_ek,0,256);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3_ek);

		unsigned char sysKey_for_in[256]={0};
		unsigned int sysKey_for_in_len = 0;
		int ret = 0;
		ret = KeyMerge(sys_Key_1_ek,len_1,sys_Key_2_ek,len_2,sys_Key_3_ek,len_3,sysKey_for_in,&sysKey_for_in_len);
//		char *path="C:\\key_after_merge_ek.txt";
//		CMyUtil::Write2File(path,sysKey_for_in,sysKey_for_in_len);
		if(0 != ret || 16 != sysKey_for_in_len)
		{
			MessageBox("��Կ�ϲ�����","��ʾ");
			return;
		}
		if(isSingle)
		{
			CChoseFilePath choseFilePath(key_in,encDes_i,sysKey_for_in,uiKeyIndexNum,&puiKeyIndex,ENC_BACKUP,phHandle_ek);
			choseFilePath.DoModal();
		}
		else if(!isSingle)
		{
			CChoseFilePath choseFilePath(key_in,NULL,sysKey_for_in,uiKeyIndexNum,key_index_int,ENC_BACKUP,phHandle_ek);
			choseFilePath.DoModal();
		}
	}
	CEncryptKeyMngr::ShowEncryptKeyInfo();
	memset(check_ek,0,256);
	i_checked_ek = 0;
	/*if(isSingle)
		m_listCtrlEncryptKey.SetCheck(nId,FALSE);
	else if(!isSingle)
	{
		for(int i = 0;i < i_checked_ek;i++)
		{
			m_listCtrlEncryptKey.SetCheck(nId_row_mux_ek[i],FALSE);
		}
	}*/

	isCheckbox_ek = FALSE;
}


void CEncryptKeyMngr::OnResumeek()
{
	// TODO: �ڴ���������������
	CEncryptKeyResume encryptKeyResume(phHandle_ek); 
	if(IDOK == encryptKeyResume.DoModal())
		CEncryptKeyMngr::ShowEncryptKeyInfo();

	//isCheckbox_ek = FALSE;

}

void CEncryptKeyMngr::ShowEncryptKeyInfo()
{
	m_listCtrlEncryptKey.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	char outKekGl[100]={0x00};
	ret = Km_KeyEncKeyGetList(phHandle_ek,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		retValueParse(ret,outKekGl);
		MessageBox("��ȡ��Կ������Կ�б�ʧ��"+(CString)outKekGl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_KeyEncKeyGetList(phHandle_ek,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		retValueParse(ret,outKekGl);
		MessageBox("��ȡ��Կ������Կ�б�ʧ��"+(CString)outKekGl,"��ʾ",MB_ICONEXCLAMATION);
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
//	int keyTimeLength = 0;
	for(int i=0;i<256;i++)
	{
//		if((int)source - (int)puiKeyList > puiKeyListLen)
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;

		time++;
//		id.Format("%d",i);
		//int nCount = m_listCtrlAppkey.GetItemCount();
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char KEKNameBuf[64]={0x00};
		char *str_KEKName = strstr(str2,"|");
		if(str_KEKName == NULL)
		{
			//MessageBox("str_KEKName == ��","");
			break;
		}
		memcpy(KEKNameBuf,str2,str_KEKName-str2);
		m_listCtrlEncryptKey.InsertItem(nCount,0); 
		m_listCtrlEncryptKey.SetItemText(nCount, 2,KEKNameBuf);   
		char *str3 = str2 + strlen(KEKNameBuf) + 1;

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(keyIndexBuf,str3,str_keyIndex-str3);
		m_listCtrlEncryptKey.SetItemText(nCount, 1,keyIndexBuf); 
		//keyIndex[i] = atoi(keyIndexBuf);//---------------------�ѽ���������Կ������������
		for(int z=0;z<256;z++)
		{
			if(appKey_index[z][0] == atoi(keyIndexBuf))
				appKey_index[z][1]=0;
		}

		char *str4 = str3 + strlen(keyIndexBuf) + 1;
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(algIdBuf,str4,str_algId-str4);
		CString alg;
		if(0 == strcmp(algIdBuf,"513"))
			alg = "SSF33";
		if(0 == strcmp(algIdBuf,"1025"))
			alg = "SM4";
		if(0 == strcmp(algIdBuf,"257"))
			alg = "SM1";
		m_listCtrlEncryptKey.SetItemText(nCount,3,alg);
		char *str5 = str4 + strlen(algIdBuf) + 1;

		char ifBackBuf[1]={0x00};
		memcpy(ifBackBuf,str5,1);
		if(0 == atoi(ifBackBuf))
		{
			m_listCtrlEncryptKey.SetItemText(nCount, 4, _T("δ����"));
		}
		else if(1 == atoi(ifBackBuf))
		{
			m_listCtrlEncryptKey.SetItemText(nCount, 4, _T("�ѱ���"));
		}
		char *str6 = str5 + 2;

		char keyTimeBuf[32]={0x00};
		char *str_keyTime = strstr(str6,"|");
		//if(NULL == str_keyTime || 1 == time )
			memcpy(keyTimeBuf,str6,20);
		/*else
			memcpy(keyTimeBuf,str6,str_keyTime-str6-2);*/
		m_listCtrlEncryptKey.SetItemText(nCount,5,keyTimeBuf);
//		keyTimeLength = strlen(keyTimeBuf)-1;
		char *str7 = str6 + strlen(keyTimeBuf);
		
		nCount++;
		source = str7;
	}
	delete puiKeyList;

	m_listCtrlEncryptKey.Scroll( CSize( 0, 100000 ) );
	//��������漰��Ӵ�������� ��Կ��������ʾ
	memcpy(keyIndex_ek,appKey_index,sizeof(appKey_index));//��ʱ����Կ��������appKey_index�Ѿ��ɼ���ÿһ�������ŵĿ���״̬,����������keyIndex������
	//����Կ���������� ���õĵ�һ������  ��ֵ��index_max--->�����������ɽ����Ĭ��ֵ
	for(int i=0;i<256;i++)
	{
		if(1 == appKey_index[i][1])
		{
			index_max_ek = appKey_index[i][0];
			break;
		}
	}
}

void CEncryptKeyMngr::ShowEncryptKeyInfo_Search(CString appName,CString keyIndex_cs)
{
	m_listCtrlEncryptKey.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	char outKekGl[100]={0x00};
	ret = Km_KeyEncKeyGetList(phHandle_ek,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		retValueParse(ret,outKekGl);
		MessageBox("��ȡ��Կ������Կ�б�ʧ��"+(CString)outKekGl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_KeyEncKeyGetList(phHandle_ek,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		retValueParse(ret,outKekGl);
		MessageBox("��ȡ��Կ������Կ�б�ʧ��"+(CString)outKekGl,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	if(0 == puiKeyListLen)
	{
		//MessageBox("","",MB_ICONEXCLAMATION);
		return;
	}
	EKISH ekish[256]={0};
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	
	CString id;
	int time = 0;
	int nCount = 0;
	for(int i=0;i,256;i++)
	{
		if(*source == 0)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;

		time++;
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char KEKNameBuf[64]={0x00};
		char *str_KEKName = strstr(str2,"|");
		memcpy(KEKNameBuf,str2,str_KEKName-str2);
		//m_listCtrlAppkey.SetItemText(nCount, 2,appNameBuf);
		memcpy(ekish[i].kekName,KEKNameBuf,strlen(KEKNameBuf));//----------------------
		char *str3 = str2 + strlen(KEKNameBuf) + 1;

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(keyIndexBuf,str3,str_keyIndex-str3);
		//m_listCtrlAppkey.SetItemText(nCount, 1,keyIndexBuf); 
		ekish[i].index = atoi(keyIndexBuf);//---------------------�ѽ���������Կ������������
		char *str4 = str3 + strlen(keyIndexBuf) + 1;
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(algIdBuf,str4,str_algId-str4);
		memcpy(ekish[i].algId,algIdBuf,strlen(algIdBuf));
		CString alg;
		if(0 == strcmp(algIdBuf,"513"))
			alg = "SSF33";
		if(0 == strcmp(algIdBuf,"1025"))
			alg = "SM4";
		if(0 == strcmp(algIdBuf,"257"))
			alg = "SM1";
		//m_listCtrlAppkey.SetItemText(nCount, 3,alg);
		char *str5 = str4 + strlen(algIdBuf) + 1;

		char ifBackBuf[32]={0x00};
		memcpy(ifBackBuf,str5,1);
		memcpy(ekish[i].ifBack,ifBackBuf,1);
		char *str6 = str5 + 2;

		int keyTimeLength = 0;
		char keyTimeBuf[32]={0x00};
		char *str_keyTime = strstr(str6,"|");
		/*if(NULL == str_keyTime || 1 == time )
		{*/
			memcpy(keyTimeBuf,str6,20);
			memcpy(ekish[i].keyTime,keyTimeBuf,20);
		/*}*/
		/*else
		{
			memcpy(keyTimeBuf,str6,str_keyTime-str6-1);
			memcpy(ekish[i].keyTime,keyTimeBuf,str_keyTime-str6-1);
		}*/
		char *str7 = str6 + strlen(keyTimeBuf);

		nCount++;
		source = str7;
	}
	delete puiKeyList;
	//MessageBox("����������ϣ�","");
	//������Կ������ѯ
	CString k = 0;	
	nCount = 0;
	CString alg_cs;
	int kkkkkkey_index = _ttoi(keyIndex_cs);
	if(appName.IsEmpty() && !keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(kkkkkkey_index == ekish[i].index)
			{
				id.Format("%d",1);
				m_listCtrlEncryptKey.InsertItem(0,0); 
				k.Format("%d",ekish[i].index);
				m_listCtrlEncryptKey.SetItemText(0, 1,k);
				m_listCtrlEncryptKey.SetItemText(0, 2,ekish[i].kekName);
				if(!strcmp(ekish[i].algId,"513"))
					alg_cs = "SSF33";
				if(!strcmp(ekish[i].algId,"1025"))
					alg_cs = "SM4";
				if(!strcmp(ekish[i].algId,"257"))
					alg_cs = "SM1";
				m_listCtrlEncryptKey.SetItemText(0, 3,alg_cs);

				if(0 == atoi(ekish[i].ifBack))
					m_listCtrlEncryptKey.SetItemText(0, 4,_T("δ����"));
				else if(1 == atoi(ekish[i].ifBack))
					m_listCtrlEncryptKey.SetItemText(0, 4,_T("�ѱ���"));

				m_listCtrlEncryptKey.SetItemText(0, 5,ekish[i].keyTime);

				break;
			}
		}
	}
	//������Կ������ѯ
	int id_int = 0;
	if(keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr(ekish[i].kekName,appName))
			{
				id.Format("%d",id_int);
				m_listCtrlEncryptKey.InsertItem(nCount,0); 
				k.Format("%d",ekish[i].index);
				m_listCtrlEncryptKey.SetItemText(nCount, 1,k);
				m_listCtrlEncryptKey.SetItemText(nCount, 2,ekish[i].kekName);
				if(!strcmp(ekish[i].algId,"513"))
					alg_cs = "SSF33";
				if(!strcmp(ekish[i].algId,"1025"))
					alg_cs = "SM4";
				if(!strcmp(ekish[i].algId,"257"))
					alg_cs = "SM1";
				m_listCtrlEncryptKey.SetItemText(nCount, 3,alg_cs);

				if(0 == atoi(ekish[i].ifBack))
					m_listCtrlEncryptKey.SetItemText(nCount, 4,_T("δ����"));
				else if(1 == atoi(ekish[i].ifBack))
					m_listCtrlEncryptKey.SetItemText(nCount, 4,_T("�ѱ���"));

				m_listCtrlEncryptKey.SetItemText(nCount, 5,ekish[i].keyTime);

				id_int++;
				nCount++;
			}
		}
	}
	BOOL isSearched = FALSE;
	//����û�ͬʱ��������Կ��������Կ������ȴ��ƥ��
	if(!keyIndex_cs.IsEmpty() && !appName.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(!strcmp(ekish[i].kekName,appName) && kkkkkkey_index == ekish[i].index)
			{
				id.Format("%d",1);
					m_listCtrlEncryptKey.InsertItem(0,0); 
					k.Format("%d",ekish[i].index);
					m_listCtrlEncryptKey.SetItemText(0, 1,k);
					m_listCtrlEncryptKey.SetItemText(0, 2,ekish[i].kekName);
					if(!strcmp(ekish[i].algId,"513"))
						alg_cs = "SSF33";
					if(!strcmp(ekish[i].algId,"1025"))
						alg_cs = "SM4";
					if(!strcmp(ekish[i].algId,"257"))
						alg_cs = "SM1";
					m_listCtrlEncryptKey.SetItemText(0, 3,alg_cs);

					if(0 == atoi(ekish[i].ifBack))
						m_listCtrlEncryptKey.SetItemText(0, 4,_T("δ����"));
					else if(1 == atoi(ekish[i].ifBack))
						m_listCtrlEncryptKey.SetItemText(0, 4,_T("�ѱ���"));

					m_listCtrlEncryptKey.SetItemText(0, 5,ekish[i].keyTime);

					isSearched = TRUE;
					break;
			}
		}
		if(!isSearched)
		{
			MessageBox("��ѯ������ƥ����������û�д�����Ϣ�������������ѯ����","��ʾ",MB_ICONEXCLAMATION);
		}
	}
}

void CEncryptKeyMngr::OnLvnItemchangedEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_ek = TRUE;
		i_checked_ek++;
		CString str2;
		nId_row = pNMLV->iItem;
		nId_row_mux_ek[i_checked_ek] = pNMLV->iItem;
		str2=m_listCtrlEncryptKey.GetItemText(pNMLV->iItem,1);//��ѡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_ek;i++)
		{
			if(check_ek[i] == 0)
				check_ek[i] = atoi(str2);
		}
		m_listCtrlEncryptKey.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//ѡ���������ʾ
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		//BOOL isCanBeFalse = TRUE;
		//int j = 0;
		//for(int i = 0;i < i_checked_ek;i++)
		//{
		//	if(check_ek[i] != 0)
		//	{
		//		isCanBeFalse = FALSE;
		//		//break;
		//		j++;
		//	}
		//}
		//if(isCanBeFalse && 1 == j)
		//	isCheckbox_ek = FALSE;
		//else
		//	isCheckbox_ek = TRUE;
		//isCheckbox_ek = FALSE;
		CString str;
		nId_row = 0;
		str=m_listCtrlEncryptKey.GetItemText(pNMLV->iItem,1);//��ѡ��ȡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_ek;i++)
		{
			if(check_ek[i] == atoi(str))
				check_ek[i] = 0;
		}
		i_checked_ek--;
		if(i_checked_ek != 0)
			isCheckbox_ek = TRUE;
		else if(i_checked_ek == 0)
			isCheckbox_ek = FALSE;
		m_listCtrlEncryptKey.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//ȡ��ѡ�У���ȡ��������ʾ
		
	} 
}

void CEncryptKeyMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlEncryptKey); nItem++) 
	{
		ListView_SetCheckState(m_listCtrlEncryptKey, nItem, fChecked);
	}
}

void CEncryptKeyMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlEncryptKey); nItem++) 
	{
		if (!ListView_GetCheckState(m_listCtrlEncryptKey, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_listCtrlEncryptKey);
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

void CEncryptKeyMngr::OnItemstateiconclickEncryptkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
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
