#include<iostream>
using namespace std;
int main(void)
{
	int n,k;
	cin>>n>>k;
	int di[30001];
	int tail,head;
	int len;
	for(int i=0;i<n;++i)
		cin>>di[i];
	tail=head=0;
	int min=di[0];
	int max=di[0];
	int maxlen=0;
	len=1;
	while(tail<n)//tail尾指针，依次遍历每个起点，并找出起高低起伏差
	{
		while(max-min<=k)// 如果小于k,则虫头head一直向前爬，且len+1,每次均更新max和min，直到大于K
		{
			++head;
			if(di[head]>max) max=di[head];
			else if(di[head]<min) min=di[head];
			++len;
		}
		--len;
		if(len>=maxlen) maxlen=len;//把当前tail所指向的尾节点为起点的高低起伏差的长度判断是否是最长
		++tail;
		head=tail;
		max=di[tail];
		min=di[tail];
		len=1;
	}
	cout<<maxlen<<endl;
	return 0;
}


/*
第一行是整数n和k，分别表示测量点的个数和博士要求的最大水深差（也就是河床地势差）。
第二行有n个整数，表示从上游开始依次得到的水位深度di(1≤i≤n, 0≤di≤32767)。

6 2
5 3 2 2 4 5



*/


//他人代码
/*
#include <iostream>
using namespace std;

int maxlength(int deep[],int size, int index,int k)
{
    int length = 2;
    int max = (deep[index] > deep[index+1]) ? deep[index] : deep[index+1];
    int min = (deep[index] < deep[index+1]) ? deep[index] : deep[index+1];
    if(max - min > k)
    return 1;
    for(int i = index+2; i < size; i++)
    {
        if( deep[i] - max >= -k
        && deep[i] - max <= k
        && deep[i] - min <= k
        && deep[i] -min >=-k)
        {
            length++;
            if(deep[i] > max)
               max = deep[i] ;
            if(deep[i] < min)
               min = deep[i];
        }
        else break;
    }
    return length;
}
int main()
{
    int deep[32767],k;
    int size;
	cin >> size>>k;
    for(int i = 0; i < size; i++)
        cin >> deep[i];
    int max = 0;
    for(int i = 0; i <size; i++)
    {
       int temp = maxlength(deep,size,i,k);//依次遍历每个点为起点的最大长度串，且高低起伏差不超过K
       if(temp > max)//找出最大的高低起伏差
          max = temp;
    }
    cout << max<<endl;
    return 0;
}

*/