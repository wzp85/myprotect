// AdminGen.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AdminGen.h"
#include "afxdialogex.h"

#include "InitKeyTip.h"
#include "ph_km.h"
#include "KeyDAO.h"
#include "MyUtil.h"
#define FILESIZE_SIGDEVADMIN 1024
#define ADM_UPDATA 777
int i_adm_log_num = 0;
unsigned int algID = 0;
unsigned int keyLength = 0;
// CAdminGen 对话框

IMPLEMENT_DYNAMIC(CAdminGen, CDialogEx)

CAdminGen::CAdminGen(int num,void *handle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminGen::IDD, pParent)
	, m_adminname(_T(""))
	, m_phoneNumber(_T(""))
	, m_paperNumber(_T(""))
	, m_adminpin(_T(""))
	, m_adminpincon(_T(""))
	, m_adminMaxCount(_T(""))
	, m_paperType_cs(_T("")/*)
	, m_adminType_cs(_T("")*/)
{
	phHandle = handle;
	admCountInGen = num;
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "宋体"));                 // lpszFacename
}

CAdminGen::CAdminGen(CString adm_name,CString adm_index,CString adm_maxNum,CString adm_phoneNum,CString adm_paperType,CString adm_paperNum,void *handle,CWnd* pParent/* = NULL*/)
		: CDialogEx(CAdminGen::IDD, pParent)
	, m_adminname(_T(""))
	, m_phoneNumber(_T(""))
	, m_paperNumber(_T(""))
	, m_adminpin(_T(""))
	, m_adminpincon(_T(""))
	, m_adminMaxCount(_T(""))
	, m_paperType_cs(_T("")/*)
	, m_adminType_cs(_T("")*/)
{
	phHandle = handle;
	adm_name_cs = adm_name;
	adm_index_in = atoi(adm_index);
	adm_maxNum_cs = adm_maxNum;
	adm_phoneNum_cs = adm_phoneNum;
	adm_paperType_cs = adm_paperType;
	adm_paperNum_cs = adm_paperNum;

	//memset(admin_keyIndex,0x00,);
	VERIFY(font.CreateFont(
    16,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_SEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    GB2312_CHARSET,            // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "宋体"));                 // lpszFacename
}

CAdminGen::~CAdminGen()
{
}

void CAdminGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THETITLE_STATIC, m_titleline);
	DDX_Text(pDX, IDC_ADMINNAME_EDIT, m_adminname);//-------管理员名
	DDX_Text(pDX, IDC_ADMINPHONE_EDIT, m_phoneNumber);
	DDX_Control(pDX, IDC_PAPERTYPE_COMBO, m_papertype);
	DDX_Text(pDX, IDC_PHONENUMBER_EDIT, m_paperNumber);
	DDX_Text(pDX, IDC_ADMINPIN_EDIT, m_adminpin);
	DDX_Text(pDX, IDC_ADMINPINCON_EDIT, m_adminpincon);
	DDX_Text(pDX, IDC_ADMINMAXCOUNT_EDIT, m_adminMaxCount);
	//	DDX_Control(pDX, IDC_ADMINTYPE_COMBO, m_adminType);
	DDX_CBString(pDX, IDC_PAPERTYPE_COMBO, m_paperType_cs);
	//	DDX_CBString(pDX, IDC_ADMINTYPE_COMBO, m_adminType_cs);
	DDX_Control(pDX, IDC_ADMINMAXCOUNT_EDIT, m_adm_max_count);
	DDX_Control(pDX, IDC_ADMINTYPE_COMBO, m_adminType);
	DDX_CBString(pDX,IDC_ADMINTYPE_COMBO, m_adminType_cs);
}

BOOL CAdminGen::OnInitDialog()
{
	/*CDialogEx::OnInitDialog();*/
	CDialogEx::OnInitDialog();
  

    // Add "About..." menu item to system menu.   
	
    // IDM_ABOUTBOX must be in the system command range.   
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
  
    // Set the icon for this dialog.  The framework does this automatically   
    //  when the application's main window is not a dialog   
    SetIcon(m_hIcon, TRUE);         // Set big icon   
    SetIcon(m_hIcon, FALSE);        // Set small icon   
  
    // TODO: Add extra initialization here  
	//设置CComBox下拉框为只读防止用户自己输入造成不必要的错误
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_ADMINTYPE_COMBO))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit1 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_PAPERTYPE_COMBO))->GetWindow(GW_CHILD));	
	pEdit1->SetReadOnly(TRUE);


	CWnd *cWnd = GetDlgItem(IDC_THETITLE_STATIC);
	cWnd->SetFont(&font);
	if(adm_index_array[0][0] == ADM_UPDATA)
	{
		cWnd->SetWindowText("更新管理员");
		SetDlgItemText(IDC_ADMINNAME_EDIT, m_adminname); 
		SetDlgItemText(IDC_ADMINPHONE_EDIT,adm_phoneNum_cs); 
		SetDlgItemText(IDC_PHONENUMBER_EDIT,adm_paperNum_cs); 
		SetDlgItemText(IDC_PAPERTYPE_COMBO,adm_paperType_cs); 
		SetDlgItemText(IDC_ADMINMAXCOUNT_EDIT,adm_maxNum_cs); 
		SetDlgItemText(IDC_ADMINTYPE_COMBO, _T("设备管理员"));
		m_adm_max_count.SetReadOnly(TRUE);
	}
	else
	{
		cWnd->SetWindowText("添加管理员");
		SetDlgItemText(IDC_PAPERTYPE_COMBO, _T("身份证"));
		SetDlgItemText(IDC_ADMINTYPE_COMBO, _T("设备管理员"));
		
	}
		
	 m_papertype.AddString(_T("身份证"));     
	 m_papertype.AddString(_T("其他")); 

	m_adminType.AddString(_T("设备管理员"));
	m_adminType.AddString(_T("密钥授权员"));
	m_adminType.AddString(_T("安全审计员"));

	//获取最大管理员数
	int ret = 0;
	DEVKEYINFO devInfo={0x00};
	char outString[100]={0x00};
	ret = Km_GetDevKeyInfo(phHandle,&devInfo);
	if(0 != ret)
	{
		retValueParse(ret,outString);
		MessageBox("获取设备密钥信息失败，错误码："+(CString)outString,"提示",MB_ICONEXCLAMATION);
		return TRUE;
	}
	algID = devInfo.uiAlgo;
	keyLength = devInfo.uiKeyLen;
	if(keyLength == 2048)
		keyLength = 1024;
	isAddOK = TRUE;
//	int admMax_forLogin = devInfo.uiBakTotalKey;
	i_adm_log_num = admCountInGen;
//	int i_adm_log_num = 0.5*admMax_forLogin+1;
	if(1 <= admCountInGen)
	{
		CString admz_num;
		admz_num.Format("%d",admCountInGen);
		SetDlgItemText(IDC_ADMINMAXCOUNT_EDIT,admz_num);
		m_adm_max_count.SetReadOnly(TRUE);
	}
//	if(i_adm_log_num >= admMax_forLogin)
		//isAddOK = FALSE;
    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CAdminGen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminGen::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAdminGen::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAdminGen::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAdminGen 消息处理程序


void CAdminGen::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("已生成"));
}


void CAdminGen::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	//数据校验部分
	if(m_adminname.IsEmpty())
	{
		MessageBox("姓名不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminname.GetLength() >= 20)
	{
		MessageBox("姓名太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if( m_phoneNumber.IsEmpty())
	{
		MessageBox("电话号码不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_phoneNumber.GetLength() >= 20)
	{
		MessageBox("电话号码长度不能超过20位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperNumber.IsEmpty())
	{
		MessageBox("证件号码不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperNumber.GetLength() >= 24)
	{
		MessageBox("证件号码太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperType_cs == "身份证"
		&& m_paperNumber.GetLength()!=18 
		&& m_paperNumber.GetLength() != 15)
	{
		MessageBox("身份证号码长度为15或18位，请输入合法的身份证号码！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin.IsEmpty())
	{
		MessageBox("请输入管理员PIN码！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin.GetLength()<6)
	{
		MessageBox("管理员PIN码不能小于6位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminpin != m_adminpincon)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminMaxCount.IsEmpty())
	{
		MessageBox("请输入最大管理员数！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	
	//---------格式化提示----------//
	INT_PTR nRes = 0;  
	int ret = 0;
	
	void * phSessionHandle = phHandle;//密码机会话句柄传递 
	ADMININFO AdminInfo = {0};
	if(adm_index_array[0][0] == ADM_UPDATA)
	{
		char outStrDelAdm[100]={0x00};
		ret = Km_DelAdmin(phSessionHandle,adm_index_in);
		if(0 != ret)
		{
			retValueParse(ret,outStrDelAdm);
			CString kkkk;
			kkkk.Format("%d",adm_index_in);
			MessageBox("销毁第"+kkkk+ "号管理员失败！错误码："+(CString)outStrDelAdm,"提示");
			return;
		}
	}
	int id_adm = 0;
	int num_adm = 0;
	ret = CMyUtil::GetAdminID(phSessionHandle,&id_adm,&num_adm);
	//CString iiiiiiiii;
	//iiiiiiiii.Format("%d",id_adm+1);
	//MessageBox("崩---------4++++++++++++++"+iiiiiiiii,"");
	if(!ret)
		AdminInfo.iAdminId = id_adm + 1;
	else
	{
		char outGetAdmList[100]={0x00};
		retValueParse(ret,outGetAdmList);
		MessageBox("获取管理员序列号失败,错误码："+(CString)outGetAdmList,"提示",MB_ICONWARNING | MB_OK);
		return;
	}
	//if(!isAddOK)
	if(1 != i_adm_log_num && num_adm == i_adm_log_num)
	{
		MessageBox("现有系统管理员数量不能超过最大管理员数量！","提示",MB_ICONEXCLAMATION);
		this->OnOK();
		return;
	}
	//读标签判断管理员类型
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(ret)
	{
		nRes = MessageBox("该操作将会格式化KEY，是否继续？","提示",MB_ICONEXCLAMATION|MB_OK);
		if(nRes == IDCANCEL)
			return;
	}
	if(!strcmp(label,"设备管理员"))
	{
		/*nRes = */MessageBox("设备管理员key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(!strcmp(label,"密钥授权员"))
	{
		/*nRes = */MessageBox("密钥授权员key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(!strcmp(label,"安全审计员"))
	{
		/*nRes = */MessageBox("安全审计员key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION);
		/*if(nRes != IDOK)*/
			return;
	}
	if(/*strcmp(label,"设备管理员") && */!strcmp(label,"密钥备份密钥"))
	{
		MessageBox("密钥备份密钥key不能被格式化！如果要格式化，请到载体管理模块做此操作！","提示",MB_ICONEXCLAMATION);
		return;
	}

	unsigned int uiAdminNum = atoi(m_adminMaxCount);
	unsigned char *pucPubKey = NULL;
	unsigned int uiPubKeyLen = 0;
	unsigned char pucSignValue[1024]={0x00};
	unsigned int puiSignValueLen = sizeof(pucSignValue);

	//格式化并获取公钥
	HAPPLICATION application;	
	RSAPUBLICKEYBLOB pBlob={0x00};
	ECCPUBLICKEYBLOB epPubKey={0x00};
	
	if(algID == SGD_RSA)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminpin,&application,&pBlob,NULL,keyLength);
	}
	else if(algID == SGD_SM2_1)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminpin,&application,NULL,&epPubKey,keyLength);
	}
	
	if(0 != ret && ret != SAR_NOTSUPPORTKEYTYPE)
	{
		MessageBox("生成公钥失败","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret)
	{
		MessageBox("您当前正在使用的KEY不支持SM2算法，请更换KEY重试或退出系统重新初始化！","检测到不支持",MB_ICONWARNING | MB_OK);
		return;
	}
	//else
	//{
	//	MessageBox("公钥生成成功");
	//}

	if(m_paperType_cs == "身份证")
		AdminInfo.iPaperType = 1;
	if(m_paperType_cs == "其他")
		AdminInfo.iPaperType = 0;

	AdminInfo.uiNameLen =m_adminname.GetLength();
	memset(AdminInfo.ucName,0x00,sizeof(AdminInfo.ucName));
	memcpy(AdminInfo.ucName,m_adminname.GetBuffer(),AdminInfo.uiNameLen);

	AdminInfo.uiTelephoneLen = m_phoneNumber.GetLength();
	memset(AdminInfo.ucTelephone,0x00,sizeof(AdminInfo.ucTelephone));
	memcpy(AdminInfo.ucTelephone,m_phoneNumber.GetBuffer(),AdminInfo.uiTelephoneLen);

	AdminInfo.uiPaperNumLen = m_paperNumber.GetLength();
	memset(AdminInfo.ucPaperNum,0x00,sizeof(AdminInfo.ucPaperNum));
	memcpy(AdminInfo.ucPaperNum,m_paperNumber.GetBuffer(),AdminInfo.uiPaperNumLen);

	unsigned int adminType = 0;//---------------------判断管理员类型

	if(m_adminType_cs == "设备管理员")
	{
		adminType = 0;
	}
	if(m_adminType_cs == "密钥授权员")
	{
		adminType = 1;
	}
	if(m_adminType_cs == "安全审计员")
	{
		adminType = 2;
	}


	if(algID == SGD_RSA)
	{
		/*pucPubKey =(unsigned char *)&pBlob;*/
		uiPubKeyLen = sizeof(RSAPUBLICKEYBLOB);
		pucPubKey = new unsigned char[uiPubKeyLen+1];
		memset(pucPubKey,0x00,uiPubKeyLen+1);
		memcpy(pucPubKey,(unsigned char *)&pBlob,uiPubKeyLen);
	}
	else if(algID == SGD_SM2_1)
	{
		//pucPubKey =(unsigned char *)&epPubKey;
		uiPubKeyLen = sizeof(ECCPUBLICKEYBLOB);
		pucPubKey = new unsigned char[uiPubKeyLen+1];
		memset(pucPubKey,0x00,uiPubKeyLen+1);
		memcpy(pucPubKey,(unsigned char *)&epPubKey,uiPubKeyLen);
	}

	ret = Km_GenAdmin(phSessionHandle,&AdminInfo,adminType,uiAdminNum,pucPubKey,uiPubKeyLen,pucSignValue,&puiSignValueLen);
	if(ret)
	{
		char outGenAdm[100]={0x00};
		retValueParse(ret,outGenAdm);
		MessageBox("服务器错误。错误码："+(CString)outGenAdm,"");
		return;
	}
	//写标签
	LPSTR szFileName_admin = "LBL_CERT_admin";
	//ret = CMyUtil::WriteLabel(szFileName_admin,pucSignValue,puiSignValueLen);
	ret = CMyUtil::WriteLabelEx(szFileName_admin,pucSignValue,puiSignValueLen,(char *)m_adminpin.GetString());
	if(ret)
	{
		MessageBox("写入签名值失败","提示");
		return;
	}

	//写入管理员序列号
	LPSTR szFileName_adminIndex = "LBL_CERT_adminIndex";
	CString adminID;
	adminID.Format("%d",AdminInfo.iAdminId);
	BYTE data_in[256]={0x00};
	memcpy(data_in,adminID.GetBuffer(),adminID.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_adminIndex,data_in,adminID.GetLength());
	ret = CMyUtil::WriteLabelEx(szFileName_adminIndex,data_in,adminID.GetLength(),(char *)m_adminpin.GetString());
	if(ret)
	{
		MessageBox("写入管理员序列号失败","提示");
		return;
	}

	//写入管理员标签
	LPSTR szFileName_USERNAME = "LBL_OTHER_LAB_USERNAME";
	CString adminLabel = m_adminType_cs;/*"设备管理员";*/
	BYTE data_in_label[256]={0x00};
	memcpy(data_in_label,adminLabel.GetBuffer(),adminLabel.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_USERNAME,data_in_label,12);
	ret = CMyUtil::WriteLabelEx(szFileName_USERNAME,data_in_label,12,(char *)m_adminpin.GetString());
	if(0 != ret)
	{
		MessageBox("写入管理员标签失败","提示");
		return;
	}
	else if(0 == ret && adm_index_array[0][0] != ADM_UPDATA)
	{
		MessageBox(_T("添加成功！"),_T(""));
	}
	CDialogEx::OnOK();
}


void CAdminGen::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
