class dpPro {
//双操作数操作（不包括mov）
//取址周期
string f_universal[2][3] = {{"M","-->IR"},{"PC","+1","-->PC"}};

//源地址获取
string s_direct;

string s_indirect[2][3] = {{"Ri","-->MAR"},{"M","-->MDR","-->C"}};

string s_minus_indirect[2][5] = {{"Ri","-1","-->MAR",",","Ri"},{"M","-->MDR","-->C"}};

string s_plus_indirect[3][3] = {{"Ri","-->MAR"},{"M","-->MDR","-->C"},{"Ri","+1","-->Ri"}};

string s_unstable_inderect[5][3] = {{"PC","-->MAR"},{"M","-->MDR","-->C"},{"PC","+1","-->PC"},{"C","+Ri","-->MAR"},{"M","-->MDR","-->C"}};

//目的地址获取
string d_direct;

string d_indirect[2][3] = {{"Rj","-->MAR"},{"M","-->MDR","-->D"}};

string d_minus_indirect[2][5] = {{"Rj","-1","-->MAR",",","Rj"},{"M","-->MDR","-->D"}};

string d_plus_indirect[3][3] = {{"Rj","-->MAR"},{"M","-->MDR","-->D"},{"Rj","+1","-->Rj"}};

string d_unstable_inderect[5][3] = {{"PC","-->MAR"},{"M","-->MDR","-->D"},{"PC","+1","-->PC"},{"D","+Rj","-->MAR"},{"M","-->MDR","-->D"}};

//执行周期
string e_dd[2][4] = {{"Ri","OP","Rj","-->Rj"},{"PC","-->MAR"}};

string e_di[3][4] = {{"Ri","OP","D","-->MDR"},{"MDR","M"},{"PC","-->MAR"}};

string e_id[2][4] = {{"C","OP","Rj","-->Rj"},{"PC","-->MAR"}};

string e_ii[3][4] = {{"C","OP","D","-->MDR"},{"MDR","-->M"},{"PC","-->MAR"}};

};

switch(key) {
	case 0:
	PO = "MOV";
	break;
	case 1:
	PO = "ADD";
	break;
	case 2:
	PO = "SUB";
	break;
	case 3:
	PO = "AND";
	break;
	case 4:
	PO = "OR";
	break;
	case 5:
	PO = "EOR";
	break;
	case 6:
	PO = "COM";
	break;
	case 7:
	PO = "NEG";
	break;
	case 8:
	PO = "ING";
	break;
	case 9:
	PO = "DEC";
	break;
	case 10:
	PO = "SL";
	break;
	case 11:
	PO = "SR";
	break;
	case 12:
	PO = "JMP";
	break;
	case 13:
	PO = "RST";
	break;
	case 14:
	PO = "JSR";
	break;
	default :
	PO = "ERROR";
	break;
}



/*变量名称：
Ri
Rj
PC
M
OP
-->IR
-->Rj
-->D
-->PC
-->MAR
-->MDR
-->C
-1(Rj-1)
+1(PC+1,Rj+1)
*/