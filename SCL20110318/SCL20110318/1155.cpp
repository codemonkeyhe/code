#include<iostream>
#include<memory.h>
using namespace std;

const int MaxVertexNum=210;
typedef int vexlist[MaxVertexNum];
//定义adjmatrix为邻接矩阵
typedef int adjmatrix[MaxVertexNum][MaxVertexNum];
const int MaxValue=100000;//最大权值
bool visited[MaxVertexNum];//顶点访问标记数组，初始化为false

bool dfsGraMat(adjmatrix GA,int i,int n)
{
	if(i==n-1){ return true;}
	//cout<<i<<' ';//访问顶点Vi时输出该顶点的序号，在此可添加响应处理函数
	visited[i]=true;//标记节点Vi已被访问过
	for(int j=0;j<n;j++){//依次遍历Vi的每个邻接点
		if(GA[i][j]!=0 && GA[i][j]!=MaxValue && !visited[j])
			if(dfsGraMat(GA,j,n)) return true;
	}
	return false;
}


int main(void)
{
	int n,m;
	int i,j,k;
	adjmatrix GA;
	while(cin>>n>>m,n!=0)
	{	
		memset(visited,false,sizeof(bool)*MaxVertexNum);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(i==j)
					GA[i][j]=0;  //自己到自己为0
				else 
					GA[i][j]=MaxValue;//不可达为MaxValue
			}
		}
		for(i=0;i<m;i++)
		{
			cin>>k>>j;
			GA[k][j]=1;
		}
		if(dfsGraMat(GA,0,n))
			cout<<"I can post the letter"<<endl;
		else 
			cout<<"I can't post the letter"<<endl;
	}
	return 0;
}


/*
(N<=200, M<=N*N/2), 
 means the number of citys and the number of roads.
 And Merlin stands at city N-1. 
 After that, there are M lines. 
 Each line contains two integers i and j,
 what means that there is a road from city i to city j.
The input is terminated by N=0.


3
2
0 1
1 2
3
1
0 1
0

9
18
0 1 
1 0 
1 2 
2 1 
3 5 
4 5 
5 4 
4 8 
8 4 
5 6 
6 5 
6 7 
7 6 
7 8 
8 7 
7 5 
6 8 
8 6 


I can post the letter
I can't post the letter

*/