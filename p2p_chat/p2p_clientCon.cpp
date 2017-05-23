#include "StdAfx.h"
#include "p2p_manager.h"
#include "p2p_chat.h"
#include "p2p_chatDlg.h"
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "p2p_clientCon.h"
#include <fstream>

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
char server_reply[2000];
	int recv_size;
	const char* specialChar_start = "%4!_%8!_%1!_%5!_%1!_%6!_%2!_%3!_%4!_%2!";
	const char* specialChar_end = "*373__=382%^535#32223fe3^^#$d2";

	int count = 0;
	ofstream pStream;
	char* fileName = new char;

	while ((recv_size = recv(s, server_reply, 1024, 0)) != SOCKET_ERROR)
	{
		//следующее собщение будет именем файла
		if (stricmp(specialChar_start, server_reply) == 0)
		{
			count++;
			continue;
		}

		//вывод на экран обычного сообщения
		if (count == 0)
		{
			server_reply[recv_size] = '\0';
			string sTempMsg = "\n<< " + string(server_reply) + "\n";
			m_pClient->ShowServerInfo(sTempMsg);
			continue;
		}

		//конец передачи файла
		if (stricmp(specialChar_end, server_reply) == 0)
		{
			pStream.close();
			count = 0;
		}

		//открываем файл для записи
		if (count == 1)
		{
			string path(server_reply);
			string ext;
			
			for (register int i = path.length() - 1; i > 0; i--) {
				if (path[i] == '\\') {
					for (register int j = i+1; j <= (int)path.length() - 1; j++) {
						ext.push_back(path[j]);
					}
					break;
				}
			}
			////////////////////////////
			const char* name = ext.c_str();
			string information(name);
			m_pClient->ShowServerInfo(information);
			count++;
			pStream.open(name, ios_base::out | ios_base::binary);
			continue;
		}

		if (count == 2)
		{
			pStream.write(server_reply, 1024);
		}
	}
}