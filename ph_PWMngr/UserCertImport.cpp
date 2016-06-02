// UserCertImport.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "UserCertImport.h"
#include "afxdialogex.h"

#include "MyUtil.h"
#include "ph_km.h"
// CUserCertImport 对话框
unsigned char *pucUsrKey_File=NULL;   //刚从文件中读出的证书数据
unsigned int uiUserKey_FileLength=0;     

IMPLEMENT_DYNAMIC(CUserCertImport, CDialogEx)

CUserCertImport::CUserCertImport(void *hand,int keyindex,int keyType,int AsymmAlgo,CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserCertImport::IDD, pParent)
	, m_certname_uc(_T(""))
	, m_algid_uc(_T(""))
	, m_certserial_uc(_T(""))
	, m_atname_uc(_T(""))
	, m_hostname_uc(_T(""))
	, m_hostphone_uc(_T(""))
	, m_usercertpath(_T(""))
	, m_cacert_indexname(_T(""))
	, m_sigcert_usradd(_T(""))
	, m_uc_pin_f(_T(""))
	, m_uc_pin_s(_T(""))
{
	phHandle_usrCertAdd = hand;
	appKeyType = keyType;
	appkeyindex = keyindex;
	asymmAlgo=AsymmAlgo;
}

CUserCertImport::~CUserCertImport()
{
}

void CUserCertImport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USRADD_CERTNAME_EDIT, m_certname_uc);
	DDX_CBString(pDX, IDC_COMBO_USRADD_ALG, m_algid_uc);
	DDX_Text(pDX, IDC_USRADD_CERTINDEX_EDIT, m_certserial_uc);
	DDX_Text(pDX, IDC_USRADD_ATNAME_EDIT, m_atname_uc);
	DDX_Text(pDX, IDC_USRADD_HOST_EDIT, m_hostname_uc);
	DDX_Text(pDX, IDC_USRADD_PHONE_EDIT, m_hostphone_uc);
	DDX_Text(pDX, IDC_USRADD_IMPATH_EDIT, m_usercertpath);
	DDX_Control(pDX, IDC_COMBO_USRADD_CERT, m_cacert);
	DDX_CBString(pDX, IDC_COMBO_USRADD_CERT, m_cacert_indexname);
	DDX_Control(pDX, IDC_COMBO_USRADD_ALG, m_algid_cbox);
	DDX_Text(pDX, IDC_USRADD_SIGCERT_IMPORT, m_sigcert_usradd);
	DDX_Text(pDX, IDC_EDIT_uc_pin_f, m_uc_pin_f);
	DDX_Text(pDX, IDC_EDIT_uc_pin_s, m_uc_pin_s);
	DDX_Text(pDX, IDC_USRCERTINDEX2, m_certserial2_uc);
}


BEGIN_MESSAGE_MAP(CUserCertImport, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserCertImport::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUserCertImport::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_IMUSR_BUTTON, &CUserCertImport::OnBnClickedImusrButton)
	ON_BN_CLICKED(IDC_USRSIGCERT_IMPORT_BUTTON, &CUserCertImport::OnBnClickedUsrsigcertImportButton)
	ON_BN_CLICKED(IDC_USERADD_ENCRYFILE_IMPORT_BUTTON, &CUserCertImport::OnBnClickedUseraddEncryfileImportButton)
END_MESSAGE_MAP()


// CUserCertImport 消息处理程序


void CUserCertImport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	UpdateData(TRUE);
	unsigned int uiKeyType = appKeyType;
	CString isis;
	isis.Format("%d",appKeyType);
	//MessageBox("appKeyType = "+(CString)isis);
	if(m_certname_uc.IsEmpty())
	{
		MessageBox("请输入证书名称！","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(m_certname_uc.GetLength()>20)
	{
		MessageBox("证书名称太长了！","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(m_certserial_uc.IsEmpty())
	{
		MessageBox("证书序列号不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_certserial_uc.GetLength()>32)
	{
		MessageBox("证书序列号最长不超过32位整数！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_atname_uc.IsEmpty())
	{
		MessageBox("机构名称不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_atname_uc.GetLength()>40)
	{
		MessageBox("机构名称最多为20个汉字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_hostname_uc.IsEmpty())
	{
		MessageBox("联系人不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_hostname_uc.GetLength()>20)
	{
		MessageBox("您输入的联系人名称太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_hostphone_uc.IsEmpty())
	{
		MessageBox("联系电话不能为空！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_hostphone_uc.GetLength()>20)
	{
		MessageBox("电话号码太长了！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(appKeyType == 2)
	{
		if(m_usercertpath.IsEmpty())
		{
			MessageBox("请导入加密证书！","提示",MB_ICONWARNING | MB_OK);
			return;
		}
		if(m_sigcert_usradd.IsEmpty())
		{
			MessageBox("请导入签名证书！","提示",MB_ICONWARNING | MB_OK);
			return;
		}
	}
	if(m_cacert_indexname.IsEmpty())
	{
		MessageBox("请选择CA证书！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_uc_pin_f.GetLength()<8)
	{
		MessageBox("PIN码长度不能小于8位！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(m_uc_pin_f != m_uc_pin_s)
	{
		MessageBox("两次PIN码输入不一致！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
	if(CMyUtil::isNum((LPSTR)(LPCTSTR)m_uc_pin_f))
	{
		MessageBox("PIN码不能全是数字！","提示",MB_ICONWARNING | MB_OK);
		return;
	}

	/*if(m_certserial_uc != m_certserial2_uc )
	{
		
		MessageBox("不是同一张证书！","提示",MB_ICONWARNING | MB_OK);
		return;
	}
    */
	void * hSessionHandle;
	hSessionHandle = phHandle_usrCertAdd;
	unsigned int uiCACertIndex;

	char caindex[32]={0x00};
	memcpy(caindex,m_cacert_indexname.GetBuffer(),m_cacert_indexname.GetLength());
	uiCACertIndex = atoi(caindex);

	unsigned int uiAlgid;
	unsigned int uiKeyLength;

	if(m_algid_uc == "SM2 256")
	{
		uiAlgid = SGD_SM2_1;
		uiKeyLength = 256;
	}
	if(m_algid_uc == "RSA 1024")
	{
		uiAlgid = SGD_RSA;
		uiKeyLength = 1024;
	}
	if(m_algid_uc == "RSA 2048")
	{
		uiAlgid = SGD_RSA;
		uiKeyLength = 2048;
	}

	unsigned int uiKeyIndex = appkeyindex;
	unsigned int uiCertIndexLength;
	unsigned char putCertIndex[32]={0x00};
	memcpy(putCertIndex,m_certserial_uc.GetBuffer(),m_certserial_uc.GetLength());
	uiCertIndexLength =  m_certserial_uc.GetLength();

	unsigned int uiCertNameLength;
	unsigned char pucCertName[64]={0x00};;
	memcpy(pucCertName,m_certname_uc.GetBuffer(),m_certname_uc.GetLength());
	uiCertNameLength=m_certname_uc.GetLength();

	unsigned int uiAtNameLength;
	unsigned char pucAtName[64]={0x00};;
	memcpy(pucAtName,m_atname_uc.GetBuffer(),m_atname_uc.GetLength());
	uiAtNameLength = m_atname_uc.GetLength();

	unsigned int uiHostLength;
	unsigned char pucHost[32]={0x00};
	memcpy(pucHost,m_hostname_uc.GetBuffer(),m_hostname_uc.GetLength());
	uiHostLength = m_hostname_uc.GetLength();

	unsigned int uiPhoneLength;
	unsigned char pucPhone[32]={0x00};
	memcpy(pucPhone,m_hostphone_uc.GetBuffer(),m_hostphone_uc.GetLength());
	uiPhoneLength = m_hostphone_uc.GetLength();

	unsigned int uiPrivateKeyAccessRightCodeLength=m_uc_pin_f.GetLength();
	unsigned char pucPrivateKeyAccessRightCode[32]={0x00};
	memcpy(pucPrivateKeyAccessRightCode,m_uc_pin_f.GetBuffer(),m_uc_pin_f.GetLength());

	unsigned int uiUsrEncCertLength=0;
	unsigned char *pucUsrEncCert=NULL;
	unsigned int uiUsrSigCertLength=0;
	unsigned char *pucUsrSigCert=NULL;
	int len = 0;
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_usercertpath,pucUsrEncCert,&len);
	uiUsrEncCertLength = len;
	pucUsrEncCert = new unsigned char[len+1];
	memset(pucUsrEncCert,0x00,len+1);
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_usercertpath,pucUsrEncCert,&len);

	unsigned char in_data[2048]={0x00};
	unsigned int  in_data_len=0;
	if(0 != CMyUtil::IsCertFile(pucUsrEncCert,len,in_data,&in_data_len))
	{
		MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		return;
	}

	int lensig=0;
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_sigcert_usradd,pucUsrSigCert,&lensig);
	uiUsrSigCertLength = lensig;
	pucUsrSigCert = new unsigned char[lensig+1];
	memset(pucUsrSigCert,0x00,lensig+1);
	CMyUtil::ReadData((LPSTR)(LPCTSTR)m_sigcert_usradd,pucUsrSigCert,&lensig);
	unsigned char in_data_sig[2048]={0x00};
	unsigned int  in_data_sig_len=0;
	if(0 != CMyUtil::IsCertFile(pucUsrSigCert,lensig,in_data_sig,&in_data_sig_len))
	{
		MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		return;
	}

	if(uiUserKey_FileLength<0)
	{


		ret = Sig_UserCertImport(hSessionHandle,uiCACertIndex,uiAlgid,uiKeyLength,uiKeyType,uiKeyIndex,uiCertIndexLength,putCertIndex,uiCertNameLength,pucCertName,uiAtNameLength,
								pucAtName,uiHostLength,pucHost,uiPhoneLength,pucPhone,in_data_len,in_data,in_data_sig_len,in_data_sig,uiPrivateKeyAccessRightCodeLength,
								pucPrivateKeyAccessRightCode);
		if(0 == ret)
		{
			MessageBox("操作成功，重启服务器后生效！","成功",MB_ICONEXCLAMATION);
		}
		else if(0 != ret)
		{
			char outCACertAddError[100]={0x00};
			retValueParse(ret,outCACertAddError);
			MessageBox("    操作失败"+(CString)outCACertAddError,"提示");
			delete []pucUsrEncCert;
			delete []pucUsrSigCert;
			return;
		}
	}
	else
	{
	  ret=0;
	   int encType=1;
	   unsigned char keyIndexBuf[32]={0x00};
	   unsigned int uiIndexLength;
	   sprintf((char *)keyIndexBuf,"%d",uiKeyIndex);
	   uiIndexLength=strlen((char *)keyIndexBuf);

     ret = Sig_UserCertImport(hSessionHandle,uiCACertIndex,uiAlgid,uiKeyLength,uiKeyType,uiKeyIndex,uiCertIndexLength,putCertIndex,uiCertNameLength,pucCertName,uiAtNameLength,
								pucAtName,uiHostLength,pucHost,uiPhoneLength,pucPhone,in_data_len,in_data,in_data_sig_len,in_data_sig,uiPrivateKeyAccessRightCodeLength,
								pucPrivateKeyAccessRightCode);
      if(0 != ret)
		{
			char outCACertAddError[100]={0x00};
			retValueParse(ret,outCACertAddError);
			MessageBox("    操作失败"+(CString)outCACertAddError,"提示");
			delete []pucUsrEncCert;
			delete []pucUsrSigCert;
			return;
		}
       ret = Sig_ImportEncCert(hSessionHandle,uiAlgid,uiIndexLength,keyIndexBuf,uiPrivateKeyAccessRightCodeLength,pucPrivateKeyAccessRightCode,
				   in_data_len,in_data,in_data_sig_len,in_data_sig,0,NULL,uiUserKey_FileLength,pucUsrKey_File,3);
	   					
		if(0 == ret)
		{
			MessageBox("操作成功，重启服务器后生效！","成功",MB_ICONEXCLAMATION);
		}
		else if(0 != ret)
		{
			char outCACertAddError[100]={0x00};
			retValueParse(ret,outCACertAddError);
			MessageBox("    操作失败"+(CString)outCACertAddError,"提示");
			delete []pucUsrEncCert;
			delete []pucUsrSigCert;
			return;
		}
	}
	delete []pucUsrEncCert;
	delete []pucUsrSigCert;
	CDialogEx::OnOK();
}


BOOL CUserCertImport::OnInitDialog()
{
	
	CEdit* pEdit = (CEdit*)(((CComboBox*)GetDlgItem(IDC_COMBO_USRADD_ALG))->GetWindow(GW_CHILD));	
	pEdit->SetReadOnly(TRUE);
	CDialogEx::OnInitDialog();
	unsigned int indexSet[256]={0};
	unsigned int algTemp[256] = {0};
	unsigned int num = 0;
	pucUsrKey_File=NULL;
	uiUserKey_FileLength=0;
	CMyUtil::GetCACertIndexSet(phHandle_usrCertAdd,&num,indexSet,algTemp);
	if(0 != num)
	{
		for(unsigned int i=0;i<num;i++)
		{
		
			CString ind,alg;
			ind.Format("%d",indexSet[i]);
			//m_rootCert_choseCAA.AddString(ind+"_RootCert.cer");
			if(2048 == algTemp[i])
			{
				alg.Format("%d",algTemp[i]);
				m_cacert.AddString(ind+"_RSA"+alg+"_CACert.cer");
			}
			if(1024 == algTemp[i])
			{
				alg.Format("%d",algTemp[i]);
				m_cacert.AddString(ind+"_RSA"+alg+"_CACert.cer");
			}
			if(256 == algTemp[i])
			{
				alg.Format("%d",algTemp[i]);
				m_cacert.AddString(ind+"_SM2"+alg+"_CACert.cer");
			}
		}
	}
	else
	{
		SetDlgItemText(IDC_COMBO_USRADD_CERT, _T("系统尚未导入CA证书！")); 
	}

	// TODO:  在此添加额外的初始化
	/*m_algid_cbox.AddString("RSA 1024");
	m_algid_cbox.AddString("RSA 2048");
	m_algid_cbox.AddString("SM2 256");*/
	if(asymmAlgo==1)
      SetDlgItemText(IDC_COMBO_USRADD_ALG,"RSA 1024");
	if(asymmAlgo==2)
      SetDlgItemText(IDC_COMBO_USRADD_ALG,"RSA 2048");	
	if(asymmAlgo==3)
	SetDlgItemText(IDC_COMBO_USRADD_ALG,"SM2 256"); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUserCertImport::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CUserCertImport::OnBnClickedImusrButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("(*.cer)|*.cer|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("cer"), NULL, 0, szFilter, this);   
    CString strFilePath; 
	/***********************************/
	int ret;
	unsigned char *pucUsrCert_File=NULL;   //刚从文件中读出的证书数据
	unsigned int uiUserCert_FileLength=0;     

	unsigned char *pucUsrCert=NULL;    //转换后的证书数据
	unsigned int uiUsrCertLength=0;
	void * hSessionHandle = phHandle_usrCertAdd;




	unsigned char ucnode[1024]={0x00};
	unsigned int  uinode_len = 0;
	unsigned char ucItemValue[100]={0x00};
	unsigned int  uiItemValue_len;
	CString cert_sn;
	CString dn_cn;
	CString algId;
	CString dn_o;

	unsigned int  o_certInfoLen;
	unsigned char * o_certInfo;
	/***********************************/

  
    // 显示打开文件对话框  
    if (IDOK != fileDlg.DoModal())   
    {   
//        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
//        strFilePath = fileDlg.GetPathName();  
////		m_CAcert_path = strFilePath;
//        SetDlgItemText(IDC_USRADD_IMPATH_EDIT, strFilePath);   
		return ;
    } 
	else{
		 
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        SetDlgItemText(IDC_USRADD_IMPATH_EDIT, strFilePath); 
	}
	//读取证书文件
	char *filename = (LPSTR)(LPCTSTR)strFilePath;
	CMyUtil::ReadData(filename,pucUsrCert_File,(int *)&uiUserCert_FileLength);
	pucUsrCert_File = new unsigned char[uiUserCert_FileLength];
	CMyUtil::ReadData(filename,pucUsrCert_File,(int *)&uiUserCert_FileLength);
	


	//读入数据格式判断 ，如果是B64编码或者PEM编码 ，全部转换成二进制格式
	ret = CMyUtil::Cert2Dercert(pucUsrCert_File,uiUserCert_FileLength,NULL,&uiUsrCertLength);
	if (ret<0)
	{
	   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
	   delete []pucUsrCert_File;
	   return ;
	}
	else
	{  
		pucUsrCert = new unsigned char[uiUserCert_FileLength+1];
		ret =  CMyUtil::Cert2Dercert(pucUsrCert_File,uiUserCert_FileLength,pucUsrCert,&uiUsrCertLength);
		if (ret<0)
		{
		   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		   delete []pucUsrCert_File;
		   delete []pucUsrCert;
		   return ;
		}
	}
	//解析证书

	ret = PKI_GetXMLCertInfo(hSessionHandle,uiUsrCertLength,pucUsrCert,&o_certInfoLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucUsrCert_File;
		delete []pucUsrCert;
		return;
	}
	o_certInfo  = new unsigned char[o_certInfoLen];
	ret = PKI_GetXMLCertInfo(hSessionHandle,uiUsrCertLength,pucUsrCert,&o_certInfoLen,o_certInfo);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucUsrCert_File;
		delete []pucUsrCert;
		delete []o_certInfo;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\o_certInfo.txt",o_certInfo,o_certInfoLen);

	


	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"subject",ucnode,&uinode_len);  //取出主题项的内容
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_o",ucItemValue,&uiItemValue_len);  //取出O项内容
	SetDlgItemText(IDC_USRADD_ATNAME_EDIT,(LPCTSTR)ucItemValue);  
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_cn",ucItemValue,&uiItemValue_len);  //取出名称项
	SetDlgItemText(IDC_USRADD_CERTNAME_EDIT,(LPCTSTR)ucItemValue);
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"serialnum",ucItemValue,&uiItemValue_len);
	SetDlgItemText(IDC_USRADD_CERTINDEX_EDIT,(LPCTSTR)ucItemValue); 
	

	//memset(ucItemValue,0x00,100);
	//CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"algorithm",ucItemValue,&uiItemValue_len);
	//SetDlgItemText(IDC_COMBO_RTADD_ALG,(LPCTSTR)ucItemValue);  
	delete []pucUsrCert;
	delete []o_certInfo;

}


void CUserCertImport::OnBnClickedUsrsigcertImportButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("(*.cer)|*.cer|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("cer"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
	/***********************************/
	int ret;
	unsigned char *pucUsrCert_File=NULL;   //刚从文件中读出的证书数据
	unsigned int uiUserCert_FileLength=0;     

	unsigned char *pucUsrCert=NULL;    //转换后的证书数据
	unsigned int uiUsrCertLength=0;
	void * hSessionHandle = phHandle_usrCertAdd;




	unsigned char ucnode[1024]={0x00};
	unsigned int  uinode_len = 0;
	unsigned char ucItemValue[100]={0x00};
	unsigned int  uiItemValue_len;
	CString cert_sn;
	CString dn_cn;
	CString algId;
	CString dn_o;

	unsigned int  o_certInfoLen;
	unsigned char * o_certInfo;
	/***********************************/

    // 显示打开文件对话框  
    if (IDOK != fileDlg.DoModal())   
    {   
//        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
//        strFilePath = fileDlg.GetPathName();  
////		m_CAcert_path = strFilePath;
//        SetDlgItemText(IDC_USRADD_SIGCERT_IMPORT, strFilePath);   
		return ;
    } 
	else{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        SetDlgItemText(IDC_USRADD_SIGCERT_IMPORT, strFilePath);  
	}
	//读取证书文件
	char *filename = (LPSTR)(LPCTSTR)strFilePath;
	CMyUtil::ReadData(filename,pucUsrCert_File,(int *)&uiUserCert_FileLength);
	pucUsrCert_File = new unsigned char[uiUserCert_FileLength];
	CMyUtil::ReadData(filename,pucUsrCert_File,(int *)&uiUserCert_FileLength);
	


	//读入数据格式判断 ，如果是B64编码或者PEM编码 ，全部转换成二进制格式
	ret = CMyUtil::Cert2Dercert(pucUsrCert_File,uiUserCert_FileLength,NULL,&uiUsrCertLength);
	if (ret<0)
	{
	   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
	   delete []pucUsrCert_File;
	   return ;
	}
	else
	{  
		pucUsrCert = new unsigned char[uiUserCert_FileLength+1];
		ret =  CMyUtil::Cert2Dercert(pucUsrCert_File,uiUserCert_FileLength,pucUsrCert,&uiUsrCertLength);
		if (ret<0)
		{
		   MessageBox("请确认导入的是证书文件！","数据格式错误",MB_ICONWARNING);
		   delete []pucUsrCert_File;
		   delete []pucUsrCert;
		   return ;
		}
	}
	//解析证书

	ret = PKI_GetXMLCertInfo(hSessionHandle,uiUsrCertLength,pucUsrCert, &o_certInfoLen,NULL);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucUsrCert_File;
		delete []pucUsrCert;
		return;
	}
	o_certInfo  = new unsigned char[o_certInfoLen];
	ret = PKI_GetXMLCertInfo(hSessionHandle,uiUsrCertLength,pucUsrCert,&o_certInfoLen,o_certInfo);
	if (0!=ret)
	{
		char outGapk[100]={0x00};
		retValueParse(ret,outGapk);
		MessageBox("解析证书失败"+(CString)outGapk,"提示",MB_ICONEXCLAMATION);
		delete []pucUsrCert_File;
		delete []pucUsrCert;
		delete []o_certInfo;
		return;
	}

	//CMyUtil::Write2File("C:\\Users\\Administrator\\Desktop\\o_certInfo.txt",o_certInfo,o_certInfoLen);

	


	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"subject",ucnode,&uinode_len);  //取出主题项的内容
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_o",ucItemValue,&uiItemValue_len);  //取出O项内容
	SetDlgItemText(IDC_USRADD_ATNAME_EDIT,(LPCTSTR)ucItemValue);  
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(ucnode,(unsigned char *)"dn_cn",ucItemValue,&uiItemValue_len);  //取出名称项
	SetDlgItemText(IDC_USRADD_CERTNAME_EDIT,(LPCTSTR)ucItemValue);
	

	memset(ucItemValue,0x00,100);
	CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"serialnum",ucItemValue,&uiItemValue_len);
	SetDlgItemText(IDC_USRCERTINDEX2,(LPCTSTR)ucItemValue);  
	
	//memset(ucItemValue,0x00,100);
	//CMyUtil::GetParamFromString(o_certInfo,(unsigned char *)"algorithm",ucItemValue,&uiItemValue_len);
	//SetDlgItemText(IDC_COMBO_RTADD_ALG,(LPCTSTR)ucItemValue);  
	delete []pucUsrCert;
	delete []o_certInfo;


}


void CUserCertImport::OnBnClickedUseraddEncryfileImportButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器  
    TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");   
    // 构造打开文件对话框  
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
	/***********************************/
	//int ret;
	 // 显示打开文件对话框  
    if (IDOK != fileDlg.DoModal())   
    {           
		return ;
    } 
	else{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里  
        strFilePath = fileDlg.GetPathName();  
//		m_CAcert_path = strFilePath;
        //SetDlgItemText(IDC_USRADD_SIGCERT_IMPORT, strFilePath);  
		SetDlgItemText(IDC_USERADD_ENCRYFILE_IMPORT, strFilePath);  
	}
	//读取密钥文件
	char *filename = (LPSTR)(LPCTSTR)strFilePath;
	CMyUtil::ReadData(filename,pucUsrKey_File,(int *)&uiUserKey_FileLength);
	pucUsrKey_File = new unsigned char[uiUserKey_FileLength];
	CMyUtil::ReadData(filename,pucUsrKey_File,(int *)&uiUserKey_FileLength);
	


	
}
