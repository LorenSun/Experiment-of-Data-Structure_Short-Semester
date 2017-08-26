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
}Mgraph; //定义图的邻接矩阵储存类型
void CreateGraph(Mgraph *G)//邻接矩阵将图存储
{
	int x = 0;
	printf("输入交通图的城市数n，道路数e：");
	scanf_s("%d %d", &G->n, &G->e);
	for (int i = 0;i<G->n;i++) //邻接矩阵置0,得到所有城市的名称
	{
		printf("输入城市%d的名称：", i + 1);
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
		printf("输入两城市及之间的距离\n");
		printf("输入城市1的名称：");
		scanf_s("%s", tmp, sizeof(tmp));//输入城市1名称
		for (int y = 0;y < G->n;y++)
		{
			if (strcmp(G->cities[y], tmp) == 0)
				i = y;
		}
		printf("输入城市2的名称：");
		scanf_s("%s", tmp, sizeof(tmp));//输入城市2名称
		for (int y = 0;y < G->n;y++)
		{
			if (strcmp(G->cities[y], tmp) == 0)
				j = y;
		}
		printf("输入两城市之间的距离：");
		scanf_s("%d", &d);//两城市之间的距离
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
	bool S[MAX];    // 判断是否已存入该点到S集合中
	char tmp[20];
	printf("输入城市1的名称：");
	scanf_s("%s", tmp, sizeof(tmp));//输入城市1名称
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
			S[i] = false;                                // 初始都未用过该点
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
		int u = v;                                 // 找出当前未使用的点j的dist[j]最小值
		for (int j = 0; j < G->n; j++)
			if ((!S[j]) && dist[j]<mindist)
			{
				u = j;                             // u保存当前邻接点中距离最小的点的号码 
				mindist = dist[j];
			}
		S[u] = true;
		for (int j = 0; j < G->n; j++)
			if ((!S[j]) && G->edges[u][j]<MAXINT)
			{
				if (dist[u] + G->edges[u][j] < dist[j])     //在通过新加入的u点路径找到离v点更短的路径  
				{
					dist[j] = dist[u] + G->edges[u][j];    //更新dist 
					prev[j] = u;                    //记录前驱顶点 
				}
			}
	}
	printf("输入城市2的名称：");
	scanf_s("%s", tmp, sizeof(tmp));//输入城市2名称
	for (int i = 0; i < G->n; i++)
	{
		if (strcmp(G->cities[i], tmp) == 0)
		{
			printf("两城市之间的最短距离为：");
			printf("%d\n", dist[i]);
			printf("两城市之间的最短路径为：");
			pre(v, prev[i], G, prev);
			printf("%s", G->cities[i]);
		}
	}
}
void main()
{
	Mgraph G;
	CreateGraph(&G);
	printf("交通图创建完成\n\n");
	Dijkstra(&G);
	printf("\n");
	system("pause");
}