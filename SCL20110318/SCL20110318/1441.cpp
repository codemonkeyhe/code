#include<iostream>
#include<iomanip>
#include <stdio.h>
using namespace std;
#define PI 3.141592653589793238462643
#define Accuracy 0.00001

int main(void)
{
	int TCase=0;
	int N=0,F=0;
	int Ri[10000]={0};
	int ri;
	int sum=0;
	int max=0;
	double Lv=0,Rv=0;
	double MidV=0;
	int DivN=0;
	cin>>TCase;
	for(int i=0;i<TCase;i++)
	{
		sum=0;
		max=0;
		cin>>N>>F;
		++F;
		for(int i=0;i<N;i++){
			cin>>ri;
			Ri[i]=ri*ri;
			sum+=Ri[i];
			if(max<Ri[i]) max=Ri[i];
		}
		Lv=((double)max)*PI/(double)F;
		//Rv=((double)sum)*PI/(double)F; 不能为上届，。。。，否则对只有1个Pi说不过去
		Rv=(double)max*PI;
		while(Rv-Lv>Accuracy)
		{

			MidV=(Lv+Rv)/2.0;
			DivN=0;
			for(int i=0;i<N;i++)
			{
				DivN+=PI*(double)Ri[i]/MidV;
			}
			if(DivN>=F) //若现在的MidV可以分给更多人，则增大MidV让它分给少人
				Lv=MidV;
			else  //若现在的MidV不够分，则减小MidV让它分给多人
				Rv=MidV;
		}
		cout<<fixed<<setprecision(4)<<MidV<<endl;
	}
	return 0;
}



/*
陷阱：Lv Rv 可以是浮点数
3
3 3
4 3 3
1 24
5
10 5
1 4 2 3 4 5 6 5 4 2


3 3
4 3 3
1 24
5
10 5
1 4 2 3 4 5 6 5 4 2


1
10 5
1 4 2 3 4 5 6 5 4 2


1
1 24
1

1
1 9999
1 

1
7 0
9999 1 1 1 1 1 1 

1
1 0
9999 

25.1327
3.1416
50.2655
*/