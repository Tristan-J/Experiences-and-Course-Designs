#pragma once
#include "MemoryChecker.h"

// LoadAPPPage �Ի���

class LoadAPPPage : public CDialogEx
{
	DECLARE_DYNAMIC(LoadAPPPage)

public:
	LoadAPPPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoadAPPPage();
	virtual BOOL OnInitDialog();

	MemoryChecker mc;

// �Ի�������
	enum { IDD = IDD_LOADAPPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk5();
};
