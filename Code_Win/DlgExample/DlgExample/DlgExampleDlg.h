
// DlgExampleDlg.h: 头文件
//

#pragma once

#include <thread>
#include <string>

// CDlgExampleDlg 对话框
class CDlgExampleDlg : public CDialogEx
{
// 构造
public:
	CDlgExampleDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CDlgExampleDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	NOTIFYICONDATA Notify;//系统托盘
private:
	std::thread* lpThreadMain;
	void ThreadMain();
	BOOL nMain;

	void WindowsReady();
	OVERLAPPED writeOver;
	HANDLE writeHEve;
public:
	CListCtrl ListCtrl1;
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam);//托盘左右键消息
	afx_msg void OnNotifymsg1();
	afx_msg void OnNotifymsg2();
	afx_msg void OnNotifymsg3();
private:
	int nCpu;
	HANDLE PipHandle;
private:
	std::thread* lpThreadRecv;
	void ThreadRecv();
	BOOL nRecv;

	OVERLAPPED readOver;
	HANDLE readHEve;
private:
	void DisplayRecv(TCHAR* szCont);
};
