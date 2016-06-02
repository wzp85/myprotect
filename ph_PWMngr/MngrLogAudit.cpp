// MngrLogAudit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "MngrLogAudit.h"
#include "afxdialogex.h"

#include "ph_km.h"
// CMngrLogAudit �Ի���

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


// CMngrLogAudit ��Ϣ�������

//����ѯ����ť��
void CMngrLogAudit::OnBnClickedButtonmlssearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret=0;
	UpdateData(TRUE);
	//�ۺ����
	if(m_mla_option_cs=="ȫ��" && m_mla_optype_cs=="ȫ��" && m_mla_opresult_cs=="ȫ��" && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
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
			MessageBox("���������ʧ�ܣ�"+(CString)smlaaError);
			return;
		}

		int nCount=0,i=0;
		CString item;

		char mngr[][50]={"Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����","Ӧ����Կ����",
						"CA֤�����","CA֤�����","CA֤�����","CA֤�����","CA֤�����","��֤�����","��֤�����","��֤�����","��֤�����"};
		char opkind[][50]={"���","����","����","�ָ�","����֤������","�����û�֤��","����","�޸Ŀ���","���","ɾ��","����","����","�ָ�","���",
							"ɾ��","����","����"};

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
			m_mngrLog_listctrl.SetItemText(nCount,4,"�ɹ�");
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
	//�������
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
		if(m_mla_option_cs!="ȫ��" && (m_mla_optype_cs=="ȫ��"||m_mla_optype_cs.IsEmpty()) && (m_mla_opresult_cs=="ȫ��"||m_mla_opresult_cs.IsEmpty()) && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_ONLYOPTION;//�������ղ���ģ����							�������

			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
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
		else if(m_mla_option_cs!="ȫ��" && m_mla_optype_cs!="ȫ��" && (m_mla_opresult_cs=="ȫ��"||m_mla_opresult_cs.IsEmpty()) && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_OPOPTYPE;//���ղ���ģ��Ͳ�������						�������
			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"���","����","����","�ָ�","����֤������","�����û�֤��","����","�޸Ŀ���"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"���","ɾ��","����","����","�ָ�"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"���","ɾ��","����","����"};
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
			if(m_mla_option_cs=="Ӧ��֤�����")
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
			else if(m_mla_option_cs=="CA֤�����")
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
			else if(m_mla_option_cs=="��֤�����")
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
		else if(m_mla_option_cs!="ȫ��" && m_mla_optype_cs!="ȫ��" && m_mla_opresult_cs!="ȫ��" && m_mla_starttime.IsEmpty() && m_mla_endtime.IsEmpty())
		{
			uiAuditMold=MLOGCOA_OPOPOPRESULT;//���ղ���ģ�顢���͡����						�������
			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"���","����","����","�ָ�","����֤������","�����û�֤��","����","�޸Ŀ���"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"���","ɾ��","����","����","�ָ�"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"���","ɾ��","����","����"};
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
			if(m_mla_option_cs=="Ӧ��֤�����")
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
			else if(m_mla_option_cs=="CA֤�����")
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
			else if(m_mla_option_cs=="��֤�����")
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
			if(m_mla_opresult_cs=="�ɹ�")
			{
				uiOptionResultLen=strlen("success");
				memcpy(pucOptionResult,"success",strlen("success"));
			}
			else if(m_mla_opresult_cs=="ʧ��")
			{
				uiOptionResultLen=strlen("fail");
				memcpy(pucOptionResult,"fail",strlen("fail"));
			}
		}
		else if(m_mla_option_cs!="ȫ��" && m_mla_optype_cs!="ȫ��" && m_mla_opresult_cs!="ȫ��" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//���ȼ���ʱ���ʽ
			if(m_mla_starttime.GetLength()!=10 || strcmp((const char*)m_mla_starttime.GetAt(4),"-") || strcmp((const char*)m_mla_starttime.GetAt(7),"-"))
			{
				MessageBox("��ʼʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((const char*)m_mla_endtime.GetAt(4),"-") || strcmp((char*)m_mla_endtime.GetAt(7),"-"))
			{
				MessageBox("��ֹʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPOPOPTIME;//���ղ���ģ�顢���͡������ʱ���				�������
			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"���","����","����","�ָ�","����֤������","�����û�֤��","����","�޸Ŀ���"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"���","ɾ��","����","����","�ָ�"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"���","ɾ��","����","����"};
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
			if(m_mla_option_cs=="Ӧ��֤�����")
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
			else if(m_mla_option_cs=="CA֤�����")
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
			else if(m_mla_option_cs=="��֤�����")
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
			if(m_mla_opresult_cs=="�ɹ�")
			{
				uiOptionResultLen=strlen("success");
				memcpy(pucOptionResult,"success",strlen("success"));
			}
			else if(m_mla_opresult_cs=="ʧ��")
			{
				uiOptionResultLen=strlen("fail");
				memcpy(pucOptionResult,"fail",strlen("fail"));
			}
			//����ʱ���ʽ����
			uiStartTimeLen=m_mla_starttime.GetLength();
			memcpy(pucStartTime,m_mla_starttime.GetBuffer(),m_mla_starttime.GetLength());
			uiEndTimeLen=m_mla_endtime.GetLength();
			memcpy(pucEndTime,m_mla_endtime.GetBuffer(),m_mla_endtime.GetLength());
		}
		else if(m_mla_option_cs!="ȫ��" && m_mla_optype_cs=="ȫ��" && m_mla_opresult_cs=="ȫ��" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//���ȼ���ʱ���ʽ
			if(m_mla_starttime.GetLength()!=10 || strcmp((char*)m_mla_starttime.GetBuffer()[4],"-") || strcmp((char*)m_mla_starttime.GetBuffer()[7],"-"))
			{
				MessageBox("��ʼʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((char*)m_mla_endtime.GetBuffer()[4],"-") || strcmp((char*)m_mla_endtime.GetBuffer()[7],"-"))
			{
				MessageBox("��ֹʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPTIONTIME;
			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
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
			//����ʱ���ʽ����
			uiStartTimeLen=m_mla_starttime.GetLength();
			memcpy(pucStartTime,m_mla_starttime.GetBuffer(),m_mla_starttime.GetLength());
			uiEndTimeLen=m_mla_endtime.GetLength();
			memcpy(pucEndTime,m_mla_endtime.GetBuffer(),m_mla_endtime.GetLength());
		}
		else if(m_mla_option_cs!="ȫ��" && m_mla_optype_cs!="ȫ��" && m_mla_opresult_cs=="ȫ��" && !m_mla_starttime.IsEmpty() && !m_mla_endtime.IsEmpty())
		{
			//���ȼ���ʱ���ʽ
			if(m_mla_starttime.GetLength()!=10 || strcmp((char*)m_mla_starttime.GetBuffer()[4],"-") || strcmp((char*)m_mla_starttime.GetBuffer()[7],"-"))
			{
				MessageBox("��ʼʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			else if(m_mla_endtime.GetLength()!=10 || strcmp((char*)m_mla_endtime.GetBuffer()[4],"-") || strcmp((char*)m_mla_endtime.GetBuffer()[7],"-"))
			{
				MessageBox("��ֹʱ���ʽ�������ϸ���YYYY-MM-DD��ʽ����ʱ�䣡","ʱ���ʽ����",MB_ICONEXCLAMATION);
				return;
			}
			uiAuditMold=MLOGCOA_OPOPTYPETIME;//���ղ���ģ�顢���͡�ʱ���					
			char option[][50]={"Ӧ��֤�����","CA֤�����","��֤�����","�豸��Կ����","��Կ������Կ����","�豸����Ա����","ǩ��������IP����"};
			char option_log[][32]={"appMngr","CACertMngr","RtCertMngr"};
			char option_type_a[][32]={"���","����","����","�ָ�","����֤������","�����û�֤��","����","�޸Ŀ���"};
			char option_type_acm[][32]={"Gen","AppKeyDistory","AppKeyBackup","Recovery","GenCertRequest","UserCertImport","UserCertExport","AppKeyModPasswd"};
			char option_type_b[][32]={"���","ɾ��","����","����","�ָ�"};
			char option_type_ccm[][32]={"Add","Delete","Export","Backup","Recovery"};
			char option_type_c[][32]={"���","ɾ��","����","����"};
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
			if(m_mla_option_cs=="Ӧ��֤�����")
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
			else if(m_mla_option_cs=="CA֤�����")
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
			else if(m_mla_option_cs=="��֤�����")
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
			MessageBox("������־�������ʧ�ܣ�"+(CString)mlcoaError,"ʧ��",MB_ICONEXCLAMATION);
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;   
    m_mngrLog_listctrl.GetClientRect(&rect);   
    m_mngrLog_listctrl.SetExtendedStyle(m_mngrLog_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	//�����иߣ�
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_mngrLog_listctrl.SetImageList(&img_list,LVSIL_SMALL); 
  
	m_mngrLog_listctrl.InsertColumn(1, _T(" "), LVCFMT_CENTER,20, 1);   
	m_mngrLog_listctrl.InsertColumn(2, _T("����ģ��"), LVCFMT_CENTER,(rect.Width()-20)/5, 2);   
    m_mngrLog_listctrl.InsertColumn(3, _T("��������"), LVCFMT_CENTER,(rect.Width()-20)/5, 3);   
    m_mngrLog_listctrl.InsertColumn(4, _T("��������"), LVCFMT_CENTER,(rect.Width()-20)/5-50, 4); 
	m_mngrLog_listctrl.InsertColumn(5, _T("�������"), LVCFMT_CENTER,(rect.Width()-20)/5, 5);
	m_mngrLog_listctrl.InsertColumn(6, _T("����ʱ��"), LVCFMT_CENTER,(rect.Width()-20)/5+50, 6); 


	m_mngrLogAudit_option.AddString("Ӧ��֤�����");
	m_mngrLogAudit_option.AddString("CA֤�����");
	m_mngrLogAudit_option.AddString("��֤�����");
	m_mngrLogAudit_option.AddString("�豸��Կ����");
	m_mngrLogAudit_option.AddString("��Կ������Կ����");
	m_mngrLogAudit_option.AddString("�豸����Ա����");
	m_mngrLogAudit_option.AddString("ǩ��������IP����");
	m_mngrLogAudit_option.AddString("ȫ��");

	m_mngrLogAudit_opresult.AddString("�ɹ�");
	m_mngrLogAudit_opresult.AddString("ʧ��");
	m_mngrLogAudit_opresult.AddString("ȫ��");


	SetDlgItemText(IDC_COMBO_mls_option,"ȫ��");
	SetDlgItemText(IDC_COMBO_optype,"ȫ��");
	SetDlgItemText(IDC_COMBO_opresult,"ȫ��");


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMngrLogAudit::OnCbnSelchangeCombomlsoption()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;    
    nSel = m_mngrLogAudit_option.GetCurSel(); 
	m_mngrLogAudit_optype.ResetContent();
	SetDlgItemText(IDC_COMBO_opresult,"");
	switch(nSel+1)
	{
	case 1:
		m_mngrLogAudit_optype.AddString("������Կ");
		m_mngrLogAudit_optype.AddString("����֤������");
		m_mngrLogAudit_optype.AddString("����֤��");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("�ָ�");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("�޸Ŀ���");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("ȫ��");
		break;
	case 2:
		m_mngrLogAudit_optype.AddString("���");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("�ָ�");
		m_mngrLogAudit_optype.AddString("ɾ��");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("ȫ��");
		break;
	case 3:
		m_mngrLogAudit_optype.AddString("���");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("�ָ�");
		m_mngrLogAudit_optype.AddString("ɾ��");
		m_mngrLogAudit_optype.AddString("����");
		m_mngrLogAudit_optype.AddString("ȫ��");
		break;
	case 8:
		SetDlgItemText(IDC_COMBO_optype,"ȫ��");
		SetDlgItemText(IDC_COMBO_opresult,"ȫ��");
		break;
	}
}
