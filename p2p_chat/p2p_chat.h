
// p2p_chat.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include <string.h>
#include <string>

using namespace std;


// Cp2p_chatApp:
// � ���������� ������� ������ ��. p2p_chat.cpp
//

class Cp2p_chatApp : public CWinApp
{
public:
	Cp2p_chatApp();

// ���������������
public:
	virtual BOOL InitInstance();
	static void OnServerAction(std::string sValue);
// ����������

	DECLARE_MESSAGE_MAP()
};

extern Cp2p_chatApp theApp;