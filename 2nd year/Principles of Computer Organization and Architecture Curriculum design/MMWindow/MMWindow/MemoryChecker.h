#pragma once

#include "Insertdata.h"
// MemoryChecker �Ի���

class MemoryChecker : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryChecker)

public:
	MemoryChecker(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MemoryChecker();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_MEMORYCHECKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
private:
	Insertdata insDialog;
};
