
// RFIDCard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRFIDCardApp: 
// �йش����ʵ�֣������ RFIDCard.cpp
//

class CRFIDCardApp : public CWinApp
{
public:
	CRFIDCardApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRFIDCardApp theApp;