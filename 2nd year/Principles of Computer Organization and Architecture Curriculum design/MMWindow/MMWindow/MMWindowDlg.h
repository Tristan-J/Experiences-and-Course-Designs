
// MMWindowDlg.h : ͷ�ļ�
//

#pragma once

#include "MainPage.h"
#include "LoadAPPPage.h"
#include "resource.h"

#include <string>

using namespace std;

enum TAB_ITEM{MAIN_PAGE=0,SUB_LOADAPP_PAGE=1};

// CMMWindowDlg �Ի���
class CMMWindowDlg : public CDialogEx
{
// ����
public:
	CMMWindowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MMWINDOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
