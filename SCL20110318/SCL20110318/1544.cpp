#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool cmp(char a,char b)
{
	return a<b;
}


int main(void)
{
	string lis;
	char li[15];
	int i,j,k,c;
	int l1,l2;
	string num;
	bool con=false;
	while(cin>>lis>>num)
	{
		if(num=="0"){cout<<"NVALID INPUT"<<endl;continue;}
		l1=(int)lis.size();
		strcpy(li,lis.c_str());
		li[l1]='\0';
		sort(li,li+l1,cmp);
		lis=li;
		l2=num.size();
		i=0;
		j=l2-1;
		while(i<=j){
			if(lis.find(num[i])==string::npos) //找不到
			{
				cout<<"NVALID INPUT"<<endl;
				con=true;
				break;
			}
			i++;
		}
		if(con==true) continue;
		i=0;
		c=1;
		while(1){
			k=lis.find(num[j]);
			if(k<l1-1 ) {
				if(c==0){//没有进位
					//num[j]=lis[k+1];
					break;
				}
				else{//有进位
					num[j]=lis[k+1];
					j--;	
					c=0;
					if(j<0) break;
				}
			}
			else 
			{
				num[j]=lis[0];
				j--;			
				c=1;
				if(j<0) break;
			}
		}
		if(c==1){
			k=lis.find('0');
			if(k==string::npos){
				 num.insert(0,1,lis[0]);
			}else
			{
				 num.insert(0,1,lis[k+1]);
			}
		}
		cout<<num<<endl;
	
	}
	return 0;
}


/*
如何把string转化为char *,用strcpy（char*,str.c_str()）
结尾记得补上‘\0’
0123456789
16
012345689
16
358
548
534
033
9876543210
999
012345
0
1
1
01325678
56
01325678
57
01325678
58
01325678
568
01325678
578
01325678
588
01325678
888

17
18
INVALID INPUT
INVALID INPUT
1000
INVALID INPUT
11


*/