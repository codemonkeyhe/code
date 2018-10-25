#include<iostream>
#include<stdio.h>
using namespace std;
//int an[501];
//int bn[501];
//int cn[501];
//int dn[501];
//此题对于输入输出用cin还是scanf影响不大
int main(void)
{
	int a,b,c,d;
	int i,j,k,h;
	int sum;
	cin>>a>>b>>c>>d;
	//scanf("%d%d%d%d",&a,&b,&c,&d);
	int *an=new int[a];
	int *bn=new int[b];
	int *cn=new int[c];
	int *dn=new int[d];
	for(i=0;i<a;i++)
		//scanf("%d",&an[i]);
		cin>>an[i];
	for(i=0;i<b;i++)
		//scanf("%d",&bn[i]);
		cin>>bn[i];
	for(i=0;i<c;i++)
		//scanf("%d",&cn[i]);
		cin>>cn[i];
	for(i=0;i<d;i++)
		//scanf("%d",&dn[i]);
		cin>>dn[i];
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			for(k=0;k<c;k++){
				for(h=0;h<d;h++){
					sum=an[i]+bn[j]+cn[k]+dn[h];
					if(sum==0){
						//printf("%d %d %d %d\n",an[i],bn[j],cn[k],dn[h]);
						cout<<an[i]<<" "<<bn[j]<<" "<<cn[k]<<" "<<dn[h]<<endl;
						return 0;//这个是关键，之前忘了，结果一直做多余的循环，所以超时
					}
						
				}
			}
		}
	}
	delete []an;
	delete []bn;
	delete []cn;
	delete []dn;
	return 0;
}

/*
1 <= a, b, c, d <= 500
3 2 4 2
5
17
-8
-13
19
6
-9
10
0
-14
7



17 -13 10 -14


*/