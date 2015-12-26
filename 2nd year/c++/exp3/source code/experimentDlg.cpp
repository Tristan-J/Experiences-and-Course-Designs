
// experimentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "experiment.h"
#include "experimentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW 
#endif

//{{ 全局说明添加在这里
List list;
void access(QUADPTR quad)
	{
		if (quad->name == "Rectangle")
		{
			Rect *p = reinterpret_cast<Rect *>(quad);
			p->draw();
			cout << "area = " << p->area() << endl;
		}
		else if (quad->name == "Diamond") {
			Diamond *p = reinterpret_cast<Diamond *>(quad);
			p->draw();
			cout << "area = " << p->area() << endl;
		}
		else if (quad->name == "Parallelogram") {
			Parallelogram *p = reinterpret_cast<Parallelogram *>(quad);
			p->draw();
			cout << "area = " << p->area() << endl;
		}
		else if (quad->name == "Trapezoid") {
			Trapezoid *p = reinterpret_cast<Trapezoid *>(quad);
			p->draw();
			cout << "area = " << p->area() << endl;
		}
		else if (quad->name == "Square") {
			Square *p = reinterpret_cast<Square *>(quad);
			p->draw();
			cout << "area = " << p->area() << endl;
		}
		return ;
	}
//}}

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


// CexperimentDlg 对话框

CexperimentDlg::CexperimentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CexperimentDlg::IDD, pParent)
	, lastDone(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	answer = 0.0;
	result = _T("");
}

void CexperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANSWER, answer);
	DDV_MinMaxDouble(pDX, answer, 1, 5000);
	DDX_Text(pDX, IDC_EDIT_RESULT, result);
	DDV_MaxChars(pDX, result, 30);
}

BEGIN_MESSAGE_MAP(CexperimentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CexperimentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CexperimentDlg::OnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CexperimentDlg::OnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CexperimentDlg::OnClickedButtonSubmit)
END_MESSAGE_MAP()


// CexperimentDlg 消息处理程序

BOOL CexperimentDlg::OnInitDialog()
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
	pCanvas = new Canvas();
	pCanvas->Create(NULL, NULL, WS_BORDER, CRect(20, 20, 560, 420), this, 999);
	pCanvas->SetScrollSizes (MM_TEXT, CSize(560, 2000));
	pCanvas->ShowWindow (TRUE);

	answer = 10.0;
	UpdateData(FALSE);

	srand(unsigned(time(NULL)));

	//{{ 如果你还有其他的初始化需求，请把代码放在符号//{{和//}}之间
		//你的初始化代码放在这里
	//}}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexperimentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CexperimentDlg::OnPaint()
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
HCURSOR CexperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexperimentDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CexperimentDlg::OnClickedButtonNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pCanvas->isLearning)
	{
		//{{
		//这里，创建一个形体，然后调用这个形体的draw()方法
		QUADPTR quad = createAquad();
		quad->draw();
		//}}

		lastDone = false;
	}

	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	p->EnableWindow (FALSE);
}


void CexperimentDlg::OnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	pCanvas->toggleMode ();

	BOOL enable = TRUE;
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	CString s;
	p->GetWindowText(s);
	if (s == "开始学习")
	{
		p->SetWindowText(_T("停止学习"));

		OnClickedButtonNext();
	}
	else
	{
		p->SetWindowText(_T("开始学习"));

		//如果最后一道题没有做，那么将该题涉及的形体从列表中删除
		if (!lastDone) list.pop_back();

		//{{ 请在这里添加遍历的代码
		list.traverse();
		//}}

		pCanvas->Invalidate ();
		
		enable = FALSE;
		CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
		p->EnableWindow (FALSE);
	}

	p = (CButton *)GetDlgItem(IDC_BUTTON_SUBMIT);
	p->EnableWindow (enable);
	CEdit *q = (CEdit *)GetDlgItem(IDC_EDIT_ANSWER);
	q->EnableWindow (enable);
}


void CexperimentDlg::OnClickedButtonSubmit()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	BOOL enable = TRUE;
	int ref = static_cast<int>(pCanvas->area * 10);
	int area = static_cast<int>(answer * 10);
	if (ref == area)
	{
		result = _T("OK!");
		lastDone = true;
	}
	else
	{
		result = _T("答案错误");
		enable = FALSE;
	}
	UpdateData(FALSE);

	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	p->EnableWindow (enable);
}


QUADPTR CexperimentDlg::createAquad(void)
{
	//{{
	//请在这里添加生成某个形体的代码
	//采用随机的方式生成平行四边形、梯形、矩形、菱形和正方形之一
	//形体的特征数据也是随机生成的
	//生成一个形体后将其指针保存到列表中
	//函数的返回值是生成的形体的指针
	
	srand(unsigned(time(NULL)));
		//为图形申请空间
		//注：不可用 Parallelogram pa; 这样的声明，否则会被解析
		qPtr q ;
		Node * nodePtr = new Node;
		Parallelogram * paPtr = new Parallelogram;
		Rect * rPtr = new Rect;
		Diamond * dPtr = new Diamond;
		Square * sPtr = new Square;
		Trapezoid * tPtr = new Trapezoid;

		//声明循环中改变并析构的变量
		int random = 1+rand()%5;
		double width = 1+rand()%10;
		double height = 1+rand()%10;
		
			//选择四边形
			if (random==1){
				Parallelogram p(width,height);
				*paPtr = p;
				q=paPtr;
			}
			else if (random==2){
				Rect p(width,height);
				*rPtr = p;
				q=rPtr;
			}
			else if (random==3){
				double a=width;
				double b=height;
				Diamond p(a,b);
				*dPtr = p;
				q=dPtr;
			}
			else if (random==4){
				double a=width;
				Square p(a);
				*sPtr = p;
				q = sPtr;
			}
			else {
				double a=width;
				double b=rand()%10;
				Trapezoid p(a,b,height);
				*tPtr = p;
				q=tPtr;
			}
			(list)+=q;
			return q;
	//}}
}



BOOL CexperimentDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	//if (wParam == 1 || wParam == 2) return FALSE;

	return CDialogEx::OnCommand(wParam, lParam);
}
