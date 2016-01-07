
// MMWindowDlg.h : 头文件
//

#pragma once

#include "MainPage.h"
#include "LoadAPPPage.h"
#include "resource.h"

#include <string>

using namespace std;

enum TAB_ITEM{MAIN_PAGE=0,SUB_LOADAPP_PAGE=1};

// CMMWindowDlg 对话框
class CMMWindowDlg : public CDialogEx
{
// 构造
public:
	CMMWindowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MMWINDOW_DIALOG };

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
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl* m_tab;
	MainPage main_page;
	LoadAPPPage load_app_page;

private :
	string tab_itemname[2];
};
