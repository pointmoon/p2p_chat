//
// p2p_chatDlg.h : ���� ���������
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

// ���������� ���� Cp2p_chatDlg
class Cp2p_chatDlg : public CDialogEx
{
// ��������
public:
	Cp2p_chatDlg(CWnd* pParent = NULL);	// ����������� �����������
	void ShowServerInfo(string sValue);

// ������ ����������� ����
	enum { IDD = IDD_P2P_CHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV

// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �������� �������� ����� �����
	int int_portNumber;
	// �������� �������� ���������
	CString Str_outMessage;
	// ��������� IP-����� (DWORD)
	DWORD dWord_IPaddr;
	// ������ �����������
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
	// ������ ���� �� ������������� �����
	CString m_PATHtoFILE;
	// �������� ���������� ���������
	CEdit m_ControlOutMsg;
};