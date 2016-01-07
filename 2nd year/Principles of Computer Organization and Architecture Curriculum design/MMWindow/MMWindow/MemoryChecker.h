#pragma once

#include "Insertdata.h"
// MemoryChecker 对话框

class MemoryChecker : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryChecker)

public:
	MemoryChecker(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MemoryChecker();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_MEMORYCHECKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
private:
	Insertdata insDialog;
};
