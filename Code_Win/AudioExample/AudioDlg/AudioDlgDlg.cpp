
// AudioDlgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "AudioDlg.h"
#include "AudioDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <mmsystem.h>
#include <SetupAPI.h>

extern "C"
{
#include <hidsdi.h>
}

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


// CAudioDlgDlg 对话框



CAudioDlgDlg::CAudioDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUDIODLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ShareptrControlAudio = nullptr;

	m_bLoopMain = TRUE;
	m_lpLoopMainThread = nullptr;
}

CAudioDlgDlg::~CAudioDlgDlg()
{
	if (m_bLoopMain&&m_lpLoopMainThread!= nullptr)
	{
		m_bLoopMain = FALSE;
		m_CvMain.notify_one();
		m_lpLoopMainThread->join();
		if (m_lpLoopMainThread!=nullptr)
		{
			delete m_lpLoopMainThread;
			m_lpLoopMainThread = nullptr;
		}
	}
}

void CAudioDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListCtrl1);
}

BEGIN_MESSAGE_MAP(CAudioDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAudioDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAudioDlgDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAudioDlgDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAudioDlgDlg::OnBnClickedButton4)
	ON_MESSAGE(WM_DEVICECHANGE, &CAudioDlgDlg::DetectDevicesChange)
END_MESSAGE_MAP()


// CAudioDlgDlg 消息处理程序

BOOL CAudioDlgDlg::OnInitDialog()
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
	CRect CtrlList_Rect;
	ListCtrl1.GetClientRect(CtrlList_Rect);
	ListCtrl1.InsertColumn(0, L"消息", LVCFMT_LEFT, CtrlList_Rect.Width());

	ReadXml();
	m_ShareptrControlAudio = std::make_shared<CControlAudio>();
	m_ShareptrControlAudio->InitConfig();

	m_bStatusSpeaker = ReturnSpeakerStatus();
	m_bStatusJoyStick = ReturnJoyStickStatus();
	m_lpLoopMainThread = new std::thread(&CAudioDlgDlg::LoopMain, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAudioDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAudioDlgDlg::OnPaint()
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
HCURSOR CAudioDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAudioDlgDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ShareptrControlAudio->ResetAudio();
}

void CAudioDlgDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ShareptrControlAudio->SetAudio();
}

void CAudioDlgDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ShareptrControlAudio->AddAudio();
}

void CAudioDlgDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ShareptrControlAudio->PlusAudio();
}

void CAudioDlgDlg::LoopMain()
{
	while (m_bLoopMain)
	{
		std::unique_lock<std::mutex> lck(m_MutMain);
		m_CvMain.wait(lck, [this]() {return this->ReturnQueueStatus();} );
		if (m_bLoopMain)
		{
			ConsumeData();
		}
		else
		{
			break;
		}
	}
}

void CAudioDlgDlg::ProductData(std::string &strs)
{
	std::unique_lock<std::mutex> lck(m_MutMain);
	if (ReturnQueueStatus()==FALSE)
	{
		theApp.m_MsgQueue.PushIntoQueue(strs);
		m_CvMain.notify_one();
	}
	else
	{
		theApp.m_MsgQueue.PushIntoQueue(strs);
	}
}

void CAudioDlgDlg::ConsumeData()
{
	std::string m_StrTemp = theApp.m_MsgQueue.GetFromQueue();
	char m_SzA[255] = { 0 };
	strcpy(m_SzA, m_StrTemp.c_str());

	Dispaly(m_SzA);
}

void CAudioDlgDlg::Dispaly(char * m_Sz)
{
	std::string m_StrFindKey = m_Sz;;;;
	std::map<std::string, std::string>::iterator  iter;
	iter = mapErrors.find(m_StrFindKey);

	if (iter != mapErrors.end())
	{
		std::string m_strValues = iter->second;
		char m_szValues[255] = { 0 };
		strcpy(m_szValues, m_strValues.c_str());
		TCHAR m_szValuesW[255] = { 0 };
		int m_nlens = MultiByteToWideChar(CP_ACP, 0, m_szValues, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, m_szValues, -1, m_szValuesW, m_nlens);

		int AlreadyNum = ListCtrl1.GetItemCount();
		ListCtrl1.InsertItem(AlreadyNum, NULL);

		ListCtrl1.SetItemText(AlreadyNum, 0, m_szValuesW);
		ListCtrl1.EnsureVisible(AlreadyNum, FALSE);
	}
}

LRESULT CAudioDlgDlg::DetectDevicesChange(WPARAM wParam, LPARAM lParam)
{
	AnalyseDevicesInfo(wParam, lParam);
	return 0;
}

LRESULT CAudioDlgDlg::AnalyseDevicesInfo(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_HDR m_lpDeviceInfo = (PDEV_BROADCAST_HDR)lParam;
	if (m_lpDeviceInfo==NULL)
	{
		BOOL m_bTepStatusSpeaker = ReturnSpeakerStatus();
		if (m_bTepStatusSpeaker!= m_bStatusSpeaker)
		{
			if (m_bTepStatusSpeaker)
			{
				std::string m_strInfo = "0103";
				ProductData(m_strInfo);//0103 插入音响
			}
			else
			{
				std::string m_strInfo = "0203";
				ProductData(m_strInfo);//0203 拔出音响
			}
			m_bStatusSpeaker = m_bTepStatusSpeaker;
		}
		BOOL m_bTepStatusJoyStick = ReturnJoyStickStatus();
		if (m_bStatusJoyStick!= m_bTepStatusJoyStick)
		{
			if (m_bStatusJoyStick)
			{
				std::string m_strInfo = "0104";
				ProductData(m_strInfo);//0104 插入手柄
			}
			else
			{
				std::string m_strInfo = "0204";
				ProductData(m_strInfo);//0204 拔出手柄
			}
			m_bStatusJoyStick = m_bTepStatusJoyStick;
		}
	}
	else
	{
		if (wParam== DBT_DEVICEARRIVAL)
		{
			DWORD m_dwDeviceType = m_lpDeviceInfo->dbch_devicetype;
			if (m_dwDeviceType== DBT_DEVTYP_VOLUME)
			{
				std::string m_strInfo = "0101";
				ProductData(m_strInfo);//0101 插入u盘
			}
			if (m_dwDeviceType== DBT_DEVTYP_PORT)
			{
				std::string m_strInfo = "0102";
				ProductData(m_strInfo);//0102 插入串口
			}
		}
		if (wParam==DBT_DEVICEREMOVECOMPLETE)
		{
			DWORD m_dwDeviceType = m_lpDeviceInfo->dbch_devicetype;
			if (m_dwDeviceType == DBT_DEVTYP_VOLUME)
			{
				std::string m_strInfo = "0201";
				ProductData(m_strInfo);//0201 拔出u盘
			}
			if (m_dwDeviceType == DBT_DEVTYP_PORT)
			{
				std::string m_strInfo = "0202";
				ProductData(m_strInfo);//0202 拔出串口
			}
		}
	}

	return 0;
}

BOOL CAudioDlgDlg::ReturnSpeakerStatus()
{
	int tNum = waveOutGetNumDevs();

	if (tNum == 1)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CAudioDlgDlg::ReturnJoyStickStatus()
{
	int tNum = joyGetNumDevs();
	BOOL FlagRet;

	JOYINFO joyinfo;
	FlagRet = FALSE;
	for (int i = 0; i < tNum; i++)
	{
		int nRet = joyGetPos(i, &joyinfo);

		if (nRet == JOYERR_NOERROR)
		{
			FlagRet = TRUE;
		}
	}

	return FlagRet;
}

void CAudioDlgDlg::ReadXml()
{
	TCHAR m_SzFile[255] = { 0 };
	GetModuleFileName(NULL, m_SzFile, 255);
	std::wstring m_WStrFile = m_SzFile;
	int nPos = m_WStrFile.find_last_of('\\');
	if (nPos <= 0)
	{
		return;
	}

	m_WStrFile = m_WStrFile.substr(0, nPos);
	m_WStrFile = m_WStrFile + L"\\MsgControl.xml";
	memset(m_SzFile, L'\0', sizeof(m_SzFile) / sizeof(TCHAR));
	wcscpy(m_SzFile, m_WStrFile.c_str());
	char m_SzFileA[255] ={0};
	int nlen = WideCharToMultiByte(CP_ACP, 0, m_SzFile, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_SzFile, -1, m_SzFileA, nlen, NULL, NULL);
	if (_access(m_SzFileA, 0)==-1)
	{
		return;
	}

	docXml.LoadFile(m_SzFileA);
	TiXmlElement* lpElemRoot = docXml.RootElement();
	TiXmlElement* lpPartSer = lpElemRoot->FirstChildElement("Part");
	while (lpPartSer != nullptr&&strcmp("InfoMap", lpPartSer->Attribute("Name")) != 0)
	{
		lpPartSer = lpPartSer->NextSiblingElement();
	}
	if (lpPartSer == nullptr)
	{
		return;
	}

	TiXmlElement* lpPartSerChild = lpPartSer->FirstChildElement();
	while (lpPartSerChild != nullptr)
	{
		std::string mapKey = lpPartSerChild->Attribute("Name");

		char szCont[255] = { 0 };
		strcpy(szCont, lpPartSerChild->GetText());
		std::string mapValue = szCont;
		mapErrors.insert(std::pair<std::string, std::string>(mapKey, mapValue));

		lpPartSerChild = lpPartSerChild->NextSiblingElement();
	}
}

BOOL CAudioDlgDlg::ReturnQueueStatus()
{
	return (theApp.m_MsgQueue.GetSize() > 0)||!m_bLoopMain;
}