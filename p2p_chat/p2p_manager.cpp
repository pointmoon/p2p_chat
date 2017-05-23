#include "StdAfx.h"
#include "p2p_manager.h"
#include "p2p_chat.h"
#include "p2p_chatDlg.h"
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <string>

static SOCKET s_socket;

//конструктор
p2p_manager::p2p_manager(Cp2p_chatDlg* dialog)
{
	m_pDialog = dialog;
}

//деструктор
p2p_manager::~p2p_manager()
{
	closesocket(s);
	WSACleanup();
}

void p2p_manager::ClearServer()
{
	closesocket(s);
	WSACleanup();
}

SOCKET sock_TEMP;

SOCKET p2p_manager::StartListening(int iPort, Cp2p_chatDlg* NUJNO, SOCKET socket_forAll)
{
	//инициализация WinSock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return SOCKET_ERROR;
	}

	//создание сокета
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(iPort);

	//bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	//очередь на входные подключения из 1 абонента
	listen(s, 1);

	c = sizeof(struct sockaddr_in);

	while ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
	{
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;

		len = sizeof(addr);
		getpeername(new_socket, (struct sockaddr*)&addr, &len);

		if (addr.ss_family == AF_INET){
			struct sockaddr_in *s = (struct sockaddr_in*)&addr;
			port = htons(s->sin_port);
			inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
		}

		//m_pDialog->ShowServerInfo("Connected Peer IP address: "+string(ipstr)+"\n");
		sock_TEMP = new_socket;
		CWinThread *cTh = AfxBeginThread(DataThreadFunc, (LPVOID)NUJNO);
	    socket_forAll = new_socket;
		//убираем сокет с прослушивания
		closesocket(s);
		return new_socket;
	}
	return socket_forAll;
}

void file();

UINT _cdecl p2p_manager::DataThreadFunc(LPVOID pParam)
{
	SOCKET pYourSocket = sock_TEMP;
	Cp2p_chatDlg* twerk = reinterpret_cast<Cp2p_chatDlg*>(pParam);

	char server_reply[1024];
	int recv_size;
	const char* specialChar_start = "%4!_%8!_%1!_%5!_%1!_%6!_%2!_%3!_%4!_%2!";
	const char* specialChar_end = "*373__=382%^535#32223fe3^^#$d2";

	int count = 0;
	ofstream pStream;
	char* fileName = new char;

	while ((recv_size = recv(pYourSocket, server_reply, 1024, 0)) != SOCKET_ERROR)
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
			twerk->ShowServerInfo(sTempMsg);
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
			twerk->ShowServerInfo(information);
			count++;
			pStream.open(name, ios_base::out | ios_base::binary);
			continue;
		}

		if (count == 2)
		{
			pStream.write(server_reply, 1024);
		}
	}

	return 0;
}


UINT p2p_manager::SendReceiveData(SOCKET cSocket)
{
	return 0;
}

void p2p_manager::SetStaticVariable(SOCKET cS)
{
	s_socket = cS;
}