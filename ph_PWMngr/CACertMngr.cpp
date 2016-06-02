// CACertMngr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "CACertMngr.h"
#include "afxdialogex.h"

#include "CACertAdd.h"
#include "ph_km.h"
#include "MyUtil.h"
#include "ChoseFilePath.h"
#include "ForRecoveryFilePath.h"
// CCACertMngr �Ի���

IMPLEMENT_DYNAMIC(CCACertMngr, CDialogEx)

CCACertMngr::CCACertMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCACertMngr::IDD, pParent)
	, m_CA_CertIndex_fors(_T(""))
	, m_CA_CertName_fors(_T(""))
	, m_CA_Alg_fors(_T(""))
	, m_CA_atName_fors(_T(""))
{
	certIndex_caCert_max = 0;
}

CCACertMngr::~CCACertMngr()
{
}

void CCACertMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CACERTMNGR_LIST, m_CACert);
	DDX_Text(pDX, IDC_CA_CERTINDEXFORS_EDIT, m_CA_CertIndex_fors);
	DDX_Text(pDX, IDC_CACERTNAMEFORS_EDIT, m_CA_CertName_fors);
	DDX_Text(pDX, IDC_CA_alg_EDIT, m_CA_Alg_fors);
	DDX_Text(pDX, IDC_CA_atName_EDIT, m_CA_atName_fors);
}


BEGIN_MESSAGE_MAP(CCACertMngr, CDialogEx)
	ON_BN_CLICKED(IDC_CACERT_SEARCHCERTLIST_BUTTON, &CCACertMngr::OnBnClickedCacertSearchcertlistButton)
	ON_NOTIFY(NM_RCLICK, IDC_CACERTMNGR_LIST, &CCACertMngr::OnNMRClickCacertmngrList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CACERTMNGR_LIST, &CCACertMngr::OnLvnItemchangedCacertmngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CCACertMngr::OnHdnItemStateIconClickCacertmngrList)
	ON_COMMAND(ID__CACERT_add, &CCACertMngr::OnCacertAdd)
	ON_COMMAND(ID__CACERT_update, &CCACertMngr::OnCacertUpdate)
	ON_COMMAND(ID__CACERT_del, &CCACertMngr::OnCacertDel)
	ON_COMMAND(ID__CACERT_export, &CCACertMngr::OnCacertExport)
	ON_COMMAND(ID__CACert_backup, &CCACertMngr::OnCacertBackup)
	ON_COMMAND(ID__CACert_recovery, &CCACertMngr::OnCacertRecovery)
END_MESSAGE_MAP()


// CCACertMngr ��Ϣ�������


BOOL CCACertMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;    
    m_CACert.GetClientRect(&rect);   
    m_CACert.SetExtendedStyle(m_CACert.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_CACert.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,780,400);   
	m_CACert.SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);

	m_CACert.InsertColumn(0,NULL,LVCFMT_CENTER,30);        //����б���
    m_CACert.InsertColumn(1, _T("֤��������"), LVCFMT_CENTER, 95, 1);   
    m_CACert.InsertColumn(2, _T("֤������"), LVCFMT_CENTER, 125, 2);   
    m_CACert.InsertColumn(3, _T("�㷨����"), LVCFMT_CENTER, 105, 3); 
	m_CACert.InsertColumn(4, _T("��������"), LVCFMT_CENTER, 145, 4);
	m_CACert.InsertColumn(5, _T("��ϵ��"), LVCFMT_CENTER, 105, 5); 
	m_CACert.InsertColumn(6, _T("��ϵ��ʽ"), LVCFMT_CENTER, 165, 6); 
//	m_CACert.InsertColumn(7, _T("����"), LVCFMT_CENTER, 90, 7); 

	HWND header = ListView_GetHeader(m_CACert);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle |= HDS_CHECKBOXES;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	int m_HeaderId = ::GetDlgCtrlID(header);

	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header, 0, &hdi);
	hdi.fmt |= HDF_CHECKBOX | HDF_FIXEDWIDTH;
	Header_SetItem(header, 0, &hdi);


	CCACertMngr::ShowCACertInfo();

	isCheckbox_cc = FALSE;
	memset(check_cc,0,256);
	i_checked_cc = 0;


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCACertMngr::OnBnClickedCacertSearchcertlistButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("CA֤���ѯ","");
	UpdateData(TRUE);

	if(m_CA_CertIndex_fors.IsEmpty()&&m_CA_CertName_fors.IsEmpty()&&m_CA_Alg_fors.IsEmpty()&&m_CA_atName_fors.IsEmpty())
		CCACertMngr::ShowCACertInfo();
	else
		CCACertMngr::ShowCACertInfo_Search(m_CA_CertIndex_fors,m_CA_CertName_fors,m_CA_Alg_fors,m_CA_atName_fors);
}

void CCACertMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_CACert); nItem++) 
	{
		ListView_SetCheckState(m_CACert, nItem, fChecked);
	}
}

void CCACertMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_CACert); nItem++) 
	{
		if (!ListView_GetCheckState(m_CACert, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_CACert);
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


void CCACertMngr::OnNMRClickCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_CACert));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ�� 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}


void CCACertMngr::OnLvnItemchangedCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_cc = TRUE;
		i_checked_cc++;
		CString str1,str2,str3;
		nId_row_cc = pNMLV->iItem;
		nId_row_mux_cc[i_checked_cc] = pNMLV->iItem;
		str2=m_CACert.GetItemText(pNMLV->iItem,1);//��ѡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_cc;i++)
		{
			if(check_cc[i] == 0)
				check_cc[i] = atoi(str2);
		}
		m_CACert.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//ѡ���������ʾ	
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_cc = 0;
		
		str=m_CACert.GetItemText(pNMLV->iItem,1);//��ѡ��ȡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_cc;i++)
		{
			if(check_cc[i] == atoi(str))
				check_cc[i] = 0;
		}
		i_checked_cc--;
		if(i_checked_cc != 0)
			isCheckbox_cc = TRUE;
		else if(i_checked_cc == 0)
			isCheckbox_cc = FALSE;
		m_CACert.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//ȡ��ѡ�У���ȡ��������ʾ
	} 
}


void CCACertMngr::OnHdnItemStateIconClickCacertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
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


void CCACertMngr::OnCacertAdd()
{
	// TODO: �ڴ���������������
	CCACertAdd CACertAddDlg(phHandle,1);

	//-----------------------
	if(0 ==  certIndex_caCert_max)//���û���Ѿ�ռ�õ�������@
	{
		CACertAddDlg.caAddIndex = 1;
		int caCert_index[256][2]={0};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
		for(int j = 0;j < 2;j++)
		{
			for(int i = 1;i < 257;i++)
			{
				if(0 == j)
					 caCert_index[i-1][j] = i;
				else
					 caCert_index[i-1][j] = 1;//@���ʾÿһ�������Ŷ�����
			}
		}
		memcpy(certIndex_caCert, caCert_index,sizeof( caCert_index));
		memcpy(CACertAddDlg.caAddIndex_array,certIndex_caCert,sizeof(certIndex_caCert));//�Ѹ����鴫�ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	else//����Ѿ�����ռ�õ�
	{
		CACertAddDlg.caAddIndex = certIndex_caCert_max;//���˴�����BUG���ѿ��õĵ�һ����������������ʾĬ��ֵ�ı���
		memcpy(CACertAddDlg.caAddIndex_array,certIndex_caCert,sizeof(certIndex_caCert));//�ѿ��õ��������� ���ݸ����ɽ���������ṩ��ѡ��Կ����������
	}
	if(IDOK == CACertAddDlg.DoModal())
	{
		certIndex_caCert_max++;
		CCACertMngr::ShowCACertInfo();
	}

}


void CCACertMngr::OnCacertUpdate()
{
	// TODO: �ڴ���������������
	int nId,ret;
	CString index;
	CString name;
	CString algId;
	CString atName;
	CString hostName;
	CString hostPhone;

	unsigned int uiRtCertIndex = 0;
	unsigned int uiRtCertType = 0;
	VerifyPriorityStrategy vs;
	unsigned char pucCACertSerialNum[32]={0x00};

	//---------------------------��֤���Խṹ���Ա�ĳ�ʼ��
	vs.CRLhand = NULL;//---����1
	vs.autoCRLip = NULL;//---����2
	vs.autoCRLport = NULL;
	vs.autoCRLurl = NULL;
	/*vs.autoCRLname = NULL;
	vs.autoCRLpwd = NULL;*/
	vs.autoCRLtime = 0;
	vs.autoFromHTTPurl = NULL;//--from http
	vs.autoFromHTTPtime = 0;
	vs.autoCRLtype = 0;
	vs.CRLverifyTime = 0;//--����3
	vs.OCSPip = NULL;//----����4
	vs.OCSPport = NULL;
	vs.OCSPurl = NULL;
	vs.OCSPcertstand = 0;
	vs.OCSPtalktype = 0;
	vs.OCSPverify = NULL;//-----����5

	vs.CRLhandLen = 100;
	vs.CRLhand = (unsigned char*)calloc(vs.CRLhandLen,sizeof(unsigned char));
	vs.autoCRLipLen = 100;
	vs.autoCRLip = (unsigned char*)calloc(vs.autoCRLipLen,sizeof(unsigned char));
	vs.autoCRLportLen = 100;
	vs.autoCRLport = (unsigned char*)calloc(vs.autoCRLportLen,sizeof(unsigned char));
	/*vs.autoCRLnameLen = 10;
	vs.autoCRLname = (unsigned char *)calloc(vs.autoCRLnameLen,sizeof(unsigned char));
	vs.autoCRLpwdLen = 10;
	vs.autoCRLpwd = (unsigned char *)calloc(vs.autoCRLpwdLen,sizeof(unsigned char));*/
	vs.autoCRLurlLen = 100;
	vs.autoCRLurl = (unsigned char*)calloc(vs.autoCRLurlLen,sizeof(unsigned char));
	vs.autoFromHTTPurlLen = 100;
	vs.autoFromHTTPurl = (unsigned char*)calloc(vs.autoFromHTTPurlLen,sizeof(unsigned char));
	vs.OCSPipLen = 100;
	vs.OCSPip = (unsigned char*)calloc(vs.OCSPipLen,sizeof(unsigned char));
	vs.OCSPprotLen = 100;
	vs.OCSPport = (unsigned char*)calloc(vs.OCSPprotLen,sizeof(unsigned char));
	vs.OCSPurlLen = 100;
	vs.OCSPurl =(unsigned char*)calloc(vs.OCSPurlLen,sizeof(unsigned char));
	vs.OCSPverifyLen = 100;
	vs.OCSPverify = (unsigned char*)calloc(vs.OCSPverifyLen,sizeof(unsigned char));

	if(!isCheckbox_cc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_cc)
	{
		if(i_checked_cc > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_cc;
		}
	}
	name = m_CACert.GetItemText(nId,2);
	index = m_CACert.GetItemText(nId,1);
	algId = m_CACert.GetItemText(nId,3);
	atName = m_CACert.GetItemText(nId,4);
	hostName = m_CACert.GetItemText(nId,5);
	hostPhone = m_CACert.GetItemText(nId,6);

	//�˴���ȡ��֤���Խӿ�
	ret = Sig_GetCACertVS(phHandle,atoi((LPSTR)(LPCTSTR)index),pucCACertSerialNum,&uiRtCertType,&uiRtCertIndex,&vs);
	if(0 != ret)
	{
		char outGCAC[100]={0x00};
		retValueParse(ret,outGCAC);
		MessageBox("��ȡ��֤����ʧ��"+(CString)outGCAC,"��ʾ");
	}

	CCACertAdd CACertAddDlg(phHandle,0,uiRtCertType,uiRtCertIndex,CString(pucCACertSerialNum),vs,index,name,algId,atName,hostName,hostPhone);
	if(IDOK == CACertAddDlg.DoModal())
	{
		CCACertMngr::ShowCACertInfo();
//		MessageBox("�����ɹ���","��ʾ");
		memset(check_cc,0,256);
		i_checked_cc = 0;

		isCheckbox_cc = FALSE;
	}

	free(vs.CRLhand);
	free(vs.autoCRLip);
	free(vs.autoCRLport);
	free(vs.autoCRLurl);
	free(vs.autoFromHTTPurl);
	/*free(vs.autoCRLname);
	free(vs.autoCRLpwd);*/
	free(vs.OCSPip);
	free(vs.OCSPport);
	free(vs.OCSPurl);
	free(vs.OCSPverify);
}


void CCACertMngr::OnCacertDel()
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

	if(!isCheckbox_cc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_cc)
	{
		if(1 == i_checked_cc)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_cc[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_cc)
		{
			uiKeyIndexNum = i_checked_cc;
			memcpy(key_index_int,check_cc,i_checked_cc*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	nRes = MessageBox("�ò��������棬���ٺ�����ݽ��޷��ָ�����ȷ���Ƿ������","��ʾ",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
		return;
	if(isSingle)
		ret = Sig_CACertDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	else if(!isSingle)
		ret = Sig_CACertDel(hSessionHandle,uiKeyIndexNum,key_index_int);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("ɾ��ʧ��"+(CString)outAkd,"��ʾ");
	}
	else
	{
		CCACertMngr::ShowCACertInfo();
		MessageBox("�����ɹ���","��ʾ");
		memset(check_cc,0,256);
		i_checked_cc = 0;

		isCheckbox_cc = FALSE;
	}
}


void CCACertMngr::OnCacertExport()
{
	// TODO: �ڴ���������������
	int ret=0;
	CString keyIndex;
	void * hSessionHandle=phHandle;
	unsigned int index=0;
	unsigned char *pucCert=NULL;
	unsigned int uiCertLength=0;
	int nId;

	if(!isCheckbox_cc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_cc)
	{
		if(i_checked_cc > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_cc;
		}
	}
	//��ȡ��ǰѡ����ÿ����Ϣ
	keyIndex = m_CACert.GetItemText(nId,1);
	index = atoi((LPSTR)(LPCTSTR)keyIndex);

	ret = Sig_CACertExport(hSessionHandle,index,&uiCertLength,pucCert);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("����֤��ʧ��"+(CString)outAkd,"��ʾ");
		return;
	}
	pucCert=new unsigned char[uiCertLength+1];
	memset(pucCert,0x00,uiCertLength+1);
	ret = Sig_CACertExport(hSessionHandle,index,&uiCertLength,pucCert);
	if(0 != ret)
	{
		char outAkEPd[100]={0x00};
		retValueParse(ret,outAkEPd);
		MessageBox("����֤��ʧ��"+(CString)outAkEPd,"��ʾ");
		delete []pucCert;
		return;
	}
	CMyUtil::Write2File("C:\\CACertExport.cer",pucCert,uiCertLength);
	MessageBox("�����ɹ���֤���ļ�������C:\\CACertExport.cer","��ʾ",MB_ICONEXCLAMATION);
}


void CCACertMngr::ShowCACertInfo()
{
	m_CACert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Sig_CACertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡCA֤���б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_CACertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡCA֤���б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGCACertGetList.txt",puiKeyList,puiKeyListLen);
	//return;

	if(0 == puiKeyListLen)
		return;
	//�˴������ʾ����,�Ѷ��������ַ�����������ʾ��listctrl��
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	int cacert_index[256][2]={0x00};//������ڶ�����Ϊ1�����ʾ��һ�е������ſ���ʹ��
	//��ʼ��Ӧ����Կ�������飬Ĭ�ϵڶ��о�Ϊ1����ʾ��һ�е������Ŷ�����ʹ��
	for(int j = 0;j < 2;j++)
	{
		for(int i = 1;i < 257;i++)
		{
			if(0 == j)
				cacert_index[i-1][j] = i;
			else
				cacert_index[i-1][j] = 1;
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

		m_CACert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------֤������
		char *str_appName = strstr(str2,"|");
		memcpy(appNameBuf,str2,str_appName-str2);
		m_CACert.SetItemText(nCount, 2,appNameBuf);   
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		char *str4 = str3 + strlen(algIdBuf)+1;

		//֤�����к�
		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
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
		m_CACert.SetItemText(nCount,3,alg); 

		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		m_CACert.SetItemText(nCount,4,atName); 
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
		m_CACert.SetItemText(nCount,5,hostName); 
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
		m_CACert.SetItemText(nCount,6,hostPhone); 
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
		m_CACert.SetItemText(nCount, 1,serialNum); 
		for(int z=0;z<256;z++)
		{
			if(cacert_index[z][0] == atoi(serialNum))
				cacert_index[z][1]=0; //-------------------------���Ѿ����õ���Կ�����ű��Ϊ0����ʾ������
		}
		char *str10 = str9 + strlen(serialNum);

		char timeBuf[32]={0x00};
		memcpy(timeBuf,str10,20);
		char *str11 = str10 + strlen(timeBuf);

		nCount++;
		source = str11;
	}
	delete puiKeyList;

	m_CACert.Scroll( CSize( 0, 100000 ) );

	//	m_ROOTCert.SetItemState(m_ROOTCert.GetItemCount()�C1,LVIS_ACTIVATING | LVIS_FOCUSED | LVIS_SELECTED,LVIS_SELECTED | LVIS_FOCUSED );
	memcpy(certIndex_caCert,cacert_index,sizeof(cacert_index));//��ʱ����Կ��������appKey_index�Ѿ��ɼ���ÿһ�������ŵĿ���״̬
	//����Կ���������� ���õĵ�һ������  ��ֵ��index_max--->�����������ɽ����Ĭ��ֵ
	for(int i=0;i<256;i++)
	{
		if(1 == cacert_index[i][1])
		{
			certIndex_caCert_max = cacert_index[i][0];
			break;
		}
	}


}


void CCACertMngr::OnCacertBackup()
{
	// TODO: �ڴ���������������
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;
	int nId = nId_row_cc;

	void * hSessionHandle = phHandle;
	unsigned int uiKeyIndexNum;//1����ѡ
	unsigned int puiKeyIndex/* = atoi(keyIndex)*/;
	CString appName_i;

	unsigned int key_index_int[256]={0};

	if(!isCheckbox_cc)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_cc)
	{
		if(1 == i_checked_cc)
		{
			uiKeyIndexNum = 1;//1���ͱ�ʾ��ѡ
			puiKeyIndex = check_cc[0];
			isSingle = TRUE;
			appName_i=m_CACert.GetItemText(nId,2);
		}
		else if(1 < i_checked_cc)
		{
			uiKeyIndexNum = i_checked_cc;
			memcpy(key_index_int,check_cc,i_checked_cc*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	if(isSingle)
	{
		CChoseFilePath choseFilePath(NULL,appName_i,NULL,uiKeyIndexNum,&puiKeyIndex,SIG_CACERTBAK,phHandle);
		choseFilePath.DoModal();
	}
	else if(!isSingle)
	{
		CChoseFilePath choseFilePath(NULL,NULL,NULL,uiKeyIndexNum,key_index_int,SIG_CACERTBAK,phHandle);
		choseFilePath.DoModal();
	}
	CCACertMngr::ShowCACertInfo();
//	MessageBox("�����ɹ���","��ʾ");
	memset(check_cc,0,256);
	i_checked_cc = 0;

	isCheckbox_cc = FALSE;
	//MessageBox("���ݳɹ��������ļ�������C:\\cacertback.backup","",MB_ICONEXCLAMATION);
}


void CCACertMngr::OnCacertRecovery()
{
	// TODO: �ڴ���������������
	int ret=0;

	int len=0;
	char *path=NULL;
	CForRecoveryFilePath forRecoveryFilePath;
	if(IDOK != forRecoveryFilePath.DoModal())
		return;
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);
	path=new char[len+1];
	memset(path,0x00,len+1);
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);

	MessageBox(path);
	BYTE *data_read = NULL;
	int data_read_len = 0;
	CMyUtil::ReadData(path,data_read,&data_read_len);
	data_read = new BYTE[data_read_len+1];
	memset(data_read,0x00,data_read_len+1);
	CMyUtil::ReadData(path,data_read,&data_read_len);

	//MessageBox((CString)data_read);
	char ch_last=data_read[data_read_len-1];
	if(0x35!=ch_last)
	{
		MessageBox("��ѡ��Ĳ���CA֤�鱸���ļ�����ѡ��CA֤��ı����ļ����лָ���","�����ļ����ʹ���",MB_ICONEXCLAMATION);
		delete data_read;
		return;
	}
	

	ret=Sig_CACertRecovery(phHandle,data_read_len,data_read);
	if(0!=ret)
	{
		char sccrError[100]={0x00};
		retValueParse(ret,sccrError);
		MessageBox("CA֤��ָ�ʧ��"+(CString)sccrError,"",MB_ICONEXCLAMATION);
		return;
	}
	MessageBox("�����ɹ�","",MB_ICONEXCLAMATION);
	CCACertMngr::ShowCACertInfo();
	memset(check_cc,0,256);
	i_checked_cc = 0;

	isCheckbox_cc = FALSE;

	delete data_read;
}


void CCACertMngr::ShowCACertInfo_Search(CString index,CString name,CString algid,CString atName)
{
	m_CACert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Sig_CACertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("��ȡCA֤���б�ʧ��"+(CString)outAkgl,"��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Sig_CACertGetList(phHandle,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("��ȡCA֤���б�ʧ��"+(CString)outAkgl2,"��ʾ",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGCACertGetList.txt",puiKeyList,puiKeyListLen);
	//return;
	CAISH caish[256]={0x00};

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

//		m_CACert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------֤������
		char *str_appName = strstr(str2,"|");
		memcpy(appNameBuf,str2,str_appName-str2);
//		m_CACert.SetItemText(nCount, 2,appNameBuf);   
		memcpy(caish[i].name,str2,str_appName-str2);
		char *str3 = str2 + strlen(appNameBuf) + 1;

		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str3,"|");
		memcpy(algIdBuf,str3,str_algId-str3);
		char *str4 = str3 + strlen(algIdBuf)+1;

		//֤�����к�
		char keyIndexBuf[50]={0x00};
		char *str_keyIndex = strstr(str4,"|");
		memcpy(keyIndexBuf,str4,str_keyIndex-str4);
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
//		m_CACert.SetItemText(nCount,3,alg); 
		memcpy(caish[i].algid,alg.GetBuffer(),alg.GetLength());

		char *str6 = str5 + strlen(keyLength)+1;

		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
//		m_CACert.SetItemText(nCount,4,atName); 
		memcpy(caish[i].atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;

		char hostName[50]={0x00};
		char *str_hostName = strstr(str7,"|");
		memcpy(hostName,str7,str_hostName-str7);
//		m_CACert.SetItemText(nCount,5,hostName); 
		memcpy(caish[i].hostName,str7,str_hostName-str7);
		char *str8 = str7 + strlen(hostName)+1;

		char hostPhone[50]={0x00};
		char *str_hostPhone = strstr(str8,"|");
		memcpy(hostPhone,str8,str_hostPhone-str8);
//		m_CACert.SetItemText(nCount,6,hostPhone); 
		memcpy(caish[i].hostPhone,str8,str_hostPhone-str8);
		char *str9 = str8 + strlen(hostPhone)+1;

		char serialNum[32]={0x00};
		char *str_serialNum = strstr(str9,"|");
		memcpy(serialNum,str9,str_serialNum-str9);
//		m_CACert.SetItemText(nCount, 1,serialNum); 
		memcpy(caish[i].index,str9,str_serialNum-str9);
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
	if(!m_CA_CertIndex_fors.IsEmpty() && m_CA_CertName_fors.IsEmpty() && m_CA_Alg_fors.IsEmpty() && m_CA_atName_fors.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(!strcmp(m_CA_CertIndex_fors.GetBuffer(),(char *)caish[i].index))
			{
				m_CACert.InsertItem(0,0);
				m_CACert.SetItemText(0,1,(char *)caish[i].index);
				m_CACert.SetItemText(0,2,(char *)caish[i].name);
				/*CString alg;
				if(!strncmp("131328",(char *)caish[i].algid,6))
					alg = "SM2";
				if(!strncmp("65536",(char *)caish[i].algid,5))
					alg = "RSA";
				m_CACert.SetItemText(0,3,alg);*/
				m_CACert.SetItemText(0,3,(char *)caish[i].algid);
				m_CACert.SetItemText(0,4,(char *)caish[i].atName);
				m_CACert.SetItemText(0,5,(char *)caish[i].hostName);
				m_CACert.SetItemText(0,6,(char *)caish[i].hostPhone);
				break;
			}
		}
	}

	//����֤�����Ʋ�ѯ 
	else if(m_CA_CertIndex_fors.IsEmpty() && !m_CA_CertName_fors.IsEmpty() && m_CA_Alg_fors.IsEmpty() && m_CA_atName_fors.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr((char *)caish[i].name,m_CA_CertName_fors.GetBuffer()))
			{
				m_CACert.InsertItem(nCount,0);
				m_CACert.SetItemText(nCount,1,(char *)caish[i].index);
				m_CACert.SetItemText(nCount,2,(char *)caish[i].name);
				m_CACert.SetItemText(nCount,3,(char *)caish[i].algid);
				m_CACert.SetItemText(nCount,4,(char *)caish[i].atName);
				m_CACert.SetItemText(nCount,5,(char *)caish[i].hostName);
				m_CACert.SetItemText(nCount,6,(char *)caish[i].hostPhone);
			//	break;
				nCount++;
			}
		}
	}

	//�����㷨��ѯ
	else if(m_CA_CertIndex_fors.IsEmpty() && m_CA_CertName_fors.IsEmpty() && !m_CA_Alg_fors.IsEmpty() && m_CA_atName_fors.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL!=strstr((char *)caish[i].algid,m_CA_Alg_fors.GetBuffer()))
			{
				m_CACert.InsertItem(nCount,0);
				m_CACert.SetItemText(nCount,1,(char *)caish[i].index);
				m_CACert.SetItemText(nCount,2,(char *)caish[i].name);
				m_CACert.SetItemText(nCount,3,(char *)caish[i].algid);
				m_CACert.SetItemText(nCount,4,(char *)caish[i].atName);
				m_CACert.SetItemText(nCount,5,(char *)caish[i].hostName);
				m_CACert.SetItemText(nCount,6,(char *)caish[i].hostPhone);
			//	break;
				nCount++;
			}
		}
	}

	//���ջ������Ʋ�ѯ
	else if(m_CA_CertIndex_fors.IsEmpty() && m_CA_CertName_fors.IsEmpty() && m_CA_Alg_fors.IsEmpty() && !m_CA_atName_fors.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr((char *)caish[i].atName,m_CA_atName_fors.GetBuffer()))
			{
				m_CACert.InsertItem(nCount,0);
				m_CACert.SetItemText(nCount,1,(char *)caish[i].index);
				m_CACert.SetItemText(nCount,2,(char *)caish[i].name);
				m_CACert.SetItemText(nCount,3,(char *)caish[i].algid);
				m_CACert.SetItemText(nCount,4,(char *)caish[i].atName);
				m_CACert.SetItemText(nCount,5,(char *)caish[i].hostName);
				m_CACert.SetItemText(nCount,6,(char *)caish[i].hostPhone);
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

	m_CACert.Scroll( CSize( 0, 100000 ) );
}
