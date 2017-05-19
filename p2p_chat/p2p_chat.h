
// p2p_chat.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include <string.h>
#include <string>

using namespace std;


// Cp2p_chatApp:
// О реализации данного класса см. p2p_chat.cpp
//

class Cp2p_chatApp : public CWinApp
{
public:
	Cp2p_chatApp();

// Переопределение
public:
	virtual BOOL InitInstance();
	static void OnServerAction(std::string sValue);
// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Cp2p_chatApp theApp;