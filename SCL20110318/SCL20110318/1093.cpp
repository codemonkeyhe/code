#include<iostream>
#include<stdio.h>
using namespace std;
int main(void)
{
	int w1,w2,w3;
	int r1,r2,r3,r4;
	int l1,l2,l3;
	int n=1;
	int w;
	int p;
	int addp;
	while(!cin.eof())
	{
		cin>>w1>>r1;
		cin>>w2>>r2;
		cin>>w3>>r3;
		cin>>r4;
		//不能这样写。除不尽的话就有危险
		//l1=(w1+1)*r2/r1;
		//l2=(w2+1)*r3/r2;
		//l3=(w3+1)*r4/r3;
		printf("Set number %d:\n",n);
		n++;
		while(cin>>w,w!=0)
		{
			if(w>0 && w<=w1) {
				if(w*r1<=(w1+1)*r2){p=r1*w;addp=0;}
				else {p=r2*(w1+1);addp=w1-w+1; }
			}
			else if(w>w1 && w<=w2) {
				if(w*r2<=(w2+1)*r3){p=r2*w;addp=0;}
				else {p=r3*(w2+1);addp=w2-w+1; }
			}
			else if(w>w2 && w<=w3) {
				if(w*r3<=(w3+1)*r4){p=r3*w;addp=0;}
				else {p=r4*(w3+1);addp=w3-w+1; }
			}
			else if(w>w3 ) {p=r4*w;addp=0;}
			printf("Weight (%d) has best price $%d (add %d pounds)\n",w,p,addp);
		}
		printf("\n");
	}
	return 0;
}


/*

9 10
49 5
99 3
2
8
10
90
100
200
0
10 10
20 20
30 30
100
1
12
29
50
0



Set number 1:
Weight (8) has best price $50 (addp 2 pounds)
Weight (10) has best price $50 (addp 0 pounds)
Weight (90) has best price $200 (addp 10 pounds)
Weight (100) has best price $200 (addp 0 pounds)
Weight (200) has best price $400 (addp 0 pounds)

Set number 2:
Weight (1) has best price $10 (addp 0 pounds)
Weight (12) has best price $240 (addp 0 pounds)
Weight (29) has best price $870 (addp 0 pounds)
Weight (50) has best price $5000 (addp 0 pounds)



*/