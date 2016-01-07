// LoadAPPPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MMWindow.h"
#include "LoadAPPPage.h"
#include "afxdialogex.h"


// LoadAPPPage 对话框

IMPLEMENT_DYNAMIC(LoadAPPPage, CDialogEx)

LoadAPPPage::LoadAPPPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoadAPPPage::IDD, pParent)
{

}

LoadAPPPage::~LoadAPPPage()
{
}

void LoadAPPPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoadAPPPage, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoadAPPPage::OnBnClickedOk)
	ON_BN_CLICKED(IDOK5, &LoadAPPPage::OnBnClickedOk5)
END_MESSAGE_MAP()


// LoadAPPPage 消息处理程序

BOOL LoadAPPPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->mc.Create(IDD_MEMORYCHECKER,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void LoadAPPPage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	_WORD tmpAddr,tmpValue;
	tmpValue.word = 0;
	CString str,result;
	//处理偏移量
	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(str);
	tmpAddr.word=atosx(str.GetBuffer());
	result = "偏移量："+str;
	if(atosx(str.GetBuffer())<0)
	{
		MessageBox("偏移量不能为负: "+atosx(str.GetBuffer()),"WARN");
		return;
	}
	// 转化文本为二进制数据
	this->GetDlgItem(IDC_EDIT1)->GetWindowTextA(str);
	char delims[5] = "\n";
	char* toks = strtok(str.GetBuffer(),delims);
	CString tmp;
	while(toks!=NULL)
	{
		tmp.Format("%s",toks);
		tmp.Trim();
		toks = tmp.GetBuffer();
		if(toks[0]=='#')
		{
			toks = strtok(NULL,delims);
			continue;
		}
		tmpValue.word = BinToHex(toks);
		Write(tmpAddr,&tmpValue);
		toks = strtok(NULL,delims);
		tmpAddr.word += 2;
	}

}


void LoadAPPPage::OnBnClickedOk5()
{
	// TODO: 在此添加控件通知处理程序代码
	this->mc.ShowWindow(true);
}
