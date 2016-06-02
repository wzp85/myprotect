// RTCertAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "RTCertAdd.h"
#include "afxdialogex.h"

#include "ph_km.h"
#include "MyUtil.h"
// CRTCertAdd 对话框

IMPLEMENT_DYNAMIC(CRTCertAdd, CDialogEx)

CRTCertAdd::CRTCertAdd(void *handle,int isUp,CWnd* pParent /*=NULL*/)
	: CDialogEx(CRTCertAdd::IDD, pParent)
	, m_RTADD_certName_cs(_T(""))
	, m_RTADD_certAlg_cs(_T(""))
	, m_RTADD_certSN_cs(_T(""))
	, m_RTADD_atName_cs(_T(""))
	, m_RTADD_hostName_cs(_T(""))
	, m_RTADD_phone_cs(_T(""))
	, m_RTADD_rootCert_cs(_T(""))
{
	isUp_rt = isUp;
	phHandle_RtCertAdd = handle;
}
CRTCertAdd::CRTCertAdd(void *handle,int isUp,CString name,CString algid,CString CertIndex,CString atName,CString hostName,CString hostPhone,CString CertSN,CWnd* pParent /*=NULL*/)
	: CDialogEx(CRTCertAdd::IDD, pParent)
	, m_RTADD_certName_cs(_T(""))
	, m_RTADD_certAlg_cs(_T(""))
	, m_RTADD_atName_cs(_T(""))
	, m_RTADD_hostName_cs(_T(""))
	, m_RTADD_phone_cs(_T(""))
	, m_RTADD_rootCert_cs(_T(""))
	//, m_RTADD_certindex_cs(_T(""))
	, m_RTADD_certSN_cs(_T(""))
	, m_rt_index_cs(_T(""))
{
	isUp_rt = isUp;
	phHandle_RtCertAdd = handle;

	m_RTADD_certName_cs = name;
	m_RTADD_certAlg_cs = algid;
	m_RTADD_certSN_cs = CertSN;
	m_RTADD_certindex_cs = CertIndex;
	m_RTADD_atName_cs = atName;
	m_RTADD_hostName_cs = hostName;
	m_RTADD_phone_cs = hostPhone;
}

CRTCertAdd::~CRTCertAdd()
{
}

void CRTCertAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RTADD_CERTNAME_EDIT, m_RTADD_certName_cs);
	DDX_CBString(pDX, IDC_COMBO_RTADD_ALG, m_RTADD_certAlg_cs);
	DDX_Control(pDX, IDC_COMBO_RTADD_ALG, m_RTADD_certAlg);
	DDX_Text(pDX, IDC_RTADD_ATNAME_EDIT, m_RTADD_atName_cs);
	DDX_Text(pDX, IDC_RTADD_HOST_EDIT, m_RTADD_hostName_cs);
	DDX_Text(pDX, IDC_RTADD_PHONE_EDIT, m_RTADD_phone_cs);
	DDX_Text(pDX, IDC_RTADD_IMCAPATH_EDIT, m_RTADD_rootCert_cs);
	//DDX_Text(pDX,IDC_RTADD_EDIT_CERTINDEX, m_RTADD_certindex_cs);
	DDX_Text(pDX, IDC_RTADD_CERTSN_EDIT, m_RTADD_certSN_cs);
	DDX_Control(pDX, IDC_RTCERT_INDEX_COMBO, m_rt_index);
	DDX_CBString(pDX, IDC_RTCERT_INDEX_COMBO, m_rt_index_cs);
}


BEGIN_MESSAGE_MAP(CRTCertAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRTCertAdd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRTCertAdd::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_IMRTC_BUTTON, &CRTCertAdd::OnBnClickedImrtcButton)
	ON_CBN_SELCHANGE(IDC_RTCERT_INDEX_COMBO, &CRTCertAdd::OnCbnSelchangeRtcertIndexCombo)
END_MESSAGE_MAP()


// CRTCertAdd 消息处理程序
BOOL CRTCertAdd::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN) 
	{
		if(GetFocus()->GetDlgCtrlID()==IDOK)//按下回车，如果当前焦点是在自己期望的控件上
        {                                           
            CRTCertAdd::OnBnClickedOk();//添加自己的处理代码
        }
		if(GetFocus()->GetDlgCtrlID()==IDCANCEL)//按下回车，如果当前焦点是在自己期望的控件上
        {                                           
            CRTCertAdd::OnBnClickedCancel();//添加自己的处理代码
        }
        return TRUE; 
	}
    if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)    
        return TRUE; 
    return CDialog::PreTranslateMessage(pMsg);
}

void CRTCertAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	INT_PTR nRes;
	unsigned int rtCert_index;
	UpdateData(TRUE);
	/***************************************************************/
	if(m_RTADD_certName_cs.IsEmpty())
	{
		MessageBox("证书名称不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_certName_cs.GetLength()>40)
	{
		MessageBox("证书名称最多为20个汉字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_certSN_cs.IsEmpty())
	{
		MessageBox("证书序列号不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_certSN_cs.GetLength()>32)
	{
		MessageBox("证书序列号最长不超过32位整数！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_atName_cs.IsEmpty())
	{
		MessageBox("机构名称不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_atName_cs.GetLength()>40)
	{
		MessageBox("机构名称最多为20个汉字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_hostName_cs.IsEmpty())
	{
		MessageBox("联系人不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_hostName_cs.GetLength()>20)
	{
		MessageBox("您输入的联系人名称太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_phone_cs.IsEmpty())
	{
		MessageBox("联系电话不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_RTADD_phone_cs.GetLength()>20)
	{
		MessageBox("电话号码太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(1 == isUp_rt && m_RTADD_rootCert_cs.IsEmpty())
	{
		MessageBox("请选择根证书！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	
	/**************************************************************************/
	void * hSessionHandle = phHandle_RtCertAdd;

	unsigned char pucCertName[50]={0x00};
	memcpy(pucCertName,m_RTADD_certName_cs.GetBuffer(),m_RTADD_certName_cs.GetLength());
	unsigned int uiCertNameLength = m_RTADD_certName_cs.GetLength();

	unsigned char pucCertSN[50]={0x00};
	memcpy(pucCertSN,m_RTADD_certSN_cs,m_RTADD_certSN_cs.GetLength());
	unsigned int  uiCertSNLength = m_RTADD_certSN_cs.GetLength();


	unsigned int uiAlgo;
	unsigned int uiKeyLength;
	if("SM2 256" == m_RTADD_certAlg_cs)
	{
		uiAlgo = SGD_SM2_1;
		uiKeyLength = 256;
	}
	if("RSA 1024" == m_RTADD_certAlg_cs)
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 1024;
	}
	if("RSA 2048" == m_RTADD_certAlg_cs)
	{
		uiAlgo = SGD_RSA;
		uiKeyLength = 2048;
	}

	unsigned char pucAtName[50]={0x00};
	memcpy(pucAtName,m_RTADD_atName_cs.GetBuffer(),m_RTADD_atName_cs.GetLength());
	unsigned int uiAtNameLength = m_RTADD_atName_cs.GetLength();

	unsigned char pucHost[50]={0x00};
	memcpy(pucHost,m_RTADD_hostName_cs.GetBuffer(),m_RTADD_hostName_cs.GetLength());
	unsigned int uiHostLength = m_RTADD_hostName_cs.GetLength();

	unsigned char pucPhone[50]={0x00};
	memcpy(pucPhone,m_RTADD_phone_cs.GetBuffer(),m_RTADD_phone_cs.GetLength());
	unsigned int uiPhoneLength = m_RTADD_phone_cs.GetLength();

	
	rtCert_index = atoi(m_rt_index_cs);   //新增加的输入0 
	
	if(0 == isUp_rt)
	{
//		ret = Sig_RootCertUpdate(hSessionHandle,uiAlgo,uiCertIndex,pucCertName,uiCertNameLength,pucAtName,uiAtNameLength,
//								pucHost,uiHostLength,pucPhone,uiPhoneLength);
		nRes = MessageBox("确定要更新该证书？","提示",MB_ICONQUESTION|MB_OKCANCEL);
		if(nRes != IDOK)
			return;
		
		ret = Sig_RootCertDel(hSessionHandle,1,&rtCert_index);
		if(0 != ret)
		{
			char outGapk[100]={0x00};
			retValueParse(ret,outGapk);
			MessageBox("(删除)操作失败"+(CString)outGapk,"提示");
			this->OnCancel();
			return;
		}
	}

	unsigned char *pucRtCert=NULL;
	unsigned int uiRtCertLength=0;
	int len = 0;

	unsigned char in_data[2048]={0x00};
	unsigned int  in_data_len=0;
	
	char *filename = (LPSTR)(LPCTSTR)certFilePath;
	CMyUtil::ReadData(filename,pucRtCert,&len);
	pucRtCert = new unsigned char[len];
	CMyUtil::ReadData(filename,pucRtCert,&len);
	uiRtCertLength = len;
	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\RtCert.txt",pucRtCert,len);

	char to_cmp[2]={0x30,0x82};
	//return;
	if(strncmp(to_cmp,(char*)pucRtCert,2) && !strncmp("M",(char*)pucRtCert,1))
	{
		//B64解码
		char dst[4096]={0x00};
		int length = 0;
		length = Km_Decode((char*)pucRtCert,len,dst);
		memcpy(in_data,dst,length);
		in_data_len = length;
	}
	else if(!strncmp(to_cmp,(char*)pucRtCert,2) && strncmp("M",(char*)pucRtCert,1))
	{
		//直接传
		memcpy(in_data,pucRtCert,len);
		in_data_len = len;
	}
	else if(strstr((char*)pucRtCert,"BEGIN CERTIFICATE"))
	{//pem编码
		PKI_DATA in_cert,out_cert;
		in_cert.size = len;
		out_cert.size=0;
		out_cert.value = new unsigned char[2048];
		in_cert.value = new unsigned char[len+1];
		memset(in_cert.value,0x00,len+1);
		memcpy(in_cert.value,pucRtCert,len);
		pkiBase64Decode(in_cert,&out_cert);
		memcpy(in_data,out_cert.value,out_cert.size);
		in_data_len = out_cert.size;

	}
	else
	{
		MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		return;
	}

	ret = Sig_RootCertAdd(hSessionHandle,pucCertName,uiCertNameLength,rtCert_index,uiAlgo,pucAtName,uiKeyLength,uiAtNameLength,
							pucHost,uiHostLength,pucPhone,uiPhoneLength,in_data,in_data_len,pucCertSN,uiCertSNLength);
	   //在增加根证书时，把证书索引号固定为0，这样后台判断，如果为0时，根据系统自动生成
	if(0 == ret)
	{
		MessageBox("操作成功","提示");
		delete []pucRtCert;
		this->OnOK();
		return;
	}
	else if(0 != ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("操作失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucRtCert;
		//this->OnCancel();
		return;
	}
//	delete []pucRtCert;
	//CDialogEx::OnOK();
}


void CRTCertAdd::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CRTCertAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//设置CComBox下拉框为只读防止用户自己输入造成不必要的错误
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_RTADD_ALG))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CEdit* pEdit1 = (CEdit*)(((CComboBox*)GetDlgItem(IDC_RTCERT_INDEX_COMBO))->GetWindow(GW_CHILD));	
	pEdit1->SetReadOnly(TRUE);
	CWnd *cWnd = GetDlgItem(IDC_RTCERT_TITLE_STATIC);
	if(isUp_rt)
	{
		this->SetWindowText("添加根证书");
		cWnd->SetWindowText("添加根证书");

		 //TODO:  在此添加额外的初始化
		int one = rtAddIndex;
		CString cs_certIndex;
		CString index;
		index.Format("%3d",one);
		cs_certIndex = index;//数据的格式化操作，需要再写一个新的方法 
		SetDlgItemText(IDC_RTCERT_INDEX_COMBO,cs_certIndex);

		int data = 0;
		for(int i=0;i<256;i++)
		{
			if(1 == rtAddIndex_array[i][1])
			{
				data = rtAddIndex_array[i][0];
				index.Format("%3d",data);
				cs_certIndex = index;
				m_rt_index.AddString(cs_certIndex);
				//m_rt_index.InsertString(i,cs_certIndex);
				//m_rt_index.InsertString(i-1,_T(cs_certIndex));
			}
		}
		
	}
	else if(!isUp_rt)
	{
		this->SetWindowText("更新根证书");
		cWnd->SetWindowText("更新根证书");
		SetDlgItemText(IDC_RTADD_CERTNAME_EDIT,m_RTADD_certName_cs);
		SetDlgItemText(IDC_COMBO_RTADD_ALG,m_RTADD_certAlg_cs);  
		SetDlgItemText(IDC_RTCERT_INDEX_COMBO,m_RTADD_certindex_cs);  
		SetDlgItemText(IDC_RTADD_ATNAME_EDIT,m_RTADD_atName_cs);  
		SetDlgItemText(IDC_RTADD_HOST_EDIT,m_RTADD_hostName_cs);  
		SetDlgItemText(IDC_RTADD_PHONE_EDIT,m_RTADD_phone_cs);  
		return TRUE;
	}
	
	// TODO:  在此添加额外的初始化
	/*m_RTADD_certAlg.AddString("RSA 1024");
	m_RTADD_certAlg.AddString("RSA 2048");
	m_RTADD_certAlg.AddString("SM2 256");
	SetDlgItemText(IDC_COMBO_RTADD_ALG, _T("SM2 256"));*/  
	
	//---------------------判断证书索引号是否已用
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRTCertAdd::OnBnClickedImrtcButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("(*.cer)|*.cer|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("cer"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
	int ret;
	unsigned char *pucRtCert_File=NULL;   //刚从文件中读出的证书数据
	unsigned int uiRtCert_FileLength=0;     

	unsigned char *pucRtCert=NULL;    //转换后的证书数据
	unsigned int uiRtCertLength=0;
	void * hSessionHandle = phHandle_RtCertAdd;




	unsigned char ucnode[1024]={0x00};
	unsigned int  uinode_len = 0;
	unsigned char ucItemValue[100]={0x00};
	unsigned int  uiItemValue_len;
	CString cert_sn;
	CString dn_cn;
	CString algId;
	CString dn_o;

	unsigned int  o_certInfoLen = 0;
	unsigned char * o_certInfo = NULL;
	unsigned int  o_publicKeyLen = 0;
	unsigned char * o_publicKey = NULL;

    // 显示打开文件对话框  
    if (IDOK != fileDlg.DoModal())   
    {   
  //      // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
  //      strFilePath = fileDlg.GetPathName();   
		//certFilePath = strFilePath;
  //      SetDlgItemText(IDC_RTADD_IMCAPATH_EDIT, strFilePath);   
		return ;
    } 
	else{
		 // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();   
		certFilePath = strFilePath;
        SetDlgItemText(IDC_RTADD_IMCAPATH_EDIT, strFilePath);   
	}
	
	//读取根证书文件
	char *filename = (LPSTR)(LPCTSTR)certFilePath;
	CMyUtil::ReadData(filename,pucRtCert_File,(int *)&uiRtCert_FileLength);
	pucRtCert_File = new unsigned char[uiRtCert_FileLength];
	CMyUtil::ReadData(filename,pucRtCert_File,(int *)&uiRtCert_FileLength);
	


	//读入数据格式判断 ，如果是B64编码或者PEM编码 ，全部转换成二进制格式
	ret = CMyUtil::Cert2Dercert(pucRtCert_File,uiRtCert_FileLength,NULL,&uiRtCertLength);
	if (ret<0)
	{
	   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
	   delete []pucRtCert_File;
	   return ;
	}
	else
	{  
		pucRtCert = new unsigned char[uiRtCert_FileLength+1];
		ret =  CMyUtil::Cert2Dercert(pucRtCert_File,uiRtCert_FileLength,pucRtCert,&uiRtCertLength);
		if (ret<0)
		{
		   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		   delete []pucRtCert_File;
		   delete []pucRtCert;
		   return ;
		}
	}
	//解析证书

	ret = PKI_GetXMLCertInfo(hSessionHandle,uiRtCertLength,pucRtCert, &o_certInfoLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucRtCert_File;
		delete []pucRtCert;
		return;
	}
	o_certInfo  = new unsigned char[o_certInfoLen];
	ret = PKI_GetXMLCertInfo(hSessionHandle,uiRtCertLength,pucRtCert,&o_certInfoLen,o_certInfo);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucRtCert_File;
		delete []pucRtCert;
		delete []o_certInfo;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\o_certInfo.txt",o_certInfo,o_certInfoLen);

	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"subject",ucnode,&uinode_len);  //取出主题项的内容
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_o",ucItemValue,&uiItemValue_len);  //取出O项内容
	SetDlgItemText(IDC_RTADD_ATNAME_EDIT,(LPCTSTR)ucItemValue);  
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_cn",ucItemValue,&uiItemValue_len);  //取出名称项
	SetDlgItemText(IDC_RTADD_CERTNAME_EDIT,(LPCTSTR)ucItemValue);

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"serialnum",ucItemValue,&uiItemValue_len);
	SetDlgItemText(IDC_RTADD_CERTINDEX_EDIT,(LPCTSTR)ucItemValue);  

	//----获取证书算法
	ret = PKI_GetPublicKeyFromCert(hSessionHandle,uiRtCertLength,pucRtCert, &o_publicKeyLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("获取算法标识失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucRtCert_File;
		delete []pucRtCert;
		return;
	}
	o_publicKey  = new unsigned char[o_publicKeyLen];
	ret = PKI_GetPublicKeyFromCert(hSessionHandle,uiRtCertLength,pucRtCert,&o_publicKeyLen,o_publicKey);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("获取算法标识失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucRtCert_File;
		delete []pucRtCert;
		delete []o_publicKey;
		return;
	}
	SetDlgItemText(IDC_COMBO_RTADD_ALG,(LPCTSTR)o_publicKey); 
	delete []pucRtCert;
	delete []o_certInfo;
	delete []o_publicKey;
}


void CRTCertAdd::OnCbnSelchangeRtcertIndexCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel; 
    nSel =m_rt_index.GetCurSel();//获取组合框控件列表里的选中项索引
	m_rt_index_cs.Format("%d", (nSel));
	m_rt_index.GetLBText(nSel,m_rt_index_cs);
}
