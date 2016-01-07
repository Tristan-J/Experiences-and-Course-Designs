#pragma once
#include "cshockwaveflash.h"


// Animation 对话框

class Animation : public CDialogEx
{
	DECLARE_DYNAMIC(Animation)

public:
	Animation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Animation();

// 对话框数据
	enum { IDD = IDD_ANIMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void flash_simulate(CString code);

	CShockwaveFlash m_flashPlayer;
//	afx_msg void OnInitMenu(CMenu* pMenu);
};
