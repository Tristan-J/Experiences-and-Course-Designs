#pragma once
#include "afxwin.h"
#define POINT (1000)
#define SIZE (20)
#define ALLSIZE (180)
#include <iostream>
using namespace std;
// CTipDlg �Ի���
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
	CTipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipDlg();

// �Ի�������
	enum { IDD = IDD_TIP_DIALOG };

	//Ѱַ��ʽ���Ĵ�����
class address_register {
public:
	CString AM;
	CString R;
	address_register () {}
	~address_register () {}
};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CStatic m_picDraw;
	void DrawWave(CDC *pDC, CRect &rectPicture);  
	//�������
	void OutputOrders(int addressing_st[2],int addressing_dt[2],int opcode);

	//Ѱַ��ʽ���Ĵ���ar_keyת��
	CString * transAddressandRegister (int ar_key[2],address_register & ar,CString *& function,int op_type, bool is_source);

	//����op_keyת��
	CString transOperator (int po_key);
	
	//ָ���
	void handleArray (CString * s);

	//������
	void outPutString (CString orderString);
	
	void outMOrderArray (mOrder * order);
	void editorOutMOrder (mOrder order);
	void outMorderByStep ();
	void outPutSteps ();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	
	
	CPoint* et();//et���ڵĲ���ָ�
	CPoint* ft();//ft���ڵĲ���ָ�
	CPoint* dp_st_indirect();//˫��������st���ڵļ�ַ
	CPoint* dp_st_minus();//˫��������st���ڵ��Լ���Ѱַ
	CPoint* dp_st_plus();//˫��������st���ڵ�������Ѱַ
	CPoint* dp_st_unstable();//˫��������st���ڵı�ַѰַ
	CPoint* dp_dt_indirect();//˫��������dt���ڵļ�ַ
	CPoint* dp_dt_minus();//˫��������dt���ڵ��Լ���Ѱַ
	CPoint* dp_dt_plus();//˫��������dt���ڵ�������Ѱַ
	CPoint* dp_dt_unstable();//˫��������dt���ڵı�ַѰַ
	CPoint* mov_dt_indirect();//mov��dt���ڵļ�ַ
	CPoint* mov_dt_minus();//mov��dt���ڵ��Լ���Ѱַ
	CPoint* mov_dt_plus();//mov��dt���ڵ�������Ѱַ
	CPoint* mov_dt_unstable();//˫mov��dt���ڵı�ַѰַ
	CPoint* jsr_st_indirect();//jsr��st���ڵļ�ַ
	CPoint* jsr_st_plus();//jsr��st���ڵ�������Ѱַ
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