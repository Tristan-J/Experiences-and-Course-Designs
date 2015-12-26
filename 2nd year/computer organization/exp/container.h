#include <iostream>
#include <string.h>
#include <string>
#include <time.h>

using std::string;
using namespace std;

//取址周期
string f_universal[2][3] = {{"M","--IR"},{"PC","+1","--PC"}};

//源地址获取
string s_direct;

string s_indirect[2][3] = {{"Ri","--MAR"},{"M","--MDR","--C"}};

string s_minus_indirect[2][5] = {{"Ri","-1","--MAR",",","Ri"},{"M","--MDR","--C"}};

string s_plus_indirect[3][3] = {{"Ri","--MAR"},{"M","--MDR","--C"},{"Ri","+1","--Ri"}};

string s_unstable_inderect[5][3] = {{"PC","--MAR"},{"M","--MDR","--C"},{"PC","+1","--PC"},{"C","+Ri","--MAR"},{"M","--MDR","--C"}};

//目的地址获取
string d_direct;

string d_indirect[2][3] = {{"Rj","--MAR"},{"M","--MDR","--D"}};

string d_minus_indirect[2][5] = {{"Rj","-1","--MAR",",","Rj"},{"M","--MDR","--D"}};

string d_plus_indirect[3][3] = {{"Rj","--MAR"},{"M","--MDR","--D"},{"Rj","+1","--Rj"}};

string d_unstable_inderect[5][3] = {{"PC","--MAR"},{"M","--MDR","--D"},{"PC","+1","--PC"},{"D","+Rj","--MAR"},{"M","--MDR","--D"}};

//执行周期
string e_dd[3];

string 




/*
Rj
PC
M
--IR
--Rj
--D
--PC
--MAR
--MDR
--C
-1(Rj-1)
+1(PC+1,Rj+1)
*/