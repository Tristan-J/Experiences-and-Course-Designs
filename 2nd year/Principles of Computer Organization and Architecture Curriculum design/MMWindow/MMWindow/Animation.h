#pragma once
#include "cshockwaveflash.h"


// Animation �Ի���

class Animation : public CDialogEx
{
	DECLARE_DYNAMIC(Animation)

public:
	Animation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Animation();

// �Ի�������
	enum { IDD = IDD_ANIMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void flash_simulate(CString code);

	CShockwaveFlash m_flashPlayer;
//	afx_msg void OnInitMenu(CMenu* pMenu);
};
