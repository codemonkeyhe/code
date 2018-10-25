#include<iostream>
#include<algorithm>
using namespace std;


////http://blog.csdn.net/morewindows/article/details/6709644
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
//在最小堆中删除数
void MinHeapDeleteNumber(int a[], int n)
{
	swap(a[0], a[n - 1]);
	MinHeapFixdown(a, 0, n - 1);
}

//建立最小堆
void MakeMinHeap(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MinHeapFixdown(a, i, n);
}

//堆排序
void MinheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		swap(a[i], a[0]); //a[0]一开始就是最小的元素，交换一下，无序区间减1，有序区间加1
		MinHeapFixdown(a, 0, i);
	}
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
//在最大堆中删除数
void MaxHeapDeleteNumber(int a[], int n)
{
	swap(a[0], a[n - 1]);
	MaxHeapFixdown(a, 0, n - 1);
}

//建立最大堆
void MakeMaxHeap(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapFixdown(a, i, n);
}

//堆排序
void MaxheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		swap(a[i], a[0]); //a[0]一开始就是最小的元素，交换一下，无序区间减1，有序区间加1
		MaxHeapFixdown(a, 0, i);
	}
}


int main(int argc, char *argv[])
{
  
	 int a[]={1,7,8,9};
   // int a[100];
	 	 int size=4;
	MakeMaxHeap(a,size);
	  for(int i=0;i<size;i++)
            cout<<a[i]<<" ";
        cout<<endl;
	 MaxheapsortTodescendarray(a,size);
	  for(int i=0;i<size;i++)
            cout<<a[i]<<" ";
        cout<<endl;

	//MakeMinHeap(a,size);
	//  for(int i=0;i<size;i++)
 //           cout<<a[i]<<" ";
 //       cout<<endl;
	// MinheapsortTodescendarray(a,size);
	//  for(int i=0;i<size;i++)
 //           cout<<a[i]<<" ";
 //       cout<<endl;
    return 0;
}




/*小根堆版本
void HeapAdjust(int *a,int size,int node)
{
	int min=node;
	int lchild=2*node; //左孩子序号
	int rchild=2*node+1; //右孩子序号
	if(node<=size/2){
		if(lchild<=size && a[lchild]<a[min])
		{
			min=lchild;
		}
		if(rchild<=size && a[rchild]<a[min])
		{
			min=rchild;
		}
		if(min!=node)
		{
			swap(a[min],a[node]);
			HeapAdjust(a,size-1,min);//避免调整之后以max为父节点的子树不是堆，递归更新子树节点
		}
	}
}


void BuildSmallHeap(int *a,int size)//建立小根堆 
{
	for(int i=size/2;i>=1;i--)//非叶节点最大序号值为size/2 
	{
		HeapAdjust(a,size,i);
	}
}


void HeapSort(int* a,int size )
{
	int last=size;
	BuildSmallHeap(a,size);//建立小跟堆
	while(last>=1)
	{
		swap(a[1],a[last]); //交换小根堆的根和数组末尾元素
		--last; //规模减一，以剔除数组末尾的小根堆的根
		HeapAdjust(a,last,1); //小根堆的根已不是最小的，重新调整小跟堆
	}
}

*/