
// AudioDlgDlg.h: 头文件
//

#pragma once

#include <Dbt.h>

#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <io.h>

#include "tinyxml.h"
#include "ControlAudio.h"

// CAudioDlgDlg 对话框
class CAudioDlgDlg : public CDialogEx
{
// 构造
public:
	CAudioDlgDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CAudioDlgDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUDIODLG_DIALOG };
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
	std::shared_ptr<CControlAudio> m_ShareptrControlAudio;//控制音量
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
public:
	CListCtrl ListCtrl1;
private:
	BOOL m_bLoopMain;
	std::thread* m_lpLoopMainThread;
	std::mutex m_MutMain;
	std::condition_variable m_CvMain;
	void LoopMain();
	BOOL ReturnQueueStatus();
private:
	void ProductData(std::string &strs);
	void ConsumeData();
	void Dispaly(char * m_Sz);
private:
	BOOL ReturnSpeakerStatus();
	BOOL ReturnJoyStickStatus();
	BOOL m_bStatusSpeaker;
	BOOL m_bStatusJoyStick;
public:
	afx_msg LRESULT DetectDevicesChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT AnalyseDevicesInfo(WPARAM wParam, LPARAM lParam);
private:
	TiXmlDocument docXml;
	std::map < std::string, std::string> mapErrors;
	void ReadXml();	
};
