// SignPWMAdmin.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "SignPWMAdmin.h"
#include "afxdialogex.h"

#include "InitKeyTip.h"
#include "ph_PWMngrDlg.h"
#include "DAI.h"
#define PWMMNGR_CAPTION _T("上海普华密码机管理系统")
#define FILESIZE_SIGDEVADMIN 1024
#include "ph_km.h"
#include "MyUtil.h"
#include "KeyDAO.h"
#include "InitDevInfo.h"
#include "IsInit.h"


// CSignPWMAdmin 对话框

BYTE adm_bkRand_1[32]={0x00};
BYTE adm_bkRand_2[32]={0x00};
BYTE adm_bkRand_3[32]={0x00};
BYTE adm_bkRand_4[32]={0x00};
BYTE adm_bkRand_5[32]={0x00};

int KeyMnGer_SQ=0;//判断config.txt里是否签发授权员
int KeyMnGer_AQ=0;//判断config.txt里是否签发安全审计员
IMPLEMENT_DYNAMIC(CSignPWMAdmin, CDialogEx)

CSignPWMAdmin::CSignPWMAdmin(int isOneToMore,int isKeyManager,int keyManagerNum,int isReSig,int keylen,int n_Count,CString data,void *key_handle,void *hSessionHandle,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSignPWMAdmin::IDD, pParent)
	, m_adminName(_T(""))
	, m_adminPhonenumber(_T(""))
	, m_adminPaperNum(_T(""))
	, m_adminPwd(_T(""))
	, m_adminConPwd(_T(""))
	, m_maxAdminNum(_T(""))
	, m_paperType_CS(_T(""))
	, m_caption(_T(""))
{
	isKMer=isKeyManager;
	KMerNumber=keyManagerNum;
	isReSigAdmin = isReSig;
	isOneToMore_kmer=isOneToMore;//该变量用来判断是否属于1对多策略

	isReadOnly = FALSE;
	phSHandle = hSessionHandle;
	key_phSHandle = key_handle;
	if(!data.IsEmpty())
		m_caption = data;
	else
		m_caption = "签发管理员";
	admin_count = 0;
	adminNum = n_Count;
	key_length = keylen;
}

CSignPWMAdmin::~CSignPWMAdmin()
{
}

void CSignPWMAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADMINNAME_EDIT, m_adminName);
	DDX_Text(pDX, IDC_ADMINPHONE_EDIT, m_adminPhonenumber);
	DDX_Text(pDX, IDC_ADMINPAPNUM_EDIT, m_adminPaperNum);
	DDX_Text(pDX, IDC_ADMINPWD_EDIT, m_adminPwd);
	DDX_Text(pDX, IDC_ADMINCONPWD_EDIT, m_adminConPwd);
	DDX_Text(pDX, IDC_MAXADMINCOUNT_EDIT, m_maxAdminNum);
	DDX_Control(pDX, IDC_PAPERTYPE_COMBO, m_paperType);
	DDX_CBString(pDX, IDC_PAPERTYPE_COMBO, m_paperType_CS);
	DDX_Text(pDX, IDC_STATIC_adm, m_caption);
	DDX_Control(pDX, IDC_MAXADMINCOUNT_EDIT, m_adminCount);
}

BOOL CSignPWMAdmin::OnInitDialog()
{
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
	CWnd *cWnd = GetDlgItem(IDC_ADMINNAME_EDIT);
	cWnd->SetFocus();

	isTwoPro = 0;

    m_paperType.AddString(_T("身份证"));       
    m_paperType.AddString(_T("其他"));   
 
    SetDlgItemText(IDC_PAPERTYPE_COMBO, _T("身份证"));  
	if(!m_caption.IsEmpty())
		SetDlgItemText(IDC_STATIC_adm,m_caption);

	if(isKMer==0)//设备管理员显示
	{
		CString admin_count_cs;
		if(0 != admin_count)
		{
			admin_count_cs.Format("%d",admin_count);
			SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,admin_count_cs);
			m_adminCount.SetReadOnly(isReadOnly);
		}
		else
		{
			admin_count_cs.Format("%d",1);
			SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,admin_count_cs);
		}
		/***********设备管理员必须签发故在此处判断是否签发授权员及审计员，并以全局变量的形式限定后面的签发状态**********************/

			int length=0;
			//int KeyMnGer_SQ=0;
			
			CMyUtil::ReadData("./config.txt",NULL,&length);
			BYTE *data = new BYTE[length+1];
			memset(data,0x00,length+1);
			CMyUtil::ReadData("./config.txt",data,&length);

			/*********************密钥授权员**********************/
			char *source=(char*)data;
			char *str_SQ=strstr(source,"KEY_MANAGER_SQ=");//判断是否签发密钥授权员（密钥授权员固定一个）
			char *tem_SQ=str_SQ+strlen("KEY_MANAGER_SQ=");
			char *end_SQ=strstr(tem_SQ,"\n");
			char num_buf_SQ[32]={0x00};
			memcpy(num_buf_SQ,tem_SQ,end_SQ-tem_SQ);
			KeyMnGer_SQ=atoi(num_buf_SQ);

			char *str_AQ=strstr(source,"KEY_MANAGER_AQ=");//判断是否签发安全审计员（固定一个）
			char *tem_AQ=str_AQ+strlen("KEY_MANAGER_AQ=");
			char *end_AQ=strstr(tem_AQ,"\n");
			char num_buf_AQ[32]={0x00};
			memcpy(num_buf_AQ,tem_AQ,end_AQ-tem_AQ);
			KeyMnGer_AQ=atoi(num_buf_AQ);
			
		}




	else if(isKMer==2)//签发安全审计员读取配置文件判断数目
	{
		//从配置文件读取安全审计员的最大数量,设置显示
		int length=0;
//		int KMerNumber=0;

		CMyUtil::ReadData("./config.txt",NULL,&length);
		BYTE *data = new BYTE[length+1];
		memset(data,0x00,length+1);
		CMyUtil::ReadData("./config.txt",data,&length);
	

		char *source=(char*)data;
		char *str=strstr(source,"KEY_MANAGER_AQ_NUM=");
		char *tem=str+strlen("KEY_MANAGER_AQ_NUM=");
		char *end=strstr(str,"\n");
		char num_buf[32]={0x00};
		memcpy(num_buf,tem,end-tem);
//		KMerNumber=atoi(num_buf);
		SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,num_buf);
	}
	else if(isKMer==1)//签发密钥授权员读取配置文件判断数目
	{
		//从配置文件读取密钥授权员的最大数量,设置显示
		int length=0;
//		int KMerNumber=0;

		CMyUtil::ReadData("./config.txt",NULL,&length);
		BYTE *data = new BYTE[length+1];
		memset(data,0x00,length+1);
		CMyUtil::ReadData("./config.txt",data,&length);


		char *source=(char*)data;
		char *str=strstr(source,"KEY_MANAGER_SQ_NUM=");
		char *tem=str+strlen("KEY_MANAGER_SQ_NUM=");
		char *end=strstr(str,"\n");
		char num_buf[32]={0x00};
		memcpy(num_buf,tem,end-tem);
//		KMerNumber=atoi(num_buf);
		SetDlgItemText(IDC_MAXADMINCOUNT_EDIT,num_buf);
	}
 
    return FALSE;  // return TRUE  unless you set the focus to a control   

}

BEGIN_MESSAGE_MAP(CSignPWMAdmin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSignPWMAdmin::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_PAPERTYPE_COMBO, &CSignPWMAdmin::OnCbnSelchangePapertypeCombo)
END_MESSAGE_MAP()


// CSignPWMAdmin 消息处理程序


void CSignPWMAdmin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	void * phSessionHandle = phSHandle;//密码机会话句柄传递 
	ADMININFO AdminInfo = {0};
	unsigned int uiAdminNum = atoi(m_maxAdminNum);
//	adm_Count = uiAdminNum;
	num_adm_max = atoi(m_maxAdminNum);
	if(num_adm_max>1)
		isOneToMore_kmer=1;
	unsigned char *pucPubKey;
	unsigned int uiPubKeyLen;
	unsigned char pucSignValue[1024]={0x00};
	unsigned int puiSignValueLen = 1024;

	//数据校验部分
	if(m_adminName.IsEmpty())
	{
		MessageBox("姓名不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminName.GetLength() >= 20)
	{
		MessageBox("姓名不超过20个字符！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPhonenumber.IsEmpty())
	{
		MessageBox("电话号码不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPhonenumber.GetLength() >= 20)
	{
		MessageBox("电话号码长度不能超过20位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPaperNum.IsEmpty())
	{
		MessageBox("证件号码不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPaperNum.GetLength() >= 24)
	{
		MessageBox("证件号码不超过20个字符！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_paperType_CS == "身份证"
		&& m_adminPaperNum.GetLength() != 18 
		&& m_adminPaperNum.GetLength() != 15)
	{
		MessageBox("身份证号码长度为15或18位，请输入合法的身份证号码！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd.IsEmpty())
	{
		MessageBox("请输入管理员PIN码！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd.GetLength()<6)
	{
		MessageBox("管理员PIN码不能小于6位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_adminPwd != m_adminConPwd)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_maxAdminNum.IsEmpty())
	{
		MessageBox("请输入最大管理员数！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	//---------格式化提示----------//
	INT_PTR nRes;               

	int ret = 0;
	//读标签
	char label[32]={0x00};
	ret = CMyUtil::ReadLabel("LBL_OTHER_LAB_USERNAME",label);
	if(1 == ret)
	{
		MessageBox("打开设备失败，请确定key是否插好！","提示",MB_ICONEXCLAMATION);
		return;
	}
	else if(3 == ret)
	{
		nRes = MessageBox("该操作将会格式化key，确定要格式化？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"密钥备份密钥"))
	{
		MessageBox("您插入的是密钥备份密钥key，该key不能被格式化！请确认插入管理员key！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(!strcmp(label,"设备管理员"))
	{
		nRes = MessageBox("该key是设备管理员key，确定要格式化并重新生成？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"密钥授权员"))
	{
		nRes = MessageBox("该key是密钥授权员key，确定要格式化并重新生成？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	if(!strcmp(label,"安全审计员"))
	{
		nRes = MessageBox("该key是安全审计员key，确定要格式化并重新生成？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
			return;
	}
	//如签发多个管理员，此处用于判断插入的是不是已经写入过的管理员key
	BOOL isReWrite = FALSE;
	if(1 < uiAdminNum && 1 < adminNum)
	{
		char label_admin_signText[17]={0x00};
		ret = CMyUtil::ReadLabel("LBL_CERT_admin_RANDOM",label_admin_signText);
		if(0 != ret)
		{
			nRes = MessageBox("您插入的不是本系统key，确定要格式化？","提示",MB_ICONWARNING | MB_OKCANCEL);
			if(nRes != IDOK)
				return;
		}
		if(2 == adminNum && !strncmp(label_admin_signText,(const char*)adm_bkRand_1,16))
		{
			isReWrite = TRUE;
		}
		if(3 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)))
		{
			isReWrite = TRUE;
		}
		if(4 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_3,16)))
		{
			isReWrite = TRUE;
		}
		if(5 == adminNum && (!strncmp(label_admin_signText,(const char*)adm_bkRand_1,16) 
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_2,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_3,16)
			|| !strncmp(label_admin_signText,(const char*)adm_bkRand_4,16)))
		{	
			isReWrite = TRUE;
		}
		if(isReWrite)
		{
			MessageBox("您插入的是刚刚写入过的管理员key，请换下一个管理员key继续！","",MB_ICONEXCLAMATION);
			return;
		}
	}

	//获取管理员信息列表，来确定该管理员的序列号
	int id_adm = 0;
	int num_adm = 0;
	ret = CMyUtil::GetAdminID(phSessionHandle,&id_adm,&num_adm);
	if(0 == ret)
		AdminInfo.iAdminId = id_adm + 1;
	else
	{
		char outGAI[100]={0x00};
		retValueParse(ret,outGAI);
		MessageBox("获取管理员序列号失败"+(CString)outGAI,"提示",MB_ICONWARNING | MB_OK);
		return;
	}
	//重新签发时删除已经存在的管理员
	if(1 == isReSigAdmin)
	{
		while(0 < id_adm)
		{
			ret = Km_DelAdmin(phSessionHandle,id_adm);
			if(0 != ret)
			{
				char outDA[100]={0x00};
				retValueParse(ret,outDA);
				MessageBox("删除管理员失败"+(CString)outDA,"提示",MB_ICONWARNING | MB_OK);
			}
			id_adm--;
		}
		AdminInfo.iAdminId = 1;
	}
	
	//获取公钥
	unsigned int algId_DevKey;
	HAPPLICATION application;	
	RSAPUBLICKEYBLOB pBlob={0x00};
	ECCPUBLICKEYBLOB epPubKey={0x00};
	DEVKEYINFO devInfo={0x00};
	ret = Km_GetDevKeyInfo(phSessionHandle,&devInfo);
	if(0 != ret)
	{
		char outGdki[100]={0x00};
		retValueParse(ret,outGdki);
		MessageBox("获取设备密钥信息失败，无法签发管理员！"+(CString)outGdki,"提示",MB_ICONEXCLAMATION);
		return;
	}
	algId_DevKey = devInfo.uiAlgo;
	key_length = devInfo.uiKeyLen;
	if(key_length == 2048)
		key_length = 1024;
	if(SGD_RSA == algId_DevKey)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminPwd,&application,&pBlob,NULL,key_length);
		//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\pubkey_4.txt",(unsigned char*)&pBlob,sizeof(RSAPUBLICKEYBLOB));
	}
	else if(SGD_SM2_1 == algId_DevKey)
	{
		ret = CMyUtil::GetPubKey((LPSTR)(LPCTSTR)m_adminPwd,&application,NULL,&epPubKey,key_length);
	}
	if(0 != ret && ret != SAR_NOTSUPPORTKEYTYPE)
	{
		MessageBox("生成公钥失败","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret && 1 == adminNum)
	{
		this->OnOK();
		MessageBox("您当前正在使用的KEY不支持SM2算法，请在生成设备密钥界面选择RSA算法并重新签发此管理员！","检测到不支持",MB_ICONINFORMATION | MB_OK);
		isTwoPro = 2;
		/*CInitDevInfo initDevInfoDlg(NULL,NULL);
		initDevInfoDlg.DoModal();*/
		return;
		
	}
	else if(SAR_NOTSUPPORTKEYTYPE == ret && 1 < adminNum)
	{
		INT_PTR nRes = 0;
		nRes = MessageBox("很抱歉，您当前正在使用的KEY支持的算法与设备密钥的算法不一致。请选择是否要重新换KEY以继续生成此管理员，选择“取消”将会重新初始化","检测到不支持",MB_ICONEXCLAMATION | MB_OKCANCEL);
		if(nRes == IDOK)
			isTwoPro = 0;
		else if(nRes != IDOK)
			isTwoPro = 1;
		return;
	}

	if(m_paperType_CS == "身份证")
		AdminInfo.iPaperType = 1;
	if(m_paperType_CS == "其他")
		AdminInfo.iPaperType = 0;

	AdminInfo.uiNameLen = m_adminName.GetLength();
	memset(AdminInfo.ucName,0x00,sizeof(AdminInfo.ucName));
	memcpy(AdminInfo.ucName,m_adminName.GetBuffer(),AdminInfo.uiNameLen);

	AdminInfo.uiTelephoneLen = m_adminPhonenumber.GetLength();
	memset(AdminInfo.ucTelephone,0x00,sizeof(AdminInfo.ucTelephone));
	memcpy(AdminInfo.ucTelephone,m_adminPhonenumber.GetBuffer(),AdminInfo.uiTelephoneLen);

	AdminInfo.uiPaperNumLen = m_adminPaperNum.GetLength();
	memset(AdminInfo.ucPaperNum,0x00,sizeof(AdminInfo.ucPaperNum));
	memcpy(AdminInfo.ucPaperNum,m_adminPaperNum.GetBuffer(),AdminInfo.uiPaperNumLen);


	unsigned int adminType;
	if(isKMer==0)
		adminType=0;//0表示设备管理员
	else if(isKMer==1)
		adminType=1;//1表示密钥授权员
	else if(isKMer==2)
		adminType=2;//2表示安全审计员

	if(SGD_RSA == algId_DevKey)
	{
		pucPubKey =(unsigned char *)&pBlob;
		uiPubKeyLen = sizeof(RSAPUBLICKEYBLOB);
	}
	else if(SGD_SM2_1 == algId_DevKey)
	{
		pucPubKey = (unsigned char *)&epPubKey;
		uiPubKeyLen = sizeof(ECCPUBLICKEYBLOB);
	}

	ret = Km_GenAdmin(phSessionHandle,&AdminInfo,adminType,uiAdminNum,pucPubKey,uiPubKeyLen,pucSignValue,&puiSignValueLen);
	if(0 != ret)
	{
		char outGa[100]={0x00};
		retValueParse(ret,outGa);
		MessageBox("服务端签发管理员失败"+(CString)outGa);
		return;
	}

    LPSTR szFileName_admin = "LBL_CERT_admin";
	//ret = CMyUtil::WriteLabel(szFileName_admin,pucSignValue,puiSignValueLen);
	ret = CMyUtil::WriteLabelEx(szFileName_admin,pucSignValue,puiSignValueLen,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		CString str_ret;
		str_ret.Format("%d",ret);
		MessageBox("写入签名值失败:=="+str_ret,"提示");
		return;
	}

	unsigned char random[256]={0x00};
	ret = Km_Random(random,16);

	LPSTR szFileName_admin_RANDOM = "LBL_CERT_admin_RANDOM";
	//ret = CMyUtil::WriteLabel(szFileName_admin_RANDOM,random,16);
	ret = CMyUtil::WriteLabelEx(szFileName_admin_RANDOM,random,16,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入管理员随机数标签失败","提示");
		return;
	}
	//生成的随机数标签存入缓存
	if(1 < uiAdminNum)
	{
		if(1 == adminNum) memcpy(adm_bkRand_1,random,16);
		if(2 == adminNum) memcpy(adm_bkRand_2,random,16);
		if(3 == adminNum) memcpy(adm_bkRand_3,random,16);
		if(4 == adminNum) memcpy(adm_bkRand_4,random,16);
		if(5 == adminNum) memcpy(adm_bkRand_5,random,16);
	}

	//写入管理员序列号
	LPSTR szFileName_adminIndex = "LBL_CERT_adminIndex";
	CString adminID;
	adminID.Format("%d",AdminInfo.iAdminId);
	BYTE data_in[256]={0x00};
	memcpy(data_in,adminID.GetBuffer(),adminID.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_adminIndex,data_in,adminID.GetLength());
	ret = CMyUtil::WriteLabelEx(szFileName_adminIndex,data_in,adminID.GetLength(),(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入管理员序列号失败","提示");
		return;
	}

	CString adminLabel;
	if(isKMer==0)
		adminLabel= "设备管理员";
	else if(isKMer==1)
		adminLabel= "密钥授权员";
	else if(isKMer==2)
		adminLabel= "安全审计员";
	//写入管理员标签
	LPSTR szFileName_USERNAME = "LBL_OTHER_LAB_USERNAME";
	
	BYTE data_in_label[256]={0x00};
	memcpy(data_in_label,adminLabel.GetBuffer(),adminLabel.GetLength());
	//ret = CMyUtil::WriteLabel(szFileName_USERNAME,data_in_label,12);
	ret = CMyUtil::WriteLabelEx(szFileName_USERNAME,data_in_label,12,(char *)m_adminPwd.GetString());
	if(0 != ret)
	{
		MessageBox("写入管理员标签失败","提示");
		return;
	}
	
	if(0 == ret && 1 == uiAdminNum)
	{
		MessageBox(_T("管理员生成成功！"),_T(""));
		this->OnOK();
		if(isKMer==1)//签发安全审计员
		{
			if(KeyMnGer_AQ==1)//读config.txt判断是否签发安全审计员
			{
				CSignPWMAdmin signPWMAdminDlg(0,2,uiAdminNum,0,key_length,1,"签发安全审计员",phSHandle,phSHandle);
				signPWMAdminDlg.DoModal();
				return ;
			}
			else//不签发安全审计员直接跳转的登录界面
				{
					Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
					if(IDOK != ph_PWMMngrDlg.DoModal())
					return;
				}
		}
		else if(isKMer==2)//跳转到登录界面
		{
			Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
			if(IDOK != ph_PWMMngrDlg.DoModal())
				return;
		}
		else if(isKMer==0 )//签发授权员
		{
			if(KeyMnGer_SQ==1)//读取config.txt判断是否需要签发授权员 
			{
				int state_km_iskm=0;
				CSignPWMAdmin signPWMAdminDlg(0,1,uiAdminNum,0,key_length,1,"签发密钥授权员",phSHandle,phSHandle);
				signPWMAdminDlg.DoModal();
				signPWMAdminDlg.GetTwoSigState(&state_km_iskm);
				if(state_km_iskm==1)
				{
					CIsInit isInitDlg(NULL,phSHandle);
					isInitDlg.DoModal();
					return;
				}
				return;
			}
			else//不需要签发授权员直接跳转到审计员签发界面
			{
				if(KeyMnGer_AQ==1)//判断是否签发安全审计员
				{
					CSignPWMAdmin signPWMAdminDlg(0,2,uiAdminNum,0,key_length,1,"签发安全审计员",phSHandle,phSHandle);
					signPWMAdminDlg.DoModal();
					return ;
				}
				else//不签发安全审计员直接跳转的登录界面
				{
					Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,phSessionHandle,key_phSHandle,NULL/*phContainer*/,PWMMNGR_CAPTION);
					if(IDOK != ph_PWMMngrDlg.DoModal())
					return;
				}
			}
			
		}
		
	}
	else if(0 == ret && 1 < uiAdminNum)
	{
		switch(adminNum)
		{
		case 1:
			MessageBox(_T("第1个管理员生成成功！"),_T(""));
			break;
		case 2:
			if(adminNum != num_adm_max)
				MessageBox(_T("第2个管理员生成成功！"),_T(""));
			else
				MessageBox(_T("全部管理员生成成功！"),_T(""));
			break;
		case 3:
			if(adminNum != num_adm_max)
				MessageBox(_T("第3个管理员生成成功！"),_T(""));
			else
				MessageBox(_T("全部管理员生成成功！"),_T(""));
			break;
		case 4:
			if(adminNum != num_adm_max)
				MessageBox(_T("第4个管理员生成成功！"),_T(""));
			else
				MessageBox(_T("全部管理员生成成功！"),_T(""));
			break;
		case 5:
			if(adminNum != num_adm_max)
				MessageBox(_T("第5个管理员生成成功！"),_T(""));
			else
				MessageBox(_T("全部管理员生成成功！"),_T(""));
			break;
		default:
			MessageBox(_T("生成成功！"),_T(""));
			break;
		}
		
		if(adminNum <= num_adm_max && isOneToMore_kmer==1 && isKMer==1)
		{
			this->OnOK();
			int adm_Count_forset = num_adm_max; 
			
			int state_km = 0;
			CString i_Count_dlg_km;
			/*while(1 < num_adm_max && state_km == 0)
			{*/
			//state_km = 0;
			//i_km++;
			adminNum++;
			if(adminNum<=num_adm_max)
			{
				i_Count_dlg_km.Format("%d",adminNum);
				CSignPWMAdmin signPWMAdminDlg(1,1,0,0,key_length,adminNum,"签发第"+i_Count_dlg_km+"个密钥授权员",key_phSHandle,phSHandle);
				signPWMAdminDlg.admin_count = adm_Count_forset;//设置只读属性框的最大管理员数
				signPWMAdminDlg.isReadOnly = TRUE;
				if(IDOK != signPWMAdminDlg.DoModal())
					//break;
					return;
				
				signPWMAdminDlg.GetTwoSigState(&state_km);
				//num_adm_max--;
				/*}*/
				if(1 == state_km)
				{
					CIsInit isInitDlg(NULL,phSHandle);
					isInitDlg.DoModal();
					return;
				}

				if(adminNum == num_adm_max)
				{
					CSignPWMAdmin signPWMAdminDlg(0,2,0,0,key_length,0,"签发安全审计员",key_phSHandle,phSHandle);
					if(IDOK != signPWMAdminDlg.DoModal())
						return;
					//Cph_PWMngrDlg ph_PWMMngrDlg(NULL,1,NULL,NULL,NULL/*phContainer*/,PWMMNGR_CAPTION);
					//ph_PWMMngrDlg.uiKeyLen = key_length;
					//ph_PWMMngrDlg.DoModal();
					//return;
				}
			}
		}
		this->OnOK();
	}
	
}

void CSignPWMAdmin::OnCbnSelchangePapertypeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWeb;   
    int nSel;   
  
    // 获取组合框控件的列表框中选中项的索引  
    nSel = m_paperType.GetCurSel();   
    // 根据选中项索引获取该项字符串  
    m_paperType.GetLBText(nSel, strWeb);   
    // 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中  
    //SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb); 
//	MessageBox(_T("选择的类型是：") + strWeb);
}

void CSignPWMAdmin::GetMaxAdminNum(int *num)
{
	*num = num_adm_max;
}

void CSignPWMAdmin::GetTwoSigState(int *x)
{
	*x = isTwoPro;
}