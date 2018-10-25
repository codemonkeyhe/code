#include<iostream>
using namespace std;
int main(void)
{
	int i,j,k;
	int T;
	int M,N;
	int left;
	int A,B;
	cin>>T;
	for(i=0;i<T;i++)
	{
		cin>>M>>N;
		for(j=0;j<N;j++)
		{
			cin>>A>>B;
			M=M-A*B;
		}
		if(M>=0) cout<<M<<endl;
		else cout<<"Not enough"<<endl;
	}
	return 0;
}


/*
水题，一次AC
T
M(1<=M<=1000)  N(1<=N<=5)
 Ai(1<=Ai<=100) and Bi(1<=Bi<=5)
3
10 2
5 1
3 1
100 2
25 2
50 1
8 1
3 3


2
0
Not enough

*/