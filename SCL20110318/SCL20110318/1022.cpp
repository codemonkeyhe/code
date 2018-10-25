#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<stdio.h>
#include<memory.h>
using namespace std;
////--------------С����ʵ��-------------------------------------
//  �¼���i���  �丸���Ϊ(i - 1) / 2
void MinHeapFixup(int a[], int i) 
{
    int j,temp;
	
	temp = a[i]; //Ҫ����Ľڵ��ֵ
	j = (i - 1) / 2;      //�����
	while (j >= 0 && i != 0)
	{
		if (a[j] <= temp)//����Ҫ�������ӽڵ㣬�������
			break;
		
		a[i] = a[j];     //�ѽϴ���ӽ�������ƶ�,�滻�����ӽ��
		i = j;      //��ǰ��iΪ�ӽڵ�
		j = (i - 1) / 2; //�������丸�ڵ�
	}
	a[i] = temp;
}

//����С���м����µ�����nNum,n��ʾ�����λ�ã�Ϊ�������Ԫ�ص���һ��λ��
void MinHeapAddNumber(int a[], int n, int nNum) 
{
	a[n] = nNum;
	MinHeapFixup(a, n);
}

//  ��i�ڵ㿪ʼ����,nΪ�ڵ����� ��0��ʼ���� i�ڵ���ӽڵ�Ϊ 2*i+1, 2*i+2
void MinHeapFixdown(int a[], int i, int n)
{
    int j, temp;

	temp = a[i];
	j = 2 * i + 1; //���ӽڵ㣬
	while (j < n) 
	{
		if (j + 1 < n && a[j + 1] < a[j]) //�����Һ���������С��
			j++;

		if (a[j] >= temp)
			break;

		a[i] = a[j];     //�ѽ�С���ӽ�������ƶ�,�滻���ĸ����
		i = j;//��ǰ�ӽڵ�����Ϊ���ڵ�
		j = 2 * i + 1; //�������ӽڵ������
	}
	a[i] = temp;
}

////--------------�����ʵ��-------------------------------------
//  �¼���i���  �丸���Ϊ(i - 1) / 2
void MaxHeapFixup(int a[], int i) 
{
    int j,temp;
	
	temp = a[i]; //Ҫ����Ľڵ��ֵ
	j = (i - 1) / 2;      //�����
	while (j >= 0 && i != 0)
	{
		if (a[j] >= temp)//����Ҫ�������ӽڵ㣬�������
			break;
		
		a[i] = a[j];     //�ѽ�С���ӽ�������ƶ�,�滻�����ӽ��
		i = j;      //��ǰ��iΪ�ӽڵ�
		j = (i - 1) / 2; //�������丸�ڵ�
	}
	a[i] = temp;
}

//�������м����µ�����nNum,n��ʾ�����λ�ã�Ϊ�������Ԫ�ص���һ��λ��
void MaxHeapAddNumber(int a[], int n, int nNum) 
{
	a[n] = nNum;
	MaxHeapFixup(a, n);
}

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


int main(void)
{
	int t;
	int j;
	char op1[13];
	char name[13];
	int pro;
	string op;
	//cin>>t;
	scanf("%d",&t);
	map<int,string> m;
	int minHeap[50010];
	int minhLast=0;
	int maxHeap[50010];
	int maxhLast=0;
	while(t>0)
	{
		minhLast=0;
		maxhLast=0;
		m.clear();
		memset(minHeap,0,sizeof(int)*50010);
		memset(maxHeap,0,sizeof(int)*50010);
		while(1){
			//cin>>op;
			scanf("%s",&op1);
			string op=op1;	
			if(op=="Add")
			{
				scanf("%s %d",&name,&pro);
				m[pro]=name;
				if(minhLast==maxhLast) //���С���Ѻʹ���Ѹ������
				{
					if(pro>maxHeap[0])//�ȴ���ѵĸ����������С����
					{
						MinHeapAddNumber(minHeap,minhLast,pro);
						minhLast++;
					}else{ //�������ȰѴ���ѵĸ�����С���ԣ��ٰ���Ԫ�ط�������
						MinHeapAddNumber(minHeap,minhLast,maxHeap[0]);
						minhLast++;
						maxHeap[0]=pro;
						MaxHeapFixdown(maxHeap,0, maxhLast);//���µ�������ѣ��Ӹ��ڵ�0��ʼ
					}

				}else{//�����ȣ��ض�minhLast��maxhLast��һ
					if(pro>minHeap[0])//��С���ѵĸ����������С���ѣ�Ȼ���ٵ���С���ѵĸ�������ѣ�֮���ڵ���һ��
					{
						MaxHeapAddNumber(maxHeap,maxhLast,minHeap[0]) ;//��С�ѵĶѸ���������,�������µ�����
						maxhLast++;
						minHeap[0]=pro;
						MinHeapFixdown(minHeap,0, minhLast);//���µ���С���ѣ��Ӹ��ڵ�0��ʼ
					}else{//�������ѣ����������
						MaxHeapAddNumber(maxHeap,maxhLast,pro);
						maxhLast++;
					}
				}
			}
			else if(op=="Query")
			{
				if(m.size()%2==1)
					printf("%s\n", m[minHeap[0]].c_str());
				else 
					printf("No one!\n");	
			}else{
				if(m.size()%2==1)
					printf("%s is so poor.\n", m[minHeap[0]].c_str());
				else
					printf("Happy BG meeting!!\n");
				if (t>1)
					printf("\n");
				break;	
			}//if
		}//while
		t--;
	}//while
	return 0;
}



/*
3
Add a 1
Query
Add b 4
Add d 7
Add e 13
Add f 43
Add g 10
Add h 58
Add i 54
Add j 12
Add k 59
Add l 89
Query
Add m 45
Add n 23
Query
Add o 9
Add p 40
Query
Add q 14
Add r 92
End
Add Radium 100
Add Magicpig 200
End
Add Magicpig 100
Add Radium 600
Add Kingfkong 300
Add Dynamic 700 
Query
Add Axing 400
Query
Add Inkfish 1000
Add Carp 800
End


No one!
Axing
Radium is so poor.

Happy BG meeting!!




*/




/*
˼���������Ϊ����ʱ�������ҳ���λ��
���ô���Ѻ�С����
Note that: Every contestant solves different number of problems.
The total number of the contestants will not exceed 10^5.
(Each name will appear in Add commands only once).
��ʱ
struct node
{
	string na;
	int pro;
};
struct compare
{
    bool operator()(node a, node b)   
	{
		return a.pro<b.pro;
    }
};
int main(void)
{
	int t;
	int j;
	char op1[10];
	char name[12];
	int pro;
	string op;
	//cin>>t;
	scanf("%d",&t);
	set<node,compare> v; 
	set<node,compare> ::iterator it;
	while(t>0)
	{
		v.clear();
		while(1){
			//cin>>op;
			scanf("%s",&op1);
			string op=op1;
			if(op=="Add")
			{
				node stu;
				//cin>>stu.na>>stu.pro;
				scanf("%s %d",&name,&pro);
				stu.na=name;
				stu.pro=pro;
				v.insert(stu);
			}
			else if(op=="Query")
			{
				if(v.size()%2==1){
					it=v.begin();
					for(j=0;j<(int)v.size()/2;j++){
						it++;
					}			
					printf("%s\n",(*it).na.c_str());
					//cout<<(*it).na<<endl;
				}
				else 
					printf("No one!\n");
					//cout<<"No one!"<<endl;	
			}else{
				if(v.size()%2==1){
					it=v.begin();
					for(j=0;j<(int)v.size()/2;j++){
						it++;
					}
					printf("%s is so poor.\n",(*it).na.c_str());
					//cout<<(*it).na<<" is so poor."<<endl;
				}else
					printf("Happy BG meeting!!\n");
					//cout<<"Happy BG meeting!!"<<endl;
				//cout<<endl;
				printf("\n");
				break;	
			}//if
		}//while
		t--;
	}//while
	return 0;
}


*/

/*
2
Add Magicpig 100
Add Radium 600
Add Kingfkong 300
Add Dynamic 700 
Query
Add Axing 400
Query
Add Inkfish 1000
Add Carp 800
End

Add Radium 100
Add Magicpig 200
End

No one!
Axing
Radium is so poor.

Happy BG meeting!!





*/