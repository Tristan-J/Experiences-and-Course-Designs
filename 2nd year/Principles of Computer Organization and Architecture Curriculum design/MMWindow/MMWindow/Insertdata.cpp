// Insertdata.cpp : 实现文件
//

#include "stdafx.h"
#include "MMWindow.h"
#include "Insertdata.h"
#include "afxdialogex.h"


// Insertdata 对话框

IMPLEMENT_DYNAMIC(Insertdata, CDialogEx)

Insertdata::Insertdata(CWnd* pParent /*=NULL*/)
	: CDialogEx(Insertdata::IDD, pParent)
{

}

Insertdata::~Insertdata()
{
}

void Insertdata::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Insertdata, CDialogEx)
	ON_BN_CLICKED(IDOK, &Insertdata::OnBnClickedOk)
END_MESSAGE_MAP()


// Insertdata 消息处理程序


void Insertdata::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	_WORD tmpAddr,tmpValue;
	tmpValue.word = 0;
	CString str,result;
	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(str);
	tmpAddr.word=atosx(str.GetBuffer());
	result = "偏移量："+str;
	if(atosx(str.GetBuffer())<0)
	{
		MessageBox("偏移量不能为负: "+atosx(str.GetBuffer()),"WARN");
		return;
	}
	// 00000 000 000 000 000
	this->GetDlgItem(IDC_EDIT1)->GetWindowTextA(str);
	tmpValue.word = atosx(str.GetBuffer());
	char buffer[50];
	//sprintf_s(buffer,"%.4X %.3X %.3X %.3X %.3X",this->op<<12,this->sr<<9,this->sd<<6,this->dr<<3,this->dd);
	sprintf_s(buffer,"%.4X",tmpValue.word);
	str.Format(_T("%s"),buffer);
	result += " ,值："+str;
	Write(tmpAddr,&tmpValue);

	MessageBox(result,"WARN");
}
