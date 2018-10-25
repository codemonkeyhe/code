#include<iostream>
#include<algorithm>
using namespace std;


////http://blog.csdn.net/morewindows/article/details/6709644
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
//����С����ɾ����
void MinHeapDeleteNumber(int a[], int n)
{
	swap(a[0], a[n - 1]);
	MinHeapFixdown(a, 0, n - 1);
}

//������С��
void MakeMinHeap(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MinHeapFixdown(a, i, n);
}

//������
void MinheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		swap(a[i], a[0]); //a[0]һ��ʼ������С��Ԫ�أ�����һ�£����������1�����������1
		MinHeapFixdown(a, 0, i);
	}
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
//��������ɾ����
void MaxHeapDeleteNumber(int a[], int n)
{
	swap(a[0], a[n - 1]);
	MaxHeapFixdown(a, 0, n - 1);
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




/*С���Ѱ汾
void HeapAdjust(int *a,int size,int node)
{
	int min=node;
	int lchild=2*node; //�������
	int rchild=2*node+1; //�Һ������
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
			HeapAdjust(a,size-1,min);//�������֮����maxΪ���ڵ���������Ƕѣ��ݹ���������ڵ�
		}
	}
}


void BuildSmallHeap(int *a,int size)//����С���� 
{
	for(int i=size/2;i>=1;i--)//��Ҷ�ڵ�������ֵΪsize/2 
	{
		HeapAdjust(a,size,i);
	}
}


void HeapSort(int* a,int size )
{
	int last=size;
	BuildSmallHeap(a,size);//����С����
	while(last>=1)
	{
		swap(a[1],a[last]); //����С���ѵĸ�������ĩβԪ��
		--last; //��ģ��һ�����޳�����ĩβ��С���ѵĸ�
		HeapAdjust(a,last,1); //С���ѵĸ��Ѳ�����С�ģ����µ���С����
	}
}

*/