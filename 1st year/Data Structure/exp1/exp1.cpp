#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Status  int
#define success 1
#define fatal   0

typedef struct stuInfo {
	char  stuName[10];      /*学生姓名*/
	int    Age  ;	/*年龄*/
	} Elemtype;
typedef struct node {
	Elemtype  data;
	struct  node  *next;
} Listnode, *Listptr;
typedef struct stack {
	Listptr top;
}stack,*stackptr;

Status Creat_node (Listptr a) {
	a=(Listptr)malloc(sizeof(Listnode));

	if (a!=NULL) return success;
	else printf ("Error");
	return fatal;
}

Listptr Insert (Listptr m,Listptr p){
	Listptr n,q;
	n=m;q=p; //保存 m、q
	m->next=p;

	if (m->data.Age>=p->data.Age) {m->next=p; return m;}

	while (1) {
		if (!p->next) {p->next=m;m->next=NULL;return q;}
		else if (m->data.Age==p->next->data.Age&&strcmp(m->data.stuName,p->next->data.stuName)==0){free(m); return q;}
		else if (m->data.Age>=p->next->data.Age){
			m->next=p->next;
			p->next=m;
			return q;
		}
		else p=p->next;
	}
}

void Delet (stackptr s){
	Listptr p,q;
	q=s->top;
	p=q->next;
	while (p){
		free(q);
		q=p;
		p=q->next;
	}
	if (!p) free(q);
}

void Rest (Listptr n,Listptr m,stackptr s){
	while (n){
		s->top=n;
		n=n->next;
		s->top->next=m;
		m=s->top;
	}
	return;
}

void View (Listptr m,stackptr s){
	if (!m)
		printf ("NULL");
	else m=s->top;

	while (m!=NULL){
		printf ("Student Name:%s\t",m->data.stuName);
		printf ("Age:%d\n",m->data.Age);
		m=m->next;
	}
	return;
}

int main (){
	Listptr L1,L2,L;
	Listptr p,q,m;
	stackptr s;
	int n;

	char c;

	printf ("please enter the names and ages of the First list (example:AnMing 19 XiaoHuang 20):\n");
	L1=(Listptr)malloc(sizeof(Listnode));
	L1->next=NULL;
	scanf (" %s %d",L1->data.stuName,&L1->data.Age);
	p=L1;
	while (getchar()!='\n'){
		q=(Listptr)malloc(sizeof(Listnode));
		q->next=NULL;
		scanf (" %s %d",q->data.stuName,&q->data.Age);
		p->next=q;
		p=q;
	}
	
	printf ("please enter the names and ages of the Second list (example:AnMing 19 XiaoHuang 20):\n");
	L2=(Listptr)malloc(sizeof(Listnode));
	L2->next=NULL;
	scanf (" %s %d",L2->data.stuName,&L2->data.Age);
	p=L2;
	while (getchar()!='\n'){
		q=(Listptr)malloc(sizeof(Listnode));
		q->next=NULL;
		scanf (" %s %d",q->data.stuName,&q->data.Age);
		p->next=q;
		p=q;
	}
	
	s=(stackptr)malloc(sizeof(stack));

	if (L1->data.Age<=L2->data.Age) {
		s->top=L1;
		m=s->top;
		p=L1->next;
		q=L2;
	}
	else {
		m=s->top=L2;
		q=L2->next;
		p=L1;
	}
	
	m->next=NULL;
	while (p&&q){
		if (p->data.Age==q->data.Age&&strcmp(p->data.stuName,q->data.stuName)==0) {
			s->top=p;
			p=p->next;
			q=q->next;
			s->top->next=m;
		}
		else if (p->data.Age<=q->data.Age) {
			s->top=p;
			p=p->next;
			s->top->next=m;
		}
		else {
			s->top=q;
			q=q->next;
			s->top->next=m;
		}
		m=s->top;
	}
	
	if (p==NULL) Rest (q,m,s);
	else Rest (p,m,s);
	
	View (m,s);
	m=s->top;
	for (;;){
		printf ("\nplease enter your order:\n'1'for view the list ;\n'2'for delet the list;\n'3'for insert a student info;\n'4' for exit\n");
		scanf("%d",&n);
		switch (n){
		case 1: 
			View(m,s);
			break;
		case 2:
			Delet(s);
			printf ("\nthe list is empty now.\n");
			system ("pause");
			return 0;
			break;
		case 3:
			printf ("please enter the new name and the age: (example: xiaohuang 19)\n");
			p=(Listptr)malloc(sizeof(Listnode));
			scanf (" %s %d",p->data.stuName,&p->data.Age);
			s->top=Insert(p,s->top);
			break;
		case 4:return 0;
		}
		m=s->top;
	}
}