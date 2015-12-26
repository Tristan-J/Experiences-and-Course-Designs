#include <iostream>
#include <string.h>
#include <string>
using namespace std;

//public
	string Ri = "Ri";
	string Rj = "Rj";
	string OP = "OP";
	int op_type = 0 ;
	//0 for false ;1 for double;2 for mov,3 for single,4 for jmp and rst,5 for jrs

	//取址 源地址 目的地址 操作
	string *fetch , *source , *destination , *execution ;
	string *function;
	string empty[1] = {"||"};


//执行命令集合
//ADD,SUB,AND,OR,EOR,
//dpPro
	//双操作数操作（不包括mov）
	//取址周期
	string d_f_universal[4] = {"M-->IR","|","PC+1-->PC","||"};

	//源地址获取
	string d_s_direct[2] = {"寄存器寻址","||"};

	string d_s_indirect[5] = {Ri,"-->MAR","|","M-->MDR-->C","||"};

	string d_s_minus_indirect[6] = {Ri,"-1-->MAR,",Ri,"|","M-->MDR-->C","||"};

	string d_s_plus_indirect[9] = {Ri,"-->MAR","|","M-->MDR-->C","|",Ri,"+1-->",Ri,"||"};

	string d_s_unstable_indirect[12] = {"PC-->MAR","|","M-->MDR-->C","|","PC+1-->PC","|","C+",Ri,"-->MAR","|","M-->MDR-->C","||"};

	//目的地址获取
	string d_d_direct[2] = {"寄存器寻址","||"};

	string d_d_indirect[5] = {Rj,"-->MAR","|","M-->MDR-->D","||"};

	string d_d_minus_indirect[6] = {Rj,"-1-->MAR,",Rj,"|","M-->MDR-->D","||"};

	string d_d_plus_indirect[9] = {Rj,"-->MAR","|","M-->MDR-->D","|",Rj,"+1-->",Rj,"||"};

	string d_d_unstable_indirect[12] = {"PC-->MAR","|","M-->MDR-->D","|","PC+1-->PC","|","D+",Rj,"-->MAR","|","M-->MDR-->D","||"};

	//执行周期
	string d_e_dd[8] = {Ri,OP,Rj,"-->",Rj,"|","PC-->MAR","||"};

	string d_e_di[8] = {Ri,OP,"D-->MDR-->M","|","PC-->MAR","||"};

	string d_e_id[8] = {"C",OP,Rj,"-->",Rj,"|","PC-->MAR","||"};

	string d_e_ii[8] = {"C",OP,"D-->MDR-->M","|","PC-->MAR","||"};

//MOV
//MOV
	//取址周期
	string mov_f_universal[4] = {"M-->IR","|","PC+1-->PC","||"};

	//源地址获取同其他双操作数操作

	//目的地址获取
	string mov_d_direct[2] = {"寄存器寻址","||"};

	string mov_d_indirect[3] = {Rj,"-->MAR","||"};

	string mov_d_minus_indirect[4] = {Rj,"-1-->MAR,",Rj,"||"};

	string mov_d_plus_indirect[7] = {Rj,"-->MAR","|",Rj,"+1-->",Rj,"||"};

	string mov_d_unstable_indirect[10] = {"PC-->MAR","|","PC+1-->PC","|","M-->MDR-->D","|","D+",Rj,"-->MAR","||"};

	//执行周期
	string mov_e_dd[8] = {Ri,OP,Rj,"-->",Rj,"|","PC-->MAR","||"};

	string mov_e_di[8] = {Ri,OP,"D-->MDR-->M","|","PC-->MAR","||"};

	string mov_e_id[8] = {"C",OP,Rj,"-->",Rj,"|","PC-->MAR","||"};

	string mov_e_ii[8] = {"C",OP,"D-->MDR-->M","|","PC-->MAR","||"};


//COM,NEG,ING,DEC,SL,SR
// spPro

	//取址周期
	string s_f_universal[4] = {"M-->IR","|","PC+1-->PC","||"};

	//目的地址获取
	string s_d_direct[2] = {"寄存器寻址","||"};

	string s_d_indirect[5] = {Rj,"-->MAR","|","M-->MDR-->D","||"};

	string s_d_minus_indirect[6] = {Rj,"-1-->MAR,",Rj,"|","M-->MDR-->D","||"};

	string s_d_plus_indirect[9] = {Rj,"-->MAR","|","M-->MDR-->D","|",Rj,"+1-->",Rj,"||"};

	string s_d_unstable_indirect[12] = {"PC-->MAR","|","M-->MDR-->D","|","PC+1-->PC","|","D+",Rj,"-->MAR","|","M-->MDR-->D","||"};

	//执行周期
	string s_e_d[7] = {OP,Rj,"-->",Rj,"|","PC-->MAR","||"};

	string s_e_i[7] = {OP,"D-->MDR-->M","|","PC-->MAR","||"};


//JMP,RST
//jmpPro 

	//取址周期
	string jmp_f_universal[4] = {"M-->IR","|","PC+1-->PC","||"};

	//执行周期
	string jmp_e_d[3] = {Ri,"-->PC,MAR","||"};

	string jmp_e_i[5] = {Ri,"-->MAR","|","M-->MDR-->PC,MAR","||"};

	string jmp_e_pi[9] = {Ri,"-->MAR","|","M-->MDR-->PC,MAR","|",Ri,"+1-->",Ri,"||"};

	string jmp_e_ui[9] = {"PC-->MAR","|","M-->MDR-->C","|","C+",Ri,"-->MAR","-->PC","||"};

//JSR
//jsrPro
	//取址周期
	string jsr_f_universal[4] = {"M-->IR","|","PC+1-->PC","||"};
	//源地址获取
	string jsr_s_direct[2] = {"寄存器寻址","||"};

	string jsr_s_indirect[5] = {Ri,"-->MAR","|","M-->MDR-->C","||"};

	string jsr_s_plus_indirect[9] = {Ri,"-->MAR","|","M-->MDR-->C","|",Ri,"+1-->",Ri,"||"};

	//执行周期
	string jsr_e_d[9] = {"SP-1-->SP,MAR","|","PC-->MDR-->M","|",Ri,"-->PC,MAR","||"};

	string jsr_e_i[8] = {"SP-1-->SP,MAR","|","PC-->MDR-->M","|","C-->PC,MAR","||"};


//寻址方式及寄存器类
class address_register {
public:
	string AM;
	string R;
	address_register () {}
	~address_register () {}
};

//寻址方式及寄存器ar_key转换
void transAddressandRegister (int ar_key[2],address_register & ar,string * function);

//操作op_key转换
string transOperator (int po_key);

//指令处理
void handleArray (string * s);