
// ExeOpen.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CExeOpenApp:
// � ���������� ������� ������ ��. ExeOpen.cpp
//

class CExeOpenApp : public CWinApp
{
public:
	CExeOpenApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CExeOpenApp theApp;