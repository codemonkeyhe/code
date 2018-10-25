//#include<iostream>
//#include<stack>
//#include<string>
//using namespace std;
//int main(void)
//{
//	int n;
//	int i,j;
//	int key;
//	while(cin>>n)
//	{
//		int *a=new int[n];
//		stack<int> s1,s2;
//		string op;
//		for(i=0;i<n;i++){
//			cin>>a[i];
//		}
//		i=0;
//		key=1;
//		while(i<n){
//			if(s1.empty()){
//				s1.push(a[i]);
//				op=op+'a';
//				if(a[i]==key){	
//					op=op+'b';
//					s1.pop();
//					key++;
//				}
//			}else if(s1.top()>a[i]){
//				s1.push(a[i]);
//				op=op+'a';
//				while(!s1.empty() && s1.top()==key){	
//					op=op+'b';
//					s1.pop();
//					key++;
//				}
//
//			}else if(s2.empty()){
//				s2.push(a[i]);
//				op=op+'c';
//				if(a[i]==key){	
//					op=op+'d';
//					s2.pop();
//					key++;
//				}
//			}else if(s2.top()>a[i]){
//				s2.push(a[i]);
//				op=op+'c';
//				while(!s2.empty() && s2.top()==key){	
//					op=op+'d';
//					s2.pop();
//					key++;
//				}
//			}else{
//				cout<<'0'<<endl;
//				break;
//			}
//			i++;
//			if(key>n) {
//				for(j=0;j<(int)op.length()-1;j++)
//					cout<<op[j]<<" ";
//				cout<<op[j]<<endl;
//			}
//			
//		}//while
//		delete []a;
//	}//while
//	return 0;
//}


/*
10
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 10 9
1 2 3 4 5 6 7 8 



*/

//如果队列inSeq中存在i<j<k，使得inSeq[k]<inSeq[i]<inSeq[j]，那么inSeq[i]和inSeq[j]不能被放进同一个栈中   
#include <iostream>   
#include <stack>   
#include <cmath>   
#include <cstring>   
#include <string>   
using namespace std;   
#define INF 10000   
int color[1010];   
bool adj[1010][1010];   
int _min[1010];   
int n;   
int inSeq[1010];   
stack<int> s1;   
stack<int> s2;   
string path;   
bool dfs(int cur) {   
    for(int i = 0; i < n; i++) {   
        if(adj[cur][i]) {   
            if(color[i] == 0) {   
                color[i] = 3 - color[cur];   
                if(!dfs(i)) return false;   
            }else if(color[i] == color[cur]) return false;   
        }   
    }   
    return true;   
}   
int main() {   
    //freopen("1.txt", "r", stdin);   
    while(cin >> n) {   
        for(int i = 0; i < n; i++)   
            cin >> inSeq[i];   
        _min[n] = INF;   
        memset(adj, false, sizeof(adj));   
        memset(color, 0, sizeof(color));   
     for(int i = n - 1; i >= 0; i--)   
            _min[i] = min(inSeq[i], _min[i + 1]);   
        //找到所有无向边   
        for(int i = 0; i < n; i++) {   
            for(int j = i + 1; j < n; j++) {   
                if(inSeq[i] < inSeq[j] && inSeq[i] > _min[j + 1]) {   
                    adj[i][j] = adj[j][i] = true;   
                }   
            }   
        }   
        //染色   
        bool ok = true;   
        for(int i = 0; i < n; i++) {   
            if(color[i] == 0) {   
                color[i] = 1;   
                if(!dfs(i)) {   
                    ok = false;   
                    break;   
                }   
            }   
       }   
        if(!ok) {   
            cout << 0 << endl;   
            continue;   
        }   
        //模拟求解   
        int out = 0;        //输出队列的元素个数   
        path = "";   
        for(int i = 0; i < n; i++) {   
            if(color[i] == 1) {   
                path += "a ";   
                s1.push(inSeq[i]);   
            }   
            else {   
                path += "c ";   
                s2.push(inSeq[i]);   
            }   
            while((!s1.empty() && s1.top() == out + 1) ||    
                (!s2.empty() && s2.top() == out + 1)) {   
                if(s1.top() == out + 1) {   
                    path += "b ";   
                    s1.pop();   
                }else {   
                    path += "d ";   
                    s2.pop();   
                }   
                out++;   
            }   
        }   
        path.erase(path.size() - 1, 1);   
        cout << path << endl;   
    }   
    return 0;   
}  


