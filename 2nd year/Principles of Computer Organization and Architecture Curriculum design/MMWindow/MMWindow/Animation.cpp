// Animation.cpp : 实现文件
//

#include "stdafx.h"
#include "MMWindow.h"
#include "Animation.h"
#include "afxdialogex.h"
#include <stdio.h>

CShockwaveFlash m_flashPlayer;

// Animation 对话框

IMPLEMENT_DYNAMIC(Animation, CDialogEx)

Animation::Animation(CWnd* pParent /*=NULL*/)
	: CDialogEx(Animation::IDD, pParent)
{

}

Animation::~Animation()
{
}

BOOL Animation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TCHAR curD[150];
	::GetCurrentDirectoryA(150,curD);
	strcat_s(curD,150,"\\flash\\ModelMachine.swf");

	m_flashPlayer.LoadMovie(0,_T(curD));
	m_flashPlayer.Play();

	this->flash_simulate("PC+C->PC");

	return TRUE;
}

void Animation::flash_simulate(CString code)
{
	CString args = "<invoke name=\"simulate\" returntype=\"void\">";
	args += "<arguments><string>"+code+"</string></arguments>";
	args += "</invoke>";
	m_flashPlayer.CallFunction(args);
}

int Animation::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int result = CDialogEx::OnCreate(lpCreateStruct);

	return result;
}

void Animation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_flashPlayer);
}


BEGIN_MESSAGE_MAP(Animation, CDialogEx)
//	ON_WM_INITMENU()
END_MESSAGE_MAP()
