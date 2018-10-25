#include<iostream>
#include<algorithm>
#include<memory.h>
#include<stdio.h>
using namespace std;

unsigned short int a[100][1000000];

 #define MIN -1//这里开始的时候出现了一个BUG，如果定义的MIN大于等于待排序的数，则会是算法出现错误
 #define MAX 10000000//最大值，附加在归并文件结尾

int b[101];
int ls[100];

void Adjust(int s,int k)
{//沿从叶子节点b[s]到根节点ls[0]的路径调整败者树
	int t=(s+k)/2;//ls[t]是b[s]的双亲节点
	while(t>0)
	{
		if(b[s]>b[ls[t]])//如果失败，则失败者位置s留下，s指向新的胜利者 
		{//如果子节点大于父节点，则把ls[t](父节点下标)与S(子节点下标)交换
			int tmp=s;
			s=ls[t];
			ls[t]=tmp;
		}
		t=t/2; //继续求其双亲结点在ls中的坐标
	}
	ls[0]=s;//ls[0]存放调整后的最小值的位置
}


void CreateLoserTree(int k)
{
    b[k]=MIN;//额外的存储一个最小值
    for(int i=0;i<k;i++)
		ls[i]=k;//先初始化为指向最小值，这样后面的调整才是正确的
		//这样能保证非叶子节点都是子树中的“二把手”
    for(int i=k-1;i>=0;i--)
        Adjust(i,k);//依次从b[k-1],b[k-2]...b[0]出发调整败者树
}
 



int main(void)
{
	int T;
	int K,N;


	int min;
	int ind[100];
	//cin>>T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
	{
	//	cin>>K>>N;
		scanf("%d%d",&K,&N);
		for(int j=0;j<K;j++)
		{
			for(int l=0;l<N;l++)
				//cin>>a[j][l];
				scanf("%d",&a[j][l]);
		}
		for(int j=0;j<K;j++)
		{
			b[j]=a[j][0];
		}
		memset(ind,0,sizeof(int)*100);
		CreateLoserTree(K);
		int q;
		while(1)//
		{
			q=ls[0];//q用来存储b中最小值的位置，同时也对应一路文件
			printf("%d ",b[q]);
			//input(b[q],q);
			++ind[q];
			int ext=0;
			for(int i=0;i<K;i++)
			{
				if(ind[i]>=N) ext++;
			}
			if(ext>=K) break;
			if(ind[q]>=N)
				b[q]=MAX;
			else
				b[q]=a[q][ind[q]];
			//fscanf(farray[q],"%d",&b[q]);
			Adjust(q,K);
		}
			//cout<<min<<" ";
		//cout<<endl;
		printf("\n");
	}//for
	return 0;
}


/*
耗时0.77秒 没有显著改善
2
3 3
1 2 3
7 8 9
4 5 6
4 3
1 3 5
2 8 9
1 5 8
2 7 9
3 3
1 2 3
7 8 9
4 5 6
3 3
3 3 3
3 3 3
3 3 3


每次挑出最小数时，用最原始的比较方法，超时,
得改用败者树
int T;
	int K,N;

	int data[100];
	int last[100]={0};
	int min;
	int ind;
	//cin>>T;
	scanf("%d",&T);
	for(int i=0;i<T;i++)
	{
	//	cin>>K>>N;
		scanf("%d%d",&K,&N);
		for(int j=0;j<K;j++)
		{
			for(int l=0;l<N;l++)
				//cin>>a[j][l];
				scanf("%d",&a[j][l]);
		}
		memset(last,0,sizeof(int)*100);
		for(int h=0; h<K   ;h++)
			data[h]=a[h][0];
		while(1)
		{
			int cou=0;
			for(int h=0;h<K;h++)
			{
				if(last[h]>=N)
					cou++;
			}
			if(cou>=K) break;
			min=199999999;
			ind=0;
			for(int j=0;j<K;j++)
			{
				if(last[j]<N &&  min>data[j])
				{
					min=data[j];
					ind=j; 
				}
			}
			++last[ind];
			data[ind]=a[ind][last[ind]];
			//cout<<min<<" ";
			printf("%d ",min);
		}//while
		//cout<<endl;
		printf("\n");
	}//for



*/
