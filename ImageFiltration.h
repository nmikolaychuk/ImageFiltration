
// ImageFiltration.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CImageFiltrationApp:
// Сведения о реализации этого класса: ImageFiltration.cpp
//

class CImageFiltrationApp : public CWinApp
{
public:
	CImageFiltrationApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CImageFiltrationApp theApp;
