#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<stdio.h>
#include<memory.h>
using namespace std;
////--------------小跟堆实现-------------------------------------
//  新加入i结点  其父结点为(i - 1) / 2
void MinHeapFixup(int a[], int i) 
{
    int j,temp;
	
	temp = a[i]; //要插入的节点的值
	j = (i - 1) / 2;      //父结点
	while (j >= 0 && i != 0)
	{
		if (a[j] <= temp)//不需要交换父子节点，插入完成
			break;
		
		a[i] = a[j];     //把较大的子结点往下移动,替换它的子结点
		i = j;      //当前的i为子节点
		j = (i - 1) / 2; //继续求其父节点
	}
	a[i] = temp;
}

//在最小堆中加入新的数据nNum,n表示插入的位置，为数组最后元素的下一个位置
void MinHeapAddNumber(int a[], int n, int nNum) 
{
	a[n] = nNum;
	MinHeapFixup(a, n);
}

//  从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
void MinHeapFixdown(int a[], int i, int n)
{
    int j, temp;

	temp = a[i];
	j = 2 * i + 1; //左孩子节点，
	while (j < n) 
	{
		if (j + 1 < n && a[j + 1] < a[j]) //在左右孩子中找最小的
			j++;

		if (a[j] >= temp)
			break;

		a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
		i = j;//当前子节点设置为父节点
		j = 2 * i + 1; //继续求子节点调整堆
	}
	a[i] = temp;
}

////--------------大根堆实现-------------------------------------
//  新加入i结点  其父结点为(i - 1) / 2
void MaxHeapFixup(int a[], int i) 
{
    int j,temp;
	
	temp = a[i]; //要插入的节点的值
	j = (i - 1) / 2;      //父结点
	while (j >= 0 && i != 0)
	{
		if (a[j] >= temp)//不需要交换父子节点，插入完成
			break;
		
		a[i] = a[j];     //把较小的子结点往下移动,替换它的子结点
		i = j;      //当前的i为子节点
		j = (i - 1) / 2; //继续求其父节点
	}
	a[i] = temp;
}

//在最大堆中加入新的数据nNum,n表示插入的位置，为数组最后元素的下一个位置
void MaxHeapAddNumber(int a[], int n, int nNum) 
{
	a[n] = nNum;
	MaxHeapFixup(a, n);
}

//  从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
void MaxHeapFixdown(int a[], int i, int n)
{
    int j, temp;

	temp = a[i];
	j = 2 * i + 1; //左孩子节点，
	while (j < n) 
	{
		if (j + 1 < n && a[j + 1] > a[j]) //在左右孩子中找最大的
			j++;

		if (a[j] <= temp)
			break;

		a[i] = a[j];     //把较大的子结点往上移动,替换它的父结点
		i = j;//当前子节点设置为父节点
		j = 2 * i + 1; //继续求子节点调整堆
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
				if(minhLast==maxhLast) //如果小根堆和大根堆个数相等
				{
					if(pro>maxHeap[0])//比大根堆的根还大，则放入小根堆
					{
						MinHeapAddNumber(minHeap,minhLast,pro);
						minhLast++;
					}else{ //否则，首先把大根堆的根加入小根对，再把新元素放入大根堆
						MinHeapAddNumber(minHeap,minhLast,maxHeap[0]);
						minhLast++;
						maxHeap[0]=pro;
						MaxHeapFixdown(maxHeap,0, maxhLast);//重新调整大根堆，从根节点0开始
					}

				}else{//若不等，必定minhLast比maxhLast大一
					if(pro>minHeap[0])//比小根堆的根还大，则放入小根堆，然后再弹出小根堆的根到大根堆，之后在调整一次
					{
						MaxHeapAddNumber(maxHeap,maxhLast,minHeap[0]) ;//最小堆的堆根插入最大堆,并且重新调整堆
						maxhLast++;
						minHeap[0]=pro;
						MinHeapFixdown(minHeap,0, minhLast);//重新调整小根堆，从根节点0开始
					}else{//放入大根堆，调整大根堆
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
思想就是人数为基数时，快速找出中位数
采用大根堆和小根堆
Note that: Every contestant solves different number of problems.
The total number of the contestants will not exceed 10^5.
(Each name will appear in Add commands only once).
超时
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