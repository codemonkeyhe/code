#include<iostream>
#include<stdio.h>
using namespace std;
int sco[110][110];
int minv[110];
int maxv[110];
int main(void)
{
	int t;
	int n,m;
	int i,j,k;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n>>m;
		for(j=0;j<m;j++)
		{
			minv[j]=9999;
			maxv[j]=0;
		}
		for(j=0;j<n;j++){
			for(k=0;k<m;k++)
			{	
				cin>>sco[j][k];
				if(minv[k]>sco[j][k]) minv[k]=sco[j][k];
				if(maxv[k]<sco[j][k]) maxv[k]=sco[j][k];
			}
		}
		for(j=0;j<m;j++){
			double sum=0;
			for(k=0;k<n;k++)
				sum=sum+sco[k][j];
			sum=(sum-minv[j]-maxv[j])/(double)(n-2);
			printf("%.2f\n",sum);
		}

			
	}
	return 0;
}

/*
һ��AC����㳬ʱ
��һ������������ n m (3 <= n,m <= 100),��ʾ�� n �� �� ί , m��ѡ��
1
3 4
1 2 3 4
1 2 3 4
1 2 3 4

������� 2 λС��
1.00
2.00
3.00
4.00


*/