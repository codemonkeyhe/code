//#include<iostream>
//using namespace std;
//int main(void)
//{
//	
//	
//	return 0;
//}
//


//此题用排列组合公式则可，先暂放


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int dp[21][21];
int dpfunction(int i, int j)
{
    if(j == 0 || i==j)return 1;
    if(dp[i][j] == -1)
        dp[i][j] = dpfunction(i-1,j-1) + dpfunction(i-1,j);
    return dp[i][j];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    dpfunction(20,20);
    int a,b,c;
    while(true)
    {
        cin >>a>>b;
        if(a==-1)break;
        c = dpfunction(a+b,a);
        if(c == a+b)cout <<a<<"+"<<b<<"="<<a+b<<endl;
        else cout <<a<<"+"<<b<<"!="<<a+b<<endl;
    }
    return 0;
}
 

