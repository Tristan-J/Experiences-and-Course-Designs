#pragma once
#include "MemoryChecker.h"

// LoadAPPPage 对话框

class LoadAPPPage : public CDialogEx
{
	DECLARE_DYNAMIC(LoadAPPPage)

public:
	LoadAPPPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoadAPPPage();
	virtual BOOL OnInitDialog();

	MemoryChecker mc;

// 对话框数据
	enum { IDD = IDD_LOADAPPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk5();
};
