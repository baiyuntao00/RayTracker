
// RayTrace.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRayTraceApp: 
// �йش����ʵ�֣������ RayTrace.cpp
//

class CRayTraceApp : public CWinApp
{
public:
	CRayTraceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRayTraceApp theApp;