// ROOTCertMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ROOTCertMngr.h"
#include "afxdialogex.h"

#include "RTCertAdd.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "ChoseFilePath.h"
#include "ForRecoveryFilePath.h"
// CROOTCertMngr �Ի���

IMPLEMENT_DYNAMIC(CROOTCertMngr, CDialogEx)

CROOTCertMngr::CROOTCertMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CROOTCertMngr::IDD, pParent)
	, m_rtCertIndex_cs(_T(""))
	, m_rtCertName_cs(_T(""))
	, m_rtCertAlgid_cs(_T(""))
	, m_rtCertAtName_cs(_T(""))
{
	certIndex_rtCert_max = 0;
}

CROOTCertMngr::~CROOTCertMngr()
{
}

void CROOTCertMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROOTCERTMNGR_LIST, m_ROOTCert);
	DDX_Text(pDX, IDC_ROOT_CERTINDEXFORS_EDIT, m_rtCertIndex_cs);
	DDX_Text(pDX, IDC_ROOT_CERTNAMEFORS_EDIT, m_rtCertName_cs);
	DDX_Text(pDX, IDC_ROOT_alg_EDIT, m_rtCertAlgid_cs);
	DDX_Text(pDX, IDC_ROOT_atName_EDIT, m_rtCertAtName_cs);
}


BEGIN_MESSAGE_MAP(CROOTCertMngr, CDialogEx)
	ON_BN_CLICKED(IDC_ROOTCERT_SEARCHCERTLIST_BUTTON, &CROOTCertMngr::OnBnClickedRootcertSearchcertlistButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ROOTCERTMNGR_LIST, &CROOTCertMngr::OnLvnItemchangedRootcertmngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CROOTCertMngr::OnHdnItemStateIconClickRootcertmngrList)
	ON_NOTIFY(NM_RCLICK, IDC_ROOTCERTMNGR_LIST, &CROOTCertMngr::OnNMRClickRootcertmngrList)
	ON_COMMAND(ID__ROOTCERT_add, &CROOTCertMngr::OnRootcertAdd)
	ON_COMMAND(ID__ROOTCERT_update, &CROOTCertMngr::OnRootcertUpdate)
	ON_COMMAND(ID__ROOTCERT_del, &CROOTCertMngr::OnRootcertDel)
	ON_COMMAND(ID__ROOTCERT_export, &CROOTCertMngr::OnRootcertExport)
	ON_COMMAND(ID__RTCert_backup, &CROOTCertMngr::OnRtcertBackup)
	ON_COMMAND(ID__RTCert_recovery, &CROOTCertMngr::OnRtcertRecovery)
END_MESSAGE_MAP()


// CROOTCertMngr ��Ϣ�������


BOOL CROOTCertMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//MessageBox("2222222222222222222222��","��ʾ",MB_ICONEXCLAMATION);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;    
    m_ROOTCert.GetClientRect(&rect);   
    m_ROOTCert.SetExtendedStyle(m_ROOTCert.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_ROOTCert.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,780,400);   
	m_ROOTCert.SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);

	m_ROOTCert.InsertColumn(0,NULL,LVCFMT_CENTER,30);        //����б���
    m_ROOTCert.InsertColumn(1, _T("֤��������"), LVCFMT_CENTER, 95, 1);   
    m_ROOTCert.InsertColumn(2, _T("֤������"), LVCFMT_CENTER, 125, 2);   
    m_ROOTCert.InsertColumn(3, _T("�㷨����"), LVCFMT_CENTER, 105, 3); 
	m_ROOTCert.InsertColumn(4, _T("��������"), LVCFMT_CENTER, 145, 4);
	m_ROOTCert.InsertColumn(5, _T("��ϵ��"), LVCFMT_CENTER, 105, 5); 
	m_ROOTCert.InsertColumn(6, _T("��ϵ�˵绰"), LVCFMT_CENTER, 165, 6); 
	m_ROOTCert.InsertColumn(7, _T("֤�����к�"), LVCFMT_CENTER, 90, 7); 

	HWND header = ListView_GetHeader(m_ROOTCert);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle |= HDS_CHECKBOXES;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	int m_HeaderId = ::GetDlgCtrlID(header);

	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header, 0, &hdi);
	hdi.fmt |= HDF_CHECKBOX | HDF_FIXEDWIDTH;
	Header_SetItem(header, 0, &hdi);
	//MessageBox("ShowRootCertInfo��","��ʾ",MB_ICONEXCLAMATION);
	CROOTCertMngr::ShowRootCertInfo();
	//MessageBox("ShowRootCertInfo end��","��ʾ",MB_ICONEXCLAMATION);
	isCheckbox_rc = FALSE;
	memset(check_rc,0,256);
	i_checked_rc = 0;
	//MessageBox("end��","��ʾ",MB_ICONEXCLAMATION);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CROOTCertMngr::OnBnClickedRootcertSearchcertlistButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("��֤���ѯ","");
	UpdateData(TRUE);
	//CString index;
	//CString name;
	//CString algid;
	//CString atName;
	//if(!m_rtCertIndex_cs.IsEmpty())
	//	index=m_rtCertIndex_cs;
	//if(!m_rtCertName_cs.IsEmpty())
	//	name=m_rtCertName_cs;
	//if(!m_rtCertAlgid_cs.IsEmpty())
	//	algid=m_rtCertAlgid_cs;
	//if(!m_rtCertAtName_cs.IsEmpty())
	//	atName=m_rtCertAtName_cs;
	if(m_rtCertIndex_cs.IsEmpty()&&m_rtCertName_cs.IsEmpty()&&m_rtCertAlgid_cs.IsEmpty()&&m_rtCertAtName_cs.IsEmpty())
		CROOTCertMngr::ShowRootCertInfo();
	else
		CROOTCertMngr::ShowRootCertInfo_Search(m_rtCertIndex_cs,m_rtCertName_cs,m_rtCertAlgid_cs,m_rtCertAtName_cs);
}

void CROOTCertMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_ROOTCert); nItem++) 
	{
		ListView_SetCheckState(m_ROOTCert, nItem, fChecked);
	}
}

void CROOTCertMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_ROOTCert); nItem++) 
	{
		if (!ListView_GetCheckState(m_ROOTCert, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_ROOTCert);
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


BOOL CROOTCertMngr::PreTranslateMessage(MSG* pMsg)
{
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
		return TRUE; 
		if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
		return TRUE; 
		return CDialog::PreTranslateMessage(pMsg);
}






void CROOTCertMngr::OnLvnItemchangedRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_rc = TRUE;
		i_checked_rc++;
		CString str1,str2,str3;
		nId_row_rc = pNMLV->iItem;
		nId_row_mux_rc[i_checked_rc] = pNMLV->iItem;
		str2=m_ROOTCert.GetItemText(pNMLV->iItem,1);//��ѡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_rc;i++)
		{
			if(check_rc[i] == 0)
				check_rc[i] = atoi(str2);
		}
		m_ROOTCert.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//ѡ���������ʾ
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_rc = 0;
		
		str=m_ROOTCert.GetItemText(pNMLV->iItem,1);//��ѡ��ȡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_rc;i++)
		{
			if(check_rc[i] == atoi(str))
				check_rc[i] = 0;
		}
		i_checked_rc--;
		if(i_checked_rc != 0)
			isCheckbox_rc = TRUE;
		else if(i_checked_rc == 0)
			isCheckbox_rc = FALSE;
		m_ROOTCert.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//ȡ��ѡ�У���ȡ��������ʾ
	} 
}


void CROOTCertMngr::OnHdnItemStateIconClickRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
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


void CROOTCertMngr::OnNMRClickRootcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_ROOTCert));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ�� 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}


void CROOTCertMngr::OnRootcertAdd()
{
	// TODO: �ڴ���������������
	CRTCertAdd rtCertAddDlg(phHandle,1);
	//-----------------------
	if(0 ==  certIndex_rtCert_max)//���û���Ѿ�ռ�õ�������@
	{
		rtCertAddDlg.rtAddIndex = 1;
		int rtCert_index[256][2]={0};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
		for(int j = 0;j < 2;j++)
		{
			for(int i = 1;i < 257;i++)
			{
				if(0 == j)
					 rtCert_index[i-1][j] = i;
				else
					 rtCert_index[i-1][j] = 1;//@���ʾÿһ�������Ŷ�����
			}
		}
		memcpy(certIndex_rtCert, rtCert_index,sizeof( rtCert_index));
		memcpy(rtCertAddDlg.rtAddIndex_array,certIndex_rtCert,sizeof(certIndex_rtCert));//�Ѹ����鴫�ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	else//����Ѿ�����ռ�õ�
	{
		rtCertAddDlg.rtAddIndex = certIndex_rtCert_max;//���˴�����BUG���ѿ��õĵ�һ����������������ʾĬ��ֵ�ı���
		memcpy(rtCertAddDlg.rtAddIndex_array,certIndex_rtCert,sizeof(certIndex_rtCert));//�ѿ��õ��������� ���ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	if(IDOK == rtCertAddDlg.DoModal())
	{
		certIndex_rtCert_max++;
		CROOTCertMngr::ShowRootCertInfo();
	}
	//--------------------------

	
}


void CROOTCertMngr::OnRootcertUpdate()
{
	// TODO: �ڴ���������������
	int nId;
	CString index;
	CString name;
	CString algId;
	CString atName;
	CString hostName;
	CString hostPhone;
	CString keyIndex;

	if(!isCheckbox_rc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_rc)
	{
		if(i_checked_rc > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_rc;
		}
	}

	name = m_ROOTCert.GetItemText(nId,2);
	index = m_ROOTCert.GetItemText(nId,1);
	algId = m_ROOTCert.GetItemText(nId,3);
	atName = m_ROOTCert.GetItemText(nId,4);
	hostName = m_ROOTCert.GetItemText(nId,5);
	hostPhone = m_ROOTCert.GetItemText(nId,6);
	keyIndex = m_ROOTCert.GetItemText(nId,7);
	CRTCertAdd rtCertAddDlg(phHandle,0,name,algId,index,atName,hostName,hostPhone,keyIndex); 
	if(IDOK == rtCertAddDlg.DoModal())
	{
		CROOTCertMngr::ShowRootCertInfo();
		memset(check_rc,0,256);
		i_checked_rc = 0;
		isCheckbox_rc = FALSE;
	}
}


void CROOTCertMngr::OnRootcertDel()
{
	// TODO: �ڴ���������������
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;

	void * hSessionHandle = phHandle;
	unsigned int uiKeyIndexNum;//1����ѡ
	unsigned int puiKeyIndex/* = atoi(keyIndex)*/;
	CString keyIndex_cs;

	unsigned int key_index_int[256]={0};

	if(!isCheckbox_rc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_rc)
	{
		if(1 == i_checked_rc)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_rc[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_rc)
		{
			uiKeyIndexNum = i_checked_rc;
			memcpy(key_index_int,check_rc,i_checked_rc*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	nRes = MessageBox("�ò��������棬���ٺ�����ݽ��޷��ָ�����ȷ���Ƿ������","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
		return;
	if(isSingle)
		ret = Sig_RootCertDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	else if(!isSingle)
		ret = Sig_RootCertDel(hSessionHandle,uiKeyIndexNum,key_index_int);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("ɾ��ʧ��"+(CString)outAkd,"��ʾ");
	}
	else
	{
		CROOTCertMngr::ShowRootCertInfo();
		MessageBox("�����ɹ���","��ʾ");
		memset(check_rc,0,256);
		i_checked_rc = 0;

		isCheckbox_rc = FALSE;
	}
}


void CROOTCertMngr::OnRootcertExport()
{
	// TODO: �ڴ���������������
	int ret=0;
	CString keyIndex;
	void * hSessionHandle=phHandle;
	unsigned int index=0;
	unsigned char *pucCert=NULL;
	unsigned int uiCertLength=0;
	int nId;

	if(!isCheckbox_rc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_rc)
	{
		if(i_checked_rc > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_rc;
		}
	}
	//��ȡ��ǰѡ����ÿ����Ϣ
	keyIndex = m_ROOTCert.GetItemText(nId,1);
	index = atoi((LPSTR)(LPCTSTR)keyIndex);

	ret = Sig_RTCertExport(hSessionHandle,index,&uiCertLength,pucCert);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("����֤��ʧ��"+(CString)outAkd,"��ʾ");
		return;
	}
	pucCert=new unsigned char[uiCertLength+1];
	memset(pucCert,0x00,uiCertLength+1);
	ret = Sig_RTCertExport(hSessionHandle,index,&uiCertLength,pucCert);
	if(0 != ret)
	{
		char outAkEPd[100]={0x00};
		retValueParse(ret,outAkEPd);
		MessageBox("����֤��ʧ��"+(CString)outAkEPd,"��ʾ");
		delete []pucCert;
		return;
	}
	CMyUtil::Write2File("C:\\RTCertExport.cer",pucCert,uiCertLength);
	MessageBox("�����ɹ���֤���ļ�������C:\\RTCertExport.cer","��ʾ",MB_ICONEXCLAMATION);
}

void CROOTCertMngr::ShowRootCertInfo()
{
	m_ROOTCert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Sig_RootCertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡ��֤���б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_RootCertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡ��֤���б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGRtCertGetList.txt",puiKeyList,puiKeyListLen);
//	return;

	if(0 == puiKeyListLen)
		return;
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;
	int rtcert_index[256][2]={0x00};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
	//��ʼ��Ӧ����Կ�������飬Ĭ�ϵڶ��о�Ϊ1����ʾ��һ�е������Ŷ�����ʹ��
	for(int j = 0;j < 2;j++)
	{
		for(int i = 1;i < 257;i++)
		{
			if(0 == j)
				rtcert_index[i-1][j] = i;
			else
				rtcert_index[i-1][j] = 1;
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

		time++;
		m_ROOTCert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------֤������
		char *str_appName = strstr(str2,"|");
		if(str_appName == NULL)
		{
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
		m_ROOTCert.SetItemText(nCount, 2,appNameBuf);   
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		//CString alg;
		//if(!strncmp("131328",algIdBuf,6))
		//	alg = "SM2";
		//if(!strncmp("65536",algIdBuf,5))
		//	alg = "RSA";
		//m_ROOTCert.SetItemText(nCount,3,alg); 
		char *str4 = str3 + strlen(algIdBuf)+1;

		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
		//����ط�Ӧ����εõ�֤���������أ��������ڷ���˵�xml�ļ��У�
		m_ROOTCert.SetItemText(nCount, 7,keyIndexBuf); 
		
		char *str5 = str4 + strlen(keyIndexBuf)+1;

		char keyLength[32]={0x00};
		char *str_keyLength=strstr(str5,"|");
		memcpy(keyLength,str5,str_keyLength-str5);
		CString alg;
		if(!strncmp("131328",algIdBuf,6))
			alg = "SM2 256";
		if(!strncmp("65536",algIdBuf,5) && !strncmp("1024",keyLength,4))
			alg = "RSA 1024";
		if(!strncmp("65536",algIdBuf,5) && !strncmp("2048",keyLength,4))
			alg = "RSA 2048";
		m_ROOTCert.SetItemText(nCount,3,alg); 

		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		m_ROOTCert.SetItemText(nCount,4,atName); 
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
		m_ROOTCert.SetItemText(nCount,5,hostName); 
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
		m_ROOTCert.SetItemText(nCount,6,hostPhone); 
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
		m_ROOTCert.SetItemText(nCount, 1,serialNum); 
		for(int z=0;z<256;z++)
		{
			if(rtcert_index[z][0] == atoi(serialNum))
				rtcert_index[z][1]=0; //-------------------------���Ѿ����õ���Կ�����ű��Ϊ0����ʾ������
		}
		char *str10 = str9 + strlen(serialNum);

		char timeBuf[32]={0x00};
		memcpy(timeBuf,str10,20);
		char *str11 = str10 + strlen(timeBuf);

		nCount++;
		source = str11;
	}
	delete puiKeyList;

	m_ROOTCert.Scroll( CSize( 0, 100000 ) );
//	m_ROOTCert.SetItemState(m_ROOTCert.GetItemCount()�C1,LVIS_ACTIVATING | LVIS_FOCUSED | LVIS_SELECTED,LVIS_SELECTED | LVIS_FOCUSED );
	memcpy(certIndex_rtCert,rtcert_index,sizeof(rtcert_index));//��ʱ����Կ��������appKey_index�Ѿ��ɼ���ÿһ�������ŵĿ���״̬
	//����Կ���������� ���õĵ�һ������  ��ֵ��index_max--->�����������ɽ����Ĭ��ֵ
	for(int i=0;i<256;i++)
	{
		if(1 == rtcert_index[i][1])
		{
			certIndex_rtCert_max = rtcert_index[i][0];
			break;
		}
	}
}

void CROOTCertMngr::ShowRootCertInfo_Search(CString index,CString name,CString algid,CString atName)
{
	m_ROOTCert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Sig_RootCertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡ��֤���б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_RootCertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡ��֤���б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	RCISH rcish[256]={0x00};

	if(0 == puiKeyListLen)
		return;
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	int time = 0;
	int nCount = 0;
	for(int i=0;i<256;i++)
	{
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;

//		time++;
//		m_ROOTCert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[32]={0x00};//---------------------֤������
		char *str_appName = strstr(str2,"|");
		if(str_appName == NULL)
		{
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
//		m_ROOTCert.SetItemText(nCount, 2,appNameBuf);   
		memcpy(rcish[i].name,str2,str_appName-str2);
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		//CString alg;
		//if(!strncmp("131328",algIdBuf,6))
		//	alg = "SM2";
		//if(!strncmp("65536",algIdBuf,5))
		//	alg = "RSA";
		//m_ROOTCert.SetItemText(nCount,3,alg); 
		
		char *str4 = str3 + strlen(algIdBuf)+1;

		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
		//����ط�Ӧ����εõ�֤���������أ��������ڷ���˵�xml�ļ��У�
		//m_ROOTCert.SetItemText(nCount, 1,keyIndexBuf); 
		char *str5 = str4 + strlen(keyIndexBuf)+1;

		char keyLength[32]={0x00};
		char *str_keyLength=strstr(str5,"|");
		memcpy(keyLength,str5,str_keyLength-str5);
		CString alg;
		if(!strncmp("131328",algIdBuf,6))
			alg = "SM2 256";
		if(!strncmp("65536",algIdBuf,5) && !strncmp("1024",keyLength,4))
			alg = "RSA 1024";
		if(!strncmp("65536",algIdBuf,5) && !strncmp("2048",keyLength,4))
			alg = "RSA 2048";
//		m_ROOTCert.SetItemText(nCount,3,alg); 
		memcpy(rcish[i].algid,alg.GetBuffer(),alg.GetLength());

		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
//		m_ROOTCert.SetItemText(nCount,4,atName); 
		memcpy(rcish[i].atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
//		m_ROOTCert.SetItemText(nCount,5,hostName); 
		memcpy(rcish[i].hostName,str7,str_hostName-str7);
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
//		m_ROOTCert.SetItemText(nCount,6,hostPhone); 
		memcpy(rcish[i].hostPhone,str8,str_hostPhone-str8);
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
//		m_ROOTCert.SetItemText(nCount, 1,serialNum); 
		memcpy(rcish[i].index,str9,str_serialNum-str9);
		char *str10 = str9 + strlen(serialNum);

		char timeBuf[32]={0x00};
		memcpy(timeBuf,str10,20);
		char *str11 = str10 + strlen(timeBuf);

		nCount++;
		source = str11;
	}
	delete puiKeyList;

	BOOL isSearched = FALSE;
	nCount = 0;
	//����֤��������ѯ
	if(!m_rtCertIndex_cs.IsEmpty() && m_rtCertName_cs.IsEmpty() && m_rtCertAlgid_cs.IsEmpty() && m_rtCertAtName_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(!strcmp(m_rtCertIndex_cs.GetBuffer(),(char *)rcish[i].index))
			{
				m_ROOTCert.InsertItem(0,0);
				m_ROOTCert.SetItemText(0,1,(char *)rcish[i].index);
				m_ROOTCert.SetItemText(0,2,(char *)rcish[i].name);
				m_ROOTCert.SetItemText(0,3,(char *)rcish[i].algid);
				/*CString alg;
				if(!strncmp("131328",(char *)rcish[i].algid,6))
					alg = "SM2";
				if(!strncmp("65536",(char *)rcish[i].algid,5))
					alg = "RSA";*/
				//m_ROOTCert.SetItemText(0,3,alg);
				m_ROOTCert.SetItemText(0,4,(char *)rcish[i].atName);
				m_ROOTCert.SetItemText(0,5,(char *)rcish[i].hostName);
				m_ROOTCert.SetItemText(0,6,(char *)rcish[i].hostPhone);
				isSearched=TRUE;
				break;
			}
		}
	}
	//����֤�����Ʋ�ѯ 
	else if(m_rtCertIndex_cs.IsEmpty() && !m_rtCertName_cs.IsEmpty() && m_rtCertAlgid_cs.IsEmpty() && m_rtCertAtName_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr((char *)rcish[i].name,m_rtCertName_cs.GetBuffer()))
			{
				m_ROOTCert.InsertItem(nCount,0);
				m_ROOTCert.SetItemText(nCount,1,(char *)rcish[i].index);
				m_ROOTCert.SetItemText(nCount,2,(char *)rcish[i].name);
				m_ROOTCert.SetItemText(nCount,3,(char *)rcish[i].algid);
				m_ROOTCert.SetItemText(nCount,4,(char *)rcish[i].atName);
				m_ROOTCert.SetItemText(nCount,5,(char *)rcish[i].hostName);
				m_ROOTCert.SetItemText(nCount,6,(char *)rcish[i].hostPhone);
				isSearched=TRUE;
			//	break;
				nCount++;
			}
		}
	}

	//�����㷨��ѯ
	else if(m_rtCertIndex_cs.IsEmpty() && m_rtCertName_cs.IsEmpty() && !m_rtCertAlgid_cs.IsEmpty() && m_rtCertAtName_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL!=strstr((char *)rcish[i].algid,m_rtCertAlgid_cs.GetBuffer()))
			{
				m_ROOTCert.InsertItem(nCount,0);
				m_ROOTCert.SetItemText(nCount,1,(char *)rcish[i].index);
				m_ROOTCert.SetItemText(nCount,2,(char *)rcish[i].name);
				m_ROOTCert.SetItemText(nCount,3,(char *)rcish[i].algid);
				m_ROOTCert.SetItemText(nCount,4,(char *)rcish[i].atName);
				m_ROOTCert.SetItemText(nCount,5,(char *)rcish[i].hostName);
				m_ROOTCert.SetItemText(nCount,6,(char *)rcish[i].hostPhone);
				isSearched=TRUE;
			//	break;
				nCount++;
			}
		}
	}

	//���ջ������Ʋ�ѯ
	else if(m_rtCertIndex_cs.IsEmpty() && m_rtCertName_cs.IsEmpty() && m_rtCertAlgid_cs.IsEmpty() && !m_rtCertAtName_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr((char *)rcish[i].atName,m_rtCertAtName_cs.GetBuffer()))
			{
				m_ROOTCert.InsertItem(nCount,0);
				m_ROOTCert.SetItemText(nCount,1,(char *)rcish[i].index);
				m_ROOTCert.SetItemText(nCount,2,(char *)rcish[i].name);
				m_ROOTCert.SetItemText(nCount,3,(char *)rcish[i].algid);
				m_ROOTCert.SetItemText(nCount,4,(char *)rcish[i].atName);
				m_ROOTCert.SetItemText(nCount,5,(char *)rcish[i].hostName);
				m_ROOTCert.SetItemText(nCount,6,(char *)rcish[i].hostPhone);
				isSearched=TRUE;
			//	break;
				nCount++;
			}
		}
	}
	else//-------------�����ѯ--------------------------------
	{
		MessageBox("�ù��ܽ�֧�ֵ����ѯ","��ʾ");
		return;
	}


	m_ROOTCert.Scroll( CSize( 0, 100000 ) );


}


void CROOTCertMngr::OnRtcertBackup()
{
	// TODO: �ڴ���������������
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;
	int nId = nId_row_rc;

	void * hSessionHandle = phHandle;
	unsigned int uiKeyIndexNum;//1����ѡ
	unsigned int puiKeyIndex/* = atoi(keyIndex)*/;
	CString appName_i;

	unsigned int key_index_int[256]={0};

	if(!isCheckbox_rc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_rc)
	{
		if(1 == i_checked_rc)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_rc[0];
			isSingle = TRUE;
			appName_i=m_ROOTCert.GetItemText(nId,2);
		}
		else if(1 < i_checked_rc)
		{
			uiKeyIndexNum = i_checked_rc;
			memcpy(key_index_int,check_rc,i_checked_rc*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	if(isSingle)
	{
		CChoseFilePath choseFilePath(NULL,appName_i,NULL,uiKeyIndexNum,&puiKeyIndex,SIG_RTCERTBAK,phHandle);
		choseFilePath.DoModal();
	}
	else if(!isSingle)
	{
		CChoseFilePath choseFilePath(NULL,NULL,NULL,uiKeyIndexNum,key_index_int,SIG_RTCERTBAK,phHandle);
		choseFilePath.DoModal();
	}
	CROOTCertMngr::ShowRootCertInfo();
	//MessageBox("�����ɹ���","��ʾ");
	memset(check_rc,0,256);
	i_checked_rc = 0;

	isCheckbox_rc = FALSE;
	//MessageBox("���ݳɹ��������ļ�������C:\\rtcertback.backup","",MB_ICONEXCLAMATION);
}


void CROOTCertMngr::OnRtcertRecovery()
{
	// TODO: �ڴ���������������
	int ret = 0;
	int len = 0;
	char *path = NULL;
	CForRecoveryFilePath forRecoveryFilePath;
	if(IDOK != forRecoveryFilePath.DoModal())
		return ;
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);
	path = new char [len + 1];
	memset(path,0x00,len+1);
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);
	MessageBox(path);


	unsigned char *pucRtCert = NULL;
	unsigned int uiRtCertLength = 0;
	
	CMyUtil::ReadData(path,pucRtCert,&len);
	pucRtCert = new unsigned char [len];
	CMyUtil::ReadData(path,pucRtCert,&len);
	uiRtCertLength = len;
	
	void *hSessionHandle = phHandle;
	/*****************����***********************/
	if(0 == uiRtCertLength)
		return ;
	unsigned char pucCertName[50] = {0x00};//֤����
	unsigned int uiCertNameLength = 0;
	char *source = (char *)pucRtCert;
	char *str = strstr(source,"||");
	uiCertNameLength = strlen(source) - strlen(str);
	memcpy(pucCertName,source,uiCertNameLength);

	

	char algIdBuf[32] = {0x00};
	unsigned int uiAlgo = 0;
	char *str1 = str + 2;
	char *str2 = strstr(str1,"||");
	memcpy(algIdBuf,str1,strlen(str1)-strlen(str2));
	
	unsigned char pucCertIndex[50] = {0x00};
	unsigned int uiCertIndexLength = 0;
	char *str3 = str2 + 2;
	char *str4 = strstr(str3,"||");
	uiCertIndexLength = strlen(str3)-strlen(str4);
	memcpy(pucCertIndex,str3,uiCertIndexLength);
	
	unsigned int uiKeyLength = 0;
	char Keylen[32] = {0x00};
	char *str5 = str4 + 2;
	char *str6 = strstr(str5,"||");
	memcpy(Keylen,str5,strlen(str5)-strlen(str6));
	if(!strncmp("131328",algIdBuf,6))//�㷨����
	{

		uiAlgo = atoi(algIdBuf);
		uiKeyLength = 256;
	}
	if(!strncmp("65536",algIdBuf,5) && !strncmp("1024",Keylen,4))
	{
		uiAlgo = atoi(algIdBuf);
		uiKeyLength = 1024;
	
	}
	if(!strncmp("65536",algIdBuf,5) && !strncmp("2048",Keylen,4))
	{
		uiAlgo = atoi(algIdBuf);
		uiKeyLength = 2048;
	}
	
	unsigned char pucAtName[50]  = {0x00};//������
	unsigned int uiAtNameLength = 0;
	char *str7 = str6 + 2;
	char *str8 = strstr(str7,"||");
	uiAtNameLength = strlen(str7) - strlen(str8);
	memcpy(pucAtName,str7,uiAtNameLength);

	unsigned char pucHost[50] = {0x00};//��ϵ��
	unsigned int uiHostLength = 0;
	char *str9 = str8 + 2;
	char *str10 = strstr(str9,"||");
	uiHostLength = strlen(str9) - strlen(str10);
	memcpy(pucHost,str9,uiHostLength);
	
	unsigned char pucPhone[50] = {0x00};//��ϵ����
	unsigned int uiPhoneLength = 0;
	char *str11 = str10 + 2;
	char *str12 = strstr(str11,"||");
	uiPhoneLength = strlen(str11) - strlen(str12);
	memcpy(pucPhone,str11,uiPhoneLength);
	
	char pucIndex[10] = {0x00};
	unsigned int uiIndexLength = 0;
	char * str13 = str12 + 2;
	char * str14 = strstr(str13,"||");

	uiIndexLength =  strlen(str13) - strlen(str14);
	if(uiIndexLength!=NULL)
      memcpy(pucIndex,str13,uiIndexLength);
	
	unsigned char pucTime[50] = {0x00};
	char *str15 = str14 + 2;
	char *str16 = strstr(str15,"||");

	
	unsigned char pucRTCert[2048] = {0x00};
	unsigned int uiRTCertLength = 0;
	int RT_len = 0;
	char *str17 = str16 + 2;
	char *str18 = strstr(str17,"||");
	RT_len= strlen(str17)-strlen(str18);
	memcpy(pucRTCert,str17, RT_len);
	uiRTCertLength = RT_len;
	
	char to_cmp[2] = {0x30,0x82};//..................��֤�����
	unsigned char in_data[2048] = {0x00};
	unsigned int in_data_len = 0;
	if(strncmp(to_cmp,(char*)pucRTCert,2) && !strncmp("M",(char*)pucRTCert,1))
	{
		//B64����
		char dst[4096] = {0x00};
		int length = 0;
		length = Km_Decode((char*)pucRTCert, RT_len,dst);
		memcpy(in_data,dst,length);
		in_data_len = length;
	}
	else if(!strncmp(to_cmp,(char*)pucRTCert,2) && strncmp("M",(char*)pucRTCert,1))
	{
		//ֱ�Ӵ�
		memcpy(in_data,pucRTCert, RT_len);
		in_data_len =  RT_len;
	}
	else if(strstr((char*)pucRTCert,"BEGIN CERTIFICATE"))
	{
		PKI_DATA in_cert,out_cert;
		in_cert.size =  RT_len;
		out_cert.size = 0;
		out_cert.value = new unsigned char [2048];
		in_cert.value = new unsigned char [ RT_len + 1];
		memset(in_cert.value,0x00, RT_len + 1);
		memcpy(in_cert.value,pucRtCert, RT_len);
		pkiBase64Decode(in_cert,&out_cert);
		memcpy(in_data,out_cert.value,out_cert.size);
		in_data_len = out_cert.size;
	}
	else
	{
		MessageBox("��ȷ���ָ����Ǹ�֤���ļ�","���ݸ�ʽ����",MB_ICONWARNING);
		return ;
	}
	

/***************֤�����֤****************/
	BYTE *data_read = NULL;
	int data_read_len = 0;
	CMyUtil::ReadData(path,data_read,&data_read_len);
	data_read = new BYTE [data_read_len + 1];
	memset(data_read,0x00,data_read_len + 1);
	CMyUtil::ReadData(path,data_read,&data_read_len);

	//MessageBox((CString)data_read);
	char ch_last = data_read[data_read_len - 1];
	if(0x36 != ch_last)//֤�����һλΪ6
	{
		MessageBox("ѡ��Ĳ��Ǹ�֤�鱸���ļ�����ѡ���֤�鱸���ļ����лָ�");
		delete data_read;
	}

	/**********************��������ӽӿ�**********************/

	ret = Sig_RootCertAdd(hSessionHandle,pucCertName,uiCertNameLength,atoi(pucIndex),uiAlgo,pucAtName,uiKeyLength,uiAtNameLength,
							pucHost,uiHostLength,pucPhone,uiPhoneLength,in_data,in_data_len,pucCertIndex,uiCertIndexLength);
	if(0 == ret)
	{
		MessageBox("�����ɹ�","��ʾ");
		delete []pucRtCert;
		//this->OnOK();
		//return;
	}
	else if(0 != ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("����ʧ��"+(CString)outGapk,"��ʾ",MB_ICONEXCLAMATION);
		delete []pucRtCert;
		//this->OnCancel();
		return;
	}
	CROOTCertMngr::ShowRootCertInfo();
	memset(check_rc,0,256);
	i_checked_rc = 0;

	isCheckbox_rc = FALSE;
	delete data_read;
	
}
