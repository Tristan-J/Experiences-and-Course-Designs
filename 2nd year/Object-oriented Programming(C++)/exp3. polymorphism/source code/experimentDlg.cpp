
// experimentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "experiment.h"
#include "experimentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW 
#endif

//{{ ȫ��˵�����������
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CexperimentDlg �Ի���

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


// CexperimentDlg ��Ϣ�������

BOOL CexperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pCanvas = new Canvas();
	pCanvas->Create(NULL, NULL, WS_BORDER, CRect(20, 20, 560, 420), this, 999);
	pCanvas->SetScrollSizes (MM_TEXT, CSize(560, 2000));
	pCanvas->ShowWindow (TRUE);

	answer = 10.0;
	UpdateData(FALSE);

	srand(unsigned(time(NULL)));

	//{{ ����㻹�������ĳ�ʼ��������Ѵ�����ڷ���//{{��//}}֮��
		//��ĳ�ʼ�������������
	//}}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CexperimentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CexperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexperimentDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CexperimentDlg::OnClickedButtonNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pCanvas->isLearning)
	{
		//{{
		//�������һ�����壬Ȼ�������������draw()����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pCanvas->toggleMode ();

	BOOL enable = TRUE;
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	CString s;
	p->GetWindowText(s);
	if (s == "��ʼѧϰ")
	{
		p->SetWindowText(_T("ֹͣѧϰ"));

		OnClickedButtonNext();
	}
	else
	{
		p->SetWindowText(_T("��ʼѧϰ"));

		//������һ����û��������ô�������漰��������б���ɾ��
		if (!lastDone) list.pop_back();

		//{{ ����������ӱ����Ĵ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		result = _T("�𰸴���");
		enable = FALSE;
	}
	UpdateData(FALSE);

	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	p->EnableWindow (enable);
}


QUADPTR CexperimentDlg::createAquad(void)
{
	//{{
	//���������������ĳ������Ĵ���
	//��������ķ�ʽ����ƽ���ı��Ρ����Ρ����Ρ����κ�������֮һ
	//�������������Ҳ��������ɵ�
	//����һ���������ָ�뱣�浽�б���
	//�����ķ���ֵ�����ɵ������ָ��
	
	srand(unsigned(time(NULL)));
		//Ϊͼ������ռ�
		//ע�������� Parallelogram pa; ����������������ᱻ����
		qPtr q ;
		Node * nodePtr = new Node;
		Parallelogram * paPtr = new Parallelogram;
		Rect * rPtr = new Rect;
		Diamond * dPtr = new Diamond;
		Square * sPtr = new Square;
		Trapezoid * tPtr = new Trapezoid;

		//����ѭ���иı䲢�����ı���
		int random = 1+rand()%5;
		double width = 1+rand()%10;
		double height = 1+rand()%10;
		
			//ѡ���ı���
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
	// TODO: �ڴ����ר�ô����/����û���

	//if (wParam == 1 || wParam == 2) return FALSE;

	return CDialogEx::OnCommand(wParam, lParam);
}
