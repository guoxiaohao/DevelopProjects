
// DlgExampleDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DlgExample.h"
#include "DlgExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDlgExampleDlg 对话框



CDlgExampleDlg::CDlgExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	nCpu = 0;
	PipHandle = INVALID_HANDLE_VALUE;

	lpThreadMain = nullptr;
	nMain = TRUE;
	writeHEve = INVALID_HANDLE_VALUE;

	lpThreadRecv = nullptr;
	nRecv = TRUE;
	readHEve = INVALID_HANDLE_VALUE;
}

CDlgExampleDlg::~CDlgExampleDlg()
{
	if (nMain&&lpThreadMain!=nullptr)
	{
		nMain = FALSE;
		lpThreadMain->join();
		delete lpThreadMain; lpThreadMain = nullptr;
		if (writeHEve!=INVALID_HANDLE_VALUE)
		{
			CloseHandle(writeHEve); writeHEve = INVALID_HANDLE_VALUE;
		}
	}
	if (nRecv&&lpThreadRecv!=nullptr)
	{
		nRecv = FALSE;
		lpThreadRecv->join();
		delete lpThreadRecv; lpThreadRecv = nullptr;
		if (readHEve != INVALID_HANDLE_VALUE)
		{
			CloseHandle(readHEve); readHEve = INVALID_HANDLE_VALUE;
		}
	}
	if (PipHandle!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(PipHandle); PipHandle = INVALID_HANDLE_VALUE;
	}
}

void CDlgExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListCtrl1);
}

BEGIN_MESSAGE_MAP(CDlgExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NOTIFYMSG, OnNotifyMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgExampleDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_COMMAND(ID_NOTIFYMSG1, &CDlgExampleDlg::OnNotifymsg1)
	ON_COMMAND(ID_NOTIFYMSG2, &CDlgExampleDlg::OnNotifymsg2)
	ON_COMMAND(ID_NOTIFYMSG3, &CDlgExampleDlg::OnNotifymsg3)
END_MESSAGE_MAP()


// CDlgExampleDlg 消息处理程序

BOOL CDlgExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	nCpu = info.dwNumberOfProcessors;
	//托盘处理
	Notify.cbSize = sizeof(NOTIFYICONDATA);
	Notify.hIcon = m_hIcon;
	Notify.hWnd = m_hWnd;
	wmemset(Notify.szTip, L'\0', sizeof(Notify.szTip)/sizeof(TCHAR));
	wsprintf(Notify.szTip, L"%s", L"DlgExample");
	Notify.uCallbackMessage = WM_NOTIFYMSG;
	Notify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &Notify);
	//列表显示
	CRect CtrlList_Rect;
	ListCtrl1.GetClientRect(CtrlList_Rect);
	for (int i = 0; i < nCpu; i++)
	{
		ListCtrl1.InsertColumn(i, L"Cpu温度", LVCFMT_LEFT, 150);
	}
	int nlen1 = CtrlList_Rect.Width() - 150 * nCpu;
	ListCtrl1.InsertColumn(nCpu, L"时间", LVCFMT_LEFT, nlen1);

	lpThreadMain = new std::thread(&CDlgExampleDlg::ThreadMain, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlgExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlgExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgExampleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &Notify);
}

LRESULT CDlgExampleDlg::OnNotifyMsg(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CMenu Menu1;
		Menu1.LoadMenuW(IDR_MENU1);
		CMenu *pPop = Menu1.GetSubMenu(0);
		CPoint PointLocal;
		GetCursorPos(&PointLocal);
		SetForegroundWindow();
		pPop->TrackPopupMenu(TPM_LEFTALIGN, PointLocal.x, PointLocal.y, this);
		HMENU hmenu = Menu1.Detach();
		Menu1.DestroyMenu();
	}
	break;
	case WM_LBUTTONDOWN:
	{
		ShowWindow(SW_NORMAL);
		SetForegroundWindow();
	}
	break;
	default:
		break;
	}

	return 0;
}

void CDlgExampleDlg::OnBnClickedButton1()//托盘
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

void CDlgExampleDlg::OnNotifymsg1()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_HIDE);
}

void CDlgExampleDlg::OnNotifymsg2()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_NORMAL);
	SetForegroundWindow();
}

void CDlgExampleDlg::OnNotifymsg3()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}

void CDlgExampleDlg::ThreadMain()
{
	std::thread ThreadWindows(&CDlgExampleDlg::WindowsReady, this);
	ThreadWindows.join();
	this->ShowWindow(SW_HIDE);//程序托盘模式后开启线程

	while (nMain)
	{
		BOOL bFlag = WaitNamedPipeA("\\\\.\\pipe\\SerExamplePipe", 0);
		if (bFlag&&PipHandle==INVALID_HANDLE_VALUE)
		{
			PipHandle = CreateFileA("\\\\.\\pipe\\SerExamplePipe", GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
			int nRet = GetLastError();

			if (PipHandle != INVALID_HANDLE_VALUE&&nRet==ERROR_SUCCESS)
			{
				lpThreadRecv = new std::thread(&CDlgExampleDlg::ThreadRecv, this);
				break;
			}
		}
		Sleep(200);
	}
	while (nMain)
	{
		Sleep(200);
		char WriteBuff[255] = "NeedMessage";
		DWORD dwWrite;

		if (writeHEve==INVALID_HANDLE_VALUE)
		{
			writeHEve = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
		memset(&writeOver, 0, sizeof(OVERLAPPED));
		writeOver.hEvent = writeHEve;

		WriteFile(PipHandle, WriteBuff, strlen(WriteBuff), &dwWrite, &writeOver);
		WaitForSingleObject(writeOver.hEvent, 200);
	}
}

void CDlgExampleDlg::WindowsReady()
{
	while (!this->IsWindowVisible());
}

void CDlgExampleDlg::ThreadRecv()
{
	while (nRecv)
	{
		if (readHEve == INVALID_HANDLE_VALUE)
		{
			readHEve = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
		memset(&readOver, 0, sizeof(OVERLAPPED));
		readOver.hEvent = readHEve;

		char szRecvs[255] = { 0 };
		DWORD dwReadByres = 0;
		int nRets = ReadFile(PipHandle, szRecvs, 255, &dwReadByres, &readOver);
		nRets = WaitForSingleObject(readOver.hEvent, 200);
		if (nRets ==WAIT_OBJECT_0)
		{
			DWORD dwDone = 0;
			GetOverlappedResult(PipHandle, &readOver, &dwDone, TRUE);
			if (dwDone!=0)
			{
				TCHAR szContent[255] = { 0 };
				int nlens = MultiByteToWideChar(CP_ACP, 0, szRecvs, -1, NULL, 0);
				MultiByteToWideChar(CP_ACP, 0, szRecvs, -1, szContent, nlens);
				DisplayRecv(szContent);
			}
		}
		else
		{
			continue;
		}
	}	
}

void CDlgExampleDlg::DisplayRecv(TCHAR* szCont)
{
	if (!IsWindow(ListCtrl1))
	{
		return;
	}

	int AlreadyNum = ListCtrl1.GetItemCount();
	ListCtrl1.InsertItem(AlreadyNum, NULL);

	TCHAR szTime[255] = { 0 };
	CTime Time_Current;
	Time_Current = CTime::GetCurrentTime();
	int nYear = Time_Current.GetYear();
	int nMonth = Time_Current.GetMonth();
	int nDay = Time_Current.GetDay();
	int nHour = Time_Current.GetHour();
	int nMinute = Time_Current.GetMinute();
	int nSecond = Time_Current.GetSecond();
	wsprintf(szTime, L"%04d:%02d:%02d-%02d::%02d::%02d", nYear, nMonth, nDay, nHour, nMinute, nSecond);

	std::wstring StrRecv = szCont;
	for (int i = 0; i < nCpu; i++)
	{
		int nPos = StrRecv.find_first_of('_');
		std::wstring sz1 = StrRecv.substr(0, nPos);
		TCHAR szText[255] = { 0 };
		wcscpy_s(szText, sz1.c_str());
		ListCtrl1.SetItemText(AlreadyNum, i, szText);
		StrRecv = StrRecv.substr(nPos+1, StrRecv.length());
	}
	
	ListCtrl1.SetItemText(AlreadyNum, nCpu, szTime);
	ListCtrl1.EnsureVisible(AlreadyNum, FALSE);
}