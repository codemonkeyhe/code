#include<iostream>
#include<algorithm>
#include<memory.h>
#include<stdio.h>
using namespace std;

unsigned short int a[100][1000000];

 #define MIN -1//���￪ʼ��ʱ�������һ��BUG����������MIN���ڵ��ڴ����������������㷨���ִ���
 #define MAX 10000000//���ֵ�������ڹ鲢�ļ���β

int b[101];
int ls[100];

void Adjust(int s,int k)
{//�ش�Ҷ�ӽڵ�b[s]�����ڵ�ls[0]��·������������
	int t=(s+k)/2;//ls[t]��b[s]��˫�׽ڵ�
	while(t>0)
	{
		if(b[s]>b[ls[t]])//���ʧ�ܣ���ʧ����λ��s���£�sָ���µ�ʤ���� 
		{//����ӽڵ���ڸ��ڵ㣬���ls[t](���ڵ��±�)��S(�ӽڵ��±�)����
			int tmp=s;
			s=ls[t];
			ls[t]=tmp;
		}
		t=t/2; //��������˫�׽����ls�е�����
	}
	ls[0]=s;//ls[0]��ŵ��������Сֵ��λ��
}


void CreateLoserTree(int k)
{
    b[k]=MIN;//����Ĵ洢һ����Сֵ
    for(int i=0;i<k;i++)
		ls[i]=k;//�ȳ�ʼ��Ϊָ����Сֵ����������ĵ���������ȷ��
		//�����ܱ�֤��Ҷ�ӽڵ㶼�������еġ������֡�
    for(int i=k-1;i>=0;i--)
        Adjust(i,k);//���δ�b[k-1],b[k-2]...b[0]��������������
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
			q=ls[0];//q�����洢b����Сֵ��λ�ã�ͬʱҲ��Ӧһ·�ļ�
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
��ʱ0.77�� û����������
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


ÿ��������С��ʱ������ԭʼ�ıȽϷ�������ʱ,
�ø��ð�����
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
