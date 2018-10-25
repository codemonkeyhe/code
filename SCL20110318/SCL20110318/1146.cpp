#include<iostream>
using namespace std;

template<class T>
void Knapsack(T p[], int w[], int c, int n, T** f,int yMax)
{
	// 对于所有i和y计算f [ i ] [ y ]
	// 初始化f [ n ] [ ]
	for (int y = 0; y <= yMax; y++)
		f[n][y] = 0;
	for (int y = w[n]; y <= c; y++)
		f[n][y] = p[n];
	// 计算剩下的f 
	for (int i = n - 1; i > 1; i--) {
		for (int y = 0; y <= yMax; y++)
			f[i][y] = f[i+1][y];
		for (int y = w[i]; y <= c; y++)
			f[i][y] = max(f[i+1][y], f[i+1][y-w[i]] + p[i]);
	}
	f[1][c] = f[2][c];
	if (c >= w[1])
		f[1][c] = max(f[1][c], f[2][c-w[1]] + p[1]);
}


int timec[110];
int value[110];


int main(void)
{
	int i,j,k;
	int T;
	int m;
	cin>>T>>m;
	for(i=1;i<=m;i++)
	{
		cin>>timec[i]>>value[i];
	}
	int **f=new int*[m+1];
	for(int i=0;i<=m;i++)
		f[i]=new int[T+1];
	Knapsack<int>(value,timec,T,m,f,T);
	cout<<f[1][T]<<endl;
	return 0;
}


/*
采用贪心算法，单位时间内的价值多优先采集,这是错误的方法，不能保证最优，例如下面例子.因此得采用动态规划
70 3
60 120
35 69
35 69

70 3
69 1
1 2
79 100

10 5
2 6
2 3
6 5
5 4
4 6

3
15




130 10
71 100
69 1
1 2
3 5
3 6
5 9
30 210
23 12
80 23 
71 180

*/




// source code of submission 482194, Zhongshan University Online Judge System
/*
#include <iostream>
#include <deque>
#include <fstream>
#include <cstring>
using namespace std;
fstream fin("test.txt");
int timing[110];int w[110];
int remember[110][1010];
int f(int n,int t)
{
    if(remember[n][t] != -1) return remember[n][t];
    if(n <= 0 || t <= 0) return 0;
    int tmp;
    if (t - timing[n] >= 0)
        tmp = f(n-1,t-timing[n]) + w[n];
    else tmp = 0;
    remember[n][t] = (tmp > f(n-1,t)) ? tmp : f(n-1,t);
    return remember[n][t];
}
int main()
{
    memset(remember,-1,sizeof(remember));
    int t,m;
    cin >>t>>m;
    for(int i = 1; i<= m; i++)
    {
        cin >> timing[i] >> w[i];
    }

    cout << f(m,t)<<endl;
    return 0;
}
 

 */