#include<iostream>
#include<iomanip>
#include<stdio.h>
using namespace std;

///--------------�����ʵ��-------------------------------------
//  ��i�ڵ㿪ʼ����,nΪ�ڵ����� ��0��ʼ���� i�ڵ���ӽڵ�Ϊ 2*i+1, 2*i+2
void MaxHeapFixdown(int a[], int i, int n)
{
    int j, temp;

	temp = a[i];
	j = 2 * i + 1; //���ӽڵ㣬
	while (j < n) 
	{
		if (j + 1 < n && a[j + 1] > a[j]) //�����Һ�����������
			j++;

		if (a[j] <= temp)
			break;

		a[i] = a[j];     //�ѽϴ���ӽ�������ƶ�,�滻���ĸ����
		i = j;//��ǰ�ӽڵ�����Ϊ���ڵ�
		j = 2 * i + 1; //�������ӽڵ������
	}
	a[i] = temp;
}

//��������
void MakeMaxHeap(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapFixdown(a, i, n);
}

//������
void MaxheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		swap(a[i], a[0]); //a[0]һ��ʼ������С��Ԫ�أ�����һ�£����������1�����������1
		MaxHeapFixdown(a, 0, i);
	}
} 
int a[250001];
int main(void)
{
	int N;
	//cin>>N;
	scanf("%d",&N);
	for(int i=0;i<=N/2;i++)
		scanf("%d",&a[i]);
		//cin>>a[i];
	
	MakeMaxHeap(a,N/2+1);
	int tmp;
	int lim=N/2+N%2;
	for(int i=1;i<lim;i++)
	{
		//cin>>tmp;
		scanf("%d",&tmp);
		if(tmp<a[0])
		{
			a[0]=tmp;
			MaxHeapFixdown(a,0,N/2+1);
		}
	}
	MaxheapsortTodescendarray(a,N/2+1);
	if(N%2==0)
		printf("%.1f\n",(double(a[N/2])+a[N/2-1])/2.0);
		//cout<<fixed<<setprecision(1)<<(double(a[N/2])+a[N/2-1])/2.0<<endl;
	else
		printf("%.1f\n",(a[N/2]/1.0));
		//cout<<fixed<<setprecision(1)<<a[N/2]/1.0<<endl;
	return 0;
}


/*
6
5 8 7 9 6 4

7
1 7 8 9 3 6 5

7
1 7 8 8 9 1 1
10



1 1 1 1 1 7 8 9 10 12

��������ʱ�����ǵ��ö�����
��cinҲ��ʱ�����ǵ���C�������
	vector<int> a;
	int N;
	scanf("%d",&N);
	//cin>>N;
	int val;
	for(int i=0;i<=N/2;i++){
		//cin>>val;
		scanf("%d",&val);
		a.push_back(val);
	}
	sort(a.begin(),a.end());

	int tmp;
	int left=0;
	int right=0;
	int lim=N/2+N%2;
	for(int i=1;i<lim;i++)
	{
		//cin>>tmp;
		scanf("%d",&tmp);
		if(tmp< a[0]) left++;
		else if(tmp>a[N/2])right++;
		else
		{
			a[N/2]=tmp;
			sort(a.begin(),a.end());
			right++;
		}
	}
	if(N%2==0)
		printf("%.1f\n",(float)(a[N/2-left-1]+a[N/2-left])/2.0);
		//cout<<fixed<<setprecision(1)<<(float)(a[N/2-left-1]+a[N/2-left])/2.0<<endl;
	else
		printf("%.1d\n",a[N/2-left]);
		//cout<<a[N/2-left]<<endl;
	return 0;

*/