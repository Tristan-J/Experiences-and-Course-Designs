
// ����γ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����γ����.h"
#include "����γ����Dlg.h"
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


//����Ԫ�ص��±��Ӧ�ŵ�ַ�ı��
CString AddressNumArray[6][6] = {
	{_T("R0"),_T("R1"),_T("R2"),_T("R3"),_T("SP"),_T("PC")},//00~05
	{_T("(R0)"),_T("(R1)"),_T("(R2)"),_T("(R3)")},//10~13
	{_T("-(R0)"),_T("-(R1)"),_T("-(R2)"),_T("-(R3)"),_T("-(SP)")},//20~24
	{_T("(R0)+"),_T("(R1)+"),_T("(R2)+"),_T("(R3)+"),_T("(SP)+"),_T("(PC)+")},//30~35
	{_T("X(R0)"),_T("X(R1)"),_T("X(R2)"),_T("X(R3)"),_T("X(PC)")},//40~44
	{_T("NULL")}//50 ��ʹ��Ϊ��
};

//ÿ������������ʹ�õ�Ѱַ��ʽ���Ĵ�����,��һλΪ��ַ����
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


// C����γ����Dlg �Ի���



C����γ����Dlg::C����γ����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C����γ����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����γ����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
}

BEGIN_MESSAGE_MAP(C����γ����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C����γ����Dlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &C����γ����Dlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &C����γ����Dlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &C����γ����Dlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// C����γ����Dlg ��Ϣ�������

BOOL C����γ����Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C����γ����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C����γ����Dlg::OnPaint()
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
HCURSOR C����γ����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C����γ����Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   
  
    CTipDlg tipDlg;           // ����Ի�����CTipDlg��ʵ��   
    nRes = tipDlg.DoModal();  // �����Ի���
	CDialogEx::OnOK();
}


void C����γ����Dlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	opcode = m_combo1.GetCurSel();//�õ�������
	int opcode_MDT[28];

	for (int i = 0; i<28; i++){//�õ�����������Ӧ�ĵ�ַ���ϵ
		opcode_MDT[i] = MatchDecisionTable[opcode][i];
	}

	m_combo2.ResetContent();//��տؼ�����
	m_combo3.ResetContent();

	int n = opcode_MDT[0];//��ַ�����

	int r,c;
	for(int i = 1; i <= n; i++){
		r = opcode_MDT[i] / 10;//����
		c = opcode_MDT[i] % 10;//����

		if (opcode < 06 || i != n){//opcode>=06&&i==n�ķ�
			m_combo2.AddString(AddressNumArray[r][c]);//����ַ������ؼ�
		}

		if (opcode < 06){//˫��ַ
			m_combo3.AddString(AddressNumArray[r][c]);
		}
		if (opcode >= 06 && i == n){//�Ե���ַ�����⴦��
			m_combo3.AddString(AddressNumArray[5][0]);
		}
	}

}


void C����γ����Dlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString addressing_str1;
	int n1 = m_combo2.GetCurSel();

	m_combo2.GetLBText(n1, addressing_str1);//���������õ���ַ���ַ���

	_judge(addressing_dt, addressing_str1);//�õ����ڵ�ַ���һά��Ԫ��������
}


void C����γ����Dlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString addressing_str2;
	int n2 = m_combo3.GetCurSel();

	m_combo3.GetLBText(n2, addressing_str2);//���������õ���ַ���ַ���

	_judge(addressing_st, addressing_str2);	//�õ����ڵ�ַ���һά��Ԫ��������
}
