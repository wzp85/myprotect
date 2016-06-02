// SysLogQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SysLogQuery.h"
#include "afxdialogex.h"
#include "ForRecoveryFilePath.h"
#include "MyUtil.h"


// CSysLogQuery 对话框
//unsigned int totalItem = 0;//总的记录条数
////
//CString LogContentCache;//日志缓存
CWnd *syquery_cWnd=NULL;

IMPLEMENT_DYNAMIC(CSysLogQuery, CDialogEx)

CSysLogQuery::CSysLogQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysLogQuery::IDD, pParent)
{

}

CSysLogQuery::~CSysLogQuery()
{
}

void CSysLogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_LIST1, m_syslog_query);
	DDX_Control(pDX, IDC_SyslogQuery_LIST, m_Syslog_query);
}


BEGIN_MESSAGE_MAP(CSysLogQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_syslog_search, &CSysLogQuery::OnBnClickedButtonsyslogsearch)
	ON_BN_CLICKED(IDC_BUTTON1, &CSysLogQuery::OnBnClickedButtonfirstpage)
	ON_BN_CLICKED(IDC_BUTTON2, &CSysLogQuery::OnBnClickedButtonprepage)
	ON_BN_CLICKED(IDC_BUTTON3, &CSysLogQuery::OnBnClickedButtonnextpage)
	ON_BN_CLICKED(IDC_BUTTON4, &CSysLogQuery::OnBnClickedButtonlastpage)
	ON_NOTIFY(NM_RCLICK, IDC_SyslogQuery_LIST, &CSysLogQuery::OnNMRClickSyslogqueryList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SyslogQuery_LIST, &CSysLogQuery::OnLvnItemchangedSyslogqueryList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CSysLogQuery::OnHdnItemStateIconClickSyslogqueryList)
END_MESSAGE_MAP()






// CSysLogQuery 消息处理程序
BOOL CSysLogQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始
	CRect rect;
	m_Syslog_query.GetClientRect(&rect);
	m_Syslog_query.SetExtendedStyle(m_Syslog_query.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );

	
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_Syslog_query.SetImageList(&img_list,LVSIL_SMALL); 

	m_Syslog_query.InsertColumn(0,NULL,LVCFMT_CENTER,40);        //添加列标题
    m_Syslog_query.InsertColumn(1, _T("操作时间"), LVCFMT_CENTER,(rect.Width()-40)/3-90, 1);   
    m_Syslog_query.InsertColumn(2, _T("主机名"), LVCFMT_CENTER, (rect.Width()-40)/3-100, 2);   
    m_Syslog_query.InsertColumn(3, _T("消息内容"), LVCFMT_CENTER, (rect.Width()-40)/3+180, 3); 
	//m_Syslog_query.InsertColumn(4, _T("消息内容"), LVCFMT_CENTER, (rect.Width()-40)/4+150, 4); 



	HWND header = ListView_GetHeader(m_Syslog_query);
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
	
	page = 1;
	current_page = 0;


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/****************************************************/
void CSysLogQuery::OnBnClickedButtonsyslogsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	/*int ret = 0;*/
	/*m_Syslog_query.SetRedraw(FALSE);
	CSysLogQuery::LogStringGetAndParse();

	m_Syslog_query.SetRedraw(TRUE);
	m_Syslog_query.Invalidate();
	m_Syslog_query.UpdateWindow();*/

/*******************测试代码***************************/
	int ret = 0;
	int len = 0;
	char *path = NULL;
	CForRecoveryFilePath forRecoveryFilePath;
	if(IDOK != forRecoveryFilePath.DoModal())
	{
		return ;
	}
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);
	path = new char [len + 1];
	memset(path,0x00,len + 1);
	forRecoveryFilePath.GetRecoveryFilePath(path,&len);
	MessageBox(path);

	unsigned char *pucSysLog = NULL;
	unsigned int uiSysLogLength = 0;

	CMyUtil::ReadData(path,pucSysLog,&len);
	pucSysLog = new unsigned char [len];
	CMyUtil::ReadData(path,pucSysLog,&len);
	uiSysLogLength = len;
	CString SysLog;
	SysLog.Format("%s",pucSysLog);
	//MessageBox(SysLog);
	
	CString Sys_time,Sys_host,Sys_progm,Sys_messg;

	char*line_start = (char*)pucSysLog;
	char*start_keep = (char*)pucSysLog;
	char line_change[1] = {0x0A};  
	int nCount = 0;
	for(int i=0;i<100;i++)
	{	
		if(0 == line_start)
		{
			break;
		}
		char *line_end = CMyUtil:: Pub_MemSearch(line_start+1,len,line_change,1);
		if(NULL == line_end || (line_end-start_keep) >= len )
		{
			break;
		}
		char *str_kg1 = strstr(line_start," ");
		char *str_kg2 = strstr(str_kg1+2," ");
		char *str_kg3 = strstr(str_kg2+1," ");
		memset(logitem[nCount].timestmp,0x00,32);
		memcpy(logitem[nCount].timestmp,line_start,str_kg3-line_start);
		if(i < 20)
		{	
			m_Syslog_query.InsertItem(nCount,0);
			Sys_time.Format("%s",logitem[nCount].timestmp);
			m_Syslog_query.SetItemText(nCount,1,Sys_time);
			//m_Syslog_query.SetItemText(nCount,1,(LPCTSTR)logitem[nCount].timestmp);
		}
		char *str1 = strstr(str_kg3+1," ");
		memset(logitem[nCount].hostname,0x00,32);
		memcpy(logitem[nCount].hostname,str_kg3,str1-str_kg3);
		if(i < 20)
		{	
			Sys_host.Format("%s",logitem[nCount].hostname);
			m_Syslog_query.SetItemText(nCount,2,Sys_host);
			//m_Syslog_query.SetItemText(nCount,2,(LPCTSTR)logitem[nCount].hostname);
		}
		
		if(line_end-str1 < 64)
		{	
			memset(logitem[nCount].message,0x00,64);
			memcpy(logitem[nCount].message,str1+1,line_end-str1);
			if(i < 20 )
			{	
			Sys_messg.Format("%s",logitem[nCount].message);
			m_Syslog_query.SetItemText(nCount,3,Sys_messg);
			//m_Syslog_query.SetItemText(nCount,4,(LPCTSTR)logitem[nCount].message);
			}
		}
		else
		{	
			memset(logitem[nCount].message,0x00,56);
			memcpy(logitem[nCount].message,str1+1,55);
			memcpy(logitem[nCount].message+55,"\0",1);

			if(i < 20 )
			{	
			Sys_messg.Format("%s",logitem[nCount].message);
			m_Syslog_query.SetItemText(nCount,3,Sys_messg);
			//m_Syslog_query.SetItemText(nCount,4,(LPCTSTR)logitem[nCount].message);
			}
		}
		nCount ++;
		line_start = line_end;
	}
	current_page = 1;
	delete []pucSysLog;
	

/**********************************************/
	//int totalItem = 100;//测试代码
	//char buf[128] = {0x00};
	//sprintf(buf,"共查询到%d 条记录！",totalItem);
	//syquery_cWnd = GetDlgItem(IDC_SysLogQuery_STATIC);
	//syquery_cWnd->SetWindowTextA(buf);

}

void CSysLogQuery::LogStringGetAndParse()
{
	/********获取系统日志*************/
	
	/*********************************/
}


void CSysLogQuery::OnBnClickedButtonfirstpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);
	if(0 == current_page)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return ;
	}
	if(1 == current_page)
	{
		MessageBox("已经是第一页！","",MB_ICONEXCLAMATION);
		return ;
	}

	current_page=1;
	m_Syslog_query.SetRedraw(FALSE);
	CSysLogQuery::GetStringFromCacheAndShow(current_page);

	m_Syslog_query.SetRedraw(TRUE);
	m_Syslog_query.Invalidate();
	m_Syslog_query.UpdateWindow();

}


void CSysLogQuery::OnBnClickedButtonprepage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);
	int totalItem = 53;
	if(0 == current_page)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return ;
	}
	if(1 == current_page)
	{
		MessageBox("已经是第一页！","",MB_ICONEXCLAMATION);
		return ;
	}

	current_page--;
	m_Syslog_query.SetRedraw(FALSE);
	CSysLogQuery::GetStringFromCacheAndShow(current_page);

	m_Syslog_query.SetRedraw(TRUE);
	m_Syslog_query.Invalidate();
	m_Syslog_query.UpdateWindow();
}


void CSysLogQuery::OnBnClickedButtonnextpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);
	int totalItem = 53;
	if(0 == current_page)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return ;
	}
	if(totalItem/20 == current_page-1|| current_page*20 == totalItem)
	{
		MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
		return ;
	}

	current_page++;
	m_Syslog_query.SetRedraw(FALSE);
	CSysLogQuery::GetStringFromCacheAndShow(current_page);

	m_Syslog_query.SetRedraw(TRUE);
	m_Syslog_query.Invalidate();
	m_Syslog_query.UpdateWindow();
}


void CSysLogQuery::OnBnClickedButtonlastpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);
	int totalItem = 53;
	if(0 == current_page)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return ;
	}
	if(totalItem/20 == current_page-1 || current_page*20 == totalItem)
	{
		MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
		return ;
	}

	if(0 == totalItem%20)
	{
		current_page = totalItem/20;
	}
	else
	{
		current_page = totalItem/20 + 1;
	}
	m_Syslog_query.SetRedraw(FALSE);
	CSysLogQuery::GetStringFromCacheAndShow(current_page);

	m_Syslog_query.SetRedraw(TRUE);
	m_Syslog_query.Invalidate();
	m_Syslog_query.UpdateWindow();
}

void CSysLogQuery::GetStringFromCacheAndShow(unsigned int current_page)
{
	m_Syslog_query.DeleteAllItems();
	int nCount = 0;
	int totalItem = 53;
	for(unsigned int i = (current_page-1)*20;i<((current_page)*20);i++)//syc
	{	
		if( i > (totalItem-1))
		{
			break;
		}
		m_Syslog_query.InsertItem(nCount,0);
		m_Syslog_query.SetItemText(nCount,1,(LPCTSTR)logitem[i].timestmp);
		m_Syslog_query.SetItemText(nCount,2,(LPCTSTR)logitem[i].hostname);
		m_Syslog_query.SetItemText(nCount,3,(LPCTSTR)logitem[i].message);
		nCount++;
	}
}
/******************界面处理********************************/
void CSysLogQuery::OnNMRClickSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_Log));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);

}
void CSysLogQuery::CheckAllItems(BOOL fChecked)
{
	for(int nItem = 0;nItem < ListView_GetItemCount(m_Syslog_query);nItem++)
	{
		ListView_SetCheckState(m_Syslog_query,nItem,fChecked);
	}
}

void CSysLogQuery::SetHeaderCheckbox(void)
{
	BOOL fChecked = TRUE;
	for(int nItem = 0;nItem < ListView_GetItemCount(m_Syslog_query);nItem++)
	{
		if(!ListView_GetCheckState(m_Syslog_query,nItem))
		{
			fChecked = FALSE;
			break;
		}
	}
	
	HWND header = ListView_GetHeader(m_Syslog_query);
	HDITEM hdi = {0};
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header,0,&hdi);
	if (fChecked) 
	{
		hdi.fmt |= HDF_CHECKED;
	} else 
	{
		hdi.fmt &= ~HDF_CHECKED;
	}
	Header_SetItem(header, 0, &hdi);
}

void CSysLogQuery::OnLvnItemchangedSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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
		str2=m_Syslog_query.GetItemText(pNMLV->iItem,1);//复选框选中时，取得其值
		for(int i = 0;i < i_checked_log;i++)
		{
			if(check_log[i] == 0)
				check_log[i] = atoi(str2);
		}
		m_Syslog_query.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//选中则高亮显示
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_log = 0;
		
		str=m_Syslog_query.GetItemText(pNMLV->iItem,1);//复选框取消选中时，取得其值
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
		m_Syslog_query.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//取消选中，则取消高亮显示
	} 
}

void CSysLogQuery::OnHdnItemStateIconClickSyslogqueryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NMHEADER *pnmHeader = (NMHEADER *)pNMHDR;
	if (pnmHeader->pitem->mask & HDI_FORMAT && pnmHeader->pitem->fmt & HDF_CHECKBOX) 
	{
			CheckAllItems(!(pnmHeader->pitem->fmt & HDF_CHECKED));
			SetHeaderCheckbox();
	}
}
/**************************************************/