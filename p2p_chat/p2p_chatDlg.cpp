//
// p2p_chatDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "p2p_chat.h"
#include <stdlib.h>
#include "p2p_chatDlg.h"
#include "afxdialogex.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SOCKET socket_forAll;
struct sockaddr_in addr;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// диалоговое окно Cp2p_chatDlg

Cp2p_chatDlg::Cp2p_chatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cp2p_chatDlg::IDD, pParent)
	, m_pServer(NULL)
	, int_portNumber(0)
	, Str_outMessage(_T(""))
	, Str_STATUS(_T(""))
	, dWord_IPaddr(0)
	, m_buffer(_T(""))
	, m_PATHtoFILE(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_buffer = _T("");
}

void Cp2p_chatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, int_portNumber);
	DDX_Text(pDX, IDC_EDIT5, Str_outMessage);
	DDX_Text(pDX, IDC_EDIT6, Str_STATUS);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, dWord_IPaddr);
	DDX_Text(pDX, IDC_EDIT4, m_buffer);
	DDX_Control(pDX, IDC_EDIT4, m_Textbox);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_PATHtoFILE);
	DDX_Control(pDX, IDC_EDIT5, m_ControlOutMsg);
}

BEGIN_MESSAGE_MAP(Cp2p_chatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT4, &Cp2p_chatDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON_sendMSG, &Cp2p_chatDlg::OnBnClickedButtonsendmsg)
	ON_BN_CLICKED(IDC_BUTTON_connect, &Cp2p_chatDlg::OnBnClickedButtonconnect)
	ON_BN_CLICKED(IDC_BUTTON_disconnect, &Cp2p_chatDlg::OnBnClickedButtondisconnect)
	ON_BN_CLICKED(IDC_BUTTON_START_SERVER, &Cp2p_chatDlg::OnBnClickedButtonStartServer)
	ON_BN_CLICKED(IDC_BUTTON_STOP_SERVER, &Cp2p_chatDlg::OnBnClickedButtonStopServer)
	ON_BN_CLICKED(IDC_BUTTON_sendFILE, &Cp2p_chatDlg::OnBnClickedButtonSendFile)
END_MESSAGE_MAP()


// обработчики сообщений Cp2p_chatDlg

BOOL Cp2p_chatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	// TODO: добавьте дополнительную инициализацию
	Str_STATUS = "Не подключен";
	dWord_IPaddr = 2130706433; //ip-addr 127.0.0.1
	int_portNumber = 3425;
	
	UpdateData(FALSE);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Cp2p_chatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Cp2p_chatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Cp2p_chatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Обработчик кнопки - "Отправить сообщение"
void Cp2p_chatDlg::OnBnClickedButtonsendmsg()
{
	UpdateData(TRUE);
	CStringA charstr(Str_outMessage);
	send(socket_forAll, (const char*)charstr, 1024, 0);
	Str_outMessage = "";
	UpdateData(FALSE);
	string temp(charstr);
	string temp_q = "\n>> " + temp + "\n";
	ShowServerInfo(temp_q);
	temp.empty();
	temp_q.empty();
}

//Обработчик кнопки - "Подключение"
void Cp2p_chatDlg::OnBnClickedButtonconnect()
{		
	//создаем сокет для входных подключений
	if ((socket_forAll = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
		MessageBox(L"Socket error!", L"Error!", MB_OK | MB_ICONERROR);
		perror("socket");
		WSACleanup();
		exit(1);
	}

	//обновляем введенную ифнормацию
	UpdateData(TRUE);

	//указываем параметры сервера
	addr.sin_family = AF_INET;
	addr.sin_port = htons(int_portNumber);
	addr.sin_addr.s_addr = htonl(dWord_IPaddr);
	//установка соединения с сервером
	if (connect(socket_forAll, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0){
		perror("connect");
		MessageBox(L"Connect error!", L"Error!", MB_OK | MB_ICONERROR);
		WSACleanup();
		exit(1);
	}
	else{
		Str_STATUS = "Подключен";
		UpdateData(FALSE);
		GetDlgItem(IDC_BUTTON_disconnect)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_sendMSG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_sendFILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_MFCEDITBROWSE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_START_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_connect)->EnableWindow(FALSE);
	}
	
	cTh = AfxBeginThread(StaticThreadFunc_client, this);
	m_Thread_handle = cTh->m_hThread;
}

//Обработчик кнопки - "Отключение"
void Cp2p_chatDlg::OnBnClickedButtondisconnect()
{
	Str_STATUS = "Не подключен";
	UpdateData(FALSE);
	closesocket(socket_forAll);
	MessageBox(L"UnConnect Succes!", L"Info.", MB_OK | MB_ICONINFORMATION);
	GetDlgItem(IDC_BUTTON_disconnect)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_sendMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_sendFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MFCEDITBROWSE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_SERVER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_connect)->EnableWindow(TRUE);
}


//Обработчик кнопки - "Стать сервером"
void Cp2p_chatDlg::OnBnClickedButtonStartServer()
{
	GetDlgItem(IDC_BUTTON_START_SERVER)->EnableWindow(FALSE);
	Str_STATUS = "Режим \"сервера\"";
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_sendMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_sendFILE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MFCEDITBROWSE1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_connect)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_SERVER)->EnableWindow(TRUE);

	cTh = AfxBeginThread(StaticThreadFunc, this);
	m_Thread_handle = cTh->m_hThread;
}

//Обработчик кнопки - "Остановить сервер"
void Cp2p_chatDlg::OnBnClickedButtonStopServer()
{
	Str_STATUS = "Не подключен";
	UpdateData(FALSE);
	GetDlgItem(IDC_BUTTON_connect)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_SERVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START_SERVER)->EnableWindow(TRUE);

	//CloseHandle(m_Thread_handle);
	m_pServer = NULL;
}

void Cp2p_chatDlg::ShowServerInfo(string sValue)
{
	CString strLine(sValue.c_str());
	AppendTextToEditCtrl(m_Textbox, strLine);
}

void Cp2p_chatDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	int nL = m_Textbox.GetWindowTextLength();
	m_Textbox.SetSel(nL, nL);
	m_Textbox.ReplaceSel(pszText);
}

UINT _cdecl Cp2p_chatDlg::StaticThreadFunc(LPVOID pParam)
{
	Cp2p_chatDlg *pYourClass = reinterpret_cast<Cp2p_chatDlg*>(pParam);
	UINT retCode = pYourClass->ThreadFunc();
	return retCode;
}

UINT _cdecl Cp2p_chatDlg::StaticThreadFunc_client(LPVOID pParam)
{
	Cp2p_chatDlg *pYourClass = reinterpret_cast<Cp2p_chatDlg*>(pParam);
	UINT retCode = pYourClass->ThreadFunc_client();
	return retCode;
}

UINT Cp2p_chatDlg::ThreadFunc()
{
	int iPort = int_portNumber;
	if (iPort == 0)
	{
		return -1;
	}
	m_pServer = new p2p_manager(this);
	socket_forAll = m_pServer->StartListening(iPort, this, socket_forAll);
	return 0;
}

UINT Cp2p_chatDlg::ThreadFunc_client()
{
	m_pClient = new Clientcon(this);
	m_pClient->StartRecv(socket_forAll);
	return 0;
}


void Cp2p_chatDlg::OnEnChangeEdit4()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


//Обработчик нажатия клавиши "Отправить файл"
void Cp2p_chatDlg::OnBnClickedButtonSendFile()
{
	UpdateData(TRUE);
	//char *p_file_in = new char;
	ifstream infile(m_PATHtoFILE, ios_base::in | ios_base::binary);
	if (!infile)
	{
		perror("ifstream");
		MessageBox(L"Error opening file!", L"Error", MB_OK | MB_ICONERROR);
		return;
	}

	string info = "Передача файла началась!";
	string temp_q = "\n\t\t" + info + "\n";
	ShowServerInfo(temp_q);

	//отправка уведомления о том, что будет отправлен файл
	const char* specialChar_start = "%4!_%8!_%1!_%5!_%1!_%6!_%2!_%3!_%4!_%2!";

	send(socket_forAll, specialChar_start, 1024, 0);

	Sleep(10);

	CStringA str(m_PATHtoFILE);
	string str_1(str);
	send(socket_forAll, str_1.c_str(), 1024, 0);

	while (!infile.eof())
	{
		char buffer[1024];
		//char* buffer;
		infile.read(buffer, 1024);
		if (infile.gcount())
		{
			send(socket_forAll, buffer, 1024, 0);
			Sleep(10);
		}
	}

	const char* specialChar_end = "*373__=382%^535#32223fe3^^#$d2";
	send(socket_forAll, specialChar_end, 1024, 0);

	info.empty();
	info = "Передача файла окончена!";
	temp_q = "\n\t\t" + info + "\n";
	ShowServerInfo(temp_q);
}
