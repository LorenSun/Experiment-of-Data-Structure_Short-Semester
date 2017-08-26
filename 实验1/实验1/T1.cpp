#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAX 20
typedef struct node {
	char value;
	struct node *lchild, *rchild;
}binode, *bitree;
binode *create_bt() {   //建立二叉树
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
//按层次遍历二叉树
void treelevel(binode * bt)
{
	printf("按层次遍历二叉树：");
	binode *q[MAX], *p;
	int front, rear;
	front = rear = 0;
	if (!bt) return;
	q[rear] = bt; //树根进队
	rear = (rear + 1) % MAX;
	while (front != rear) //队列不为空
	{
		p = q[front]; //出队
		front = (front + 1) % MAX;
		printf("%C ", p->value);
		if (p->lchild) //左子树不为空
		{
			q[rear] = p->lchild;
			rear = (rear + 1) % MAX;
		}
		if (p->rchild) //右子树不为空
		{
			q[rear] = p->rchild;
			rear = (rear + 1) % MAX;
		}
	}
	printf("\n");
}
//交换左右子树
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
	printf("\t1-建立二叉树\n");
	printf("\t2-按二叉树层次输出各结点的值\n");
	printf("\t3-利用先根遍历算法将二叉树中所有结点的左右子树交换\n");
	printf("\t0-退出\n");
	printf("请选择：");
	scanf_s("%d", &key);
	while (key != 0) {
		switch (key)
		{
		case 1:printf("输入建树元素<char>:\n");getchar();bt = create_bt();break;
		case 2:treelevel(bt);break;
		case 3:exchange(bt);printf("左右子树交换后");treelevel(bt);break;
		default:break;
		}
		printf("请选择：");
		scanf_s("%d", &key);
	}
	system("pause");


}