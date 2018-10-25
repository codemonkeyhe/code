#include<iostream>
#include<stack>
using namespace std;
int main(void)
{
	int i,j,k;
	int n;
	while(cin>>n,n!=0)
	{
		stack<int> sta;
		int c1,c2;
		int *cir=new int[2*n+1];
		int cupN=n;
		for(i=0;i<n;i++)
		{
			cin>>c1>>c2;
			cir[c1]=c2;
			cir[c2]=c1;
		}
		for(i=1;i<=2*n;i++)
		{
			if(!sta.empty() && cir[i]==sta.top()) 
			{
				sta.pop();
				continue;
			}
			if(cir[i]!=i+1 ) 
				sta.push(i);
			else 
				i++;
		}
		if(sta.empty()) 
			cout<<"Yes"<<endl;
		else  
			cout<<"No"<<endl;
		delete []cir;
	}
	return 0;
}


//严重超时，应采用括号匹配的思想
//#include<iostream>
//#include<algorithm>
//using namespace std;
//int main(void)
//{
//	int i,j,k;
//	int n;
//	while(cin>>n,n!=0)
//	{
//		int coup[100000][2];
//		int *cir=new int[2*n+1];
//		int cupN=n;
//		for(i=0;i<n;i++)
//		{
//			cin>>coup[i][0]>>coup[i][1];
//			cir[coup[i][0]]=coup[i][1];
//			cir[coup[i][1]]=coup[i][0];
//		}
//		int k;
//		bool end;
//		while(1){
//			end=true;
//			for(i=1;i<=2*n ;i++)
//			{
//				
//				if(cir[i]==-1) continue;
//				k=i+1;
//				if(k==2*n+1) k=1;
//				while(cir[k]==-1){k++;}
//				if(cir[i]==k){
//					cupN--;
//					cir[i]=-1;
//					cir[k]=-1;
//					end=false;
//				}
//
//			}
//			if(cupN==0) {cout<<"Yes"<<endl;break;}
//			if(cupN==n || end==true) {cout<<"No"<<endl;break;}
//		}
//
//		delete [] cir;
//	}
//	return 0;
//}

/*
1 <= N <= 100000
4
1 4
2 3
5 6
7 8

2
1 3
2 4

4
1 8
2 7
3 5
4 6


4
1 8
2 7
3 6
4 5

8
1 4
2 3
5 6
7 8
9 16
10 15
11 13
12 14
0

Yes
No
No
Yes
no



*/



////大神的括号匹配思想
////数据结构——栈   
////先开一个数字然后标记号是couple的编号   
////接着从1~2n一个个塞进栈中,同时调用couple数组进行检查，看是否能与栈顶元素合并   
////如果能合并，就从栈顶中移除   
////到最后如果栈顶为空，则说明能够全部移除   
//#include<iostream>   
//#include<stack>   
//#include<cstring>   
//using namespace std;   
//int couple[200010];   
//int main()   
//{   
//    int n,l,r;   
//    while(scanf("%d",&n) && n)   
//    {   
//        memset(couple,-1,sizeof(couple));   
//        stack<int> s;   
//        for(int i = 0;i < n;++i)   
//        {   
//            scanf("%d%d",&l,&r);   
//            couple[l] = r;   
//            couple[r] = l;   
//        }   
//        for(int i = 1;i <= 2*n;++i)   
//        {   
//            if(s.empty())   s.push(i);   
//            else if(couple[i] == s.top())   s.pop();   
//        }   
//        if(s.empty())       printf("Yes\n");   
//        else        printf("No\n");   
//    }   
//    return 0;   
//}  
//

