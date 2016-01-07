// MainPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MMWindow.h"
#include "MainPage.h"
#include "afxdialogex.h"
#include "resource.h"

// MainPage 对话框

IMPLEMENT_DYNAMIC(MainPage, CDialogEx)

MainPage::MainPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(MainPage::IDD, pParent)
{
}

MainPage::~MainPage()
{
}

void MainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_CMD, m_static_cmd_text);
}


BEGIN_MESSAGE_MAP(MainPage, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON3, &MainPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &MainPage::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &MainPage::OnEnChange_MAR)
	ON_BN_CLICKED(IDC_BUTTON6, &MainPage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_NextCycle, &MainPage::OnBnClickedNextcycle)
	ON_BN_CLICKED(IDC_NextOpeCode, &MainPage::OnBnClickedNextopecode)
	ON_WM_CLOSE()
//	ON_EN_CHANGE(IDC_MAR, &MainPage::OnEnChangeMar)
ON_CBN_SELCHANGE(IDC_COMBO1, &MainPage::OnCbnSelchangeCombo1)
ON_CBN_SELCHANGE(IDC_COMBO2, &MainPage::OnCbnSelchangeCombo2)
ON_CBN_SELCHANGE(IDC_COMBO3, &MainPage::OnCbnSelchangeCombo3)
ON_CBN_SELCHANGE(IDC_COMBO4, &MainPage::OnCbnSelchangeCombo4)
ON_CBN_SELCHANGE(IDC_COMBO5, &MainPage::OnCbnSelchangeCombo5)
ON_BN_CLICKED(IDC_BUTTON7, &MainPage::OnBnClickedButton7)
//ON_EN_KILLFOCUS(IDC_PC, &MainPage::OnEnKillfocusPc)
ON_EN_KILLFOCUS(IDC_SP, &MainPage::OnEnKillfocusSp)
//ON_EN_KILLFOCUS(IDC_PSW, &MainPage::OnEnKillfocusPsw)
//ON_EN_KILLFOCUS(IDC_R0, &MainPage::OnEnKillfocusR0)
//ON_EN_KILLFOCUS(IDC_R1, &MainPage::OnEnKillfocusR1)
//ON_EN_KILLFOCUS(IDC_R2, &MainPage::OnEnKillfocusR2)
//ON_EN_KILLFOCUS(IDC_R3, &MainPage::OnEnKillfocusR3)
ON_EN_CHANGE(IDC_PC, &MainPage::OnEnChangePc)
ON_EN_CHANGE(IDC_SP, &MainPage::OnEnChangeSp)
ON_EN_CHANGE(IDC_PSW, &MainPage::OnEnChangePsw)
ON_EN_CHANGE(IDC_R0, &MainPage::OnEnChangeR0)
ON_EN_CHANGE(IDC_R1, &MainPage::OnEnChangeR1)
ON_EN_CHANGE(IDC_R2, &MainPage::OnEnChangeR2)
ON_EN_CHANGE(IDC_R3, &MainPage::OnEnChangeR3)
END_MESSAGE_MAP()


// MainPage 消息处理程序

//回调，控制主界面
MainPage* mainPage = NULL;
ProcessorBase* curPb = NULL;

void cycleCStringMapping(CPU_Cycle cycle,CString* str)
{
	switch(cycle)
	{
		case FT:
			(*str) = "FT";
			break;
		case ST:
			(*str) = "ST";
			break;
		case DT:
			(*str) = "DT";
			break;
		case ET:
			(*str) = "ET";
			break;
		case DMAT:
			(*str) = "DMAT";
			break;
		case IT:
			(*str) = "IT";
			break;
		default:
			(*str) = "UnKnown";
	}

}

void updateRegisterData()
{
	char buffer[10];
	//获取各寄存器的值 MAR=1,MDR,IR,PC,SP,PSW,R0,R1,R2,R3,C,D
	MM_INT16 _MAR_,_MDR_,_IR_,_PC_,_SP_,_PSW_,_R0_,_R1_,_R2_,_R3_,_C_,_D_;//12个寄存器存储单元 
	_MAR_ = *(_cpu->getRegister(MAR));
	_MDR_ = *(_cpu->getRegister(MDR));
	_IR_ = *(_cpu->getRegister(IR));
	_PC_ = *(_cpu->getRegister(PC));
	_SP_ = *(_cpu->getRegister(SP));
	_PSW_ = *(_cpu->getRegister(PSW));
	_R0_ = *(_cpu->getRegister(R0));
	_R1_ = *(_cpu->getRegister(R1));
	_R2_ = *(_cpu->getRegister(R2));
	_R3_ = *(_cpu->getRegister(R3));
	_C_ = *(_cpu->getRegister(C));
	_D_ = *(_cpu->getRegister(D));

	//更新寄存器显示
	sprintf_s(buffer,"%.4X",_MAR_.STG); mainPage->SetDlgItemTextA(IDC_MAR,buffer);
	sprintf_s(buffer,"%.4X",_MDR_.STG); mainPage->SetDlgItemTextA(IDC_MDR,buffer);
	sprintf_s(buffer,"%.4X",_IR_.STG); mainPage->SetDlgItemTextA(IDC_IR,buffer);
	sprintf_s(buffer,"%.4X",_PC_.STG); mainPage->SetDlgItemTextA(IDC_PC,buffer);
	sprintf_s(buffer,"%.4X",_SP_.STG); mainPage->SetDlgItemTextA(IDC_SP,buffer);
	sprintf_s(buffer,"%.4X",_PSW_.STG); mainPage->SetDlgItemTextA(IDC_PSW,buffer);
	sprintf_s(buffer,"%.4X",_R0_.STG); mainPage->SetDlgItemTextA(IDC_R0,buffer);
	sprintf_s(buffer,"%.4X",_R1_.STG); mainPage->SetDlgItemTextA(IDC_R1,buffer);
	sprintf_s(buffer,"%.4X",_R2_.STG); mainPage->SetDlgItemTextA(IDC_R2,buffer);
	sprintf_s(buffer,"%.4X",_R3_.STG); mainPage->SetDlgItemTextA(IDC_R3,buffer);
	sprintf_s(buffer,"%.4X",_C_.STG); mainPage->SetDlgItemTextA(IDC_C,buffer);
	sprintf_s(buffer,"%.4X",_D_.STG); mainPage->SetDlgItemTextA(IDC_D,buffer);
}

void callback(CPU* cpu,ProcessorBase* pb)
{
	curPb = pb;
	
	updateRegisterData();

	CString curCPUCycle;
	cycleCStringMapping(_cpu->getCPUCycle(),&curCPUCycle);

	int curOpeCode = _cpu->getRegister(IR)->STG;

	int curOpeLen = 0;
	const string* curOpe = _cpu->getCurMicroCommand(curOpeLen);
	CString curOpeStr;
	for(int i=0;i<curOpeLen;i++)
	{
		curOpeStr += _T(curOpe[i].c_str());
		curOpeStr += "\r\n";
		mainPage->aniDialog.flash_simulate(_T(curOpe[i].c_str()));
	}

	//更新当前周期显示
	mainPage->SetDlgItemTextA(IDC_Cycle,curCPUCycle);
	//更新当前CPU操作显示
	mainPage->SetDlgItemTextA(IDC_CurOpe,curOpeStr);
}

//CPU初始化
 CPU* _cpu;

 void MainPage::initArgs()
 {
	 mainPage = this;
	//ini CPU	
	_cpu = new CPU();
	this->pb1 = new Operators1();
	this->pb2 = new ProcessorBase2();;
	this->pb3 = new Operators3();
	_cpu->addPB(static_cast<ProcessorBase*>(pb1));
	_cpu->addPB(static_cast<ProcessorBase*>(pb2));
	_cpu->addPB(static_cast<ProcessorBase*>(pb3));
	_cpu->CallBackShell = &callback;
	_cpu->prepare();
	_cpu->setDEBUG(true);

	this->op = 0;
	this->sr = 0;
	this->sd = 0;
	this->dr = 0;
	this->dd = 0;
 }

int MainPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int result = CDialogEx::OnCreate(lpCreateStruct);

	return result;
}

void initComboBox(MainPage* _this)//MAR=1,MDR,IR,PC,SP,PSW,R0,R1,R2,R3,C,D
{
	CComboBox* opCode = (CComboBox*)_this->GetDlgItem(IDC_COMBO1);
	CComboBox* sr = (CComboBox*)_this->GetDlgItem(IDC_COMBO2);
	CComboBox* sd = (CComboBox*)_this->GetDlgItem(IDC_COMBO3);
	CComboBox* dr = (CComboBox*)_this->GetDlgItem(IDC_COMBO4);
	CComboBox* dd = (CComboBox*)_this->GetDlgItem(IDC_COMBO5);

	opCode->AddString("MOV");	sr->AddString("MAR");	sd->AddString("寄存器寻址");	dr->AddString("MAR");	dd->AddString("寄存器寻址");
	opCode->AddString("ADD");	sr->AddString("MDR");	sd->AddString("寄存器间址");	dr->AddString("MDR");	dd->AddString("寄存器间址");
	opCode->AddString("SUB");	sr->AddString("IR");	sd->AddString("自减型间址");	dr->AddString("IR");	dd->AddString("自减型间址");
	opCode->AddString("AND");	sr->AddString("PC");	sd->AddString("自增型间址");	dr->AddString("PC");	dd->AddString("自增型间址");
	opCode->AddString("OR");	sr->AddString("SP");	sd->AddString("自增型双间址");	dr->AddString("SP");	dd->AddString("自增型双间址");
	opCode->AddString("EOR");	sr->AddString("PSW");	sd->AddString("变址寻址");		dr->AddString("PSW");	dd->AddString("变址寻址");
	opCode->AddString("COM");	sr->AddString("R0");	sd->AddString("跳步");			dr->AddString("R0");	dd->AddString("跳步");
	opCode->AddString("NEG");	sr->AddString("R1");	sd->AddString(" ");				dr->AddString("R1");	dd->AddString(" ");
	opCode->AddString("INC");	sr->AddString("R2");									dr->AddString("R2");
	opCode->AddString("DEC");	sr->AddString("R3");									dr->AddString("R3");
	opCode->AddString("SL");	sr->AddString("C");										dr->AddString("C");
	opCode->AddString("SR");	sr->AddString("D");										dr->AddString("D");
	opCode->AddString("JMP");	sr->AddString(" ");										dr->AddString(" ");
	opCode->AddString("RST");
	opCode->AddString("JSR");
	opCode->AddString(" ");
}

BOOL MainPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->mc.Create(IDD_MEMORYCHECKER,this);
	this->aniDialog.Create(IDD_ANIMATION,this);
	this->insDialog.Create(IDD_INSERTDATA,this);

	initComboBox(this);

	this->initArgs();
	updateRegisterData();

	/*mainPage->GetDlgItem(IDC_Cycle);
	mainPage->GetDlgItem(IDC_CurCode);
	mainPage->GetDlgItem(IDC_CurOpe);*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MainPage::OnBnClickedButton3()
{
	this->mc.ShowWindow(true);
	// TODO: 在此添加控件通知处理程序代码
}


void MainPage::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	this->aniDialog.ShowWindow(true);
}


void MainPage::OnEnChange_MAR()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	CString value;
	this->GetDlgItem(IDC_EDIT1)->GetWindowTextA(value);
	MessageBox("确定改变MAR的值为"+value+"吗","WARN");
	// TODO:  在此添加控件通知处理程序代码
}


void MainPage::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	_WORD tmpAddr,tmpValue;
	tmpValue.word = 0;
	CString str,result;
	this->GetDlgItem(IDC_EDIT17)->GetWindowTextA(str);
	tmpAddr.word=atosx(str.GetBuffer());
	result = "偏移量："+str;
	if(atosx(str.GetBuffer())<0)
	{
		MessageBox("偏移量不能为负: "+atosx(str.GetBuffer()),"WARN");
		return;
	}
	// 00000 000 000 000 000
	//this->GetDlgItem(IDC_EDIT16)->GetWindowTextA(str);
	//tmpValue.word = atosx(str.GetBuffer());
	tmpValue.word = this->op<<12;
	tmpValue.word += this->sr<<9;
	tmpValue.word += this->sd<<6;
	tmpValue.word += this->dr<<3;
	tmpValue.word += this->dd;
	char buffer[50];
	//sprintf_s(buffer,"%.4X %.3X %.3X %.3X %.3X",this->op<<12,this->sr<<9,this->sd<<6,this->dr<<3,this->dd);
	sprintf_s(buffer,"%.4X",tmpValue.word);
	str.Format(_T("%s"),buffer);
	result += " ,值："+str;
	Write(tmpAddr,&tmpValue);

	MessageBox(result,"WARN");
}

int status = 1;
void MainPage::OnBnClickedNextcycle()
{
	// TODO: 在此添加控件通知处理程序代码
 	if(curPb!=NULL&&status)
		status = curPb->next();

	//updateRegisterData();
}


void MainPage::OnBnClickedNextopecode()
{
	// TODO: 在此添加控件通知处理程序代码

	status = 1;
	if(_cpu->getCPUStatus()==PREPARED)
	{
		//MessageBox("RUNNING","CPU Status");
		_cpu->start();
	}
	else
	{
		//MessageBox("NEXTOP","CPU");
		_cpu->nextOp();
	}
	//updateRegisterData();
}


void MainPage::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	delete _cpu;
	delete this->pb1;
	delete this->pb2;
	delete this->pb3;
	CDialogEx::OnClose();
}


//void MainPage::OnEnChangeMar()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}

WORD mapOPCode(CString& op)
{//MOV=0,ADD,SUB,AND,OR,EOR,COM,NEG,INC,DEC,SL,SR,JMP,RST,JSR
	OP opc = (OP)0;
	if(op=="MOV")
		opc = MOV;
	else if(op=="ADD")
		opc = ADD;
	else if(op=="SUB")
		opc = SUB;
	else if(op=="AND")
		opc = AND;
	else if(op=="OR")
		opc = OR;
	else if(op=="EOR")
		opc = EOR;
	else if(op=="COM")
		opc = COM;
	else if(op=="NEG")
		opc = NEG;
	else if(op=="INC")
		opc = INC;
	else if(op=="DEC")
		opc = DEC;
	else if(op=="SL")
		opc = SL;
	else if(op=="SR")
		opc = SR;
	else if(op=="JMP")
		opc = JMP;
	else if(op=="RST")
		opc = RST;
	else if(op=="JSR")
		opc = JSR;
	else if(op ==" ")
		opc = (OP)0;

	return opc;
}

/*	寻址方式
*	R_0:寄存器寻址		R_1:寄存器间址
*	R_2:自减型间址		R_3:自增型间址
*	R_4:自增型双间址	R_5:变址寻址
*	R_6:跳步
*	PSW寄存器只适用于R_0型寻址方式
*	PC寄存器不适用于R_2型寻址方式
*	
*/
WORD mapAddr(CString& addr)
{
	AM am = (AM)0;
	if(addr == "寄存器寻址")
		am = R_0;
	else if(addr == "寄存器间址")
		am = R_1;
	else if(addr == "自减型间址")
		am = R_2;
	else if(addr == "自增型间址")
		am = R_3;
	else if(addr == "自增型双间址")
		am = R_4;
	else if(addr == "变址寻址")
		am = R_5;
	else if(addr == "跳步")
		am = R_6;
	else if(addr == " ")
		am = (AM)0;

	return am;
}

WORD mapReg(CString& r)
{//PC,SP,PSW,R0,R1,R2,R3
	REGISTER reg = (REGISTER)0;
	
	if(r=="IR")
		reg = IR;
	else if(r=="PC")
		reg = PC;
	else if(r=="SP")
		reg = SP;
	else if(r=="PSW")
		reg = PSW;
	else if(r=="R0")
		reg = R0;
	else if(r=="R1")
		reg = R1;
	else if(r=="R2")
		reg = R2;
	else if(r=="R3")
		reg = R3;
	else if(r==" ")
		reg = (REGISTER)0;

	return reg;
}

void MainPage::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString op;
	CComboBox* opCode = (CComboBox*)this->GetDlgItem(IDC_COMBO1);
	opCode->GetLBText(opCode->GetCurSel(),op);

	this->op = mapOPCode(op);
}


void MainPage::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString reg;
	CComboBox* opCode = (CComboBox*)this->GetDlgItem(IDC_COMBO2);
	opCode->GetLBText(opCode->GetCurSel(),reg);

	this->sr = mapReg(reg);
}


void MainPage::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString am;
	CComboBox* opCode = (CComboBox*)this->GetDlgItem(IDC_COMBO3);
	opCode->GetLBText(opCode->GetCurSel(),am);
	this->sd = mapAddr(am);
}


void MainPage::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString reg;
	CComboBox* opCode = (CComboBox*)this->GetDlgItem(IDC_COMBO4);
	opCode->GetLBText(opCode->GetCurSel(),reg);

	this->dr = mapReg(reg);
}


void MainPage::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString am;
	CComboBox* opCode = (CComboBox*)this->GetDlgItem(IDC_COMBO5);
	opCode->GetLBText(opCode->GetCurSel(),am);

	this->dd = mapAddr(am);
}


void MainPage::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect pwPos,clPos;
	this->GetWindowRect(pwPos);
	this->insDialog.GetClientRect(clPos);
	this->insDialog.SetWindowPos(NULL,pwPos.left+pwPos.Width()/4,pwPos.top+pwPos.Height()/4,clPos.Width(),clPos.Height(),SWP_NOSIZE);
	this->insDialog.ShowWindow(true);
}

CString changeRegisterValue(int id,REGISTER reg,CString regName="")
{
	CPUOperator op;
	CString pcValue,msg="";
	int oldValue = op.Register(reg)->WORD;
	int newValue;
	BOOL same = 0;
	mainPage->GetDlgItemTextA(id,pcValue);
	newValue = atosx(pcValue.GetBuffer());
	if(newValue==oldValue)
		return msg;
	op.Register(reg)->WORD = newValue;
	msg += "修改";
	msg += regName;
	msg += "为：";
	msg += pcValue.GetBuffer();

	return msg;
}

//void MainPage::OnEnKillfocusPc()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_PC,PC,"PC");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


void MainPage::OnEnKillfocusSp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString result = changeRegisterValue(IDC_SP,SP,"SP");
	if(result!="")
		MessageBox(result,"INFO");
}


//void MainPage::OnEnKillfocusPsw()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_PSW,PSW,"PSW");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


//void MainPage::OnEnKillfocusR0()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_R0,R0,"R0");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


//void MainPage::OnEnKillfocusR1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_R1,R1,"R1");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


//void MainPage::OnEnKillfocusR2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_R2,R2,"R2");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


//void MainPage::OnEnKillfocusR3()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString result = changeRegisterValue(IDC_R3,R3,"R3");
//	if(result!="")
//		MessageBox(result,"INFO");
//}


void MainPage::OnEnChangePc()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_PC,PC,"PC");
}


void MainPage::OnEnChangeSp()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_SP,SP,"SP");
}


void MainPage::OnEnChangePsw()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_PSW,PSW,"PSW");
}


void MainPage::OnEnChangeR0()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_R0,R0,"R0");
}


void MainPage::OnEnChangeR1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_R1,R1,"R1");
}


void MainPage::OnEnChangeR2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_R2,R2,"R2");
}


void MainPage::OnEnChangeR3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	changeRegisterValue(IDC_R3,R3,"R3");
}
