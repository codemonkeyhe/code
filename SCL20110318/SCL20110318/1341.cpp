#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int main(void)
{
	int n;
	int i;
	//while(!cin.eof())  //以后不要这样用
	while(cin>>n)
	//while(scanf("%d",&n)!=EOF)
	{
		//cin>>n;
		int * rami=new int[n];
		for(i=0;i<n;i++)
		{
			cin>>rami[i];
		}
		sort(rami,rami+n);
		int len=n;
		for(i=0;i<n-1;i++)
		{
			if(rami[i]==rami[i+1]) {
				rami[i]=-1;
				len--;
			}
		}
		cout<<len<<endl;
		for(i=0;i<n-1;i++)
		{
			if(rami[i]!=-1) 
				cout<<rami[i]<<" ";
		}
		cout<<rami[i]<<endl;
		delete []rami;
	}
	return 0;
}


/*
小心EOF循环控制语句
第1行为1个正整数，表示所生成的随机数的个数N，第2行有N个用空格隔开的正整数
10
20 40 32 67 40 20 89 300 400 15
3
3 2 1


8
15 20 32 40 67 89 300 400
3
1 2 3



*/
//#include<iostream>
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int main()
//{
//    int n;
//    while(scanf("%d",&n)!=EOF)
//    {
//        int arr[100],count = 0;
//        int b[100];
//        for(int i = 0;i < n;i++)
//        {
//            int a,j;
//            cin >> a;
//            for(j = 0;j < count ;j++)
//                if(a == b[j])
//                    break;
//            if(j == count)
//                b[count++] = a;
//
//        }
//        sort(b,b+count);
//        cout << count << endl;
//        for(int i = 0;i < count-1;i++)
//            cout << b[i] << " ";
//        if(n !=0 )
//        cout << b[count-1] << endl;
//       
//    }
//    return 0;
//}
