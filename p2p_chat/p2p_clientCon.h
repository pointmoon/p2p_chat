#pragma once

#include "stdafx.h"
#include <winsock2.h>
#include <string.h>
#include <string>

using namespace std;

class Cp2p_chatDlg;

class Clientcon
{
public:

    //constr and destruct
	Clientcon(Cp2p_chatDlg *dlg);
	~Clientcon(void);

	void StartRecv(SOCKET sock);

	WSADATA wsa;
	SOCKET s;
	Cp2p_chatDlg *m_pClient;
};