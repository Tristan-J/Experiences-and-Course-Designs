						// TipDlg.cpp : 实现文件
						//

						#include "stdafx.h"
						#include "计组课程设计.h"
						#include "TipDlg.h"
						#include "afxdialogex.h"
						extern int addressing_st[2];//////**********************************************
						extern int addressing_dt[2];//////**********************************************
						extern int opcode;
						int code_size=0;
						int ft_code_size=0;
						int dt_code_size=-1;
						int st_code_size=-1;
						int et_code_size=-1;
						int ft_size=0;
						int dt_size=0;
						int st_size=0;
						int et_size=0;
						int edit=1;
						int xxx=0;//////////////////////////////////////
						//public
							CString Ri = _T("Ri");
							CString Rj = _T("Rj");
							CString OP = _T("OP");

							//微指令计数器
							int m_order_step_counter = 0;
							int m_order_step_counter_copy = 0;

							//操作数类型
							int op_type = 0 ;//0 for false ;1 for double;2 for mov,3 for single,4 for jmp and rst,5 for jrs

							//步骤数
							int step = 0;//0 for fetch , 1 for source, 2 for destination , 3 for execution

							//周期内的步骤数
							int programStep = 0;//0 for step1...

							//取指 源地址 目的地址 操作
							CString *fetch , *source , *destination , *execution ;
							CString *function;
							//为空时的赋值
							CString empty[1] = {_T("||")};
							//取指 源地址 目的地址 操作 （微命令）
							mOrder *m_fetch , *m_source , *m_destination , *m_execution ;

						//执行命令集合
						//ADD,SUB,AND,OR,EOR,
						//dpPro
							//双操作数操作（不包括mov）
							//取指周期
							CString d_f_universal[4] = {_T("M-->IR"),_T("|"),_T("PC+1-->PC"),_T("||")};

							//源地址获取
							CString d_s_direct[2] = {_T("寄存器寻址"),_T("||")};

							CString d_s_indirect[5] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("||")};

							CString d_s_minus_indirect[6] = {Ri,_T("-1-->MAR,"),Ri,_T("|"),_T("M-->MDR-->C"),_T("||")};

							CString d_s_plus_indirect[9] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("|"),Ri,_T("+1-->"),Ri,_T("||")};

							CString d_s_unstable_indirect[12] = {_T("PC-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("|"),_T("PC+1-->PC"),_T("|"),_T("C+"),Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("||")};

							CString d_s_double_indirect[10] = {Ri,_T("+MAR"),_T("|"),Ri,_T("+1-->"),Ri,_T("|"),_T("M-->MDR-->MAR"),_T("||")};


							//目的地址获取
							CString d_d_direct[2] = {_T("寄存器寻址"),_T("||")};

							CString d_d_indirect[5] = {Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("||")};

							CString d_d_minus_indirect[6] = {Rj,_T("-1-->MAR,"),Rj,_T("|"),_T("M-->MDR-->D"),_T("||")};

							CString d_d_plus_indirect[9] = {Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("|"),Rj,_T("+1-->"),Rj,_T("||")};

							CString d_d_unstable_indirect[12] = {_T("PC-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("|"),_T("PC+1-->PC"),_T("|"),_T("D+"),Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("||")};

							CString d_d_double_indirect[9] = {Rj,_T("+MAR"),_T("|"),Rj,_T("+1-->"),Rj,_T("|"),_T("M-->MDR-->MAR"),_T("||")};

							//执行周期
							CString d_e_dd[8] = {Ri,OP,Rj,_T("-->"),Rj,_T("|"),_T("PC-->MAR"),_T("||")};

							CString d_e_di[8] = {Ri,OP,_T("D-->MDR-->M"),_T("|"),_T("PC-->MAR"),_T("||")};

							CString d_e_id[8] = {_T("C"),OP,Rj,_T("-->"),Rj,_T("|"),_T("PC-->MAR"),_T("||")};

							CString d_e_ii[8] = {_T("C"),OP,_T("D-->MDR-->M"),_T("|"),_T("PC-->MAR"),_T("||")};

						//MOV
						//MOV
							//取指周期
							CString mov_f_universal[4] = {_T("M-->IR"),_T("|"),_T("PC+1-->PC"),_T("||")};

							//源地址获取同其他双操作数操作

							//目的地址获取
							CString mov_d_direct[2] = {_T("寄存器寻址"),_T("||")};

							CString mov_d_indirect[3] = {Rj,_T("-->MAR"),_T("||")};

							CString mov_d_minus_indirect[4] = {Rj,_T("-1-->MAR,"),Rj,_T("||")};

							CString mov_d_plus_indirect[7] = {Rj,_T("-->MAR"),_T("|"),Rj,_T("+1-->"),Rj,_T("||")};

							CString mov_d_unstable_indirect[10] = {_T("PC-->MAR"),_T("|"),_T("PC+1-->PC"),_T("|"),_T("M-->MDR-->D"),_T("|"),_T("D+"),Rj,_T("-->MAR"),_T("||")};
							
							CString mov_d_double_indirect[9] = {Rj,_T("+MAR"),_T("|"),Rj,_T("+1-->"),Rj,_T("|"),_T("M-->MDR-->MAR"),_T("||")};

							//执行周期
							CString mov_e_dd[8] = {Ri,OP,Rj,_T("-->"),Rj,_T("|"),_T("PC-->MAR"),_T("||")};

							CString mov_e_di[8] = {Ri,OP,_T("D-->MDR-->M"),_T("|"),_T("PC-->MAR"),_T("||")};

							CString mov_e_id[8] = {_T("C"),OP,Rj,_T("-->"),Rj,_T("|"),_T("PC-->MAR"),_T("||")};

							CString mov_e_ii[6] = {_T("C"),OP,_T("D-->MDR-->M"),_T("|"),_T("PC-->MAR"),_T("||")};

						//COM,NEG,ING,DEC,SL,SR
						// spPro

							//取指周期
							CString s_f_universal[4] = {_T("M-->IR"),_T("|"),_T("PC+1-->PC"),_T("||")};

							//目的地址获取
							CString s_d_direct[2] = {_T("寄存器寻址"),_T("||")};

							CString s_d_indirect[5] = {Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("||")};

							CString s_d_minus_indirect[6] = {Rj,_T("-1-->MAR,"),Rj,_T("|"),_T("M-->MDR-->D"),_T("||")};

							CString s_d_plus_indirect[9] = {Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("|"),Rj,_T("+1-->"),Rj,_T("||")};

							CString s_d_unstable_indirect[12] = {_T("PC-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("|"),_T("PC+1-->PC"),_T("|"),_T("D+"),Rj,_T("-->MAR"),_T("|"),_T("M-->MDR-->D"),_T("||")};

							//执行周期
							CString s_e_d[7] = {OP,Rj,_T("-->"),Rj,_T("|"),_T("PC-->MAR"),_T("||")};

							CString s_e_i[7] = {OP,_T("D-->MDR-->M"),_T("|"),_T("PC-->MAR"),_T("||")};

						//JMP,RST
						//jmpPro 

							//取指周期
							CString jmp_f_universal[4] = {_T("M-->IR"),_T("|"),_T("PC+1-->PC"),_T("||")};

							//执行周期
							CString jmp_e_d[3] = {Ri,_T("-->PC,MAR"),_T("||")};

							CString jmp_e_i[5] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->PC,MAR"),_T("||")};

							CString jmp_e_pi[9] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->PC,MAR"),_T("|"),Ri,_T("+1-->"),Ri,_T("||")};

							CString jmp_e_ui[9] = {_T("PC-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("|"),_T("C+"),Ri,_T("-->MAR"),_T("-->PC"),_T("||")};

						//JSR
						//jsrPro
							//取指周期
							CString jsr_f_universal[4] = {_T("M-->IR"),_T("|"),_T("PC+1-->PC"),_T("||")};
							//源地址获取
							CString jsr_s_direct[2] = {_T("寄存器寻址"),_T("||")};

							CString jsr_s_indirect[5] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("||")};

							CString jsr_s_plus_indirect[9] = {Ri,_T("-->MAR"),_T("|"),_T("M-->MDR-->C"),_T("|"),Ri,_T("+1-->"),Ri,_T("||")};

							//执行周期
							CString jsr_e_d[9] = {_T("SP-1-->SP,MAR"),_T("|"),_T("PC-->MDR-->M"),_T("|"),Ri,_T("-->PC,MAR"),_T("||")};

							CString jsr_e_i[8] = {_T("SP-1-->SP,MAR"),_T("|"),_T("PC-->MDR-->M"),_T("|"),_T("C-->PC,MAR"),_T("||")};

						//微命令struct赋值
							mOrder OVER = {0,0,_T("\n\n")};
							mOrder NEXT = {0,0,_T(" ")};
							mOrder PRE = {0,0,_T("               ")};
							mOrder EMAR = {75,73,_T("EMAR")} , R = {95,23,_T("R")} , SIR = {95,28,_T("SIR")} ;
							mOrder PC2A = {75,43,_T("PC-->A")} , Aadd1 = {40,75,_T("A+1")} , DM = {50,38,_T("DM")} , CPPC = {50,15,_T("CPPC")} , O12ST = {5,1,_T("1-->ST")} ;
							mOrder CPFT = {10,1,_T("CPFT(P')")} , CPST = {15,1,_T("CPST(P')")} , CPDT = {20,1,_T("CPDT(P')")} , CPET = {25,1,_T("CPET(P')")} , CPTC = {30,1,_T("CPTC(P')")} ;
							mOrder outA = {40,78,_T("输出A")} , CPMAR = {50,15,_T("CPMAR")} , Tadd1 = {5,1,_T("T+1")} , CPT = {10,1,_T("CPT(P')")} , SMDR = {95,28,_T("SMDR")} ;
							mOrder MDR2B = {75,58,_T("MDR-->B")} , outB = {60,78,_T("输出B")} , CPC = {50,15,_T("CPC")} , Ri2A = {15,12,_T("R0-->A")} , C2B = {15,73,_T("C-->B")} ;
							mOrder AaddB = {44,55,_T("A+B")} ,  O12DT = {5,1,_T("1-->DT")} , Rj2A = {15,28,_T("R1-->A")} , CPD = {50,15,_T("CPD")} ;
							mOrder O12ET = {5,1,_T("1-->ET")} , W = {95,23,_T("W")} , O12FT = {5,1,_T("1-->FT")} , CPRj = {50,15,_T("CPR1")} , CPMDR = {75,58,_T("CPMDR")};
						//MOV @(R1)+ x(R0) 微命令集合
							mOrder m_0[4] = {EMAR , R, SIR , OVER};
							mOrder m_1[11] = {PC2A , Aadd1 , DM , CPPC , O12ST , CPFT , CPST , CPDT , CPET , CPT , OVER};
							mOrder m_2[7] = {PC2A , outA , DM , CPMAR , Tadd1 , CPT , OVER};
							mOrder m_3[10] = {EMAR , R , SMDR , MDR2B , outB , DM , CPC , Tadd1 , CPT , OVER};
							mOrder m_4[7] = {PC2A , Aadd1 , DM , CPPC , Tadd1 , CPT , OVER};
							mOrder m_5[8] = {Ri2A , C2B , AaddB , DM , CPMAR , Tadd1 , CPT , OVER};
							mOrder m_6[14] = {EMAR , R , SMDR , MDR2B , outB , DM , CPC , O12DT , CPFT , CPST , CPDT , CPET , CPT, OVER};
							mOrder m_7[7] = {Rj2A , outA , DM , CPMAR , Tadd1 , CPT, OVER};
							mOrder m_8[7] = {Rj2A , Aadd1 , DM , CPRj , Tadd1 , CPT , OVER};
							mOrder m_9[13] = {EMAR , R , MDR2B , outB , DM , CPMAR , O12ET , CPFT , CPST , CPDT , CPET , CPT , OVER};
							mOrder m_10[7] = {C2B , outB , DM , CPMDR , Tadd1 , CPT , OVER};
							mOrder m_11[5] = {EMAR , W , Tadd1 , CPT , OVER};
							mOrder m_12[11] = {PC2A , outA , DM , CPMAR ,O12FT , CPFT , CPST , CPDT , CPET , CPT , OVER};
							mOrder * mOrders[13] = {m_0,m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9,m_10,m_11,m_12};

						// CTipDlg 对话框

						IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

						CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
							: CDialogEx(CTipDlg::IDD, pParent)
						{

						}

						CTipDlg::~CTipDlg()
						{
						}

						void CTipDlg::DoDataExchange(CDataExchange* pDX)
						{
							CDialogEx::DoDataExchange(pDX);
							DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
						}


						BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
							ON_BN_CLICKED(IDOK, &CTipDlg::OnBnClickedOk)
							ON_WM_TIMER()
							ON_WM_PAINT()
							ON_EN_CHANGE(IDC_EDIT2, &CTipDlg::OnEnChangeEdit2)
							ON_EN_CHANGE(IDC_EDIT1, &CTipDlg::OnEnChangeEdit1)
						END_MESSAGE_MAP()


						// CTipDlg 消息处理程序


						void CTipDlg::OnBnClickedOk()
						{
							// TODO: 在此添加控件通知处理程序代码
							CDialogEx::OnOK();
						}


						BOOL CTipDlg::OnInitDialog()
						{
							CDialogEx::OnInitDialog();

							// TODO:  在此添加额外的初始化
							 // 启动定时器，ID为1，定时时间为200ms   
						    SetTimer(1, 100, NULL); 
							
							int a[2] ;
							memcpy(a,addressing_st,2*sizeof(int));

						    int b[2] ;
							memcpy(b,addressing_dt,2*sizeof(int));
						    int c = opcode;

						    OutputOrders(a,b,c);
							return TRUE;  // return TRUE unless you set the focus to a control
							// 异常: OCX 属性页应返回 FALSE
						}


						void CTipDlg::OnTimer(UINT_PTR nIDEvent)
						{
							// TODO: 在此添加消息处理程序代码和/或调用默认值
							CRect rectPicture;
							m_picDraw.GetClientRect(&rectPicture);   
							CDC *pDC=m_picDraw.GetDC();
							point_width=(float)rectPicture.Width() / (POINT - 1);
							point_height=(float)rectPicture.Height() / (POINT- 1);
							//Shifter
							    CPen newPen;       // 用于创建新画笔   
						    CPen *pOldPen;     // 用于存放旧画笔   
						    CBrush newBrush;   // 用于创建新画刷   
						    CBrush *pOldBrush; // 用于存放旧画刷   
							//CPoint a[SIZE]={(2,1)}
						    // 计算fDeltaX和fDeltaY   
						    //fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);   
						    //fDeltaY = (float)rectPicture.Height() / 80;   
							
						    // 创建黑色新画刷   
						    //newBrush.CreateSolidBrush(RGB(100,1,1));   
						    // 选择新画刷，并将旧画刷的指针保存到pOldBrush   
						    //pOldBrush = pDC->SelectObject(&newBrush);   
						    // 以黑色画刷为绘图控件填充黑色，形成黑色背景   
						   // pDC->Rectangle(rectPicture);   
						    // 恢复旧画刷   
						    //pDC->SelectObject(pOldBrush);   
						    // 删除新画刷   
						    newBrush.DeleteObject();   
							
						    // 创建实心画笔，粗度为1，颜色为绿色   
						    newPen.CreatePen(PS_SOLID, 4, RGB(0,255,0));   
						// 选择新画笔，并将旧画笔的指针保存到pOldPen   
						    pOldPen = pDC->SelectObject(&newPen);  
							CPoint R0_A1[SIZE]={CPoint(200*point_width,225*point_height),CPoint(250*point_width,225*point_height),CPoint(250*point_width,300*point_height),CPoint(250*point_width,375*point_height),CPoint(250*point_width,450*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,600*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,750*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint R0_B1[SIZE]={CPoint(200*point_width,225*point_height),CPoint(250*point_width,225*point_height),CPoint(250*point_width,300*point_height),CPoint(250*point_width,375*point_height),CPoint(250*point_width,450*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,600*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,750*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(400*point_width,725*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height)};
							CPoint R1_A1[SIZE]={CPoint(200*point_width,375*point_height),CPoint(250*point_width,375*point_height),CPoint(250*point_width,450*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,600*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,750*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint R1_B1[SIZE]={CPoint(200*point_width,375*point_height),CPoint(250*point_width,375*point_height),CPoint(250*point_width,450*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,600*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,750*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint R2_A1[SIZE]={CPoint(200*point_width,525*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,575*point_height),CPoint(250*point_width,625*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,725*point_height),CPoint(250*point_width,775*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,875*point_height),CPoint(250*point_width,925*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint R2_B1[SIZE]={CPoint(200*point_width,525*point_height),CPoint(250*point_width,525*point_height),CPoint(250*point_width,575*point_height),CPoint(250*point_width,625*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,725*point_height),CPoint(250*point_width,775*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,875*point_height),CPoint(250*point_width,925*point_height),CPoint(250*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint R3_A1[SIZE]={CPoint(200*point_width,675*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,705*point_height),CPoint(250*point_width,735*point_height),CPoint(250*point_width,765*point_height),CPoint(250*point_width,795*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,855*point_height),CPoint(250*point_width,885*point_height),CPoint(250*point_width,915*point_height),CPoint(250*point_width,945*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint R3_B1[SIZE]={CPoint(200*point_width,675*point_height),CPoint(250*point_width,675*point_height),CPoint(250*point_width,725*point_height),CPoint(250*point_width,775*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,875*point_height),CPoint(250*point_width,925*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(400*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(500*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint C_A1[SIZE]={CPoint(200*point_width,825*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,850*point_height),CPoint(250*point_width,875*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,925*point_height),CPoint(250*point_width,950*point_height),CPoint(250*point_width,975*point_height),CPoint(275*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(325*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint C_B1[SIZE]={CPoint(200*point_width,825*point_height),CPoint(250*point_width,825*point_height),CPoint(250*point_width,850*point_height),CPoint(250*point_width,875*point_height),CPoint(250*point_width,900*point_height),CPoint(250*point_width,925*point_height),CPoint(250*point_width,950*point_height),CPoint(250*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(400*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(500*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint D_A1[SIZE]={CPoint(200*point_width,975*point_height),CPoint(250*point_width,975*point_height),CPoint(275*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(325*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,950*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,900*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,850*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,800*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,750*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint D_B1[SIZE]={CPoint(200*point_width,975*point_height),CPoint(250*point_width,975*point_height),CPoint(275*point_width,975*point_height),CPoint(300*point_width,975*point_height),CPoint(325*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(400*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(500*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,900*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,850*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,800*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,750*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint SP_A1[SIZE]={CPoint(700*point_width,375*point_height),CPoint(650*point_width,375*point_height),CPoint(650*point_width,450*point_height),CPoint(650*point_width,525*point_height),CPoint(650*point_width,600*point_height),CPoint(650*point_width,675*point_height),CPoint(650*point_width,750*point_height),CPoint(650*point_width,825*point_height),CPoint(650*point_width,900*point_height),CPoint(650*point_width,975*point_height),CPoint(600*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(500*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,825*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height)};
							CPoint PC_A1[SIZE]={CPoint(700*point_width,525*point_height),CPoint(650*point_width,525*point_height),CPoint(650*point_width,575*point_height),CPoint(650*point_width,625*point_height),CPoint(650*point_width,675*point_height),CPoint(650*point_width,725*point_height),CPoint(650*point_width,775*point_height),CPoint(650*point_width,825*point_height),CPoint(650*point_width,875*point_height),CPoint(650*point_width,925*point_height),CPoint(650*point_width,975*point_height),CPoint(600*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(450*point_width,975*point_height),CPoint(350*point_width,975*point_height),CPoint(350*point_width,925*point_height),CPoint(350*point_width,875*point_height),CPoint(350*point_width,775*point_height),CPoint(350*point_width,725*point_height),CPoint(350*point_width,725*point_height)};
							CPoint PSW_B1[SIZE]={CPoint(700*point_width,625*point_height),CPoint(650*point_width,225*point_height),CPoint(650*point_width,300*point_height),CPoint(650*point_width,375*point_height),CPoint(650*point_width,450*point_height),CPoint(650*point_width,525*point_height),CPoint(650*point_width,600*point_height),CPoint(650*point_width,675*point_height),CPoint(650*point_width,750*point_height),CPoint(650*point_width,825*point_height),CPoint(650*point_width,900*point_height),CPoint(650*point_width,975*point_height),CPoint(600*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint MDR_B1[SIZE]={CPoint(700*point_width,660*point_height),CPoint(650*point_width,660*point_height),CPoint(650*point_width,705*point_height),CPoint(650*point_width,735*point_height),CPoint(650*point_width,765*point_height),CPoint(650*point_width,795*point_height),CPoint(650*point_width,825*point_height),CPoint(650*point_width,855*point_height),CPoint(650*point_width,885*point_height),CPoint(650*point_width,915*point_height),CPoint(650*point_width,945*point_height),CPoint(650*point_width,975*point_height),CPoint(600*point_width,975*point_height),CPoint(550*point_width,975*point_height),CPoint(550*point_width,925*point_height),CPoint(550*point_width,875*point_height),CPoint(550*point_width,825*point_height),CPoint(550*point_width,775*point_height),CPoint(550*point_width,725*point_height),CPoint(550*point_width,725*point_height)};
							CPoint Y_D1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(350*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(150*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,150*point_height),CPoint(50*point_width,225*point_height),CPoint(50*point_width,300*point_height),CPoint(50*point_width,375*point_height),CPoint(50*point_width,450*point_height),CPoint(50*point_width,525*point_height),CPoint(50*point_width,600*point_height),CPoint(50*point_width,675*point_height),CPoint(50*point_width,750*point_height),CPoint(50*point_width,825*point_height),CPoint(50*point_width,900*point_height),CPoint(50*point_width,975*point_height),CPoint(100*point_width,975*point_height)};
							CPoint Y_C1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(350*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(150*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,150*point_height),CPoint(50*point_width,225*point_height),CPoint(50*point_width,300*point_height),CPoint(50*point_width,375*point_height),CPoint(50*point_width,450*point_height),CPoint(50*point_width,525*point_height),CPoint(50*point_width,600*point_height),CPoint(50*point_width,675*point_height),CPoint(50*point_width,750*point_height),CPoint(50*point_width,825*point_height),CPoint(100*point_width,825*point_height)};
							CPoint Y_R31[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(400*point_width,50*point_height),CPoint(350*point_width,50*point_height),CPoint(300*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(200*point_width,50*point_height),CPoint(150*point_width,50*point_height),CPoint(100*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,150*point_height),CPoint(50*point_width,225*point_height),CPoint(50*point_width,300*point_height),CPoint(50*point_width,375*point_height),CPoint(50*point_width,450*point_height),CPoint(50*point_width,525*point_height),CPoint(50*point_width,600*point_height),CPoint(50*point_width,675*point_height),CPoint(100*point_width,675*point_height)};
							CPoint Y_R21[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(400*point_width,50*point_height),CPoint(350*point_width,50*point_height),CPoint(300*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(200*point_width,50*point_height),CPoint(150*point_width,50*point_height),CPoint(100*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,150*point_height),CPoint(50*point_width,225*point_height),CPoint(50*point_width,300*point_height),CPoint(50*point_width,375*point_height),CPoint(50*point_width,450*point_height),CPoint(50*point_width,525*point_height),CPoint(100*point_width,525*point_height)};
							CPoint Y_R11[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,175*point_height),CPoint(450*point_width,100*point_height),CPoint(450*point_width,50*point_height),CPoint(400*point_width,50*point_height),CPoint(350*point_width,50*point_height),CPoint(300*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(200*point_width,50*point_height),CPoint(150*point_width,50*point_height),CPoint(100*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,100*point_height),CPoint(50*point_width,175*point_height),CPoint(50*point_width,225*point_height),CPoint(50*point_width,300*point_height),CPoint(50*point_width,375*point_height),CPoint(100*point_width,375*point_height)};
							CPoint Y_R01[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,175*point_height),CPoint(450*point_width,100*point_height),CPoint(450*point_width,50*point_height),CPoint(410*point_width,50*point_height),CPoint(370*point_width,50*point_height),CPoint(330*point_width,50*point_height),CPoint(290*point_width,50*point_height),CPoint(250*point_width,50*point_height),CPoint(210*point_width,50*point_height),CPoint(170*point_width,50*point_height),CPoint(130*point_width,50*point_height),CPoint(90*point_width,50*point_height),CPoint(50*point_width,50*point_height),CPoint(50*point_width,100*point_height),CPoint(50*point_width,175*point_height),CPoint(50*point_width,225*point_height),CPoint(100*point_width,225*point_height)};
							CPoint Y_PSW1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,175*point_height),CPoint(450*point_width,100*point_height),CPoint(450*point_width,50*point_height),CPoint(490*point_width,50*point_height),CPoint(530*point_width,50*point_height),CPoint(570*point_width,50*point_height),CPoint(610*point_width,50*point_height),CPoint(650*point_width,50*point_height),CPoint(690*point_width,50*point_height),CPoint(730*point_width,50*point_height),CPoint(770*point_width,50*point_height),CPoint(810*point_width,50*point_height),CPoint(850*point_width,50*point_height),CPoint(850*point_width,100*point_height),CPoint(850*point_width,175*point_height),CPoint(850*point_width,225*point_height),CPoint(80*point_width,225*point_height)};
							CPoint Y_SP1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,175*point_height),CPoint(450*point_width,100*point_height),CPoint(450*point_width,50*point_height),CPoint(500*point_width,50*point_height),CPoint(550*point_width,50*point_height),CPoint(600*point_width,50*point_height),CPoint(650*point_width,50*point_height),CPoint(700*point_width,50*point_height),CPoint(750*point_width,50*point_height),CPoint(800*point_width,50*point_height),CPoint(850*point_width,50*point_height),CPoint(850*point_width,100*point_height),CPoint(850*point_width,175*point_height),CPoint(850*point_width,225*point_height),CPoint(850*point_width,300*point_height),CPoint(850*point_width,375*point_height),CPoint(800*point_width,375*point_height)};
							CPoint Y_PC1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(500*point_width,50*point_height),CPoint(550*point_width,50*point_height),CPoint(600*point_width,50*point_height),CPoint(650*point_width,50*point_height),CPoint(700*point_width,50*point_height),CPoint(750*point_width,50*point_height),CPoint(800*point_width,50*point_height),CPoint(850*point_width,50*point_height),CPoint(850*point_width,150*point_height),CPoint(850*point_width,225*point_height),CPoint(850*point_width,300*point_height),CPoint(850*point_width,375*point_height),CPoint(850*point_width,450*point_height),CPoint(850*point_width,525*point_height),CPoint(800*point_width,525*point_height)};
							CPoint Y_MDR1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(500*point_width,50*point_height),CPoint(550*point_width,50*point_height),CPoint(600*point_width,50*point_height),CPoint(650*point_width,50*point_height),CPoint(700*point_width,50*point_height),CPoint(750*point_width,50*point_height),CPoint(800*point_width,50*point_height),CPoint(850*point_width,50*point_height),CPoint(850*point_width,150*point_height),CPoint(850*point_width,225*point_height),CPoint(850*point_width,300*point_height),CPoint(850*point_width,375*point_height),CPoint(850*point_width,450*point_height),CPoint(850*point_width,525*point_height),CPoint(850*point_width,600*point_height),CPoint(850*point_width,675*point_height),CPoint(800*point_width,675*point_height)};
							CPoint Y_MAR1[SIZE]={CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,225*point_height),CPoint(450*point_width,150*point_height),CPoint(450*point_width,50*point_height),CPoint(550*point_width,50*point_height),CPoint(650*point_width,50*point_height),CPoint(750*point_width,50*point_height),CPoint(850*point_width,50*point_height),CPoint(850*point_width,150*point_height),CPoint(850*point_width,225*point_height),CPoint(850*point_width,300*point_height),CPoint(850*point_width,375*point_height),CPoint(850*point_width,450*point_height),CPoint(850*point_width,525*point_height),CPoint(850*point_width,600*point_height),CPoint(850*point_width,675*point_height),CPoint(850*point_width,750*point_height),CPoint(850*point_width,810*point_height),CPoint(800*point_width,810*point_height)};
							CPoint M_IR1[SIZE]={CPoint(950*point_width,125*point_height),CPoint(925*point_width,125*point_height),CPoint(900*point_width,125*point_height),CPoint(900*point_width,225*point_height),CPoint(900*point_width,325*point_height),CPoint(900*point_width,425*point_height),CPoint(900*point_width,525*point_height),CPoint(900*point_width,625*point_height),CPoint(900*point_width,725*point_height),CPoint(900*point_width,825*point_height),CPoint(900*point_width,938*point_height),CPoint(860*point_width,938*point_height),CPoint(830*point_width,938*point_height),CPoint(830*point_width,975*point_height),CPoint(800*point_width,975*point_height),CPoint(800*point_width,975*point_height),CPoint(800*point_width,975*point_height),CPoint(800*point_width,975*point_height),CPoint(800*point_width,975*point_height),CPoint(800*point_width,975*point_height)};
							CPoint M_MDR1[SIZE]={CPoint(950*point_width,125*point_height),CPoint(925*point_width,125*point_height),CPoint(900*point_width,125*point_height),CPoint(900*point_width,225*point_height),CPoint(900*point_width,325*point_height),CPoint(900*point_width,425*point_height),CPoint(900*point_width,525*point_height),CPoint(900*point_width,625*point_height),CPoint(900*point_width,725*point_height),CPoint(900*point_width,825*point_height),CPoint(900*point_width,938*point_height),CPoint(860*point_width,938*point_height),CPoint(830*point_width,938*point_height),CPoint(830*point_width,900*point_height),CPoint(750*point_width,900*point_height),CPoint(680*point_width,900*point_height),CPoint(680*point_width,800*point_height),CPoint(680*point_width,690*point_height),CPoint(700*point_width,690*point_height),CPoint(700*point_width,690*point_height)};
							CPoint M_MAR1[SIZE]={CPoint(950*point_width,200*point_height),CPoint(925*point_width,200*point_height),CPoint(900*point_width,200*point_height),CPoint(875*point_width,200*point_height),CPoint(875*point_width,250*point_height),CPoint(875*point_width,300*point_height),CPoint(875*point_width,350*point_height),CPoint(875*point_width,400*point_height),CPoint(875*point_width,450*point_height),CPoint(875*point_width,500*point_height),CPoint(875*point_width,550*point_height),CPoint(875*point_width,600*point_height),CPoint(875*point_width,650*point_height),CPoint(875*point_width,700*point_height),CPoint(875*point_width,750*point_height),CPoint(875*point_width,800*point_height),CPoint(875*point_width,840*point_height),CPoint(845*point_width,840*point_height),CPoint(800*point_width,840*point_height),CPoint(800*point_width,840*point_height)};
							CPoint MDR_M1[SIZE]={CPoint(700*point_width,690*point_height),CPoint(700*point_width,690*point_height),CPoint(680*point_width,690*point_height),CPoint(680*point_width,800*point_height),CPoint(680*point_width,900*point_height),CPoint(750*point_width,900*point_height),CPoint(830*point_width,900*point_height),CPoint(830*point_width,938*point_height),CPoint(860*point_width,938*point_height),CPoint(900*point_width,938*point_height),CPoint(900*point_width,825*point_height),CPoint(900*point_width,725*point_height),CPoint(900*point_width,625*point_height),CPoint(900*point_width,525*point_height),CPoint(900*point_width,425*point_height),CPoint(900*point_width,325*point_height),CPoint(900*point_width,225*point_height),CPoint(900*point_width,125*point_height),CPoint(925*point_width,125*point_height),CPoint(950*point_width,125*point_height)};
							CPoint MAR_M1[SIZE]={CPoint(800*point_width,840*point_height),CPoint(800*point_width,840*point_height),CPoint(845*point_width,840*point_height),CPoint(875*point_width,840*point_height),CPoint(875*point_width,800*point_height),CPoint(875*point_width,750*point_height),CPoint(875*point_width,700*point_height),CPoint(875*point_width,650*point_height),CPoint(875*point_width,600*point_height),CPoint(875*point_width,550*point_height),CPoint(875*point_width,500*point_height),CPoint(875*point_width,450*point_height),CPoint(875*point_width,400*point_height),CPoint(875*point_width,350*point_height),CPoint(875*point_width,300*point_height),CPoint(875*point_width,250*point_height),CPoint(875*point_width,200*point_height),CPoint(900*point_width,200*point_height),CPoint(925*point_width,200*point_height),CPoint(950*point_width,200*point_height)};
							CPoint A_Y1[SIZE]={CPoint(350*point_width,725*point_height),CPoint(1,2),CPoint(1,3),CPoint(1,4),CPoint(1,5),CPoint(350*point_width,575*point_height),CPoint(350*point_width,525*point_height),CPoint(0,8),CPoint(0,9),CPoint(0,10),CPoint(0,11),CPoint(450*point_width,375*point_height),CPoint(450*point_width,325*point_height),CPoint(0,14),CPoint(0,15),CPoint(0,16),CPoint(0,17),CPoint(0,17),CPoint(0,17),CPoint(0,17)};
							CPoint B_Y1[SIZE]={CPoint(550*point_width,725*point_height),CPoint(2,2),CPoint(2,3),CPoint(2,4),CPoint(2,5),CPoint(550*point_width,575*point_height),CPoint(550*point_width,525*point_height),CPoint(0,8),CPoint(0,9),CPoint(0,10),CPoint(0,11),CPoint(450*point_width,375*point_height),CPoint(450*point_width,325*point_height),CPoint(0,14),CPoint(0,15),CPoint(0,16),CPoint(0,17),CPoint(0,17),CPoint(0,17),CPoint(0,17)};
							memcpy(R0_A,R0_A1,20*sizeof(CPoint));
							memcpy(R1_A,R1_A1,20*sizeof(CPoint));
							memcpy(R2_A,R2_A1,20*sizeof(CPoint));
							memcpy(R3_A,R3_A1,20*sizeof(CPoint));
							memcpy(R0_B,R0_B1,20*sizeof(CPoint));
							memcpy(R1_B,R1_B1,20*sizeof(CPoint));
							memcpy(R2_B,R2_B1,20*sizeof(CPoint));
							memcpy(R3_B,R3_B1,20*sizeof(CPoint));
							memcpy(C_A,C_A1,20*sizeof(CPoint));
							memcpy(D_A,D_A1,20*sizeof(CPoint));
							memcpy(C_B,C_B1,20*sizeof(CPoint));
							memcpy(D_B,D_B1,20*sizeof(CPoint));
							memcpy(PC_A,PC_A1,20*sizeof(CPoint));
							memcpy(SP_A,SP_A1,20*sizeof(CPoint));
							memcpy(PSW_B,PSW_B1,20*sizeof(CPoint));
							memcpy(MDR_B,MDR_B1,20*sizeof(CPoint));
							memcpy(Y_R0,Y_R01,20*sizeof(CPoint));
							memcpy(Y_R1,Y_R11,20*sizeof(CPoint));
							memcpy(Y_R2,Y_R21,20*sizeof(CPoint));
							memcpy(Y_R3,Y_R31,20*sizeof(CPoint));
							memcpy(Y_C,Y_C1,20*sizeof(CPoint));
							memcpy(Y_D,Y_D1,20*sizeof(CPoint));
							memcpy(Y_PSW,Y_PSW1,20*sizeof(CPoint));
							memcpy(Y_PC,Y_PC1,20*sizeof(CPoint));
							memcpy(Y_SP,Y_SP1,20*sizeof(CPoint));
							memcpy(Y_MDR,Y_MDR1,20*sizeof(CPoint));
							memcpy(Y_MAR,Y_MAR1,20*sizeof(CPoint));
							memcpy(M_IR,M_IR1,20*sizeof(CPoint));
							memcpy(M_MDR,M_MDR1,20*sizeof(CPoint));
							memcpy(M_MAR,M_MAR1,20*sizeof(CPoint));
							memcpy(MDR_M,MDR_M1,20*sizeof(CPoint));
							memcpy(MAR_M,MAR_M1,20*sizeof(CPoint));
							memcpy(A_Y,A_Y1,20*sizeof(CPoint));
							memcpy(B_Y,B_Y1,20*sizeof(CPoint));
							CPoint left1(50*point_width,50*point_height);
							CPoint left2(50*point_width,975*point_height);
							CPoint left3(250*point_width,225*point_height);
							CPoint left4(250*point_width,975*point_height);
							CPoint right1(650*point_width,225*point_height);
							CPoint right2(650*point_width,975*point_height);
							CPoint right3(850*point_width,50*point_height);
							CPoint right4(850*point_width,810*point_height);
							CPoint Shifter1(450*point_width,50*point_height);
							CPoint Shifter2(450*point_width,225*point_height);
							CPoint Shifter3(450*point_width,325*point_height);
							//Operation
							CPoint Operation1(450*point_width,425*point_height);
							CPoint Operation2(400*point_width,425*point_height);
							CPoint Operation3(500*point_width,425*point_height);
							CPoint Operation4(300*point_width,525*point_height);
							CPoint Operation5(600*point_width,525*point_height);
							CPoint Operation6(400*point_width,525*point_height);
							CPoint Operation7(500*point_width,525*point_height);
							CPoint Operation8(450*point_width,475*point_height);
							CPoint Operation9(350*point_width,525*point_height);
							CPoint Operation10(550*point_width,525*point_height);
							CPoint A_point1(350*point_width,625*point_height);
							CPoint A_point2(350*point_width,725*point_height);
							CPoint A_point3(350*point_width,975*point_height);
							CPoint B_point1(550*point_width,625*point_height);
							CPoint B_point2(550*point_width,725*point_height);
							CPoint B_point3(550*point_width,975*point_height);
							CPoint R0_side1(50*point_width,225*point_height);
							CPoint R0_side2(100*point_width,225*point_height);
							CPoint R0_side3(200*point_width,225*point_height);
							CPoint R0_side4(250*point_width,225*point_height);
							CPoint R1_side1(50*point_width,375*point_height);
							CPoint R1_side2(100*point_width,375*point_height);
							CPoint R1_side3(200*point_width,375*point_height);
							CPoint R1_side4(250*point_width,375*point_height);
							CPoint R2_side1(50*point_width,525*point_height);
							CPoint R2_side2(100*point_width,525*point_height);
							CPoint R2_side3(200*point_width,525*point_height);
							CPoint R2_side4(250*point_width,525*point_height);
							CPoint R3_side1(50*point_width,675*point_height);
							CPoint R3_side2(100*point_width,675*point_height);
							CPoint R3_side3(200*point_width,675*point_height);
							CPoint R3_side4(250*point_width,675*point_height);
							CPoint C_side1(50*point_width,825*point_height);
							CPoint C_side2(100*point_width,825*point_height);
							CPoint C_side3(200*point_width,825*point_height);
							CPoint C_side4(250*point_width,825*point_height);
							CPoint D_side1(50*point_width,975*point_height);
							CPoint D_side2(100*point_width,975*point_height);
							CPoint D_side3(200*point_width,975*point_height);
							CPoint D_side4(250*point_width,975*point_height);
							CPoint PSW_side1(650*point_width,225*point_height);
							CPoint PSW_side2(700*point_width,225*point_height);
							CPoint PSW_side3(800*point_width,225*point_height);
							CPoint PSW_side4(850*point_width,225*point_height);
							CPoint SP_side1(650*point_width,375*point_height);
							CPoint SP_side2(700*point_width,375*point_height);
							CPoint SP_side3(800*point_width,375*point_height);
							CPoint SP_side4(850*point_width,375*point_height);
							CPoint PC_side1(650*point_width,525*point_height);
							CPoint PC_side2(700*point_width,525*point_height);
							CPoint PC_side3(800*point_width,525*point_height);
							CPoint PC_side4(850*point_width,525*point_height);
							CPoint MDR_side1(650*point_width,660*point_height);
							CPoint MDR_side2(700*point_width,660*point_height);
							CPoint MDR_side3(800*point_width,675*point_height);
							CPoint MDR_side4(850*point_width,675*point_height);
							CPoint MDR_side5(700*point_width,690*point_height);
							CPoint MDR_side6(680*point_width,690*point_height);
							CPoint MDR_side7(680*point_width,900*point_height);
							CPoint MDR_side8(830*point_width,900*point_height);
							CPoint MAR_side1(800*point_width,810*point_height);
							CPoint MAR_side2(850*point_width,810*point_height);
							CPoint IR_side1(800*point_width,975*point_height);
							CPoint IR_side2(830*point_width,975*point_height);
							CPoint AB_side1(875*point_width,0*point_height);
							CPoint AB_side2(875*point_width,1000*point_height);
							CPoint AB_side3(875*point_width,200*point_height);
							CPoint AB_side4(950*point_width,200*point_height);
							CPoint AB_side5(800*point_width,840*point_height);
							CPoint AB_side6(875*point_width,840*point_height);
							CPoint DB_side1(900*point_width,0*point_height);
							CPoint DB_side2(900*point_width,1000*point_height);
							CPoint DB_side3(900*point_width,125*point_height);
							CPoint DB_side4(950*point_width,125*point_height);
							CPoint DB_side5(830*point_width,938*point_height);
							CPoint DB_side6(900*point_width,938*point_height);
							CPoint CB_side1(925*point_width,0*point_height);
							CPoint CB_side2(925*point_width,1000*point_height);
							CPoint CB_side3(925*point_width,50*point_height);
							CPoint CB_side4(950*point_width,50*point_height);
							CRect R0(100*point_width,200*point_height,200*point_width,250*point_height);
							CRect R1(100*point_width,350*point_height,200*point_width,400*point_height);
							CRect R2(100*point_width,500*point_height,200*point_width,550*point_height);
							CRect R3(100*point_width,650*point_height,200*point_width,700*point_height);
							CRect C(100*point_width,800*point_height,200*point_width,850*point_height);
							CRect D(100*point_width,950*point_height,200*point_width,1000*point_height);
							CRect PSW(700*point_width,200*point_height,800*point_width,250*point_height);
							CRect SP(700*point_width,350*point_height,800*point_width,400*point_height);
							CRect PC(700*point_width,500*point_height,800*point_width,550*point_height);
							CRect MDR(700*point_width,650*point_height,800*point_width,700*point_height);
							CRect MAR(700*point_width,800*point_height,800*point_width,850*point_height);
							CRect IR(700*point_width,950*point_height,800*point_width,1000*point_height);
							CRect M(950*point_width,50*point_height,1000*point_width,200*point_height);
							CRect Shifter(400*point_width,225*point_height,500*point_width,325*point_height);
							CRect A(300*point_width,625*point_height,400*point_width,725*point_height);
							CRect B(500*point_width,625*point_height,600*point_width,725*point_height);
							pDC->MoveTo(left1);
							pDC->LineTo(left2);
							pDC->MoveTo(left3);
							pDC->LineTo(left4);
							pDC->MoveTo(right1);
							pDC->LineTo(right2);
							pDC->MoveTo(right3);
							pDC->LineTo(right4);
							pDC->MoveTo(right3);
							pDC->LineTo(left1);
							pDC->MoveTo(right2);
							pDC->LineTo(left2);
							pDC->MoveTo(Shifter1);
							pDC->LineTo(Shifter2);
							pDC->MoveTo(Shifter3);
							pDC->LineTo(Operation1);
							pDC->LineTo(Operation2);
							pDC->LineTo(Operation4);
							pDC->LineTo(Operation6);
							pDC->LineTo(Operation8);
							pDC->LineTo(Operation7);
							pDC->LineTo(Operation5);
							pDC->LineTo(Operation3);
							pDC->LineTo(Operation1);
							pDC->MoveTo(Operation9);
							pDC->LineTo(A_point1);
							pDC->MoveTo(A_point2);
							pDC->LineTo(A_point3);
							pDC->MoveTo(Operation10);
							pDC->LineTo(B_point1);
							pDC->MoveTo(B_point2);
							pDC->LineTo(B_point3);
							pDC->MoveTo(R0_side1);
							pDC->LineTo(R0_side2);
							pDC->MoveTo(R0_side3);
							pDC->LineTo(R0_side4);
							pDC->MoveTo(R1_side1);
							pDC->LineTo(R1_side2);
							pDC->MoveTo(R1_side3);
							pDC->LineTo(R1_side4);
							pDC->MoveTo(R2_side1);
							pDC->LineTo(R2_side2);
							pDC->MoveTo(R2_side3);
							pDC->LineTo(R2_side4);
							pDC->MoveTo(R3_side1);
							pDC->LineTo(R3_side2);
							pDC->MoveTo(R3_side3);
							pDC->LineTo(R3_side4);
							pDC->MoveTo(C_side1);
							pDC->LineTo(C_side2);
							pDC->MoveTo(C_side3);
							pDC->LineTo(C_side4);
							pDC->MoveTo(D_side1);
							pDC->LineTo(D_side2);
							pDC->MoveTo(D_side3);
							pDC->LineTo(D_side4);
							pDC->MoveTo(PSW_side1);
							pDC->LineTo(PSW_side2);
							pDC->MoveTo(PSW_side3);
							pDC->LineTo(PSW_side4);
							pDC->MoveTo(SP_side1);
							pDC->LineTo(SP_side2);
							pDC->MoveTo(SP_side3);
							pDC->LineTo(SP_side4);
							pDC->MoveTo(PC_side1);
							pDC->LineTo(PC_side2);
							pDC->MoveTo(PC_side3);
							pDC->LineTo(PC_side4);
							pDC->MoveTo(MDR_side1);
							pDC->LineTo(MDR_side2);
							pDC->MoveTo(MDR_side3);
							pDC->LineTo(MDR_side4);
							pDC->MoveTo(MDR_side5);
							pDC->LineTo(MDR_side6);
							//pDC->MoveTo(MDR_side6);
							pDC->LineTo(MDR_side7);
							//pDC->MoveTo(MDR_side7);
							pDC->LineTo(MDR_side8);
							pDC->LineTo(IR_side2);
							pDC->MoveTo(MAR_side1);
							pDC->LineTo(MAR_side2);
							pDC->MoveTo(IR_side1);
							pDC->LineTo(IR_side2);
							pDC->MoveTo(AB_side1);
							pDC->LineTo(AB_side2);
							pDC->MoveTo(AB_side3);
							pDC->LineTo(AB_side4);
							pDC->MoveTo(AB_side5);
							pDC->LineTo(AB_side6);
							pDC->MoveTo(DB_side1);
							pDC->LineTo(DB_side2);
							pDC->MoveTo(DB_side3);
							pDC->LineTo(DB_side4);
							pDC->MoveTo(DB_side5);
							pDC->LineTo(DB_side6);
							pDC->MoveTo(CB_side1);
							pDC->LineTo(CB_side2);
							pDC->MoveTo(CB_side3);
							pDC->LineTo(CB_side4);
							pDC->Rectangle(R0);
							pDC->Rectangle(R1);
							pDC->Rectangle(R2);
							pDC->Rectangle(R3);
							pDC->Rectangle(C);
							pDC->Rectangle(D);
							pDC->Rectangle(PSW);
							pDC->Rectangle(SP);
							pDC->Rectangle(PC);
							pDC->Rectangle(MDR);
							pDC->Rectangle(MAR);
							pDC->Rectangle(IR);
							pDC->Rectangle(M);
							pDC->Rectangle(Shifter);
							pDC->Rectangle(A);
							pDC->Rectangle(B);
						   // 创建实心画笔，粗度为1，颜色为绿色   
						    //newPen.CreatePen(PS_SOLID, 5, RGB(225,255,0));   
						    // 选择新画笔，并将旧画笔的指针保存到pOldPen   
						   // pOldPen = pDC->SelectObject(&newPen);  
							
							     
						   DrawWave(m_picDraw.GetDC(), rectPicture);
						   if(edit==1)
						  {
							  xxx++;
							outPutSteps();
							edit=0;
						   }
								
							 // 绘制波形图   
							  pDC->SelectObject(pOldPen);   
						    // 删除新画笔   
						    newPen.DeleteObject();
							CDialogEx::OnTimer(nIDEvent);

						//输出微命令
							outMorderByStep();
						}

						CPoint* CTipDlg::dp_st_indirect()//双操作数的st周期的间址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE);
							st_size=2*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_st[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::dp_st_minus()//双操作数的st周期的自减型寻址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							st_size=2*ALLSIZE;
							int size=0;
							/********Ri-1->Ri->MAR************/
							if(addressing_st[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							
							else if(addressing_st[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							for(int i=0;size<100;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
								for(int i=0;size<120;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::dp_st_plus()//双操作数的st周期的自增型寻址
						{
							CPoint  *value = new CPoint[3*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *3* ALLSIZE); 
							st_size=3*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_st[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==5)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							size=2*ALLSIZE-1;
							/************Ri+1->Ri*****************/
							if(addressing_st[1]==0)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
							}
							else if(addressing_st[1]==1)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
							}
							else if(addressing_st[1]==2)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
							}
							else if(addressing_st[1]==3)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
							}
							else if(addressing_st[1]==4)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
							}
							else if(addressing_st[1]==5)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_PC[i];
								}
								size--;
							}
							return value;
						}
						CPoint* CTipDlg::dp_st_unstable()//双操作数的st周期的变址寻址
						{
							CPoint  *value = new CPoint[5*ALLSIZE];
							//CPoint value[5*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *5* ALLSIZE); 
							st_size=5*ALLSIZE;
							int size=0;
							/********PC->MAR*********/
							for(int i=0;size<20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							size=2*ALLSIZE-1;
							/************PC+1->PC*****************/
							for(int i=0;size<2*ALLSIZE+20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+60;size++,i++)
							{
								value[size]=Y_PC[i];
							}
							size--;
							size=3*ALLSIZE-1;
							/****************C+Ri->MAR***************/
							if(addressing_st[1]==0)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==1)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==2)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==3)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_st[1]==4)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<3*ALLSIZE+40;size++,i++)
							{
								value[size]=C_B[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+60;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+80;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+100;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=4*ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<4*ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::et()//et周期的操作指令集(自动检测属于什么类型的操作码)
						{
							CPoint *value1=new CPoint[2*ALLSIZE];
							CPoint *value_size1=new CPoint[ALLSIZE];
							//CPoint [ALLSIZE];
							CPoint *value_size2=new CPoint[2*ALLSIZE];
							CPoint *value_size3=new CPoint[3*ALLSIZE];
							CPoint *value=new CPoint[4*ALLSIZE];
							//CPoint value1[2*ALLSIZE];
							//CPoint value_size1[ALLSIZE];
							//CPoint value_size2[2*ALLSIZE];
							//CPoint value_size3[3*ALLSIZE];
							//CPoint value[4*ALLSIZE];
							memset(value1, 0, sizeof(CPoint) *2* ALLSIZE); 
							memset(value, 0, sizeof(CPoint) *4* ALLSIZE); 
							memset(value_size1, 0, sizeof(CPoint) * ALLSIZE);
							memset(value_size2, 0, sizeof(CPoint) *2* ALLSIZE);
							memset(value_size3, 0, sizeof(CPoint) *3* ALLSIZE);
							int size=0;
							if(opcode==0)
							{
								if(addressing_dt[0]==0)
								{
									if(addressing_st[0]==0)
									{
										if(addressing_st[1]==0)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==1)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==2)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==3)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==4)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==5)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;
									}
									else
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=C_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										if(addressing_dt[1]==0)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_R0[i];
											}
											size--;
										}
										else if(addressing_dt[1]==1)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_R1[i];
											}
											size--;
										}
										else if(addressing_dt[1]==2)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_R2[i];
											}
											size--;
										}
										else if(addressing_dt[1]==3)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_R3[i];
											}
											size--;
										}
										else if(addressing_dt[1]==4)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_SP[i];
											}
											size--;
										}
										else if(addressing_dt[1]==1)
										{
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=Y_PC[i];
											}
											size--;
										}
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;
									}
								}	
								else
								{
									if(addressing_st[1]==0)
									{
										if(addressing_dt[1]==0)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R0_A[i];
											}
											size--;
										}
										else if(addressing_dt[1]==1)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R1_A[i];
											}
											size--;
										}
										else if(addressing_dt[1]==2)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R2_A[i];
											}
											size--;
										}
										else if(addressing_dt[1]==3)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R3_A[i];
											}
											size--;
										}
										else if(addressing_dt[1]==4)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=SP_A[i];
											}
											size--;
										}
										else if(addressing_dt[1]==5)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=PC_A[i];
											}
											size--;
										}
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_MDR[i];
										}
										size--;
										for(int i=0;size<80;size++,i++)
										{
											value1[size]=MDR_M[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;
									}
									else
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=C_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_MDR[i];
										}
										size--;
										for(int i=0;size<80;size++,i++)
										{
											value1[size]=MDR_M[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;

									}
								}
							}
							else if(opcode>=1&&opcode<=5)
							{
								if(addressing_dt[0]==0)
								{
									if(addressing_st[0]==0)
									{
										if(addressing_st[1]==0)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==1)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==2)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==3)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
											else if(addressing_dt[1]==4)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_SP[i];
												}
												size--;
											}
											else if(addressing_dt[1]==5)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_PC[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==4)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=SP_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
										}
										else if(addressing_st[1]==5)
										{
											if(addressing_dt[1]==0)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R0_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R0[i];
												}
												size--;
											}
											else if(addressing_dt[1]==1)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R1_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R1[i];
												}
												size--;
											}
											else if(addressing_dt[1]==2)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R2_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R2[i];
												}
												size--;
											}
											else if(addressing_dt[1]==3)
											{
												for(int i=0;size<20;size++,i++)
												{
													value1[size]=PC_A[i];
												}
												size--;
												for(int i=0;size<40;size++,i++)
												{
													value1[size]=R3_B[i];
												}
												size--;
												for(int i=0;size<60;size++,i++)
												{
													value1[size]=A_Y[i];
												}
												size--;
												for(int i=0;size<80;size++,i++)
												{
													value1[size]=B_Y[i];
												}
												size--;
												for(int i=0;size<100;size++,i++)
												{
													value1[size]=Y_R3[i];
												}
												size--;
											}
										}
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;

									}
									else
									{
										if(addressing_dt[1]==0)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R0_A[i];
											}
											size--;
											for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_R0[i];
											}
											size--;
										}
										else if(addressing_dt[1]==1)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R1_A[i];
											}
											size--;
											for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_R1[i];
											}
											size--;
										}
										else if(addressing_dt[1]==2)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R2_A[i];
											}
											size--;
											for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_R2[i];
											}
											size--;
										}
										else if(addressing_dt[1]==3)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R3_A[i];
											}
											size--;
											for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_R3[i];
											}
											size--;
										}
										else if(addressing_dt[1]==4)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=SP_A[i];
											}
											size--;for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_SP[i];
											}
											size--;
										}
										else if(addressing_dt[1]==5)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=PC_A[i];
											}
											size--;
											for(int i=0;size<40;size++,i++)
											{
												value1[size]=C_B[i];
											}
											size--;
											for(int i=0;size<60;size++,i++)
											{
												value1[size]=A_Y[i];
											}
											size--;
											for(int i=0;size<80;size++,i++)
											{
												value1[size]=B_Y[i];
											}
											size--;
											for(int i=0;size<100;size++,i++)
											{
												value1[size]=Y_PC[i];
											}
											size--;
										}
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value1[size]=Y_MAR[i];
										}
										size--;
										et_size=2*ALLSIZE;
										return value1;
									}
								}	
								else
								{
									if(addressing_st[0]==0)
									{
										if(addressing_st[1]==0)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R0_A[i];
											}
											size--;
										}
										else if(addressing_st[1]==1)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R1_A[i];
											}
											size--;
										}
										else if(addressing_st[1]==2)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R2_A[i];
											}
											size--;
										}
										else if(addressing_st[1]==3)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=R3_A[i];
											}
											size--;
										}
										else if(addressing_st[1]==4)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=SP_A[i];
											}
											size--;
										}
										else if(addressing_st[1]==5)
										{
											for(int i=0;size<20;size++,i++)
											{
												value1[size]=PC_A[i];
											}
											size--;
										}
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=D_B[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<80;size++,i++)
										{
											value1[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<100;size++,i++)
										{
											value1[size]=Y_MDR[i];
										}
										size--;
										for(int i=0;size<120;size++,i++)
										{
											value1[size]=MDR_M[i];
										}
										size--;
									}
									else 
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=C_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=D_B[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<80;size++,i++)
										{
											value1[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<100;size++,i++)
										{
											value1[size]=Y_MDR[i];
										}
										size--;
										for(int i=0;size<120;size++,i++)
										{
											value1[size]=MDR_M[i];
										}
										size--;
									}
									size=ALLSIZE-1;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value1[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value1[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value1[size]=Y_MAR[i];
									}
									size--;
									et_size=2*ALLSIZE;
									return value1;
								}	
							}
							else if(opcode>=6&&opcode<=11)
							{
								if(addressing_dt[0]==0)
								{
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=R1_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_R1[i];
										}
										size--;
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=R2_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_R2[i];
										}
										size--;
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=R3_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_R3[i];
										}
										size--;
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=SP_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_SP[i];
										}
										size--;
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<20;size++,i++)
										{
											value1[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value1[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value1[size]=Y_PC[i];
										}
										size--;
									}
								}
								else
								{
									for(int i=0;size<20;size++,i++)
									{
										value1[size]=D_A[i];
									}
									size--;
									for(int i=0;size<40;size++,i++)
									{
										value1[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<60;size++,i++)
									{
										value1[size]=Y_MDR[i];
									}
									size--;
									for(int i=0;size<20;size++,i++)
									{
										value1[size]=MDR_M[i];
									}
									size--;
								}
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value1[size]=PC_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value1[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value1[size]=Y_MAR[i];
								}
								size--;
								et_size=2*ALLSIZE;
								return value1;
							}
							else if(opcode>=12&&opcode<=13)
							{

								if(addressing_dt[0]==0)
								{
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=R0_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=R1_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=R2_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=R3_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=SP_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size1[size]=PC_A[i];
										}
										size--;
									}
									for(int i=0;size<40;size++,i++)
									{
										value_size1[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<60;size++,i++)
									{
										value_size1[size]=Y_PC[i];
									}
									size--;
									for(int i=0;size<80;size++,i++)
									{
										value_size1[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<100;size++,i++)
									{
										value_size1[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<1200;size++,i++)
									{
										value_size1[size]=Y_MAR[i];
									}
									size--;
									et_size=ALLSIZE;
									return value_size1;
								}
								else if(addressing_dt[0]==1)
								{
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=R0_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=R1_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=R2_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=R3_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=SP_A[i];
										}
										size--;
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size2[size]=PC_A[i];
										}
										size--;
									}
									for(int i=0;size<40;size++,i++)
									{
										value_size2[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<60;size++,i++)
									{
										value_size2[size]=Y_MAR[i];
									}
									size--;
									size=ALLSIZE-1;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value_size2[size]=M_MDR[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value_size2[size]=MDR_B[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value_size2[size]=B_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+80;size++,i++)
									{
										value_size2[size]=Y_PC[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+100;size++,i++)
									{
										value_size2[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+120;size++,i++)
									{
										value_size2[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+140;size++,i++)
									{
										value_size2[size]=Y_MAR[i];
									}
									size--;
									et_size=2*ALLSIZE;
									return value_size2;
								}
								else if(addressing_dt[0]==3)
								{
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=R1_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=R2_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=R3_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=SP_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<20;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<60;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=ALLSIZE-1;
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=M_MDR[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+40;size++,i++)
										{
											value_size3[size]=MDR_B[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+60;size++,i++)
										{
											value_size3[size]=B_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+80;size++,i++)
										{
											value_size3[size]=Y_PC[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+100;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+120;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<ALLSIZE+140;size++,i++)
										{
											value_size3[size]=Y_MAR[i];
										}
										size--;
										size=2*ALLSIZE-1;
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+40;size++,i++)
										{
											value_size3[size]=A_Y[i];
										}
										size--;
										for(int i=0;size<2*ALLSIZE+60;size++,i++)
										{
											value_size3[size]=Y_R0[i];
										}
										size--;
									}
									et_size=3*ALLSIZE;	
									return value_size3;
								}		
								else if(addressing_dt[0]==4)
								{
									for(int i=0;size<20;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<20;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									size--;
									size=ALLSIZE-1;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value_size3[size]=M_MDR[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value_size3[size]=MDR_B[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value_size3[size]=B_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value_size3[size]=Y_C[i];
									}
									size--;
									size=2*ALLSIZE-1;
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
										size--;				
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R1_A[i];
										}
										size--;				
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R2_A[i];
										}
										size--;				
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R3_A[i];
										}
										size--;				
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=SP_A[i];
										}
										size--;				
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<ALLSIZE+20;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
										size--;				
									}
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value_size3[size]=C_B[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+80;size++,i++)
									{
										value_size3[size]=B_Y[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+100;size++,i++)
									{
										value_size3[size]=Y_PC[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+120;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+140;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;	
									for(int i=0;size<ALLSIZE+160;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									size--;	
									et_size=3*ALLSIZE;
									return value_size3;
								}
							}
							else 
							{
								if(addressing_dt[0]==0)
								{
									for(int i=0;size<20;size++,i++)
									{
										value_size3[size]=SP_A[i];
									}
									size--;
									for(int i=0;size<40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<60;size++,i++)
									{
										value_size3[size]=Y_SP[i];
									}
									size--;
									for(int i=0;size<80;size++,i++)
									{
										value_size3[size]=SP_A[i];
									}
									size--;
									for(int i=0;size<100;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<120;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									size--;
									size=ALLSIZE-1;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value_size3[size]=Y_MDR[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+80;size++,i++)
									{
										value_size3[size]=MDR_M[i];
									}
									size--;
									size=2*ALLSIZE-1;
									if(addressing_dt[1]==0)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R0_A[i];
										}
									}
									else if(addressing_dt[1]==1)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R1_A[i];
										}
									}
									else if(addressing_dt[1]==2)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R2_A[i];
										}
									}
									else if(addressing_dt[1]==3)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=R3_A[i];
										}
									}
									else if(addressing_dt[1]==4)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=SP_A[i];
										}
									}
									else if(addressing_dt[1]==5)
									{
										for(int i=0;size<2*ALLSIZE+20;size++,i++)
										{
											value_size3[size]=PC_A[i];
										}
									}
									for(int i=0;size<2*ALLSIZE+40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									for(int i=0;size<2*ALLSIZE+60;size++,i++)
									{
										value_size3[size]=Y_PC[i];
									}
									for(int i=0;size<2*ALLSIZE+80;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									for(int i=0;size<2*ALLSIZE+100;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									for(int i=0;size<2*ALLSIZE+120;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									et_size=3*ALLSIZE;
									return value_size3;
								}
								else 
								{
									for(int i=0;size<20;size++,i++)
									{
										value_size3[size]=SP_A[i];
									}
									size--;
									for(int i=0;size<40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<60;size++,i++)
									{
										value_size3[size]=Y_SP[i];
									}
									size--;
									for(int i=0;size<80;size++,i++)
									{
										value_size3[size]=SP_A[i];
									}
									size--;
									for(int i=0;size<100;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<120;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									size--;
									size=ALLSIZE-1;
									for(int i=0;size<ALLSIZE+20;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+60;size++,i++)
									{
										value_size3[size]=Y_MDR[i];
									}
									size--;
									for(int i=0;size<ALLSIZE+80;size++,i++)
									{
										value_size3[size]=MDR_M[i];
									}
									size--;
									size=2*ALLSIZE-1;
									for(int i=0;size<2*ALLSIZE+20;size++,i++)
									{
										value_size3[size]=C_A[i];
									}
									
									for(int i=0;size<2*ALLSIZE+40;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									for(int i=0;size<2*ALLSIZE+60;size++,i++)
									{
										value_size3[size]=Y_PC[i];
									}
									for(int i=0;size<2*ALLSIZE+80;size++,i++)
									{
										value_size3[size]=PC_A[i];
									}
									for(int i=0;size<2*ALLSIZE+100;size++,i++)
									{
										value_size3[size]=A_Y[i];
									}
									for(int i=0;size<2*ALLSIZE+120;size++,i++)
									{
										value_size3[size]=Y_MAR[i];
									}
									et_size=3*ALLSIZE;
									return value_size3;
								}
							}
						}
						CPoint* CTipDlg::ft()//ft周期的操作指令集
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							ft_size=2*ALLSIZE;
							int size=0;
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							for(int i=0;size<20;size++,i++)
							{
								value[size]=M_IR[i];
							}
							size--;
							size=ALLSIZE-1;
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=Y_PC[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::dp_dt_indirect()//双操作数的st周期的间址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							dt_size=2*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::dp_dt_minus()//双操作数的st周期的自减型寻址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							dt_size=2*ALLSIZE;
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							int size=0;
							/********Ri-1->Ri->MAR************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							for(int i=0;size<100;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
								for(int i=0;size<120;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::dp_dt_plus()//双操作数的st周期的自增型寻址
						{
							CPoint  *value = new CPoint[3*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *3* ALLSIZE); 
							dt_size=3*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==5)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							size=2*ALLSIZE-1;
							/************Ri+1->Ri*****************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
							}
							else if(addressing_dt[1]==5)
							{
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_PC[i];
								}
								size--;
							}
							return value;
						}
						CPoint* CTipDlg::dp_dt_unstable()//双操作数的st周期的变址寻址
						{
							CPoint  *value = new CPoint[5*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *5* ALLSIZE); 
							dt_size=5*ALLSIZE;
							int size=0;
							/********P->MAR*********/
							for(int i=0;size<20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							size=ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							size=2*ALLSIZE-1;
							/************PC+1->PC*****************/
							for(int i=0;size<2*ALLSIZE+20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+60;size++,i++)
							{
								value[size]=Y_PC[i];
							}
							size--;
							size=3*ALLSIZE-1;
							/****************C+Ri->MAR***************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==1)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==2)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==3)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==4)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<3*ALLSIZE+40;size++,i++)
							{
								value[size]=D_B[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+60;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+80;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+100;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=4*ALLSIZE-1;
							/************M->MDR->C **************/
							for(int i=0;size<4*ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<4*ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::mov_dt_indirect()//mov的dt周期的间址
						{
							CPoint  *value = new CPoint[ALLSIZE];
							memset(value, 0, sizeof(CPoint) * ALLSIZE); 
							dt_size=ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							return value;
						}
						CPoint* CTipDlg::mov_dt_minus()//mov的st周期的自减型寻址
						{
							CPoint  *value = new CPoint[ALLSIZE];
							memset(value, 0, sizeof(CPoint) * ALLSIZE); 
							dt_size=ALLSIZE;
							int size=0;
							/********Ri-1->Ri->MAR************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
								for(int i=0;size<80;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							for(int i=0;size<100;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
								for(int i=0;size<120;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							return value;
						}
						CPoint* CTipDlg::mov_dt_plus()//mov的st周期的自增型寻址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							dt_size=2*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==5)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							
							/************Ri+1->Ri*****************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
							}
							else if(addressing_dt[1]==5)
							{
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=Y_PC[i];
								}
								size--;
							}
							return value;
						}
						CPoint* CTipDlg::mov_dt_unstable()//mov的st周期的变址寻址
						{
							CPoint  *value = new CPoint[4*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *4* ALLSIZE); 
							dt_size=4*ALLSIZE;
							int size=0;
							/********P->MAR*********/
							for(int i=0;size<20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							size=ALLSIZE-1;
							/************M->MDR->D **************/
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_D[i];
							}
							size--;
							size=2*ALLSIZE-1;
							/************PC+1->PC*****************/
							for(int i=0;size<2*ALLSIZE+20;size++,i++)
							{
								value[size]=PC_A[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<2*ALLSIZE+60;size++,i++)
							{
								value[size]=Y_PC[i];
							}
							size--;
							size=3*ALLSIZE-1;
							/****************C+Ri->MAR***************/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==1)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==2)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==3)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							if(addressing_dt[1]==4)
							{
								for(int i=0;size<3*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
							}
							for(int i=0;size<3*ALLSIZE+40;size++,i++)
							{
								value[size]=D_B[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+60;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+80;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<3*ALLSIZE+100;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							
							return value;
						}
						CPoint* CTipDlg::jsr_st_indirect()//jsr的st周期的间址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							st_size=2*ALLSIZE;
							int size=0;
							/********Ri->MAR*********/
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
							}
							for(int i=0;size<40;size++,i++)
							{
								value[size]=A_Y[i];
							}
							size--;
							for(int i=0;size<60;size++,i++)
							{
								value[size]=Y_MAR[i];
							}
							size--;
							size=ALLSIZE-1;
							for(int i=0;size<ALLSIZE+20;size++,i++)
							{
								value[size]=M_MDR[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+40;size++,i++)
							{
								value[size]=MDR_B[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+60;size++,i++)
							{
								value[size]=B_Y[i];
							}
							size--;
							for(int i=0;size<ALLSIZE+80;size++,i++)
							{
								value[size]=Y_C[i];
							}
							size--;
							return value;
						}
						CPoint* CTipDlg::jsr_st_plus()//jsr的st周期的自增型寻址
						{
							CPoint  *value = new CPoint[2*ALLSIZE];
							memset(value, 0, sizeof(CPoint) *2* ALLSIZE); 
							st_size=2*ALLSIZE;
							int size=0;
							if(addressing_dt[1]==0)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R0_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R0[i];
								}
								size--;
							}
							else if(addressing_dt[1]==1)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R1_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R1[i];
								}
								size--;
							}
							else if(addressing_dt[1]==2)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R2_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R2[i];
								}
								size--;
							}
							else if(addressing_dt[1]==3)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=R3_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_R3[i];
								}
								size--;
							}
							else if(addressing_dt[1]==4)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=SP_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_SP[i];
								}
								size--;
							}
							else if(addressing_dt[1]==5)
							{
								for(int i=0;size<20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
									for(int i=0;size<40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<60;size++,i++)
								{
									value[size]=Y_MAR[i];
								}
								size--;
								size=ALLSIZE-1;
								for(int i=0;size<ALLSIZE+20;size++,i++)
								{
									value[size]=M_MDR[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+40;size++,i++)
								{
									value[size]=MDR_B[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+60;size++,i++)
								{
									value[size]=B_Y[i];
								}
								size--;
								for(int i=0;size<ALLSIZE+80;size++,i++)
								{
									value[size]=Y_C[i];
								}
								size--;
								size=2*ALLSIZE-1;
								for(int i=0;size<2*ALLSIZE+20;size++,i++)
								{
									value[size]=PC_A[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+40;size++,i++)
								{
									value[size]=A_Y[i];
								}
								size--;
								for(int i=0;size<2*ALLSIZE+60;size++,i++)
								{
									value[size]=Y_PC[i];
								}
								size--;
							}
							return value;
						}
						void CTipDlg::DrawWave(CDC *pDC, CRect &rectPicture)   
						{      
						    CPen newPen;       // 用于创建新画笔   
						    CPen *pOldPen;     // 用于存放旧画笔   
						  //  CBrush newBrush;   // 用于创建新画刷   
						   // CBrush *pOldBrush; // 用于存放旧画刷   
						  
						    // 计算fDeltaX和fDeltaY   
						    //fDeltaX = (float)rectPicture.Width() / (POINT_COUNT - 1);   
						    //fDeltaY = (float)rectPicture.Height() / 80;   
						  
						    // 创建黑色新画刷   
						   // newBrush.CreateSolidBrush(RGB(0,0,0));   
						    // 选择新画刷，并将旧画刷的指针保存到pOldBrush   
						   // pOldBrush = pDC->SelectObject(&newBrush);   
						    // 以黑色画刷为绘图控件填充黑色，形成黑色背景   
						   // pDC->Rectangle(rectPicture);   
						    // 恢复旧画刷   
						  //  pDC->SelectObject(pOldBrush);   
						    // 删除新画刷   
						   // newBrush.DeleteObject(); 
							 // 创建实心画笔，粗度为1，颜色为绿色  
							/*if(code_size/20==0)
						    newPen.CreatePen(PS_SOLID, 6, RGB(255,255,0));   
							else if(code_size/20==1)
							 newPen.CreatePen(PS_SOLID, 6, RGB(255,0,0));  
							else if(code_size/20==2)
							 newPen.CreatePen(PS_SOLID, 6, RGB(0,0,255));
							else if(code_size/20==3)
							 newPen.CreatePen(PS_SOLID, 6, RGB(255,128,0));
							else if(code_size/20==4)
							 newPen.CreatePen(PS_SOLID, 6, RGB(153,51,250));
							else 
							 newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));*/
						    newPen.CreatePen(PS_SOLID, 6, RGB(255,255,0));   
						    // 选择新画笔，并将旧画笔的指针保存到pOldPen   
						    pOldPen = pDC->SelectObject(&newPen);
							CPoint *ft_value=NULL,*value,*et_value=NULL,*st_value=NULL,*dt_value=NULL;
							ft_value=ft();
							et_value=et();
							if(opcode<=5)
							{
								if(addressing_st[0]==1)
									st_value=dp_st_indirect();
								else if(addressing_st[0]==2)
									st_value=dp_st_minus();
								else if(addressing_st[0]==3)
									st_value=dp_st_plus();
								else if(addressing_st[0]==4)
									st_value=dp_st_unstable();
								if(opcode==0)
								{
									if(addressing_dt[0]==1)
										dt_value=mov_dt_indirect();
									else if(addressing_dt[0]==2)
										dt_value=mov_dt_minus();
									else if(addressing_dt[0]==3)
										dt_value=mov_dt_plus();
									else if(addressing_dt[0]==4)
										dt_value=mov_dt_unstable();
								}
								else
								{
									if(addressing_dt[0]==1)
										dt_value=dp_dt_indirect();
									else if(addressing_dt[0]==2)
										dt_value=dp_dt_minus();
									else if(addressing_dt[0]==3)
										dt_value=dp_dt_plus();
									else if(addressing_dt[0]==4)
										dt_value=dp_dt_unstable();
								}
							}
							else if(opcode>=6&&opcode<=11)
							{
								if(addressing_dt[0]==1)
									dt_value=dp_dt_indirect();
								else if(addressing_dt[0]==2)
									dt_value=dp_dt_minus();
								else if(addressing_dt[0]==3)
									dt_value=dp_dt_plus();
								else if(addressing_dt[0]==4)
									dt_value=dp_dt_unstable();
							}
							else
							{
								if(addressing_st[0]==1)
									dt_value=jsr_st_indirect();
								else if(addressing_dt[0]==3)
									dt_value=jsr_st_plus();
							}
							//value=dp_dt_unstable();
						   pDC->MoveTo(ft_value[0]);   
						    // 计算m_nzValues数组中每个点对应的坐标位置，并依次连接，最终形成曲线   
							  
						        //nX = rectPicture.left + (int)(i * fDeltaX);   
						        //nY = rectPicture.bottom - (int)(m_nzValues[i] * fDeltaY);

							//code_size++;
							int size = dt_size;
							//int small_zize=code_size/ALLSIZE;
							
						if(ft_code_size<ft_size)
							{
								ft_code_size++;

							}
							for(int i=0;i<ft_code_size;i++)
							{
								value=ft_value;
								if(value[i].x>=1000*point_width||value[i].y>=1000*point_height||i>=ft_size-1)
								{
									if(st_code_size==-1)
										st_code_size=0;
									break;
									
								}
									
								if(value[i].x!=0||value[i].y!=0)
								{
									if((i+1)%20==0)
									{pDC->MoveTo(value[i]);}
									else 
									{
										
										if(value[i].x==2&&value[i].y==2)
										{
											pDC->MoveTo(550*point_width,725*point_height);
											pDC->LineTo(500*point_width,725*point_height);
											pDC->MoveTo(550*point_width,725*point_height);
											pDC->LineTo(600*point_width,725*point_height);
										}
										else if(value[i].x==1&&value[i].y==2)
										{
											pDC->MoveTo(350*point_width,725*point_height);
											pDC->LineTo(300*point_width,725*point_height);
											pDC->MoveTo(350*point_width,725*point_height);
											pDC->LineTo(400*point_width,725*point_height);
										}
										else if(value[i].x==1&&value[i].y==3)
										{
											pDC->MoveTo(300*point_width,725*point_height);
											pDC->LineTo(300*point_width,675*point_height);
											pDC->MoveTo(400*point_width,725*point_height);
											pDC->LineTo(400*point_width,675*point_height);
										}
										else if(value[i].x==2&&value[i].y==3)
										{
											pDC->MoveTo(500*point_width,725*point_height);
											pDC->LineTo(500*point_width,675*point_height);
											pDC->MoveTo(600*point_width,725*point_height);
											pDC->LineTo(600*point_width,675*point_height);
										}
										else if(value[i].x==1&&value[i].y==4)
										{
											pDC->MoveTo(300*point_width,675*point_height);
											pDC->LineTo(300*point_width,625*point_height);
											pDC->MoveTo(400*point_width,675*point_height);
											pDC->LineTo(400*point_width,625*point_height);
										}
										else if(value[i].x==2&&value[i].y==4)
										{
											pDC->MoveTo(500*point_width,675*point_height);
											pDC->LineTo(500*point_width,625*point_height);
											pDC->MoveTo(600*point_width,675*point_height);
											pDC->LineTo(600*point_width,625*point_height);
										}
										else if(value[i].x==1&&value[i].y==5)
										{
											pDC->MoveTo(300*point_width,625*point_height);
											pDC->LineTo(350*point_width,625*point_height);
											pDC->MoveTo(400*point_width,625*point_height);
											pDC->LineTo(350*point_width,625*point_height);
										}
										else if(value[i].x==2&&value[i].y==5)
										{
											pDC->MoveTo(500*point_width,625*point_height);
											pDC->LineTo(550*point_width,625*point_height);
											pDC->MoveTo(600*point_width,625*point_height);
											pDC->LineTo(550*point_width,625*point_height);
										}
										else if(value[i].x==0&&value[i].y==8)
										{
											pDC->MoveTo(350*point_width,525*point_height);
											pDC->LineTo(300*point_width,525*point_height);
											pDC->MoveTo(350*point_width,525*point_height);
											pDC->LineTo(400*point_width,525*point_height);
											pDC->MoveTo(550*point_width,525*point_height);
											pDC->LineTo(500*point_width,525*point_height);
											pDC->MoveTo(550*point_width,525*point_height);
											pDC->LineTo(600*point_width,525*point_height);
										}
										else if(value[i].x==0&&value[i].y==9)
										{
											pDC->MoveTo(300*point_width,525*point_height);
											pDC->LineTo(350*point_width,475*point_height);
											pDC->MoveTo(400*point_width,525*point_height);
											pDC->LineTo(450*point_width,475*point_height);
											pDC->MoveTo(500*point_width,525*point_height);
											pDC->LineTo(450*point_width,475*point_height);
											pDC->MoveTo(600*point_width,525*point_height);
											pDC->LineTo(550*point_width,475*point_height);
										}
										else if(value[i].x==0&&value[i].y==10)
										{
											pDC->MoveTo(350*point_width,475*point_height);
											pDC->LineTo(400*point_width,425*point_height);
											pDC->MoveTo(550*point_width,475*point_height);
											pDC->LineTo(500*point_width,425*point_height);
										}
										else if(value[i].x==0&&value[i].y==11)
										{
											pDC->MoveTo(400*point_width,425*point_height);
											pDC->LineTo(450*point_width,425*point_height);
											pDC->MoveTo(500*point_width,425*point_height);
											pDC->LineTo(450*point_width,425*point_height);
										}
										else if(value[i].x==0&&value[i].y==14)
										{
											pDC->MoveTo(450*point_width,325*point_height);
											pDC->LineTo(400*point_width,325*point_height);
											pDC->MoveTo(450*point_width,325*point_height);
											pDC->LineTo(500*point_width,325*point_height);
										}
										else if(value[i].x==0&&value[i].y==15)
										{
											pDC->MoveTo(400*point_width,325*point_height);
											pDC->LineTo(400*point_width,275*point_height);
											pDC->MoveTo(500*point_width,275*point_height);
											pDC->LineTo(500*point_width,325*point_height);
										}
										else if(value[i].x==0&&value[i].y==16)
										{
											pDC->MoveTo(400*point_width,275*point_height);
											pDC->LineTo(400*point_width,225*point_height);
											pDC->MoveTo(500*point_width,325*point_height);
											pDC->LineTo(500*point_width,225*point_height);
										}
										else if(value[i].x==0&&value[i].y==17)
										{
											pDC->MoveTo(400*point_width,225*point_height);
											pDC->LineTo(450*point_width,225*point_height);
											pDC->MoveTo(500*point_width,225*point_height);
											pDC->LineTo(450*point_width,225*point_height);
										}
										else
										{
											if(i/ALLSIZE==0)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(255,255,0)); 
												 pOldPen = pDC->SelectObject(&newPen);
											}
											  
											else if(i/ALLSIZE==1)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(65,105,225));  
												pOldPen = pDC->SelectObject(&newPen);
											}
											else if(i/ALLSIZE==2)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(0,0,255));  
												pOldPen = pDC->SelectObject(&newPen);
											}
											
											else if(i/ALLSIZE==3)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(255,128,0));
												pOldPen = pDC->SelectObject(&newPen);
											}
											 
											else if(i/ALLSIZE==4)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(153,51,250));
												pOldPen = pDC->SelectObject(&newPen);
											}
											 
											else if(i/ALLSIZE==5)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));
												pOldPen = pDC->SelectObject(&newPen);
											}
											else if(i/ALLSIZE==6)
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(85,102,0));
												pOldPen = pDC->SelectObject(&newPen);
											}
											else
											{
												 pDC->SelectObject(pOldPen);   
												// 删除新画笔   
												newPen.DeleteObject(); 
												newPen.CreatePen(PS_SOLID, 6, RGB(0,255,0));
												pOldPen = pDC->SelectObject(&newPen);
											}
											 
											pDC->LineTo(value[i]);
										}
										//pDC->LineTo(value[i]); 
									
									}
								}
								else if(value[ft_code_size].x==0&&value[ft_code_size].y==0)
								{
									for(;value[ft_code_size].x==0&&value[ft_code_size].y==0;ft_code_size++);
									ft_code_size--;
									edit=1;
								}
								
							}
							if(st_code_size!=-1)
							{
								
								if(st_size!=0)
								{
									value=st_value;
									pDC->MoveTo(value[0]);
									if(st_code_size<st_size)
									{
										st_code_size++;

									}
									for(int i=0;i<st_code_size;i++)
									{
										if(value[i].x>=1000*point_width||value[i].y>=1000*point_height||i>=st_size-1)
										{
											if(dt_code_size==-1)
											dt_code_size=0;
											break;
											
										}
											
										if(value[i].x!=0||value[i].y!=0)
										{
											if((i+1)%20==0)
											{pDC->MoveTo(value[i]);}
											else 
											{
												
												if(value[i].x==2&&value[i].y==2)
												{
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(500*point_width,725*point_height);
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(600*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==2)
												{
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(300*point_width,725*point_height);
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(400*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==3)
												{
													pDC->MoveTo(300*point_width,725*point_height);
													pDC->LineTo(300*point_width,675*point_height);
													pDC->MoveTo(400*point_width,725*point_height);
													pDC->LineTo(400*point_width,675*point_height);
												}
												else if(value[i].x==2&&value[i].y==3)
												{
													pDC->MoveTo(500*point_width,725*point_height);
													pDC->LineTo(500*point_width,675*point_height);
													pDC->MoveTo(600*point_width,725*point_height);
													pDC->LineTo(600*point_width,675*point_height);
												}
												else if(value[i].x==1&&value[i].y==4)
												{
													pDC->MoveTo(300*point_width,675*point_height);
													pDC->LineTo(300*point_width,625*point_height);
													pDC->MoveTo(400*point_width,675*point_height);
													pDC->LineTo(400*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==4)
												{
													pDC->MoveTo(500*point_width,675*point_height);
													pDC->LineTo(500*point_width,625*point_height);
													pDC->MoveTo(600*point_width,675*point_height);
													pDC->LineTo(600*point_width,625*point_height);
												}
												else if(value[i].x==1&&value[i].y==5)
												{
													pDC->MoveTo(300*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
													pDC->MoveTo(400*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==5)
												{
													pDC->MoveTo(500*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
													pDC->MoveTo(600*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
												}
												else if(value[i].x==0&&value[i].y==8)
												{
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(300*point_width,525*point_height);
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(400*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(500*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(600*point_width,525*point_height);
												}
												else if(value[i].x==0&&value[i].y==9)
												{
													pDC->MoveTo(300*point_width,525*point_height);
													pDC->LineTo(350*point_width,475*point_height);
													pDC->MoveTo(400*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(500*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(600*point_width,525*point_height);
													pDC->LineTo(550*point_width,475*point_height);
												}
												else if(value[i].x==0&&value[i].y==10)
												{
													pDC->MoveTo(350*point_width,475*point_height);
													pDC->LineTo(400*point_width,425*point_height);
													pDC->MoveTo(550*point_width,475*point_height);
													pDC->LineTo(500*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==11)
												{
													pDC->MoveTo(400*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
													pDC->MoveTo(500*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==14)
												{
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(400*point_width,325*point_height);
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==15)
												{
													pDC->MoveTo(400*point_width,325*point_height);
													pDC->LineTo(400*point_width,275*point_height);
													pDC->MoveTo(500*point_width,275*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==16)
												{
													pDC->MoveTo(400*point_width,275*point_height);
													pDC->LineTo(400*point_width,225*point_height);
													pDC->MoveTo(500*point_width,325*point_height);
													pDC->LineTo(500*point_width,225*point_height);
												}
												else if(value[i].x==0&&value[i].y==17)
												{
													pDC->MoveTo(400*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
													pDC->MoveTo(500*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
												}
												else
												{
													if(i/ALLSIZE==0)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(192,192,192)); 
														 pOldPen = pDC->SelectObject(&newPen);
													}
													  
													else if(i/ALLSIZE==1)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==2)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,0,255));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													
													else if(i/ALLSIZE==3)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,128,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==4)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(153,51,250));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==5)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==6)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(85,102,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==7)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(102,102,153));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													pDC->LineTo(value[i]);
												}
												//pDC->LineTo(value[i]); 
											
											}
										}
										else if(value[st_code_size].x==0&&value[st_code_size].y==0)
										{
											for(;value[st_code_size].x==0&&value[st_code_size].y==0;st_code_size++);
											st_code_size--;
											edit=1;
										}
										
									}
								}
								else 
								{
									
									if(dt_code_size==-1)
									{
										dt_code_size=0;
										
									}
										
								}
									

							}
							if(dt_code_size!=-1)
							{
								
								if(dt_size!=0)
								{
									value=dt_value;
									pDC->MoveTo(value[0]);
									if(dt_code_size<dt_size)
									{
										dt_code_size++;

									}
									for(int i=0;i<dt_code_size;i++)
									{
										if(value[i].x>=1000*point_width||value[i].y>=1000*point_height||i>=dt_size-1)
										{
											if(et_code_size==-1)
											et_code_size=0;
											break;
											
										}
											
										if(value[i].x!=0||value[i].y!=0)
										{
											if((i+1)%20==0)
											{pDC->MoveTo(value[i]);}
											else 
											{
												
												if(value[i].x==2&&value[i].y==2)
												{
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(500*point_width,725*point_height);
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(600*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==2)
												{
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(300*point_width,725*point_height);
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(400*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==3)
												{
													pDC->MoveTo(300*point_width,725*point_height);
													pDC->LineTo(300*point_width,675*point_height);
													pDC->MoveTo(400*point_width,725*point_height);
													pDC->LineTo(400*point_width,675*point_height);
												}
												else if(value[i].x==2&&value[i].y==3)
												{
													pDC->MoveTo(500*point_width,725*point_height);
													pDC->LineTo(500*point_width,675*point_height);
													pDC->MoveTo(600*point_width,725*point_height);
													pDC->LineTo(600*point_width,675*point_height);
												}
												else if(value[i].x==1&&value[i].y==4)
												{
													pDC->MoveTo(300*point_width,675*point_height);
													pDC->LineTo(300*point_width,625*point_height);
													pDC->MoveTo(400*point_width,675*point_height);
													pDC->LineTo(400*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==4)
												{
													pDC->MoveTo(500*point_width,675*point_height);
													pDC->LineTo(500*point_width,625*point_height);
													pDC->MoveTo(600*point_width,675*point_height);
													pDC->LineTo(600*point_width,625*point_height);
												}
												else if(value[i].x==1&&value[i].y==5)
												{
													pDC->MoveTo(300*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
													pDC->MoveTo(400*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==5)
												{
													pDC->MoveTo(500*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
													pDC->MoveTo(600*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
												}
												else if(value[i].x==0&&value[i].y==8)
												{
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(300*point_width,525*point_height);
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(400*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(500*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(600*point_width,525*point_height);
												}
												else if(value[i].x==0&&value[i].y==9)
												{
													pDC->MoveTo(300*point_width,525*point_height);
													pDC->LineTo(350*point_width,475*point_height);
													pDC->MoveTo(400*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(500*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(600*point_width,525*point_height);
													pDC->LineTo(550*point_width,475*point_height);
												}
												else if(value[i].x==0&&value[i].y==10)
												{
													pDC->MoveTo(350*point_width,475*point_height);
													pDC->LineTo(400*point_width,425*point_height);
													pDC->MoveTo(550*point_width,475*point_height);
													pDC->LineTo(500*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==11)
												{
													pDC->MoveTo(400*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
													pDC->MoveTo(500*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==14)
												{
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(400*point_width,325*point_height);
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==15)
												{
													pDC->MoveTo(400*point_width,325*point_height);
													pDC->LineTo(400*point_width,275*point_height);
													pDC->MoveTo(500*point_width,275*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==16)
												{
													pDC->MoveTo(400*point_width,275*point_height);
													pDC->LineTo(400*point_width,225*point_height);
													pDC->MoveTo(500*point_width,325*point_height);
													pDC->LineTo(500*point_width,225*point_height);
												}
												else if(value[i].x==0&&value[i].y==17)
												{
													pDC->MoveTo(400*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
													pDC->MoveTo(500*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
												}
												else
												{
													if(i/ALLSIZE==0)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(128,42,42)); 
														 pOldPen = pDC->SelectObject(&newPen);
													}
													  
													else if(i/ALLSIZE==1)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(160,32,640));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==2)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,192,203));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													
													else if(i/ALLSIZE==3)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,128,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==4)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(153,51,250));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==5)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==6)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(85,102,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==7)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,51,153));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													pDC->LineTo(value[i]);
												}
												//pDC->LineTo(value[i]); 
											
											}
										}
										else if(value[dt_code_size].x==0&&value[dt_code_size].y==0)
										{
											for(;value[dt_code_size].x==0&&value[dt_code_size].y==0;dt_code_size++);
											dt_code_size--;
											edit=1;
										}

										
									}
								}
								else 
								{
									
									if(et_code_size==-1)
									{
										edit=1;
										et_code_size=0;

									}
												}
									

							}
							
							if(et_code_size!=-1)
							{
								value=et_value;
								if(et_size!=0)
								{
									pDC->MoveTo(value[0]);
									if(et_code_size<et_size)
									{
										et_code_size++;

									}
									for(int i=0;i<et_code_size;i++)
									{
										if(value[i].x>=1000*point_width||value[i].y>=1000*point_height||i>=et_size-1)
										{
											break;
											//et_code_size=0;
										}
											
										if(value[i].x!=0||value[i].y!=0)
										{
											if((i+1)%20==0)
											{pDC->MoveTo(value[i]);}
											else 
											{
												
												if(value[i].x==2&&value[i].y==2)
												{
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(500*point_width,725*point_height);
													pDC->MoveTo(550*point_width,725*point_height);
													pDC->LineTo(600*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==2)
												{
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(300*point_width,725*point_height);
													pDC->MoveTo(350*point_width,725*point_height);
													pDC->LineTo(400*point_width,725*point_height);
												}
												else if(value[i].x==1&&value[i].y==3)
												{
													pDC->MoveTo(300*point_width,725*point_height);
													pDC->LineTo(300*point_width,675*point_height);
													pDC->MoveTo(400*point_width,725*point_height);
													pDC->LineTo(400*point_width,675*point_height);
												}
												else if(value[i].x==2&&value[i].y==3)
												{
													pDC->MoveTo(500*point_width,725*point_height);
													pDC->LineTo(500*point_width,675*point_height);
													pDC->MoveTo(600*point_width,725*point_height);
													pDC->LineTo(600*point_width,675*point_height);
												}
												else if(value[i].x==1&&value[i].y==4)
												{
													pDC->MoveTo(300*point_width,675*point_height);
													pDC->LineTo(300*point_width,625*point_height);
													pDC->MoveTo(400*point_width,675*point_height);
													pDC->LineTo(400*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==4)
												{
													pDC->MoveTo(500*point_width,675*point_height);
													pDC->LineTo(500*point_width,625*point_height);
													pDC->MoveTo(600*point_width,675*point_height);
													pDC->LineTo(600*point_width,625*point_height);
												}
												else if(value[i].x==1&&value[i].y==5)
												{
													pDC->MoveTo(300*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
													pDC->MoveTo(400*point_width,625*point_height);
													pDC->LineTo(350*point_width,625*point_height);
												}
												else if(value[i].x==2&&value[i].y==5)
												{
													pDC->MoveTo(500*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
													pDC->MoveTo(600*point_width,625*point_height);
													pDC->LineTo(550*point_width,625*point_height);
												}
												else if(value[i].x==0&&value[i].y==8)
												{
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(300*point_width,525*point_height);
													pDC->MoveTo(350*point_width,525*point_height);
													pDC->LineTo(400*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(500*point_width,525*point_height);
													pDC->MoveTo(550*point_width,525*point_height);
													pDC->LineTo(600*point_width,525*point_height);
												}
												else if(value[i].x==0&&value[i].y==9)
												{
													pDC->MoveTo(300*point_width,525*point_height);
													pDC->LineTo(350*point_width,475*point_height);
													pDC->MoveTo(400*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(500*point_width,525*point_height);
													pDC->LineTo(450*point_width,475*point_height);
													pDC->MoveTo(600*point_width,525*point_height);
													pDC->LineTo(550*point_width,475*point_height);
												}
												else if(value[i].x==0&&value[i].y==10)
												{
													pDC->MoveTo(350*point_width,475*point_height);
													pDC->LineTo(400*point_width,425*point_height);
													pDC->MoveTo(550*point_width,475*point_height);
													pDC->LineTo(500*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==11)
												{
													pDC->MoveTo(400*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
													pDC->MoveTo(500*point_width,425*point_height);
													pDC->LineTo(450*point_width,425*point_height);
												}
												else if(value[i].x==0&&value[i].y==14)
												{
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(400*point_width,325*point_height);
													pDC->MoveTo(450*point_width,325*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==15)
												{
													pDC->MoveTo(400*point_width,325*point_height);
													pDC->LineTo(400*point_width,275*point_height);
													pDC->MoveTo(500*point_width,275*point_height);
													pDC->LineTo(500*point_width,325*point_height);
												}
												else if(value[i].x==0&&value[i].y==16)
												{
													pDC->MoveTo(400*point_width,275*point_height);
													pDC->LineTo(400*point_width,225*point_height);
													pDC->MoveTo(500*point_width,325*point_height);
													pDC->LineTo(500*point_width,225*point_height);
												}
												else if(value[i].x==0&&value[i].y==17)
												{
													pDC->MoveTo(400*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
													pDC->MoveTo(500*point_width,225*point_height);
													pDC->LineTo(450*point_width,225*point_height);
												}
												else
												{
													if(i/ALLSIZE==0)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,255,0)); 
														 pOldPen = pDC->SelectObject(&newPen);
													}
													  
													else if(i/ALLSIZE==1)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,0,0));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==2)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,0,255));  
														pOldPen = pDC->SelectObject(&newPen);
													}
													
													else if(i/ALLSIZE==3)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(255,128,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==4)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(153,51,250));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													else if(i/ALLSIZE==5)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,255));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else if(i/ALLSIZE==6)
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(85,102,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													else
													{
														 pDC->SelectObject(pOldPen);   
														// 删除新画笔   
														newPen.DeleteObject(); 
														newPen.CreatePen(PS_SOLID, 6, RGB(0,255,0));
														pOldPen = pDC->SelectObject(&newPen);
													}
													 
													pDC->LineTo(value[i]);
												}
												//pDC->LineTo(value[i]); 
											
											}
										}
										else if(value[et_code_size].x==0&&value[et_code_size].y==0)
										{
											for(;value[et_code_size].x==0&&value[et_code_size].y==0;et_code_size++);
											et_code_size--;
											edit=1;
										}
										
									}
								}

							}


						    
						  
						    // 将当前点移动到绘图控件窗口的左下角，以此为波形的起始点  
							
							//pDC->MoveTo
						    // 恢复旧画笔   
						    pDC->SelectObject(pOldPen);   
						    // 删除新画笔   
						    newPen.DeleteObject();   
						}

						//根据步骤数输出微指令
						void CTipDlg::outMorderByStep () {
							if (m_order_step_counter == 14){
								return ;
							}
							else if (m_order_step_counter == m_order_step_counter_copy){
								// //out the morder in the pic
								// CPaintDC dc(this); // device context for painting  
								// CDC *pDC1 = GetDC();
						  //       // 设置文本颜色
						  //       dc.SetTextColor(RGB(71,71,71));
						  //       // 在指定位置输出文本 

						  //       if (m_order_step_counter!=1) {
						  //       	for (int i=0;mOrders[m_order_step_counter-2][i].str!=_T("\n\n");i++){
							 //        	pDC1->TextOut(mOrders[m_order_step_counter-2][i].x*10*point_width,mOrders[m_order_step_counter-2][i].y*10*point_height,PRE.str);
							 //        }
						  //       }
						  //       for (int i=0;mOrders[m_order_step_counter-1][i].str!=_T("\n\n");i++){
						  //       	pDC1->TextOut(mOrders[m_order_step_counter-1][i].x*10*point_width,mOrders[m_order_step_counter-1][i].y*10*point_height,mOrders[m_order_step_counter-1][i].str);
						  //       }
							}
							else if (m_order_step_counter != m_order_step_counter_copy) {
								outMOrderArray(mOrders[m_order_step_counter-1]);

								// out the morder in the pic
								CPaintDC dc(this); // device context for painting  
								CDC *pDC1 = GetDC();
						        // 设置文本颜色
						        dc.SetTextColor(RGB(71,71,71));
						        // 在指定位置输出文本 

						        if (m_order_step_counter!=1) {
						        	for (int i=0;mOrders[m_order_step_counter-2][i].str!=_T("\n\n");i++){
							        	pDC1->TextOut(mOrders[m_order_step_counter-2][i].x*10*point_width,mOrders[m_order_step_counter-2][i].y*10*point_height,PRE.str);
							        }
						        }
						        for (int i=0;mOrders[m_order_step_counter-1][i].str!=_T("\n\n");i++){
						        	pDC1->TextOut(mOrders[m_order_step_counter-1][i].x*10*point_width,mOrders[m_order_step_counter-1][i].y*10*point_height,mOrders[m_order_step_counter-1][i].str);
						        }

								m_order_step_counter_copy++;
							}
							return ;
						}

						//输出一条操作对应的微指令
						void CTipDlg::outMOrderArray (mOrder * order) {
							int counter = 0;
							for (;(order[counter]).str !=  _T("\n\n");counter++) {
								editorOutMOrder(order[counter]);
								editorOutMOrder(NEXT);
							}
							editorOutMOrder(OVER);
							editorOutMOrder(OVER);
							return ;
						}

						//在编辑框中输出一条微指令字符
						void CTipDlg::editorOutMOrder (mOrder order) {
								CEdit * edit = (CEdit*)GetDlgItem(IDC_EDIT1);
								int start,end;
								edit->GetSel(start,end);
								edit->SetSel(end+1,end+150);
								edit->ReplaceSel(order.str);
						}


						//寻址方式及寄存器ar_key转换
						CString * CTipDlg::transAddressandRegister (int ar_key[2],address_register & ar,CString *& function,int op_type, bool is_source){
							CString AM;
							CString R;
							switch (ar_key[0]) {
								case 0:
								AM = "direct";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_direct;
										break;
										case 5:
											function = jsr_s_direct;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_direct;
										break;
										case 2:
											function = mov_d_direct;
										break;
										case 3:
											function = s_d_direct;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									case 4:
									R = "SP";
									break;
									case 5:
									R = "PC";
									break;
									case 6:
									R = "PSW";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 1:
								AM = "indirect";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_indirect;
										break;
										case 5:
											function = jsr_s_indirect;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_indirect;
										break;
										case 2:
											function = mov_d_indirect;
										break;
										case 3:
											function = s_d_indirect;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 2:
								AM = "minus_indirect";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_minus_indirect;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_minus_indirect;
										break;
										case 2:
											function = mov_d_minus_indirect;
										break;
										case 3:
											function = s_d_minus_indirect;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									case 4:
									R = "SP";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 3:
								AM = "plus_indirect";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_plus_indirect;
										break;
										case 5:
											function = jsr_s_plus_indirect;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_plus_indirect;
										break;
										case 2:
											function = mov_d_plus_indirect;
										break;
										case 3:
											function = s_d_plus_indirect;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									case 4:
									R = "SP";
									break;
									case 5:
									R = "PC";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 4:
								AM = "unstable_indirect";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_unstable_indirect;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_unstable_indirect;
										break;
										case 2:
											function = mov_d_unstable_indirect;
										break;
										case 3:
											function = s_d_unstable_indirect;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									case 4:
									R = "PC";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 5:
								AM = "double_indirect";
								if (is_source == true){
									switch (op_type) {
										case 1:
										case 2:
											function = d_s_double_indirect;
										break;
										default:
										break;
									}
								}
								else {
									switch (op_type) {
										case 1:
											function = d_d_double_indirect;
										break;
										case 2:
											function = mov_d_unstable_indirect;
										break;
										default:
										break;
									}
								}
								switch (ar_key[1]) {
									case 0:
									R = "R0";
									break;
									case 1:
									R = "R1";
									break;
									case 2:
									R = "R2";
									break;
									case 3:
									R = "R3";
									break;
									case 4:
									R = "PC";
									break;
									default:
									R = "ERROR";
									break;
								}
								break;
								case 6:
								AM = "SKP";
								break;
								default:
								AM = "ERROR";
								R = "ERROR";
								break;
							}
							ar.AM = AM;
							ar.R = R;
							return function;
						}

						//操作op_key转换
						CString CTipDlg::transOperator (int po_key) {
							CString OP;
							switch(po_key) {
								case 0:
								OP = " MOV ";
								break;
								case 1:
								OP = " ADD ";
								break;
								case 2:
								OP = " SUB ";
								break;
								case 3:
								OP = " AND ";
								break;
								case 4:
								OP = " OR ";
								break;
								case 5:
								OP = " EOR ";
								break;
								case 6:
								OP = " COM ";
								break;
								case 7:
								OP = " NEG ";
								break;
								case 8:
								OP = " ING ";
								break;
								case 9:
								OP = " DEC ";
								break;
								case 10:
								OP = " SL ";
								break;
								case 11:
								OP = " SR ";
								break;
								case 12:
								OP = " JMP ";
								break;
								case 13:
								OP = " RST ";
								break;
								case 14:
								OP = " JSR ";
								break;
								default :
								OP = "ERROR";
								break;
							}
							return OP;
						}

						//指令处理
						void CTipDlg::handleArray (CString * s) {
							if (s[0] == "||") {
								if (step == 0){
									outPutString(_T("取指周期为NULL"));
									step++;
									outPutString(_T("\n\n"));
									outPutString(_T("\n\n"));
									handleArray(source);
								}
								else if (step == 1) {
									outPutString(_T("源周期为NULL"));
									step++;
									outPutString(_T("\n\n"));
									outPutString(_T("\n\n"));
									handleArray(destination);
								}
								else if (step == 2) {
									outPutString(_T("目的周期为NULL"));
									step++;
									outPutString(_T("\n\n"));
									outPutString(_T("\n\n"));
									handleArray(execution);
								}
								else if (step == 3) {
									outPutString(_T("操作周期为NULL"));
									step++;
								}
								return ;
							}
							else {
								if (step == 0&&programStep == 0){
									outPutString(_T("取指周期"));
									outPutString(_T("\n\n"));
								}
								else if (step == 1&&programStep == 0) {
									outPutString(_T("源周期"));
									outPutString(_T("\n\n"));
								}
								else if (step == 2&&programStep == 0) {
									outPutString(_T("目的周期"));
									outPutString(_T("\n\n"));
								}
								else if (step == 3&&programStep == 0) {
									outPutString(_T("操作周期"));
									outPutString(_T("\n\n"));
								}
								for (;;) {
									if (s[programStep] == "|"){
										outPutString(_T("\n\n"));
										programStep++;
										return ;
									}
									else if (s[programStep] == "||"){
										outPutString(_T("\n\n"));
										outPutString(_T("\n\n"));
										step++;
										programStep = 0;
										return ;
									}
									else {
										outPutString(s[programStep]);
										programStep++;
									}
								}
							}
						}

						//输出指令中的一个CString元素
						void CTipDlg::outPutString (CString orderString) {
								CEdit * edit = (CEdit*)GetDlgItem(IDC_EDIT2);
								int start,end;
								edit->GetSel(start,end);
								edit->SetSel(end+1,end+150);
								edit->ReplaceSel(orderString);
						}

						//输出指令
						void CTipDlg::OutputOrders (int addressing_st[2],int addressing_dt[2],int opcode) {
							
							int ar_key1[2] ;
							ar_key1[0] = addressing_st[0];
							ar_key1[1] = addressing_st[1];
							int ar_key2[2] ;
							ar_key2[0] = addressing_dt[0];
							ar_key2[1] = addressing_dt[1];
							int op_n = opcode;

							address_register ar1 ,ar2;

							OP = transOperator (op_n);

							//对op_type的赋值
							if (OP == " ADD "||OP == " SUB "||OP == " AND "||OP == " OR "||OP == " EOR ") {op_type = 1;}
							else if (OP == " MOV ") {op_type =2;}
							else if (OP == " COM "||OP == " NEG "||OP == " ING "||OP == " DEC "||OP == " SL "||OP == " SR "){op_type = 3;}
							else if (OP == " JMP "||OP == " RST ") {op_type = 4;}
							else if (OP == " JSR ") {op_type = 5;}

							//操作码(OP)、源地址取指(source)、目的地址取指(destination) 赋值
							fetch = empty;
							source = empty;
							destination = empty;
							execution = empty;
							
							transAddressandRegister (ar_key1,ar1,source,op_type,true);
							transAddressandRegister (ar_key2,ar2,destination,op_type,false);

							Ri = ar1.R;
							Rj = ar2.R;

							//给fetch source destination execution 赋值
							//fetch赋值
							fetch = d_f_universal;

							//execution 赋值
							switch (op_type) {
								case 1:
									if (ar1.AM == "direct"){
										if (ar2.AM == "direct"){
											execution = d_e_dd;
										}
										else {
											execution = d_e_di;
										}
									}
									else if (ar2.AM == "direct"){
										execution = d_e_id;
									}
									else {
										execution = d_e_ii;
									}
								break;
								case 2:
									if (ar1.AM == "direct"){
										if (ar2.AM == "direct"){
											execution = mov_e_dd;
										}
										else {
											execution = mov_e_di;
										}
									}
									else if (ar2.AM == "direct"){
										execution = mov_e_id;
									}
									else {
										execution = mov_e_ii;
									}
								break;
								case 3:
									if (ar2.AM == "direct"){
										execution = s_e_d;
									}
									else {
										execution = s_e_i;
									}
								break;
								case 4:
									if (ar1.AM == "direct"){execution = jmp_e_d;}
									else if (ar1.AM == "indirect"){execution = jmp_e_i;}
									else if (ar1.AM == "plus_indirect"){execution = jmp_e_pi;}
									else if (ar1.AM == "unstable_indirect"){execution = jmp_e_ui;}
									else {
										cout<<"ERROR"
											<<endl;
									}
								break;
								case 5:
									if (ar1.AM == "direct"){
										execution = jsr_e_d;
									}
									else {
										execution = jsr_e_i;
									}
								break;
								default:
								break;
							}

							//处理source destination execution 的变量(Ri,Rj)
							for (int i = 0;source[i] != "||";i++){
								if (source[i] == "Ri"){
									source[i] = Ri;
								}
							}
							for (int i = 0;destination[i] != "||";i++){
								if (destination[i] == "Rj"){
									destination[i] = Rj;
								}
							}
							for (int i = 0;execution[i] != "||";i++){
								if (execution[i] == "Ri"){
									execution[i] = Ri;
								}
								else if (execution[i] == "Rj") {
									execution[i] = Rj;
								}
								else if (execution[i] == "OP") {
									execution[i] = OP;
								}
							}

							return ;
						}

						void CTipDlg::OnPaint()
						{
							
							CRect rectPicture;
							m_picDraw.GetClientRect(&rectPicture);   
							float point_width=(float)rectPicture.Width() / (POINT - 1);
							float point_height=(float)rectPicture.Height() / (POINT- 1);
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
							}
							else
							{
								CPaintDC dc(this); // device context for painting  
								// 设置m_newFont对象的字体为当前字体，并将之前的字体指针保存到m_pOldFont   
						        // 设置   
						        dc.SetBkMode(TRANSPARENT); //设置背景为透明！   
						        // 设置文本颜色
						        dc.SetTextColor(RGB(71,71,71));   
						        // 在指定位置输出文本 

						        dc.TextOut(150*point_width,170*point_height,_T("R0")); 
						        dc.TextOut(150*point_width,320*point_height,_T("R1")); 
						        dc.TextOut(150*point_width,470*point_height,_T("R2")); 
						        dc.TextOut(150*point_width,620*point_height,_T("R3")); 
						        dc.TextOut(150*point_width,770*point_height,_T("C")); 
						        dc.TextOut(150*point_width,920*point_height,_T("D")); 
						        dc.TextOut(750*point_width,170*point_height,_T("PSW")); 
						        dc.TextOut(750*point_width,320*point_height,_T("SP")); 
						        dc.TextOut(750*point_width,470*point_height,_T("PC")); 
						        dc.TextOut(750*point_width,620*point_height,_T("MDR")); 
						        dc.TextOut(750*point_width,770*point_height,_T("MAR")); 
						        dc.TextOut(750*point_width,935*point_height,_T("IR")); 
						        dc.TextOut(520*point_width,270*point_height,_T("SHIRFT")); 
						        dc.TextOut(430*point_width,645*point_height,_T("A")); 
						        dc.TextOut(630*point_width,645*point_height,_T("B")); 

						        CDialogEx::OnPaint();
							}
						}

						void CTipDlg::OnEnChangeEdit2()
						{
							// TODO:  如果该控件是 RICHEDIT 控件，它将不
							// 发送此通知，除非重写 CDialogEx::OnInitDialog()
							// 函数并调用 CRichEditCtrl().SetEventMask()，
							// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


							// TODO:  在此添加控件通知处理程序代码
						}

						void CTipDlg::outPutSteps () {
							if (step == 0){
								handleArray(fetch);
							}
							else if (step == 1){
								handleArray(source);
							}
							else if (step == 2){
								handleArray(destination);
							}
							else if (step == 3){
								handleArray(execution);
							}
						}


						void CTipDlg::OnEnChangeEdit1()
						{
							// TODO:  如果该控件是 RICHEDIT 控件，它将不
							// 发送此通知，除非重写 CDialogEx::OnInitDialog()
							// 函数并调用 CRichEditCtrl().SetEventMask()，
							// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

							// TODO:  在此添加控件通知处理程序代码
						}
