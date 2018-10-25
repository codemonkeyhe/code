////超时，已经排除不是生成ABCDE全排表时超时，而是计算最小值时超时，重写核心算法
//我草他个亲娘四舅奶奶，之所以超时是因为scanf("%c%c%c%c%c",&in[i][0],&in[i][1],&in[i][2],&in[i][3],&in[i][4]);
//改为scanf("%s",&in[i]);则没事，我了个去，就因为这个耽误了我一阵天啊！shit
//#include<iostream>
//#include<stdio.h>
//#include<string.h>
//#include<vector>
//using namespace std;
//char p[120][5]; //ABCDE全排表
//bool visit[5];
//int sum[120];
//char ord[10][2];
//char in[101][5];
//vector<char> sta;
//	int h=0;
//void SetPre()
//{
//	int i,j;
//	if(sta.size()==5)
//	{
//		for(j=0;j<5;j++)
//		{
//			p[h][j]=sta[j];
//		}
//		h++;
//		i=sta.back()-65;
//		visit[i]=false;
//		sta.pop_back();
//		return ;
//	}
//
//	char ch;
//	i=0;
//	for(ch='A';ch<='E';ch++)
//	{
//		i=ch-65;
// 		if(!visit[i]){
//			sta.push_back(ch);
//			visit[i]=true;				
//			SetPre();
//		}
//	}
//	if(!sta.empty()){
//		i=sta.back()-65;
//		visit[i]=false;
//		sta.pop_back();
//	}
//	
//}
//
//void MakeOrd(char* pre)
//{
//	int i,j;
//	int m=0;
//	for(i=0;i<5;i++)
//	{
//		for(j=i+1;j<5;j++)
//		{	
//			ord[m][0]=pre[i];
//			ord[m][1]=pre[j];
//			m++;
//		}
//	}
//}
//
//int find(char ch1,char ch2,int j)
//{
//	string str=in[j];
//	if(str.find(ch1)<str.find(ch2))
//		return 0;
//	else
//		return 1;
//}
//
//int main()
//{
//	int i,j,k;
//	int n;
//	int dis[101];	
//	int min;
//	int mink;
//	SetPre();
//	memset(visit,false,sizeof(visit));
//	while(scanf("%d",&n),n!=0)
//	{
//		min=1000;
//		mink=-1;
//		memset(sum,0,sizeof(sum));		
//	
//		for(i=0;i<n;i++)
//		{
//			fflush(stdin); 
//			scanf("%s",&in[i]);
//		}
//		for(i=0;i<120;i++)
//		{
//			memset(dis,0,sizeof(dis));
//			MakeOrd(p[i]);
//			for(j=0;j<n;j++)
//			{
//				for(k=0;k<10;k++)
//				{
//					dis[j]=dis[j]+find(ord[k][0],ord[k][1],j);
//				}
//			}
//			for(j=0;j<n;j++)
//			{
//				sum[i]=sum[i]+dis[j];
//			}
//			if(min>sum[i]) {min=sum[i];mink=i;}
//			if(min==0) break;
//		}
//		for(i=0;i<5;i++){
//		printf("%c",p[mink][i]);
//		}	
//		printf(" is the median ranking with value %d.\n",min);
//	}
//	return 0;
//}
//


#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
char p[120][6]; //ABCDE全排表
bool visit[6];

char ord[10][3];
char in[110][6];
vector<char> sta;
	int h=0;
void MakeOrd(char* pre)
{
	int i,j;
	int m=0;
	for(i=0;i<5;i++)
	{
		for(j=i+1;j<5;j++)
		{	
			ord[m][0]=pre[i];
			ord[m][1]=pre[j];
			m++;
		}
	}
}
void SetPre()
{
	int i,j;
	if(sta.size()==5)
	{
		for(j=0;j<5;j++)
		{
			p[h][j]=sta[j];
		}
		h++;
		i=sta.back()-65;
		visit[i]=false;
		sta.pop_back();
		return ;
	}
	char ch;
	i=0;
	for(ch='A';ch<='E';ch++)
	{
		i=ch-65;
 		if(!visit[i]){
			sta.push_back(ch);
			visit[i]=true;				
			SetPre();
		}
	}
	if(!sta.empty()){
		i=sta.back()-65;
		visit[i]=false;
		sta.pop_back();
	}	
}
int main()
{
	int i,j,k;
	int n;
	int dis[110];	
	int min;
	int mink;
	int sum[120];
	SetPre();
	
	while(scanf("%d",&n),n!=0)
	{
		min=1000;
		mink=-1;
		memset(sum,0,sizeof(sum));	
		memset(visit,false,sizeof(visit));
		for(i=0;i<n;i++)
		{
			fflush(stdin); 
			//scanf("%c%c%c%c%c",&in[i][0],&in[i][1],&in[i][2],&in[i][3],&in[i][4]);  超时
				scanf("%s",&in[i]);
		}
		for(i=0;i<120;i++)
		{
			memset(dis,0,sizeof(dis));
			MakeOrd(p[i]);
			for(j=0;j<n;j++)
			{
				for(k=0;k<10;k++)
				{
					string str=in[j];
						if(str.find(ord[k][0])>str.find(ord[k][1]))
							dis[j]++;
				}
				sum[i]=sum[i]+dis[j];
			}
			if(min>sum[i]) {min=sum[i];mink=i;}
			if(min==0) break;
		}	
		for(i=0;i<5;i++){
	printf("%c",p[mink][i]);
	}				
		printf(" is the median ranking with value %d.\n",min);
	}
	return 0;
}





//
//#include<iostream>  
//#include <string>  
//#include <memory.h>  
//using namespace std;  
//
//   
//
//string hold = "ABCDE";  
//string result;  
//string a[101];  
//int total;  
//void all_permutation(int current);  
//int calculate();  
//int find(char);  
//
//   
//int mini, n;  
//bool used[5];  
//int main()  
//{ 
//    while (cin >> n && n)  
//    {  
//        memset(used, false, 5*sizeof(bool));  
//        for (int i = 0; i < n; i++)  
//            cin >> a[i];  
//        mini = calculate();  
//        result = hold;  
//        all_permutation(0);  
//        cout << result << " is the median ranking with value " << mini << "." << endl;  
//    }  
//    return 0;  
//}  
//
//   
//
//void all_permutation(int current)  
//{  
//    if (current >= 5)  
//    {  
//        total = calculate();  
//        if (total < mini)  
//        {  
//            mini = total;  
//            result = hold;  
//        }  
//    }  
//    else 
//    {  
//        for (int i = 0; i < 5; i++)  
//            if (!used[i])  
//            {  
//                used[i] = true;  
//                hold[current] = i+'A';  
//                all_permutation(current+1);  
//                used[i] = false;  
//            }  
//    }  
//}  
//
//   
//
//int calculate()  
//{  
//    int result = 0;  
//    for (int i = 0; i < n; i++)  
//    {  
//        for (int j = 0; j < 4; j++)  
//        {  
//            for (int k = j+1; k < 5; k++)  
//            {  
//                if (find(a[i][j]) > find(a[i][k]))  
//                    result++;  
//            }  
//        }  
//    }  
//    return result;  
//}  
//
//   
//
//int find(char x)  
//{  
//    int index;  
//    for (int i = 0; i < 5; i++)  
//    { 
//        if (hold[i] == x)  
//        {  
//           index = i;  
//            return index;  
//        }  
//    }  
//} 



/*
#include   <time.h> 
#include   <iostream.h> 
void   main() 
{ 
	time_t start=clock();  
	for(int   i=0;   i <10000000;   i++); 
	time_t  end = clock(); 
	double  dur = static_cast <double>(end-start)/CLOCKS_PER_SEC*1000; 
	cout<<"\n您的程序执行所耗费的时间为:   "<<dur<<"   毫秒 "<<endl; 
}

*/

//#include<iostream>
//#include   <time.h> 
//#include <stdio.h>
//#include <algorithm>
//#include <map>
//
//using namespace std;
//int main()
//{
//	int n,i,j,k;
//	char rank[100][5];
//	char finalans[5];
//	map<char,bool> mymap;
//	scanf("%d",&n);
//	int score,best;
//	while(n != 0)
//	{
//		
//		for(i = 0; i < n; i++)
//			scanf("%s",rank[i]);
//		char ans[] = {'A','B','C','D','E'};
//		best = 999999999;
//		do{
//			score = 0;
//			for(i = 0; i < n; i++)
//			{
//				mymap.clear();
//				for(j = 0; j < 5; j++)
//				{
//					mymap[rank[i][j]] = true;    //求逆序数算法
//					for(k = 0; k < 5; k++)
//					{
//						if(!mymap[ans[k]])     //若为出现，则会组成逆序
//							score ++;
//						if(ans[k] == rank[i][j])   //若一样，则之后的无须再比较
//							break;
//					}
//				}
//			}
//			if(score < best)        //记录出现的最优
//			{
//				for(j = 0; j < 5; j++)
//					finalans[j] = ans[j];
//				best = score;
//			}
//		}while(next_permutation(ans,ans+5));
//
//		for(i = 0; i< 5; i++)
//			printf("%c",finalans[i]);
//		printf(" is the median ranking with value %d.\n",best);
//		scanf("%d",&n);
//	}
// return 1;
//}
