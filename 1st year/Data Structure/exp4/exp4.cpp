#include <stdio.h>
#include <stdlib.h>

#define maxnum 100 

int input (int res[]) {
	int num;
	char c=NULL;

	for (num=0;c!='\n'&&num<=maxnum;num++) {
		scanf ("%d",&res[num+1]);
		c=getchar();
	}

	return num;
}

void fastArrange (int res[],int f,int e) {
	int i=f,j=e;
	int a;

	a=res[i];
	while (1){

		for (;i<j&&res[j]>=a;j--);
		if (i!=j){res[i]=res[j];}
		else break;

		for (;i<j&&res[i]<=a;i++);
		if (i!=j){res[j]=res[i];}
		else break;
	}

	res[i]=a;
	
	if (f<j-1)
		fastArrange (res,f,j-1);
	
	if (i+1<e)
		fastArrange (res,i+1,e);
	
	return;
}

void print_List (int res[],int num) {
	int i;

	printf ("\n");

	for (i=1;i<=num;i++){
		printf ("%d\t",res[i]);
	}

	return;
}

void search_List (int res[],int f,int e) {
	int i=f,j=e,mid;
	int n;

	printf ("\n\nplease enter the number you want:\n");
	scanf ("%d",&n);

	for (;i<=j;) {
		mid=(i+j)/2;
		if (res[mid]==n){
			printf ("\ni find the number!\n");
			i=0;
			break;
		}
		else if (res[mid]>n)
			j=mid-1;
		else 
			i=mid+1;
	}

	if (i!=0) printf ("\nsorry ,you don't have the number.\n");

	return;
}

int main (void) {
	int resource[maxnum+1];
	int num,n;

	num=input (resource);

	fastArrange (resource,1,num);

	print_List (resource,num);

	for (;;){
		printf ("\nplease enter your order:(1 for search;others for exit)\n");
		scanf ("%d",&n);

		switch (n) {
		case 1:
			search_List (resource,1,num);
			break;
		default:
			system("pause");
			return 0;
		}
	}

}