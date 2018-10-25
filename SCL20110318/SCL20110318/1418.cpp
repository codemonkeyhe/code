#include<iostream>
#include<algorithm>
using namespace std;
int av[110];
int bv[110];
int cv[110];
int dv[110];
int ev[110];
int val[1020000];
int main(void)
{
	int i,j,k,h,l,m;
	int n;
	int a,b,c,d,e;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a>>b>>c>>d>>e;
		for(j=0;j<a;j++)
			cin>>av[j];
		for(j=0;j<b;j++)
			cin>>bv[j];
		for(j=0;j<c;j++)
			cin>>cv[j];
		for(j=0;j<d;j++)
			cin>>dv[j];
		for(j=0;j<e;j++)
			cin>>ev[j];
		l=0;
		if(d==0) cout<<"0"<<endl;
		for(j=0;j<a;j++){
			for(k=0;k<c;k++){
				for(h=0;h<d;h++){
					if(av[j]+cv[k]+dv[h]>=0){
						val[l]=av[j]+cv[k]+dv[h];
						l++;
					}
				}
			}
		}
		for(j=0;j<a;j++){
			for(k=0;k<b;k++){
				for(h=0;h<d;h++){
					if(av[j]+bv[k]+dv[h]>=0){
						val[l]=av[j]+bv[k]+dv[h];
						l++;
					}
				}
			}
		}
		for(j=0;j<d;j++){
			for(k=0;k<e;k++){
				if(dv[j]+ev[k]>=0){
						val[l]=dv[j]+ev[k];
						l++;
					}
			}
		}
		sort(val,val+l);
		m=l;
		for(j=0;j<l-1;j++)
			if(val[j]==val[j+1]) m--;
		cout<<m<<endl;


	}
	return 0;
}


/*
水题，注意搭配为a,c,d 或者a,b,d,或者e,d
但如果其中任意一种缺失，不能形成搭配，如a,c不算搭配
2
1 1 1 1 1
5
2
3
1
7
1 1 0 1 0
1
-10
5


2
0


*/