#pragma once
#include "afxwin.h"
#define POINT (1000)
#define SIZE (20)
#define ALLSIZE (180)
#include <iostream>
using namespace std;
// CTipDlg 对话框
/*
CPoint R0_A[SIZE];
CPoint R0_B[SIZE];
CPoint R1_A[SIZE];
CPoint R1_B[SIZE];
CPoint R2_A[SIZE];
CPoint R2_B[SIZE];
CPoint R3_A[SIZE];
CPoint R3_B[SIZE];
CPoint C_A[SIZE];
CPoint C_B[SIZE];
CPoint D_A[SIZE];
CPoint D_B[SIZE];
CPoint SP_A[SIZE];
CPoint PC_A[SIZE];
CPoint PSW_B[SIZE];
CPoint MDR_B[SIZE];
CPoint Y_D[SIZE];
CPoint Y_C[SIZE];
CPoint Y_R3[SIZE];
CPoint Y_R2[SIZE];
CPoint Y_R1[SIZE];
CPoint Y_R0[SIZE];
CPoint Y_PSW[SIZE];
CPoint Y_SP[SIZE];
CPoint Y_PC[SIZE];
CPoint Y_MDR[SIZE];
CPoint Y_MAR[SIZE];
CPoint M_IR[SIZE];
CPoint M_MDR[SIZE];
CPoint M_MAR[SIZE];
CPoint MDR_M[SIZE];
CPoint MAR_M[SIZE];
CPoint A_Y[SIZE];
CPoint B_Y[SIZE];
*/

class mOrder {
public:
	int x;
	int y;
	CString str;
}; 
class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipDlg();

// 对话框数据
	enum { IDD = IDD_TIP_DIALOG };

	//寻址方式及寄存器类
class address_register {
public:
	CString AM;
	CString R;
	address_register () {}
	~address_register () {}
};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CStatic m_picDraw;
	void DrawWave(CDC *pDC, CRect &rectPicture);  
	//输出命令
	void OutputOrders(int addressing_st[2],int addressing_dt[2],int opcode);

	//寻址方式及寄存器ar_key转换
	CString * transAddressandRegister (int ar_key[2],address_register & ar,CString *& function,int op_type, bool is_source);

	//操作op_key转换
	CString transOperator (int po_key);
	
	//指令处理
	void handleArray (CString * s);

	//语句输出
	void outPutString (CString orderString);
	
	void outMOrderArray (mOrder * order);
	void editorOutMOrder (mOrder order);
	void outMorderByStep ();
	void outPutSteps ();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	
	
	CPoint* et();//et周期的操作指令集
	CPoint* ft();//ft周期的操作指令集
	CPoint* dp_st_indirect();//双操作数的st周期的间址
	CPoint* dp_st_minus();//双操作数的st周期的自减型寻址
	CPoint* dp_st_plus();//双操作数的st周期的自增型寻址
	CPoint* dp_st_unstable();//双操作数的st周期的变址寻址
	CPoint* dp_dt_indirect();//双操作数的dt周期的间址
	CPoint* dp_dt_minus();//双操作数的dt周期的自减型寻址
	CPoint* dp_dt_plus();//双操作数的dt周期的自增型寻址
	CPoint* dp_dt_unstable();//双操作数的dt周期的变址寻址
	CPoint* mov_dt_indirect();//mov的dt周期的间址
	CPoint* mov_dt_minus();//mov的dt周期的自减型寻址
	CPoint* mov_dt_plus();//mov的dt周期的自增型寻址
	CPoint* mov_dt_unstable();//双mov的dt周期的变址寻址
	CPoint* jsr_st_indirect();//jsr的st周期的间址
	CPoint* jsr_st_plus();//jsr的st周期的自增型寻址
	CPoint R0_A[SIZE];
	CPoint R0_B[SIZE];
	CPoint R1_A[SIZE];
	CPoint R1_B[SIZE];
	CPoint R2_A[SIZE];
	CPoint R2_B[SIZE];
	CPoint R3_A[SIZE];
	CPoint R3_B[SIZE];
	CPoint C_A[SIZE];
	CPoint C_B[SIZE];
	CPoint D_A[SIZE];
	CPoint D_B[SIZE];
	CPoint SP_A[SIZE];
	CPoint PC_A[SIZE];
	CPoint PSW_B[SIZE];
	CPoint MDR_B[SIZE];
	CPoint Y_D[SIZE];
	CPoint Y_C[SIZE];
	CPoint Y_R3[SIZE];
	CPoint Y_R2[SIZE];
	CPoint Y_R1[SIZE];
	CPoint Y_R0[SIZE];
	CPoint Y_PSW[SIZE];
	CPoint Y_SP[SIZE];
	CPoint Y_PC[SIZE];
	CPoint Y_MDR[SIZE];
	CPoint Y_MAR[SIZE];
	CPoint M_IR[SIZE];
	CPoint M_MDR[SIZE];
	CPoint M_MAR[SIZE];
	CPoint MDR_M[SIZE];
	CPoint MAR_M[SIZE];
	CPoint A_Y[SIZE];
	CPoint B_Y[SIZE];
	float point_width;
	float point_height;
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
};
