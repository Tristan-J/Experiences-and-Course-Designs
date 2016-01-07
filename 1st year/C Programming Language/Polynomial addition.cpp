#include <stdio.h>
#include <stdlib.h>

#define success 1
#define fatal   0
#define N       20
#define Status  int

typedef struct Term{
	float coef;
	int expn;
	struct Term *next;
}Term,*TermPtr;

TermPtr CreateList (TermPtr L,float Coef[],int Expn[],int n){

	Status status=success;
	TermPtr p,q;
	int i= n-1;

	while (i>=0){
		if (i==n-1){L=(TermPtr)malloc(sizeof(Term));}

		p=(TermPtr)malloc(sizeof(Term));

		if (!p||!L){status=fatal;break;}

		p->coef=Coef[i];
		p->expn=Expn[i];

		if (i==n-1){
			p->next=NULL;
			L->next=p;
			q=L;}
		else {
			p->next=q->next;
			q->next=p;
		}
		i--;
	}

	return L;
}

TermPtr AddPolyn(TermPtr L1,TermPtr L2,int i1,int i2){
	Status status=0,i=0;
	TermPtr n1,n2,m;
	
	n1=L1->next;
	if (!n1->next){
		status=1;
	}
	
	n2=L2->next;
	if (!n2->next){
		status=2;
	}

	m=n1;

	for (;;){
		switch (status){			
		case 0:
			if (n1->expn<n2->expn){
				L1=n1;
				n1=n1->next;

				i++;

				if (!n1->next){status=1;}
			}

			else if (n1->expn>n2->expn){

				if (i==0){m=n2;}
				i++;
				
				L1->next=n2;
				L1=L1->next;
				n2=n2->next;
				L1->next=n1;
				L2->next=n2;

				if (!n2->next){status=2;}
			}

			else{
				n1->coef=n1->coef+n2->coef;

				if (n1->coef==0){

					if (i==0){m=n1->next;}
					else{i++;}						

					n1=n1->next;
					free(L1->next);
					L1->next=n1;
					if (!n1->next){status=1;}

					L2=n2;
					n2=n2->next;
					if (!n2->next){status=2;}
				}
				else{
					L1=n1;
					n1=n1->next;
					if (!n1->next){status=1;}

					L2=n2;
					n2=n2->next;
					if (!n2->next){status=2;}

					i++;
				}
			}
			break;
			
		case 1:
			if (n1->expn<n2->expn){
				n1->next=n2;
				return m;
			}

			else if (n1->expn>n2->expn){
				L1->next=n2;
				L1=L1->next;
				L1->next=n1;

				i++;
				if (!n2->next){return m;}
			}

			else{
				n1->coef=n1->coef+n2->coef;

				if (!n2->next){return m;}
				else{
					n1->next=n2->next;
					return m;
				}

				if(n1->coef==0){
					n1=n2;
					free(L1->next);
					L1->next=n1;
					return m;
				}
			}
			break;
			
		case 2:
			if (n1->expn<n2->expn){
				L1=n1;
				n1=n1->next;
				i++;

				if (!n1->next){
					status=1;
					break;
				}
			}

			else if (n1->expn>n2->expn){
				L1->next=n2;
				L1->next->next=n1;
				return m;
			}

			else{
				n1->coef=n1->coef+n2->coef;
				if (n1->coef==0){
					free(n1);
				}
				return m;
			}
			break;
		}
	}
}

int main (void){
	float a1[N],a2[N];
	int b1[N],b2[N];
	int	i1=0,i2=0;
	Term n1,n2;
	TermPtr L1=NULL,L2=NULL;
	
	printf ("Please import the first multinomial(coef1|expn1,coef2|expn2...):\nF(x)=");

	for (char c=',';c==',';i1++){
		scanf (" %f",&a1[i1]);
		scanf (" %c",&c);
		scanf (" %d",&b1[i1]);
		c=getchar();
	}
	L1=CreateList (L1,a1,b1,i1);
	if (!L1){return 0;}

	printf ("\nPlease import the second multinomial(coef1|expn1,coef2|expn2...):\nG(x)=");

	for (char c=',';c==',';i2++){
		scanf (" %f",&a2[i2]);
		scanf (" %c",&c);
		scanf (" %d",&b2[i2]);
		c=getchar();
	}

	L2=CreateList (L2,a2,b2,i2);

	if (!L2){return 0;}
	else 
		L1=AddPolyn(L1,L2,i1,i2);

	printf ("the result is:\n");

	if (!L1->next)
		printf ("%fX^%d",L1->coef,L1->expn);

	for (;L1;L1=L1->next){
		if (L1->next)
			printf ("%fX^%d + ",L1->coef,L1->expn);
		else 
			printf ("%fX^%d",L1->coef,L1->expn);
	}

	system ("pause");
	return 0;
}