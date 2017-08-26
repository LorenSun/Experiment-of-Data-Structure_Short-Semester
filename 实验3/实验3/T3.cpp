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
//����ʽ���е�ͷβ�ڵ�ָ�붨��Ϊһ�������Ľṹ�壬�����������ڵ�ʱռ�ù���Ŀռ�
typedef struct {
	Qnode *front;
	Qnode *rear;
}LinkQueue;
//��ʼ����ʽ����
void InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (Qnode *)malloc(sizeof(Qnode));
	if (!Q->front)
	{
		printf("error!");
		return;
	}
	Q->rear->next = NULL;//����ʽ���е�β�ڵ�ʼ��ָ��NULL
}
void InQueue(LinkQueue *Q)//���
{
	Qnode *p;
	p = (Qnode *)malloc(sizeof(Qnode));
	printf("�����복�ţ�");
	scanf_s("%s", p->id, sizeof(p->id));
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
}
bool isEmptyQ(LinkQueue *Q)//�ж϶����Ƿ�Ϊ��
{
	if (Q->front->next == NULL)
		return true;
	else	return false;
}
void PrintQueue(LinkQueue *Q)//�����
{
	Qnode *p;
	p = Q->front->next;
	if (!p)
	{
		printf("���Ϊ�գ�\n");
		return;
	}
	else
	{
		printf("�����״̬��������Ϊ:\n");
		while (p)
		{
			printf("����:");
			printf("%s\n", p->id);
			p = p->next;
		}
	}
}
void InitStack(LinkStack &topPt) //��ʼ��ջ
{
	topPt = NULL;
}
int isEmpty(LinkStack top) //�п�ջ
{
	return top == NULL;
}
void in_push(LinkStack &topPt, stackNode *p)
{
	p->next = topPt;
	topPt = p;
}
void push(LinkStack &topPt, LinkQueue *Q, int n) //��ջ
{
	if (count >= n)
	{
		printf("ͣ�������������ڱ���ϵȴ���\n");
		InQueue(Q);
		return;
	}
	stackNode *p;
	p = (stackNode*)malloc(sizeof(stackNode));
	printf("�����복�ţ�");
	scanf_s("%s", p->id, sizeof(p->id));
	printf("���������ʱ�䣺");
	scanf_s("%s", p->time, sizeof(p->time));
	printf("������������ڣ�");
	scanf_s("%s", p->date, sizeof(p->date));
	in_push(topPt, p);
	count++;
}
stackNode* pop(LinkStack &topPt) //��ջ
{
	stackNode *p;
	if (isEmpty(topPt))
		return NULL;
	p = topPt;
	topPt = p->next;
	return p;
}
void OutStack(LinkStack &topPt, LinkStack &wtopPt, LinkQueue *Q, int fee)//�뿪ͣ����
{
	if (isEmpty(topPt))
	{
		printf("ͣ����Ϊ�գ�\n");
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
	printf("�������뿪ͣ�����ĳ��ƺţ�");
	scanf_s("%s", &tmp, sizeof(tmp));
	printf("�������뿪ʱ�䣺");
	scanf_s("%s", &time, sizeof(time));
	printf("�������뿪���ڣ�");
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
			printf("�ӱ�����뿪�����շѣ�\n");
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
		printf("δ�ҵ��ó�!\n");
		return;
	}
	strcpy_s(arrive_time, topPt->time);
	strcpy_s(arrive_date, topPt->date);
	pop(topPt);
	count--;
	while (!isEmpty(wtopPt))
		in_push(topPt, pop(wtopPt));
	//ʱ����ת��Ϊ��ֵ
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
		printf("�Ʒ�ͣ��ʱ��Ϊ%dСʱ������Ϊ%dԪ\n", t, fee * t);
	}
	if (!isEmptyQ(Q))
	{
		printf("������еȴ�����������ϵĳ�������ͣ����������ʱ��Ϊ%s,��������Ϊ:%s\n", time_t, date_t);
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
void showStack(LinkStack &topPt, LinkStack &wtopPt)//��ʾͣ��������״̬
{
	if (isEmpty(topPt))
	{
		printf("ͣ����Ϊ�գ�\n");
		return;
	}
	while (!isEmpty(topPt))
		in_push(wtopPt, pop(topPt));

	stackNode * p = wtopPt;
	printf("ͣ������״̬��������Ϊ:\n");
	while (p)
	{
		printf("����:");
		printf("%s\t", p->id);
		printf("����ʱ��:");
		printf("%s\t", p->time);
		printf("��������:");
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
	printf("������ͣ��������ͣ������������n��");
	scanf_s("%d", &n);
	printf("������ͣ����ÿСʱ�ķ���fee��");
	scanf_s("%d", &fee);
	printf("\n\t1-��ʾͣ����״̬\n");
	printf("\t2-��������\n");
	printf("\t3-�����뿪\n");
	printf("\t0-�˳�\n\n");
	printf("��ѡ��");
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
		printf("��ѡ��");
		scanf_s("%d", &x);
	}
	system("pause");
}