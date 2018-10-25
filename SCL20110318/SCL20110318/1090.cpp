#include<iostream>
#include<algorithm>
using namespace std;

typedef int adjmatrix[510][510];

const int MaxValue =1000000;
struct edgeset  //�洢��С�������Ľṹ��
{
	int formvex;
	int endvex;
	int weight;
};



//����Prim�㷨�Ӷ���Va�������ͼ����С������
//ͼ���ڽӾ����ʾ����С�������ı߼���������CT��
void Prim(adjmatrix GA,edgeset CT[],int a,int n)
{
	int i,j,k,min,t,m,w;
	//��CT����ֵ����Ӧ��0�ε���̱ߺϼ�
	for(i=0;i<n;i++){
		k=i;
		if(i>a) k--;
		CT[k].formvex=a;
		CT[k].endvex=i;
		CT[k].weight=GA[a][i];
		
	}
	//����n-1��ѭ����ÿ�������С�������еĵ�K����
	for(k=1;k<n;k++){
		min=MaxValue;//��CT[k-1]~CT[n-2]�У�����̱ߺϼ���������̱�CT[m]
		m=k-1;
		for(j=k-1;j<n-1;j++){
			if(CT[j].weight<min)
			{
				min=CT[j].weight;
				m=j;
			}
		}
		edgeset temp=CT[k-1]; //����̱߶Ե�����K-1�±�λ��
		CT[k-1]=CT[m];
		CT[m]=temp;
		j=CT[k-1].endvex;//���¼��뵽��С������T�еĶ�����Ÿ���j
		for(i=k;i<n-1;i++){//�޸���̱߼��ϣ�ʹÿ�����㶼ά��һ����̱�
			t=CT[i].endvex;
			w=GA[j][t];
			if(w<CT[i].weight){
				CT[i].weight=w;
				CT[i].formvex=j;
			}
		}
	}
}

bool cmp(edgeset a,edgeset b )
{
	return (a.weight<b.weight);
}

adjmatrix GA;
edgeset CT[510];

int main(void)
{
	int i,j,k;
	int t,n;	
	cin>>t;	
	bool e=false;
	for(i=0;i<t;i++){
		if(e) cout<<endl;
		e=true;
		cin>>n;	
		//��ʼ���ڽӾ���
		for(k=0;k<n;k++){
			for(j=0;j<n;j++){
				if(k==j)GA[k][j]=0;  //�Լ����Լ�Ϊ0
				else GA[k][j]=MaxValue;//���ɴ�ΪMaxValue
			}
		}
		for(k=0;k<n;k++){
			for(j=0;j<n;j++){
				cin>>GA[k][j];
			}
		}	
		Prim(GA ,CT,1,n);
		sort(CT,CT+n-1,cmp);
		cout<<CT[n-2].weight<<endl;
	}
	return 0;
}


/*
T
 N (3 <= N <= 500), which is the number of villages
 Then come N lines, the i-th of which contains N integers, 
 and the j-th of these N integers is the distance 
 (the distance should be an integer within [1, 65536])
 between village i and village j. 
2

3
0 990 692
990 0 179
692 179 0




6
0 15 7 4 12 100000
15 0 100000 100000 10 100000
7 100000 0 8 5 25
4 100000 8 0 100000 16
12 10 5 100000 0 100000
100000 100000 25 16 100000 0

692

*/


