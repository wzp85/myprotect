// DevAdminMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "DevAdminMngr.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
#include "ChoseFilePath.h"
// CDevAdminMngr 对话框
#define ADM_UPDATA 777
int devAdmNum = 0;
int aTime_show = 0;


IMPLEMENT_DYNAMIC(CDevAdminMngr, CDialogEx)

CDevAdminMngr::CDevAdminMngr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevAdminMngr::IDD, pParent)
	, m_adminIndex_sh(_T(""))
	, m_adminName_sh(_T(""))
{
	admin_index_max = 0;
}

CDevAdminMngr::~CDevAdminMngr()
{
}

void CDevAdminMngr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SH_ADMININDEX_EDIT, m_adminIndex_sh);
	DDX_Text(pDX, IDC_SH_ADMINNAME_EDIT, m_adminName_sh);
	DDX_Control(pDX, IDC_DEVADMINMNGR_LIST, m_listCtrlAdminMngr);
}

BOOL CDevAdminMngr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;    
    m_listCtrlAdminMngr.GetClientRect(&rect);   
    m_listCtrlAdminMngr.SetExtendedStyle(m_listCtrlAdminMngr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//设置行高！
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_listCtrlAdminMngr.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,530,450);   
	m_listCtrlAdminMngr.SetWindowPos(NULL,0,0,rect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
  
	m_listCtrlAdminMngr.InsertColumn(0,NULL,LVCFMT_CENTER,30);
    m_listCtrlAdminMngr.InsertColumn(1, _T("管理员编号"), LVCFMT_CENTER, (rect.Width() - 30)/6, 1);   
    m_listCtrlAdminMngr.InsertColumn(2, _T("管理员名称"), LVCFMT_CENTER, (rect.Width() - 30)/6, 2);   
    m_listCtrlAdminMngr.InsertColumn(3, _T("联系方式"), LVCFMT_CENTER, (rect.Width() - 30)/6, 3); 
	m_listCtrlAdminMngr.InsertColumn(4, _T("证件类型"), LVCFMT_CENTER, (rect.Width() - 30)/6, 4);
	m_listCtrlAdminMngr.InsertColumn(5, _T("证件号"), LVCFMT_CENTER, (rect.Width() - 30)/6, 5); 
	m_listCtrlAdminMngr.InsertColumn(6, _T("管理员最大数量"), LVCFMT_CENTER, (rect.Width() - 30)/6, 6); 
	//m_listCtrlAdminMngr.InsertColumn(7, _T("管理员类型"), LVCFMT_CENTER, (rect.Width() - 30)/7, 7); 

	//列表头添加checkbox
	// Here's where we can add the checkbox to the column header
	// First, we need to snag the header control and give it the
	// HDS_CHECKBOXES style since the list view doesn't do this for us
	HWND header = ListView_GetHeader(m_listCtrlAdminMngr);
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
	
	aTime_show++;
	CDevAdminMngr::ShowAdminInfo();

	isCheckbox_adm = FALSE;
	memset(check_adm,0,256);
	i_checked_adm = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CDevAdminMngr, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &CDevAdminMngr::OnBnClickedButton1)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDevAdminMngr::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_ADMINSEARCH_BUTTON, &CDevAdminMngr::OnBnClickedAdminsearchButton)
	ON_NOTIFY(NM_RCLICK, IDC_DEVADMINMNGR_LIST, &CDevAdminMngr::OnNMRClickDevadminmngrList)
	ON_COMMAND(ID__ADDADM, &CDevAdminMngr::OnAddadm)
	ON_COMMAND(ID__UPDATEADM, &CDevAdminMngr::OnUpdateadm)
	ON_COMMAND(ID__DELADM, &CDevAdminMngr::OnDeladm)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DEVADMINMNGR_LIST, &CDevAdminMngr::OnLvnItemchangedDevadminmngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CDevAdminMngr::OnItemstateiconclickDevadminmngrList)
//	ON_NOTIFY(NM_CLICK, IDC_DEVADMINMNGR_LIST, &CDevAdminMngr::OnClickDevadminmngrList)
ON_NOTIFY(NM_CLICK, IDC_DEVADMINMNGR_LIST, &CDevAdminMngr::OnNMClickDevadminmngrList)
ON_COMMAND(ID__BACKUPADM, &CDevAdminMngr::OnBackupadm)
END_MESSAGE_MAP()


// CDevAdminMngr 消息处理程序
BOOL CDevAdminMngr::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)    
        return TRUE; 
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CDevAdminMngr::OnBnClickedAdminsearchButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//查询
	UpdateData(TRUE);
	
	int aTime = 0;
	CString appName = m_adminName_sh;
	CString keyIndex = m_adminIndex_sh;
	if(appName.IsEmpty() && keyIndex.IsEmpty())
	{
		CDevAdminMngr::ShowAdminInfo();
	}
	else
	{
		CDevAdminMngr::ShowAdminInfo_Search(appName,keyIndex);
	}
}


void CDevAdminMngr::ShowAdminInfo()
{
	m_listCtrlAdminMngr.DeleteAllItems();
	int ret = 0;
	void * hSessionHandle = phHandle_adm;
	unsigned char *puiAdminList = NULL;
	unsigned int puiAdminListLen=0;
	char outGal[100]={0x00};
	ret = Km_GetAdminList(hSessionHandle,puiAdminList,&puiAdminListLen);
	if(0 != ret)
	{
		retValueParse(ret,outGal);
		MessageBox("获取管理员列表失败"+(CString)outGal,"提示",MB_ICONEXCLAMATION);
		return;
	}
	puiAdminList = new unsigned char[puiAdminListLen+1];
	memset(puiAdminList,0x00,puiAdminListLen+1);
	ret = Km_GetAdminList(hSessionHandle,puiAdminList,&puiAdminListLen);
	if(0 != ret)
	{
		retValueParse(ret,outGal);
		MessageBox("获取管理员列表失败"+(CString)outGal,"提示",MB_ICONEXCLAMATION);
		delete puiAdminList;
		return;
	}
	//char *filename = "C:\\Users\\Administrator\\Desktop\\admadmin.txt";
	//unsigned char *pbData=NULL;
	//int nDataLen = puiAdminListLen;
	//pbData = new unsigned char[nDataLen];
	//memcpy(pbData,puiAdminList,puiAdminListLen);
	//CMyUtil::Write2File(filename,pbData,nDataLen);
	//delete pbData;

	if(0 == puiAdminListLen)
		return;
	char *keyList = (char *)puiAdminList;
	char *str = strstr(keyList,"uiAdminType");
	char *source = str + strlen("uiAdminType");
	CString id;

	//刚开始假设每一个管理员序列号都是可以用的---即：第二列都为1
	int admin_index[16][2]={0};
	for(int j = 0;j < 2;j++)
	{
		for(int i = 0;i < 16;i++)
		{
			if(0 == j)
				admin_index[i][0] = i;
			else
				admin_index[i][1] = 1;
		}
	}

	int time = 0;
	int nCount = 0;
	for(int i = 0;i < 16;i++)
	{
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");		//这里是在管理员序列号之前   数据库ID之后的   |
		//MessageBox("str1--->"+(CString)str1);
		if(str1 == NULL)
		{
			//MessageBox("BREAK---str1");
			break;
		}
		/*time++;
		id.Format("%d",i);*/
		//m_listCtrlAdminMngr.InsertItem(nCount,0); 

		//数据库id字段项
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		//管理员序列号
		char adminIndexBuf[32]={0x00};
		char *str_admName = strstr(str2,"|");
		if(str_admName == NULL)
		{
			//MessageBox("str_admName == 为空","");
			break;
		}
		m_listCtrlAdminMngr.InsertItem(nCount,0);
		memcpy(adminIndexBuf,str2,str_admName-str2);
		//MessageBox("str_appName222222 == 为空","");
		m_listCtrlAdminMngr.SetItemText(nCount,1,adminIndexBuf);   
		char *str3 = str2 + strlen(adminIndexBuf) + 1;
		for(int z=0;z<16;z++)//如果序列号用过就标识出来，在序列号数组对应数字的第二位标识我0：即不可用
		{
			if(admin_index[z][0] == atoi(adminIndexBuf))
				admin_index[z][1]=0;
		}
		if(adm_ind == atoi(adminIndexBuf))
			nID = nCount;
			//m_listCtrlAdminMngr.SetCheck(adm_ind,FALSE);

		//管理员名称
		char adminNameBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(adminNameBuf,str3,str_keyIndex-str3);
		m_listCtrlAdminMngr.SetItemText(nCount,2,adminNameBuf); 
		char *str4 = str3 + strlen(adminNameBuf) + 1;
		
		//管理员电话号码
		char adminTelBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(adminTelBuf,str4,str_algId-str4);
		m_listCtrlAdminMngr.SetItemText(nCount,3,CString(adminTelBuf));
		char *str5 = str4 + strlen(adminTelBuf) + 1;

		//证件类型
		char adminPaperType[1]={0x00};
		memcpy(adminPaperType,str5,1);
		if(0 == atoi(adminPaperType))
			m_listCtrlAdminMngr.SetItemText(nCount,4, _T("其他"));
		if(1 == atoi(adminPaperType))
			m_listCtrlAdminMngr.SetItemText(nCount,4, _T("身份证"));
		char *str6 = str5 + 2;

		//证件号码
		char adminPaperNum[32]={0x00};
		char *str_apn=strstr(str6,"|");
		memcpy(adminPaperNum,str6,str_apn-str6);
		m_listCtrlAdminMngr.SetItemText(nCount,5,CString(adminPaperNum));
		char *str7 = str6 + strlen(adminPaperNum) + 1;

		//编码后的公钥
		char pubKeyBuf[1024]={0x00};
		char *str_pubKey = strstr(str7,"|");
		memcpy(pubKeyBuf,str7,str_pubKey-str7);
		char *str8 = str7 + strlen(pubKeyBuf) + 1;

		CString maxNum;
		DEVKEYINFO devInfo={0x00};
		//if(1 == time/* && 1 == aTime_show*/)
		//{
			ret = Km_GetDevKeyInfo(hSessionHandle,&devInfo);
			maxNum.Format("%d",devInfo.uiBakTotalKey);
			devAdmNum = devInfo.uiBakTotalKey;
		/*}
		else*/
		//MessageBox("崩---in_show","");
		//maxNum.Format("%d",devAdmNum/*admCountInShow*/);
		m_listCtrlAdminMngr.SetItemText(nCount,6,maxNum);//---------显示最大管理员数量

		//管理员类型
	/*	char adminType[1]={0x00};
		char *str_adminType=strstr(str8,"|");
		memcpy(adminType,str8,1);
		CString admin_type;
		if(0 == atoi(adminType))
			admin_type = "系统管理员";
		if(1 == atoi(adminType))
			admin_type = "密钥管理员";*/

		char *str9 = str8 + 2;

		nCount++;
		source = str9;
	}
	//MessageBox("崩---delete pre","");
	delete puiAdminList;
	//MessageBox("崩---delete after","");
	m_listCtrlAdminMngr.Scroll( CSize( 0, 100000 ) );

	memcpy(admin_keyIndex,admin_index,sizeof(admin_index));
	for(int i = 0;i < 16;i++)
	{
		if(1 == admin_index[i][1])
		{
			admin_index_max = admin_index[i][0];
			break;
		}
	}
}

void CDevAdminMngr::ShowAdminInfo_Search(CString admName,CString admIndex)
{
	m_listCtrlAdminMngr.DeleteAllItems();
	int ret = 0;
	void * hSessionHandle = phHandle_adm;
	unsigned char *puiAdminList = NULL;
	unsigned int puiAdminListLen=0;
	char outGalist[100]={0x00};
	ret = Km_GetAdminList(hSessionHandle,puiAdminList,&puiAdminListLen);
	if(0 != ret)
	{
		retValueParse(ret,outGalist);
		MessageBox("获取管理员列表失败"+(CString)outGalist,"提示",MB_ICONEXCLAMATION);
		return;
	}
	puiAdminList = new unsigned char[puiAdminListLen+1];
	memset(puiAdminList,0x00,puiAdminListLen+1);
	ret = Km_GetAdminList(hSessionHandle,puiAdminList,&puiAdminListLen);
	if(0 != ret)
	{
		retValueParse(ret,outGalist);
		MessageBox("获取管理员列表失败"+(CString)outGalist,"提示",MB_ICONEXCLAMATION);
		delete puiAdminList;
		return;
	}

	if(0 == puiAdminListLen)
		return;
	char *keyList = (char *)puiAdminList;
	char *str = strstr(keyList,"uiAdminType");
	char *source = str + strlen("uiAdminType");
	CString id;

	//刚开始假设每一个管理员序列号都是可以用的---即：第二列都为1
	int admin_index[16][2]={0};
	for(int j = 0;j < 2;j++)
	{
		for(int i = 0;i < 16;i++)
		{
			if(0 == j)
				admin_index[i][0] = i;
			else
				admin_index[i][1] = 1;
		}
	}

	AISH aish[16]={0};

	int time = 0;
	int nCount = 0;
	for(int i = 0;i < 16;i++)
	{
//		if((int)source -(int)puiAdminList>puiAdminListLen)
		if(0 == *source)
			break;
		char *str1 = strstr(source,"|");
		if(str1 == NULL)
			break;

		time++;
		//id.Format("%d",i);
		//m_listCtrlAdminMngr.InsertItem(nCount,0); 

		//数据库id字段项
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		//管理员序列号
		char adminIndexBuf[32]={0x00};
		char *str_appName = strstr(str2,"|");
		memcpy(adminIndexBuf,str2,str_appName-str2);
		aish[i].index = atoi(adminIndexBuf);//---------------------------------------管理员序列号
		//m_listCtrlAdminMngr.SetItemText(nCount,1,adminIndexBuf);   
		char *str3 = str2 + strlen(adminIndexBuf) + 1;
		for(int z=0;z<16;z++)//如果序列号用过就标识出来，在序列号数组对应数字的第二位标识我0：即不可用
		{
			if(admin_index[z][0] == atoi(adminIndexBuf))
				admin_index[z][1]=0;
		}
		if(adm_ind == atoi(adminIndexBuf))
			nID = nCount;
			//m_listCtrlAdminMngr.SetCheck(adm_ind,FALSE);

		//管理员名称
		char adminNameBuf[32]={0x00};
		char *str_keyIndex = strstr(str3,"|");
		memcpy(adminNameBuf,str3,str_keyIndex-str3);
		memcpy(aish[i].name,adminNameBuf,strlen(adminNameBuf));//------------------------------管理员姓名
		//m_listCtrlAdminMngr.SetItemText(nCount,2,adminNameBuf); 
		char *str4 = str3 + strlen(adminNameBuf) + 1;
		
		//管理员电话号码
		char adminTelBuf[32]={0x00};
		char *str_algId = strstr(str4,"|");
		memcpy(adminTelBuf,str4,str_algId-str4);
		memcpy(aish[i].phone,adminTelBuf,strlen(adminTelBuf));//--------------------------------------管理员电话号码
		//m_listCtrlAdminMngr.SetItemText(nCount,3,CString(adminTelBuf));
		char *str5 = str4 + strlen(adminTelBuf) + 1;

		//证件类型
		char adminPaperType[1]={0x00};
		memcpy(adminPaperType,str5,1);
		aish[i].paperType = atoi(adminPaperType);//-----------------------------------------管理员证件类型
		/*if(0 == atoi(adminPaperType))
			m_listCtrlAdminMngr.SetItemText(nCount,4, _T("其他"));
		if(1 == atoi(adminPaperType))
			m_listCtrlAdminMngr.SetItemText(nCount,4, _T("身份证"));*/
		char *str6 = str5 + 2;

		//证件号码
		char adminPaperNum[32]={0x00};
		char *str_apn=strstr(str6,"|");
		memcpy(adminPaperNum,str6,str_apn-str6);
		memcpy(aish[i].paperNunber,adminPaperNum,strlen(adminPaperNum));//---------------------证件号码
		//m_listCtrlAdminMngr.SetItemText(nCount,5,CString(adminPaperNum));
		char *str7 = str6 + strlen(adminPaperNum) + 1;

		//编码后的公钥
		char pubKeyBuf[1024]={0x00};
		char *str_pubKey = strstr(str7,"|");
		memcpy(pubKeyBuf,str7,str_pubKey-str7);
		char *str8 = str7 + strlen(pubKeyBuf) + 1;

		CString maxNum;
		DEVKEYINFO devInfo={0x00};
		//if(1 == time/* && 1 == aTime_show*/)
		//{
		ret = Km_GetDevKeyInfo(hSessionHandle,&devInfo);
		if(ret)
		{
			char Gdki[100]={0x00};
			retValueParse(ret,Gdki);
			MessageBox(Gdki);
			break;
		}
		maxNum.Format("%d",devInfo.uiBakTotalKey);
		devAdmNum = devInfo.uiBakTotalKey;
		/*}
		else*/
		//maxNum.Format("%d",devAdmNum/*admCountInShow*/);
		aish[i].max = devAdmNum;
		//m_listCtrlAdminMngr.SetItemText(nCount,6,maxNum);//---------显示最大管理员数量

		//管理员类型
		char adminType[1]={0x00};
		char *str_adminType=strstr(str8,"|");
		memcpy(adminType,str8,1);
		CString admin_type;
		if(0 == atoi(adminType))
			admin_type = "系统管理员";
		if(1 == atoi(adminType))
			admin_type = "密钥管理员";

		char *str9 = str8 + 2;

		nCount++;
		source = str9;
	}
	delete puiAdminList;

	memcpy(admin_keyIndex,admin_index,sizeof(admin_index));
	for(int i = 0;i < 16;i++)
	{
		if(1 == admin_index[i][1])
		{
			admin_index_max = admin_index[i][0];
			break;
		}
	}

	//按照管理员索引查询
	CString k = 0;	
	nCount = 0;
	CString alg_cs;
	int kkkkkkey_index = _ttoi(admIndex);
	if(admName.IsEmpty() && !admIndex.IsEmpty())
	{
		for(int i = 0;i < 16;i++)
		{
			if(kkkkkkey_index == aish[i].index  && kkkkkkey_index != 0)
			{
				//id.Format("%d",1);
				m_listCtrlAdminMngr.InsertItem(0,0); 
				k.Format("%d",aish[i].index);
				m_listCtrlAdminMngr.SetItemText(0, 1,k);
				m_listCtrlAdminMngr.SetItemText(0, 2,aish[i].name);
				m_listCtrlAdminMngr.SetItemText(0, 3,aish[i].phone);
				CString pT;
				if(0 == aish[i].paperType)
					pT = "其他";
				if(1 == aish[i].paperType)
					pT = "身份证";
				m_listCtrlAdminMngr.SetItemText(0, 4,pT);
				m_listCtrlAdminMngr.SetItemText(0, 5,aish[i].paperNunber);
				CString max;
				max.Format("%d",aish[i].max);
				m_listCtrlAdminMngr.SetItemText(0, 6,max);

				break;
			}
		}
	}
	//按照管理员名称查询
	int id_int = 0;
	if(admIndex.IsEmpty())
	{
		for(int i = 0;i < 16;i++)
		{
			if(NULL != strstr(aish[i].name,admName))
			{
				//id.Format("%d",id_int);
				m_listCtrlAdminMngr.InsertItem(nCount,0); 
				k.Format("%d",aish[i].index);
				m_listCtrlAdminMngr.SetItemText(nCount, 1,k);
				m_listCtrlAdminMngr.SetItemText(nCount, 2,aish[i].name);
				m_listCtrlAdminMngr.SetItemText(nCount, 3,aish[i].phone);
				CString pT;
				if(0 == aish[i].paperType)
					pT = "其他";
				if(1 == aish[i].paperType)
					pT = "身份证";
				m_listCtrlAdminMngr.SetItemText(nCount, 4,pT);

				m_listCtrlAdminMngr.SetItemText(nCount, 5,aish[i].paperNunber);
				CString max;
				max.Format("%d",aish[i].max);
				m_listCtrlAdminMngr.SetItemText(nCount, 6,max);

				id_int++;
				nCount++;
			}
		}
	}
	BOOL isSearched = FALSE;
	//如果用户同时输入了密钥索引和应用名称，却不匹配
	if(!admIndex.IsEmpty() && !admName.IsEmpty())
	{
		for(int i = 0;i < 16;i++)
		{
			if(!strcmp(aish[i].name,admName) && kkkkkkey_index == aish[i].index)
			{
				//id.Format("%d",1);
				m_listCtrlAdminMngr.InsertItem(nCount,0); 
				k.Format("%d",aish[i].index);
				m_listCtrlAdminMngr.SetItemText(nCount, 1,k);
				m_listCtrlAdminMngr.SetItemText(nCount, 2,aish[i].name);
				m_listCtrlAdminMngr.SetItemText(nCount, 3,aish[i].phone);
				CString pT;
				if(0 == aish[i].paperType)
					pT = "其他";
				if(1 == aish[i].paperType)
					pT = "身份证";
				m_listCtrlAdminMngr.SetItemText(nCount, 4,pT);

				m_listCtrlAdminMngr.SetItemText(nCount, 5,aish[i].paperNunber);
				CString max;
				max.Format("%d",aish[i].max);
				m_listCtrlAdminMngr.SetItemText(nCount, 6,max);

				isSearched = TRUE;
				break;
			}
		}
		if(!isSearched)
		{
			MessageBox("查询条件不匹配或密码机中没有此项信息，请重新输入查询条件","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
}


void CDevAdminMngr::OnNMRClickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_RCLICK_adm));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}


void CDevAdminMngr::OnAddadm()
{
	// TODO: 在此添加命令处理程序代码
	CAdminGen adminGenDlg(admCountInShow,phHandle_adm);
	if(0 == admin_index_max)//如果没有已经占用的索引号@
	{
		adminGenDlg.adm_key_index_max = 1;
		int appKey_index[16][2]={0};//该数组第二列若为1，则表示第一列的索引号可以使用
		for(int j = 0;j < 2;j++)
		{
			for(int i = 1;i < 16;i++)
			{
				if(0 == j)
					appKey_index[i-1][j] = i;
				else
					appKey_index[i-1][j] = 1;//@则表示每一个索引号都能用
			}
		}
		memcpy(admin_keyIndex,appKey_index,sizeof(appKey_index));
		memcpy(adminGenDlg.adm_index_array,admin_keyIndex,sizeof(admin_keyIndex));//把该数组传递给生成界面的用于提供可选密钥索引的数组
	}
	else//如果已经存在占用的
	{
		adminGenDlg.adm_key_index_max = admin_index_max;//（此处曾出BUG）把可用的第一个赋给界面用于显示默认值的变量
		memcpy(adminGenDlg.adm_index_array,admin_keyIndex,sizeof(admin_keyIndex));//把可用的索引数组 传递给生成界面的用于提供可选密钥索引的数组
	}
	if(IDOK == adminGenDlg.DoModal())
	{
		admin_index_max++;
		CDevAdminMngr::ShowAdminInfo();
	}	
	//else
	//{
	//	memset(check_adm,0,256);
	//	i_checked_adm = 0;

	//	isCheckbox_adm = FALSE;
	//}
	
}


void CDevAdminMngr::OnUpdateadm()
{
	// TODO: 在此添加命令处理程序代码
	CString adm_index;
	CString adm_name;
	CString adm_phoneNum;
	CString adm_paperType;
	CString adm_paperNum;
	CString adm_maxNum;
	int nId;
	if(/*pos==NULL && */!isCheckbox_adm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*pos == NULL && */isCheckbox_adm)
	{
		if(isCheckbox_adm > 1)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_adm;
		}
	}
	
	//获取当前选中行每项信息
	adm_index = m_listCtrlAdminMngr.GetItemText(nId,1);
	if(adm_ind == atoi(adm_index))
	{
		MessageBox("不可对当前管理员进行操作！","警告",MB_ICONEXCLAMATION);
		return;
	}

	adm_name = m_listCtrlAdminMngr.GetItemText(nId,2);
	adm_phoneNum = m_listCtrlAdminMngr.GetItemText(nId,3);
	adm_paperType = m_listCtrlAdminMngr.GetItemText(nId,4);
	adm_paperNum = m_listCtrlAdminMngr.GetItemText(nId,5);
	adm_maxNum = m_listCtrlAdminMngr.GetItemText(nId,6);

	void * hSessionHandle = phHandle_adm;
	//unsigned int uiKeyIndexNum = 1;//1代表单选
	//unsigned int puiKeyIndex = atoi(adm_index);
	/*INT_PTR nRes = 0x00;
	nRes = MessageBox("确定要更新该密钥信息？","提示",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
		return;*/

	CAdminGen admGenDlg(adm_name,adm_index,adm_maxNum,adm_phoneNum,adm_paperType,adm_paperNum,hSessionHandle);
	/*appKeyGen.uig.index_uig = uiKeyIndexNum;
	appKeyGen.uig.index_uig_num = puiKeyIndex;*/
	//appKeyGen.keyIndex_max = index_max;//BUG所在！
	admin_keyIndex[0][0] = ADM_UPDATA;
	memcpy(admGenDlg.adm_index_array,admin_keyIndex,sizeof(admin_keyIndex));
	if(IDOK == admGenDlg.DoModal())
	{
		MessageBox("操作成功","提示");
		CDevAdminMngr::ShowAdminInfo();
		memset(check_adm,0,256);
		i_checked_adm = 0;

		isCheckbox_adm = FALSE;
	}
	
}


void CDevAdminMngr::OnDeladm()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox("删除","");
	INT_PTR nRes = 0x00;
	int ret = 0;
	void * hSessionHandle = phHandle_adm;
	unsigned int uiKeyIndexNum = 0;//
	unsigned int puiKeyIndex = 0;

	if(/*!count && */!isCheckbox_adm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*!count && */isCheckbox_adm)
	{
		if(1 == i_checked_adm)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_adm[0];
		}
		else if(1 < i_checked_adm)
		{
			MessageBox("管理员删除不支持多选！","提示",MB_ICONEXCLAMATION);
		}
	}
	nRes = MessageBox("警告！密码机最大管理员数量大于1时，需要至少一半以上管理员才能登录，管理员数量不足，将会导致无法登录！是否继续？","提示",MB_ICONEXCLAMATION | MB_OKCANCEL);;
	if(nRes != IDOK)
		return;
	if(adm_ind == puiKeyIndex)
	{
		MessageBox("不可对当前管理员进行操作！","警告",MB_ICONEXCLAMATION);
		return;
	}
	ret = Km_DelAdmin(hSessionHandle,puiKeyIndex);
	if(0 != ret)
	{
		char outDa[100]={0x00};
		retValueParse(ret,outDa);
		MessageBox("  删除失败"+(CString)outDa,"提示");
	}
	else
	{
		CDevAdminMngr::ShowAdminInfo();
		MessageBox("  操作成功！","提示");
		memset(check_adm,0,256);
		i_checked_adm = 0;

		isCheckbox_adm = FALSE;
	}
}


void CDevAdminMngr::OnLvnItemchangedDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_adm = TRUE;
		i_checked_adm++;
		CString str1,str2,str3;
		nId_row_adm = pNMLV->iItem;
		nId_row_adm_mux[i_checked_adm] = pNMLV->iItem;
		str2=m_listCtrlAdminMngr.GetItemText(pNMLV->iItem,1);//复选框选中时，取得其值
		for(int i = 0;i < i_checked_adm;i++)
		{
			if(check_adm[i] == 0)
				check_adm[i] = atoi(str2);
		}
		m_listCtrlAdminMngr.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//选中则高亮显示
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		//isCheckbox_adm = FALSE;
		CString str;
		nId_row_adm = 0;
		str=m_listCtrlAdminMngr.GetItemText(pNMLV->iItem,1);//复选框取消选中时，取得其值
		for(int i = 0;i < i_checked_adm;i++)
		{
			if(check_adm[i] == atoi(str))
				check_adm[i] = 0;
		}
		i_checked_adm--;
		if(i_checked_adm != 0)
			isCheckbox_adm = TRUE;
		else if(i_checked_adm == 0)
			isCheckbox_adm = FALSE;
		m_listCtrlAdminMngr.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//取消选中，则取消高亮显示
	}
}

void CDevAdminMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlAdminMngr); nItem++) 
	{
		//if(m_bHit)
		//{
		//	m_bHit = FALSE;
		//	break;
		//	//break;
		//}
		ListView_SetCheckState(m_listCtrlAdminMngr, nItem, fChecked);
	}
}

void CDevAdminMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_listCtrlAdminMngr); nItem++) 
	{
		
		if (!ListView_GetCheckState(m_listCtrlAdminMngr, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_listCtrlAdminMngr);
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

void CDevAdminMngr::OnItemstateiconclickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult)
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

void CDevAdminMngr::OnNMClickDevadminmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();  
    CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
    m_listCtrlAdminMngr.ScreenToClient(&point);  
    //定义结构体   
    LVHITTESTINFO lvinfo;  
    lvinfo.pt = point;  
    //获取行号信息   
    int nItem = m_listCtrlAdminMngr.HitTest(&lvinfo);  
    if(nItem != -1)  
    m_itemSel = lvinfo.iItem;   //当前行号  
	/*if(adm_ind == m_itemSel)
	{
		CString iiii;
		iiii.Format("%d",m_itemSel);
		MessageBox("别点这行！不可对当前使用管理员进行操作！","提示");
	}*/
  
    //判断是否点击在CheckBox上   
    /*if(lvinfo.flags == LVHT_ONITEMSTATEICON && adm_ind == m_itemSel) 
	{
		MessageBox("别点这行！不可对当前使用管理员进行操作！","提示");
		m_bHit = TRUE;  
	}*/
  
	*pResult = 0;

}


void CDevAdminMngr::OnBackupadm()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isSingle = FALSE;
	int nId = nId_row_adm;
	CString admin_name;
	INT_PTR nRes = 0x00;
	int ret = 0;
	unsigned int uiKeyIndexNum;//1代表单选
	unsigned int puiKeyIndex;

	unsigned int key_index_int[256]={0};

	if(/*!count && */!isCheckbox_adm)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(/*!count && */isCheckbox_adm)
	{
		if(1 == i_checked_adm)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_adm[0];
			admin_name = m_listCtrlAdminMngr.GetItemText(nId,2);
			isSingle = TRUE;
		}
		else if(1 < i_checked_adm)
		{
			//MessageBox("管理员删除不支持多选！","提示",MB_ICONEXCLAMATION);
			uiKeyIndexNum = i_checked_adm;
			memcpy(key_index_int,check_adm,i_checked_adm*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	BOOL isMux = FALSE;
	for(int i=0;i<i_checked_adm;i++)
	{
		if(key_index_int[i] == adm_ind)
		{
			isMux = TRUE;
			break;
		}
	}
	/*if(adm_ind == puiKeyIndex || isMux)
	{
		MessageBox("不可对当前管理员进行操作！","警告",MB_ICONEXCLAMATION);
		return;
	}*/
	//ret = Km_AdminBackup(hSessionHandle,uiAdminIndexNum,puiAdminIndex,pucAdminBak,puiAdminBakLength);
	if(isSingle)
	{
		CChoseFilePath choseFilePath(NULL,admin_name,NULL,uiKeyIndexNum,&puiKeyIndex,ADM_BACKUP,phHandle_adm);
		choseFilePath.DoModal();
	}
	else if(!isSingle)
	{
		CChoseFilePath choseFilePath(NULL,NULL,NULL,uiKeyIndexNum,key_index_int,ADM_BACKUP,phHandle_adm);
		choseFilePath.DoModal();
	}
	CDevAdminMngr::ShowAdminInfo();
	memset(check_adm,0,256);
	i_checked_adm = 0;

	/*if(isSingle)
		m_listCtrlAdminMngr.SetCheck(nId,FALSE);
	else if(!isSingle)
	{
		for(int i = 0;i < i_checked_adm;i++)
		{
			m_listCtrlAdminMngr.SetCheck(nId_row_adm_mux[i],FALSE);
		}
	}*/

	isCheckbox_adm = FALSE;
}
