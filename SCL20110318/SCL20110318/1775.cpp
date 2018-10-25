#include<iostream>
#include<string>
#include<stdio.h>
#include<memory.h>
#include<algorithm>
using namespace std;


int colN;
struct entry
{
	int id;
	int col[12];
};

int GetMin(int *pri,int colN)
{
	int min=10000;
	int k,i;
	for(i=0;i<colN;i++)
	{
		if(min>pri[i]){min=pri[i];k=i;}
	}
	if(min==10000) return -1;
	pri[k]=100000;
	return k;
}

bool cmp(entry a,entry b)
{
	int i=0;
	while(i<colN)
	{
		if(a.col[i]<b.col[i]) return true;
		if(a.col[i]>b.col[i]) return false;
		if(a.col[i]==b.col[i]) {i++;continue;}
	}
	return false;
}

int main(void)
{
	int i,j,k,h;
	int tesN;
	int entN;	
	int queN;
	int tmp;
	cin>>tesN;
	for(i=0;i<tesN;i++)
	{
		cin>>entN>>colN;
		entry ent[120];
		for(j=0;j<entN;j++)
		{
			for(k=0;k<colN;k++)
			{
				cin>>ent[j].col[k];
			}
			ent[j].id=j;
		}
		cin>>queN;
		
		for(j=0;j<queN;j++)
		{
			int pri[12];
			int ord[12];
			for(k=0;k<colN;k++)
			{
				cin>>pri[k];
			}
			for(k=0;k<colN;k++)
			{
				ord[k]=GetMin(pri,colN);
			}
			entry tmp[120];
			for(k=0;k<entN;k++)
			{
				tmp[k].id=ent[k].id;
				for(h=0;h<colN;h++)
				{
					tmp[k].col[h]=ent[k].col[ord[h]];
				}
			}
			sort(tmp,tmp+entN,cmp);
			for(k=0;k<entN-1;k++)
			{
				cout<<tmp[k].id<<' ';
			}
			cout<<tmp[k].id<<endl;
		}
	}
	return 0;
}


/*
2


6 3
1 1 1
1 2 3
2 2 4
2 2 3
3 1 2
3 2 2
4
1 2 3
0 1 2
30 20 10
0 -1 1

3 6
1 1 1 1 1 1
2 2 4 5 2 6
3 6 3 6 3 3
2
1 2 3 4 5 6
2 3 1 0 -1 4



0 1 3 2 4 5
0 1 3 2 4 5
0 4 5 1 3 2
0 4 1 3 2 5

 

*/