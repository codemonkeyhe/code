#include<iostream>
#include<queue>
#include<stdlib.h>
#include<string>
using namespace std;

//采用逆向邻接阵去做
struct node
{
	int vertex;
	node * next;
};

struct GraList
{
	int cost;
	node *next;
};

GraList adjlist[10010];
int re[10010];
bool visited[10010];
int main(void)
{
	int i,j,k,l;
	int n;
	int m;
	int cost;
	
	while(cin>>n,n!=0)
	{
		cin>>m;
		
		//fflush(stdin);
		cin.get();
		cost=0;
	//	char ch;
		for(i=1;i<=n;i++) {adjlist[i].next=NULL;re[i]=0;}
		for(i=1;i<=n;i++)//建立逆向邻接表
		{
			string str;
			string num;
			k=0;
			getline(cin,str);
			l=str.length();
			while(str[l-1]==' ')l--;
			for(j=0;j<=l;j++){
				if(str[j]!=' ' && str[j]!='\0')
					num=num+str[j];
				else{
					re[k]=atoi(num.c_str());
					num.clear();
					k++;
				}
			}
			adjlist[i].cost=re[0];
			for(j=1;j<k;j++){
				node * p=new node;
				p->vertex=re[j];
				p->next=adjlist[i].next;
				adjlist[i].next=p;
				p=NULL;
			}
		/*	cin>>adjlist[i].cost;
			while((ch=cin.get())==' '){}	
			while(ch!='\n'){
				while(ch==' ' ){ch=cin.get();}
				if(ch=='\n') break;
				string str;
				str=str+ch;
				while((ch=cin.get())!=' '){
					if(ch=='\n') break;
					str=str+ch;
				}
				node * p=new node;
				j=atoi(str.c_str());
				p->vertex=j;
				p->next=adjlist[i].next;
				adjlist[i].next=p;
				p=NULL;
			}	*/

		}
		for(i=1;i<=n;i++)
			visited[i]=false;
		queue<int> fa;
		fa.push(m);
		while(!fa.empty())
		{
			j=fa.front();
			fa.pop();
			cost=cost+adjlist[j].cost;
			visited[j]=true;
			node *p=adjlist[j].next;
			while(p!=NULL && !visited[p->vertex]){
				fa.push(p->vertex);
				visited[p->vertex]=true;
				p=p->next;
			}

		}
		if(m>n){ cout<<'0'<<endl;continue;}
		else cout<<cost<<endl;	
	}
	return 0;
}


/*
N (0≤N≤10,000)
2 2
3
2 1
3 3
3
2 1
4 1 2

7 3
3 4 5
2 1
4 1 2
1
3
5 5
7

8 3
3 4 5
2 1
4 1 2
1
3 8
5 5
7
30




7 X
1
2
3
4
5
6
7

7 1
10
20 1
30 1 2
40 1 2 3
50 1 2 3 4
60 1 2 3 4 5
70 1 2 3 4 5 6

12 11
10 4 5
7 1 9
4 1 2
5 5
11 8
3 5
9 10
20
3 1
10 
4 10 12 
12 

7 5
3 15 56
21 1
41 11 22
1
3
5 5
7

*/

//
//#include <iostream>   
//#include <sstream>   
//#include <string>   
//#include <vector>   
//#include <cstring>   
//using namespace std;   
//int n, m;   
//int cost[10000];   
//vector<int> adj[10000];   
//int allCost;   
//bool isVis[10000];   
//void getCost(int m) {   
//    for(vector<int>::iterator iter = adj[m].begin();   
//        iter != adj[m].end(); iter++) {   
//            if(!isVis[*iter]) {   
//                isVis[*iter] = true;   
//                allCost += cost[*iter];   
//                getCost(*iter);   
//            }   
//    }   
//}   
//int main() {   
//    string data;   
//    int num;   
//    while(cin >> n && n != 0) {   
//        cin >> m;   
//        memset(isVis, false, sizeof(isVis));   
//        for(int i = 0; i < n; i++)   
//            adj[i].clear();   
//        getline(cin, data);   
//        for(int i = 0; i < n; i++) {   
//            getline(cin, data);   
//            istringstream stream(data);   
//            stream >> num;   
//            cost[i] = num;   
//            while(stream >> num)   
//                adj[i].push_back(num - 1);   
//        }   
//        isVis[m - 1] = true;   
//        allCost = cost[m - 1];   
//        getCost(m - 1);   
//        cout << allCost << endl;   
//   }   
//    return 0;   
//}  
