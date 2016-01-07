// MemoryChecker.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MMWindow.h"
#include "MemoryChecker.h"
#include "afxdialogex.h"
#include "utils.h"
#include <cstring>

// MemoryChecker �Ի���

IMPLEMENT_DYNAMIC(MemoryChecker, CDialogEx)

MemoryChecker::MemoryChecker(CWnd* pParent /*=NULL*/)
	: CDialogEx(MemoryChecker::IDD, pParent)
{

}

BOOL MemoryChecker::OnInitDialog()
{
	this->insDialog.Create(IDD_INSERTDATA,this);
	return true;
}

MemoryChecker::~MemoryChecker()
{
}

void MemoryChecker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MemoryChecker, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MemoryChecker::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &MemoryChecker::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &MemoryChecker::OnBnClickedButton2)
END_MESSAGE_MAP()


// MemoryChecker ��Ϣ�������

void MemoryChecker::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT addr,num;
	CString tmp;
	this->GetDlgItem(IDC_EDIT1)->SetWindowTextA("");

	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(tmp);
	addr = atosx(tmp.GetBuffer());
	this->GetDlgItem(IDC_EDIT3)->GetWindowTextA(tmp);
	num = atoi(tmp.GetBuffer());
	if(addr<=0)addr=0;
	if(num<=0)num=80;
	checkMemory(addr,num,this->GetDlgItem(IDC_EDIT1),10);
}


void MemoryChecker::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT addr,num;
	CString tmp;
	this->GetDlgItem(IDC_EDIT1)->SetWindowTextA("");

	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(tmp);
	addr = atosx(tmp.GetBuffer());
	this->GetDlgItem(IDC_EDIT3)->GetWindowTextA(tmp);
	num = atoi(tmp.GetBuffer());
	if(addr<=0)addr=0;
	if(num<=0)num=80;
	checkMemory(addr,num,this->GetDlgItem(IDC_EDIT1),10);
}


void MemoryChecker::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect pwPos,clPos;
	this->GetClientRect(pwPos);
	this->insDialog.GetClientRect(clPos);
	this->insDialog.SetWindowPos(&wndTop,pwPos.left+pwPos.Width()/4,pwPos.top+pwPos.Height()/4,clPos.Width(),clPos.Height(),SWP_NOSIZE);
	this->insDialog.ShowWindow(true);
}
