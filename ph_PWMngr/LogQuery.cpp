// LogQuery.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "LogQuery.h"
#include "afxdialogex.h"



// CLogQuery �Ի���
/***************������ѯ***************************************/
unsigned int totalItem=0;//�ܵļ�¼����
CString LogContentCache;
unsigned int page = 0;//�û���ʵ�ֵĻ����˱�������ڼ��β�ѯ
unsigned int current_page = 0;

CWnd *tip_cWnd=NULL;
/*****************������ѯ*********************************/
CString Logstarttime ;//�����ѯ������������֤��ҳ��������������
CString Logendtime ;
CString Logoptkind;
unsigned int page_search = 0;//������ѯʱ��ѯ�Ĵ���
unsigned int totalItem_search = 0;
IMPLEMENT_DYNAMIC(CLogQuery, CDialogEx)

CLogQuery::CLogQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogQuery::IDD, pParent)
	, m_timeStart_cs(_T(""))
	, m_timeEnd_cs(_T(""))
	, m_optKind_cs(_T(""))
{

}

CLogQuery::~CLogQuery()
{
}

void CLogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_log, m_lc_log);
	DDX_Control(pDX, IDC_EDIT_TIMESTART, m_timeStart);
	DDX_Control(pDX, IDC_EDIT_TIMEEND, m_timeEnd);
	//DDX_Control(pDX, IDC_EDIT_OPTKIND, m_optKind);
	DDX_Text(pDX,IDC_EDIT_TIMESTART,m_timeStart_cs);
	DDX_Text(pDX,IDC_EDIT_TIMEEND,m_timeEnd_cs);
	//DDX_Text(pDX,IDC_EDIT_OPTKIND,m_optKind_cs);
	DDX_Control(pDX, IDC_COMBO_OPTRESULT, m_optresult_CBox);
}


BEGIN_MESSAGE_MAP(CLogQuery, CDialogEx)
	//ON_BN_CLICKED(IDC_RADIO_log_time, &CLogQuery::OnBnClickedRadiologtime)
	//ON_BN_CLICKED(IDC_RADIO_log_admname, &CLogQuery::OnBnClickedRadiologadmname)
	ON_BN_CLICKED(IDC_BUTTON_first_page, &CLogQuery::OnBnClickedButtonfirstpage)
	ON_BN_CLICKED(IDC_BUTTON_prepage, &CLogQuery::OnBnClickedButtonprepage)
	ON_BN_CLICKED(IDC_BUTTON_nextpage, &CLogQuery::OnBnClickedButtonnextpage)
	ON_BN_CLICKED(IDC_BUTTON_lastpage, &CLogQuery::OnBnClickedButtonlastpage)
	ON_BN_CLICKED(IDC_BUTTON_serch_log, &CLogQuery::OnBnClickedButtonserchlog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_log, &CLogQuery::OnLvnItemchangedListlog)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CLogQuery::OnHdnItemStateIconClickListlog)
	ON_COMMAND(ID__Log_detail, &CLogQuery::OnLogDetail)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_log, &CLogQuery::OnNMRClickAppkeymngrList)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTRESULT, &CLogQuery::OnCbnSelchangeComboOptresult)
	//ON_CBN_DBLCLK(IDC_COMBO_OPTRESULT, &CLogQuery::OnCbnDblclkComboOptresult)
END_MESSAGE_MAP()


// CLogQuery ��Ϣ�������


BOOL CLogQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//	CheckDlgButton(IDC_RADIO_log_time, 1);
//	CLogQuery::OnBnClickedRadiologtime();
	CRect rect;   
 
    m_lc_log.GetClientRect(&rect);   
   
    m_lc_log.SetExtendedStyle(m_lc_log.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   


	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_lc_log.SetImageList(&img_list,LVSIL_SMALL); 


	m_lc_log.InsertColumn(0,NULL,LVCFMT_CENTER,50);        //����б���
    m_lc_log.InsertColumn(1, _T("��־���"), LVCFMT_CENTER,(rect.Width()-50)/5-50, 1);   
    m_lc_log.InsertColumn(2, _T("����ģ��"), LVCFMT_CENTER, (rect.Width()-50)/5, 2);   
    m_lc_log.InsertColumn(3, _T("����ʱ��"), LVCFMT_CENTER, (rect.Width()-50)/5+50, 3); 
	m_lc_log.InsertColumn(4, _T("��������"), LVCFMT_CENTER, (rect.Width()-50)/5, 4); 
	m_lc_log.InsertColumn(5, _T("���"), LVCFMT_CENTER, (rect.Width()-50)/5, 5);

	HWND header = ListView_GetHeader(m_lc_log);
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

	isCheckbox_log = FALSE;
	memset(check_log,0,256);
	i_checked_log = 0;

	page=1;//��һ�β�
	current_page=0;//��ǰҳ����ʼ��Ϊ0
	page_search = 1;//������ѯʱ�Ĵ���


	//��ʼ����ʾ��������������
	m_optresult_CBox.AddString(_T("ʧ��"));
	m_optresult_CBox.InsertString(1,_T("�ɹ�"));
	SetDlgItemText(IDC_COMBO_OPTRESULT, _T("�ɹ�"));  
	 //�ؼ��б��һ��
	//CComboBox����Ϊֻ��,��ֹ�û��Լ�������ɲ���Ҫ���鷳
	//CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_OPTRESULT))->GetWindow(GW_CHILD));	
	//pEdit->SetReadOnly(TRUE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLogQuery::OnBnClickedButtonfirstpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret=0;
	UpdateData(TRUE);
	
	//if(page==0)
	if(current_page==0)
	{
		MessageBox("������ѯ��ʼ��","",MB_ICONEXCLAMATION);
		return;
	}
	//if(page==1)
	if(current_page==1)
	{
		MessageBox("�Ѿ��ǵ�һҳ��","",MB_ICONEXCLAMATION);
		return;
	}
	
	//page=1;
	current_page=1;
	m_lc_log.SetRedraw(FALSE);

//	CLogQuery::LogStringGetAndParse();
	CLogQuery::LogStringParseAndShow(current_page);

	m_lc_log.SetRedraw(TRUE);
    m_lc_log.Invalidate();
    m_lc_log.UpdateWindow();
	
}


void CLogQuery::OnBnClickedButtonprepage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	/**************************û������������������***************************/
	if(m_timeStart_cs.IsEmpty()&&m_timeEnd_cs.IsEmpty()&&m_optKind_cs.IsEmpty())
	{
		if(page==0)
		{
			MessageBox("������ѯ��ʼ��","",MB_ICONEXCLAMATION);
			return;
		}
		if(page==1)
		{
			MessageBox("�Ѿ��ǵ�һҳ��","",MB_ICONEXCLAMATION);
			return;
		}
	
		page--;
		m_lc_log.SetRedraw(FALSE);
		CLogQuery::LogStringGetAndParse();
		m_lc_log.SetRedraw(TRUE);
		m_lc_log.Invalidate();
		m_lc_log.UpdateWindow();
	}
	/***************************����������������������******************************/
	else{
			if((Logstarttime != m_timeStart_cs)||(Logendtime != m_timeEnd_cs)||(Logoptkind != m_optKind_cs))//��ҳǰ��������һ����ʾ
			{
				MessageBox("�뱣֤����������ҳǰ��һ�£�","",MB_ICONEXCLAMATION);
				return;
			}
			else{
				if(page_search==0)
				{
					MessageBox("������ѯ������","",MB_ICONEXCLAMATION);
					return;
				}
				if(page_search == 1)
				{
					MessageBox("�Ѿ��ǵ�һҳ��","",MB_ICONEXCLAMATION);
					return;
				}
				page_search --;
				m_lc_log.SetRedraw(FALSE);
				CLogQuery::LogStringGetAndParse_Search(Logstarttime,Logendtime,Logoptkind);
				m_lc_log.SetRedraw(TRUE);
				m_lc_log.Invalidate();
				m_lc_log.UpdateWindow();
				}
		}
	
}


void CLogQuery::OnBnClickedButtonnextpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	/**************************û������������������***************************/
	if(m_timeStart_cs.IsEmpty()&&m_timeEnd_cs.IsEmpty()&&m_optKind_cs.IsEmpty())
	{
		if(page==0)
		{
			MessageBox("������ѯ��ʼ��","",MB_ICONEXCLAMATION);
			return;
		}
	
		if(totalItem < 100)
		{
			MessageBox("�Ѿ������һҳ��","",MB_ICONEXCLAMATION);
			return;
		}

		page++;
		m_lc_log.SetRedraw(FALSE);
		CLogQuery::LogStringGetAndParse();
		m_lc_log.SetRedraw(TRUE);
		m_lc_log.Invalidate();
		m_lc_log.UpdateWindow();
		if(totalItem < 100)
		{
			MessageBox("�Ѿ������һҳ��","",MB_ICONEXCLAMATION);
			return;
		}
	}
	/***************************����������������������******************************/
	else{
			if((Logstarttime != m_timeStart_cs)||(Logendtime != m_timeEnd_cs)||(Logoptkind != m_optKind_cs))//��ҳǰ��������һ����ʾ
			{
				MessageBox("�뱣֤����������ҳǰ��һ�£�","",MB_ICONEXCLAMATION);
				return;
			}
			else{
				if(page_search==0)
				{
					MessageBox("������ѯ������","",MB_ICONEXCLAMATION);
					return;
				}
				if(totalItem_search < 100)
				{
					MessageBox("�Ѿ������һҳ��","",MB_ICONEXCLAMATION);
					return;
				}
				page_search ++;
				m_lc_log.SetRedraw(FALSE);
				CLogQuery::LogStringGetAndParse_Search(Logstarttime,Logendtime,Logoptkind);//����ʲô�����Ͷ�ʲô����������CStringûֵ��Ϊ�մ���
				m_lc_log.SetRedraw(TRUE);
				m_lc_log.Invalidate();
				m_lc_log.UpdateWindow();
				if(totalItem_search < 100)
				{
					MessageBox("�Ѿ������һҳ��","",MB_ICONEXCLAMATION);
					return;
				}
			}
		
	}

}


void CLogQuery::OnBnClickedButtonlastpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//βҳ
	int ret=0;
//	UpdateData(TRUE);
//	if(page==0)
	if(current_page==0)
	{
		MessageBox("������ѯ��ʼ��","",MB_ICONEXCLAMATION);
		return;
	}
//	if(page-1==totalItem/20)//��Ҫ���������Ƿ�ͷ���ж�
//	if(current_page==totalItem/20)
	if(current_page-1==totalItem/20 || current_page*20==totalItem)
	{
		MessageBox("�Ѿ������һҳ��","",MB_ICONEXCLAMATION);
		return;
	}
	
	if(totalItem%20!=0)
		current_page=(totalItem/20)+1;
	else
		current_page=totalItem/20;
//	current_page=5;
	m_lc_log.SetRedraw(FALSE);

//	CLogQuery::LogStringGetAndParse();
	CLogQuery::LogStringParseAndShow(current_page);

	m_lc_log.SetRedraw(TRUE);
    m_lc_log.Invalidate();
    m_lc_log.UpdateWindow();
	
}


void CLogQuery::OnBnClickedButtonserchlog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ѯ��ť
	UpdateData(TRUE);
	 Logstarttime = m_timeStart_cs;//�����������������ڷ�ҳʱ��֤��������
	 Logendtime = m_timeEnd_cs;
	 Logoptkind = m_optKind_cs;
	 //�����ѯ��Ĭ�ϴӵ�һҳ��ʼ����
	 page=1;//��һ�β�
	 page_search = 1;//������ѯʱ�Ĵ���
	//���������Ϊ�գ�������ѯ��ʾ
	if(m_timeStart_cs.IsEmpty()&&m_timeEnd_cs.IsEmpty()&&m_optKind_cs)
	{
		m_lc_log.SetRedraw(FALSE);
		CLogQuery::LogStringGetAndParse();
		//CLogQuery::LogStringGetAndParse();
		m_lc_log.SetRedraw(TRUE);
		m_lc_log.Invalidate();
		m_lc_log.UpdateWindow();
		page++;//��ʾ��һ�β�ѯ��ť����ѯ������1
		if(totalItem<100)
		{
			page--;
			MessageBox("��־��ѯ������","",MB_ICONEXCLAMATION);
			return;
		}
	}
	else//����ʲô�����Ͷ�ʲô����������CStringûֵ��Ϊ�մ���
	{
		/********************�ж�ʱ���ʽ*************************/
		char *start =  (LPSTR)(LPCTSTR) Logstarttime;
		char *end = (LPSTR)(LPCTSTR) Logendtime;
		char *start1 = start + 4;
		char *start2 = start1 + 3;
		char * end1 = end + 4;
		char * end2 = end1 + 3;
		if((start1[0] != '-')||(start2[0] != '-')||(end1[0] != '-')||(end2[0] != '-'))
		{
			MessageBox("�뱣֤���ڸ�ʽΪ��-��-��","",MB_ICONEXCLAMATION);
			return ;
		}
		m_lc_log.SetRedraw(FALSE);
		CLogQuery::LogStringGetAndParse_Search(Logstarttime,Logendtime,Logoptkind);
		m_lc_log.SetRedraw(TRUE);
		m_lc_log.Invalidate();
		m_lc_log.UpdateWindow();
		page_search++;//��ʾ��һ�β�ѯ��ť����ѯ������1
		if(totalItem_search<100)
		{
			page_search--;
			MessageBox("��־������ѯ������","",MB_ICONEXCLAMATION);
			return;
		}
	}
		
}

void CLogQuery::LogStringGetAndParse()
{
	unsigned char *logcontent=NULL;
	unsigned int logcontentlength=0;
	unsigned int	pubkeylen=0;
	unsigned char	*pubkey=NULL;
	totalItem=0;
	
	for(int i=0;i<100;i++)
	{
		memset(&logitem[i],0x00,sizeof(LOGITEM));
	}

	m_lc_log.DeleteAllItems();

	int ret=0;
	ret=Sig_GetLog(phHandle_log,page,&totalItem,logcontent,&logcontentlength,&pubkeylen,pubkey);
	if(0 != ret)
	{
		char sglerr[100]={0x00};
		retValueParse(ret,sglerr);
		MessageBox("��ȡ��־��¼����ʧ��"+(CString)sglerr,"ʧ��",MB_ICONEXCLAMATION);
		return ;
	}
	logcontent=new unsigned char[logcontentlength+1];
	memset(logcontent,0x00,logcontentlength);
	pubkey=new unsigned char[pubkeylen+1];
	memset(pubkey,0x00,pubkeylen+1);
	ret=Sig_GetLog(phHandle_log,page,&totalItem,logcontent,&logcontentlength,&pubkeylen,pubkey);
	if(0 != ret)
	{
		char sglerror[100]={0x00};
		retValueParse(ret,sglerror);
		MessageBox("��ȡ��־ʧ��"+(CString)sglerror,"ʧ��",MB_ICONEXCLAMATION);
		delete []logcontent;
		delete []pubkey;
		return ;
	}
	if(logcontentlength==0)
	{
	  return ;
	}		

	LogContentCache.Format("%s",logcontent);
	memset(&rsaPubKeyCache,0x00,sizeof(RSAPUBLICKEYBLOB));
	memcpy(&rsaPubKeyCache,pubkey,pubkeylen);
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_1.txt",(unsigned char*)&rsaPubKeyCache,sizeof(RSAPUBLICKEYBLOB));
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_2.txt",pubkey,sizeof(RSAPUBLICKEYBLOB));

	char *start,*end,*str,*str_time;

	char index[32]={0x00};
	char opt[32]={0x00};
	char opt_kind[32]={0x00};
	char opt_result[32]={0x00};
	char opt_time[32]={0x00};

	str_time=strstr((char*)logcontent,"ucOptionTime");
	str=str_time+sizeof("ucOptionTime");
	int nCount=0;

	for(int i=0;i<100;i++)
	{
		if(0==*str)
			 break;
		start=strstr(str,"|");
		if(start==NULL)
			break;
		
		memcpy(index,str,start-str);
		memcpy(logitem[i].index,str,start-str);//------�ŵ��ṹ�建������
		if(i<100)
		{
			m_lc_log.InsertItem(nCount,0);
			m_lc_log.SetItemText(nCount,1,index);
		}
		end=start+strlen("|");
		memset(index,0x00,32);

		start=strstr(end,"|");
		end=start+strlen("|");

		start=strstr(end,"|");
		if(start==NULL)
		{
			MessageBox("startΪ��!");
			break;
		}
		memset(opt,0x00,32);
		memcpy(opt,end,start-end);
		memcpy(logitem[i].opt,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,2,opt);
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_kind,0x00,32);
		memcpy(opt_kind,end,start-end);
		memcpy(logitem[i].opt_kind,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,4,opt_kind);
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_result,0x00,32);
		memcpy(opt_result,end,start-end);
		memcpy(logitem[i].opt_result,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,5,opt_result);
		end=start+strlen("|");

		start=strstr(end,"|");//����
		end=start+strlen("|");

		start=strstr(end,"|");//ǩ��ֵ
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_time,0x00,32);
		memcpy(opt_time,end,19);
		memcpy(logitem[i].opt_time,end,19);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,3,opt_time);
//		end=start+20;

		nCount++;
		str=end+19;
	}

	delete []logcontent;
	delete []pubkey;
}

void CLogQuery::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_lc_log); nItem++) 
	{
		ListView_SetCheckState(m_lc_log, nItem, fChecked);
	}
}

void CLogQuery::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_lc_log); nItem++) 
	{
		if (!ListView_GetCheckState(m_lc_log, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_lc_log);
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

void CLogQuery::OnLvnItemchangedListlog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_log = TRUE;
		i_checked_log++;
		CString str1,str2,str3;
		nId_row_log = pNMLV->iItem;
		nId_row_mux_log[i_checked_log] = pNMLV->iItem;
		str2=m_lc_log.GetItemText(pNMLV->iItem,1);//��ѡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_log;i++)
		{
			if(check_log[i] == 0)
				check_log[i] = atoi(str2);
		}
		m_lc_log.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//ѡ���������ʾ
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_log = 0;
		
		str=m_lc_log.GetItemText(pNMLV->iItem,1);//��ѡ��ȡ��ѡ��ʱ��ȡ����ֵ
		for(int i = 0;i < i_checked_log;i++)
		{
			if(check_log[i] == atoi(str))
				check_log[i] = 0;
		}
		i_checked_log--;
		if(i_checked_log != 0)
			isCheckbox_log = TRUE;
		else if(i_checked_log == 0)
			isCheckbox_log = FALSE;
		m_lc_log.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//ȡ��ѡ�У���ȡ��������ʾ
	} 
}


void CLogQuery::OnHdnItemStateIconClickListlog(NMHDR *pNMHDR, LRESULT *pResult)
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


void CLogQuery::OnLogDetail()
{
	// TODO: �ڴ���������������
	int ret=0;
	CString optime;
	CString logIndex;
	char index[32]={0x00};
	int nId;

	unsigned int AllSignDataLength=0;
	unsigned char AllSignData[4096]={0x00};

	unsigned int nameLen=0;
	unsigned char name[128]={0x00};

	unsigned int idLen=0;
	unsigned char id[128]={0x00};

	unsigned int opKindLen=0;
	unsigned char opKind[128]={0x00};

	unsigned int opContentLen=0;
	unsigned char opContent[128]={0x00};

	unsigned int opResultLen=0;
	unsigned char opResult[128]={0x00};

	unsigned int opDetailLen=0;
	unsigned char opDetail[1024]={0x00};


	if(!isCheckbox_log)
	{
		MessageBox(_T("������ѡ��һ�м�¼��"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_log)
	{
		if(i_checked_log > 1)
		{
			MessageBox("�ù��ܲ�֧�ֶ�ѡ��","��ʾ",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_log;
		}
	}
	optime=m_lc_log.GetItemText(nId,3);
	logIndex=m_lc_log.GetItemText(nId,1);
	sprintf(index,"%s|",(LPSTR)(LPCTSTR)logIndex);

	//�ӻ������ҵ������Ŷ�Ӧ����־��������ԭ�ĺ�ǩ��ֵ
	char *str=strstr((LPSTR)(LPCTSTR)LogContentCache,index);//107|
	if(str==NULL)
	{
		MessageBox("û���ҵ���Ӧ��¼��","",MB_ICONEXCLAMATION);
		return;
	}

	char *str_1=strstr(str,"|");//|adm_test


	char *str_2=str_1+strlen("|");//adm_test
	char *str_3=strstr(str_2,"|");//|adm_login

	memcpy(AllSignData,str_2,str_3-str_2);
	AllSignDataLength+=str_3-str_2;

	memcpy(name,str_2,str_3-str_2);
	nameLen=str_3-str_2;

	char *str_4=str_3+strlen("|");//adm_login
	char *str_5=strstr(str_4,"|");//|login

	memcpy(AllSignData+AllSignDataLength,str_4,str_5-str_4); 
	AllSignDataLength+=str_5-str_4;

	memcpy(opKind,str_4,str_5-str_4);
	opKindLen=str_5-str_4;

	char *str_6=str_5+strlen("|");//login
	char *str_7=strstr(str_6,"|");//|success

	memcpy(AllSignData+AllSignDataLength,str_6,str_7-str_6);
	AllSignDataLength+=str_7-str_6;

	memcpy(opKind,"-",strlen("-"));
	opKindLen+=strlen("-");
	memcpy(opKind,str_4,str_5-str_4);
	opKindLen+=str_7-str_6;

	char *str_8=str_7+strlen("|");//success
	char *str_9=strstr(str_8,"|");//|admin:adm_test,loginsuccess------------����

	memcpy(AllSignData+AllSignDataLength,str_8,str_9-str_8);
	AllSignDataLength+=str_9-str_8;

	memcpy(opResult,str_8,str_9-str_8);
	opResultLen=str_9-str_8;

	char *str_10=str_9+strlen("|");//admin:adm_test,loginsuccess------------����
	char *str_11=strstr(str_10,"|");//|ǩ��ֵ��B64����ֵ

	memcpy(AllSignData+AllSignDataLength,str_10,str_11-str_10);
	AllSignDataLength+=str_11-str_10;

	memcpy(opDetail,str_10,str_11-str_10);
	opDetailLen=str_11-str_10;

	char *detail_str=strstr((char*)opDetail,"ADMID=");
	char *detail_admid=detail_str+strlen("ADMID=");
	char *detail_id=strstr(detail_str,",");
	memcpy(id,detail_admid,detail_id-detail_admid);
	idLen=detail_id-detail_admid;

	char *str_12=str_11+strlen("|");//ǩ��ֵ��B64����ֵ
	char *str_13=strstr(str_12,"|");//|2013-11-09 00:34:57
	char *str_14=str_13+strlen("|");//2013-11-09 00:34:57

	memcpy(AllSignData+AllSignDataLength,str_14,19);
	AllSignDataLength+=19;

	unsigned int sign_value_len=0;
	unsigned char sign_value[1024]={0x00};
	unsigned int sign_value_decode_len=0;
	unsigned char sign_value_decode[1024]={0x00};
	unsigned long rsa_out_data_len=0;
	unsigned char rsa_out_data[1024]={0x00};


	sign_value_len=str_13-str_12;
	memcpy(sign_value,str_12,str_13-str_12);//B64��ʽ��ǩ��ֵ


//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\sign_value.txt",sign_value,sign_value_len);
	sign_value_decode_len=Km_Decode((char*)sign_value,sign_value_len,(char*)sign_value_decode);

//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\sign_value_decode.txt",sign_value_decode,sign_value_decode_len);

	CKeyDao keyDao;
	DEVHANDLE handle=0;


	if(!keyDao.OpenDevice(&handle))
	{
		MessageBox("���豸ʧ��","",MB_ICONEXCLAMATION);
		return;
	}

	LPSTR szAppName = "wellhope";
	HAPPLICATION phApplication;
	if(!keyDao.OpenApplication(handle,szAppName,&phApplication))
	{
		MessageBox("��Ӧ��ʧ��","");
		return;
	}
	LPSTR szContainerName = "LAB_USERCERT";
	HCONTAINER hcontainer;
	if(!keyDao.OpenContainer(phApplication,szContainerName,&hcontainer))
	{
		MessageBox("������ʧ��","");
		return;
	}
	ULONG pulContainerType=0;	
	if(!keyDao.GetContainerType(hcontainer,&pulContainerType))
	{				
		MessageBox("��ȡ��������ʧ�ܣ�","");
		return;
	}
	int  uiHashAlgo = 0;
	int seH = 0;
	HANDLE pHash = (void *)&seH;
	if(pulContainerType == 1)
	{
		uiHashAlgo = SGD_SHA1;
	}
	else if(pulContainerType == 2)
	{
		uiHashAlgo = SGD_SM3;
	}
	else
	{
		MessageBox("��ȡ��������ʧ�ܣ�","");
		return;
	}
	if(!keyDao.DigestInit(handle,SGD_SHA1,NULL,NULL,0,&pHash))
	{
		MessageBox("��ϣ��ʼ��ʧ��","",MB_ICONEXCLAMATION);
		return;
	}
	BYTE pbHashData[256]={0x00};
	ULONG pulHashLen=sizeof(pbHashData);
	if(!keyDao.Digest(pHash,AllSignData,AllSignDataLength,pbHashData,&pulHashLen))
	{
		MessageBox("��ϣʧ��","");
		return;
	}
	CMyUtil::Write2File("C:\\AllSignData.txt",AllSignData,AllSignDataLength);
	CLogQuery::ReverseData(sign_value_decode,sign_value_decode_len);
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_3.txt",(unsigned char*)&rsaPubKeyCache,sizeof(RSAPUBLICKEYBLOB));
	//if(!keyDao.ExtRSAPubKeyOperation(handle,&rsaPubKeyCache,sign_value_decode,sign_value_decode_len,rsa_out_data,&rsa_out_data_len))
	//{
	//	MessageBox("��Կ����ʧ�ܣ�","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//if(!memcmp(pbHashData,&rsa_out_data[rsa_out_data_len-pulHashLen],pulHashLen))
	//{
	//	MessageBox("��֤��־ǩ��ֵʧ�ܣ���־�����ѱ��۸ģ�","",MB_ICONEXCLAMATION);
	//	return;
	//}
	////��ʾ
	CString lgd_adm_id;
	lgd_adm_id.Format("%s",id);
	CString lgd_opKind;
	lgd_opKind.Format("%s",opKind);
	CString lgd_name;
	lgd_name.Format("%s",name);
	CString lgd_opResult;
	lgd_opResult.Format("%s",opResult);
	CString lgd_opDetail;
	lgd_opDetail.Format("%s",opDetail);
	CSeeLogDetail lgdDlg(logIndex,lgd_adm_id,lgd_opKind,optime,lgd_name,lgd_opResult,lgd_opDetail);
	lgdDlg.DoModal();
	isCheckbox_log = FALSE;
	memset(check_log,0,256);
	i_checked_log = 0;
}


void CLogQuery::OnNMRClickAppkeymngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_Log));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ�� 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}


void CLogQuery::LogStringParseAndShow(unsigned int current_page)
{
	m_lc_log.DeleteAllItems();

	int nCount=0;

	for(unsigned int i = (current_page-1)*20;i<((current_page)*20);i++)//syc
	{
		if(i>(totalItem-1))
			break;
		m_lc_log.InsertItem(nCount,0);
		m_lc_log.SetItemText(nCount,1,(LPCTSTR)logitem[i].index);
		m_lc_log.SetItemText(nCount,2,(LPCTSTR)logitem[i].opt);
		m_lc_log.SetItemText(nCount,3,(LPCTSTR)logitem[i].opt_time);
		m_lc_log.SetItemText(nCount,4,(LPCTSTR)logitem[i].opt_kind);
		m_lc_log.SetItemText(nCount,5,(LPCTSTR)logitem[i].opt_result);

		nCount++;
	}
}


void CLogQuery::ReverseData(unsigned char * pdata, unsigned int len)
{
	unsigned int i=0, j=len-1;
	unsigned char temp=0;

	while (i<j)
	{
		temp=pdata[i];
		pdata[i]=pdata[j];
		pdata[j]=temp;
		i++;	
		j--;
	}

}

void CLogQuery::LogStringGetAndParse_Search(CString Logstarttime,CString Logendtime,CString Logoptkind)
{
	unsigned char *logcontent=NULL;
	unsigned int logcontentlength=0;
	unsigned int	pubkeylen=0;
	unsigned char	*pubkey=NULL;
	totalItem_search=0;
	/************���Դ���**************/
	CString startTime = Logstarttime;
	CString endTime = Logendtime;
	CString optKind = Logoptkind;
	/********************************/
	/*for(int i=0;i<100;i++)
	{
		memset(&logitem[i],0x00,sizeof(LOGITEM));
	}
*/
	m_lc_log.DeleteAllItems();

	int ret=0;
	/*****************���÷���˽ӿ�ͨ����������������������������־���ݼ�������һ��һ����***********************/
	//ret=Sig_GetLog(phHandle_log,page_search/******������ѯҳ��*****/,&totalItem_search/***�ټ���Logstarttime,Logendtime,Logopkind��������***/
	//	,logcontent,&logcontentlength,&pubkeylen,pubkey);
	//if(0 != ret)
	//{
	//	char sglerr[100]={0x00};
	//	retValueParse(ret,sglerr);
	//	MessageBox("������־��¼����ʧ��"+(CString)sglerr,"ʧ��",MB_ICONEXCLAMATION);
	//	return ;
	//}
	//logcontent=new unsigned char[logcontentlength+1];
	//memset(logcontent,0x00,logcontentlength);
	//pubkey=new unsigned char[pubkeylen+1];
	//memset(pubkey,0x00,pubkeylen+1);
	//ret=Sig_GetLog(phHandle_log,page,&totalItem,logcontent,&logcontentlength,&pubkeylen,pubkey);
	//if(0 != ret)
	//{
	//	char sglerror[100]={0x00};
	//	retValueParse(ret,sglerror);
	//	MessageBox("������־ʧ��"+(CString)sglerror,"ʧ��",MB_ICONEXCLAMATION);
	//	delete []logcontent;
	//	delete []pubkey;
	//	return ;
	//}
	/*****************���÷���˽ӿ�ͨ����������������������������־���ݼ�������һ��һ����***********************/
	if(logcontentlength==0)
	{
	  return ;
	}		

	LogContentCache.Format("%s",logcontent);
	memset(&rsaPubKeyCache,0x00,sizeof(RSAPUBLICKEYBLOB));
	memcpy(&rsaPubKeyCache,pubkey,pubkeylen);
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_1.txt",(unsigned char*)&rsaPubKeyCache,sizeof(RSAPUBLICKEYBLOB));
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_2.txt",pubkey,sizeof(RSAPUBLICKEYBLOB));

	char *start,*end,*str,*str_time;

	char index[32]={0x00};
	char opt[32]={0x00};
	char opt_kind[32]={0x00};
	char opt_result[32]={0x00};
	char opt_time[32]={0x00};

	str_time=strstr((char*)logcontent,"ucOptionTime");
	str=str_time+sizeof("ucOptionTime");
	int nCount=0;

	for(int i=0;i<100;i++)
	{
		if(0==*str)
			 break;
		start=strstr(str,"|");
		if(start==NULL)
			break;
		
		memcpy(index,str,start-str);
	//	memcpy(logitem[i].index,str,start-str);//------�ŵ��ṹ�建������
		if(i<100)
		{
			m_lc_log.InsertItem(nCount,0);
			m_lc_log.SetItemText(nCount,1,index);
		}
		end=start+strlen("|");
		memset(index,0x00,32);

		start=strstr(end,"|");
		end=start+strlen("|");

		start=strstr(end,"|");
		if(start==NULL)
		{
			MessageBox("startΪ��!");
			break;
		}
		memset(opt,0x00,32);
		memcpy(opt,end,start-end);
	//	memcpy(logitem[i].opt,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,2,opt);
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_kind,0x00,32);
		memcpy(opt_kind,end,start-end);
	//	memcpy(logitem[i].opt_kind,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,4,opt_kind);
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_result,0x00,32);
		memcpy(opt_result,end,start-end);
	//	memcpy(logitem[i].opt_result,end,start-end);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,5,opt_result);
		end=start+strlen("|");

		start=strstr(end,"|");//����
		end=start+strlen("|");

		start=strstr(end,"|");//ǩ��ֵ
		end=start+strlen("|");

		start=strstr(end,"|");
		memset(opt_time,0x00,32);
		memcpy(opt_time,end,19);
	//	memcpy(logitem[i].opt_time,end,19);//------�ŵ��ṹ�建������
		if(i<100)
			m_lc_log.SetItemText(nCount,3,opt_time);
//		end=start+20;

		nCount++;
		str=end+19;
	}

	delete []logcontent;
	delete []pubkey;
}

void CLogQuery::OnCbnSelchangeComboOptresult()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel; 
    nSel =m_optresult_CBox.GetCurSel(); //��ȡ��Ͽ�ؼ��б����ѡ��������
	m_optresult_CBox.GetLBText(nSel,m_optKind_cs);
	//m_optresult_CBox.EnableWindow(FALSE);
	
	
	
}

