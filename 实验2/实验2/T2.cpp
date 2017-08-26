#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10
#define MAXINT 32767
char tmp[MAX][20];
typedef struct {
	char* cities[MAX];
	int edges[MAX][MAX];
	int n, e;
}Mgraph; //����ͼ���ڽӾ��󴢴�����
void CreateGraph(Mgraph *G)//�ڽӾ���ͼ�洢
{
	int x = 0;
	printf("���뽻ͨͼ�ĳ�����n����·��e��");
	scanf_s("%d %d", &G->n, &G->e);
	for (int i = 0;i<G->n;i++) //�ڽӾ�����0,�õ����г��е�����
	{
		printf("�������%d�����ƣ�", i + 1);
		scanf_s("%s", tmp[x], sizeof(tmp[x]));
		G->cities[x] = tmp[x];
		x++;
		for (int j = 0;j<G->n;j++)
			G->edges[i][j] = MAXINT;
	}
	for (int k = 0;k<G->e;k++)
	{
		char tmp[20];
		int i, j, d;
		printf("���������м�֮��ľ���\n");
		printf("�������1�����ƣ�");
		scanf_s("%s", tmp, sizeof(tmp));//�������1����
		for (int y = 0;y < G->n;y++)
		{
			if (strcmp(G->cities[y], tmp) == 0)
				i = y;
		}
		printf("�������2�����ƣ�");
		scanf_s("%s", tmp, sizeof(tmp));//�������2����
		for (int y = 0;y < G->n;y++)
		{
			if (strcmp(G->cities[y], tmp) == 0)
				j = y;
		}
		printf("����������֮��ľ��룺");
		scanf_s("%d", &d);//������֮��ľ���
		G->edges[i][j] = d;
		G->edges[j][i] = d;
	}

}
void pre(int v, int x, Mgraph *G, int prev[])
{
	if (x != v)
	{
		pre(v, prev[x], G, prev);
		printf("%s->", G->cities[x]);
	}
	else printf("%s->", G->cities[v]);
}
void Dijkstra(Mgraph *G)
{
	int dist[MAX];
	int prev[MAX];
	int v;
	bool S[MAX];    // �ж��Ƿ��Ѵ���õ㵽S������
	char tmp[20];
	printf("�������1�����ƣ�");
	scanf_s("%s", tmp, sizeof(tmp));//�������1����
	for (int i = 0; i < G->n; i++)
	{
		if (strcmp(G->cities[i], tmp) == 0)
			v = i;
	}
	for (int i = 0; i < G->n; i++)
	{
		if (v != i)
		{
			dist[i] = G->edges[v][i];
			S[i] = false;                                // ��ʼ��δ�ù��õ�
			if (dist[i] == MAXINT)
				prev[i] = -1;
			else
				prev[i] = v;
		}
	}
	dist[v] = 0;
	S[v] = true;
	for (int i = 1; i < G->n; i++)
	{
		int mindist = MAXINT;
		int u = v;                                 // �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for (int j = 0; j < G->n; j++)
			if ((!S[j]) && dist[j]<mindist)
			{
				u = j;                             // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ��� 
				mindist = dist[j];
			}
		S[u] = true;
		for (int j = 0; j < G->n; j++)
			if ((!S[j]) && G->edges[u][j]<MAXINT)
			{
				if (dist[u] + G->edges[u][j] < dist[j])     //��ͨ���¼����u��·���ҵ���v����̵�·��  
				{
					dist[j] = dist[u] + G->edges[u][j];    //����dist 
					prev[j] = u;                    //��¼ǰ������ 
				}
			}
	}
	printf("�������2�����ƣ�");
	scanf_s("%s", tmp, sizeof(tmp));//�������2����
	for (int i = 0; i < G->n; i++)
	{
		if (strcmp(G->cities[i], tmp) == 0)
		{
			printf("������֮�����̾���Ϊ��");
			printf("%d\n", dist[i]);
			printf("������֮������·��Ϊ��");
			pre(v, prev[i], G, prev);
			printf("%s", G->cities[i]);
		}
	}
}
void main()
{
	Mgraph G;
	CreateGraph(&G);
	printf("��ͨͼ�������\n\n");
	Dijkstra(&G);
	printf("\n");
	system("pause");
}