#include<iostream>
#include<algorithm>
#include<list>
#include<iterator>
using namespace std;

int main(void)
{
	int T;
	int n,m;
	cin>>T;
	int op,e1,e2;
	list<int> li;
	list<int>::iterator it1;
	while(T>0)
	{
		T--;

		cin>>n>>m;
		for(int i=1;i<=n;i++)
			li.push_back(i);

		for(int i=0;i<m;i++)
		{
			cin>>op>>e1>>e2;
			if(op==1)
			{

			}else{//op==2

			}
		}

		cout<<endl;
	}
	return 0;
}


/*


数据量大，用链表超时
int main(void)
{
	int T;
	int n,m;
	cin>>T;
	int op,e1,e2;
	list<int> li;
	list<int>::iterator it1;
	while(T>0)
	{
		T--;
		li.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			li.push_back(i);
		for(int i=0;i<m;i++)
		{
			cin>>op>>e1>>e2;
			if(op==1)
			{
				it1=find(li.begin(),li.end(),e1);
				li.erase(it1);
				it1=find(li.begin(),li.end(),e2);
				li.insert(it1,e1);
			}else{//op==2
				it1=find(li.begin(),li.end(),e1);
				li.erase(it1);
				it1=find(li.begin(),li.end(),e2);
				it1++;
				li.insert(it1,e1);
			}
		}
		for(it1=li.begin();it1!=li.end();it1++)
			cout<<*it1<<" ";
		cout<<endl;
	}
	return 0;
}

*/