// Insertdata.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MMWindow.h"
#include "Insertdata.h"
#include "afxdialogex.h"


// Insertdata �Ի���

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


// Insertdata ��Ϣ�������


void Insertdata::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();

	_WORD tmpAddr,tmpValue;
	tmpValue.word = 0;
	CString str,result;
	this->GetDlgItem(IDC_EDIT2)->GetWindowTextA(str);
	tmpAddr.word=atosx(str.GetBuffer());
	result = "ƫ������"+str;
	if(atosx(str.GetBuffer())<0)
	{
		MessageBox("ƫ��������Ϊ��: "+atosx(str.GetBuffer()),"WARN");
		return;
	}
	// 00000 000 000 000 000
	this->GetDlgItem(IDC_EDIT1)->GetWindowTextA(str);
	tmpValue.word = atosx(str.GetBuffer());
	char buffer[50];
	//sprintf_s(buffer,"%.4X %.3X %.3X %.3X %.3X",this->op<<12,this->sr<<9,this->sd<<6,this->dr<<3,this->dd);
	sprintf_s(buffer,"%.4X",tmpValue.word);
	str.Format(_T("%s"),buffer);
	result += " ,ֵ��"+str;
	Write(tmpAddr,&tmpValue);

	MessageBox(result,"WARN");
}
