/*
Q1003: Hit or Miss
问题描述
一个非常简单的纸牌游戏叫做“Hit or Miss”（也叫做“Frustration”，“Harvest”，“Roll-Call”，“Talkative”或“Treize”），它的玩法如下：
准备一副已经洗乱的52张的扑克牌——4个由1至13的集合（花色对此游戏没有影响），然后开始数1，2，3，……，等，
当你数到13时，又从1开始数。每数一个数，看看最上面的牌，如果你数到的数与牌面的数值相等，丢弃这张牌，
如果不相等，将此牌移到整副牌的底部。如果你能够移去整副牌（这将会花费非常长的时间），那么你就会赢得此游戏。
这个游戏的一个版本还可以有两位或更多的游戏者。第一位游戏者像先前那样拥有一副52张的牌，而其他游戏者起初是没有牌的。
当第一位游戏者移去牌时，那将移去的牌交给第二位游戏者，然后第二位游戏者开始同样的游戏，他将移去的牌交给第三位游戏者，依此类推。
最后一位游戏者会直接将牌丢弃，而不是交给第一位游戏者。所有的游戏者都遵循如下的两步循环：
1.每位游戏者检查当前所数之数与最上面的牌是否匹配。如果不匹配，那么便将此牌移至整副牌的底部，否则将此牌交给下一位游戏（最后一位游戏者直接将牌丢弃）。
2.每位游戏者拿到传过来的牌后，将此牌放到整副牌的底部。
这些步骤会一直重复下去，直到赢得游戏（所有的牌都被最后一位游戏者丢弃），或者出现无法获胜的局面。如果某位游戏者没有牌了，
他将会等待传过来的牌，然后从中断的位置继续数（例如：如果第三位游戏者数到7时将最后一张牌传给每四位游戏者，
他会等待直到从第二位游戏者手中获得牌，然后继续从8开始向后数）。
输入格式
输入包含多组输入集。输入的第一行包含一个正整数，表示输入集的数量。每个输入集为单独一行包含53个整数。
第一个整数表示游戏者的数目，余下的52个值是整副牌的初始顺序，第一个值是最上面的牌。这些值都在[1, 13]范围内，游戏者的数目在[1, 10]范围内。
输出格式
对于每个输入集，输出输入集的编号（如下所示，由1开始）然后是“unwinnable”或一列数表示每位游戏者丢弃的最后一张牌。
输入样例

2
4 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13
4 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1

输出样例

    Case 1: 13 13 13 13
    Case 2: unwinnable
	1
	1 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13
*/


#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;



int main(void)
{
	int n;
	int p;
	int i;
	int j;
	int k;
	int num;
	int a[52];
	queue<int> pl[11];
	int che[11]={1,1,1,1,1,1,1,1,1,1,1};
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{	
	
		scanf("%d",&p);
		for(j = 0;j< p;j++ ) { 
		che[j] = 1; 
		while( !pl[j].empty() ) 
			pl[j].pop(); }
		for(j=0;j<52;j++)
		{
			scanf("%d",&num);
			pl[0].push(num);
		}
		

		k=0;
		bool win=false;
		bool end=false;
		int count=0;
		while(count<13*52 && !win){
			k=0;
			for(j=0;j<p;j++)
			{
				if(!pl[j].empty()){
					if(che[j]==pl[j].front())
					{
						pl[j].pop();
						pl[j+1].push(che[j]);
						count=0;


					}else{
						pl[j].push(pl[j].front());
						pl[j].pop();
						count++;
					}
					che[j]++;
					if(che[j]==14) che[j]=1;
					
				}
				else
					k++;
			}
			
			if(k==p) win=true;
		}
		if(win==false)
			printf("Case %d: unwinnable\n",i);
		else{
			printf("Case %d:",i);
			for(j=0;j<p;j++)
			{
				if(che[j]==1)
				    che[j]=13;
				else
					che[j]--;
				printf(" %d",che[j]);

			}
			printf("\n");

		}
	}
	return 0;
}

/*
//简单的模拟..   
//wengsht   
#include <iostream>   
#include <cstdio>   
#include <queue>   
using namespace std;   
  
int t,n,c[10],card;   
int no_count;   
queue<int> q[11];   
int main()   
{   
    //freopen("1.txt","r",stdin);   
    scanf("%d",&t);   
    for( int k = 1;k <= t;k++ )   
    {   
        printf("Case %d:",k);   
        no_count = 0;   
        scanf("%d",&n);   
        for( int i = 0;i <= n;i++ ) { c[i] = 1; while( !q[i].empty() ) q[i].pop(); }   
  
        for( int i = 0;i < 52;i++ ) { scanf("%d",&card); q[0].push(card); }   
  
        bool no_c = true;   
        bool accomplish = false;   
        while( no_count < 13*52 && !accomplish )   
        {   
            accomplish = no_c = true;   
            for( int i = 0;i < n;i++ )   
            {   
                if( !q[i].empty() )   
                {   
                    accomplish = false;   
  
                    if( c[i] == q[i].front() )   
                    {   
                        q[i+1].push(c[i]);   
  
                        no_c = false;   
                    }   
                    else q[i].push( q[i].front() );   
                    c[i]++;   
                    q[i].pop();   
                    if( c[i] == 14 ) c[i] = 1;   
                }   
            }   
            if( no_c ) no_count++;   
            else       no_count = 0;   
        }   
        if( accomplish )   
        {   
            for( int i = 0;i < n;i++ )   
            {   
                if( c[i] == 1 ) c[i] = 13;   
                else            c[i]--;   
                printf(" %d",c[i]);   
            }   
            printf("\n");   
        }   
        else printf(" unwinnable\n");   
    }   
    return 0;   
} 

*/