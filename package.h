#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#define MAX_LIST_LENGTH 100		//静态线性表最大存储空间
#define MAX_VERTEXNUM 100		//最大顶点数
#define Elemtype int
#define Stacktype char			//栈元素类型
#define Verttype char			//图顶点类型
#define OVERFLOW 0				//溢出
#define NOTFOUND 0				//查找不到

bool visited[MAX_VERTEXNUM] = { false };	//访问点宏观变量
int height = 1;	//深度宏观变量
char haffcode[MAX_LIST_LENGTH] = { 0 };

/**************结构体**************/
typedef struct SqList {					//顺序表
	Elemtype data[MAX_LIST_LENGTH];
	int length;
}SqList;
typedef struct LinkNode{				//链表
	Elemtype data;
	LinkNode* next;
}*pLinkNode;
typedef struct SqStack {				//顺序栈
	Elemtype data[MAX_LIST_LENGTH];
	int top;
}SqStack;
typedef struct LinkStack {				//链栈
	Stacktype data;
	LinkStack* next;
}*pLinkStack;
typedef struct SqQueue {				//顺序队列
	Verttype data[MAX_LIST_LENGTH];
	int front;
	int rear;
}SqQuene;
typedef struct LinkQueue {				//链式队列
	pLinkNode front;
	pLinkNode rear;
}LinkQueue;
/*typedef struct SqTree {				//顺序二叉树
	char data[MAX_LIST_LENGTH];
}SqTree;*/
typedef struct TreeNode {				//链式二叉树
	Verttype data;
	TreeNode* left;
	TreeNode* right;
}TNode,*pTNode;
typedef struct {						//哈夫曼树
	int weight;							//结点权重
	int parent, left, right;			//父结点、左孩子、右孩子在数组中的位置下标
}Huff[MAX_LIST_LENGTH];
typedef char HuffCo[MAX_LIST_LENGTH][MAX_LIST_LENGTH];				//哈夫曼编码
/*****************邻接矩阵结构体定义*****************/
typedef struct {
	Verttype Vex[MAX_VERTEXNUM];			//顶点
	bool Edge[MAX_VERTEXNUM][MAX_VERTEXNUM];			//矩阵
	int vexnum, arcnum;			//顶点数、弧数
}AMGraph;
/*****************邻接表结构体定义*****************/
typedef struct ArcNode {				//边表同链表
	Verttype adjvex;
	ArcNode* next;
}*pArcNode;
typedef struct VerNode {				//顺序顶表
	Verttype data;
	pArcNode first;						//边表头结点
}VerNode, AdjList[MAX_VERTEXNUM];
typedef struct {
	AdjList vertice;
	int vexnum, arcnum;					//顶点数、弧数
}ALGraph;
/************顺序表声明*************/
void InitSqList(SqList&);							//初始化
int GetSqListLen(SqList);							//获取长度
void GetSqListElement(SqList, int, Elemtype&);		//获取元素
int LocateSqList(SqList, Elemtype);					//定位
void InsertSqList(SqList&, int, Elemtype);			//按序号插入
void DestroySqList(SqList&, int);					//按序号删除
void InsertSqListByNum(SqList&, Elemtype);			//按值升序插入
/**************链表声明**************/
void InitLinkList(pLinkNode&);						//初始化
int GetLinkListLen(pLinkNode);						//获取长度
void GetLinkListElement(pLinkNode, int, Elemtype&);	//获取元素
pLinkNode LocateLinkListByNum(pLinkNode, Elemtype);	//按值返回指针
pLinkNode LocateLinkListByIndex(pLinkNode, int);	//按序号返回指针
void InsertLinkList(pLinkNode&, int, Elemtype);		//按序号插入
void DestroyLinkList(pLinkNode&, int);				//按序号删除
void InsertLinkListByNum(pLinkNode&, Elemtype);		//按值升序插入
/**************顺序栈声明**************/
void InitSqStack(SqStack&);							//初始化
bool EmptySqStack(SqStack);							//是否空
bool FullSqStack(SqStack);							//是否满
void GetSqTop(SqStack, Elemtype&);					//获取栈顶元素
void PushSqStack(SqStack&, Elemtype);				//入栈
void PopSqStack(SqStack&, Elemtype&);				//出栈
/**************链栈声明**************/
void InitLinkStack(pLinkStack&);					//初始化
bool EmptyLinkStack(pLinkStack);					//是否空
void GetLinkTop(pLinkStack, Stacktype&);			//获取栈顶元素
void PushLinkStack(pLinkStack&, Stacktype);			//入栈
void PopLinkStack(pLinkStack&, Stacktype&);			//出栈
void ClearStack(pLinkStack&);						//清空栈
/**************循环队列声明**************/
void InitSqQueue(SqQueue& Q);						//初始化
bool EmptySqQueue(SqQueue Q);						//是否空
bool FullSqQueue(SqQueue Q);						//是否满
void GetSqQueue(SqQueue Q, Verttype& num);			//获取队头元素
void EnQueue(SqQueue& Q, Verttype num);				//入队
void DeQueue(SqQueue& Q, Verttype& num);			//出队
/**************链式队列声明**************/
void InitLinkQueue(LinkQueue&);						//初始化
void DestroyQueue(LinkQueue&);						//销毁
void EnLinkQueue(LinkQueue&, Elemtype);				//入队
void DeQueue(LinkQueue&, Elemtype&);				//出队
void GetLinkQueue(LinkQueue&, Elemtype&);			//获取队头元素
bool EmptyLinkQueue(LinkQueue);						//是否空
/**************链式二叉树声明**************/
void CreatLinkTree(pTNode&);						//建立二叉树
void PreOrder(pTNode);								//先序遍历
void InOrder(pTNode);								//中序遍历
void LatOrder(pTNode);								//后序遍历
void PreOrderDel(pTNode&, Verttype);				//先序删除
int DeepLinkTree(pTNode);							//深度
/**************哈夫曼树声明**************/
void Select(Huff, int, int&, int&);					//选两最小值 树/终止位/最小值1/最小值2
void CreatHuffTree(Huff&, HuffCo&, int*, int, int&);//创建哈夫曼树 树/编码/权值/权值数/带权路径长度
/**************邻接矩阵声明**************/
void CreatGraph_AM(AMGraph&);						//创建邻接矩阵
int Arcnum(AMGraph);								//返回边数
int FirstNeighbor(AMGraph, Verttype);				//第一个相邻点
int NextNeighbor(AMGraph, Verttype, Verttype);		//访问过的点外的相邻节点
void BFS_AM(AMGraph, Verttype);						//广度优先
void BFS_AM_MIN(AMGraph, Verttype, Verttype);		//广度优先最短路径
int Index(AMGraph, Verttype);						//索引查找
/**************邻接表声明**************/
void CreatGraph_AL(ALGraph&);						//创建邻接表
int Arcnum(ALGraph);								//返回边数
int FirstNeighbor(ALGraph, Verttype);				//第一个相邻结点
int NextNeighbor(ALGraph, Verttype, Verttype);		//访问过的结点外的相邻结点
bool BFS_AL(ALGraph, Verttype);						//广度优先+判断是否联通
void BFS_AL_MIN(ALGraph, Verttype, Verttype);		//广度优先最短路径
int Index(ALGraph, Verttype);						//索引查找
/************顺序表*************/
void InitSqList(SqList& L) {
	L.length = 0;
}
int GetSqListLen(SqList L) {
	return L.length;
}
void GetSqListElement(SqList L, int i, Elemtype& num) {
	if (i > 0 && i <= L.length) num = L.data[i - 1];
	else num = 0;
}
int LocateSqList(SqList L, Elemtype num) {
	for (int i = 0; i < L.length; i++){
		if (num == L.data[i]) return i;
	}
	return -1;
}
void InsertSqList(SqList& L, int i, Elemtype num) {
	if (MAX_LIST_LENGTH == L.length + 1) exit(OVERFLOW);
	else {
		for (int j = L.length; j >= i; j--) {
			L.data[j] = L.data[j - 1];
		}
		L.data[i - 1] = num;
		L.length++;
	}
}
void DestroySqList(SqList& L, int i) {
	if (i > L.length && i < 0) printf("This List isn't have the length of 'i'"), exit(NOTFOUND);
	else {
		while (i <= L.length) L.data[i - 1] = L.data[i++];
		L.length--;
	}
}
void InsertSqListByNum(SqList& L,Elemtype num) {
	if (MAX_LIST_LENGTH == L.length) printf("This SqList is overflow"), exit(OVERFLOW);
	else {
		int temp = L.length - 1;
		while (temp >= 0 && L.data[temp] > num) {
			L.data[temp + 1] = L.data[temp--];
		}
		L.data[temp + 1] = num;
		L.length++;
	}
}
/***************链表***************/
void InitLinkList(pLinkNode& L) {
	L = (pLinkNode)malloc(sizeof(LinkNode));
	if (!L) printf("This LinkList isn't be created"), exit(OVERFLOW);
	L->next = NULL;
}
int GetLinkListLen(pLinkNode L) {
	int i = 0;
	pLinkNode p = L->next;
	while (p) {
		p = p->next;
		i++;
	}
	return i;
}
void GetLinkListElement(pLinkNode L, int i, Elemtype& num) {
	if (i > 0 && i <= GetLinkListLen(L)) {
		while (i-- && L->next != NULL) L = L->next;
		num = L->data;
	}
	else num = 0;
}
pLinkNode LocateLinkListByNum(pLinkNode L, Elemtype num) {	//返回0000000000000000为不存在
	pLinkNode p = L->next;
	while (p != NULL && p->data != num) p = p->next;
	return p;
}
pLinkNode LocateLinkListByIndex(pLinkNode L, int i) {	//返回0为不存在
	if (i > 0 && i <= GetLinkListLen(L)) {
		while (i-- && L->next != NULL) L = L->next;
		return L;
	}
	else return NULL;
}
void InsertLinkList(pLinkNode& L, int i, Elemtype num) {
	pLinkNode s, p = L;
	while (p != NULL && --i) p = p->next;
	if (NULL == p) printf("This 'i' is not found\n");
	else {
		s = (pLinkNode)malloc(sizeof(LinkNode));
		if (!s) printf("This LinkList isn't be created"), exit(OVERFLOW);
		s->data = num;
		s->next = p->next;
		p->next = s;
	}
}
void DestroyLinkList(pLinkNode& L, int i) {
	pLinkNode s, p = L;
	if (i < 0) printf("This 'i' is not found"), exit(NOTFOUND);
	while (p != NULL && --i) p = p->next;
	if (NULL == p || NULL == p->next) printf("This 'i' is not found\n");
	else {
		s = p->next;
		p->next = s->next;
		free(s);
	}
}
void InsertLinkListByNum(pLinkNode& L, Elemtype num) {
	pLinkNode s, p = L;
	while (p->next != NULL && p->next->data < num) p = p->next;
	s = (pLinkNode)malloc(sizeof(LinkNode));
	if (!s) printf("This LinkList isn't be created"), exit(OVERFLOW);
	s->data = num;
	s->next = p->next;
	p->next = s;
}
/***************顺序栈***************/
void InitSqStack(SqStack& S) {
	S.top = -1;
}
bool EmptySqStack(SqStack S) {
	return (-1 == S.top);
}
bool FullSqStack(SqStack S) {
	return(MAX_LIST_LENGTH - 1 == S.top);
}
void GetSqTop(SqStack S, Elemtype& num) {
	if (EmptySqStack(S)) printf("This SqStack is empty"), exit(0);
	num = S.data[S.top];
}
void PushSqStack(SqStack& S, Elemtype num) {
	if (FullSqStack(S)) printf("This SqStack is overflow"), exit(OVERFLOW);
	else S.data[++S.top] = num;
}
void PopSqStack(SqStack& S, Elemtype& num) {
	if (EmptySqStack(S)) printf("This SqStack is empty"), exit(0);
	else num = (S.data[S.top--]);
}
///***************链栈***************/
void InitLinkStack(pLinkStack &S){
	S = (pLinkStack)malloc(sizeof(LinkStack));
	if (!S) printf("This LinkStack isn't be created"), exit(OVERFLOW);
	S->next = NULL;
}
bool EmptyLinkStack(pLinkStack S){
	return (NULL == S->next);
}
void GetLinkTop(pLinkStack S,Stacktype& num) {
	if (EmptyLinkStack(S)) printf("This LinkStack is empty"), exit(0);
	else num = S->next->data;
}
void PushLinkStack(pLinkStack& S, Stacktype num) {
	pLinkStack p;
	p = (pLinkStack)malloc(sizeof(LinkStack));
	if(!p) printf("This LinkStack isn't be created"), exit(OVERFLOW);
	else {
		p->data = num;
		p->next = S->next;
		S->next = p;
	}
}
void PopLinkStack(pLinkStack& S, Stacktype& num) {
	if (EmptyLinkStack(S)) printf("This LinkStack is empty"), exit(0);
	else {
		pLinkStack p = S->next;
		S->next = p->next;
		num = p->data;
		free(p);
	}
}
void ClearStack(pLinkStack& S) {
	pLinkStack p = NULL;
	while (S->next != NULL) {
		p = S->next;
		S->next = p->next;
		free(p);
	}
}
/***************循环队列***************/
void InitSqQueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
}
bool EmptySqQueue(SqQueue Q) {
	return (Q.front == Q.rear);
}
bool FullSqQueue(SqQueue Q) {
	return((Q.rear + 1) % MAX_LIST_LENGTH == Q.front);
}
void GetSqQueue(SqQueue Q, Verttype& num) {
	if (Q.data[Q.front]!= -52) num = Q.data[Q.front];	//VS char初始化为-52
	else printf("this queue is empty"), exit(0);
}
void EnQueue(SqQueue& Q, Verttype num) {
	if (FullSqQueue(Q)) printf("this queue is full"), exit(0);
	Q.data[Q.rear] = num;
	Q.rear = (Q.rear + 1) % MAX_LIST_LENGTH;
}
void DeQueue(SqQueue& Q, Verttype& num) {
	if (EmptySqQueue(Q)) printf("error"), exit(0);
	num = Q.data[Q.front];
	Q.front = (Q.front + 1) % MAX_LIST_LENGTH;
}
/***************链式队列***************/
void InitLinkQueue(LinkQueue& Q) {
	Q.front = Q.rear = (pLinkNode)malloc(sizeof(LinkNode));
	if (!Q.front) printf("This LinkQueue isn't be created"), exit(OVERFLOW);
	Q.front->next = NULL;
}
void DestroyQueue(LinkQueue& Q) {
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}
void EnLinkQueue(LinkQueue& Q,Elemtype num) {
	pLinkNode p = (pLinkNode)malloc(sizeof(LinkNode));
	if (!p) printf("This LinkQueue isn't be created"), exit(OVERFLOW);
	p->data = num;
	p->next = Q.rear->next;
	Q.rear->next = p;
	Q.rear = p;
}
void DeQueue(LinkQueue& Q, Elemtype& num) {
	pLinkNode p;
	if (EmptyLinkQueue(Q)) printf("This LinkQueue is empty"), exit(NOTFOUND);
	num = Q.front->data;
	p = Q.front->next;
	Q.front = Q.front->next;
	free(p);
}
void GetLinkQueue(LinkQueue& Q, Elemtype& num) {
	if (EmptyLinkQueue(Q)) printf("This LinkQueue is empty"), exit(NOTFOUND);
	num = Q.front->data;
}
bool EmptyLinkQueue(LinkQueue Q) {
	return (Q.front == Q.rear);
}
/**************链式二叉树**************/
void CreatLinkTree(pTNode& T) {
	Verttype c = 0;
	scanf_s("%c", &c, 1);
	T = (pTNode)malloc(sizeof(TNode));
	if (!T) printf("This LinkTree is not creat"), exit(OVERFLOW);
	if ('*' == c) T = NULL;
	else {
		T->data = c;
		CreatLinkTree(T->left);
		CreatLinkTree(T->right);
	}
}
void PreOrder(pTNode T) {
	if (T) {
		putchar(T->data);
		PreOrder(T->left);
		PreOrder(T->right);
	}
}
void PreOrderDel(pTNode& T, Verttype c) {
	if (T) {
		if (c == T->data) {
			if (T->left != NULL) PreOrderDel(T->left, T->left->data);
			if (T->right != NULL) PreOrderDel(T->right, T->right->data);
			free(T);
			T = NULL;
			return;
		}
		putchar(T->data);
		PreOrderDel(T->left,c);
		PreOrderDel(T->right,c);
		}
}
void InOrder(pTNode T) {
	if (T) {
		InOrder(T->left);
		putchar(T->data);
		InOrder(T->right);
	}
}
void LatOrder(pTNode T) {
	if (T) {
		LatOrder(T->left);
		LatOrder(T->right);
		putchar(T->data);
	}
}
int DeepLinkTree(pTNode T) {
	int m, n;		//m左子树深度 n右子树深度
	if (NULL == T)  return 0; 		//根为空
	if (NULL == T->left && NULL == T->right) { printf("%c:%d,", T->data,height); return 1; }			//根为叶子
	else {
		height++;
		m = DeepLinkTree(T->left);
		n = DeepLinkTree(T->right);
		height--;
	}
	if (m >= n) return m + 1;
	else return n + 1;
}
/**************哈夫曼树**************/
void Select(Huff T, int end, int& s1, int& s2){
	int one = 0, two = 0, i = 1;		//初始下标
	while (T[i].parent != 0 && i <= end) i++;		//未使用结点
	one = T[i].weight;
	s1 = i++;
	while (T[i].parent != 0 && i <= end) i++;
	T[i].weight < one ? two = one, s2 = s1, one = T[i].weight, s1 = i :
		two = T[i].weight, s2 = i;		//问号表达式，比大小
	for (int j = i + 1; j <= end; j++)		//与未使用结点比较大小
	{
		if (T[j].parent != 0) continue;		//使用就跳过
		T[j].weight < one ? two = one, one = T[j].weight, s2 = s1, s1 = j :		//未使用且比最小的小替换
			T[j].weight >= one && T[j].weight < two ? two = T[j].weight, s2 = j : 0;		//未使用且比最小的大，比最大的小替换
	}
}
void CreatHuffTree(Huff& T, HuffCo& C, int* w, int n, int& wpl) {
	if (n <= 1) return; // 如果只有一个编码就相当于0
	int i, m = 2 * n - 1; // 哈夫曼树总节点数，n就是叶子结点
	for (i = 1; i <= n; i++, w++)		//初始化
		T[i] = { *w,0,0,0 };
	for (i = n + 1; i <= m; i++)
		T[i] = { 0,0,0,0 };
	for (i = n + 1; i <= m; i++)		//构建哈夫曼树
	{
		int s1 = 0, s2 = 0;
		Select(T, i - 1, s1, s2);
		T[s1].parent = T[s2].parent = i;
		T[i].left = s1;
		T[i].right = s2;
		T[i].weight = T[s1].weight + T[s2].weight;
	}
	char code[MAX_LIST_LENGTH] = { 0 };		//哈夫曼编码部分
	for (i = 1; i <= n; i++) {		//权值循环
		int heigh = 0, start = n - 1;
		for (int c = i, f = T[i].parent; f != 0; c = f, f = T[f].parent) {
			if (T[f].left == c) code[--start] = '0';		//若为左子树为0,右为1
			else code[--start] = '1';
		strcpy(&C[i][0], &code[start]);		//复制
		heigh++;
		}
		wpl += heigh * T[i].weight;
	}
}
/************邻接矩阵*************/
void CreatGraph_AM(AMGraph &G) {
	printf("顶点数:");
	scanf_s("%d", &G.vexnum);
	if (!G.vexnum) printf("Vex error"), exit(0);		//顶点数错误
	printf("---------------\n弧数:");
	scanf_s("%d", &G.arcnum);
	if (G.arcnum > (G.vexnum * G.vexnum - 1) / 2) printf("Arc error"), exit(0);		//弧数错误
	printf("---------------\n顶点:");
	for (int i = 0; i < G.vexnum; i++) scanf_s(" %c", &G.Vex[i], 1);		//建立顶点
	for (int i = 0; i < G.arcnum; i++) {		//建立弧
		char out, in;
		int one, two;
		printf("---------------\n顶点(出):");
		scanf_s(" %c", &out, 1);
		printf("顶点(入):");
		scanf_s(" %c", &in, 1);
		one = Index(G, out);
		two = Index(G, in);
		if (one < 0 || two < 0) printf("Vex index error"), exit(0);		//顶点序号错误
		G.Edge[one][two] = false;		//VS bool型数组初始化为True
		G.Edge[two][one] = false;		//False为存在弧
	}
}
int Arcnum(AMGraph G) {
	int k = G.vexnum;
	int num = 0;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j <= i; j++) {
			if (G.Edge[i][j] == false) num++;
		}
	}
	return num;
}
int FirstNeighbor(AMGraph G, Verttype v) {
	int n = Index(G, v);
	for (int i = 0; i < G.vexnum; i++) 
		if (false == G.Edge[n][i]) return i;
	return -1;
}
int NextNeighbor(AMGraph G, Verttype v, Verttype m) {
	int n = Index(G, v);
	for (int i = 0; i < G.vexnum; i++) 
		if (false == G.Edge[n][i] && !visited[i]) return i;
	return -1;
}
void BFS_AM(AMGraph G, Verttype v) {
	SqQueue Q;
	InitSqQueue(Q);
	visited[Index(G,v)] = true;
	EnQueue(Q, v);
	while (!EmptySqQueue(Q)) {
		DeQueue(Q, v);
		printf("%c",v);
		for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, G.Vex[w]))
			if (!visited[w]) {
				visited[w] = true;
				EnQueue(Q, G.Vex[w]);
			}
	}
}
void BFS_AM_MIN(AMGraph G, Verttype v, Verttype e) {
	if (-1 == Index(G, v) || -1 == Index(G, e)) printf("输入错误"), exit(NOTFOUND);
	int i, len[MAX_VERTEXNUM];			//弧长
	char path[MAX_VERTEXNUM] = { 0 };		//路径
	SqQueue Q;		//辅助队列
	InitSqQueue(Q);
	len[Index(G, v)] = 0;
	visited[Index(G, v)] = true;
	EnQueue(Q, v); 
	printf("辅助队列出队顺序:");
	while (!EmptySqQueue(Q)) {	
		DeQueue(Q, v);
		printf("%c", v);
		for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, G.Vex[w]))
			if (!visited[w]) {
				len[w] = len[Index(G, v)] + 1;
				path[w] = v;
				visited[w] = true;
				EnQueue(Q, G.Vex[w]);
			}
	}
	if (len[Index(G, e)] != -858993460) {	//VS int型初始化值
		printf("\n---------------\n最短路径长度:%d", len[Index(G, e)]);
		printf("\n路径:%c", e);
		for (i = Index(G, path[Index(G, e)]); path[i] != '\0'; i = Index(G, path[i]))
			printf("<-%c", G.Vex[i]);
		printf("<-%c", G.Vex[i]);
	}
	else printf("\n无路径可从%c达结点%c", v, e);
}
int Index(AMGraph G, Verttype v) {
	for (int i = 0; i < G.vexnum; i++) 
		if (v == G.Vex[i]) return i;
	return -1;
}
/************邻接表*************/
void CreatGraph_AL(ALGraph& G) {
	pArcNode N;
	printf("顶点数:");
	scanf_s("%d", &G.vexnum);
	if (!G.vexnum) printf("Vex error"), exit(0);		//顶点数错误
	printf("---------------\n弧数:");
	scanf_s("%d", &G.arcnum);
	if (G.arcnum > (G.vexnum * G.vexnum - 1) / 2) printf("Arc error"), exit(0);		//弧数错误
	printf("---------------\n顶点:");
	for (int i = 0; i < G.vexnum; i++) {		//建立顶点
		scanf_s(" %c",&G.vertice[i].data,1);
		G.vertice[i].first = NULL;
	}
	for (int i = 0; i < G.arcnum; i++) {		//建立弧
		char out, in;
		int one, two;
		printf("---------------\n顶点(出):");
		scanf_s(" %c", &out, 1);
		printf("顶点(入):");
		scanf_s(" %c", &in, 1);
		one = Index(G, out);
		two = Index(G, in);
		if (one < 0 || two < 0) printf("Vex index error"), exit(0);		//顶点序号错误
		N = (pArcNode)malloc(sizeof(ArcNode));
		if (!N) printf("This Node is not crate"), exit(OVERFLOW);
		N->adjvex = G.vertice[two].data;
		N->next = G.vertice[one].first;
		G.vertice[one].first = N;
		N = (pArcNode)malloc(sizeof(ArcNode));
		if (!N) printf("This Node is not crate"), exit(OVERFLOW);
		N->adjvex = G.vertice[one].data;
		N->next = G.vertice[two].first;
		G.vertice[two].first = N;
	}
}
int Arcnum(ALGraph G) {
	int k = G.vexnum;
	int num = 0;
	pArcNode p;
	for(int i=0;i<k;i++){
		p = G.vertice[i].first;
		while (p) {
			num++;
			p = p->next;
		}
	}
	return num/2;
}
int FirstNeighbor(ALGraph G, Verttype v) {
	int x = -1, i = Index(G, v);
	pArcNode p = NULL;
	p = G.vertice[i].first;
	if (p) x = Index(G,p->adjvex);
	return x;
}
int NextNeighbor(ALGraph G, Verttype v, Verttype m) {
	int x = -1, i = Index(G, v);
	pArcNode p=NULL;
	p = G.vertice[i].first;
	if (p && !visited[i]) x = Index(G,p->adjvex);
	return x;
}
bool BFS_AL(ALGraph G, Verttype v) {
	SqQueue Q;		//辅助队列
	InitSqQueue(Q);
	visited[Index(G, v)] = true;
	EnQueue(Q, v);
	while (!EmptySqQueue(Q)) {
		DeQueue(Q, v);
		printf("%c", v);
		pArcNode p = G.vertice[Index(G, v)].first;
		while (p != NULL) {
			if (!visited[Index(G, p->adjvex)]) {
				visited[Index(G, p->adjvex)] = true;
				EnQueue(Q, G.vertice[Index(G, p->adjvex)].data);
			}
			p = p->next;
		}
	}
	printf("\n是否连通:");
	for (int i = 0; i < G.vexnum; i++) {
		if (false == visited[i]) {
			printf("FALSE");
			return false;
		}
		else continue;
	}
	printf("TRUE");
	return true;
}
void BFS_AL_MIN(ALGraph G, Verttype v, Verttype e) {
	if (-1 == Index(G, v) || -1 == Index(G, e)) printf("输入错误"), exit(NOTFOUND);
	int i, len[MAX_VERTEXNUM];			//弧长
	char path[MAX_VERTEXNUM] = { 0 };		//路径
	SqQueue Q;		//辅助队列
	InitSqQueue(Q);
	len[Index(G, v)] = 0;
	visited[Index(G, v)] = true;
	EnQueue(Q, v);
	printf("辅助队列出队顺序:");
	while (!EmptySqQueue(Q)) {
		DeQueue(Q, v);
		printf("%c", v);
		pArcNode p = G.vertice[Index(G, v)].first;
		while (p != NULL) {
			if (!visited[Index(G,p->adjvex)]) {
				len[Index(G, p->adjvex)] = len[Index(G, v)] + 1;
				path[Index(G, p->adjvex)] = v;
				visited[Index(G, p->adjvex)] = true;
				EnQueue(Q, G.vertice[Index(G, p->adjvex)].data);
			}
			p = p->next;
		}
	}
	if (len[Index(G, e)] != -858993460) {	//VS int型初始化值
		printf("\n---------------\n最短路径长度:%d", len[Index(G, e)]);
		printf("\n路径:%c", e);
		for (i = Index(G, path[Index(G, e)]); path[i] != '\0'; i = Index(G, path[i]))
			printf("<-%c", G.vertice[i].data);
		printf("<-%c", G.vertice[i].data);
	}
	else printf("\n无路径可从%c达结点%c", v, e);
}
int Index(ALGraph G, Verttype v) {
	for (int i = 0; i < G.vexnum; i++) 
		if (v == G.vertice[i].data) return i;
	return -1;
}
