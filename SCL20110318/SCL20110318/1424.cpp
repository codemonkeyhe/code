#include<iostream>
#include<memory.h>

using namespace std;
//图的最大顶点数，要大于等于具体图的顶点数n;
const int MaxVertexNum=10010;
//图的邻接表
struct edgenode
{
	int adjvex;   //邻接点域，存放相邻接的节点
	edgenode *next; //下一结点的指针
};

//定义adjlist为存储n个表头指针的数组类型
typedef edgenode* adjlist[MaxVertexNum];

//对邻接表GL表示的具有n个顶点的有向图进行拓扑排序
int Toposort(adjlist GL,int n)
{
	int i,j,k,top,m=0; //m用来统计拓扑序列的顶点数
	int tol=0;
	int *wage=new int [n+1];
	for(i=1;i<=n;i++) wage[i]=100;
	edgenode *p;
	int *d=new int [n+1]; //d存放每个顶点的入度
	for(i=0;i<=n;i++) d[i]=0;//初始化数组
	for(i=0;i<=n;i++){//将邻接表的每个顶点的出度统计到入度数组d中
		p=GL[i];
		while(p!=NULL){
			j=p->adjvex;
			d[j]++;
			p=p->next;
		}
	}
	top=-1;//栈底值定义为-1，top为栈顶指针
	for(i=1;i<=n;i++){//建立入度为0的链栈
		if(d[i]==0){
			d[i]=top;
			top=i;
		}
	}
	while(top!=-1)//每循环一次删除一个入度为0的顶点以及相应的所有出边
	{
		j=top;   //j为当前入度为0的节点
		top=d[top];//栈顶指针下移，即把当前入度为0的节点出栈
		//cout<<j<<' ';  //因为顶点Vj对应的入度数组d的下标（0~N-1）,可以再次加一得到原来的下标
		m++;//拓扑序列顶点个数加1
		p=GL[j];//p指向当前入度为0的节点Vj所在的邻接表的表头位置	
		while(p!=NULL){//把和Vj相邻接的所有顶点的入度全部减一，代表着删除了相应的入边
			k=p->adjvex;
			if(wage[k]<=wage[j]) wage[k]=wage[j]+1;
			d[k]--;
			if(d[k]==0) {//如果入度为0，则把该节点加入到链栈的栈顶
				d[k]=top;top=k;
			}
			p=p->next;
		}	
	}
	for(i=1;i<=n;i++)
	{
		tol=tol+wage[i];
	}
	if(m<n) return -1;
	else return tol;
	delete []d;

}

int main(void)
{


	adjlist GL;
	int i,j,k,w;
	int n,e;
	cin>>n>>e;//输入顶点数以及边数
	//初始化邻接表
	for(i=0;i<=n;i++) GL[i]=NULL;
	//建立有向图邻接表,输入两端点i,j及边上的权w
	for(k=1;k<=e;k++)
	{
		cin>>i>>j;
		edgenode* p=new edgenode;
		p->adjvex=i;
		p->next=GL[j];//将新节点插入到Vi邻接表的表头
		GL[j]=p;
	}
	w=Toposort( GL, n);
	if(w!=-1) cout<<w<<endl;
	else cout<<"Poor Xed"<<endl;
	return 0;
}

/*

一次AC，采用模板
5 4
1 2
4 1
3 1
4 3

7 6
3 1
1 2
1 7
6 2
4 1
4 3

7 6
3 1
1 2
1 7
6 2
1 4
4 3

*/