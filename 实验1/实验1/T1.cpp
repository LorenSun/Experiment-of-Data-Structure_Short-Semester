#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAX 20
typedef struct node {
	char value;
	struct node *lchild, *rchild;
}binode, *bitree;
binode *create_bt() {   //����������
	char pos, ch;
	binode *Q[MAX];
	int front, rear;
	binode *root, *s;
	root = NULL;
	front = 1;rear = 0;
	scanf_s("%c", &pos, sizeof(pos));
	scanf_s("%c", &ch, sizeof(ch));
	while (pos != ' ')
	{
		rear++;
		s = (binode *)malloc(sizeof(binode));
		s->value = ch;
		s->lchild = s->rchild = NULL;
		Q[rear] = s;
		if (rear == 1) root = s;
		else {
			if (rear % 2 == 0)
				Q[front]->lchild = s;
			else {
				Q[front]->rchild = s;
				front++;
			}
		}
		getchar();
		scanf_s("%c", &pos, sizeof(pos));
		scanf_s("%c", &ch, sizeof(ch));
	}
	return root;
}
//����α���������
void treelevel(binode * bt)
{
	printf("����α�����������");
	binode *q[MAX], *p;
	int front, rear;
	front = rear = 0;
	if (!bt) return;
	q[rear] = bt; //��������
	rear = (rear + 1) % MAX;
	while (front != rear) //���в�Ϊ��
	{
		p = q[front]; //����
		front = (front + 1) % MAX;
		printf("%C ", p->value);
		if (p->lchild) //��������Ϊ��
		{
			q[rear] = p->lchild;
			rear = (rear + 1) % MAX;
		}
		if (p->rchild) //��������Ϊ��
		{
			q[rear] = p->rchild;
			rear = (rear + 1) % MAX;
		}
	}
	printf("\n");
}
//������������
void exchange(binode *bt)
{
	binode *tmp;
	if (bt)
	{
		tmp = bt->lchild;
		bt->lchild = bt->rchild;
		bt->rchild = tmp;
		exchange(bt->lchild);
		exchange(bt->rchild);
	}
}
void main() {
	binode *bt = NULL;
	int key;
	printf("\t1-����������\n");
	printf("\t2-��������������������ֵ\n");
	printf("\t3-�����ȸ������㷨�������������н���������������\n");
	printf("\t0-�˳�\n");
	printf("��ѡ��");
	scanf_s("%d", &key);
	while (key != 0) {
		switch (key)
		{
		case 1:printf("���뽨��Ԫ��<char>:\n");getchar();bt = create_bt();break;
		case 2:treelevel(bt);break;
		case 3:exchange(bt);printf("��������������");treelevel(bt);break;
		default:break;
		}
		printf("��ѡ��");
		scanf_s("%d", &key);
	}
	system("pause");


}