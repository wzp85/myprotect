// ServiceLogMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ServiceLogMngr.h"
#include "afxdialogex.h"

#include "ServiceLogDetail.h"
#include "ForRecoveryFilePath.h"
#include "ChoseFilePath.h"
#include "MyUtil.h"
#include "ph_km.h"

// CServiceLogMngr 对话框
/*************正常查询**************************/
unsigned int totalItem_SLM=0;//总的记录条数
CString sLogContentCache;
CWnd *stip_cWnd=NULL;
unsigned int page_SLM = 0;//用缓存实现的话，此变量代表第几次查询
unsigned int current_page_SLM = 0;
BOOL  SearchType = FALSE;
/***************条件查询变量初始化**********************/
unsigned int totalItem_SLM_search = 0;
unsigned int page_SLM_search = 0;
CString Logstarttime_SLM ;//缓存查询条件，用来保证翻页过程中条件不变
CString Logendtime_SLM ;
CString Logoptkind_SLM;

IMPLEMENT_DYNAMIC(CServiceLogMngr, CDialogEx)

CServiceLogMngr::CServiceLogMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServiceLogMngr::IDD, pParent)
	//, m_syslogaddress_cstring(_T(""))
	//, m_weburl_cstring(_T(""))
	, m_syslog_cstring(_T(""))
	, m_weburl_cstring(_T(""))
	, m_time_start(_T(""))
	, m_time_end(_T(""))
	, m_opt_kind(_T(""))
	, m_LogSaveCS(_T(""))
{

}

CServiceLogMngr::~CServiceLogMngr()
{
}

void CServiceLogMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_sign, m_check_sign);
	DDX_Control(pDX, IDC_CHECK_verify, m_check_verify);
	DDX_Control(pDX, IDC_CHECK_envelop, m_check_envelop);
	DDX_Control(pDX, IDC_CHECK_openenvelop, m_check_openevvelop);
	DDX_Control(pDX, IDC_CHECK_checkcert, m_check_checkcert);
	DDX_Control(pDX, IDC_LIST_slm, m_slm_listctrl);
	DDX_Control(pDX, IDC_EDIT_SYSLOG_ADDRESS, m_sylogaddres);

	DDX_Text(pDX, IDC_EDIT_WEB_URL,  m_weburl_cstring);
	DDX_Text(pDX, IDC_EDIT_SYSLOG_ADDRESS, m_syslog_cstring);
	DDX_Control(pDX, IDC_EDIT_WEB_URL, m_webUrl);
	DDX_Control(pDX, IDC_CHECK_checkcert2, m_getcertinfo);
	DDX_Control(pDX, IDC_CHECK_openenvelop3, m_open_sign_envelop);
	DDX_Control(pDX, IDC_CHECK_openenvelop2, m_sign_envelop);

	DDX_Text(pDX,IDC_EDIT_TIME_START,m_time_start);
	DDX_Text(pDX,IDC_EDIT_TIME_END,m_time_end);
	//DDX_Text(pDX,IDC_EDIT_OPT_KIND,m_opt_kind);
	DDX_Control(pDX, IDC_COMBO_OPTKIND, m_optkind_CBox);//通过ComBox获取操作类型
	DDX_Control(pDX, IDC_LGSAVECOMBO2, m_LogSaveCCBoX);
}


BEGIN_MESSAGE_MAP(CServiceLogMngr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_xml_ok, &CServiceLogMngr::OnBnClickedButtonxmlok)
	ON_BN_CLICKED(IDC_RADIO_norecord, &CServiceLogMngr::OnBnClickedRadionorecord)
	ON_BN_CLICKED(IDC_RADIO_recordpart, &CServiceLogMngr::OnBnClickedRadiorecordpart)
	ON_BN_CLICKED(IDC_RADIO_recordwithcert, &CServiceLogMngr::OnBnClickedRadiorecordwithcert)
	ON_BN_CLICKED(IDC_RADIO_recordwithoutcert, &CServiceLogMngr::OnBnClickedRadiorecordwithoutcert)
	ON_BN_CLICKED(IDC_RADIO_norecord_sp, &CServiceLogMngr::OnBnClickedRadionorecordsp)
	ON_BN_CLICKED(IDC_RADIO_recordlocal_sp, &CServiceLogMngr::OnBnClickedRadiorecordlocalsp)
	ON_BN_CLICKED(IDC_RADIO_recordsyslog_sp, &CServiceLogMngr::OnBnClickedRadiorecordsyslogsp)
	ON_BN_CLICKED(IDC_RADIO_recordweb_sp, &CServiceLogMngr::OnBnClickedRadiorecordwebsp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_slm, &CServiceLogMngr::OnLvnItemchangedListslm)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CServiceLogMngr::OnHdnItemStateIconClickListslm)
	ON_COMMAND(ID__del_slm, &CServiceLogMngr::OnDelSlm)
	ON_COMMAND(ID__back_slm, &CServiceLogMngr::OnBackSlm)
	ON_COMMAND(ID__recover_slm, &CServiceLogMngr::OnRecoverSlm)
	ON_COMMAND(ID__detail_slm, &CServiceLogMngr::OnDetailSlm)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_slm, &CServiceLogMngr::OnNMRClickListslm)
	ON_BN_CLICKED(IDC_BUTTON_slm_search, &CServiceLogMngr::OnBnClickedButtonslmsearch)
	ON_BN_CLICKED(IDC_BUTTON_slm_firstpage, &CServiceLogMngr::OnBnClickedButtonslmfirstpage)
	ON_BN_CLICKED(IDC_BUTTON_slm_prepage, &CServiceLogMngr::OnBnClickedButtonslmprepage)
	ON_BN_CLICKED(IDC_BUTTON_nextpage, &CServiceLogMngr::OnBnClickedButtonnextpage)
	ON_BN_CLICKED(IDC_BUTTON_lastpage, &CServiceLogMngr::OnBnClickedButtonlastpage)
//	ON_BN_CLICKED(IDC_CHECK_sign, &CServiceLogMngr::OnBnClickedChecksign)
//	ON_BN_CLICKED(IDC_CHECK_verify, &CServiceLogMngr::OnBnClickedCheckverify)
ON_CBN_SELCHANGE(IDC_COMBO_OPTKIND, &CServiceLogMngr::OnCbnSelchangeComboOptkind)
//ON_BN_CLICKED(IDC_CHECK_sign, &CServiceLogMngr::OnBnClickedChecksign)
ON_CBN_SELCHANGE(IDC_LGSAVECOMBO2, &CServiceLogMngr::OnCbnSelchangeLgsavecombo2)
END_MESSAGE_MAP()


// CServiceLogMngr 消息处理程序


BOOL CServiceLogMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	logContentType=0;
	logPolicyType=0;


	CRect rect;   
 
    m_slm_listctrl.GetClientRect(&rect);   
   
    m_slm_listctrl.SetExtendedStyle(m_slm_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   


	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_slm_listctrl.SetImageList(&img_list,LVSIL_SMALL); 


	m_slm_listctrl.InsertColumn(0,NULL,LVCFMT_CENTER,25);        //添加列标题
	m_slm_listctrl.InsertColumn(1, _T("索引"), LVCFMT_CENTER,(rect.Width()-50)/5-50, 1);   
    m_slm_listctrl.InsertColumn(2, _T("入库时间"), LVCFMT_CENTER,(rect.Width()-50)/5, 2); 
	m_slm_listctrl.InsertColumn(3, _T("序列号"), LVCFMT_CENTER,(rect.Width()-50)/5, 3); 
	m_slm_listctrl.InsertColumn(4, _T("是否备份"), LVCFMT_CENTER,(rect.Width()-50)/5+50, 4);  
    m_slm_listctrl.InsertColumn(5, _T("是否正确"), LVCFMT_CENTER, (rect.Width()-50)/5+50, 5);   
    m_slm_listctrl.InsertColumn(6, _T("完整编码"), LVCFMT_CENTER, (rect.Width()-50)/5+50, 6); 
	

	HWND header = ListView_GetHeader(m_slm_listctrl);
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

	isCheckbox_log_slm = FALSE;
	memset(check_log_slm,0,256);
	i_checked_log_slm = 0;

	//page_SLM=1;//第一次查
	//current_page_SLM=0;//当前页数初始化为0
	//page_SLM_search = 1;
	////默认Syslog远程ip及URL输入变灰
	//m_sylogaddres.EnableWindow(FALSE);
	//m_webUrl.EnableWindow(FALSE);
	///****************设置CComBox下拉框为只读防止用户自己输入造成不必要的错误******************************/
	//CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_OPTKIND))->GetWindow(GW_CHILD));	
	//pEdit->SetReadOnly(TRUE);
	//CEdit* pEdit1 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_LGSAVECOMBO2))->GetWindow(GW_CHILD));	
	//pEdit1->SetReadOnly(TRUE);
	//初始化显示搜索类型下拉框
	// m_optkind_CBox.AddString(_T("签名"));
	// m_optkind_CBox.InsertString(1,_T("验签"));
	// //控件列表第一个
	// m_optkind_CBox.InsertString(2,_T("做信封"));
	// m_optkind_CBox.InsertString(3,_T("解信封"));
	// m_optkind_CBox.InsertString(4,_T("做签名信封"));
	// m_optkind_CBox.InsertString(5,_T("解签名信封"));
	// m_optkind_CBox.InsertString(6,_T("验证证书"));
	// m_optkind_CBox.InsertString(7,_T("获取证书信息"));
	//  m_optkind_CBox.InsertString(8,_T("全部"));
	//SetDlgItemText(IDC_COMBO_OPTKIND, _T("全部"));
	////初始化显示日志存储时间
	//m_LogSaveCCBoX.AddString(_T("1个月"));
	//m_LogSaveCCBoX.InsertString(1,_T("2个月"));
	////控件列表第一个
	//m_LogSaveCCBoX.InsertString(2,_T("3个月"));
	//m_LogSaveCCBoX.InsertString(3,_T("4个月"));
	//m_LogSaveCCBoX.InsertString(4,_T("5个月"));
	//m_LogSaveCCBoX.InsertString(5,_T("6个月"));
	//m_LogSaveCCBoX.InsertString(6,_T("7个月"));
	//m_LogSaveCCBoX.InsertString(7,_T("8个月"));
	//m_LogSaveCCBoX.InsertString(8,_T("9个月"));
	//m_LogSaveCCBoX.InsertString(9,_T("10个月"));
	//m_LogSaveCCBoX.InsertString(10,_T("11个月"));
	//m_LogSaveCCBoX.InsertString(11,_T("12个月"));
	//m_LogSaveCCBoX.InsertString(12,_T("12个月"));
	//SetDlgItemText(IDC_LGSAVECOMBO2, _T("6个月"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CServiceLogMngr::OnBnClickedButtonxmlok()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	UpdateData(TRUE);
	MessageBox("即将修改时间戳策略配置文件","",MB_ICONEXCLAMATION);
	/*****************syslogip及url判断********************************/
		unsigned int uiURLLength=0;

	unsigned char pucURL[64]={0x00};
	if(logPolicyType==3)
	{
		if(m_syslog_cstring.IsEmpty())
		{
			MessageBox("远程IP不能为空！","",MB_ICONEXCLAMATION);
			//return ;
		}
		else
		{	memcpy(pucURL,m_syslog_cstring.GetBuffer(),m_syslog_cstring.GetLength());
	     	uiURLLength=m_syslog_cstring.GetLength();
		}
	
	}
	if(logPolicyType==4)
	{
		if(  m_weburl_cstring.IsEmpty())
		{
			MessageBox("URL不能为空！","",MB_ICONEXCLAMATION);
			//return ;
		}
		else
		{	memcpy(pucURL,m_weburl_cstring.GetBuffer(),m_weburl_cstring.GetLength());
	     	uiURLLength=m_weburl_cstring.GetLength();
		}
	}

	
	unsigned int slRequestValue=0;
	CServiceLogMngr::calcuSLR(&slRequestValue);
	


	unsigned int  Logtime = atoi (m_LogSaveCS);
	ret = Sig_ModifyServiceLogXmlFile(phHandle_slm,logContentType,logPolicyType,Logtime,slRequestValue,pucURL,uiURLLength);
	if(0 != ret)
	{
		char mslxferror[100]={0x00};
		retValueParse(ret,mslxferror);
		MessageBox("服务日志策略配置文件修改失败！"+(CString)mslxferror,"",MB_ICONEXCLAMATION);
	}
	else if(0==ret)
	{
		MessageBox("服务日志策略配置文件修改成功,重启服务器后生效！","",MB_ICONEXCLAMATION);
	}
}


void CServiceLogMngr::OnBnClickedRadionorecord()
{
	// TODO: 在此添加控件通知处理程序代码
	logContentType=1;
}


void CServiceLogMngr::OnBnClickedRadiorecordpart()
{
	// TODO: 在此添加控件通知处理程序代码
	logContentType=2;
}


void CServiceLogMngr::OnBnClickedRadiorecordwithcert()
{
	// TODO: 在此添加控件通知处理程序代码
	logContentType=3;
}


void CServiceLogMngr::OnBnClickedRadiorecordwithoutcert()
{
	// TODO: 在此添加控件通知处理程序代码
	logContentType=4;
}


void CServiceLogMngr::OnBnClickedRadionorecordsp()
{
	// TODO: 在此添加控件通知处理程序代码
	logPolicyType=1;
	m_sylogaddres.EnableWindow(FALSE);
	m_webUrl.EnableWindow(FALSE);
}


void CServiceLogMngr::OnBnClickedRadiorecordlocalsp()
{
	// TODO: 在此添加控件通知处理程序代码
	logPolicyType=2;
	m_sylogaddres.EnableWindow(FALSE);
	m_webUrl.EnableWindow(FALSE);
}


void CServiceLogMngr::OnBnClickedRadiorecordsyslogsp()
{
	// TODO: 在此添加控件通知处理程序代码
	logPolicyType=3;
	m_sylogaddres.EnableWindow(TRUE);
	m_webUrl.EnableWindow(FALSE);
}


void CServiceLogMngr::OnBnClickedRadiorecordwebsp()
{
	// TODO: 在此添加控件通知处理程序代码
	logPolicyType=4;
	m_sylogaddres.EnableWindow(FALSE);
	m_webUrl.EnableWindow(TRUE);
}


void CServiceLogMngr::calcuSLR(unsigned int *SLRvalue)
{
	
	unsigned int value[]={1,2,4,8,16,32,64,128};
	CButton *button[]={&m_check_sign,&m_check_verify,&m_check_envelop,&m_check_openevvelop,
		&m_sign_envelop,&m_open_sign_envelop,&m_check_checkcert,&m_getcertinfo};
	unsigned int num[8]={0,0,0,0,0};
	unsigned int sp_value=1;
	for(int i=0;i<8;i++)
	{
		if(1==button[i]->GetCheck())
			sp_value=value[i] | sp_value;
	}
	*SLRvalue=sp_value;
}


void CServiceLogMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_slm_listctrl); nItem++) 
	{
		ListView_SetCheckState(m_slm_listctrl, nItem, fChecked);
	}
}


void CServiceLogMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_slm_listctrl); nItem++) 
	{
		if (!ListView_GetCheckState(m_slm_listctrl, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_slm_listctrl);
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


void CServiceLogMngr::OnLvnItemchangedListslm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_log_slm = TRUE;
		i_checked_log_slm++;
		CString str1,str2,str3;
		nId_row_log_slm = pNMLV->iItem;
		nId_row_mux_log_slm[i_checked_log_slm] = pNMLV->iItem;
		str2=m_slm_listctrl.GetItemText(pNMLV->iItem,1);//复选框选中时，取得其值
		for(int i = 0;i < i_checked_log_slm;i++)
		{
			if(check_log_slm[i] == 0)
				check_log_slm[i] = atoi(str2);
		}
		m_slm_listctrl.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//选中则高亮显示
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_log_slm = 0;
		
		str=m_slm_listctrl.GetItemText(pNMLV->iItem,1);//复选框取消选中时，取得其值
		for(int i = 0;i < i_checked_log_slm;i++)
		{
			if(check_log_slm[i] == atoi(str))
				check_log_slm[i] = 0;
		}
		i_checked_log_slm--;
		if(i_checked_log_slm != 0)
			isCheckbox_log_slm = TRUE;
		else if(i_checked_log_slm == 0)
			isCheckbox_log_slm = FALSE;
		m_slm_listctrl.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//取消选中，则取消高亮显示
	} 
}


void CServiceLogMngr::OnHdnItemStateIconClickListslm(NMHDR *pNMHDR, LRESULT *pResult)
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


void CServiceLogMngr::OnDelSlm()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;

	void * hSessionHandle = phHandle_slm;
	unsigned int uiKeyIndexNum;//1代表单选
	unsigned int puiKeyIndex;
	CString keyIndex_cs;
	CString  SLogTime;
	int nId = 0;
	unsigned int key_index_int[256]={0x00};
	int m_nYear = 0;
	int m_nMonth = 0;
	
	if(!isCheckbox_log_slm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_log_slm)
	{
		if(1 == i_checked_log_slm)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_log_slm[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_log_slm)
		{
			uiKeyIndexNum = i_checked_log_slm;
			memcpy(key_index_int,check_log_slm,i_checked_log_slm*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	//获取服务日志时间项
	SLogTime = m_slm_listctrl.GetItemText(nId,8);
	char *Time = (LPSTR)(LPCTSTR)SLogTime;
	char cYear[16] = {0x00};
	unsigned int inYear = 0;
	char cMonth[16] = {0x00};
	unsigned int inMonth = 0;
	memcpy(cYear,Time,4);
	inYear = atoi(cYear);
	memcpy(cMonth,Time+5,2);
	inMonth = atoi(cMonth);


	nRes = MessageBox("该操作不可逆，销毁后的数据将无法恢复，请确认是否继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
		return;
	if(isSingle)
		ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex,inYear,inMonth);
	else if(!isSingle)
		ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,key_index_int,inYear,inMonth);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("  删除失败"+(CString)outAkd,"提示");
	}
	else
	{
		m_slm_listctrl.SetRedraw(FALSE);

		CServiceLogMngr::ServiceLogStringGetAndParse();

		m_slm_listctrl.SetRedraw(TRUE);
		m_slm_listctrl.Invalidate();
		m_slm_listctrl.UpdateWindow();

		MessageBox("  操作成功！","提示");
		memset(check_log_slm,0,256);
		i_checked_log_slm = 0;

		isCheckbox_log_slm = FALSE;


	}

	////获取客户端系统时间
	//CTime time = CTime::GetCurrentTime();
	//m_nYear = time.GetYear();
	//m_nMonth = time.GetMonth();
	////判断所要删除的日志的时间周期是否在半年以内
	//if(m_nYear == inYear)
	//{
	//	if((m_nMonth - inMonth)> 6)
	//	{
	//		nRes = MessageBox("该操作不可逆，销毁后的数据将无法恢复，请确认是否继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
	//		if(nRes != IDOK)
	//			return;
	//		if(isSingle)
	//			ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	//		else if(!isSingle)
	//			ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,key_index_int);
	//		if(0 != ret)
	//		{
	//			char outAkd[100]={0x00};
	//			retValueParse(ret,outAkd);
	//			MessageBox("  删除失败"+(CString)outAkd,"提示");
	//		}
	//		else
	//		{
	//			m_slm_listctrl.SetRedraw(FALSE);

	//			CServiceLogMngr::ServiceLogStringGetAndParse();

	//			m_slm_listctrl.SetRedraw(TRUE);
	//			m_slm_listctrl.Invalidate();
	//			m_slm_listctrl.UpdateWindow();

	//			MessageBox("  操作成功！","提示");
	//			memset(check_log_slm,0,256);
	//			i_checked_log_slm = 0;

	//			isCheckbox_log_slm = FALSE;
	//		}
	//	}
	//	else{
	//		MessageBox("半年以内的日志，不允许删除！","",MB_ICONEXCLAMATION);
	//		return;
	//	}
	//}

	//if(m_nYear != inYear)
	//{
	//	if((m_nYear - inYear)>=2 )
	//	{
	//		nRes = MessageBox("该操作不可逆，销毁后的数据将无法恢复，请确认是否继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
	//		if(nRes != IDOK)
	//			return;
	//		if(isSingle)
	//			ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	//		else if(!isSingle)
	//			ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,key_index_int);
	//		if(0 != ret)
	//		{
	//			char outAkd[100]={0x00};
	//			retValueParse(ret,outAkd);
	//			MessageBox("  删除失败"+(CString)outAkd,"提示");
	//		}
	//		else
	//		{
	//			m_slm_listctrl.SetRedraw(FALSE);

	//			CServiceLogMngr::ServiceLogStringGetAndParse();

	//			m_slm_listctrl.SetRedraw(TRUE);
	//			m_slm_listctrl.Invalidate();
	//			m_slm_listctrl.UpdateWindow();

	//			MessageBox("  操作成功！","提示");
	//			memset(check_log_slm,0,256);
	//			i_checked_log_slm = 0;

	//			isCheckbox_log_slm = FALSE;
	//		}
	//	}
	//	else if((m_nYear - inYear) == 1)
	//	{
	//		if(((12-inMonth)+m_nMonth) > 6)
	//		{
	//			nRes = MessageBox("该操作不可逆，销毁后的数据将无法恢复，请确认是否继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
	//			if(nRes != IDOK)
	//				return;
	//			if(isSingle)
	//				ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,&puiKeyIndex);
	//			else if(!isSingle)
	//				ret = Sig_ServiceLogDel(hSessionHandle,uiKeyIndexNum,key_index_int);
	//			if(0 != ret)
	//			{
	//				char outAkd[100]={0x00};
	//				retValueParse(ret,outAkd);
	//				MessageBox("  删除失败"+(CString)outAkd,"提示");
	//			}
	//			else
	//			{
	//				m_slm_listctrl.SetRedraw(FALSE);

	//				CServiceLogMngr::ServiceLogStringGetAndParse();

	//				m_slm_listctrl.SetRedraw(TRUE);
	//				m_slm_listctrl.Invalidate();
	//				m_slm_listctrl.UpdateWindow();

	//				MessageBox("  操作成功！","提示");
	//				memset(check_log_slm,0,256);
	//				i_checked_log_slm = 0;

	//				isCheckbox_log_slm = FALSE;
	//			}

	//		}
	//	}
	//	else{
	//		MessageBox("半年以内的日志，不允许删除！","",MB_ICONEXCLAMATION);
	//		return;
	//	}
	//}
	
}


void CServiceLogMngr::OnBackSlm()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;
	int nId = nId_row_log_slm;

	void * hSessionHandle = phHandle_slm;
	unsigned int uiKeyIndexNum;//1代表单选
	unsigned int puiKeyIndex;
	CString appName_i;//ip

	unsigned int key_index_int[256]={0};

	if(!isCheckbox_log_slm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_log_slm)
	{
		if(1 == i_checked_log_slm)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_log_slm[0];
			isSingle = TRUE;
			appName_i=m_slm_listctrl.GetItemText(nId,2);//单选取列表的ip用于服务端查询此条记录
		}
		else if(1 < i_checked_log_slm)
		{
			uiKeyIndexNum = i_checked_log_slm;
			memcpy(key_index_int,check_log_slm,i_checked_log_slm*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	if(isSingle)
	{
		CChoseFilePath choseFilePath(NULL,appName_i,NULL,uiKeyIndexNum,&puiKeyIndex,SIG_SERVICELOGBAK,phHandle_slm);
		choseFilePath.DoModal();
	}
	else if(!isSingle)
	{
		CChoseFilePath choseFilePath(NULL,NULL,NULL,uiKeyIndexNum,key_index_int,SIG_SERVICELOGBAK,phHandle_slm);
		choseFilePath.DoModal();
	}

	m_slm_listctrl.SetRedraw(FALSE);

	CServiceLogMngr::ServiceLogStringGetAndParse();

	m_slm_listctrl.SetRedraw(TRUE);
	m_slm_listctrl.Invalidate();
	m_slm_listctrl.UpdateWindow();

	MessageBox("  操作成功！","提示");
	memset(check_log_slm,0,256);
	i_checked_log_slm = 0;

	isCheckbox_log_slm = FALSE;
}


void CServiceLogMngr::OnRecoverSlm()
{
	// TODO: 在此添加命令处理程序代码
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

	MessageBox((CString)data_read);
	char ch_last=data_read[data_read_len-1];
	if(0x38!=ch_last)
	{
		MessageBox("您选择的不是服务日志备份文件，请选择服务日志的备份文件进行恢复！","备份文件类型错误",MB_ICONEXCLAMATION);
		delete data_read;
		return;
	}
	ret=Sig_ServiceLogRecovery(phHandle_slm,data_read_len,data_read);
	if(0!=ret)
	{
		char sccrError[100]={0x00};
		retValueParse(ret,sccrError);
		MessageBox("CA证书恢复失败"+(CString)sccrError,"",MB_ICONEXCLAMATION);
		return;
	}
	MessageBox("操作成功","",MB_ICONEXCLAMATION);

	m_slm_listctrl.SetRedraw(FALSE);

	CServiceLogMngr::ServiceLogStringGetAndParse();

	m_slm_listctrl.SetRedraw(TRUE);
	m_slm_listctrl.Invalidate();
	m_slm_listctrl.UpdateWindow();

	MessageBox("  操作成功！","提示");

	memset(check_log_slm,0,256);
	i_checked_log_slm = 0;

	isCheckbox_log_slm = FALSE;

	delete data_read;
}


void CServiceLogMngr::OnDetailSlm()
{
	// TODO: 在此添加命令处理程序代码
	int ret=0;
	int nId;
	CString logIndex;
	char index[32]={0x00};
	if(!isCheckbox_log_slm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_log_slm)
	{
		if(i_checked_log_slm > 1)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_log_slm;
		}
	}
	//MessageBox((LPSTR)(LPCTSTR)sLogContentCache,(LPSTR)(LPCTSTR)sLogContentCache,MB_ICONEXCLAMATION);
	logIndex=m_slm_listctrl.GetItemText(nId,1);
	sprintf(index,"\n%s|",(LPSTR)(LPCTSTR)logIndex);
	//MessageBox(index,index,MB_ICONEXCLAMATION);
	char *str=strstr((LPSTR)(LPCTSTR)sLogContentCache,index);//107|
	if(str==NULL)
	{
		MessageBox("没有找到对应记录！","",MB_ICONEXCLAMATION);
		return;
	}

	char *start,*end;
	char ipBuf[32]={0x00};
	char operTypeBuf[32]={0x00};
	char resultFlagBuf[32]={0x00};
	char userIDBuf[32]={0x00};
	//char certBuf[2048]={0x00};//不确定长度
	char certSNBuf[64]={0x00};
	char certNameBuf[512]={0x00};
	//char plainDataBuf[2048]={0x00};//
	//char cipherDataBuf[2048]={0x00};//
	char hashAlgoBuf[32]={0x00};
	char symmAlgoBuf[32]={0x00};
	char logTimeBuf[32]={0x00};
	/***************防止堆栈溢出*************************/
	Datil_DATA certBuf = {0,NULL};
	Datil_DATA plainDataBuf = {0,NULL};
	Datil_DATA cipherDataBuf = {0,NULL};
	/*****************************************************/
	start=strstr(str,"|");//|ip
	end=start+strlen("|");

	start=strstr(end,"|");//-------ip
	memcpy(ipBuf,end,start-end);
	end=start+strlen("|");

	start=strstr(end,"|");//--------操作类型
	memcpy(operTypeBuf,end,start-end);
	end=start+strlen("|");

	start=strstr(end,"|");//-------------操作结果
	memcpy(resultFlagBuf,end,start-end);
	end=start+strlen("|");

	start=strstr(end,"|");//---------用户id
	memcpy(userIDBuf,end,start-end);
	end=start+strlen("|");

	start=strstr(end,"|");//-----------证书内容
	certBuf.size = start-end;
	certBuf.value = new char[certBuf.size+1];
	//certBuf.value = new unsigned char[certBuf.size];
	memset(certBuf.value,0x00,certBuf.size+1);
	if((start-end) > 1)
	{
		memcpy(certBuf.value,end,start-end);
		//certBuf.value[certBuf.size+1] = '\0';
	}
	end=start+strlen("|");

	start=strstr(end,"|");//-------------证书序列号
	memcpy(certSNBuf,end,start-end);
	end=start+strlen("|");
	char certSN[64]={0x00};
	memcpy(certSN,certSNBuf,strlen(certSNBuf));

	

	start=strstr(end,"|");//-------------证书名
	memcpy(certNameBuf,end,start-end);
	end=start+strlen("|");
	char certName[512]={0x00};
	memcpy(certName,certNameBuf,strlen(certNameBuf));

	start=strstr(end,"|");//-------------原文
	plainDataBuf.size = start-end;
	plainDataBuf.value = new char[plainDataBuf.size+1 ];
	//plainDataBuf.value =new unsigned char[plainDataBuf.size ];
	memset(plainDataBuf.value,0x00,plainDataBuf.size+1);
	if((start-end) > 1)
	{
		memcpy(plainDataBuf.value,end,start-end);
	}
	end=start+strlen("|");
	//char plainData[2048]={0x00};
	//memcpy(plainData,plainDataBuf,strlen(plainDataBuf));//证书原文


	start=strstr(end,"|");//-------------密文
	cipherDataBuf.size = start-end;
	cipherDataBuf.value = new char[cipherDataBuf.size +1];
	//cipherDataBuf.value = new unsigned char[cipherDataBuf.size ];
	memset(cipherDataBuf.value,0x00,cipherDataBuf.size+1);
	if((start-end) > 1)
	{
		memcpy(cipherDataBuf.value,end,start-end);
	}
	end=start+strlen("|");
	//char cipherData[2048]={0x00};
	//memcpy(cipherData,cipherDataBuf,strlen(cipherDataBuf));//密文


	start=strstr(end,"|");//-------------哈希算法
	memcpy(hashAlgoBuf,end,start-end);
	end=start+strlen("|");
	char hashAlgo[32]={0x00};
	
	memcpy(hashAlgo,hashAlgoBuf,strlen(hashAlgoBuf));
	

	start=strstr(end,"|");//-------------
	memcpy(symmAlgoBuf,end,start-end);
	end=start+strlen("|");
	char symmAlgo[32]={0x00};
	memcpy(symmAlgo,symmAlgoBuf,strlen(symmAlgoBuf));


	start=strstr(end,"|");//-------------登录时间
	memcpy(logTimeBuf,end,start-end);
	end=start+strlen("|");

	CServiceLogDetail slDetail(phHandle_slm,_ttoi(logIndex),certName,certSN,hashAlgo,symmAlgo,plainDataBuf.value,cipherDataBuf.value,certBuf.value);
	slDetail.DoModal();
	/************解决多选报错问题即每次显示日志详情后刷新重新显示*****************/
	delete plainDataBuf.value;
	delete cipherDataBuf.value;
	delete certBuf.value;
	m_slm_listctrl.SetRedraw(FALSE);
	if(FALSE == SearchType)
	{
		CServiceLogMngr::ServiceLogStringGetAndParse();
	}

	else if (TRUE == SearchType)
	{
		CServiceLogMngr::ServiceLogStringGetAndParse_search( Logstarttime_SLM,Logendtime_SLM,Logoptkind_SLM);
	}

	m_slm_listctrl.SetRedraw(TRUE);
	m_slm_listctrl.Invalidate();
	m_slm_listctrl.UpdateWindow();
	//CServiceLogMngr::ServiceLogStringGetAndParse();
	memset(check_log_slm,0,256);
	i_checked_log_slm = 0;
	isCheckbox_log_slm = FALSE;

}


void CServiceLogMngr::OnNMRClickListslm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_slm));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}


//点击了“查询”按钮
void CServiceLogMngr::OnBnClickedButtonslmsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Logstarttime_SLM = m_time_start;
	Logendtime_SLM = m_time_end;
	Logoptkind_SLM = m_opt_kind;
	//点击查询就默认从第一页开始查找
	page_SLM=1;//第一次查
	page_SLM_search = 1;
	/*******************正常查询*************************/
	if("9" == m_opt_kind)
	{
		m_time_start = "";
		m_time_end = "";
	}
	if((m_time_start.IsEmpty()&&m_time_end.IsEmpty())&&(m_opt_kind.IsEmpty() || m_opt_kind == "9"))
	{
		m_slm_listctrl.SetRedraw(FALSE);
		CServiceLogMngr::ServiceLogStringGetAndParse();
		/*SetDlgItemText(IDC_EDIT_TIME_START,""); 
		SetDlgItemText(IDC_EDIT_TIME_END,""); */
		m_slm_listctrl.SetRedraw(TRUE);
		m_slm_listctrl.Invalidate();
		m_slm_listctrl.UpdateWindow();
		page_SLM++;//表示按一次查询按钮，查询次数加1
		if((totalItem_SLM<100) && (0 != totalItem_SLM) )
		{
			page_SLM--;
			MessageBox("日志查询结束！","",MB_ICONEXCLAMATION);
			return;
		}
		if((2 == page_SLM) && ( 0 == totalItem_SLM))
		{
			MessageBox("数据库没有数据！","",MB_ICONEXCLAMATION);
			return;
		}
	}
	
			
	/*******************条件搜索**************************/
	else{//输入什么条件就对什么条件搜索，CString没值就为空传入

		//判断条件是否填写完全
		if(m_time_start.IsEmpty()||m_time_end.IsEmpty()||m_opt_kind.IsEmpty())
		{
			MessageBox("请完整输入始末时间和操作类型！","",MB_ICONEXCLAMATION);
			return ;
		}	
		/*************************判断输入日期格式是否正确********************************/
		char *start =  (LPSTR)(LPCTSTR)Logstarttime_SLM;
		char *end = (LPSTR)(LPCTSTR)Logendtime_SLM;
		char *start1 = start + 4;
		char *start2 = start1 + 3;
		char * end1 = end + 4;
		char * end2 = end1 + 3;
		if((!m_time_start.IsEmpty())||(!m_time_end.IsEmpty()))
		{
			if((start1[0] != '-')||(start2[0] != '-')||(end1[0] != '-')||(end2[0] != '-'))
			{
				MessageBox("请保证日期格式为yyyy-mm-dd！","",MB_ICONEXCLAMATION);
				return ;
			}
		}
		m_slm_listctrl.SetRedraw(FALSE);

	

		CServiceLogMngr::ServiceLogStringGetAndParse_search(Logstarttime_SLM,Logendtime_SLM,Logoptkind_SLM);
		m_slm_listctrl.SetRedraw(TRUE);
		m_slm_listctrl.Invalidate();
		m_slm_listctrl.UpdateWindow();
		page_SLM_search++;//表示按一次查询按钮，查询次数加1
		if((totalItem_SLM_search<100) && (0 != totalItem_SLM_search))
		{
			page_SLM_search--;
			MessageBox("日志搜索结束！","",MB_ICONEXCLAMATION);
			return;
		}
		if((2 == page_SLM_search) && (0 == totalItem_SLM_search))
		{
			MessageBox("抱歉数据库没有您要查找的数据，请核对您的查询条件！","",MB_ICONEXCLAMATION);
			return;
		}
		
	}
}

void CServiceLogMngr::ServiceLogStringGetAndParse()
{
	unsigned char *logcontent=NULL;
	unsigned int logcontentlength=0;
	SearchType = FALSE;

	totalItem_SLM=0;
	
	for(int i=0;i<100;i++)
	{
		memset(&slogitem[i],0x00,sizeof(SLOGITEM));
	}

	m_slm_listctrl.DeleteAllItems();

	int ret=0;
	ret=Sig_GetServiceLog(phHandle_slm,page_SLM,&totalItem_SLM,logcontent,&logcontentlength);
	if(0 != ret)
	{
		char sglerr[100]={0x00};
		retValueParse(ret,sglerr);
		MessageBox("获取日志记录长度失败"+(CString)sglerr,"失败",MB_ICONEXCLAMATION);
		return ;
	}
	logcontent=new unsigned char[logcontentlength+1];
	memset(logcontent,0x00,logcontentlength);
	ret=Sig_GetServiceLog(phHandle_slm,page_SLM,&totalItem_SLM,logcontent,&logcontentlength);
	if(0 != ret)
	{
		char sglerror[100]={0x00};
		retValueParse(ret,sglerror);
		MessageBox("获取日志失败"+(CString)sglerror,"失败",MB_ICONEXCLAMATION);
		delete []logcontent;
		return ;
	}

	if(logcontentlength==0)
	{
	  return ;
    }
	sLogContentCache.Format("%s",logcontent);
	
		//MessageBox((CString)logcontent,(CString)logcontent,MB_ICONEXCLAMATION);
	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\logcontent_1.txt",logcontent,logcontentlength);
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_2.txt",pubkey,sizeof(RSAPUBLICKEYBLOB));

	char *start,*end,*str,*str_time;
	CString ip_cs,opt_kind_cs,opt_result_cs,oper_ID_cs,opt_time_cs,index_cs,opt_certSN_cs,opt_certDN_cs;

	str_time=strstr((char*)logcontent,"logSignV");
	str=str_time+sizeof("logSignV");
	int nCount=0;

	for(int i=0;i<100;i++)
	{
		if(0==*str)
			 break;
		start=strstr(str,"|");
		if(start==NULL)
			break;
		memcpy(slogitem[i].index,str,start-str);


		if(i<100)
		{
			m_slm_listctrl.InsertItem(nCount,0);
			index_cs.Format("%s",slogitem[i].index);
			//m_slm_listctrl.SetItemText(nCount,1,(LPCTSTR)slogitem[i].index);
			m_slm_listctrl.SetItemText(nCount,1,index_cs);
		}
		end=start+strlen("|");

		start=strstr(end,"|");
		memcpy(slogitem[i].ip,end,start-end);

		if(i<100)
		{
			//ip_cs.Format("%s",slogitem[i].ip);
			//m_slm_listctrl.SetItemText(nCount,2,ip_cs);
			m_slm_listctrl.SetItemText(nCount,2,(LPCTSTR)slogitem[i].ip);
		}
		
		end=start+strlen("|");

		start=strstr(end,"|");
		if(start==NULL)
		{
			MessageBox("start为空!");
			break;
		}
		memcpy(slogitem[i].opt_kind,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{
			//opt_kind_cs.Format("%s",slogitem[i].opt_kind);


			if(strstr((char*)slogitem[i].opt_kind,"1")!=NULL)
				 opt_kind_cs.Format("%s","签名");
			else if (strstr((char*)slogitem[i].opt_kind,"2")!=NULL)
				 opt_kind_cs.Format("%s","验签");
			else if (strstr((char*)slogitem[i].opt_kind,"3")!=NULL)
				 opt_kind_cs.Format("%s","做数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"4")!=NULL)
				 opt_kind_cs.Format("%s","解数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"5")!=NULL)
				 opt_kind_cs.Format("%s","做签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"6")!=NULL)
				 opt_kind_cs.Format("%s","解签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"7")!=NULL)
				 opt_kind_cs.Format("%s","验证证书有效性");
			else if (strstr((char*)slogitem[i].opt_kind,"8")!=NULL)
				 opt_kind_cs.Format("%s","获取证书信息");
			
			m_slm_listctrl.SetItemText(nCount,6,opt_kind_cs);
		}
		
		end=start+strlen("|");

		start=strstr(end,"|");

		memcpy(slogitem[i].opt_result,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{  
			if(0 == strcmp((char*)slogitem[i].opt_result,"0"))
			{
				 opt_result_cs.Format("%s","成功");
			}
				
			else
			{
				opt_result_cs.Format("%s","失败");

			}

			//opt_result_cs.Format("%s",slogitem[i].opt_result);
			m_slm_listctrl.SetItemText(nCount,7,opt_result_cs);
		}
			end=start+strlen("|");

		start=strstr(end,"|");

		//索引号
		memcpy(slogitem[i].oper_ID,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{  
			oper_ID_cs.Format("%s",slogitem[i].oper_ID);
			m_slm_listctrl.SetItemText(nCount,3,oper_ID_cs);
		}
		end=start+strlen("|");

		start=strstr(end,"|");
		//证书内容
		end=start+strlen("|");

		start=strstr(end,"|");//证书序列号
		memcpy(slogitem[i].cert_SN,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{ 
			
			opt_certSN_cs.Format("%s",slogitem[i].cert_SN);
			m_slm_listctrl.SetItemText(nCount,4,opt_certSN_cs);
		}
		end=start+strlen("|");
		//if(start-end>0)
		//{
		//	memcpy(slogitem[i].cert_SN,end,start-end);//------放到结构体缓存数组
		//	MessageBox(opt_certSN_cs,opt_certSN_cs,MB_ICONEXCLAMATION);
		//	if(i<20)
		//	{  


		//		opt_certSN_cs.Format("%s",slogitem[i].cert_SN);
		//		//MessageBox(opt_certSN_cs,opt_certSN_cs,MB_ICONEXCLAMATION);
		//		m_slm_listctrl.SetItemText(nCount,3,opt_certSN_cs);
		//	}
		//}	
		start=strstr(end,"|");//证书名字
		memcpy(slogitem[i].cert_DN,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{ 
			
			opt_certDN_cs.Format("%s",slogitem[i].cert_DN);
			m_slm_listctrl.SetItemText(nCount,5,opt_certDN_cs);
		}


		end=start+strlen("|");
		//if(start-end>0)
		//{
		//	memcpy(slogitem[i].cert_DN,end,start-end);//------放到结构体缓存数组
		//	if(i<20)
		//	{  
		//

		//		opt_certDN_cs.Format("%s",slogitem[i].cert_DN);
		//		m_slm_listctrl.SetItemText(nCount,4,opt_certDN_cs);
		//	}
		//		//MessageBox(opt_certDN_cs,opt_certDN_cs,MB_ICONEXCLAMATION);
		//}
		start=strstr(end,"|");//原文
		end=start+strlen("|");

		start=strstr(end,"|");//密文
		end=start+strlen("|");

		start=strstr(end,"|");//哈希标识
		end=start+strlen("|");

		start=strstr(end,"|");//对称算法标识
		end=start+strlen("|");

		start=strstr(end,"|");
		memcpy(slogitem[i].opt_time,end,19);//------放到结构体缓存数组
		if(i<100)
		{
			
			opt_time_cs.Format("%s",slogitem[i].opt_time);
			m_slm_listctrl.SetItemText(nCount,8,opt_time_cs);
		}
		//MessageBox(opt_time_cs,opt_time_cs,MB_ICONEXCLAMATION);
		end=start+strlen("|");
		start=strstr(end,"\n");
		end=start+strlen("\n");

//		end=start+20;

		nCount++;
		//str=end+19;
		str=end;

	}

	delete []logcontent;
}

void CServiceLogMngr::ServiceLogShowFromCache(unsigned int current_page_SLM)
{
	m_slm_listctrl.DeleteAllItems();

	int nCount=0;
	CString opt_kind_cs,opt_result_cs;
	for(unsigned int i = (current_page_SLM-1)*20;i<((current_page_SLM)*20);i++)//syc
	{
		if(i>(totalItem_SLM-1))
			break;
		m_slm_listctrl.InsertItem(nCount,0);
		m_slm_listctrl.SetItemText(nCount,1,(LPCTSTR)slogitem[i].index);
		m_slm_listctrl.SetItemText(nCount,2,(LPCTSTR)slogitem[i].ip);
		m_slm_listctrl.SetItemText(nCount,3,(LPCTSTR)slogitem[i].oper_ID);
		m_slm_listctrl.SetItemText(nCount,4,(LPCTSTR)slogitem[i].cert_SN);
		m_slm_listctrl.SetItemText(nCount,5,(LPCTSTR)slogitem[i].cert_DN);
		m_slm_listctrl.SetItemText(nCount,8,(LPCTSTR)slogitem[i].opt_time);
		//m_slm_listctrl.SetItemText(nCount,6,(LPCTSTR)slogitem[i].opt_kind);
		//m_slm_listctrl.SetItemText(nCount,7,(LPCTSTR)slogitem[i].opt_result);
	 if(strstr((char*)slogitem[i].opt_kind,"1")!=NULL)
				 opt_kind_cs.Format("%s","签名");
			else if (strstr((char*)slogitem[i].opt_kind,"2")!=NULL)
				 opt_kind_cs.Format("%s","验签");
			else if (strstr((char*)slogitem[i].opt_kind,"3")!=NULL)
				 opt_kind_cs.Format("%s","做数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"4")!=NULL)
				 opt_kind_cs.Format("%s","解数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"5")!=NULL)
				 opt_kind_cs.Format("%s","做签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"6")!=NULL)
				 opt_kind_cs.Format("%s","解签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"7")!=NULL)
				 opt_kind_cs.Format("%s","验证证书有效性");
			else if (strstr((char*)slogitem[i].opt_kind,"8")!=NULL)
				 opt_kind_cs.Format("%s","获取证书信息");
			
			m_slm_listctrl.SetItemText(nCount,6,opt_kind_cs);		
			if(0 == strcmp((char*)slogitem[i].opt_result,"0"))
			{
				 opt_result_cs.Format("%s","成功");
			}
				
			else
			{
				opt_result_cs.Format("%s","失败");

			}
				
			m_slm_listctrl.SetItemText(nCount,7,opt_result_cs);
			
		nCount++;
	}
}


void CServiceLogMngr::OnBnClickedButtonslmfirstpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	UpdateData(TRUE);
	
	if(current_page_SLM==0)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return;
	}
	if(current_page_SLM==1)
	{
		MessageBox("已经是第一页！","",MB_ICONEXCLAMATION);
		return;
	}
	
	current_page_SLM=1;
	m_slm_listctrl.SetRedraw(FALSE);

	CServiceLogMngr::ServiceLogShowFromCache(current_page_SLM);

	m_slm_listctrl.SetRedraw(TRUE);
    m_slm_listctrl.Invalidate();
    m_slm_listctrl.UpdateWindow();
}


void CServiceLogMngr::OnBnClickedButtonslmprepage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	UpdateData(TRUE);
	if("9" == m_opt_kind)
	{
		m_time_start = "";
		m_time_end = "";
	}
	/**************************没有搜索条件正常搜索***************************/
	if(m_time_start.IsEmpty()&&m_time_end.IsEmpty()&&(m_opt_kind.IsEmpty() || m_opt_kind == "9"))
	{
		if(page_SLM==0)
		{
			MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
			return;
		}
		if(page_SLM==1)
		{
			MessageBox("已经是第一页！","",MB_ICONEXCLAMATION);
			return;
		}
	
		page_SLM--;
		m_slm_listctrl.SetRedraw(FALSE);
		CServiceLogMngr::ServiceLogStringGetAndParse();
		m_slm_listctrl.SetRedraw(TRUE);
		m_slm_listctrl.Invalidate();
		m_slm_listctrl.UpdateWindow();
	}
	/***************************有搜索条件，非正常搜索******************************/
	else{
			if((Logstarttime_SLM != m_time_start)||(Logendtime_SLM != m_time_end)||(Logoptkind_SLM != m_opt_kind))//翻页前后条件不一致提示
			{
				MessageBox("请保证搜索条件翻页前后一致！","",MB_ICONEXCLAMATION);
				return;
			}
			else{
				if(page_SLM_search==0)
				{
					MessageBox("请点击查询搜索！","",MB_ICONEXCLAMATION);
					return;
				}
				if(page_SLM_search==1)
				{
					MessageBox("已经是第一页！","",MB_ICONEXCLAMATION);
					return;
				}
				page_SLM_search --;
				m_slm_listctrl.SetRedraw(FALSE);
				CServiceLogMngr::ServiceLogStringGetAndParse_search(Logstarttime_SLM,Logendtime_SLM,Logoptkind_SLM);
				m_slm_listctrl.SetRedraw(TRUE);
				m_slm_listctrl.Invalidate();
				m_slm_listctrl.UpdateWindow();
				
			}
		
	}
}


void CServiceLogMngr::OnBnClickedButtonnextpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	UpdateData(TRUE);
	//9为全部选择即正常查询
	if("9" == m_opt_kind)
	{
		m_time_start = "";
		m_time_end = "";
	}
	/**************************没有搜索条件正常搜索***************************/
	if(m_time_start.IsEmpty()&&m_time_end.IsEmpty()&&(m_opt_kind.IsEmpty() || m_opt_kind == "9"))
	{
		if(page_SLM==0)
		{
			MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
			return;
		}
		if(totalItem_SLM < 100)
		{
			MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
			return;
		}

		page_SLM++;

		m_slm_listctrl.SetRedraw(FALSE);
		CServiceLogMngr::ServiceLogStringGetAndParse();
		m_slm_listctrl.SetRedraw(TRUE);
		m_slm_listctrl.Invalidate();
		m_slm_listctrl.UpdateWindow();

		if(totalItem_SLM < 100)
		{
			MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
			return;
		}
	}
	/***************************有搜索条件，非正常搜索******************************/
	else{
			if((Logstarttime_SLM != m_time_start)||(Logendtime_SLM != m_time_end)||(Logoptkind_SLM != m_opt_kind))//翻页前后条件不一致提示
			{
				MessageBox("请保证搜索条件翻页前后一致！","",MB_ICONEXCLAMATION);
				return;
			}
			else{
				if(page_SLM_search==0)
				{
					MessageBox("请点击查询搜索！","",MB_ICONEXCLAMATION);
					return;
				}
				if(totalItem_SLM_search < 100)
				{
					MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
					return;
				}
				page_SLM_search ++;
				m_slm_listctrl.SetRedraw(FALSE);
				CServiceLogMngr::ServiceLogStringGetAndParse_search(Logstarttime_SLM,Logendtime_SLM,Logoptkind_SLM);
				m_slm_listctrl.SetRedraw(TRUE);
				m_slm_listctrl.Invalidate();
				m_slm_listctrl.UpdateWindow();
				if(totalItem_SLM_search < 100)
				{
					MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
					return;
				}
			}
		
	}
}


void CServiceLogMngr::OnBnClickedButtonlastpage()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;

	if(current_page_SLM==0)
	{
		MessageBox("请点击查询开始！","",MB_ICONEXCLAMATION);
		return;
	}
	if(current_page_SLM-1==totalItem_SLM/20 || current_page_SLM*20==totalItem_SLM)
	{
		MessageBox("已经是最后一页！","",MB_ICONEXCLAMATION);
		return;
	}
	
	if(totalItem_SLM%20!=0)
		current_page_SLM=(totalItem_SLM/20)+1;
	else
		current_page_SLM=totalItem_SLM/20;

	m_slm_listctrl.SetRedraw(FALSE);

	CServiceLogMngr::ServiceLogShowFromCache(current_page_SLM);

	m_slm_listctrl.SetRedraw(TRUE);
    m_slm_listctrl.Invalidate();
    m_slm_listctrl.UpdateWindow();
}

void CServiceLogMngr::ServiceLogStringGetAndParse_search(CString Logstarttime_SLM,CString Logendtime_SLM,CString Logoptkind_SLM)
{
	unsigned char *logcontent=NULL;
	unsigned int logcontentlength=0;

	SearchType = TRUE;
	unsigned int uiStartTimeLength;
	unsigned char pucStartTime[32]={0x00};
	memcpy(pucStartTime,Logstarttime_SLM.GetBuffer(),Logstarttime_SLM.GetLength());
	uiStartTimeLength = Logstarttime_SLM.GetLength();

	unsigned int uiStartEndLength;
	unsigned char pucStartEnd[32]={0x00};
	memcpy(pucStartEnd,Logendtime_SLM.GetBuffer(),Logendtime_SLM.GetLength());
	uiStartEndLength = Logendtime_SLM.GetLength();

	
	/*unsigned int uiLogopkindLength;
	unsigned char pucLogopkind[32]={0x00};
	memcpy(pucLogopkind,Logoptkind_SLM.GetBuffer(),Logoptkind_SLM.GetLength());
	uiLogopkindLength = Logoptkind_SLM.GetLength();*/
	unsigned int uilogopKind = atoi(Logoptkind_SLM);
	totalItem_SLM_search=0;

	for(int i=0;i<100;i++)
	{
		memset(&slogitem[i],0x00,sizeof(SLOGITEM));
	}

	m_slm_listctrl.DeleteAllItems();

	int ret=0;
	/*****************下面调用服务端接口通过条件进行搜索，给我搜索的日志内容及条数，一次一百条***********************/
	ret=Sig_GetServiceLogSearch(phHandle_slm,page_SLM_search/*页数*//*条数*还包括三个搜索条件*/, 
		uiStartTimeLength,pucStartTime,uiStartEndLength,pucStartEnd,/*uiLogopkindLength,pucLogopkind*/uilogopKind
		,&totalItem_SLM_search,logcontent,&logcontentlength);
	if(0 != ret)
	{
		char sglerr[100]={0x00};
		retValueParse(ret,sglerr);
		MessageBox("搜索日志记录长度失败"+(CString)sglerr,"失败",MB_ICONEXCLAMATION);
		return ;
	}
	
	logcontent=new unsigned char[logcontentlength+1];
	memset(logcontent,0x00,logcontentlength);
	ret=Sig_GetServiceLogSearch(phHandle_slm,page_SLM_search/*页数*//*条数*还包括三个搜索条件*/, 
		uiStartTimeLength,pucStartTime,uiStartEndLength,pucStartEnd,/*uiLogopkindLength,pucLogopkind*/uilogopKind
		,&totalItem_SLM_search,logcontent,&logcontentlength);
	if(0 != ret)
	{
		char sglerror[100]={0x00};
		retValueParse(ret,sglerror);
		MessageBox("搜索日志失败"+(CString)sglerror,"失败",MB_ICONEXCLAMATION);
		delete []logcontent;
		return ;
	}
	
	/***************调用服务端接口***************************************************************************/
	if(logcontentlength==0)
	{
	  return ;
    }
	sLogContentCache.Format("%s",logcontent);
	
	//	MessageBox((CString)logcontent,(CString)logcontent,MB_ICONEXCLAMATION);
	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\logcontent_1.txt",logcontent,logcontentlength);
//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_2.txt",pubkey,sizeof(RSAPUBLICKEYBLOB));


	char *start,*end,*str,*str_time;
	CString ip_cs,opt_kind_cs,opt_result_cs,oper_ID_cs,opt_time_cs,index_cs,opt_certSN_cs,opt_certDN_cs;

	str_time=strstr((char*)logcontent,"logSignV");
	str=str_time+sizeof("logSignV");
	int nCount=0;

	for(int i=0;i<100;i++)
	{
		if(0==*str)
			break;
		start=strstr(str,"|");
		if(start==NULL)
			break;
		memcpy(slogitem[i].index,str,start-str);


		if(i<100)
		{
			m_slm_listctrl.InsertItem(nCount,0);
			index_cs.Format("%s",slogitem[i].index);
			//m_slm_listctrl.SetItemText(nCount,1,(LPCTSTR)slogitem[i].index);
			m_slm_listctrl.SetItemText(nCount,1,index_cs);
		}
		end=start+strlen("|");

		start=strstr(end,"|");
		memcpy(slogitem[i].ip,end,start-end);

		if(i<100)
		{
			//ip_cs.Format("%s",slogitem[i].ip);
			//m_slm_listctrl.SetItemText(nCount,2,ip_cs);
			m_slm_listctrl.SetItemText(nCount,2,(LPCTSTR)slogitem[i].ip);
		}

		end=start+strlen("|");

		start=strstr(end,"|");
		if(start==NULL)
		{
			MessageBox("start为空!");
			break;
		}
		memcpy(slogitem[i].opt_kind,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{
			//opt_kind_cs.Format("%s",slogitem[i].opt_kind);


			if(strstr((char*)slogitem[i].opt_kind,"1")!=NULL)
				opt_kind_cs.Format("%s","签名");
			else if (strstr((char*)slogitem[i].opt_kind,"2")!=NULL)
				opt_kind_cs.Format("%s","验签");
			else if (strstr((char*)slogitem[i].opt_kind,"3")!=NULL)
				opt_kind_cs.Format("%s","做数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"4")!=NULL)
				opt_kind_cs.Format("%s","解数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"5")!=NULL)
				opt_kind_cs.Format("%s","做签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"6")!=NULL)
				opt_kind_cs.Format("%s","解签名数字信封");
			else if (strstr((char*)slogitem[i].opt_kind,"7")!=NULL)
				opt_kind_cs.Format("%s","验证证书有效性");
			else if (strstr((char*)slogitem[i].opt_kind,"8")!=NULL)
				opt_kind_cs.Format("%s","获取证书信息");

			m_slm_listctrl.SetItemText(nCount,6,opt_kind_cs);
		}

		end=start+strlen("|");

		start=strstr(end,"|");

		memcpy(slogitem[i].opt_result,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{  
			if(0 == strcmp((char*)slogitem[i].opt_result,"0"))
			{
				opt_result_cs.Format("%s","成功");
			}

			else
			{
				opt_result_cs.Format("%s","失败");

			}

			//opt_result_cs.Format("%s",slogitem[i].opt_result);
			m_slm_listctrl.SetItemText(nCount,7,opt_result_cs);
		}
		end=start+strlen("|");

		start=strstr(end,"|");

		//索引号
		memcpy(slogitem[i].oper_ID,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{  
			oper_ID_cs.Format("%s",slogitem[i].oper_ID);
			m_slm_listctrl.SetItemText(nCount,3,oper_ID_cs);
		}
		end=start+strlen("|");

		start=strstr(end,"|");
		//证书内容
		end=start+strlen("|");

		start=strstr(end,"|");//证书序列号
		memcpy(slogitem[i].cert_SN,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{ 

			opt_certSN_cs.Format("%s",slogitem[i].cert_SN);
			m_slm_listctrl.SetItemText(nCount,4,opt_certSN_cs);
		}
		end=start+strlen("|");
		//if(start-end>0)
		//{
		//	memcpy(slogitem[i].cert_SN,end,start-end);//------放到结构体缓存数组
		//	MessageBox(opt_certSN_cs,opt_certSN_cs,MB_ICONEXCLAMATION);
		//	if(i<20)
		//	{  


		//		opt_certSN_cs.Format("%s",slogitem[i].cert_SN);
		//		//MessageBox(opt_certSN_cs,opt_certSN_cs,MB_ICONEXCLAMATION);
		//		m_slm_listctrl.SetItemText(nCount,3,opt_certSN_cs);
		//	}
		//}	
		start=strstr(end,"|");//证书名字
		memcpy(slogitem[i].cert_DN,end,start-end);//------放到结构体缓存数组
		if(i<100)
		{ 

			opt_certDN_cs.Format("%s",slogitem[i].cert_DN);
			m_slm_listctrl.SetItemText(nCount,5,opt_certDN_cs);
		}


		end=start+strlen("|");
		//if(start-end>0)
		//{
		//	memcpy(slogitem[i].cert_DN,end,start-end);//------放到结构体缓存数组
		//	if(i<20)
		//	{  
		//

		//		opt_certDN_cs.Format("%s",slogitem[i].cert_DN);
		//		m_slm_listctrl.SetItemText(nCount,4,opt_certDN_cs);
		//	}
		//		//MessageBox(opt_certDN_cs,opt_certDN_cs,MB_ICONEXCLAMATION);
		//}
		start=strstr(end,"|");//原文
		end=start+strlen("|");

		start=strstr(end,"|");//密文
		end=start+strlen("|");

		start=strstr(end,"|");//哈希标识
		end=start+strlen("|");

		start=strstr(end,"|");//对称算法标识
		end=start+strlen("|");

		start=strstr(end,"|");
		memcpy(slogitem[i].opt_time,end,19);//------放到结构体缓存数组
		if(i<100)
		{

			opt_time_cs.Format("%s",slogitem[i].opt_time);
			m_slm_listctrl.SetItemText(nCount,8,opt_time_cs);
		}
		//MessageBox(opt_time_cs,opt_time_cs,MB_ICONEXCLAMATION);
		end=start+strlen("|");
		start=strstr(end,"\n");
		end=start+strlen("\n");

		//		end=start+20;

		nCount++;
		//str=end+19;
		str=end;

	}

	delete []logcontent;
}

void CServiceLogMngr::OnCbnSelchangeComboOptkind()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel; 
    nSel =m_optkind_CBox.GetCurSel(); //获取组合框控件列表里的选中项索引
	m_opt_kind.Format("%d", (nSel+1));


	//m_optkind_CBox.GetLBText(nSel,m_opt_kind);//根据索引获取对应字符串
}


////void CServiceLogMngr::OnBnClickedChecksign()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CServiceLogMngr::OnCbnSelchangeLgsavecombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel; 
	nSel =m_LogSaveCCBoX.GetCurSel(); //获取组合框控件列表里的选中项索引
	m_LogSaveCS.Format("%d", (nSel +1));
}
