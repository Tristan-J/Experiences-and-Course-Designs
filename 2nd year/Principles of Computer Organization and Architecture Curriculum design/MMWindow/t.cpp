#include <stdio.h>
#include <math.h>
#include <string.h>

unsigned int BinToHex(char* str)
{
	unsigned int result = 0;
	int strLen = strlen(str)-1;
	while(*str!='\0')
	{
		result += ((*str)-'1'+1)*pow(2,strLen--);
		str++;
	}
	
	return result;
}

int main()
{
	char str[100] = "10100011000101;111;11;1000\n\
111";
	char delims[5] = ";\n";
	char* result = strtok(str,delims);
	while(result!=NULL)
	{
		printf("%d\n",BinToHex(result));
		result = strtok(NULL,delims);
	}
	
	return 0;
}