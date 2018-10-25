#include<iostream>
#include<memory.h>
using namespace std;

const int MaxVertexNum=210;
typedef int vexlist[MaxVertexNum];
//����adjmatrixΪ�ڽӾ���
typedef int adjmatrix[MaxVertexNum][MaxVertexNum];
const int MaxValue=100000;//���Ȩֵ
bool visited[MaxVertexNum];//������ʱ�����飬��ʼ��Ϊfalse

bool dfsGraMat(adjmatrix GA,int i,int n)
{
	if(i==n-1){ return true;}
	//cout<<i<<' ';//���ʶ���Viʱ����ö������ţ��ڴ˿������Ӧ������
	visited[i]=true;//��ǽڵ�Vi�ѱ����ʹ�
	for(int j=0;j<n;j++){//���α���Vi��ÿ���ڽӵ�
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
					GA[i][j]=0;  //�Լ����Լ�Ϊ0
				else 
					GA[i][j]=MaxValue;//���ɴ�ΪMaxValue
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