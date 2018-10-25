#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int pa[160];
int qa[160];

int cal(int k,int *a)
{
	int i;
	int l;
	l=0;
	for(i=1;i<=(int)sqrt((double)k);i++){
		if(k%i==0){
			if(k/i!=i){
				a[l]=i;
				a[l+1]=k/i;
				l=l+2;
			}
			else{
				a[l]=i;
				l++;
			}
		}
	}
	return l;
}

int main(void)
{
	int p;
	int q;
	int i,j,k,l;
	cin>>p>>q;
	i=cal(p,pa);
	j=cal(q,qa);
	sort(pa,pa+i);
	sort(qa,qa+j);
	for(k=0;k<i;k++){
		for(l=0;l<j;l++){
			cout<<pa[k]<<" "<<qa[l]<<endl;
		}
	}
	return 0;
}



/*
24 2

1 1
1 2
2 1
2 2
3 
3 2
4 1
4 2
6 1
6 2
8 1
8 2
12 1
12 2
24 1
24 2


*/