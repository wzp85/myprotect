// MngrLogAudit.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "MngrLogAudit.h"
#include "afxdialogex.h"

#include "ph_km.h"
// CMngrLogAudit 对话框

IMPLEMENT_DYNAMIC(CMngrLogAudit, CDialogEx)

CMngrLogAudit::CMngrLogAudit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMngrLogAudit::IDD, pParent)
	, m_mla_starttime(_T(""))
	, m_mla_endtime(_T(""))
	, m_mla_option_cs(_T(""))
	, m_mla_optype_cs(_T(""))
	, m_mla_opresult_cs(_T(""))
{

}

CMngrLogAudit::~CMngrLogAudit()
{
}

void CMngrLogAudit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_mngrLog_shenji, m_mngrLog_listctrl);
	DDX_Control(pDX, IDC_COMBO_mls_option, m_mngrLogAudit_option);
	DDX_Control(pDX, IDC_COMBO_optype, m_mngrLogAudit_optype);
	DDX_Control(pDX, IDC_COMBO_opresult, m_mngrLogAudit_opresult);
	DDX_Text(pDX, IDC_EDIT_mls_starttime, m_mla_starttime);
	DDX_Text(pDX, IDC_EDIT_endtime, m_mla_endtime);
	DDX_CBString(pDX, IDC_COMBO_mls_option, m_mla_option_cs);
	DDX_CBString(pDX, IDC_COMBO_optype, m_mla_optype_cs);
	DDX_CBString(pDX, IDC_COMBO_opresult, m_mla_opresult_cs);
}


BEGIN_MESSAGE_MAP(CMngrLogAudit, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_mls_search, &CMngrLogAudit::OnBnClickedButtonmlssearch)
	ON_CBN_SELCHANGE(IDC_COMBO_mls_option, &CMngrLogAudit::OnCbnSelchangeCombomlsoption)
END_MESSAGE_MAP()


// CMngrLogAudit 消息处理程序

//“查询”按钮！
void CMngrLogAudit::OnBnClickedButtonmlssearch()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	UpdateData(TRUE);
	//综合审计
	if(m_mla_option_cs=="全部" && m_mla_optype_cs=="全部" && m_mla_opresult_cs=="全部" && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
	{
		unsigned int uiLogIndexNum=0;
		unsigned int puiLogIndex[100]={0};
		unsigned int uiLogTimeLen=0;
		unsigned char pucLogTime[1024]={0x00};
		ret=Sig_MngrLogAuditAll(phHandle_mla,&uiLogIndexNum,puiLogIndex,&uiLogTimeLen,pucLogTime);
		if(0!=ret)
		{
			char smlaaError[100]={0x00};
			retValueParse(ret,smlaaError);
			MessageBox("服务器审计失败！"+(CString)smlaaError);
			return;
		}

		int nCount=0,i=0;
		CString item;

		char mngr[][50]={"应用密钥管理","应用密钥管理","应用密钥管理","应用密钥管理","应用密钥管理","应用密钥管理","应用密钥管理","应用密钥管理",
						"CA证书管理","CA证书管理","CA证书管理","CA证书管理","CA证书管理","根证书管理","根证书管理","根证书管理","根证书管理"};
		char opkind[][50]={"添加","销毁","备份","恢复","生成证书请求","导入用户证书","导出","修改口令","添加","删除","导出","备份","恢复","添加",
							"删除","导出","备份"};

		char *start=(char*)pucLogTime;
		char *end;
		char timeBuf[32]={0x00};

		for(unsigned int i=0;i<uiLogIndexNum;i++)
		{
			m_mngrLog_listctrl.InsertItem(nCount,0);
			m_mngrLog_listctrl.SetItemText(nCount,1,mngr[i]);
			m_mngrLog_listctrl.SetItemText(nCount,2,opkind[i]);
			item.Format("%d",puiLogIndex[i]);
			m_mngrLog_listctrl.SetItemText(nCount,3,item);
			m_mngrLog_listctrl.SetItemText(nCount,4,"成功");
			end=strstr(start,"||");
			memset(timeBuf,0x00,32);
			memcpy(timeBuf,start,end-start);
			start=end+strlen("||");
			if(!strncmp(start,"!",1))
				break;
			if(!strncmp(timeBuf,"notime",6))
				memset(timeBuf,0x00,32);
			m_mngrLog_listctrl.SetItemText(nCount,5,(LPCTSTR)timeBuf);
			nCount++;
		}
	}
	//分类审计
	else
	{
		unsigned int uiAuditMold=0;
		unsigned int uiOptionLen=0;
		unsigned char pucOption[32]={0x00};
		unsigned int uiOptionTypeLen=0;
		unsigned char pucOptionType[32]={0x00};
		unsigned int uiOptionResultLen=0;
		unsigned char pucOptionResult[32]={0x00};
		unsigned int uiStartTimeLen=0;
		unsigned char pucStartTime[64]={0x00};
		unsigned int uiEndTimeLen=0;
		unsigned char pucEndTime[64]={0x00};
		unsigned int auditResultCount=0;
		unsigned int uiReLogTimeLenth=0;
		unsigned char pucReLogTime[32]={0x00};
		if(m_mla_option_cs!="全部" && (m_mla_optype_cs=="全部"||m_mla_optype_cs.IsEmpty()) && (m_mla_opresult_cs=="全部"||m_mla_opresult_cs.IsEmpty()) && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_ONLYOPTION;//仅仅按照操作模块做							分类审计

			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
		}
		else if(m_mla_option_cs!="全部" && m_mla_optype_cs!="全部" && (m_mla_opresult_cs=="全部"||m_mla_opresult_cs.IsEmpty()) && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_OPOPTYPE;//按照操作模块和操作类型						分类审计
			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"添加","销毁","备份","恢复","生成证书请求","导入用户证书","导出","修改口令"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"添加","删除","导出","备份","恢复"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"添加","删除","导出","备份"};
			char option_type_rcm[][32]={"RootCertAdd","RootCertDel","Export","Backup"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
			if(m_mla_option_cs=="应用证书管理")
			{
				for(int j=0;j<8;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_a[j]))
					{
						uiOptionTypeLen=strlen(option_type_acm[j]);
						memcpy(pucOptionType,option_type_acm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="CA证书管理")
			{
				for(int j=0;j<5;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_b[j]))
					{
						uiOptionTypeLen=strlen(option_type_ccm[j]);
						memcpy(pucOptionType,option_type_ccm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="根证书管理")
			{
				for(int j=0;j<4;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_c[j]))
					{
						uiOptionTypeLen=strlen(option_type_rcm[j]);
						memcpy(pucOptionType,option_type_rcm[j],uiOptionTypeLen);
						break;
					}
				}
			}
		}
		else if(m_mla_option_cs!="全部" && m_mla_optype_cs!="全部" && m_mla_opresult_cs!="全部" && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_OPOPOPRESULT;//按照操作模块、类型、结果						分类审计
			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"添加","销毁","备份","恢复","生成证书请求","导入用户证书","导出","修改口令"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"添加","删除","导出","备份","恢复"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"添加","删除","导出","备份"};
			char option_type_rcm[][32]={"RootCertAdd","RootCertDel","Export","Backup"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
			if(m_mla_option_cs=="应用证书管理")
			{
				for(int j=0;j<8;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_a[j]))
					{
						uiOptionTypeLen=strlen(option_type_acm[j]);
						memcpy(pucOptionType,option_type_acm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="CA证书管理")
			{
				for(int j=0;j<5;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_b[j]))
					{
						uiOptionTypeLen=strlen(option_type_ccm[j]);
						memcpy(pucOptionType,option_type_ccm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="根证书管理")
			{
				for(int j=0;j<4;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_c[j]))
					{
						uiOptionTypeLen=strlen(option_type_rcm[j]);
						memcpy(pucOptionType,option_type_rcm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			if(m_mla_opresult_cs=="成功")
			{
				uiOptionResultLen=strlen("success");
				memcpy(pucOptionResult,"success",strlen("success"));
			}
			else if(m_mla_opresult_cs=="失败")
			{
				uiOptionResultLen=strlen("fail");
				memcpy(pucOptionResult,"fail",strlen("fail"));
			}
		}
		else if(m_mla_option_cs!="全部" && m_mla_optype_cs!="全部" && m_mla_opresult_cs!="全部" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//首先检验时间格式
			if(m_mla_starttime.GetLength()!=10 || strcmp((const char*)m_mla_starttime.GetAt(4),"-") || strcmp((const char*)m_mla_starttime.GetAt(7),"-"))
			{
				MessageBox("起始时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((const char*)m_mla_endtime.GetAt(4),"-") || strcmp((char*)m_mla_endtime.GetAt(7),"-"))
			{
				MessageBox("终止时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPOPOPTIME;//按照操作模块、类型、结果、时间段				分类审计
			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"添加","销毁","备份","恢复","生成证书请求","导入用户证书","导出","修改口令"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"添加","删除","导出","备份","恢复"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"添加","删除","导出","备份"};
			char option_type_rcm[][32]={"RootCertAdd","RootCertDel","Export","Backup"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
			if(m_mla_option_cs=="应用证书管理")
			{
				for(int j=0;j<8;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_a[j]))
					{
						uiOptionTypeLen=strlen(option_type_acm[j]);
						memcpy(pucOptionType,option_type_acm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="CA证书管理")
			{
				for(int j=0;j<5;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_b[j]))
					{
						uiOptionTypeLen=strlen(option_type_ccm[j]);
						memcpy(pucOptionType,option_type_ccm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="根证书管理")
			{
				for(int j=0;j<4;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_c[j]))
					{
						uiOptionTypeLen=strlen(option_type_rcm[j]);
						memcpy(pucOptionType,option_type_rcm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			if(m_mla_opresult_cs=="成功")
			{
				uiOptionResultLen=strlen("success");
				memcpy(pucOptionResult,"success",strlen("success"));
			}
			else if(m_mla_opresult_cs=="失败")
			{
				uiOptionResultLen=strlen("fail");
				memcpy(pucOptionResult,"fail",strlen("fail"));
			}
			//传递时间格式参数
			uiStartTimeLen=m_mla_starttime.GetLength();
			memcpy(pucStartTime,m_mla_starttime.GetBuffer(),m_mla_starttime.GetLength());
			uiEndTimeLen=m_mla_endtime.GetLength();
			memcpy(pucEndTime,m_mla_endtime.GetBuffer(),m_mla_endtime.GetLength());
		}
		else if(m_mla_option_cs!="全部" && m_mla_optype_cs=="全部" && m_mla_opresult_cs=="全部" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//首先检验时间格式
			if(m_mla_starttime.GetLength()!=10 || strcmp((char*)m_mla_starttime.GetBuffer()[4],"-") || strcmp((char*)m_mla_starttime.GetBuffer()[7],"-"))
			{
				MessageBox("起始时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((char*)m_mla_endtime.GetBuffer()[4],"-") || strcmp((char*)m_mla_endtime.GetBuffer()[7],"-"))
			{
				MessageBox("终止时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPTIONTIME;
			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
			//传递时间格式参数
			uiStartTimeLen=m_mla_starttime.GetLength();
			memcpy(pucStartTime,m_mla_starttime.GetBuffer(),m_mla_starttime.GetLength());
			uiEndTimeLen=m_mla_endtime.GetLength();
			memcpy(pucEndTime,m_mla_endtime.GetBuffer(),m_mla_endtime.GetLength());
		}
		else if(m_mla_option_cs!="全部" && m_mla_optype_cs!="全部" && m_mla_opresult_cs=="全部" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//首先检验时间格式
			if(m_mla_starttime.GetLength()!=10 || strcmp((char*)m_mla_starttime.GetBuffer()[4],"-") || strcmp((char*)m_mla_starttime.GetBuffer()[7],"-"))
			{
				MessageBox("起始时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((char*)m_mla_endtime.GetBuffer()[4],"-") || strcmp((char*)m_mla_endtime.GetBuffer()[7],"-"))
			{
				MessageBox("终止时间格式错误！请严格按照YYYY-MM-DD格式输入时间！","时间格式错误",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPOPTYPETIME;//按照操作模块、类型、时间段					
			char option[][50]={"应用证书管理","CA证书管理","根证书管理","设备密钥管理","密钥备份密钥生成","设备管理员管理","签名服务器IP管理"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"添加","销毁","备份","恢复","生成证书请求","导入用户证书","导出","修改口令"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"添加","删除","导出","备份","恢复"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"添加","删除","导出","备份"};
			char option_type_rcm[][32]={"RootCertAdd","RootCertDel","Export","Backup"};
			for(int i=0;i<3;i++)
			{
				if(!strcmp(m_mla_option_cs.GetBuffer(),option[i]))
				{
					uiOptionLen=strlen(option_log[i]);
					memcpy(pucOption,option_log[i],uiOptionLen);
					break;
				}
			}
			if(m_mla_option_cs=="应用证书管理")
			{
				for(int j=0;j<8;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_a[j]))
					{
						uiOptionTypeLen=strlen(option_type_acm[j]);
						memcpy(pucOptionType,option_type_acm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="CA证书管理")
			{
				for(int j=0;j<5;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_b[j]))
					{
						uiOptionTypeLen=strlen(option_type_ccm[j]);
						memcpy(pucOptionType,option_type_ccm[j],uiOptionTypeLen);
						break;
					}
				}
			}
			else if(m_mla_option_cs=="根证书管理")
			{
				for(int j=0;j<4;j++)
				{
					if(!strcmp(m_mla_optype_cs.GetBuffer(),option_type_c[j]))
					{
						uiOptionTypeLen=strlen(option_type_rcm[j]);
						memcpy(pucOptionType,option_type_rcm[j],uiOptionTypeLen);
						break;
					}
				}
			}
		}

		ret=Sig_ManagementLogCOA(phHandle_mla,uiAuditMold,uiOptionLen,pucOption,uiOptionTypeLen,pucOptionType,uiOptionResultLen,pucOptionResult,
								uiStartTimeLen,pucStartTime,uiEndTimeLen,pucEndTime,&auditResultCount,&uiReLogTimeLenth,pucReLogTime);
		if(0!=ret)
		{
			char mlcoaError[100]={0x00};
			retValueParse(ret,mlcoaError);
			MessageBox("管理日志分类审计失败！"+(CString)mlcoaError,"失败",MB_ICONEXCLAMATION);
			return; 
		}
		m_mngrLog_listctrl.DeleteAllItems();
		CString item_count;
		m_mngrLog_listctrl.InsertItem(0,0);
		m_mngrLog_listctrl.SetItemText(0,1,m_mla_option_cs);
		m_mngrLog_listctrl.SetItemText(0,2,m_mla_optype_cs);
		item_count.Format("%d",auditResultCount);
		m_mngrLog_listctrl.SetItemText(0,3,item_count);
		m_mngrLog_listctrl.SetItemText(0,4,m_mla_opresult_cs);
		m_mngrLog_listctrl.SetItemText(0,5,(LPCTSTR)pucReLogTime);
	}

}


BOOL CMngrLogAudit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;   
    m_mngrLog_listctrl.GetClientRect(&rect);   
    m_mngrLog_listctrl.SetExtendedStyle(m_mngrLog_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	//设置行高！
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_mngrLog_listctrl.SetImageList(&img_list,LVSIL_SMALL); 
  
	m_mngrLog_listctrl.InsertColumn(1, _T(" "), LVCFMT_CENTER,20, 1);   
	m_mngrLog_listctrl.InsertColumn(2, _T("操作模块"), LVCFMT_CENTER,(rect.Width()-20)/5, 2);   
    m_mngrLog_listctrl.InsertColumn(3, _T("操作类型"), LVCFMT_CENTER,(rect.Width()-20)/5, 3);   
    m_mngrLog_listctrl.InsertColumn(4, _T("操作数量"), LVCFMT_CENTER,(rect.Width()-20)/5-50, 4); 
	m_mngrLog_listctrl.InsertColumn(5, _T("操作结果"), LVCFMT_CENTER,(rect.Width()-20)/5, 5);
	m_mngrLog_listctrl.InsertColumn(6, _T("操作时间"), LVCFMT_CENTER,(rect.Width()-20)/5+50, 6); 


	m_mngrLogAudit_option.AddString("应用证书管理");
	m_mngrLogAudit_option.AddString("CA证书管理");
	m_mngrLogAudit_option.AddString("根证书管理");
	m_mngrLogAudit_option.AddString("设备密钥管理");
	m_mngrLogAudit_option.AddString("密钥备份密钥生成");
	m_mngrLogAudit_option.AddString("设备管理员管理");
	m_mngrLogAudit_option.AddString("签名服务器IP管理");
	m_mngrLogAudit_option.AddString("全部");

	m_mngrLogAudit_opresult.AddString("成功");
	m_mngrLogAudit_opresult.AddString("失败");
	m_mngrLogAudit_opresult.AddString("全部");


	SetDlgItemText(IDC_COMBO_mls_option,"全部");
	SetDlgItemText(IDC_COMBO_optype,"全部");
	SetDlgItemText(IDC_COMBO_opresult,"全部");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMngrLogAudit::OnCbnSelchangeCombomlsoption()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;    
    nSel = m_mngrLogAudit_option.GetCurSel(); 
	m_mngrLogAudit_optype.ResetContent();
	SetDlgItemText(IDC_COMBO_opresult,"");
	switch(nSel+1)
	{
	case 1:
		m_mngrLogAudit_optype.AddString("生成密钥");
		m_mngrLogAudit_optype.AddString("生成证书请求");
		m_mngrLogAudit_optype.AddString("导入证书");
		m_mngrLogAudit_optype.AddString("备份");
		m_mngrLogAudit_optype.AddString("更新");
		m_mngrLogAudit_optype.AddString("恢复");
		m_mngrLogAudit_optype.AddString("销毁");
		m_mngrLogAudit_optype.AddString("修改口令");
		m_mngrLogAudit_optype.AddString("导出");
		m_mngrLogAudit_optype.AddString("全部");
		break;
	case 2:
		m_mngrLogAudit_optype.AddString("添加");
		m_mngrLogAudit_optype.AddString("备份");
		m_mngrLogAudit_optype.AddString("更新");
		m_mngrLogAudit_optype.AddString("恢复");
		m_mngrLogAudit_optype.AddString("删除");
		m_mngrLogAudit_optype.AddString("导出");
		m_mngrLogAudit_optype.AddString("全部");
		break;
	case 3:
		m_mngrLogAudit_optype.AddString("添加");
		m_mngrLogAudit_optype.AddString("备份");
		m_mngrLogAudit_optype.AddString("更新");
		m_mngrLogAudit_optype.AddString("恢复");
		m_mngrLogAudit_optype.AddString("删除");
		m_mngrLogAudit_optype.AddString("导出");
		m_mngrLogAudit_optype.AddString("全部");
		break;
	case 8:
		SetDlgItemText(IDC_COMBO_optype,"全部");
		SetDlgItemText(IDC_COMBO_opresult,"全部");
		break;
	}
}
