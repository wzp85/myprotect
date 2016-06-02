// AppCertKeyGen.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "AppCertKeyGen.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"

// CAppCertKeyGen 对话框
  

IMPLEMENT_DYNAMIC(CAppCertKeyGen, CDialogEx)

CAppCertKeyGen::CAppCertKeyGen(void *handle,int isUpDate,CString certname,CString city,CString nation,CString area,CString organization,CString email,CString organizationUnite,CString keyIndex,CString algid,CString keyType,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppCertKeyGen::IDD, pParent)
	, m_ac_appName(_T(""))
	, m_ac_alg_cs(_T(""))
	, m_ac_index_cs(_T(""))
	, m_ac_appType_cs(_T(""))
	, m_ac_keyType_cs(_T(""))
	, m_ac_pinf(_T(""))
	, m_ac_pins(_T(""))
	, m_ac_cnName(_T(""))
	, m_ac_cityName_cs(_T(""))
	, m_ac_atName(_T(""))
	, m_ac_areaName_cs(_T(""))
	, m_ac_eMail(_T(""))
	, m_ac_OUvalue(_T(""))
{
	isUp = isUpDate;//1是生成，0是更新
	phHandle_appCertMngr = handle;

	in_certname=certname;
	in_city=city;
	in_nation=nation;
	in_area=area;
	in_organization=organization;
	in_email=email;
	in_organizationUnite=organizationUnite;
	in_keyIndex=keyIndex;
	in_algid=algid;
	in_keyType=keyType;

}

CAppCertKeyGen::CAppCertKeyGen(void *handle,int isUpDate,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppCertKeyGen::IDD, pParent)
	, m_ac_appName(_T(""))
	, m_ac_alg_cs(_T(""))
	, m_ac_index_cs(_T(""))
	, m_ac_appType_cs(_T(""))
	, m_ac_keyType_cs(_T(""))
	, m_ac_pinf(_T(""))
	, m_ac_pins(_T(""))
	, m_ac_cnName(_T(""))
	, m_ac_cityName_cs(_T(""))
	, m_ac_atName(_T(""))
	, m_ac_areaName_cs(_T(""))
	, m_ac_eMail(_T(""))
	, m_ac_OUvalue(_T(""))
{
	isUp = isUpDate;//1是生成，0是更新
	phHandle_appCertMngr = handle;
}

CAppCertKeyGen::~CAppCertKeyGen()
{
}

void CAppCertKeyGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AC_apname, m_ac_appName);
	DDX_Control(pDX, IDC_COMBO_AC_alg, m_ac_alg);
	DDX_CBString(pDX, IDC_COMBO_AC_alg, m_ac_alg_cs);
	DDX_Control(pDX, IDC_COMBO_AC_index, m_ac_index);
	DDX_CBString(pDX, IDC_COMBO_AC_index, m_ac_index_cs);
	DDX_Control(pDX, IDC_COMBO_AC_apType, m_ac_appType);
	DDX_CBString(pDX, IDC_COMBO_AC_apType, m_ac_appType_cs);
	DDX_Control(pDX, IDC_COMBO_AC_keyType, m_ac_keyType);
	DDX_CBString(pDX, IDC_COMBO_AC_keyType, m_ac_keyType_cs);
	DDX_Text(pDX, IDC_EDIT_AC_pinf, m_ac_pinf);
	DDX_Text(pDX, IDC_EDIT_AC_pins, m_ac_pins);
	DDX_Text(pDX, IDC_EDIT_AC_cnName, m_ac_cnName);
	DDX_Control(pDX, IDC_COMBO_AC_cityName, m_ac_cityName);
	DDX_CBString(pDX, IDC_COMBO_AC_cityName, m_ac_cityName_cs);
	DDX_Text(pDX, IDC_EDIT_AC_atName, m_ac_atName);
	DDX_Control(pDX, IDC_COMBO_AC_areaName, m_ac_areaName);
	DDX_CBString(pDX, IDC_COMBO_AC_areaName, m_ac_areaName_cs);
	//	DDX_Text(pDX, IDC_EDIT_AC_atUnitName, m_atUnitName);
	DDX_Text(pDX, IDC_EDIT_AC_eMail, m_ac_eMail);
	DDX_Text(pDX, IDC_EDIT_APPCERT_OU, m_ac_OUvalue);
}


BEGIN_MESSAGE_MAP(CAppCertKeyGen, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAppCertKeyGen::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAppCertKeyGen::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_AC_cityName, &CAppCertKeyGen::OnCbnSelchangeComboAccityname)
	//ON_CBN_SELCHANGE(IDC_COMBO_AC_index, &CAppCertKeyGen::OnCbnSelchangeComboAcindex)
END_MESSAGE_MAP()


// CAppCertKeyGen 消息处理程序
BOOL CAppCertKeyGen::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)  
	{
		if(GetFocus()->GetDlgCtrlID()==IDOK)//按下回车，如果当前焦点是在自己期望的控件上
        {                                           
            CAppCertKeyGen::OnBnClickedOk();//添加自己的处理代码
        }
		if(GetFocus()->GetDlgCtrlID()==IDCANCEL)//按下回车，如果当前焦点是在自己期望的控件上
        {                                           
            CAppCertKeyGen::OnBnClickedCancel();//添加自己的处理代码
        }
        return TRUE;
	}
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CAppCertKeyGen::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);

	if(m_ac_appName.IsEmpty())
	{
		MessageBox("应用名称不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_appName.GetLength()>20)
	{
		MessageBox("应用名称不能超过20个字符！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_cityName_cs.IsEmpty())
	{
		MessageBox("请选择省份或直辖市！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_areaName_cs.IsEmpty())
	{
		MessageBox("请选择城市或区县！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_cnName.IsEmpty())
	{
		MessageBox("请输入国家名称！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_atName.IsEmpty())
	{
		MessageBox("请输入机构名称！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_eMail.IsEmpty())
	{
		MessageBox("请输入电子邮箱！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_pinf.GetLength()<8)
	{
		MessageBox("PIN码长度不能小于8位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_ac_pinf != m_ac_pins)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_ac_pinf))
	{
		MessageBox("PIN码不能全是数字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}


	void * hSessionHandle = phHandle_appCertMngr;

	if(0 == isUp)
	{
		unsigned int index_del=atoi((LPSTR)(LPCTSTR)in_keyIndex);
		INT_PTR nRes = 0x00;
		nRes = MessageBox("确定要更新该密钥信息？","提示",MB_ICONWARNING | MB_OKCANCEL);
		if(nRes != IDOK)
		{
			return;
		}
		ret = Km_AppKeyDestroy(hSessionHandle,1,1,&index_del);
		if(0 != ret)
		{
			char outApkd[100]={0x00};
			retValueParse(ret,outApkd);
			CString index_uig_num_cs;
			index_uig_num_cs.Format("%d",index_del);
			MessageBox("销毁第"+index_uig_num_cs+ "号应用密钥失败！错误码："+(CString)outApkd,"提示");
			return;
		}
	}



	unsigned char pucIndex[32]={0x00};
	unsigned int uiIndexLength = m_ac_index_cs.GetLength();
	memcpy(pucIndex,m_ac_index_cs.GetBuffer(),m_ac_index_cs.GetLength());
	unsigned int uikeyIndex = atoi(m_ac_index_cs);
	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	unsigned int uiHashAlgo;

	if(m_ac_alg_cs == "RSA 1024")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 1024;
		uiHashAlgo = SGD_SHA1;
	}
	if(m_ac_alg_cs == "RSA 2048")
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 2048;
		uiHashAlgo = SGD_SHA1;
	}
	if(m_ac_alg_cs == "SM2")
	{
		uiAlgo = SGD_SM2_1;
		uiKeyLength = 256; 
		uiHashAlgo = SGD_SM3;
	}
	
	unsigned char pucKeyPasswd[32]={0x00};
	memcpy(pucKeyPasswd,m_ac_pinf.GetBuffer(),m_ac_pinf.GetLength());
	unsigned int uiKeyPasswdLength = m_ac_pinf.GetLength();
	unsigned char pucAppName[50]={0x00};
	memcpy(pucAppName,m_ac_appName.GetBuffer(),m_ac_appName.GetLength());
	unsigned int uiAppNameLength = m_ac_appName.GetLength(); 
	unsigned int uiKeyType;
	if(m_ac_keyType_cs == "签名、加密共用密钥")
		uiKeyType = 2;
	if(m_ac_keyType_cs == "签名、加密不共用密钥")
		uiKeyType = 3;
	if(m_ac_keyType_cs == "签名密钥")
		uiKeyType = 0;
	if(m_ac_keyType_cs == "加密密钥")
		uiKeyType = 1;
	unsigned char pucCityName[50]={0x00};
	memcpy(pucCityName,m_ac_cityName_cs.GetBuffer(),m_ac_cityName_cs.GetLength());
	unsigned int uiCityNameLength = m_ac_cityName_cs.GetLength();
	unsigned char pucCNName[50]={0x00};
	memcpy(pucCNName,m_ac_cnName.GetBuffer(),m_ac_cnName.GetLength());
	unsigned int uiCNNameLength = m_ac_cnName.GetLength();
	unsigned char pucAreaName[50]={0x00};
	memcpy(pucAreaName,m_ac_areaName_cs.GetBuffer(),m_ac_areaName_cs.GetLength());
	unsigned int uiAreaNameLength = m_ac_areaName_cs.GetLength();
	unsigned char pucAtName[50]={0x00};
	memcpy(pucAtName,m_ac_atName.GetBuffer(),m_ac_atName.GetLength());
	unsigned int uiAtNameLength = m_ac_atName.GetLength();
	unsigned char pucEmail[50]={0x00};
	memcpy(pucEmail,m_ac_eMail.GetBuffer(),m_ac_eMail.GetLength());
	unsigned int uiEmailLength = m_ac_eMail.GetLength();

	unsigned char pucOUValue[50]={0x00};
	unsigned int uiOUValueLength = m_ac_OUvalue.GetLength();
	memcpy(pucOUValue,m_ac_OUvalue.GetBuffer(),m_ac_OUvalue.GetLength());
	

	ret = Km_GenAppKey_SIG(hSessionHandle,uikeyIndex,uiAlgo,uiKeyLength,pucKeyPasswd,uiKeyPasswdLength,pucAppName,uiAppNameLength,
		uiKeyType,pucCityName,uiCityNameLength,pucCNName,uiCNNameLength,pucAreaName,uiAreaNameLength,pucAtName,uiAtNameLength,
		pucEmail,uiEmailLength,pucOUValue,uiOUValueLength);
	if(0 == ret && 1 == isUp)
	{
		this->OnOK();
		INT_PTR nRes;
		
		/*MessageBox("    添加成功","提示");*/
		nRes = MessageBox("添加成功,是否要继续生成证书请求？","",MB_ICONQUESTION|MB_OKCANCEL);
		if(nRes == IDOK)
		{
			//-------------------------在这里调用生成证书请求接口------------------------
			//(unsigned char *)"C=CN,S=上海,L=上海,O=普华,OU=研发部,CN=测试证书1,E=asdfg@qq.com",
			unsigned char pucRequest[1024]={0x00};
			memcpy(pucRequest,"C=",strlen("C="));
			strncat((char*)pucRequest,m_ac_cnName,m_ac_cnName.GetLength());
			strncat((char*)pucRequest,",S=",strlen(",S="));
			strncat((char*)pucRequest,m_ac_cityName_cs,m_ac_cityName_cs.GetLength());
			strncat((char*)pucRequest,",L=",strlen(",L="));
			strncat((char*)pucRequest,m_ac_areaName_cs,m_ac_areaName_cs.GetLength());
			strncat((char*)pucRequest,",O=",strlen(",O="));
			strncat((char*)pucRequest,m_ac_atName,m_ac_atName.GetLength());
			strncat((char*)pucRequest,",OU=",strlen(",OU="));
			strncat((char*)pucRequest,m_ac_OUvalue,m_ac_OUvalue.GetLength());
			strncat((char*)pucRequest,",CN=",strlen(",CN="));
			strncat((char*)pucRequest,m_ac_appName,m_ac_appName.GetLength());
			strncat((char*)pucRequest,",E=",strlen(",E="));
			strncat((char*)pucRequest,m_ac_eMail,m_ac_eMail.GetLength());
			//printf("pucRequest == %s\n",pucRequest);
			unsigned int uiRequestLength = strlen((char*)pucRequest);
			unsigned char pucB64Req[2048]={0x00};
			unsigned char pucReq[1024]={0x00};
			ret = Sig_GenCertRequest(hSessionHandle,26115,uiHashAlgo,uiAlgo,uiIndexLength,pucIndex,uiKeyPasswdLength,pucKeyPasswd,
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
		//CDialogEx::OnOK();
		
	}
	else if(0 != ret && 1 == isUp)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		//CDialogEx::OnOK();
		this->OnCancel();
		MessageBox("    添加失败"+(CString)outGapk,"提示");
	}
	else if(0 == ret && 0 == isUp)
	{
		MessageBox("操作成功！","提示",MB_ICONEXCLAMATION);
		this->OnOK();
	}

}


void CAppCertKeyGen::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CAppCertKeyGen::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/****************设置CComBox下拉框为只读防止用户自己输入造成不必要的错误******************************/
	CAppCertKeyGen:: SetReadOnly();
	/***********************************************/
	CWnd *cWnd = GetDlgItem(IDC_STATIC_AC_TITLE);
	if(isUp)
	{
		this->SetWindowText("应用密钥生成");
		cWnd->SetWindowText("应用密钥生成");
	
	
		// TODO:  在此添加额外的初始化
		int one = acKeyIndex;
		CString cs_keyIndex;
		CString index;
		index.Format("%d",one);
		cs_keyIndex = "00"+index;//数据的格式化操作，需要再写一个新的方法 
		SetDlgItemText(IDC_COMBO_AC_index,cs_keyIndex);

		int data = 0;
		for(int i=0;i<256;i++)
		{
			if(1 == acKeyIndex_array[i][1])
			{
				data = acKeyIndex_array[i][0];
				index.Format("%d",data);
				cs_keyIndex = "00"+index;
				m_ac_index.AddString(cs_keyIndex);
			}
		}


		cWnd = GetDlgItem(IDC_EDIT_AC_apname);//光标聚焦到应用名称
		cWnd->SetFocus();
		SetDlgItemText(IDC_EDIT_AC_cnName,"CN");
		//SetDlgItemText(IDC_COMBO_AC_alg, _T("SM2"));  
		SetDlgItemText(IDC_COMBO_AC_alg, _T("RSA 1024"));
		SetDlgItemText(IDC_COMBO_AC_keyType, _T("签名、加密共用密钥"));
	}
	else if(!isUp)
	{
		this->SetWindowText("应用密钥更新");
		cWnd->SetWindowText("应用密钥更新");

		SetDlgItemText(IDC_EDIT_AC_apname,in_certname);
		SetDlgItemText(IDC_COMBO_AC_cityName,in_city);
		SetDlgItemText(IDC_EDIT_AC_cnName,in_nation);
		
		SetDlgItemText(IDC_EDIT_AC_atName,in_organization);
		SetDlgItemText(IDC_EDIT_AC_eMail,in_email);
		SetDlgItemText(IDC_EDIT_APPCERT_OU,in_organizationUnite);
		SetDlgItemText(IDC_COMBO_AC_index,in_keyIndex);
		

		SetDlgItemText(IDC_COMBO_AC_alg,in_algid);
		SetDlgItemText(IDC_COMBO_AC_keyType,in_keyType);

		int num=0;
		CAppCertKeyGen::GetCityInUpdate(in_city,&num);
		CAppCertKeyGen::ShowCityInfo(num);

		SetDlgItemText(IDC_COMBO_AC_areaName,in_area);
	}


	m_ac_alg.AddString(_T("RSA 1024"));     
	m_ac_alg.AddString(_T("RSA 2048")); 
	m_ac_alg.AddString(_T("SM2"));

	m_ac_appType.AddString(_T("应用非对称密钥"));
	SetDlgItemText(IDC_COMBO_AC_apType, _T("应用非对称密钥"));

	//m_ac_keyType.AddString(_T("签名密钥"));
	//m_ac_keyType.AddString(_T("加密密钥"));
	m_ac_keyType.AddString(_T("签名、加密共用密钥"));
	m_ac_keyType.AddString(_T("签名、加密不共用密钥"));

	CAppCertKeyGen::WriteCityInfo();

	m_ac_cityName.AddString(_T("北京市"));
	m_ac_cityName.AddString(_T("上海市"));
	m_ac_cityName.AddString(_T("天津市"));
	m_ac_cityName.AddString(_T("重庆市"));
	m_ac_cityName.AddString(_T("河北省"));
	m_ac_cityName.AddString(_T("山西省"));
	m_ac_cityName.AddString(_T("台湾省"));
	m_ac_cityName.AddString(_T("辽宁省"));
	m_ac_cityName.AddString(_T("吉林省"));
	m_ac_cityName.AddString(_T("黑龙江省"));
	m_ac_cityName.AddString(_T("江苏省"));
	m_ac_cityName.AddString(_T("浙江省"));
	m_ac_cityName.AddString(_T("安徽省"));
	m_ac_cityName.AddString(_T("福建省"));
	m_ac_cityName.AddString(_T("江西省"));
	m_ac_cityName.AddString(_T("山东省"));
	m_ac_cityName.AddString(_T("河南省"));
	m_ac_cityName.AddString(_T("湖北省"));
	m_ac_cityName.AddString(_T("湖南省"));
	m_ac_cityName.AddString(_T("广东省"));
	m_ac_cityName.AddString(_T("甘肃省"));
	m_ac_cityName.AddString(_T("四川省"));
	m_ac_cityName.AddString(_T("贵州省"));
	m_ac_cityName.AddString(_T("海南省"));
	m_ac_cityName.AddString(_T("云南省"));
	m_ac_cityName.AddString(_T("青海省"));
	m_ac_cityName.AddString(_T("陕西省"));
	m_ac_cityName.AddString(_T("广西壮族自治区"));
	m_ac_cityName.AddString(_T("西藏自治区"));
	m_ac_cityName.AddString(_T("宁夏回族自治区"));
	m_ac_cityName.AddString(_T("新疆维吾尔自治区"));
	m_ac_cityName.AddString(_T("内蒙古自治区"));
	m_ac_cityName.AddString(_T("澳门特别行政区"));
	m_ac_cityName.AddString(_T("香港特别行政区"));
	SetDlgItemText(IDC_COMBO_AC_cityName, _T("北京"));
	SetDlgItemText(IDC_COMBO_AC_areaName, _T("海淀区"));

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAppCertKeyGen::OnCbnSelchangeComboAccityname()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel; 
    nSel = m_ac_cityName.GetCurSel();   

	CAppCertKeyGen::ShowCityInfo(nSel);
}

void CAppCertKeyGen::WriteCityInfo()
{
	char ShangHai[][50]={"黄浦区","卢湾区","徐汇区","长宁区","静安区","普陀区","闸北区","虹口区","杨浦区","闵行区","宝山区","嘉定区","浦东新区"
							,"金山区","松江区","青浦区","南汇区","奉贤区","崇明县"};
	CAppCertKeyGen::WriteProviceInfo("上海市",(char *)ShangHai,19);

	char BeiJing[][50]={"东城区","西城区","崇文区","宣武区","朝阳区","丰台区","石景山区","海淀区","门头沟区","房山区","通州区","顺义区"
						,"昌平区","大兴区","怀柔区","平谷区","密云县","延庆县"};
	CAppCertKeyGen::WriteProviceInfo("北京市",(char *)BeiJing,18);

	char TianJin[][50]={"和平区","河东区","河西区","南开区","河北区","红桥区","塘沽区","汉沽区","大港区","东丽区","西青区","津南区","北辰区"
						,"武清区","宝坻区","宁河县","静海县","蓟　县"};
	CAppCertKeyGen::WriteProviceInfo("天津市",(char *)TianJin,18);

	char ChongQing[][50]={"万州区","涪陵区","渝中区","大渡口区","江北区","沙坪坝区","九龙坡区","南岸区","北碚区","万盛区","双桥区","渝北区"
							,"巴南区","黔江区","长寿区","綦江县","潼南县","铜梁县","大足县","荣昌县","璧山县","梁平县","城口县","丰都县"
							,"垫江县","武隆县","忠　县","开　县","云阳县","奉节县","巫山县","巫溪县","石柱土家族自治县"
						,"秀山土家族苗族自治县","酉阳土家族苗族自治县","彭水苗族土家族自治县"};
	CAppCertKeyGen::WriteProviceInfo("重庆市",(char *)ChongQing,36);

	char HeBei[][50]={"石家庄市","唐山市","秦皇岛市","邯郸市","邢台市","保定市","张家口市","承德市","沧州市","廊坊市","衡水市"};
	CAppCertKeyGen::WriteProviceInfo("河北省",(char *)HeBei,11);

	char ShanXi[][50]={"太原市","大同市","阳泉市","长治市","晋城市","朔州市","晋中市","运城市","忻州市","临汾市","吕梁市"};
	CAppCertKeyGen::WriteProviceInfo("山西省",(char *)ShanXi,11);

	char TaiWan[][50]={"台北市","高雄市","基隆市","台中市","台南市","新竹市","嘉义市","台北县","宜兰县","桃园县","新竹县","苗栗县","台中县"
						,"彰化县","南投县","云林县","嘉义县","台南县","高雄县","屏东县","澎湖县","台东县","花莲县"};
	CAppCertKeyGen::WriteProviceInfo("台湾省",(char *)TaiWan,23);

	char LiaoNing[][50]={"沈阳市","大连市","鞍山市","抚顺市","本溪市","丹东市","锦州市","营口市","阜新市","辽阳市","盘锦市","铁岭市"
						,"朝阳市","葫芦岛市"};
	CAppCertKeyGen::WriteProviceInfo("辽宁省",(char *)LiaoNing,14);

	char JiLin[][50]={"长春市","吉林市","四平市","辽源市","通化市","白山市","松原市","白城市","延边朝鲜族自治州"};
	CAppCertKeyGen::WriteProviceInfo("吉林省",(char *)JiLin,9);

	char HeiLongJiang[][50]={"哈尔滨市","齐齐哈尔市","鹤岗市","双鸭山市","鸡西市","大庆市","伊春市","牡丹江市","佳木斯市","七台河市"
							,"黑河市","绥化市","大兴安岭地区"};
	CAppCertKeyGen::WriteProviceInfo("黑龙江省",(char *)HeiLongJiang,13);

	char JiangSu[][50]={"南京市","无锡市","徐州市","常州市","苏州市","南通市","连云港市","淮安市","盐城市","扬州市","镇江市","泰州市"
						,"宿迁市"};
	CAppCertKeyGen::WriteProviceInfo("江苏省",(char *)JiangSu,13);

	char ZheJiang[][50]={"杭州市","宁波市","温州市","嘉兴市","湖州市","绍兴市","金华市","衢州市","舟山市","台州市","丽水市"};
	CAppCertKeyGen::WriteProviceInfo("浙江省",(char *)ZheJiang,11);

	char AnHui[][50]={"合肥市","芜湖市","蚌埠市","淮南市","马鞍山市","淮北市","铜陵市","安庆市","黄山市","滁州市","阜阳市","宿州市"
						,"巢湖市","六安市","亳州市","池州市","宣城市"};
	CAppCertKeyGen::WriteProviceInfo("安徽省",(char *)AnHui,17);

	char FuJian[][50]={"福州市","厦门市","莆田市","三明市","泉州市","漳州市","南平市","龙岩市","宁德市"};
	CAppCertKeyGen::WriteProviceInfo("福建省",(char *)FuJian,9);

	char JiangXi[][50]={"南昌市","景德镇市","萍乡市","九江市","新余市","鹰潭市","赣州市","吉安市","宜春市","抚州市","上饶市"};
	CAppCertKeyGen::WriteProviceInfo("江西省",(char *)JiangXi,11);

	char ShanDong[][50]={"济南市","青岛市","淄博市","枣庄市","东营市","烟台市","潍坊市","济宁市","泰安市","威海市","日照市","莱芜市"
						,"临沂市","德州市","聊城市","滨州市","菏泽市"};
	CAppCertKeyGen::WriteProviceInfo("山东省",(char *)ShanDong,17);

	char HeNan[][50]={"郑州市","开封市","洛阳市","平顶山市","安阳市","鹤壁市","新乡市","焦作市","濮阳市","许昌市","漯河市","三门峡市"
						,"南阳市","商丘市","信阳市","周口市","驻马店市","济源市"};
	CAppCertKeyGen::WriteProviceInfo("河南省",(char *)HeNan,18);

	char HuBei[][50]={"武汉市","黄石市","十堰市","荆州市","宜昌市","襄樊市","鄂州市","荆门市","孝感市","黄冈市","咸宁市","随州市","仙桃市"
						,"天门市","潜江市","神农架林区","恩施土家族苗族自治州"};
	CAppCertKeyGen::WriteProviceInfo("湖北省",(char *)HuBei,17);

	char HuNan[][50]={"长沙市","株洲市","湘潭市","衡阳市","邵阳市","岳阳市","常德市","张家界市","益阳市","郴州市","永州市","怀化市"
						,"娄底市","湘西土家族苗族自治州"};
	CAppCertKeyGen::WriteProviceInfo("湖南省",(char *)HuNan,14);

	char GuangDong[][50]={"广州市","深圳市","珠海市","汕头市","韶关市","佛山市","江门市","湛江市","茂名市","肇庆市","惠州市","梅州市"
							,"汕尾市","河源市","阳江市","清远市","东莞市","中山市","潮州市","揭阳市","云浮市"};
	CAppCertKeyGen::WriteProviceInfo("广东省",(char *)GuangDong,21);

	char GanSu[][50]={"兰州市","金昌市","白银市","天水市","嘉峪关市","武威市","张掖市","平凉市","酒泉市","庆阳市","定西市","陇南市"
					,"临夏回族自治州","甘南藏族自治州"};
	CAppCertKeyGen::WriteProviceInfo("甘肃省",(char *)GanSu,14);

	char SiChuan[][50]={"成都市","自贡市","攀枝花市","泸州市","德阳市","绵阳市","广元市","遂宁市","内江市","乐山市","南充市","眉山市"
						,"宜宾市","广安市","达州市","雅安市","巴中市","资阳市","阿坝藏族羌族自治州","甘孜藏族自治州","凉山彝族自治州"};
	CAppCertKeyGen::WriteProviceInfo("四川省",(char *)SiChuan,21);

	char GuiZhou[][50]={"贵阳市","六盘水市","遵义市","安顺市","铜仁地区","毕节地区","黔西南布依族苗族自治州","黔东南苗族侗族自治州"
						,"黔南布依族苗族自治州"};
	CAppCertKeyGen::WriteProviceInfo("贵州省",(char *)GuiZhou,9);

	char HaiNan[][50]={"海口市","三亚市","五指山市","琼海市","儋州市","文昌市","万宁市","东方市","澄迈县","定安县","屯昌县","临高县"
						,"白沙黎族自治县","昌江黎族自治县","乐东黎族自治县","陵水黎族自治县","保亭黎族苗族自治县","琼中黎族苗族自治县"};
	CAppCertKeyGen::WriteProviceInfo("海南省",(char *)HaiNan,18);

	char YunNan[][50]={"昆明市","曲靖市","玉溪市","保山市","昭通市","丽江市","思茅市","临沧市","文山壮族苗族自治州","红河哈尼族彝族自治州"
						,"西双版纳傣族自治州","楚雄彝族自治州","大理白族自治州","德宏傣族景颇族自治州","怒江傈傈族自治州","迪庆藏族自治州"};
	CAppCertKeyGen::WriteProviceInfo("云南省",(char *)YunNan,16);

	char QingHai[][50]={"西宁市","海东地区","海北藏族自治州","黄南藏族自治州","海南藏族自治州","果洛藏族自治州","玉树藏族自治州","海西蒙古族藏族自治州"};
	CAppCertKeyGen::WriteProviceInfo("青海省",(char *)QingHai,8);

	char ShanXi_2[][50]={"西安市","铜川市","宝鸡市","咸阳市","渭南市","延安市","汉中市","榆林市","安康市","商洛市"};
	CAppCertKeyGen::WriteProviceInfo("陕西省",(char *)ShanXi_2,10);

	char GuangXi[][50]={"南宁市","柳州市","桂林市","梧州市","北海市","防城港市","钦州市","贵港市","玉林市","百色市","贺州市","河池市"
						,"来宾市","崇左市"};
	CAppCertKeyGen::WriteProviceInfo("广西壮族自治区",(char *)GuangXi,14);

	char XiZang[][50]={"拉萨市","那曲地区","昌都地区","山南地区","日喀则地区","阿里地区","林芝地区"};
	CAppCertKeyGen::WriteProviceInfo("西藏自治区",(char *)XiZang,7);

	char NingXia[][50]={"银川市","石嘴山市","吴忠市","固原市","中卫市"};
	CAppCertKeyGen::WriteProviceInfo("宁夏回族自治区",(char *)NingXia,5);

	char XinJiang[][50]={"乌鲁木齐市","克拉玛依市","石河子市","阿拉尔市","图木舒克市","五家渠市","吐鲁番市","阿克苏市","喀什市","哈密市"
						,"和田市","阿图什市","库尔勒市","昌吉市","阜康市","米泉市","博乐市","伊宁市","奎屯市","塔城市","乌苏市","阿勒泰市"};
	CAppCertKeyGen::WriteProviceInfo("新疆维吾尔自治区",(char *)XinJiang,22);

	char NeiMengGu[][50]={"呼和浩特市","包头市","乌海市","赤峰市","通辽市","鄂尔多斯市","呼伦贝尔市","巴彦淖尔市","乌兰察布市","锡林郭勒盟"
							,"兴安盟","阿拉善盟"};
	CAppCertKeyGen::WriteProviceInfo("内蒙古自治区",(char *)NeiMengGu,12);

	char AoMen[][50]={"澳门特别行政区"};
	CAppCertKeyGen::WriteProviceInfo("澳门特别行政区",(char *)AoMen,1);

	char HongKong[][50]={"香港特别行政区"};
	CAppCertKeyGen::WriteProviceInfo("香港特别行政区",(char *)HongKong,1);
}

void CAppCertKeyGen::WriteProviceInfo(CString ProName,char *city,int num)
{
	if(city==NULL)
		return;
	for(int i =0;i<num;i++)
	{
		CString iii;
		iii.Format("%d",i);
		::WritePrivateProfileString("ProviceName",ProName+iii,(LPCSTR)&(city)[i*50],"c://city.ini");
	}
	CString i_num;
	i_num.Format("%d",num);
	::WritePrivateProfileString("ProviceName",ProName+(CString)"共计",i_num,"c://city.ini");
}

void CAppCertKeyGen::ReadProviceInfo(CString proName)
{
	CString cityName;
	int Count = 0;
	Count = GetPrivateProfileInt("ProviceName",proName+(CString)"共计",0,"c://city.ini");
	for(int i=0;i<Count;i++)
	{
		CString ii;
		ii.Format("%d",i);
		GetPrivateProfileString("ProviceName",proName+ii,"默认姓名",cityName.GetBuffer(MAX_PATH),MAX_PATH,"c://city.ini");
		m_ac_areaName.AddString(cityName);
	}
}

void CAppCertKeyGen::ShowCityInfo(int num)
{
	m_ac_areaName.ResetContent();

	switch(num)
	{
	case 0:
		CAppCertKeyGen::ReadProviceInfo("北京市");
		break;
	case 1:
		CAppCertKeyGen::ReadProviceInfo("上海市");
		break;
	case 2:
		CAppCertKeyGen::ReadProviceInfo("天津市");
		break;
	case 3:
		CAppCertKeyGen::ReadProviceInfo("重庆市");
		break;
	case 4:
		CAppCertKeyGen::ReadProviceInfo("河北省");
		break;
	case 5:
		CAppCertKeyGen::ReadProviceInfo("山西省");
		break;
	case 6:
		CAppCertKeyGen::ReadProviceInfo("台湾省");
		break;
	case 7:
		CAppCertKeyGen::ReadProviceInfo("辽宁省");
		break;
	case 8:
		CAppCertKeyGen::ReadProviceInfo("吉林省");
		break;
	case 9:
		CAppCertKeyGen::ReadProviceInfo("黑龙江省");
		break;
	case 10:
		CAppCertKeyGen::ReadProviceInfo("江苏省");
		break;
	case 11:
		CAppCertKeyGen::ReadProviceInfo("浙江省");
		break;
	case 12:
		CAppCertKeyGen::ReadProviceInfo("安徽省");
		break;
	case 13:
		CAppCertKeyGen::ReadProviceInfo("福建省");
		break;
	case 14:
		CAppCertKeyGen::ReadProviceInfo("江西省");
		break;
	case 15:
		CAppCertKeyGen::ReadProviceInfo("山东省");
		break;
	case 16:
		CAppCertKeyGen::ReadProviceInfo("河南省");
		break;
	case 17:
		CAppCertKeyGen::ReadProviceInfo("湖北省");
		break;
	case 18:
		CAppCertKeyGen::ReadProviceInfo("湖南省");
		break;
	case 19:
		CAppCertKeyGen::ReadProviceInfo("广东省");
		break;
	case 20:
		CAppCertKeyGen::ReadProviceInfo("甘肃省");
		break;
	case 21:
		CAppCertKeyGen::ReadProviceInfo("四川省");
		break;
	case 22:
		CAppCertKeyGen::ReadProviceInfo("贵州省");
		break;
	case 23:
		CAppCertKeyGen::ReadProviceInfo("海南省");
		break;
	case 24:
		CAppCertKeyGen::ReadProviceInfo("云南省");
		break;
	case 25:
		CAppCertKeyGen::ReadProviceInfo("青海省");
		break;
	case 26:
		CAppCertKeyGen::ReadProviceInfo("陕西省");
		break;
	case 27:
		CAppCertKeyGen::ReadProviceInfo("广西壮族自治区");
		break;
	case 28:
		CAppCertKeyGen::ReadProviceInfo("西藏自治区");
		break;
	case 29:
		CAppCertKeyGen::ReadProviceInfo("宁夏回族自治区");
		break;
	case 30:
		CAppCertKeyGen::ReadProviceInfo("新疆维吾尔自治区");
		break;
	case 31:
		CAppCertKeyGen::ReadProviceInfo("内蒙古自治区");
		break;
	case 32:
		CAppCertKeyGen::ReadProviceInfo("澳门特别行政区");
		break;
	case 33:
		CAppCertKeyGen::ReadProviceInfo("香港特别行政区");
		break;
	}
}

void CAppCertKeyGen::GetCityInUpdate(CString city,int *num)
{
	if(city=="北京市")
		*num = 0;
	else if(city=="上海市")
		*num = 1;
	else if(city=="天津市")
		*num = 2;
	else if(city=="重庆市")
		*num = 3;
	else if(city=="河北省")
		*num = 4;
	else if(city=="山西省")
		*num = 5;
	else if(city=="台湾省")
		*num = 6;
	else if(city=="辽宁省")
		*num = 7;
	else if(city=="吉林省")
		*num = 8;
	else if(city=="黑龙江省")
		*num = 9;
	else if(city=="江苏省")
		*num = 10;
	else if(city=="浙江省")
		*num = 11;
	else if(city=="安徽省")
		*num = 12;
	else if(city=="福建省")
		*num = 13;
	else if(city=="江西省")
		*num = 14;
	else if(city=="山东省")
		*num = 15;
	else if(city=="河南省")
		*num = 16;
	else if(city=="湖北省")
		*num = 17;
	else if(city=="湖南省")
		*num = 18;
	else if(city=="广东省")
		*num = 19;
	else if(city=="甘肃省")
		*num = 20;
	else if(city=="四川省")
		*num = 21;
	else if(city=="贵州省")
		*num = 22;
	else if(city=="海南省")
		*num = 23;
	else if(city=="云南省")
		*num = 24;
	else if(city=="青海省")
		*num = 25;
	else if(city=="陕西省")
		*num = 26;
	else if(city=="广西壮族自治区")
		*num = 27;
	else if(city=="西藏自治区")
		*num = 28;
	else if(city=="宁夏回族自治区")
		*num = 29;
	else if(city=="新疆维吾尔自治区")
		*num = 30;
	else if(city=="内蒙古自治区")
		*num = 31;
	else if(city=="澳门特别行政区")
		*num = 32;
	else if(city=="香港特别行政区")
		*num = 33;
}


void CAppCertKeyGen:: SetReadOnly()
{
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_index))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit2 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_cityName))->GetWindow(GW_CHILD));	
	pEdit2->SetReadOnly(TRUE);
	CEdit* pEdit3 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_areaName))->GetWindow(GW_CHILD));	
	pEdit3->SetReadOnly(TRUE);
	CEdit* pEdit4 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_alg))->GetWindow(GW_CHILD));	
	pEdit4->SetReadOnly(TRUE);
	CEdit* pEdit5 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_keyType))->GetWindow(GW_CHILD));	
	pEdit5->SetReadOnly(TRUE);
	CEdit* pEdit6 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_AC_apType))->GetWindow(GW_CHILD));	
	pEdit6->SetReadOnly(TRUE);
	return ;
}