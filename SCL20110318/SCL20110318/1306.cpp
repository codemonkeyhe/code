#include<iostream>
#include<string>
#include<stdio.h>
#include<memory.h>
#include<algorithm>
using namespace std;

int main(void)
{
	int i,j,k;
	int n,m;
	while(cin>>n>>m, n!=0 && m!=0)
	{
		int *arr=new int[n];
		for(i=0;i<n;i++)
		{
			cin>>arr[i];
		}
		sort(arr,arr+n);
		cout<<arr[0];
		for(i=m;i<n;i=i+m)
		{
			cout<<" "<<arr[i];
		}
		cout<<endl;
		delete []arr;
	}
	 return 0;
}


/*


注意输出格式，1 3 5 7的7后面不能有空格字符
8 2
3
5
7
1
8
6
4
2
0 0

8 0
3
5
7
1
8
6
4
2
0 0

1 3 5 7
*/