#include <stdio.h>
#include <stdlib.h>

#define maxbit 10
#define maxvalue 1000

typedef struct hnode  {
	int weight;
	int parent, lchild, rchild;
}hnode;

typedef struct hcode  {
	int bit[maxbit];
	int start;
}hcode;

void input (char *m) {
	int n=0;

	printf ("please enter the sentence (no more than 100 letters) :\n");

	do {
		scanf ("%c", &m[n]);
		n++;
	}while(m[n-1]!='\n');
	
	return;
}

int sumtheletters (char *m,int *p,int num) {
	int i,j,n;

	for (i=0;i<=99;i++){
		if ('a'<=m[i]&&'z'>=m[i]){
			p[m[i]-'a']++;
		}
		else if ('A'<=m[i]&&'Z'>=m[i]){
			p[26+m[i]-'A']++;
		}
		else if (m[i]==' '){
			p[52]++;
		}
		else if (m[i]=='!'){
			p[53]++;
		}
		else if (m[i]==','){
			p[54]++;
		}
		else if (m[i]=='.'){
			p[55]++;
		}
		else if (m[i]=='?'){
			p[56]++;
		}
	}

	for (i=0;i<26;i++){
		m[i]=char(i+'a');
	}
	for (i=0;i<26;i++){
		m[i+26]=char(i+'A');
	}
	m[52]=' ';
	m[53]='!';
	m[54]=',';
	m[55]='.';
	m[56]='?';

	for (i=0;i<(52+6);i++){
		if (!p[i])m[i]='0';
	}

	for (i=0,j=0,num=0,n=0;i<(52+6);i++){
		if (p[i])
			num++;
		else {
			j=i+n;
			while(!p[j]&&j<(52+6)){
				j++;
			}
			p[i]=p[j];
			p[j]=0;
			n=j-i;

			if (j<(52+6))
				num++;
			else return num;
		}
	}

	return num;
}

hcode* huffmancoding (hnode *ht, hcode *hc, int w[], int n) {
	int m, i, j;
	int m1, m2, x1, x2;
	int start, c, f;
	hnode *p;

	if (n<=1) return hc;

	m=2*n-1;

	ht= (hnode *) malloc (m*sizeof (hnode) );

	for (p=ht, i=1;i<n;++i, ++p, ++w) {
		(*p) .weight=*w;
		(*p) .lchild=-1;
		(*p) .rchild=-1;
		(*p) .parent=-1;
	}

	for (;i<=m;i++, p++) {
		(*p) .weight=0;
		(*p) .lchild=-1;
		(*p) .rchild=-1;
		(*p) .parent=-1;
	}

	for (i=n;i<m;i++) {

		m1=m2=maxvalue;
		x1=x2=0;

		for (j=0;j<i;j++) {

			if (ht[j].parent==-1&&ht[j].weight<m1) {
				m2=m1; x2=x1;
				m1=ht[j].weight; x1=j;
			}
			else if (ht[j].parent==-1&&ht[j].weight<m2) {
				m2=ht[j].weight;x2=j;
			}
		}
		ht[x1].parent=i; ht[x2].parent=i;
		ht[i].lchild=x1; ht[i].rchild=x2;
		ht[i].weight=m1+m2;
	}

	hc=(hcode *) malloc (n*sizeof(hcode));

	for (i=0;i<n;i++) {
		start=0;
		for (c=i, f=ht[i].parent;f != -1;c=f, f=ht[f].parent) {
			if (ht[f].lchild==c) 
				hc[i].bit[start++]=0;
			else 
				hc[i].bit[start++]=1;
		}
		hc[i].start=start-1;
	}

	return hc;
}

char* printthelist (hcode *hc,int num,char *m) {
	int i,j,k;

	printf ("\nhere is the huffman coding :\n");

	for (i=0,k=0;k<num;i++){
		if (m[i]=='0')
			continue;
		else {
			printf ("\n%c:\t",m[i]);
			for (j=hc->start;j>=0;j--){
				printf ("%d",hc->bit[j]);
			}
			hc++;
			k++;
		}
	}
	return m;
}

int main (void) {
	char m[100];
	int p[52+6+1]={0};
	int n,num=NULL;
	hnode *ht=NULL;
	hcode *hc=NULL;

	input (m);

	num=sumtheletters (m,p,num);

	hc=huffmancoding (ht,hc,p,num);

	printthelist (hc,num,m);

	system ("pause");
	return 0;
}