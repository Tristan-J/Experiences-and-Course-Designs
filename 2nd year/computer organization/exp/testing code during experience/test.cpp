#include "testhead.h"

//int opcode 操作码
//int addressing_st[2] 源
//int addressing_dt[2] 目的

//寻址方式及寄存器ar_key转换
void transAddressandRegister (int ar_key[2],address_register & ar,string * function,int op_type, bool is_source){
	string AM;
	string R;
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
		AM = "UNKNOWN";
		// function = "UNKNOWN";
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
	return ;
}

//操作op_key转换
string transOperator (int po_key) {
	string OP;
	switch(po_key) {
		case 0:
		OP = "MOV";
		break;
		case 1:
		OP = "ADD";
		break;
		case 2:
		OP = "SUB";
		break;
		case 3:
		OP = "AND";
		break;
		case 4:
		OP = "OR";
		break;
		case 5:
		OP = "EOR";
		break;
		case 6:
		OP = "COM";
		break;
		case 7:
		OP = "NEG";
		break;
		case 8:
		OP = "ING";
		break;
		case 9:
		OP = "DEC";
		break;
		case 10:
		OP = "SL";
		break;
		case 11:
		OP = "SR";
		break;
		case 12:
		OP = "JMP";
		break;
		case 13:
		OP = "RST";
		break;
		case 14:
		OP = "JSR";
		break;
		default :
		OP = "ERROR";
		break;
	}
	return OP;
}

//指令处理
void handleArray (string * s) {
	int i = 1;
	for (i = 1;;i++){
		if (s[i-1] == "|"){
			cout<<"end of an order"
				<<endl;
		}
		else if (s[i-1] == "||"){
			cout<<"end of a block"
				<<endl;
			return ;
		}
		else {
			cout<<s[i-1]
				<<endl;
		}
	}
}

void main () {
	int ar_key1[2] = {1,3};
	int ar_key2[2] = {3,2};
	int op_n = 5;

	address_register ar1 ,ar2;

	//对op_type的赋值
	if (OP == "ADD"||OP == "SUB"||OP == "AND"||OP == "OR"||OP == "EOR") {op_type = 1;}
	else if (OP == "MOV") {op_type =2;}
	else if (OP == "COM"||OP == "NEG"||OP == "ING"||OP == "DEC"||OP == "SL"||OP == "SR"){op_type = 3;}
	else if (OP == "JMP"||OP == "RST") {op_type = 4;}
	else if (OP == "JSR") {op_type = 5;}

	//操作码(OP)、源地址取址(source)、目的地址取址(destination) 赋值
	fetch = empty;
	source = empty;
	destination = empty;
	execution = empty;
	
	OP = transOperator (op_n);
	transAddressandRegister (ar_key1,ar1,source,op_type,true);
	transAddressandRegister (ar_key2,ar2,destination,op_type,false);

	Ri = ar1.R;
	Rj = ar2.R;

//给fetch source destination execution 赋值
	//fetch赋值
	fetch = d_f_universal;

	//处理source destination 的变量(Ri,Rj)
	for (int i = 0;source[i] != "||";i++){
		if (source[i] == "Ri"){
			source[i] == Ri;
		}
	}
	for (int i = 0;destination[i] != "||";i++){
		if (source[i] == "Rj"){
			source[i] == Rj;
		}
	}

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

	handleArray(fetch);
	handleArray(source);
	handleArray(destination);
	handleArray(execution);

	system("pause");
	return ;
}