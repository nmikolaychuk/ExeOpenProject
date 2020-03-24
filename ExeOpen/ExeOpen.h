
// ExeOpen.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CExeOpenApp:
// О реализации данного класса см. ExeOpen.cpp
//

class CExeOpenApp : public CWinApp
{
public:
	CExeOpenApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CExeOpenApp theApp;