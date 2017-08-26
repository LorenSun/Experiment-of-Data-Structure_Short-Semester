#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string>
int count = 0;
typedef struct Snode {
	char id[20];
	char time[10];
	char date[10];
	struct Snode *next;
}stackNode, *LinkStack;
typedef struct node
{
	char id[20];
	char time[10];
	char date[10];
	struct node *next;
}Qnode, *q_node;
//把链式队列的头尾节点指针定义为一个单独的结构体，避免在新增节点时占用过多的空间
typedef struct {
	Qnode *front;
	Qnode *rear;
}LinkQueue;
//初始化链式队列
void InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (Qnode *)malloc(sizeof(Qnode));
	if (!Q->front)
	{
		printf("error!");
		return;
	}
	Q->rear->next = NULL;//将链式队列的尾节点始终指向NULL
}
void InQueue(LinkQueue *Q)//入队
{
	Qnode *p;
	p = (Qnode *)malloc(sizeof(Qnode));
	printf("请输入车号：");
	scanf_s("%s", p->id, sizeof(p->id));
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}
bool isEmptyQ(LinkQueue *Q)//判断队列是否为空
{
	if (Q->front->next == NULL)
		return true;
	else	return false;
}
void PrintQueue(LinkQueue *Q)//输出队
{
	Qnode *p;
	p = Q->front->next;
	if (!p)
	{
		printf("便道为空！\n");
		return;
	}
	else
	{
		printf("便道的状态由里至外为:\n");
		while (p)
		{
			printf("车号:");
			printf("%s\n", p->id);
			p = p->next;
		}
	}
}
void InitStack(LinkStack &topPt) //初始化栈
{
	topPt = NULL;
}
int isEmpty(LinkStack top) //判空栈
{
	return top == NULL;
}
void in_push(LinkStack &topPt, stackNode *p)
{
	p->next = topPt;
	topPt = p;
}
void push(LinkStack &topPt, LinkQueue *Q, int n) //进栈
{
	if (count >= n)
	{
		printf("停车场已满，请在便道上等待！\n");
		InQueue(Q);
		return;
	}
	stackNode *p;
	p = (stackNode*)malloc(sizeof(stackNode));
	printf("请输入车号：");
	scanf_s("%s", p->id, sizeof(p->id));
	printf("请输入进入时间：");
	scanf_s("%s", p->time, sizeof(p->time));
	printf("请输入进入日期：");
	scanf_s("%s", p->date, sizeof(p->date));
	in_push(topPt, p);
	count++;
}
stackNode* pop(LinkStack &topPt) //出栈
{
	stackNode *p;
	if (isEmpty(topPt))
		return NULL;
	p = topPt;
	topPt = p->next;
	return p;
}
void OutStack(LinkStack &topPt, LinkStack &wtopPt, LinkQueue *Q, int fee)//离开停车场
{
	if (isEmpty(topPt))
	{
		printf("停车场为空！\n");
		return;
	}
	int arrive_t[2], leave_t[2];
	int arrive_d[2], leave_d[2];
	bool isFind = false;
	bool isFindQ = true;
	char tmp[20];
	char time[20];
	char date[20];
	char time_t[20];
	char date_t[20];
	char arrive_time[20];
	char arrive_date[20];
	printf("请输入离开停车场的车牌号：");
	scanf_s("%s", &tmp, sizeof(tmp));
	printf("请输入离开时间：");
	scanf_s("%s", &time, sizeof(time));
	printf("请输入离开日期：");
	scanf_s("%s", &date, sizeof(date));
	strcpy_s(time_t, time);
	strcpy_s(date_t, date);
	Qnode *p, *q;
	p = Q->front;
	q = NULL;
	while (p->next)
	{
		q = p;
		q = q->next;
		if (strcmp(q->id, tmp) == 0)
		{
			p->next = q->next;
			free(q);
			printf("从便道上离开，不收费！\n");
			isFind = true;
			return;
		}
		p = p->next;
	}
	while (!isEmpty(topPt) && (strcmp(topPt->id, tmp) != 0))
		in_push(wtopPt, pop(topPt));
	if (isEmpty(topPt))
		isFindQ = false;
	if (!isFind && !isFindQ)
	{
		printf("未找到该车!\n");
		return;
	}
	strcpy_s(arrive_time, topPt->time);
	strcpy_s(arrive_date, topPt->date);
	pop(topPt);
	count--;
	while (!isEmpty(wtopPt))
		in_push(topPt, pop(wtopPt));
	//时间拆分转化为数值
	int x = 0;
	char delims[] = ":";
	char delimst[] = "/";
	char *buf;
	char *result = NULL;
	result = strtok_s(arrive_time, delims, &buf);
	while (result != NULL) {
		arrive_t[x++] = atoi(result);
		result = strtok_s(NULL, delims, &buf);
	}
	x = 0;
	result = strtok_s(time, delims, &buf);
	while (result != NULL) {
		leave_t[x++] = atoi(result);
		result = strtok_s(NULL, delims, &buf);
	}
	x = 0;
	result = strtok_s(arrive_date, delimst, &buf);
	while (result != NULL) {
		arrive_d[x++] = atoi(result);
		result = strtok_s(NULL, delimst, &buf);
	}
	x = 0;
	result = strtok_s(date, delimst, &buf);
	while (result != NULL) {
		leave_d[x++] = atoi(result);
		result = strtok_s(NULL, delimst, &buf);
	}
	int t = leave_t[0] - arrive_t[0];
	if (leave_t[1] - arrive_t[1] < 0)
		t--;
	if (t < 0 && leave_d[1] - arrive_d[1] <= 0)
	{
		printf("error!");
		return;
	}
	else
	{
		t += 24 * (leave_d[1] - arrive_d[1]);
		printf("计费停车时间为%d小时，费用为%d元\n", t, fee * t);
	}
	if (!isEmptyQ(Q))
	{
		printf("便道上有等待车辆，便道上的车辆进入停车场，进入时间为%s,进入日期为:%s\n", time_t, date_t);
		stackNode *p = (stackNode*)malloc(sizeof(stackNode));
		Qnode *qq = Q->front->next;
		strcpy_s(p->id, qq->id);
		strcpy_s(p->time, time_t);
		strcpy_s(p->date, date_t);
		in_push(topPt, p);
		count++;
		Q->front = Q->front->next;
	}
}
void showStack(LinkStack &topPt, LinkStack &wtopPt)//显示停车场与便道状态
{
	if (isEmpty(topPt))
	{
		printf("停车场为空！\n");
		return;
	}
	while (!isEmpty(topPt))
		in_push(wtopPt, pop(topPt));

	stackNode * p = wtopPt;
	printf("停车场的状态由里至外为:\n");
	while (p)
	{
		printf("车号:");
		printf("%s\t", p->id);
		printf("进入时间:");
		printf("%s\t", p->time);
		printf("进入日期:");
		printf("%s\n", p->date);
		p = p->next;
	}
	while (!isEmpty(wtopPt))
		in_push(topPt, pop(wtopPt));
}
void main()
{
	LinkQueue Q;
	LinkStack top, wtop;
	InitQueue(&Q);
	InitStack(top);
	InitStack(wtop);
	int n, x, fee;
	printf("请输入停车场可以停放汽车的数量n：");
	scanf_s("%d", &n);
	printf("请输入停车场每小时的费用fee：");
	scanf_s("%d", &fee);
	printf("\n\t1-显示停车场状态\n");
	printf("\t2-车辆到达\n");
	printf("\t3-车辆离开\n");
	printf("\t0-退出\n\n");
	printf("请选择：");
	scanf_s("%d", &x);
	while (x != 0)
	{
		switch (x)
		{
		case 1:showStack(top, wtop);PrintQueue(&Q);break;
		case 2:push(top, &Q, n);break;
		case 3:OutStack(top, wtop, &Q, fee);break;
		default:break;
		}
		printf("请选择：");
		scanf_s("%d", &x);
	}
	system("pause");
}