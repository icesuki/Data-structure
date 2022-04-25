#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_LENGTH 100		//��̬���Ա����洢�ռ�
#define MAX_VERTEXNUM 100		//��󶥵���
#define Elemtype int
#define Stacktype char			//ջԪ������
#define Verttype char			//ͼ��������
#define OVERFLOW 0				//���
#define NOTFOUND 0				//���Ҳ���

bool visited[MAX_VERTEXNUM] = { false };	//���ʵ���۱���
int j = 1;	//��Ⱥ�۱���

/**************�ṹ��**************/
typedef struct SqList {					//˳���
	Elemtype data[MAX_LIST_LENGTH];
	int length;
}SqList;
typedef struct LinkNode{				//����
	Elemtype data;
	LinkNode* next;
}*pLinkNode;
typedef struct SqStack {				//˳��ջ
	Elemtype data[MAX_LIST_LENGTH];
	int top;
}SqStack;
typedef struct LinkStack {				//��ջ
	Stacktype data;
	LinkStack* next;
}*pLinkStack;
typedef struct SqQueue {				//˳�����
	Verttype data[MAX_LIST_LENGTH];
	int front;
	int rear;
}SqQuene;
typedef struct LinkQueue {				//��ʽ����
	pLinkNode front;
	pLinkNode rear;
}LinkQueue;
typedef struct TreeNode {				//��ʽ������
	char data;
	TreeNode* left;
	TreeNode* right;
}TNode,*pTNode;
/*****************�ڽӾ���ṹ�嶨��*****************/
typedef struct {
	Verttype Vex[MAX_VERTEXNUM];			//����
	bool Edge[MAX_VERTEXNUM][MAX_VERTEXNUM];			//����
	int vexnum, arcnum;			//������������
}AMGraph;
/*****************�ڽӱ�ṹ�嶨��*****************/
typedef struct ArcNode {				//�߱�ͬ����
	Verttype adjvex;
	ArcNode* next;
}*pArcNode;
typedef struct VerNode {				//˳�򶥱�
	Verttype data;
	pArcNode first;						//�߱�ͷ���
}VerNode, AdjList[MAX_VERTEXNUM];
typedef struct {
	AdjList vertice;
	int vexnum, arcnum;					//������������
}ALGraph;
/************˳�������*************/
void InitSqList(SqList&);							//��ʼ��
int GetSqListLen(SqList);							//��ȡ����
void GetSqListElement(SqList, int, Elemtype&);		//��ȡԪ��
int LocateSqList(SqList, Elemtype);					//��λ
void InsertSqList(SqList&, int, Elemtype);			//����Ų���
void DestroySqList(SqList&, int);					//�����ɾ��
void InsertSqListByNum(SqList&, Elemtype);			//��ֵ�������
/**************��������**************/
void InitLinkList(pLinkNode&);						//��ʼ��
int GetLinkListLen(pLinkNode);						//��ȡ����
void GetLinkListElement(pLinkNode, int, Elemtype&);	//��ȡԪ��
pLinkNode LocateLinkList(pLinkNode, Elemtype);		//����Ԫ��ָ��
int LocateLinkListByNum(pLinkNode, Elemtype);		//����Ԫ�����
void InsertLinkList(pLinkNode&, int, Elemtype);		//����Ų���
void DestroyLinkList(pLinkNode&, int);				//�����ɾ��
void InsertLinkListByNum(pLinkNode&, Elemtype);		//��ֵ�������
/**************˳��ջ����**************/
void InitSqStack(SqStack&);							//��ʼ��
bool EmptySqStack(SqStack);							//�Ƿ��
bool FullSqStack(SqStack);							//�Ƿ���
void GetSqTop(SqStack, Elemtype&);					//��ȡջ��Ԫ��
void PushSqStack(SqStack&, Elemtype);				//��ջ
void PopSqStack(SqStack&, Elemtype&);				//��ջ
/**************��ջ����**************/
void InitLinkStack(pLinkStack&);					//��ʼ��
bool EmptyLinkStack(pLinkStack);					//�Ƿ��
void GetLinkTop(pLinkStack, Stacktype&);			//��ȡջ��Ԫ��
void PushLinkStack(pLinkStack&, Stacktype);			//��ջ
void PopLinkStack(pLinkStack&, Stacktype&);			//��ջ
void ClearStack(pLinkStack&);						//���ջ
/**************ѭ����������**************/
void InitSqQueue(SqQueue& Q);						//��ʼ��
bool EmptySqQueue(SqQueue Q);						//�Ƿ��
bool FullSqQueue(SqQueue Q);						//�Ƿ���
void GetSqQueue(SqQueue Q, Verttype& num);			//��ȡ��ͷԪ��
void EnQueue(SqQueue& Q, Verttype num);				//���
void DeQueue(SqQueue& Q, Verttype& num);			//����
/**************��ʽ��������**************/
void InitLinkQueue(LinkQueue&);						//��ʼ��
void DestroyQueue(LinkQueue&);						//����
void EnLinkQueue(LinkQueue&, Elemtype);				//���
void DeQueue(LinkQueue&, Elemtype&);				//����
void GetLinkQueue(LinkQueue&, Elemtype&);			//��ȡ��ͷԪ��
bool EmptyLinkQueue(LinkQueue);						//�Ƿ��
/**************��ʽ����������**************/
void CreatLinkTree(pTNode&);						//����������
void PreOrder(pTNode);								//�������
void InOrder(pTNode);								//�������
void LatOrder(pTNode);								//�������
int DeepLinkTree(pTNode);							//���
/**************�ڽӾ�������**************/
void CreatGraph_AM(AMGraph&);						//�����ڽӾ���
int FirstNeighbor(AMGraph, Verttype);				//��һ�����ڵ�
int NextNeighbor(AMGraph, Verttype, Verttype);		//���ʹ��ĵ�������ڽڵ�
void BFS_AM(AMGraph, Verttype);						//�������
void BFS_AM_MIN(AMGraph, Verttype, Verttype);		//����������·��
int Index(AMGraph, Verttype);						//��������
/**************�ڽӱ�����**************/
void CreatGraph_AL(ALGraph&);						//�����ڽӱ�
int FirstNeighbor(ALGraph, Verttype);				//��һ�����ڽ��
int NextNeighbor(ALGraph, Verttype, Verttype);		//���ʹ��Ľ��������ڽ��
void BFS_AL(ALGraph, Verttype);						//�������
void BFS_AL_MIN(ALGraph, Verttype, Verttype);		//����������·��
int Index(ALGraph, Verttype);						//��������
/************˳���*************/
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
/***************����***************/
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
pLinkNode LocateLinkList(pLinkNode L, Elemtype num) {	//����0000000000000000Ϊ������
	pLinkNode p = L->next;
	while (p != NULL && p->data != num) p = p->next;
	return p;
}
int LocateLinkListByNum(pLinkNode L, Elemtype num) {	//����0Ϊ������
	pLinkNode p = L->next;
	int i = 1;
	while (p != NULL && p->data != num) p = p->next, i++;
	if (p) return i;
	else return 0;
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
	if (i <= 0) printf("This 'i' is not found"), exit(NOTFOUND);
	while (p != NULL && --i) p = p->next;
	if (NULL == p || NULL == p->next) printf("This 'i' is not found"), exit(NOTFOUND);
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
/***************˳��ջ***************/
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
///***************��ջ***************/
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
/***************ѭ������***************/
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
	if (Q.data[Q.front]) num = Q.data[Q.front];
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
/***************��ʽ����***************/
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
/**************��ʽ������**************/
void CreatLinkTree(pTNode& T) {
	char c = 0;
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
	int m, n;		//m��������� n���������
	if (NULL == T)  return 0; 		//��Ϊ��
	if (NULL == T->left && NULL == T->right) { printf("%c:%d,", T->data,j); return 1; }			//��ΪҶ��
	else {
		j++;
		m = DeepLinkTree(T->left);
		n = DeepLinkTree(T->right);
		j--;
	}
	if (m >= n) return m + 1;
	else return n + 1;
}
/************�ڽӾ���*************/
void CreatGraph_AM(AMGraph &G) {
	printf("������:");
	scanf_s("%d", &G.vexnum);
	if (!G.vexnum) printf("Vex error"), exit(0);		//����������
	printf("---------------\n����:");
	scanf_s("%d", &G.arcnum);
	if (G.arcnum > (G.vexnum * G.vexnum - 1) / 2) printf("Arc error"), exit(0);		//��������
	printf("---------------\n����:");
	for (int i = 0; i < G.vexnum; i++) scanf_s(" %c", &G.Vex[i], 1);		//��������
	for (int i = 0; i < G.arcnum; i++) {		//������
		char out, in;
		int one, two;
		printf("---------------\n����(��):");
		scanf_s(" %c", &out, 1);
		printf("����(��):");
		scanf_s(" %c", &in, 1);
		one = Index(G, out);
		two = Index(G, in);
		if (one < 0 || two < 0) printf("Vex index error"), exit(0);		//������Ŵ���
		G.Edge[one][two] = false;
		G.Edge[two][one] = false;
	}
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
void BFS_AM_MIN(AMGraph G, Verttype v,Verttype e) {
	int i, len[MAX_VERTEXNUM];			//����
	char path[MAX_VERTEXNUM] = {0};		//·��
	SqQueue Q;		//��������
	InitSqQueue(Q);
	len[Index(G, v)] = 0;
	visited[Index(G, v)] = true;
	EnQueue(Q, v);
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
	printf("\n---------------\n���·������:%d", len[Index(G, e)]);
	printf("\n·��:%c",e);
	for (i = Index(G, path[Index(G, e)]); path[i]!='\0'; i = Index(G, path[i]))
		printf("<-%c", G.Vex[i]);
	printf("<-%c", G.Vex[i]);
}
int Index(AMGraph G, Verttype v) {
	for (int i = 0; i < G.vexnum; i++) 
		if (v == G.Vex[i]) return i;
	return -1;
}
/************�ڽӱ�*************/
void CreatGraph_AL(ALGraph& G) {
	pArcNode N;
	printf("������:");
	scanf_s("%d", &G.vexnum);
	if (!G.vexnum) printf("Vex error"), exit(0);		//����������
	printf("---------------\n����:");
	scanf_s("%d", &G.arcnum);
	if (G.arcnum > (G.vexnum * G.vexnum - 1) / 2) printf("Arc error"), exit(0);		//��������
	printf("---------------\n����:");
	for (int i = 0; i < G.vexnum; i++) {		//��������
		scanf_s(" %c",&G.vertice[i].data,1);
		G.vertice[i].first = NULL;
	}
	for (int i = 0; i < G.arcnum; i++) {		//������
		char out, in;
		int one, two;
		printf("---------------\n����(��):");
		scanf_s(" %c", &out, 1);
		printf("����(��):");
		scanf_s(" %c", &in, 1);
		one = Index(G, out);
		two = Index(G, in);
		if (one < 0 || two < 0) printf("Vex index error"), exit(0);		//������Ŵ���
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
void BFS_AL(ALGraph G, Verttype v) {
	SqQueue Q;		//��������
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
}
void BFS_AL_MIN(ALGraph G, Verttype v, Verttype e) {
	int i, len[MAX_VERTEXNUM];			//����
	char path[MAX_VERTEXNUM] = { 0 };		//·��
	SqQueue Q;		//��������
	InitSqQueue(Q);
	len[Index(G, v)] = 0;
	visited[Index(G, v)] = true;
	EnQueue(Q, v);
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
	printf("\n---------------\n���·������:%d", len[Index(G, e)]);
	printf("\n·��:%c", e);
	for (i = Index(G, path[Index(G, e)]); path[i] != '\0'; i = Index(G, path[i]))
		printf("<-%c", G.vertice[i].data);
	printf("<-%c", G.vertice[i].data);
}
int Index(ALGraph G, Verttype v) {
	for (int i = 0; i < G.vexnum; i++) 
		if (v == G.vertice[i].data) return i;
	return -1;
}