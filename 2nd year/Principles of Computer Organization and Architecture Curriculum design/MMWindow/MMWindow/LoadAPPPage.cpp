// LoadAPPPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MMWindow.h"
#include "LoadAPPPage.h"
#include "afxdialogex.h"


// LoadAPPPage �Ի���

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


// LoadAPPPage ��Ϣ�������

BOOL LoadAPPPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->mc.Create(IDD_MEMORYCHECKER,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void LoadAPPPage::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_WORD tmpAddr,tmpValue;
	tmpValue.word = 0;
	CString str,result;
	//����ƫ����
	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(str);
	tmpAddr.word=atosx(str.GetBuffer());
	result = "ƫ������"+str;
	if(atosx(str.GetBuffer())<0)
	{
		MessageBox("ƫ��������Ϊ��: "+atosx(str.GetBuffer()),"WARN");
		return;
	}
	// ת���ı�Ϊ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->mc.ShowWindow(true);
}
