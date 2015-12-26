#include <stdio.h>
#include <stdlib.h>

#define maxnode 64
#define max     64
#define maxedgs 2016
#define extrem  10000

//�ڽӾ���ṹ����
typedef struct arcell {
	int adj;//�ߵ�Ȩֵ
	char *info;//�ߵ���Ϣ
}arcell,adjmatrix[max][max];

//ͼ�ı�ʾ
typedef struct {
	char vexs[max];//����
	adjmatrix arcs;//�ڽӾ���
	int vexnum,arcnum;//���㡢�ߵ���Ŀ
}mgraph_L;

//���ڵ�
typedef struct arc {
	int pre;
	int bak;
	int weight;
}edg;

//�ڽӱ���ͷ���
typedef struct {
	int data;//�ڵ���Ϣ
	edg *firstarc;//ָ���һ�������ڸýڵ�Ļ���ָ��
}vnode,adjlist;

//ͼ�Ķ���
typedef struct {
	adjlist vertices[max];//ͼ���ڽӱ�
	int vexnum,arcnum;//ͼ�Ķ�����������
}algraph;

int arcvisited [max];

int find(int arcvisited[],int f){
	while (arcvisited[f]){
		if (f==arcvisited[f])
			continue;
		f=arcvisited[f];
	}
	return f;
}

int input_G (adjmatrix G){
	int n;
	int i,j;

	printf ("pleaes tell me the number of weights in a line:");
	scanf ("%d",&n);
	printf ("please input the adjmatrix:\n(for example:\n0 2 3\n2 0 10000\n3 10000 0\nps:the value of edg is 10000 if the two vertexes are not conected directedly.)\n");

	for (i=0;i<n;i++){
		for (j=0;j<n;j++)
			scanf ("%d",&G[i][j].adj);
	}

	return n;
}

int kruscal (adjmatrix G,edg Edg[],int n){
	edg edgs[max];
	int i,j,k,m;
	int a,b;
	int record,e_num,v_num,e;

	//���ڽӾ���Ϊ�ߵ�����
	e_num=0;
	for (i=0;i<n;i++){
		for (j=i+1;j<n;j++){
			if (G[i][j].adj!=max){
				edgs[e_num].pre=i;
				edgs[e_num].bak=j;
				edgs[e_num].weight=G[i][j].adj;
				e_num++;
			}
		}
	}

	//��ʼ��arcvisited
	for (k=0;k<n;k++){
		arcvisited[k]=0;
	}

	//������С��
	e=1;
	for (v_num=1;v_num<n;){
		//Ѱ����СȨֵ�ı�
		m=extrem;
		for (k=0;k<e_num;k++){
			if (edgs[k].weight<=m){
				m=edgs[k].weight;
				i=edgs[k].pre;
				j=edgs[k].bak;
				record=k;
			}
		}
		//�ж��Ƿ�ɻ�
		a=find(arcvisited,i);
		b=find(arcvisited,j);
		if(a!=b){
			Edg[e-1]=edgs[record];
			arcvisited[i]=j;
			e++;
			v_num++;
		}
		edgs[record].weight=max;
	}

	return e;
}

void output (edg Edg[],int n){
	int i,j,k;

	printf("Here is the tree you want:\n");

	for (i=0;i<n-1;i++){
		printf ("V%d-V%d:%d\n",Edg[i].pre,Edg[i].bak,Edg[i].weight);
	}

	return;
}

int main (void){
	adjmatrix G;
	edg Edg[max];
	int n;

	n=input_G (G);

	n=kruscal(G,Edg,n);

	output(Edg,n);

	system("pause");
	return 0;
}