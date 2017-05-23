//
// p2p_chatDlg.h : файл заголовка
//

#pragma once
#include "stdafx.h"
#include "p2p_manager.h"
#include "p2p_clientCon.h"
#include <Windows.h>
#include "afxwin.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// диалоговое окно Cp2p_chatDlg
class Cp2p_chatDlg : public CDialogEx
{
// Создание
public:
	Cp2p_chatDlg(CWnd* pParent = NULL);	// стандартный конструктор
	void ShowServerInfo(string sValue);

// Данные диалогового окна
	enum { IDD = IDD_P2P_CHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Введённый клиентом номер порта
	int int_portNumber;
	// Введённое клиентом сообщение
	CString Str_outMessage;
	// Введенный IP-адрес (DWORD)
	DWORD dWord_IPaddr;
	// Статус подключения
	CString Str_STATUS;
	
	afx_msg void OnBnClickedButtonsendmsg();
	afx_msg void OnBnClickedButtonconnect();
	afx_msg void OnBnClickedButtondisconnect();
	afx_msg void OnBnClickedButtonStartServer();
	afx_msg void OnBnClickedButtonStopServer();
	afx_msg void OnEnChangeEdit4();

	
	CString m_buffer;
	CEdit m_Textbox;


	p2p_manager *m_pServer;
	Clientcon *m_pClient;
	static UINT _cdecl StaticThreadFunc(LPVOID pParam);
	static UINT _cdecl StaticThreadFunc_client(LPVOID pParam);
	static UINT _cdecl StaticThreadFunc_file(LPVOID pParam);
	UINT ThreadFunc();
	UINT ThreadFunc_client();
	UINT ThreadFunc_file();
	//UINT ThreadFunc_client();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	CEdit m_Portbox;
	//virtual DWORD Cp2p_chatDlg::talkWithClient(LPVOID);

private:
	HANDLE m_Thread_handle;
	CWinThread *cTh;
	
	HANDLE m_ThreadFile_handle;
	CWinThread *fTh;
	
public:
	afx_msg void OnBnClickedButtonSendFile();
	// Полный путь до отправляемого файла
	CString m_PATHtoFILE;
	// Контроль исходящего сообщения
	CEdit m_ControlOutMsg;
};