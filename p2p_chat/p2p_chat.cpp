//
// p2p_chat.cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "p2p_chat.h"
#include "p2p_chatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cp2p_chatApp

BEGIN_MESSAGE_MAP(Cp2p_chatApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// создание Cp2p_chatApp

Cp2p_chatApp::Cp2p_chatApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект Cp2p_chatApp

Cp2p_chatApp theApp;



// инициализация Cp2p_chatApp

BOOL Cp2p_chatApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	SetRegistryKey(_T("P2P-Chat"));

	Cp2p_chatDlg dlg;
	m_pMainWnd = &dlg; //указатель на главное окно программы

	/*
	//структура с информацией о WinSock
	WSADATA wsa;

	//Инициализация WinSock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
	perror("socket");
	return FALSE;
	}
	*/

	//Функция DoModal() будет работать
	//пока открыто диалоговое окно
	INT_PTR nResponse = dlg.DoModal();
	//Здесь мы окажемся в случае 
	//закрытия главного окна программы

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

void Cp2p_chatApp::OnServerAction(string sValue)
{
	CString strLine;
	strLine.Format(_T("\r\n%s"), sValue);
}