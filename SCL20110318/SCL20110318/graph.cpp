#include<iostream>
#include<memory.h>
#include<stack>
#include<queue>
using namespace std;


//图的最大顶点数，要大于等于具体图的顶点数n;
const int MaxVertexNum=100;
//图的最大边数，要大于等于具体图的边数e;
const int MaxEdgeNum=10000;
//定义vexlist为存储顶点信息的数组
//VertexType为用户事先确定的顶点值类型，例如char或者string。
//其实就是相当于顶点信息和矩阵顶点建立一一映射的关系,在输入数据时可能需要建立这种映射转换
//typedef VertexType vexlist[MaxVertexNum];
typedef int vexlist[MaxVertexNum];
//定义adjmatrix为邻接矩阵
typedef int adjmatrix[MaxVertexNum][MaxVertexNum];
const int MaxValue=100000;//最大权值
bool visited[MaxVertexNum];//顶点访问标记数组，初始化为false



//建立无向(有向)图的邻接矩阵
//形参列表：顶点信息数组，邻接矩阵,顶点数，边数
//若不需要存储顶点信息，则可删去参数1
//有些题可能连n,e都不提供，则分解此程序。
void CreGraMatrix(vexlist GV,adjmatrix GA,int n,int e)
{
	int i,j,k,w;
	//建立顶点信息数组，
	for(i=0;i<n;i++)
		cin>>GV[i];
	//初始化邻接矩阵
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)GA[i][j]=0;  //自己到自己为0
			else GA[i][j]=MaxValue;//不可达为MaxValue
		}
	}
	//建立无向图邻接矩阵,输入两端点i,j及边上的权w
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		GA[i][j]=w;
		GA[j][i]=w;//**若去掉此句话则变为建立有向图邻接矩阵
	}
}


//从初始节点i出发深度优先搜索由邻接矩阵构成的图
//***适用于连通图的遍历
void dfsGraMat(adjmatrix GA,int i,int n)
{
	cout<<i<<' ';//访问顶点Vi时输出该顶点的序号，在此可添加响应处理函数
	visited[i]=true;//标记节点Vi已被访问过
	for(int j=0;j<n;j++){//依次遍历Vi的每个邻接点
		if(GA[i][j]!=0 && GA[i][j]!=MaxValue && !visited[j])
			dfsGraMat(GA,j,n);
	}
}

//从初始节点i出发深度优先搜索由邻接矩阵构成的图
//用堆栈实现的非递归算法
//***适用于连通图的遍历
void dfsGraMat1(adjmatrix GA,int i,int n)
{
	stack<int> S;
	S.push(i);//初始节点Vi进栈
	while(!S.empty())//栈非空时进行循环操作
	{
		int k=S.top();
		S.pop();
		if(!visited[k])//若Vk没被访问过
		{
			cout<<k<<' ';//访问Vk
			visited[k]=true;//标记Vk已被访问过
			for(int j=0;j<n;j++){//把和Vk邻接的且未被访问过的顶点压栈
			if(GA[k][j]!=0 && GA[k][j]!=MaxValue && !visited[j])
				S.push(j);
			}
		}
		//若访问过则继续循环	
	}
}


//从初始节点i出发宽度优先搜索由邻接矩阵构成的图
//用队列实现的非递归算法
//***适用于连通图的遍历
void bfsGraMat(adjmatrix GA,int i,int n)
{
	queue<int> S;
	cout<<i<<' ';
	visited[i]=true;
	S.push(i);
	while(!S.empty())
	{
		int k=S.front();
		S.pop();
		for(int j=0;j<n;j++){//把和Vk邻接的且未被访问过的顶点先访问，再入队
			if(GA[k][j]!=0 && GA[k][j]!=MaxValue && !visited[j]){	
				cout<<j<<' ';
				visited[j]=true;
				S.push(j);		
			}
		}
	}
}

//****************************************************************
//图的邻接表
struct edgenode
{
	int adjvex;   //邻接点域，存放相邻接的节点
	int weight;	  //权值域
	edgenode *next; //下一结点的指针
};
//定义adjlist为存储n个表头指针的数组类型
typedef edgenode* adjlist[MaxVertexNum];


//建立有向(无向)图的邻接表
//形参列表：顶点信息数组，邻接表,顶点数，边数
//若不需要存储顶点信息，则可删去参数1
//有些题可能连n,e都不提供，则分解此程序。
void CreGralist(vexlist GV,adjlist GL,int n,int e)
{
	int i,j,k,w;
	//建立顶点信息数组，
	for(i=0;i<n;i++)
		cin>>GV[i];
	//初始化邻接表
	for(i=0;i<n;i++) GL[i]=NULL;
	//建立有向图邻接表,输入两端点i,j及边上的权w
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		edgenode* p=new edgenode;
		p->adjvex=j;
		p->next=GL[i];//将新节点插入到Vi邻接表的表头
		GL[i]=p;
		//若添加以下这段则变为建立无向图邻接表
		/*p->adjvex=i;
		p->next=GL[j];
		GL[j]=p;*/
		//delete p;
	}
}


//从初始节点i出发深度优先搜索由邻接表构成的图
//***适用于连通图的遍历
void dfsGraList(adjlist GL,int i,int n)
{
	cout<<i<<' ';//访问顶点Vi时输出该顶点的序号，在此可添加响应处理函数
	visited[i]=true;//标记节点Vi已被访问过
	edgenode* p=GL[i];
	while(p!=NULL){//依次遍历Vi的每个邻接点		
		int j=p->adjvex;
		if(!visited[j])
			dfsGraList(GL,j,n); 
		p=p->next;
	}
}

//从初始节点i出发深度优先搜索由邻接表构成的图
//用堆栈实现的非递归算法
//***适用于连通图的遍历
void dfsGraList1(adjlist GL,int i,int n)
{
	stack<int> S;
	S.push(i);//初始节点Vi进栈
	while(!S.empty())//栈非空时进行循环操作
	{
		int k=S.top();
		S.pop();
		if(!visited[k])//若Vk没被访问过
		{
			cout<<k<<' ';//访问Vk
			visited[k]=true;//标记Vk已被访问过
			edgenode * p=GL[k];
			while(p!=NULL){
				int j=p->adjvex;
				if(!visited[j])
					S.push(j);
				p=p->next;
			}
		}
		//若访问过则继续循环	
	}
}


//从初始节点i出发宽度优先搜索由邻接表构成的图
//用队列实现的非递归算法
//***适用于连通图的遍历
void bfsGraList(adjlist GL,int i,int n)
{
	queue<int> S;
	cout<<i<<' ';
	visited[i]=true;
	S.push(i);
	while(!S.empty())
	{
		int k=S.front();
		S.pop();
		edgenode *p=GL[k];
		while(p!=NULL)//把和Vk邻接的且未被访问过的顶点先访问，再入队
		{
			int j=p->adjvex;
			if(!visited[j]){
				cout<<j<<' ';
				visited[j]=true;
				S.push(j);
			}
			p=p->next;
		}
	}
}


//非连通图的邻接阵遍历
void dfsGraLisUncne(adjlist GL,int n)
{
	for(int i=0;i<n;i++){	
		if(!visited[i])
			bfsGraList(GL,i,n);
	}
}


//非连通图的邻接阵遍历
void dfsGraMatUncne(adjmatrix GA,int n)
{
	for(int i=0;i<n;i++){
		if(!visited[i])
			//此处可以添加任何遍历算法，在此以dfsGraMat为例
		 //dfsGraMat(GA,i,n);
		 bfsGraMat(GA,i,n);
	}
}

//测试数据，有向图
const int NUM_VERTICE=9;
int graph[NUM_VERTICE][NUM_VERTICE]=
{
	{0, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 1, 1},
	{0, 0, 0, 0, 0, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 1, 0}
};


const int NUMV=6;
int minsptre[NUMV][NUMV]=
{
	{0,			15,		7,		4,		12,		MaxValue},
	{15,		0,		MaxValue,MaxValue,10,	MaxValue},
	{7,			MaxValue, 0,	8,		5,			25},
	{4,			MaxValue, 8,	0,		MaxValue,	16},
	{12,		10,		5,		MaxValue,0,		MaxValue},
	{MaxValue,	MaxValue,25,	16,		MaxValue,	0},
};



//-------------------------------------------------------------

struct edgeset  //存储最小生成树的结构体
{
	int formvex;
	int endvex;
	int weight;
};
//struct mint edgeset[100];


//利用Prim算法从顶点Va出发求出图的最小生成树
//图用邻接矩阵表示，最小生成树的边集存于数组CT中
void Prim(adjmatrix GA,edgeset CT[],int a,int n)
{
	int i,j,k,min,t,m,w;
	//给CT赋初值，对应第0次地最短边合集
	for(i=0;i<n;i++){
		k=i;
		if(i>a) k--;
		CT[k].formvex=a;
		CT[k].endvex=i;
		CT[k].weight=GA[a][i];
		
	}
	//进行n-1次循环，每次求出最小生成树中的第K条边
	for(k=1;k<n;k++){
		min=MaxValue;//从CT[k-1]~CT[n-2]中（即最短边合集）查找最短边CT[m]
		m=k-1;
		for(j=k-1;j<n-1;j++){
			if(CT[j].weight<min)
			{
				min=CT[j].weight;
				m=j;
			}
		}
		edgeset temp=CT[k-1]; //把最短边对调到第K-1下标位置
		CT[k-1]=CT[m];
		CT[m]=temp;
		j=CT[k-1].endvex;//把新加入到最小生成树T中的顶点序号赋给j
		for(i=k;i<n-1;i++){//修改最短边集合，使每个顶点都维持一条最短边
			t=CT[i].endvex;
			w=GA[j][t];
			if(w<CT[i].weight){
				CT[i].weight=w;
				CT[i].formvex=j;
			}
		}
	}
}


//---------------------------------------------------------------
//对邻接表GL表示的具有n个顶点的有向图进行拓扑排序
void Toposort(adjlist GL,int n)
{
	int i,j,k,top,m=0; //m用来统计拓扑序列的顶点数
	edgenode *p;
	int *d=new int [n]; //d存放每个顶点的入度
	for(i=0;i<n;i++) d[i]=0;//初始化数组
	for(i=0;i<n;i++){//将邻接表的每个顶点的出度统计到入度数组d中
		p=GL[i];
		while(p!=NULL){
			j=p->adjvex;
			d[j]++;
			p=p->next;
		}
	}
	top=-1;//栈底值定义为-1，top为栈顶指针
	for(i=0;i<n;i++){//建立入度为0的链栈
		if(d[i]==0){
			d[i]=top;
			top=i;
		}
	}
	while(top!=-1)//每循环一次删除一个入度为0的顶点以及相应的所有出边
	{
		j=top;   //j为当前入度为0的节点
		top=d[top];//栈顶指针下移，即把当前入度为0的节点出栈
		cout<<j<<' ';  //因为顶点Vj对应的入度数组d的下标（0~N-1）,可以再次加一得到原来的下标
		m++;//拓扑序列顶点个数加1
		p=GL[j];//p指向当前入度为0的节点Vj所在的邻接表的表头位置
		while(p!=NULL){//把和Vj相邻接的所有顶点的入度全部减一，代表着删除了相应的入边
			k=p->adjvex;
			d[k]--;
			if(d[k]==0) {//如果入度为0，则把该节点加入到链栈的栈顶
				d[k]=top;top=k;
			}
			p=p->next;
		}
	}
	cout<<endl;
	if(m<n) cout<<"存在回路"<<endl;
	delete []d;

}

int main(void)
{
	//邻接阵图遍历测试
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMat(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMat1(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//bfsGraMat(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMatUncne(graph,9);

	//邻接表图遍历测试
	//adjlist GL;
	//int i,j,k,w;
	//int n,e;
	//cin>>n>>e;//输入顶点数以及边数
	//初始化邻接表
	//for(i=0;i<n;i++) GL[i]=NULL;
	//建立无向图邻接表,输入两端点i,j及边上的权w
	//for(k=1;k<=e;k++)
	//{
	//	cin>>i>>j>>w;
	//	edgenode* p=new edgenode;
	//	p->adjvex=j;
	//	p->next=GL[i];//将新节点插入到Vi邻接表的表头
	//	GL[i]=p;
	//}
	//dfsGraList(GL,3,9);
	//dfsGraList1(GL,3,9);
	//bfsGraList(GL,1,9);
	//dfsGraLisUncne( GL,9);

	//最小生成树测试
	//edgeset CT[6];
	//Prim(minsptre,CT,1,6);
	//cin.get();

	//邻接表拓扑测试
	adjlist GL;
	int i,j,k,w;
	int n,e;
	cin>>n>>e;//输入顶点数以及边数
	//初始化邻接表
	for(i=0;i<n;i++) GL[i]=NULL;
	//建立有向图邻接表,输入两端点i,j及边上的权w
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		edgenode* p=new edgenode;
		p->adjvex=j;
		p->next=GL[i];//将新节点插入到Vi邻接表的表头
		GL[i]=p;
	}
	Toposort( GL, n);
	return 0;
}
/*
9
18
0 1 1
1 0 1
1 2 1
2 1 1
3 5 1
4 5 1
5 4 1
4 8 1
8 4 1
5 6 1
6 5 1
6 7 1
7 6 1
7 8 1
8 7 1
7 5 1
6 8 1
8 6 1


12
15
0 5 1
1 3 1
2 3 1
2 4 1
2 5 1
3 4 1
4 6 1
4 9 1
5 6 1
5 8 1
5 10 1
6 7 1
6 8 1
9 10 1
9 11 1


12
14
0 5 1
1 3 1
2 3 1
2 4 1
2 5 1
3 4 1
4 6 1
4 9 1
5 6 1
5 8 1
5 10 1
6 7 1
6 8 1
9 10 1

*/
 