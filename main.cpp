#include "package.h"
/**********educoder***********/
void Union(SqList La, SqList Lb, SqList& Lc);					//两顺序表C=A∪B
void Intersect(SqList La, SqList Lb, SqList& Lc);				//两顺序表C=A∩B
void Different(SqList La, SqList Lb, SqList& Lc);				//两顺序表C=A-B
void Intersect(pLinkNode La, pLinkNode Lb, pLinkNode& Lc);		//两链表C=A∩B
void Print(SqList);												//打印顺序表
void Print(pLinkNode);											//打印链表

/**************实验***************/
void test1_1();		//实验1.1
void test1_2();		//实验1.2
void test2_1();		//实验2.1
void test2_2();		//实验2.2
void test3_1();		//实验3.1
void test3_2();		//实验3.1
void test4();		//实验4
void test5();		//实验5
void test6();		//实验6
void test7();		//实验7
void test8();		//实验8
void test9();		//实验9


int main() {
	//	test1_1();
	// 	test1_2();
	//	test2_1();
	//	test2_2();
	//	test3_1();
	//	test3_2();
	//	test4();
	//	test5();
	//	test6();
	//	test7();
	//	test8();
	//	test9();

}
void Union(SqList La, SqList Lb, SqList& Lc) {
	int i, j, k;
	InitSqList(Lc);
	for (i = 0, j = 0, k = 0; i < La.length && j < Lb.length;) {
		if (La.data[i] < Lb.data[j]) Lc.data[k++] = La.data[i++], Lc.length++;
		else if (La.data[i] > Lb.data[j]) Lc.data[k++] = Lb.data[j++], Lc.length++;
		else Lc.data[k++] = La.data[i++], j++, Lc.length++;
	}
	while (i < La.length) Lc.data[k++] = La.data[i++], Lc.length++;
	while (j < Lb.length) Lc.data[k++] = Lb.data[j++], Lc.length++;
}

void Intersect(SqList La, SqList Lb, SqList& Lc) {
	int i = 0, j = 0, k = 0;
	InitSqList(Lc);
	while (i < La.length && j < Lb.length) {
		if (La.data[i] < Lb.data[j]) i++;
		else if (La.data[i] > Lb.data[j]) j++;
		else Lc.data[k++] = La.data[i++], j++, Lc.length++;
	}
}
void Different(SqList La, SqList Lb, SqList& Lc) {
	int i = 0, j = 0;
	InitSqList(Lc);
	while (i < La.length && j < Lb.length) {
		if (La.data[i] > Lb.data[j]) j++;
		else if (La.data[i] < Lb.data[j]) i++;
		else DestroySqList(La, i + 1);
	}
	Lc = La;
}
void Intersect(pLinkNode La, pLinkNode Lb, pLinkNode& Lc) {
	int i = 1;
	InitLinkList(Lc);
	while (Lb->next && La->next) {
		if (La->next->data < Lb->next->data) La = La->next;
		else if (La->next->data > Lb->next->data) Lb = Lb->next;
		else {
			InsertLinkList(Lc, i++, La->next->data);
			Lb = Lb->next;
			La = La->next;
		}
	}
}
void Print(SqList L) {
	printf("线性表：");
	for (int i = 0; i < L.length; i++) {
		printf("%4d", L.data[i]);
	}
	printf("\n");
}
void Print(pLinkNode L) {
	pLinkNode p = L->next;
	printf("链表:Head");
	while (p) {
		printf("->%d", p->data);
		p = p->next;
	}
	printf("->NULL\n");
}
void test1_1()
{
	pLinkNode L;
	int a, num[10] = { 10,20,30,40,50,60,70,80,90,100 };
	Elemtype x;
	InitLinkList(L);
	for (int i = 0; i < 10;i++) InsertLinkListByNum(L, num[i]);
	Print(L);
	printf("i:");
	while (scanf_s("%d", &a)) {
		GetLinkListElement(L, a, x);
		printf("返回:%d\n---------------\ni:", x);
	}
}
void test1_2()
{
	pLinkNode L;
	int a;
	Elemtype x;
	InitLinkList(L);
	printf("i:");
	while (scanf_s("%d", &a)) {
		GetLinkListElement(L, a, x);
		printf("返回:%d\n---------------\ni:", x);
	}
}
void test2_1()
{
	pLinkNode L;
	int  a, num[10] = { 10,20,30,40,50,60,70,80,90,100 };
	InitLinkList(L);
	for (int i = 0; i < 10; i++) {
		InsertLinkListByNum(L, num[i]);
	}
	Print(L);
	printf("---------------\ni:");
	while (scanf_s("%d", &a) == 1) {
		InsertLinkList(L, a, 100);
		Print(L);
		printf("---------------\ni:");
	}
}
void test2_2()
{
	pLinkNode L;
	int  a;
	InitLinkList(L);
	printf("i:");
	while (scanf_s("%d", &a) == 1) {
		InsertLinkList(L, a, 100);
		Print(L);
		printf("---------------\ni:");
	}
}

void test3_1()
{
	pLinkNode L;
	int a, num[10] = { 10,20,30,40,50,60,70,80,90,100 };
	InitLinkList(L);
	for (int i = 0; i < 10; i++) InsertLinkListByNum(L, num[i]);
	Print(L);
	printf("---------------\ni:");
	while (scanf_s("%d", &a) == 1) {
		DestroyLinkList(L, a);
		Print(L);
		printf("---------------\ni:");
	}
}

void test3_2()
{
	pLinkNode L;
	int a;
	InitLinkList(L);
	printf("i:");
	while (scanf_s("%d", &a) == 1) {
		DestroyLinkList(L, a);
		Print(L);
		printf("---------------\ni:");
	}
}

void test4()
{
	pLinkNode L;
	Elemtype a, num[10] = { 10,20,30,40,50,60,70,80,90,100 };
	InitLinkList(L);
	for (int i = 0; i < 10; i++) InsertLinkListByNum(L, num[i]);
	Print(L);
	printf("---------------\n元素:");
	while (scanf_s("%d", &a) == 1) {
		InsertLinkListByNum(L, a);
		Print(L);
		printf("---------------\n元素:");
	}
}

void test5()
{
	pLinkStack S;
	char c;
	InitLinkStack(S);
	printf("字符串:");
	while (scanf_s("%c", &c, 1) == 1) {
		if (c == '#') break;
		PushLinkStack(S, c);
	}
	printf("---------------\n出栈:");
	PopLinkStack(S,c);
	printf("%c\n", c);
	printf("---------------\n取栈顶:");
	GetLinkTop(S, c);
	printf("%c\n", c);
}

void test6()
{
	SqQuene Q;
	char a, h;
	InitSqQueue(Q);
	printf("字符串:");
	while (scanf_s("%c", &a,1) == 1) EnQueue(Q, a);
	DeQueue(Q, h);
	GetSqQueue(Q, a);
	printf("---------------\n出队:%c\n入队:%c", h, a);
}

void test7()
{
	pTNode T;
	printf("输入数据:");
	CreatLinkTree(T);
	DeepLinkTree(T);
}

void test8()
{
	AMGraph G;
	CreatGraph_AM(G);
	printf("\n弧长:%d\n", G.arcnum);
	BFS_AM_MIN(G, '2', '3');
}

void test9()
{
	ALGraph G;
	CreatGraph_AL(G);
	printf("\n弧长:%d", G.arcnum);
	BFS_AL_MIN(G, '2', '3');
}
