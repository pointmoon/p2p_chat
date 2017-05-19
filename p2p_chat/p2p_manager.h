//
//p2p_manager.h : файл заголовка
//

#pragma once

#include "stdafx.h"
#include <winsock2.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstdlib>

class Cp2p_chatDlg;

using namespace std;

#pragma comment(lib, "ws2_32.lib")

class p2p_manager
{
public:
	p2p_manager(Cp2p_chatDlg* dialog);
	~p2p_manager(void);

	SOCKET StartListening(int iPort, Cp2p_chatDlg* NUJNO, SOCKET socket_forAll);

	static UINT _cdecl DataThreadFunc(LPVOID pParam);
	UINT SendReceiveData(SOCKET cSocket);
	void ClearServer();
	WSADATA wsa;
	SOCKET s, new_socket;
	struct  sockaddr_in server, client;
	int c;
	int iTempCount;
	Cp2p_chatDlg* m_pDialog;
	HANDLE m_Thread_handle;
	CWinThread *cpTh;
	static void SetStaticVariable(SOCKET cS);
};