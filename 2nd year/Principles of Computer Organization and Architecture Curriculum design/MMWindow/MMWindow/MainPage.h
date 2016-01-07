#pragma once

#include "MemoryChecker.h"
#include "Animation.h"
#include "Insertdata.h"

// MainPage 对话框

class MainPage : public CDialogEx
{
	DECLARE_DYNAMIC(MainPage)

public:
	MainPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainPage();

// 对话框数据
	enum { IDD = IDD_MAINPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedTmp();
	MemoryChecker mc;
	Animation aniDialog;
	Insertdata insDialog;

//	CStatic m_static_cmd_text;
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChange_MAR();
	afx_msg void OnBnClickedButton6();

	Operators1* pb1;
	ProcessorBase2* pb2;
	Operators3* pb3;

	void initArgs();
	afx_msg void OnBnClickedNextcycle();
	afx_msg void OnBnClickedNextopecode();
	afx_msg void OnClose();
//	afx_msg void OnEnChangeMar();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();

	private:
		WORD op;
		WORD sr;
		WORD sd;
		WORD dr;
		WORD dd;
public:
	afx_msg void OnBnClickedButton7();
//	afx_msg void OnEnKillfocusPc();
	afx_msg void OnEnKillfocusSp();
//	afx_msg void OnEnKillfocusPsw();
//	afx_msg void OnEnKillfocusR0();
//	afx_msg void OnEnKillfocusR1();
//	afx_msg void OnEnKillfocusR2();
//	afx_msg void OnEnKillfocusR3();
	afx_msg void OnEnChangePc();
	afx_msg void OnEnChangeSp();
	afx_msg void OnEnChangePsw();
	afx_msg void OnEnChangeR0();
	afx_msg void OnEnChangeR1();
	afx_msg void OnEnChangeR2();
	afx_msg void OnEnChangeR3();
};

void callback(CPU* cpu,ProcessorBase* pb);
CString cycleCStringMapping(CPU_Cycle cycle);
void updateRegisterData();
