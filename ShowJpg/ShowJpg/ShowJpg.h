
// ShowJpg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowJpgApp:
// �йش����ʵ�֣������ ShowJpg.cpp
//

class CShowJpgApp : public CWinApp
{
public:
	CShowJpgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowJpgApp theApp;