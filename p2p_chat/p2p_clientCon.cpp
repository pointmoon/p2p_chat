#include "StdAfx.h"
#include "p2p_manager.h"
#include "p2p_chat.h"
#include "p2p_chatDlg.h"
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "p2p_clientCon.h"

/*#include "stdafx.h"
#include "p2p_clientCon.h"
//#include <stdio.h>
#include <string.h>
#include "p2p_chatDlg.h"*/

#pragma comment(lib, "ws2_32.lib")

Clientcon::Clientcon(Cp2p_chatDlg *dlg)
{
	m_pClient = dlg;
}

Clientcon::~Clientcon(void)
{
	closesocket(s);
	WSACleanup();
}

void Clientcon::StartRecv(SOCKET sock)
{
	s = sock;
	int recv_size;
	char server_reply[2000];
	while ((recv_size = recv(s, server_reply, 2000, 0)) != SOCKET_ERROR)
	{
		server_reply[recv_size] = '\0';
		string sTempMsg = "\n<< " + string(server_reply) + "\n";
		m_pClient->ShowServerInfo(sTempMsg);
	}
}