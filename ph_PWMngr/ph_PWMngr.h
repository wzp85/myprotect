
// ph_PWMngr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cph_PWMngrApp:
// �йش����ʵ�֣������ ph_PWMngr.cpp
//

class Cph_PWMngrApp : public CWinApp
{
public:
	Cph_PWMngrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cph_PWMngrApp theApp;