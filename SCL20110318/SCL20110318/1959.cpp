#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;
int main(void)
{
	int x1,x2,y1,y2;
	cin>>x1>>y1>>x2>>y2;
	int sum=abs(x1-x2)+abs(y1-y2);
	cout<<sum<<endl;

	return 0;
}

/*

All integers in the input are in the range of [-10000000, 10000000].

1 3
4 1


5


*/