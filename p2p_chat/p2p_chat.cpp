//
// p2p_chat.cpp : ���������� ��������� ������� ��� ����������.
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


// �������� Cp2p_chatApp

Cp2p_chatApp::Cp2p_chatApp()
{
	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ Cp2p_chatApp

Cp2p_chatApp theApp;



// ������������� Cp2p_chatApp

BOOL Cp2p_chatApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ������� ��������� ��������, � ������, ���� ���������� ���� ��������
	// ������������� ������ �������� ��� �����-���� ��� �������� ����������.
	CShellManager *pShellManager = new CShellManager;

	// ��������� ����������� ���������� "������������ Windows" ��� ��������� ��������� ���������� MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ����������� �������������
	SetRegistryKey(_T("P2P-Chat"));

	Cp2p_chatDlg dlg;
	m_pMainWnd = &dlg; //��������� �� ������� ���� ���������

	/*
	//��������� � ����������� � WinSock
	WSADATA wsa;

	//������������� WinSock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
	perror("socket");
	return FALSE;
	}
	*/

	//������� DoModal() ����� ��������
	//���� ������� ���������� ����
	INT_PTR nResponse = dlg.DoModal();
	//����� �� �������� � ������ 
	//�������� �������� ���� ���������

	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}

void Cp2p_chatApp::OnServerAction(string sValue)
{
	CString strLine;
	strLine.Format(_T("\r\n%s"), sValue);
}