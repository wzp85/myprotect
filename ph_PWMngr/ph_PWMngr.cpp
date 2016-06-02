
// ph_PWMngr.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ph_PWMngr.h"
#include "ph_PWMngrDlg.h"
#include "MainMenuDlg.h"
#define PWMMNGR_CAPTION _T("�Ϻ��ջ�����ϵͳ  Version 2.0")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cph_PWMngrApp

BEGIN_MESSAGE_MAP(Cph_PWMngrApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cph_PWMngrApp ����

Cph_PWMngrApp::Cph_PWMngrApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cph_PWMngrApp ����

Cph_PWMngrApp theApp;


// Cph_PWMngrApp ��ʼ��

BOOL Cph_PWMngrApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	Cph_PWMngrDlg dlg(NULL,1,NULL,NULL,NULL,PWMMNGR_CAPTION);
	m_pMainWnd = &dlg;
	
	INT_PTR nResponse = dlg.DoModal();



	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
		//������Ա��
	//	int admMaxLogin = 0;
	//	dlg.GetMaxAdminLogin(&admMaxLogin);
	//	void *handle = dlg.phSHandle;
	////	dlg.adm_Num_log = admMaxLogin;
	//	if(1 < admMaxLogin)
	//	{
	//		/*int adm_Count = 0.5 * admMaxLogin + 1;*/
	//	
	//		while(1 < admMaxLogin)
	//		{
	//			Cph_PWMngrDlg loginDlg(2,NULL,NULL,NULL,PWMMNGR_CAPTION);
	//			loginDlg.DoModal();
	//			admMaxLogin--;
	//		}
	//		CMainMenuDlg mainmenudlg(handle,PWMMNGR_CAPTION);
	//		mainmenudlg.DoModal();
	//	}
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

