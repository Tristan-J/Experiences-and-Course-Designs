
// 计组课程设计Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "计组课程设计.h"
#include "计组课程设计Dlg.h"
#include "afxdialogex.h"
#include "TipDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int opcode;
int addressing_dt[2];
int addressing_st[2];

CComboBox *m_combo2;
CComboBox *m_combo3;


//数组元素的下标对应着地址的编号
CString AddressNumArray[6][6] = {
	{_T("R0"),_T("R1"),_T("R2"),_T("R3"),_T("SP"),_T("PC")},//00~05
	{_T("(R0)"),_T("(R1)"),_T("(R2)"),_T("(R3)")},//10~13
	{_T("-(R0)"),_T("-(R1)"),_T("-(R2)"),_T("-(R3)"),_T("-(SP)")},//20~24
	{_T("(R0)+"),_T("(R1)+"),_T("(R2)+"),_T("(R3)+"),_T("(SP)+"),_T("(PC)+")},//30~35
	{_T("X(R0)"),_T("X(R1)"),_T("X(R2)"),_T("X(R3)"),_T("X(PC)")},//40~44
	{_T("NULL")}//50 不使用为空
};

//每个操作码所能使用的寻址方式及寄存器号,第一位为地址个数
const int MatchDecisionTable[14][28] = {
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//MOV 00
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//ADD 01
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//SUB 02
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//AND 03
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//OR  04
	{ 26, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44 },//EOR 05
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//COM 06
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//NEG 07
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//INC 08
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//DEC 09
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//SL  10
	{ 27, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50},//SR  11
	{ 22, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 30, 31, 32, 33, 34, 35, 40, 41, 42, 43, 44, 50 },//JMP(RST) 12
	{ 17, 00, 01, 02, 03, 04, 05, 10, 11, 12, 13, 30, 31, 32, 33, 34, 35, 50 },//JSR  13
};

int* _judge(int addressing[2], CString addressing_str){
	int i, j, s = -1;

	for (i = 0; i<6; i++){
		for (j = 0; j<6; j++){
			if (AddressNumArray[i][j] == addressing_str){
				s = 0;
				break;
			}
		}
		if (s == 0){
			break;
		}
	}

	addressing[0] = i;
	addressing[1] = j;

	return addressing;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C计组课程设计Dlg 对话框



C计组课程设计Dlg::C计组课程设计Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C计组课程设计Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C计组课程设计Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
}

BEGIN_MESSAGE_MAP(C计组课程设计Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C计组课程设计Dlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &C计组课程设计Dlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &C计组课程设计Dlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &C计组课程设计Dlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// C计组课程设计Dlg 消息处理程序

BOOL C计组课程设计Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C计组课程设计Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C计组课程设计Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C计组课程设计Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C计组课程设计Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
  
    CTipDlg tipDlg;           // 构造对话框类CTipDlg的实例   
    nRes = tipDlg.DoModal();  // 弹出对话框
	CDialogEx::OnOK();
}


void C计组课程设计Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	opcode = m_combo1.GetCurSel();//得到操作码
	int opcode_MDT[28];

	for (int i = 0; i<28; i++){//得到这个操作码对应的地址码关系
		opcode_MDT[i] = MatchDecisionTable[opcode][i];
	}

	m_combo2.ResetContent();//清空控件数据
	m_combo3.ResetContent();

	int n = opcode_MDT[0];//地址码个数

	int r,c;
	for(int i = 1; i <= n; i++){
		r = opcode_MDT[i] / 10;//行数
		c = opcode_MDT[i] % 10;//列数

		if (opcode < 06 || i != n){//opcode>=06&&i==n的非
			m_combo2.AddString(AddressNumArray[r][c]);//添加字符串到控件
		}

		if (opcode < 06){//双地址
			m_combo3.AddString(AddressNumArray[r][c]);
		}
		if (opcode >= 06 && i == n){//对单地址的特殊处理
			m_combo3.AddString(AddressNumArray[5][0]);
		}
	}

}


void C计组课程设计Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString addressing_str1;
	int n1 = m_combo2.GetCurSel();

	m_combo2.GetLBText(n1, addressing_str1);//根据索引得到地址码字符串

	_judge(addressing_dt, addressing_str1);//得到关于地址码的一维二元整型数组
}


void C计组课程设计Dlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString addressing_str2;
	int n2 = m_combo3.GetCurSel();

	m_combo3.GetLBText(n2, addressing_str2);//根据索引得到地址码字符串

	_judge(addressing_st, addressing_str2);	//得到关于地址码的一维二元整型数组
}
