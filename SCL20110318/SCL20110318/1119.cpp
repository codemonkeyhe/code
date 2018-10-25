#include<iostream>
#include<cmath>
using namespace std;

int main(void)
{
	int i;
	double j;
	double b;
	int n;
	double sum;
	while(cin>>n,n!=0)
	{
		i=n/10-194;
		b=1<<i;
		b=b*log((double)2);
		sum=0;
		j=1;
		while(sum<b){
			sum+=log(j);
			j++;
		}
		cout<<j-2<<endl;
	}
	return 0;
}




//#include <iostream>
//#include <cmath>
//using namespace std;
//
//int main()
//{
//    long long n,t,tt,i;
//    double ans;
//     while(cin>>n&&n)
//     {
//      t=(n-1960)/10+2;
//      tt=1<<t;
//      ans=i=0;
//      while(ans<tt)
//                   ans+=log((double)++i)/log((double)2);
//       printf("%lld\n",i-1); 
//      }
//}

/*
1960
1981
0


3 
8


*/
