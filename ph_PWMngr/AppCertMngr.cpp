// AppCertMngr.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertMngr.h"
#include "afxdialogex.h"
#include "AppCertKeyGen.h"


#include "MyUtil.h"
#include "ph_km.h"
#include "ReqInputKeyPwd.h"
#include "UserCertImport.h"

#include "DevKeyFirBac.h"
#include "ChoseFilePath.h"
#include "KeyDevide.h"
#include "APPKeyResume.h"
#include "APPKeyChangePIN.h"
#include "CheckKeyManager.h"
#include "AppCertOnline.h"
#include "AppCertKeySet.h"
#include "AppCertNtfIp.h"
#include "HttpSocket.h"
// CAppCertMngr 对话框
//int state=0;
IMPLEMENT_DYNAMIC(CAppCertMngr, CPropertyPage)

CAppCertMngr::CAppCertMngr()
	: CPropertyPage(CAppCertMngr::IDD)
	, m_AppCert_index_fors(_T(""))
	, m_AppCert_apname_fors(_T(""))
{
	keyIndex_appCert_max = 0;
}

CAppCertMngr::~CAppCertMngr()
{
}

void CAppCertMngr::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_APPCERTMNGR_LIST, m_AppCert);
	DDX_Text(pDX, IDC_CERTINDEXFORS_EDIT, m_AppCert_index_fors);
	DDX_Text(pDX, IDC_CERTNAMEFORS_EDIT, m_AppCert_apname_fors);
}


BEGIN_MESSAGE_MAP(CAppCertMngr, CPropertyPage)
	ON_BN_CLICKED(IDC_SEARCHCERTLIST_BUTTON, &CAppCertMngr::OnBnClickedSearchcertlistButton)
	ON_NOTIFY(NM_RCLICK, IDC_APPCERTMNGR_LIST, &CAppCertMngr::OnNMRClickAppcertmngrList)
	ON_COMMAND(ID__appCert_adk, &CAppCertMngr::OnAppcertAdk)
	ON_COMMAND(ID__appCert_greq, &CAppCertMngr::OnAppcertGreq)
	ON_COMMAND(ID__appCert_import, &CAppCertMngr::OnAppcertImport)
	ON_COMMAND(ID__appCert_backup, &CAppCertMngr::OnAppcertBackup)
	ON_COMMAND(ID__appCert_update, &CAppCertMngr::OnAppcertUpdate)
	ON_COMMAND(ID__appCert_resume, &CAppCertMngr::OnAppcertResume)
	ON_COMMAND(ID__appCert_distroy, &CAppCertMngr::OnAppcertDistroy)
	ON_COMMAND(ID__appCert_changePin, &CAppCertMngr::OnAppcertChangepin)
	ON_COMMAND(ID__appCert_export, &CAppCertMngr::OnAppcertExport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_APPCERTMNGR_LIST, &CAppCertMngr::OnLvnItemchangedAppcertmngrList)
	ON_NOTIFY(HDN_ITEMSTATEICONCLICK, 0, &CAppCertMngr::OnHdnItemStateIconClickAppcertmngrList)
//	ON_WM_TIMER()
ON_COMMAND(ID__APPCERT_online, &CAppCertMngr::OnAppcertOnline)
ON_COMMAND(ID__AppKeySet, &CAppCertMngr::OnAppkeyset)
ON_COMMAND(ID__AppKeyUpdate, &CAppCertMngr::OnAppkeyupdate)
ON_COMMAND(ID__AppCert_NTF, &CAppCertMngr::OnAppcertNtf)
END_MESSAGE_MAP()


// CAppCertMngr 消息处理程序


BOOL CAppCertMngr::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//SetTimer(1,10000,NULL);

	// TODO:  在此添加额外的初始化
	CRect rect;    
    m_AppCert.GetClientRect(&rect);   
    m_AppCert.SetExtendedStyle(m_AppCert.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);   

	//设置行高！
	CImageList img_list;
	img_list.Create(1,25,ILC_COLORDDB | ILC_MASK,0,0); 
	m_AppCert.SetImageList(&img_list,LVSIL_SMALL); 

	CRect temprect(0,0,780,400);   
	m_AppCert.SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);

	m_AppCert.InsertColumn(0,NULL,LVCFMT_CENTER,30);        //添加列标题
    m_AppCert.InsertColumn(1, _T("密钥索引"), LVCFMT_CENTER, 85, 1);   
    m_AppCert.InsertColumn(2, _T("应用名称"), LVCFMT_CENTER, 125, 2);   
    m_AppCert.InsertColumn(3, _T("算法名称"), LVCFMT_CENTER, 105, 3); 
	m_AppCert.InsertColumn(4, _T("长度"), LVCFMT_CENTER, 85, 4);
	m_AppCert.InsertColumn(5, _T("密钥类型"), LVCFMT_CENTER, 165, 5); 
	m_AppCert.InsertColumn(6, _T("最近修改时间"), LVCFMT_CENTER, 165, 6); 
//	m_AppCert.InsertColumn(7, _T("导出"), LVCFMT_CENTER, 90, 7); 

	HWND header = ListView_GetHeader(m_AppCert);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle |= HDS_CHECKBOXES;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	int m_HeaderId = ::GetDlgCtrlID(header);

	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	Header_GetItem(header, 0, &hdi);
	hdi.fmt |= HDF_CHECKBOX | HDF_FIXEDWIDTH;
	Header_SetItem(header, 0, &hdi);

	CAppCertMngr::ShowAppCertKeyInfo();

	isCheckbox_ac = FALSE;
	memset(check_ac,0,256);
	i_checked_ac = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAppCertMngr::CheckAllItems(BOOL fChecked) 
{
	for (int nItem = 0; nItem < ListView_GetItemCount(m_AppCert); nItem++) 
	{
		ListView_SetCheckState(m_AppCert, nItem, fChecked);
	}
}

void CAppCertMngr::SetHeaderCheckbox(void) 
{
	// Loop through all of our items.  If any of them are
	// unchecked, we'll want to uncheck the header checkbox.
	BOOL fChecked = TRUE;
	for (int nItem = 0; nItem < ListView_GetItemCount(m_AppCert); nItem++) 
	{
		if (!ListView_GetCheckState(m_AppCert, nItem)) 
		{
			fChecked = FALSE;
			break;
		}
	}
	// We need to get the current format of the header
	// and set or remove the HDF_CHECKED flag
	HWND header = ListView_GetHeader(m_AppCert);
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

void CAppCertMngr::OnNMRClickAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu menu,*pSubMenu;
	VERIFY(menu.LoadMenu (IDR_MENU_appCert));
	pSubMenu = menu.GetSubMenu(0);
//	ASSERT(pSubMenu != NULL);
	CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置 
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,myPoint.x, myPoint.y, this);
}

void CAppCertMngr::checkKeyManager(int *status,BYTE * pConfigData )
{
	CCheckKeyManager checkKMDlg;
	checkKMDlg.pConfigData=pConfigData;
	checkKMDlg.DoModal( );
	checkKMDlg.getCheckState(status);
}

void CAppCertMngr::OnAppcertAdk()
{
	// TODO: 在此添加命令处理程序代码
	
	/*if(state==-1)
	{
		MessageBox("请验证密钥管理员！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==0)
	{
		MessageBox("请验证密钥管理员！","",MB_ICONEXCLAMATION);
		return;
	}*/
	int state=0;
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥授权员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	CAppCertKeyGen appCertKeyGenDlg(phHandle,1);
	if(0 == keyIndex_appCert_max)//如果没有已经占用的索引号@
	{
		appCertKeyGenDlg.acKeyIndex = 1;
		int appKey_index[256][2]={0};//该数组第二列若为1，则表示第一列的索引号可以使用
		for(int j = 0;j < 2;j++)
		{
			for(int i = 1;i < 257;i++)
			{
				if(0 == j)
					appKey_index[i-1][j] = i;
				else
					appKey_index[i-1][j] = 1;//@则表示每一个索引号都能用
			}
		}
		memcpy(keyIndex_appCert,appKey_index,sizeof(appKey_index));
		memcpy(appCertKeyGenDlg.acKeyIndex_array,keyIndex_appCert,sizeof(keyIndex_appCert));//把该数组传递给生成界面的用于提供可选密钥索引的数组
	}
	else//如果已经存在占用的
	{
		appCertKeyGenDlg.acKeyIndex = keyIndex_appCert_max;//（此处曾出BUG）把可用的第一个赋给界面用于显示默认值的变量
		memcpy(appCertKeyGenDlg.acKeyIndex_array,keyIndex_appCert,sizeof(keyIndex_appCert));//把可用的索引数组 传递给生成界面的用于提供可选密钥索引的数组
	}
	if(IDOK == appCertKeyGenDlg.DoModal())
	{
		keyIndex_appCert_max++;
		CAppCertMngr::ShowAppCertKeyInfo();
	}
//	appCertKeyGenDlg.DoModal();
}


void CAppCertMngr::OnAppcertGreq()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	int ret = 0;
	void * hSessionHandle = phHandle;
	unsigned int puiKeyIndex;
	unsigned char *pucItem;
	unsigned int   uiItemLength;
	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			puiKeyIndex = check_ac[0];
		}
		else if(1 < i_checked_ac)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
	}

	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,NULL,&uiItemLength);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("服务器抽取本条记录失败"+(CString)outAkd,"提示");
		return;
	}
	pucItem = new unsigned char[uiItemLength+1];
	memset(pucItem,0x00,uiItemLength+1);
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,pucItem,&uiItemLength);
	if(0 != ret)
	{
		char outGAKI[100]={0x00};
		retValueParse(ret,outGAKI);
		MessageBox("服务器抽取本条记录失败"+(CString)outGAKI,"提示");
		delete []pucItem;
		return;
	}
	//解析字符串
	unsigned int uiAlgo;
	//unsigned int uiKeyLength;
	unsigned int uiHashAlgo;

	unsigned char CN_value[50]={0x00};
	unsigned char S_value[50]={0x00};
	unsigned char C_value[50]={0x00};
	unsigned char L_value[50]={0x00};
	unsigned char O_value[50]={0x00};
	unsigned char E_value[50]={0x00};
	unsigned char OU_value[50]={0x00};
	unsigned char keyIndexBuf[32]={0x00};
	unsigned int uiIndexLength;
	unsigned char algIdBuf[32]={0x00};

	char *itemInfo=(char*)pucItem;
	char *str = strstr(itemInfo,"ucBakTime");
	char *source = str + strlen("ucBakTime");

	char *id=strstr(source,"|");
	char idBuf[32]={0x00};
	int len = strlen(source)-strlen(id);
	memcpy(idBuf,source,len);
	char *str2 = source + len + 1;

	char *str_appName = strstr(str2,"|");
	memcpy(CN_value,str2,str_appName-str2);
	char *str3 = str2 + strlen((char*)CN_value) + 1;

	//---------------uiCityName----------------
	char *str_cityName = strstr(str3,"|");
	memcpy(S_value,str3,str_cityName-str3);
	//m_AppCert.SetItemText(nCount,3,cityName);
	char *str4 = str3 + strlen((char*)S_value)+1;

	//-----------------CNName------------------
	char *str_cnname = strstr(str4,"|");
	memcpy(C_value,str4,str_cnname-str4);
	char *str5 = str4 + strlen((char*)C_value)+1;
	//-----------------cuAreaName--------------

	char *str_areaName = strstr(str5,"|");
	memcpy(L_value,str5,str_areaName-str5);
	char *str6 = str5 + strlen((char*)L_value)+1;
	//-----------------ucAtName----------------

	char *str_atName = strstr(str6,"|");
	memcpy(O_value,str6,str_atName-str6);
	char *str7 = str6 + strlen((char*)O_value)+1;
	//-----------------ucEmail-----------------

	char *str_email = strstr(str7,"|");
	memcpy(E_value,str7,str_email-str7);
	char *str8 = str7 + strlen((char*)E_value)+1;

	char *str_OUvalue = strstr(str8,"|");
	memcpy(OU_value,str8,str_OUvalue-str8);
	char *str9 = str8 + strlen((char*)OU_value)+1;


	char *str_keyIndex = strstr(str9,"|");
	memcpy(keyIndexBuf,str9,str_keyIndex-str9);
	char *str10 = str9 + strlen((char*)keyIndexBuf) + 1;
	

	char *str_algId = strstr(str10,"|");
	memcpy(algIdBuf,str10,str_algId-str10);
	
	if(!strncmp((char*)algIdBuf,"65536",5))
	{
		uiAlgo = SGD_RSA;
		uiHashAlgo = SGD_SHA1;
	}
	else if(!strncmp((char*)algIdBuf,"131328",6))
	{
		uiAlgo = SGD_SM2_1;
		uiHashAlgo = SGD_SM3;
	}

	uiIndexLength = strlen((char*)keyIndexBuf);

	unsigned char pucRequest[1024]={0x00};
		/*
	memcpy(pucRequest,"C=",strlen("C="));
	strncat((char*)pucRequest,(char*)C_value,strlen((char*)C_value));

		strncat((char*)pucRequest,",S=",strlen(",S="));
	strncat((char*)pucRequest,(char*)S_value,strlen((char*)S_value));
	strncat((char*)pucRequest,",L=",strlen(",L="));
	strncat((char*)pucRequest,(char*)L_value,strlen((char*)L_value));
	strncat((char*)pucRequest,",O=",strlen(",O="));
	strncat((char*)pucRequest,(char*)O_value,strlen((char*)O_value));
	strncat((char*)pucRequest,",OU=",strlen(",OU="));
	strncat((char*)pucRequest,(char*)OU_value,strlen((char*)OU_value));
	*/
	strncat((char*)pucRequest,"C=CN,O=MOF,ST=01,L=00,L=00,T=11111",strlen(",C=CN,O=MOF,ST=01,L=00,L=00,T=11111"));
	strncat((char*)pucRequest,",CN=",strlen(",CN="));
	strncat((char*)pucRequest,(char*)CN_value,strlen((char*)CN_value));
	//strncat((char*)pucRequest,",E=",strlen(",E="));
	//strncat((char*)pucRequest,(char*)E_value,strlen((char*)E_value));
	
	
	printf("pucRequest == %s\n",pucRequest);
	unsigned int uiRequestLength = strlen((char*)pucRequest);
	unsigned char pucB64Req[10240]={0x00};
	unsigned char pucReq[10240]={0x00};


	unsigned char pucKeyPasswd[32]={0x00};
	unsigned int uiKeyPasswdLength;

	CReqInputKeyPwd reqInputKeyPwdDlg;
	if(IDOK == reqInputKeyPwdDlg.DoModal())
	{
		reqInputKeyPwdDlg.GetKeyPassword(pucKeyPasswd,&uiKeyPasswdLength);
	}
	else 
	{
		return;
	}

	ret = Sig_GenCertRequest(hSessionHandle,26115,uiHashAlgo,uiAlgo,uiIndexLength,keyIndexBuf,uiKeyPasswdLength,pucKeyPasswd,
							uiRequestLength,pucRequest,pucB64Req,pucReq);

	if(0 == ret)
	{
		//写文件
		CMyUtil::Write2File("C:\\pucB64Req.txt",pucB64Req,strlen((char*)pucB64Req));
		//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pucReq.txt",pucReq,strlen((char*)pucReq));
		MessageBox("证书请求生成成功，文件保存在C:\\pucB64Req.txt！","提示",MB_ICONEXCLAMATION);
	}
	else if(0 != ret)
	{
		char outGapkReq[100]={0x00};
		retValueParse(ret,outGapkReq);
		MessageBox("    证书请求生成失败"+(CString)outGapkReq,"提示");
	}
}


void CAppCertMngr::OnAppcertImport()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	int ret = 0;
	int nId = 0;
	void * hSessionHandle = phHandle;
	CString keytype;
	CString keyindex;
	CString AsymmAlg;
	int uiKeyType;
	int uiAsymmAlg=1;
	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(i_checked_ac > 1)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_ac;
		}
	}
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	keyindex = m_AppCert.GetItemText(nId,1);
	keytype = m_AppCert.GetItemText(nId,5);
	//MessageBox(keytype);


	if(keytype == "签名、加密共用密钥")
	{
		uiKeyType = 2;
	}
	if(keytype == "签名、加密不共用密钥")
	{
		uiKeyType = 3;
	}
	if(keytype == "签名密钥")
	{
		uiKeyType = 0;
	}
	if(keytype == "加密密钥")
	{
		uiKeyType = 1;
	}
	AsymmAlg = m_AppCert.GetItemText(nId,3);
	//MessageBox(AsymmAlg);
	if(AsymmAlg.Compare("RSA 1024")==0)
	{
		uiAsymmAlg = 1;
	}
	if(AsymmAlg.Compare("RSA 2048")==0)
	{
		uiAsymmAlg = 2;
	}
	if(AsymmAlg.Compare("SM2")==0)
	{
		uiAsymmAlg = 3;
	}
	CUserCertImport usrCertImportDlg(phHandle,atoi(keyindex),uiKeyType,uiAsymmAlg);
	usrCertImportDlg.DoModal();
}


void CAppCertMngr::OnAppcertBackup()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	BOOL isSingle = FALSE;
	int nId = nId_row_ac;
	CString keyIndex_i;
	CString appName_i;
	unsigned int uiKeyIndexNum;//1代表单选
	unsigned int puiKeyIndex;
	unsigned int key_index_int[256]={0};

	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_ac[0];
			appName_i = m_AppCert.GetItemText(nId,2);
			isSingle = TRUE;
		}
		else if(1 < i_checked_ac)
		{
			uiKeyIndexNum = i_checked_ac;
			memcpy(key_index_int,check_ac,i_checked_ac*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}

	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	CDevKeyFirBac devKeyFirBacDlg1(1,_T("请插入第一份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg1.DoModal())
		return;

	unsigned int B64KeyLen1=0;
	unsigned char B64Key1[256]={0x00};

	Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg1.keykek,devKeyFirBacDlg1.keykek_len,
		devKeyFirBacDlg1.key_sys,devKeyFirBacDlg1.key_sys_len,B64Key1,&B64KeyLen1);

	B64KeyLen1=B64KeyLen1-B64Key1[B64KeyLen1-1];
	memset(&B64Key1[B64KeyLen1],0x00,64);
	
	memset(sys_Key_1,0,256);
	unsigned int len_1=Km_Decode((char *)B64Key1,B64KeyLen1,(char *)sys_Key_1);

	CDevKeyFirBac devKeyFirBacDlg2(2,_T("请插入第二份密钥备份密钥"));
	if(IDOK != devKeyFirBacDlg2.DoModal())
		return;

	unsigned int B64KeyLen2=0;
	unsigned char B64Key2[256]={0x00};

	Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg2.keykek,devKeyFirBacDlg2.keykek_len,
		devKeyFirBacDlg2.key_sys,devKeyFirBacDlg2.key_sys_len,B64Key2,&B64KeyLen2);

	B64KeyLen2=B64KeyLen2-B64Key2[B64KeyLen2-1];
	memset(&B64Key2[B64KeyLen2],0x00,64);

	memset(sys_Key_2,0,256);
	unsigned int len_2=Km_Decode((char *)B64Key2,B64KeyLen2,(char *)sys_Key_2);

	CDevKeyFirBac devKeyFirBacDlg3(3,_T("请插入第三份密钥备份密钥"));
	if(devKeyFirBacDlg3.DoModal() == IDOK)
	{
		unsigned char key_in[32]={0x00};
		devKeyFirBacDlg3.GetRandomInKey(key_in);//得到key中的用于判断备份文件与备份密钥是否匹配的随机数

		unsigned int B64KeyLen3=0;
		unsigned char B64Key3[256]={0x00};

		Km_SymmCrypt(phHandle,1,0,devKeyFirBacDlg3.keykek,devKeyFirBacDlg3.keykek_len,
			devKeyFirBacDlg3.key_sys,devKeyFirBacDlg3.key_sys_len,B64Key3,&B64KeyLen3);

		B64KeyLen3=B64KeyLen3-B64Key3[B64KeyLen3-1];
		memset(&B64Key3[B64KeyLen3],0x00,64);

		memset(sys_Key_3,0,256);
		unsigned int len_3=Km_Decode((char *)B64Key3,B64KeyLen3,(char *)sys_Key_3);

		int ret = 0;
		unsigned char Keydata[256]={0};
		unsigned int Keydata_len = 0;

		ret = KeyMerge(sys_Key_1,len_1,sys_Key_2,len_2,sys_Key_3,len_3,Keydata,&Keydata_len);
		if(0 != ret || 16 != Keydata_len)
		{
			MessageBox("密钥合并出错！","提示");
			return;
		}
		//测试代码，可删除
//		char *path="C:\\key_after_merge_app.txt";
//		CMyUtil::Write2File(path,Keydata,Keydata_len);

		if(isSingle)
		{
			CChoseFilePath choseFilePath(key_in,appName_i,Keydata,uiKeyIndexNum,&puiKeyIndex,SIG_APPBAK,phHandle);
			choseFilePath.DoModal();
		}
		else if(!isSingle)
		{
			CChoseFilePath choseFilePath(key_in,NULL,Keydata,uiKeyIndexNum,key_index_int,SIG_APPBAK,phHandle);
			choseFilePath.DoModal();
		}
	}
	CAppCertMngr::ShowAppCertKeyInfo();
	memset(check_ac,0,256);
	i_checked_ac = 0;
	isCheckbox_ac = FALSE;
}


void CAppCertMngr::OnAppcertUpdate()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	int ret = 0;
	void * hSessionHandle = phHandle;
	unsigned int puiKeyIndex;
	unsigned char *pucItem;
	unsigned int   uiItemLength;

	char *pBegin,*pEnd;

	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			puiKeyIndex = check_ac[0];
		}
		else if(1 < i_checked_ac)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,NULL,&uiItemLength);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("服务器抽取本条记录失败"+(CString)outAkd,"提示");
		return;
	}
	pucItem = new unsigned char[uiItemLength+1];
	memset(pucItem,0x00,uiItemLength+1);
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,pucItem,&uiItemLength);
	if(0 != ret)
	{
		char outGAKI[100]={0x00};
		retValueParse(ret,outGAKI);
		MessageBox("服务器抽取本条记录失败"+(CString)outGAKI,"提示");
		delete []pucItem;
		return;
	}

//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\app.txt",pucItem,uiItemLength);

	unsigned int uiAlgo;
	//unsigned int uiKeyLength;

	unsigned char CN_value[50]={0x00};
	unsigned char S_value[50]={0x00};
	unsigned char C_value[50]={0x00};
	unsigned char L_value[50]={0x00};
	unsigned char O_value[50]={0x00};
	unsigned char E_value[50]={0x00};
	unsigned char OU_value[50]={0x00};
	unsigned char keyIndexBuf[32]={0x00};
	unsigned char algIdBuf[32]={0x00};

	char keyLength[32]={0x00};
	char keyType[32]={0x00};

	char *itemInfo=(char*)pucItem;
	char *str = strstr(itemInfo,"ucBakTime");
	char *source = str + strlen("ucBakTime");

	char *id=strstr(source,"|");
	char idBuf[32]={0x00};
	int len = strlen(source)-strlen(id);
	memcpy(idBuf,source,len);
	char *str2 = source + len + 1;

	char *str_appName = strstr(str2,"|");
	memcpy(CN_value,str2,str_appName-str2);
	char *str3 = str2 + strlen((char*)CN_value) + 1;

	//---------------uiCityName----------------
	char *str_cityName = strstr(str3,"|");
	memcpy(S_value,str3,str_cityName-str3);
	//m_AppCert.SetItemText(nCount,3,cityName);
	char *str4 = str3 + strlen((char*)S_value)+1;

	//-----------------CNName------------------
	char *str_cnname = strstr(str4,"|");
	memcpy(C_value,str4,str_cnname-str4);
	char *str5 = str4 + strlen((char*)C_value)+1;
	//-----------------cuAreaName--------------

	char *str_areaName = strstr(str5,"|");
	memcpy(L_value,str5,str_areaName-str5);
	char *str6 = str5 + strlen((char*)L_value)+1;
	//-----------------ucAtName----------------

	char *str_atName = strstr(str6,"|");
	memcpy(O_value,str6,str_atName-str6);
	char *str7 = str6 + strlen((char*)O_value)+1;
	//-----------------ucEmail-----------------

	char *str_email = strstr(str7,"|");
	memcpy(E_value,str7,str_email-str7);
	char *str8 = str7 + strlen((char*)E_value)+1;

	char *str_OUvalue = strstr(str8,"|");
	memcpy(OU_value,str8,str_OUvalue-str8);
	char *str9 = str8 + strlen((char*)OU_value)+1;
	MessageBox("OU_value=="+(CString)OU_value);


	char *str_keyIndex = strstr(str9,"|");
	memcpy(keyIndexBuf,str9,str_keyIndex-str9);
	char *str10 = str9 + strlen((char*)keyIndexBuf) + 1;
	

	char *str_algId = strstr(str10,"|");
	memcpy(algIdBuf,str10,str_algId-str10);
	pBegin=str10+strlen((char*)algIdBuf)+1;

	pEnd=strstr(pBegin,"|");
	memcpy(keyLength,pBegin,pEnd-pBegin);
	pBegin=pEnd+strlen("|");

	pEnd=strstr(pBegin,"|");
	memcpy(keyType,pBegin,pEnd-pBegin);
	pBegin=pEnd+strlen("|");

	CString algo;
	if(!strncmp((char*)algIdBuf,"65536",5) && atoi(keyLength)==1024)
	{
		uiAlgo = SGD_RSA;
		algo = "RSA 1024";
	}
	else if(!strncmp((char*)algIdBuf,"65536",5) && atoi(keyLength)==2048)
	{
		uiAlgo = SGD_RSA;
		algo = "RSA 2048";
	}
	else if(!strncmp((char*)algIdBuf,"131328",6))
	{
		uiAlgo = SGD_SM2_1;
		algo = "SM2"; 
	}

	CString keytype_cs;
	if(!strncmp("2",keyType,1))
		keytype_cs="签名、加密共用密钥";
	if(!strncmp("3",keyType,1))
		keytype_cs="签名、加密不共用密钥";
	if(!strncmp("1",keyType,1))
		keytype_cs="加密密钥";
	if(!strncmp("0",keyType,1))
		keytype_cs="签名密钥";

	//下一步修改构造函数传参isUp什么的。
	CAppCertKeyGen appCertKeyGenDlg(phHandle,0,CString(CN_value),CString(S_value),CString(C_value),CString(L_value),CString(O_value),CString(E_value),CString(OU_value),CString(keyIndexBuf),algo,keytype_cs);
	if(IDOK==appCertKeyGenDlg.DoModal())
	{
		CAppCertMngr::ShowAppCertKeyInfo();
		memset(check_ac,0,256);
		i_checked_ac = 0;
		isCheckbox_ac = FALSE;
	}
}


void CAppCertMngr::OnAppcertResume()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	CAPPKeyResume appKeyResume(phHandle,1);
	if(IDOK == appKeyResume.DoModal())
		CAppCertMngr::ShowAppCertKeyInfo();
}


void CAppCertMngr::OnAppcertDistroy()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	BOOL isSingle = FALSE;
	INT_PTR nRes = 0x00;
	int ret = 0;
	/*************先判断有没有选项*******************************/
	void * hSessionHandle = phHandle;
	unsigned int uiKeyIndexNum;//1代表单选
	unsigned int puiKeyIndex/* = atoi(keyIndex)*/;
	CString keyIndex_cs;

	unsigned int key_index_int[256]={0};

	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			uiKeyIndexNum = 1;//1个就表示单选
			puiKeyIndex = check_ac[0];
			isSingle = TRUE;
		}
		else if(1 < i_checked_ac)
		{
			uiKeyIndexNum = i_checked_ac;
			memcpy(key_index_int,check_ac,i_checked_ac*sizeof(unsigned int));
			isSingle = FALSE;
		}
	}
	/*************再验证密钥授权员************************/
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥授权员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	nRes = MessageBox("该操作不可逆，销毁后的数据将无法恢复，请确认是否继续？","提示",MB_ICONWARNING | MB_OKCANCEL);
	if(nRes != IDOK)
		return;
	if(isSingle)
		ret = Km_AppKeyDestroy(hSessionHandle,1,uiKeyIndexNum,&puiKeyIndex);
	else if(!isSingle)
		ret = Km_AppKeyDestroy(hSessionHandle,1,uiKeyIndexNum,key_index_int);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("  删除失败"+(CString)outAkd,"提示");
	}
	else
	{
		CAppCertMngr::ShowAppCertKeyInfo();
		MessageBox("操作成功！","提示",MB_ICONEXCLAMATION);
		memset(check_ac,0,256);
		i_checked_ac = 0;

		isCheckbox_ac = FALSE;
	}
}


void CAppCertMngr::OnAppcertChangepin()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	CString keyIndex;//先确定有没有选项再验证密钥授权员
	int nId;

	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(i_checked_ac > 1)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_ac;
		}
	}

	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	//获取当前选中行每项信息
	keyIndex = m_AppCert.GetItemText(nId,1);
	CAPPKeyChangePIN appKeyChangePin(phHandle,keyIndex);
	appKeyChangePin.DoModal();

	CAppCertMngr::ShowAppCertKeyInfo();
	memset(check_ac,0,256);
	i_checked_ac = 0;
	isCheckbox_ac = FALSE;
	m_AppCert.SetCheck(nId,FALSE);
	/*memset(check_ac,0,256);
	i_checked_ac = 0;

	m_AppCert.SetCheck(nId,FALSE);
	isCheckbox_ac = FALSE;*/
}


void CAppCertMngr::OnAppcertExport()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	//CAppCertMngr::checkKeyManager(&state);
	//if(state==-1)
	//{
	//	MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
	//	return;
	//}
	//else if(state==1)//放弃验证
	//{
	//	return;
	//}
	int ret=0;//先确定有没有选项再验证
	CString keyIndex;
	void * hSessionHandle=phHandle;
	unsigned int index=0;
	unsigned char *pucSigCert=NULL;
	unsigned int uiSigCertLength=0;
	unsigned char *pucEncCert=NULL;
	unsigned int uiEncCertLegnth=0;
	int nId;

	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(i_checked_ac > 1)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			nId = nId_row_ac;
		}
	}

	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}

	//获取当前选中行每项信息
	keyIndex = m_AppCert.GetItemText(nId,1);
	index = atoi((LPSTR)(LPCTSTR)keyIndex);

	ret = Sig_UserCertExport(hSessionHandle,index,pucSigCert,&uiSigCertLength,pucEncCert,&uiEncCertLegnth);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("导出证书失败"+(CString)outAkd,"提示");
		return;
	}
	pucSigCert=new unsigned char[uiSigCertLength+1];
	memset(pucSigCert,0x00,uiSigCertLength+1);
	pucEncCert=new unsigned char[uiEncCertLegnth+1];
	memset(pucEncCert,0x00,uiEncCertLegnth+1);
	ret = Sig_UserCertExport(hSessionHandle,index,pucSigCert,&uiSigCertLength,pucEncCert,&uiEncCertLegnth);
	if(0 != ret)
	{
		char outAkEPd[100]={0x00};
		retValueParse(ret,outAkEPd);
		MessageBox("导出证书失败"+(CString)outAkEPd,"提示");
		delete []pucSigCert;
		delete []pucEncCert;
		return;
	}
	CMyUtil::Write2File("C:\\SigCertExport.cer",pucSigCert,uiSigCertLength);
	CMyUtil::Write2File("C:\\EncCertExport.cer",pucEncCert,uiEncCertLegnth);
	MessageBox("导出成功！签名证书文件保存在C:\\SigCertExport.cer\r\n加密证书文件保存在C:\\EncCertExport.cer","提示",MB_ICONEXCLAMATION);
}


void CAppCertMngr::OnLvnItemchangedAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
	  ) 
	{ 
		isCheckbox_ac = TRUE;
		i_checked_ac++;
		CString str1,str2,str3;
		nId_row_ac = pNMLV->iItem;
		nId_row_mux_ac[i_checked_ac] = pNMLV->iItem;
		str2=m_AppCert.GetItemText(pNMLV->iItem,1);//复选框选中时，取得其值
		for(int i = 0;i < i_checked_ac;i++)
		{
			if(check_ac[i] == 0)
				check_ac[i] = atoi(str2);
		}
		m_AppCert.SetItemState(pNMLV->iItem, LVIS_SELECTED, LVIS_SELECTED);//选中则高亮显示
		
	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
	  && (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
	  ) 
	{ 
		CString str;
		nId_row_ac = 0;
		
		str=m_AppCert.GetItemText(pNMLV->iItem,1);//复选框取消选中时，取得其值
		for(int i = 0;i < i_checked_ac;i++)
		{
			if(check_ac[i] == atoi(str))
				check_ac[i] = 0;
		}
		i_checked_ac--;
		if(i_checked_ac != 0)
			isCheckbox_ac = TRUE;
		else if(i_checked_ac == 0)
			isCheckbox_ac = FALSE;
		m_AppCert.SetItemState(pNMLV->iItem, 0, LVIS_SELECTED);//取消选中，则取消高亮显示
	} 
}


void CAppCertMngr::OnHdnItemStateIconClickAppcertmngrList(NMHDR *pNMHDR, LRESULT *pResult)
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

void CAppCertMngr::ShowAppCertKeyInfo()
{
	m_AppCert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Km_AppKeyGetList(phHandle,1,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("获取应用密钥列表失败"+(CString)outAkgl,"提示",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_AppKeyGetList(phHandle,1,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("获取应用密钥列表失败"+(CString)outAkgl2,"提示",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGAppCertGetList.txt",puiKeyList,puiKeyListLen);

	if(0 == puiKeyListLen)
		return;
	//此处添加显示代码,把读出来的字符串解析后显示在listctrl中
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	int appKey_index[256][2]={0};//该数组第二列若为1，则表示第一列的索引号可以使用
	//初始化应用密钥索引数组，默认第二列均为1，表示第一列的索引号都可以使用
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

		time++;
		m_AppCert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------应用名称
		char *str_appName = strstr(str2,"|");
		if(str_appName == NULL)
		{
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
		m_AppCert.SetItemText(nCount, 2,appNameBuf);   
		char *str3 = str2 + strlen(appNameBuf) + 1;

		//从这里开始再解析5个char类型之后才是keyindex
		//---------------uiCityName----------------
		char cityName[50]={0x00};
		char *str_cityName = strstr(str3,"|");
		memcpy(cityName,str3,str_cityName-str3);
		//m_AppCert.SetItemText(nCount,3,cityName);
		char *str4 = str3 + strlen(cityName)+1;

		//-----------------CNName------------------
		char CNName[50]={0x00};
		char *str_cnname = strstr(str4,"|");
		memcpy(CNName,str4,str_cnname-str4);
		char *str5 = str4 + strlen(CNName)+1;
		//-----------------cuAreaName--------------
		char areaName[50]={0x00};
		char *str_areaName = strstr(str5,"|");
		memcpy(areaName,str5,str_areaName-str5);
		char *str6 = str5 + strlen(areaName)+1;
		//-----------------ucAtName----------------
		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;
		//-----------------ucEmail-----------------
		char Email[50]={0x00};
		char *str_email = strstr(str7,"|");
		memcpy(Email,str7,str_email-str7);
		char *str8 = str7 + strlen(Email)+1;

		char OUvalue[50]={0x00};
		char *str_OUvalue = strstr(str8,"|");
		memcpy(OUvalue,str8,str_OUvalue-str8);
		char *str9 = str8 + strlen(OUvalue)+1;

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str9,"|");
		memcpy(keyIndexBuf,str9,str_keyIndex-str9);
		m_AppCert.SetItemText(nCount, 1,keyIndexBuf); 
		//keyIndex[i] = atoi(keyIndexBuf);//---------------------把解析出的密钥索引放入数组
		for(int z=0;z<256;z++)
		{
			if(appKey_index[z][0] == atoi(keyIndexBuf))
				appKey_index[z][1]=0; //-------------------------把已经在用的密钥索引号标记为0，表示不可用
		}

		char *str10 = str9 + strlen(keyIndexBuf) + 1;
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str10,"|");
		memcpy(algIdBuf,str10,str_algId-str10);
		CString alg;
		
		char *str11 = str10 + strlen(algIdBuf) + 1;

		char keyLengthBuf[32]={0x00};
		char *str_keyLength = strstr(str11,"|");
		memcpy(keyLengthBuf,str11,str_keyLength-str11);
		m_AppCert.SetItemText(nCount, 4,keyLengthBuf);
		if(0 == strcmp(algIdBuf,"65536") && 1024 == atoi(keyLengthBuf))
			alg = "RSA 1024";
		if(0 == strcmp(algIdBuf,"65536") && 2048 == atoi(keyLengthBuf))
			alg = "RSA 2048";
		if(0 == strcmp(algIdBuf,"131328"))
			alg = "SM2";
		m_AppCert.SetItemText(nCount, 3,alg);
		char *str12 = str11 + strlen(keyLengthBuf) + 1;

		char keyType[1]={0x00};
		memcpy(keyType,str12,1);
		if(!strncmp("2",keyType,1))
			m_AppCert.SetItemText(nCount, 5, _T("签名、加密共用密钥"));
		if(!strncmp("3",keyType,1))
			m_AppCert.SetItemText(nCount, 5, _T("签名、加密不共用密钥"));
		if(!strncmp("1",keyType,1))
			m_AppCert.SetItemText(nCount, 5, _T("加密密钥"));
		if(!strncmp("0",keyType,1))
			m_AppCert.SetItemText(nCount, 5, _T("签名密钥"));

		char *str13 = str12 + 2;

		char *str14 = str13 + 2;

		char *str15 = str14 + 2;

		char timeBuf[32]={0x00};
		char *str_time = strstr(str14,"|");
		memcpy(timeBuf,str15,20);
		m_AppCert.SetItemText(nCount,6,timeBuf);
		char *str16 = str15 + strlen(timeBuf);

		nCount++;
		source = str16;
	}
	delete puiKeyList;

	m_AppCert.Scroll( CSize( 0, 100000 ) );
//	m_AppCert.SetItemState(m_AppCert.GetItemCount()–1,LVIS_ACTIVATING | LVIS_FOCUSED | LVIS_SELECTED,LVIS_SELECTED | LVIS_FOCUSED );
	//下面代码涉及添加代码界面中 密钥索引的显示
	memcpy(keyIndex_appCert,appKey_index,sizeof(appKey_index));//此时，密钥索引数组appKey_index已经采集了每一个索引号的可用状态
	//把密钥索引数组中 能用的第一个索引  赋值给index_max--->用于设置生成界面的默认值
	for(int i=0;i<256;i++)
	{
		if(1 == appKey_index[i][1])
		{
			keyIndex_appCert_max = appKey_index[i][0];
			break;
		}
	}
}

void CAppCertMngr::ShowAppCertKeyInfo_Search(CString appName,CString keyIndex_cs)
{
	m_AppCert.DeleteAllItems();
	int ret = 0;
	unsigned char *puiKeyList = NULL;
	unsigned int puiKeyListLen = 0;
	ret = Km_AppKeyGetList(phHandle,1,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl[100]={0x00};
		retValueParse(ret,outAkgl);
		MessageBox("获取应用密钥列表失败"+(CString)outAkgl,"提示",MB_ICONEXCLAMATION);
		return;
	}
	puiKeyList = new unsigned char[puiKeyListLen+1];
	memset(puiKeyList,0x00,puiKeyListLen+1);
	ret = Km_AppKeyGetList(phHandle,1,puiKeyList,&puiKeyListLen);
	if(0 != ret)
	{
		char outAkgl2[100]={0x00};
		retValueParse(ret,outAkgl2);
		MessageBox("获取应用密钥列表失败"+(CString)outAkgl2,"提示",MB_ICONEXCLAMATION);
		delete puiKeyList;
		return;
	}

//	CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\SIGAppCertGetList.txt",puiKeyList,puiKeyListLen);

	if(0 == puiKeyListLen)
		return;
	//此处添加显示代码,把读出来的字符串解析后显示在listctrl中
	char *keyList = (char *)puiKeyList;
	char *str = strstr(keyList,"ucBakTime");
	char *source = str + strlen("ucBakTime");
	CString id;

	ACSINFO acsinfo[256]={0x00};
	
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
		//m_AppCert.InsertItem(nCount,0); 
		
		char idBuf[32]={0x00};
		int len = strlen(source)-strlen(str1);
		memcpy(idBuf,source,len);
		char *str2 = source + len + 1;

		char appNameBuf[128]={0x00};//---------------------应用名称
		char *str_appName = strstr(str2,"|");
		if(str_appName == NULL)
		{
			break;
		}
		memcpy(appNameBuf,str2,str_appName-str2);
		memset(acsinfo[i].appName,0x00,64);
		memcpy(acsinfo[i].appName,str2,str_appName-str2);
		char *str3 = str2 + strlen(appNameBuf) + 1;

		//从这里开始再解析5个char类型之后才是keyindex
		//---------------uiCityName----------------
		char cityName[50]={0x00};
		char *str_cityName = strstr(str3,"|");
		memcpy(cityName,str3,str_cityName-str3);
		char *str4 = str3 + strlen(cityName)+1;

		//-----------------CNName------------------
		char CNName[50]={0x00};
		char *str_cnname = strstr(str4,"|");
		memcpy(CNName,str4,str_cnname-str4);
		char *str5 = str4 + strlen(CNName)+1;
		//-----------------cuAreaName--------------
		char areaName[50]={0x00};
		char *str_areaName = strstr(str5,"|");
		memcpy(areaName,str5,str_areaName-str5);
		char *str6 = str5 + strlen(areaName)+1;
		//-----------------ucAtName----------------
		char atName[50]={0x00};
		char *str_atName = strstr(str6,"|");
		memcpy(atName,str6,str_atName-str6);
		char *str7 = str6 + strlen(atName)+1;
		//-----------------ucEmail-----------------
		char Email[50]={0x00};
		char *str_email = strstr(str7,"|");
		memcpy(Email,str7,str_email-str7);
		char *str8 = str7 + strlen(Email)+1;

		char OUvalue[50]={0x00};
		char *str_OUvalue = strstr(str8,"|");
		memcpy(OUvalue,str8,str_OUvalue-str8);
		char *str9 = str8 + strlen(OUvalue)+1;

		char keyIndexBuf[32]={0x00};
		char *str_keyIndex = strstr(str9,"|");
		memcpy(keyIndexBuf,str9,str_keyIndex-str9);
		acsinfo[i].index=atoi(keyIndexBuf);
		//keyIndex[i] = atoi(keyIndexBuf);//---------------------把解析出的密钥索引放入数组
		

		char *str10 = str9 + strlen(keyIndexBuf) + 1;
		
		char algIdBuf[32]={0x00};
		char *str_algId = strstr(str10,"|");
		memcpy(algIdBuf,str10,str_algId-str10);
		memset(acsinfo[i].algid,0x00,32);
		memcpy(acsinfo[i].algid,str10,str_algId-str10);
		CString alg;
		
		char *str11 = str10 + strlen(algIdBuf) + 1;

		char keyLengthBuf[32]={0x00};
		char *str_keyLength = strstr(str11,"|");
		memcpy(keyLengthBuf,str11,str_keyLength-str11);
		memset(acsinfo[i].keyLen,0x00,32);
		memcpy(acsinfo[i].keyLen,str11,str_keyLength-str11);

		char *str12 = str11 + strlen(keyLengthBuf) + 1;

		char keyType[1]={0x00};
		memcpy(keyType,str12,1);
		memset(acsinfo[i].keyType,0x00,32);
		memcpy(acsinfo[i].keyType,str12,1);

		char *str13 = str12 + 2;

		char *str14 = str13 + 2;

		char *str15 = str14 + 2;

		char timeBuf[32]={0x00};
		char *str_time = strstr(str14,"|");
		memcpy(timeBuf,str15,20);
		memset(acsinfo[i].optime,0x00,32);
		memcpy(acsinfo[i].optime,str15,20);
		char *str16 = str15 + strlen(timeBuf);

		nCount++;
		source = str16;
	}
	delete puiKeyList;

	//按照密钥索引查询
	CString k = 0;	
	nCount = 0;
	CString alg_cs;
	int kkkkkkey_index = _ttoi(keyIndex_cs);
	if(appName.IsEmpty() && !keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(kkkkkkey_index == acsinfo[i].index)
			{
				m_AppCert.InsertItem(0,0); 
				k.Format("%d",acsinfo[i].index);
				m_AppCert.SetItemText(0, 1,k);
				m_AppCert.SetItemText(0, 2,acsinfo[i].appName);
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(acsinfo[i].algid,"131328"))
					alg_cs = "SM2";
				m_AppCert.SetItemText(0, 3,alg_cs);

				m_AppCert.SetItemText(0, 4,acsinfo[i].keyLen);

				if(!strncmp("2",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密共用密钥"));
				if(!strncmp("3",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密不共用密钥"));
				if(!strncmp("1",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("加密密钥"));
				if(!strncmp("0",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名密钥"));

				m_AppCert.SetItemText(0,6,acsinfo[i].optime);
				break;
			}
		}
	}
	//按照应用名称查询
	int id_int = 0;
	if(keyIndex_cs.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(NULL != strstr(acsinfo[i].appName,appName))
			{
				m_AppCert.InsertItem(nCount,0); 
				k.Format("%d",acsinfo[i].index);
				m_AppCert.SetItemText(0, 1,k);
				m_AppCert.SetItemText(nCount, 2,acsinfo[i].appName);
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(acsinfo[i].algid,"131328"))
					alg_cs = "SM2";
				m_AppCert.SetItemText(nCount, 3,alg_cs);
				m_AppCert.SetItemText(nCount, 4,acsinfo[i].keyLen);

				if(!strncmp("2",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密共用密钥"));
				if(!strncmp("3",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密不共用密钥"));
				if(!strncmp("1",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("加密密钥"));
				if(!strncmp("0",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名密钥"));

				m_AppCert.SetItemText(nCount,6,acsinfo[i].optime);

				id_int++;
				nCount++;
			}
		}
	}
	BOOL isSearched = FALSE;
	//如果用户同时输入了密钥索引和应用名称，却不匹配
	if(!keyIndex_cs.IsEmpty() && !appName.IsEmpty())
	{
		for(int i = 0;i < 256;i++)
		{
			if(!strcmp(acsinfo[i].appName,appName) && kkkkkkey_index == acsinfo[i].index)
			{
				m_AppCert.InsertItem(0,0); 
				k.Format("%d",acsinfo[i].index);
				m_AppCert.SetItemText(0, 1,k);
				m_AppCert.SetItemText(0, 2,acsinfo[i].appName);
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"1024"))
					alg_cs = "RSA 1024";
				if(!strcmp(acsinfo[i].algid,"65536") && !strcmp(acsinfo[i].keyLen,"2048"))
					alg_cs = "RSA 2048";
				if(!strcmp(acsinfo[i].algid,"131328"))
					alg_cs = "SM2";
				m_AppCert.SetItemText(0, 3,alg_cs);

				m_AppCert.SetItemText(0, 4,acsinfo[i].keyLen);

				if(!strncmp("2",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密共用密钥"));
				if(!strncmp("3",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名、加密不共用密钥"));
				if(!strncmp("1",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("加密密钥"));
				if(!strncmp("0",acsinfo[i].keyType,1))
					m_AppCert.SetItemText(nCount, 5, _T("签名密钥"));

				m_AppCert.SetItemText(0,6,acsinfo[i].optime);

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

void CAppCertMngr::OnBnClickedSearchcertlistButton()
{
	UpdateData(TRUE);
	
	CString appName = m_AppCert_apname_fors;
	CString keyIndex = m_AppCert_index_fors;
	if(appName.IsEmpty() && keyIndex.IsEmpty())
	{
		CAppCertMngr::ShowAppCertKeyInfo();
	}
	else
	{
		CAppCertMngr::ShowAppCertKeyInfo_Search(appName,keyIndex);
	}
}


//void CAppCertMngr::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if(nIDEvent==1)
//		CAppCertMngr::checkKeyManager(&state);
//	CPropertyPage::OnTimer(nIDEvent);
//}

int OperateJaRA(LPCTSTR DlServerIP, int DlPort,LPCTSTR subjectSN,
	                     
						   LPCTSTR pkcs10,LPCTSTR OrganID,char * CertIP ,int CertIPLen
			         ,char * CertPort ,int CertPortLen,char *encCert,char *sigCert,char *encPubKey, char *encPriKey , int * encType,
					 LPCTSTR   object
) 
{
	CHttpSocket myHttpSocket;
	CString getRequestData2;
	int ret = 0;
	BYTE buf[81920] ={0};
	PKI_DATA getresponsedata = {0,NULL};
	getresponsedata.value = buf;
	getresponsedata.size=81920;
	PKI_DATA tmp= {0,NULL};

	


	
	PKI_DATA data = {0,NULL};
	data.size=  strlen(subjectSN);
	data.value = new BYTE[data.size+1];
	memset(data.value,0,data.size+1);
	memcpy(data.value,subjectSN,strlen(subjectSN));
	tmp.size=(data.size/3)*4;
	if(data.size%3>0)
		tmp.size=tmp.size+1*4;
	tmp.value=new BYTE[tmp.size+1];
	memset(tmp.value,0,tmp.size+1);
	ret=encode((char *)data.value,data.size,(char *)tmp.value);

	if(data.value)
		delete data.value;
	data.size=  strlen(pkcs10)+strlen(OrganID)+4+2+tmp.size+2+CertIPLen+2+CertIPLen;
	data.value = new BYTE[data.size+1];
	memset(data.value,0,data.size+1);
	memcpy(data.value,tmp.value,tmp.size);
	memcpy(data.value+tmp.size,(char *)"||",2);
	memcpy(data.value+tmp.size+2,pkcs10,strlen(pkcs10));
	memcpy(data.value+tmp.size+2+strlen(pkcs10),(char *)"||",2);
	memcpy(data.value+tmp.size+2+strlen(pkcs10)+2,OrganID,strlen(OrganID));
	memcpy(data.value+tmp.size+2+strlen(pkcs10)+2+strlen(OrganID),(char *)"||",2);
	memcpy(data.value+tmp.size+2+strlen(pkcs10)+2+strlen(OrganID)+2,CertIP,CertIPLen);
	memcpy(data.value+tmp.size+2+strlen(pkcs10)+2+strlen(OrganID)+2+CertIPLen,(char *)"||",2);
	memcpy(data.value+tmp.size+2+strlen(pkcs10)+2+strlen(OrganID)+2+CertIPLen+2,CertPort,CertPortLen);
	//getRequestData2 = tmp.value;

	PKI_DATA data64 = {0,NULL};
	//对生成的证书请求进行编码
	

	getRequestData2 = data.value;
	//CMyUtil::Write2File("C:\\ab64.txt",data64.value,data64.size);

	//连接签发代理发出请求并接受数据	
	ret = myHttpSocket.StartClient((char *)DlServerIP, DlPort,getRequestData2, &getresponsedata,(LPTSTR)object);
    if(ret != 0)
	{
		if(data64.value)
			delete data64.value;
		return ret;
	}
	if(data64.value)
		delete data64.value;
	char *start ,* end;
	
	
	//CMyUtil::Write2File("C:\\getresponsedata.txt",getresponsedata.value,getresponsedata.size);
	if(*encType==0)
	{
		start=(char *)getresponsedata.value;

	    end=strstr((char *)start,"||");
	   if(end ==NULL)
		   return -1;
	   memcpy(sigCert,start,end-start);
		start= end +strlen("||");
		//end=strstr((char *)start,"||");
		end= (char *)getresponsedata.value+getresponsedata.size;
	
		memcpy(encCert,start,end-start);
	}

  
	
	if(*encType==1)
	{

		start=(char *)getresponsedata.value;

		end=strstr((char *)start,"||");
	    if(end ==NULL)
		   return -1;
		memcpy(sigCert,start,end-start);
		start= end +strlen("||");
			end=strstr((char *)start,"||");
		
		memcpy(encCert,start,end-start);
		start= end +strlen("||");
		end= (char *)getresponsedata.value+getresponsedata.size;
		memcpy(encPriKey,start,end-start);
	}
	return ret;
}

void CAppCertMngr::OnAppcertOnline()
{
	// TODO: 在此添加命令处理程序代码
	int state = 0;
	int ret = 0;
	void * hSessionHandle = phHandle;
	unsigned int puiKeyIndex;
	unsigned char *pucItem;
	unsigned int   uiItemLength;
	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			puiKeyIndex = check_ac[0];
		}
		else if(1 < i_checked_ac)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
	}

	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,NULL,&uiItemLength);
	if(0 != ret)
	{
		char outAkd[100]={0x00};
		retValueParse(ret,outAkd);
		MessageBox("服务器抽取本条记录失败"+(CString)outAkd,"提示");
		return;
	}
	pucItem = new unsigned char[uiItemLength+1];
	memset(pucItem,0x00,uiItemLength+1);
	ret = Sig_GetItemAppKeyInfo(hSessionHandle,puiKeyIndex,pucItem,&uiItemLength);
	if(0 != ret)
	{
		char outGAKI[100]={0x00};
		retValueParse(ret,outGAKI);
		MessageBox("服务器抽取本条记录失败"+(CString)outGAKI,"提示");
		delete []pucItem;
		return;
	}
	//解析字符串
	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	unsigned int uiHashAlgo;

	unsigned char CN_value[50]={0x00};
	unsigned char S_value[50]={0x00};
	unsigned char C_value[50]={0x00};
	unsigned char L_value[50]={0x00};
	unsigned char O_value[50]={0x00};
	unsigned char E_value[50]={0x00};
	unsigned char OU_value[50]={0x00};
	unsigned char keyIndexBuf[32]={0x00};
	unsigned int uiIndexLength;
	unsigned char algIdBuf[32]={0x00};

	char *itemInfo=(char*)pucItem;
	char *str = strstr(itemInfo,"ucBakTime");
	char *source = str + strlen("ucBakTime");

	char *id=strstr(source,"|");
	char idBuf[32]={0x00};
	int len = strlen(source)-strlen(id);
	memcpy(idBuf,source,len);
	char *str2 = source + len + 1;

	char *str_appName = strstr(str2,"|");
	memcpy(CN_value,str2,str_appName-str2);
	char *str3 = str2 + strlen((char*)CN_value) + 1;

	//---------------uiCityName----------------
	char *str_cityName = strstr(str3,"|");
	memcpy(S_value,str3,str_cityName-str3);
	//m_AppCert.SetItemText(nCount,3,cityName);
	char *str4 = str3 + strlen((char*)S_value)+1;

	//-----------------CNName------------------
	char *str_cnname = strstr(str4,"|");
	memcpy(C_value,str4,str_cnname-str4);
	char *str5 = str4 + strlen((char*)C_value)+1;
	//-----------------cuAreaName--------------

	char *str_areaName = strstr(str5,"|");
	memcpy(L_value,str5,str_areaName-str5);
	char *str6 = str5 + strlen((char*)L_value)+1;
	//-----------------ucAtName----------------

	char *str_atName = strstr(str6,"|");
	memcpy(O_value,str6,str_atName-str6);
	char *str7 = str6 + strlen((char*)O_value)+1;
	//-----------------ucEmail-----------------

	char *str_email = strstr(str7,"|");
	memcpy(E_value,str7,str_email-str7);
	char *str8 = str7 + strlen((char*)E_value)+1;

	char *str_OUvalue = strstr(str8,"|");
	memcpy(OU_value,str8,str_OUvalue-str8);
	char *str9 = str8 + strlen((char*)OU_value)+1;


	char *str_keyIndex = strstr(str9,"|");
	memcpy(keyIndexBuf,str9,str_keyIndex-str9);
	char *str10 = str9 + strlen((char*)keyIndexBuf) + 1;
	

	char *str_algId = strstr(str10,"|");
	memcpy(algIdBuf,str10,str_algId-str10);
	

	if(!strncmp((char*)algIdBuf,"65536",5))
	{
		uiAlgo = SGD_RSA;
		uiHashAlgo = SGD_SHA1;
	}
	else if(!strncmp((char*)algIdBuf,"131328",6))
	{
		uiAlgo = SGD_SM2_1;
		uiHashAlgo = SGD_SM3;
	}

	
	
	//跳转到在线证书请求页面并获取证书标准和URL.ip及端口号
	CAppCertOnline appCertOnlineDlg;
	if(IDOK == appCertOnlineDlg.DoModal())
	{	
		/*****************************************************************************************/
		ret = appCertOnlineDlg.GetURLandType(standard_type,&standardtypeLength,cert_url,
			&certurllength,certip,&certiplength,certport,&certportlength,&type);
		if(type == 1)//财政部
		{
			
			appCertOnlineDlg.GetURLandType(standard_type,&standardtypeLength,cert_url,
			&certurllength,certip,&certiplength,certport,&certportlength,&type);
		}
		else{//普华和税务
			appCertOnlineDlg.GetURLandType(standard_type,&standardtypeLength,cert_url,
			&certurllength,certip,&certiplength,certport,&certportlength,&type);
		}

	/********************************************************************/
		if(0 == ret)
		{	
			//生成证书请求
			uiIndexLength = strlen((char*)keyIndexBuf);
			unsigned char pucRequest[1024]={0x00};
			memcpy(pucRequest,"C=",strlen("C="));
			strncat((char*)pucRequest,(char*)C_value,strlen((char*)C_value));
			strncat((char*)pucRequest,",S=",strlen(",S="));
			strncat((char*)pucRequest,(char*)S_value,strlen((char*)S_value));
			strncat((char*)pucRequest,",L=",strlen(",L="));
			strncat((char*)pucRequest,(char*)L_value,strlen((char*)L_value));
			strncat((char*)pucRequest,",O=",strlen(",O="));
			strncat((char*)pucRequest,(char*)O_value,strlen((char*)O_value));
			strncat((char*)pucRequest,",OU=",strlen(",OU="));
			strncat((char*)pucRequest,(char*)OU_value,strlen((char*)OU_value));
			strncat((char*)pucRequest,",CN=",strlen(",CN="));
			strncat((char*)pucRequest,(char*)CN_value,strlen((char*)CN_value));
			strncat((char*)pucRequest,",E=",strlen(",E="));
			strncat((char*)pucRequest,(char*)E_value,strlen((char*)E_value));
			//printf("pucRequest == %s\n",pucRequest);
			unsigned int uiRequestLength = strlen((char*)pucRequest);
			unsigned char pucB64Req[1024]={0x00};
			unsigned char pucReq[1024]={0x00};


			unsigned char pucKeyPasswd[32]={0x00};
			unsigned int uiKeyPasswdLength;

			CReqInputKeyPwd reqInputKeyPwdDlg;
			if(IDOK == reqInputKeyPwdDlg.DoModal())
			{
				reqInputKeyPwdDlg.GetKeyPassword(pucKeyPasswd,&uiKeyPasswdLength);
			}
			else 
			{
				return;
			}
			ret = Sig_GenCertRequest(hSessionHandle,26115,uiHashAlgo,uiAlgo,uiIndexLength,keyIndexBuf,uiKeyPasswdLength,pucKeyPasswd,
									uiRequestLength,pucRequest,pucB64Req,pucReq);

			if(0 != ret)
			{
				char outGapkReq[100]={0x00};
				retValueParse(ret,outGapkReq);
				MessageBox("    证书请求生成失败"+(CString)outGapkReq,"提示");
				return ;
			}

		
			int encType=1;

			unsigned char encCert[4096]={0x00};
			unsigned char SigCert[4096]={0x00};
			unsigned char encPriKey[4096]={0x00};
			unsigned char encPubKey[4096]={0x00};
			int encCertLen ,SigCertLen,encKeyLen;
			if(type == 1)//财政部   
			{
				unsigned char pucSubject[1024]={0x00};
				memcpy(pucSubject,"CN=",strlen("CN="));
				strncat((char*)pucSubject,(char*)CN_value,strlen((char*)CN_value));
				strncat((char*)pucSubject,",OU=",strlen(",OU="));
			    strncat((char*)pucSubject,(char*)OU_value,strlen((char*)OU_value));
				strncat((char*)pucSubject,",O=",strlen(",O="));
		    	strncat((char*)pucSubject,(char*)O_value,strlen((char*)O_value));
				strncat((char*)pucSubject,",C=",strlen(",C="));
			    strncat((char*)pucSubject,(char*)C_value,strlen((char*)C_value));
	            char *strcRequesStart =  strstr((char *)pucB64Req,"-----BEGIN NEW CERTIFICATE REQUEST-----\r\n");
			    char *strcRequesEnd =  strstr((char *)pucB64Req,"-----END NEW CERTIFICATE REQUEST-----\r\n");
			    unsigned char pucRequestBase64[2048]={0x00};
				memcpy(pucRequestBase64,strcRequesStart+strlen("-----BEGIN NEW CERTIFICATE REQUEST-----\r\n"),strcRequesEnd-2-(strcRequesStart+strlen("-----BEGIN NEW CERTIFICATE REQUEST-----\r\n")));
				if(uiAlgo==SGD_RSA)
				 {
					  encType=0;
					  ret = OperateJaRA(szIP, 8080,(LPCTSTR)pucSubject ,(LPCTSTR)pucRequestBase64,"1160",(char *)certip,certiplength,(char *)certport,certportlength,(char *)encCert,(char *)SigCert,(char *)encPubKey,(char *)encPriKey,&encType,(LPCTSTR)"/webRSA/RsaRA");
				}
			 if(uiAlgo==SGD_SM2_1)
			 {
				 encType=1;
				  ret = OperateJaRA(szIP, 8080,(LPCTSTR)pucSubject ,(LPCTSTR)pucRequestBase64,"1160",(char *)certip,certiplength,(char *)certport,certportlength,(char *)encCert,(char *)SigCert,(char *)encPubKey,(char *)encPriKey,&encType,(LPCTSTR)"/webSM2/Sm2RA");
			 }
			}
			   if(ret!=0)
			{
				char outGapkReq[100]={0x00};
				retValueParse(ret,outGapkReq);
				MessageBox("    证书签发失败和RSA通讯失败"+(CString)outGapkReq,"提示");
				return ;
			}
				   
			//CMyUtil::Write2File("C:\\encCert.cer",encCert,strlen((char *)encCert));
			//CMyUtil::Write2File("C:\\SigCert.cer",SigCert,strlen((char *)SigCert));
			//CMyUtil::Write2File("C:\\encPriKey.txt",encPriKey,strlen((char *)encPriKey));
			//CMyUtil::Write2File("C:\\encPubKey.txt",encPubKey,strlen((char *)encPubKey));		
			
			unsigned char encCertDecode[4096]={0x00};
			unsigned char SigCertDecode[4096]={0x00};
			unsigned char encPriKeyDecode[4096]={0x00};
			unsigned char encPubKeyDecode[4096]={0x00};
			int encCertDecodeLen ,SigCertDecodeLen,encPriKeyDecodeLen=0,encPubKeyDecodeLen=0;
			encCertDecodeLen=Km_Decode((char *)encCert,strlen((char *)encCert),(char *)encCertDecode);
			SigCertDecodeLen=Km_Decode((char *)SigCert,strlen((char *)SigCert),(char *)SigCertDecode);
			encPriKeyDecodeLen=Km_Decode((char *)encPriKey,strlen((char *)encPriKey),(char *)encPriKeyDecode);
			//CMyUtil::Write2File("C:\\encPriKeyDecode.txt",encPriKeyDecode,encPriKeyDecodeLen);		

			//encPubKeyDecodeLen=Km_Decode((char *)encPubKey,strlen((char *)encPubKey),(char *)encPubKeyDecode);

			if(encType==0||encType==1)  //符合财政部接口的数据
               ret = Sig_ImportEncCert(hSessionHandle,uiAlgo,uiIndexLength,keyIndexBuf,uiKeyPasswdLength,pucKeyPasswd,encCertDecodeLen,encCertDecode,SigCertDecodeLen,SigCertDecode,encPubKeyDecodeLen,encPubKeyDecode,encPriKeyDecodeLen,encPriKeyDecode,encType);

			
			//CMyUtil::Write2File("C:\\encCertDecode.cer",encCertDecode,encCertDecodeLen);
			//CMyUtil::Write2File("C:\\SigCertDecode.cer",SigCertDecode,SigCertDecodeLen);
			//CMyUtil::Write2File("C:\\encPriKeyDecode.txt",encPriKeyDecode,encPriKeyDecodeLen);
			//CMyUtil::Write2File("C:\\encPubKeyDecode.txt",encPubKeyDecode,encPubKeyDecodeLen);
			if(ret==0)
				MessageBox("操作成功！","提示",MB_ICONEXCLAMATION);
			else
				MessageBox("操作失败！","提示",MB_ICONEXCLAMATION);

			
			//证书请求及证书标准信息。调用在线证书签发接口


		}
	}
}
void CAppCertMngr::OnAppkeyset()
{
	// TODO: 在此添加命令处理程序代码

	int state=0;
	
	unsigned int puiKeyIndex;
	
	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			puiKeyIndex = check_ac[0];
		}
		else if(1 < i_checked_ac)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	
	CAppCertKeySet AppCertKeySet(phHandle,1,puiKeyIndex );
	if(IDOK != AppCertKeySet.DoModal())
	{
		return ;
	}
	
}


void CAppCertMngr::OnAppkeyupdate()
{
	// TODO: 在此添加命令处理程序代码
	int state=0;
	unsigned int puiKeyIndex;
	
	if(!isCheckbox_ac)
	{
		MessageBox(_T("请至少选择一行记录！"),_T(""),MB_ICONEXCLAMATION);
		return;
	}
	else if(isCheckbox_ac)
	{
		if(1 == i_checked_ac)
		{
			puiKeyIndex = check_ac[0];
		}
		else if(1 < i_checked_ac)
		{
			MessageBox("该功能不支持多选！","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	
	CAppCertMngr::checkKeyManager(&state,pConfigData);
	if(state==-1)
	{
		MessageBox("验证密钥管理员失败！","",MB_ICONEXCLAMATION);
		return;
	}
	else if(state==1)//放弃验证
	{
		return;
	}
	
	CAppCertKeySet AppCertKeySet(phHandle,2,puiKeyIndex );
	if(IDOK != AppCertKeySet.DoModal())
	{
		return ;
	}
}


void CAppCertMngr::OnAppcertNtf()
{
	// TODO: 在此添加命令处理程序代码
	 CAppCertNtfIp appCertNtfIp(phHandle,NULL);
	 if(IDOK != appCertNtfIp.DoModal())
	{
		return ;
	}
}
