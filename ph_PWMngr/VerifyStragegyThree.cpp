// VerifyStragegyThree.cpp : 实现文件
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "VerifyStragegyThree.h"
#include "afxdialogex.h"


// CVerifyStragegyThree 对话框

IMPLEMENT_DYNAMIC(CVerifyStragegyThree, CDialogEx)

CVerifyStragegyThree::CVerifyStragegyThree(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVerifyStragegyThree::IDD, pParent)
	, m_day(_T(""))
	, m_hour(_T(""))
	, m_minute(_T(""))
	, m_second(_T(""))
{

}

CVerifyStragegyThree::~CVerifyStragegyThree()
{
}

void CVerifyStragegyThree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CRLREL, m_day);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_hour);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_minute);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_second);
}


BEGIN_MESSAGE_MAP(CVerifyStragegyThree, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_vs3_1, &CVerifyStragegyThree::OnBnClickedButtonvs31)
END_MESSAGE_MAP()


// CVerifyStragegyThree 消息处理程序


BOOL CVerifyStragegyThree::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	upTime = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CVerifyStragegyThree::OnBnClickedButtonvs31()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;
	UpdateData(TRUE);

	unsigned int	days;
	unsigned int	hour;
	unsigned int	minute;
	unsigned int	second;
//	unsigned int	updateTime;
	if(m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
	{
		MessageBox("请设置CRL更新周期！","提示",MB_ICONEXCLAMATION);
		return;
	}
	if(!m_day.IsEmpty())
	{
		days = atoi(m_day);
		if(days>365)
		{
			nRes = MessageBox("您设置的CRL列表文件更新周期较长，确定要继续？","提示",MB_ICONQUESTION|MB_OKCANCEL);
			if(nRes != IDOK)
				return;
		}
	}
	if(!m_day.IsEmpty())
	{
		t_day = m_day;
	}
	if(!m_hour.IsEmpty())
	{
		hour = atoi(m_hour);
		t_hour = m_hour;
	}
	if(!m_minute.IsEmpty())
	{
		minute = atoi(m_minute);
		t_minute = m_minute;
	}
	if(!m_second.IsEmpty())
	{
		second = atoi(m_second);
		t_second = m_second;
	}
	
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + minute*60 + second;
	//一项为空
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = hour*60*60 + minute*60 + second;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + minute*60 + second;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + second;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + minute*60;
	//两项为空
	if(m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = minute*60 + second;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = hour*60*60 + second;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = hour*60*60 + minute*60;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + second;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + minute*60;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60;
	//三项为空
	if(m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = second;
	if(m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = minute*60;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = hour*60*60;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60;
}
int CVerifyStragegyThree::GetDataVS3()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;
	UpdateData(TRUE);

	unsigned int	days;
	unsigned int	hour;
	unsigned int	minute;
	unsigned int	second;
//	unsigned int	updateTime;
	/*if(m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
	{
		MessageBox("请设置CRL更新周期！","提示",MB_ICONEXCLAMATION);
		return -1;
	}*/
	if(!m_day.IsEmpty())
	{
		days = atoi(m_day);
		if(days>365)
		{
			nRes = MessageBox("您设置的CRL列表文件更新周期较长，确定要继续？","提示",MB_ICONQUESTION|MB_OKCANCEL);
			if(nRes != IDOK)
				return-1;
		}
	}
	if(!m_day.IsEmpty())
	{
		t_day = m_day;
	}
	if(!m_hour.IsEmpty())
	{
		hour = atoi(m_hour);
		t_hour = m_hour;
	}
	if(!m_minute.IsEmpty())
	{
		minute = atoi(m_minute);
		t_minute = m_minute;
	}
	if(!m_second.IsEmpty())
	{
		second = atoi(m_second);
		t_second = m_second;
	}
	
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + minute*60 + second;
	//一项为空
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = hour*60*60 + minute*60 + second;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + minute*60 + second;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + second;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60 + minute*60;
	//两项为空
	if(m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = minute*60 + second;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = hour*60*60 + second;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = hour*60*60 + minute*60;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = days*24*60*60 + second;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + minute*60;
	if(!m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60*60 + hour*60*60;
	//三项为空
	if(m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && !m_second.IsEmpty())
		upTime = second;
	if(m_day.IsEmpty() && m_hour.IsEmpty() && !m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = minute*60;
	if(m_day.IsEmpty() && !m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = hour*60*60;
	if(!m_day.IsEmpty() && m_hour.IsEmpty() && m_minute.IsEmpty() && m_second.IsEmpty())
		upTime = days*24*60;
	return 0;
}

int CVerifyStragegyThree::GetVS3Time(unsigned int *updateTsime)
{
	//-----------------------------------获取数据
	CVerifyStragegyThree::GetDataVS3();
	//------------------------------------------
	/*if(t_day.IsEmpty() && t_hour.IsEmpty() && t_minute.IsEmpty() && t_second.IsEmpty())
	{
		MessageBox("请设置CRL更新周期！","提示",MB_ICONEXCLAMATION);
		return -1;
	}*/
	*updateTsime = upTime;
	return 0;
}

void CVerifyStragegyThree::SetVS3_Time(unsigned int vs_time)
{
	int in_day=0,in_hour=0,in_minute=0,in_second=0;
	CString cs_day,cs_hour,cs_minute,cs_second;
	in_day = vs_time/(24*60*60);
	//in_hour = vs_time/(60*60);
	//in_minute = vs_time/60;


	if(in_day > 0)
	{
		cs_day.Format("%d",in_day);
		in_hour = (vs_time-in_day*24*60*60)/(60*60);
		if(in_hour>0)
		{
			cs_hour.Format("%d",in_hour);
			in_minute = (vs_time-in_day*24*60*60-in_hour*60*60)/(60);
			if(in_minute>0)
			{
				cs_minute.Format("%d",in_minute);
				in_second = vs_time-in_day*24*60*60-in_hour*60*60-in_minute*60;
				cs_second.Format("%d",in_second);
			}
			else 
			{
				cs_minute = "0";
				in_second = vs_time-in_day*24*60*60-in_hour*60*60;
				cs_second.Format("%d",in_second);
			}
		}
		else
		{
			cs_hour = "0";
			in_minute = (vs_time-in_day*24*60*60)/(60);
			if(in_minute>0)
			{
				cs_minute.Format("%d",in_minute);
				in_second=vs_time-in_day*24*60*60-in_hour*60*60-in_minute*60;
				cs_second.Format("%d",in_second);
			}
			else 
			{
				cs_minute = "0";
				in_second = vs_time-in_day*24*60*60;
				cs_second.Format("%d",in_second);
			}
		}
	}
	else
	{
		cs_day = "0";
		in_hour = vs_time/(60*60);
		if(in_hour>0)
		{
			cs_hour.Format("%d",in_hour);
			in_minute = (vs_time-in_hour*60*60)/(60);
			if(in_minute>0)
			{
				cs_minute.Format("%d",in_minute);
				in_second = vs_time-in_hour*60*60-in_minute*60;
				cs_second.Format("%d",in_second);
			}
			else 
			{
				cs_minute = "0";
				in_second = vs_time-in_hour*60*60;
				cs_second.Format("%d",in_second);
			}
		}
		else
		{
			cs_hour = "0";
			in_minute = vs_time/60;
			if(in_minute>0)
			{
				cs_minute.Format("%d",in_minute);
				in_second=vs_time-in_minute*60;
				cs_second.Format("%d",in_second);
			}
			else 
			{
				cs_minute = "0";
				in_second = vs_time;
				cs_second.Format("%d",in_second);
			}
		}
	}

	SetDlgItemText(IDC_EDIT_CRLREL,cs_day); 
	SetDlgItemText(IDC_EDIT_HOUR,cs_hour); 
	SetDlgItemText(IDC_EDIT_MINUTE,cs_minute); 
	SetDlgItemText(IDC_EDIT_SECOND,cs_second); 

}
