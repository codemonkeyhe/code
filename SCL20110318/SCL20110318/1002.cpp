/*
Q1002: Anti-prime Sequences
问题描述
给定一个连续整数序列n, n+1, n+2, … , m，一个反素数序列是这些整数的一个重排，使得每对相邻的整数和为合数。
例如，若n = 1且m = 10，那么1, 3, 5, 4, 2, 6, 9, 7, 8, 10就是一个反素数序列。它也是按字典顺序的第一个这样的序列。
我们可以扩展此定义，度d反素数序列是相邻2~d个整数之和为合数的这种序列。所以，之前的序列是一个度2反素数序列，但是不是度3的，
因为子列5, 4, 2和为11。这些数按字典顺序的第一个度3反素数序列为1, 3, 5, 4, 6, 2, 10, 8, 7, 9。
输入格式
输入包含多组输入集。每个输入集包含同一行的三个整数，n, m和d。n, m和d的值满足1≤n<m≤1000和2≤d≤10。以一行0 0 0（此行不需处理）代表输入的结束。
输出格式
对于每个输入集，输出一行以逗号隔开的整数列，此整数列组成一个度d反素数序列（不要插入任何空格并且输出不要跨越多行）。
如果不存在反素数序列，则输出“No anti-prime sequence exist.”。
输入样例

    1 10 2
    1 10 3
    1 10 5
    40 60 7
    0 0 0
输出样例

    1,3,5,4,2,6,9,7,8,10
    1,3,5,4,6,2,10,8,7,9
    No anti-prime sequence exists.
    40,41,43,42,44,46,45,47,48,50,55,53,52,60,56,49,51,59,58,57,54
*/



////#include <iostream>   
////#include <cstring>   
////#include<stdio.h>
////#include <vector>   
////using namespace std; 
////
////
////
////如果要打印N以内的素数表，若M<N,且M是合数，则M必定存在一个因子(该因子!=1)小于等于sqrt(N)
////因此遍历2~sqrt(N),找到这个因子，乘以某个倍数时则可以剔除合数M
////为了减少遍历规模，只需要剔除2~sqrt(N)内素数的倍数即可
////因为（算术基本定理）任何一个大于1的自然数N，都可以唯一分解成有限个质数之积。所以，合数也必定能分成质数之积。
////因为假若在2~sqrt(N)内，存在合数，由算术基本定理可得，则这个合数肯定被更小的质因子的倍数给剔除，
////若M是素数，它不存在1和它本身之外因子，用因子的倍数剔除所有的合数后，剩余的便是素数
////N以内的数初始化为全是素数，不是素数的话迟早被剔除出来，
////该方法需要已知2~sqrt(N)以内的所有素数，先假设2~sqrt(N)以内的数全是素数，不是素数的倍数一样不是素数，
////const int L=10000;
////bool IsPrime[L+1];
////
////void PrimeTable()
////{
////	memset(IsPrime,true,sizeof(IsPrime));
////	IsPrime[0]=IsPrime[1]=false;
////	for(int i=2;i*i<=L;++i){
////		if(IsPrime[i]){//如果i是素数，那么它的倍数必定是合数,减少重复剔除，删除该过滤条件依然正确
////			for(int j=2;i*j<=L;++j)
////				IsPrime[i*j]=false;
////		}
////	}
////}
////
////
////
////
////
////
////检测新增加的l是否使整个序列是反素数序列
////inline bool IsAntiPrimeSqe(int *data,int l,int d)
////{
////	if(l<1) return true;
////	int sum=data[l];
////	int m=2;
////	for(int i=l-1;i>=0 && m<=d;--i){
////		sum+=data[i];
////		if(IsPrime[sum]) 
////			return false;
////		else 
////			m++;
////	}
////	return true;
////}
////
////从data[l~k-1]的全排列
////bool Permutation(int* data,int l,int k,int d)
////{
////	if(l==k-1){
////		if(data[9]==8 && data[8]==4 && data[7]==2)
////			cout<<"s "<<endl;
////		if(IsAntiPrimeSqe(data,k-1,d))
////			return true;
////		else
////			return false;
////	}else{
////		for(int i=l;i<k;++i){
////			swap(data[l],data[i]);
////			if(IsAntiPrimeSqe(data,l,d))
////				if(Permutation(data,l+1,k,d))
////					return true;
////			swap(data[l],data[i]);
////		}
////		return false;
////	}
////}
////
////
////int main()
////{
////	/*int data[]={1,2,3};
////	Permutation1(data,0,3);*/
////	int n,m,d;
////	PrimeTable();
////	while(scanf("%d%d%d",&n,&m,&d),n!=0 && m!=0 && d!=0){
////		int k=m-n+1;
////		int* sqe=new int[k];
////		for(int i=0;i<k;++i)
////			sqe[i]=n+i;
////
////		if(Permutation(sqe,0,k,d)){
////			printf("%d",sqe[0]);
////			for(int i=1;i<k;++i)
////				printf(",%d",sqe[i]);
////			printf("\n");
////		}
////		else 
////			printf("No anti-prime sequence exists.\n");
////		delete []sqe;
////	}
////	return 0;
////}


//
//
//#include <iostream>   
//#include <cstring>   
//#include <vector>   
//using namespace std;   
//int n, m, d;   
//bool isPrime[9956];    //素数
//vector<int> ans;   
//bool isVis[1001];   
//
//bool isPass() {   //判断2~D个数之和是不是合数
//     int maxIndex = ans.size() - 1;   
//    int sum = ans.back();   
//    for(int i = 1; i < d && i < (int)ans.size(); i++) {   
//        sum += ans[maxIndex - i];  
//		 if(isPrime[sum]) //如果其和是奇数，返回false
//			return false; 
//       
//    }  
//   return true;   //是合数，返回true
//}   
//
//bool dfs() {   
//    if(ans.size() == m - n + 1){   
//        if(isPass()) 
//			return true;   
//        else 
//			return false;   
//    }   
//    for(int i = n; i <= m; i++) {   
//        if(!isVis[i]) {   //如果该节点无效
//            ans.push_back(i);   
//            isVis[i] = true;   //标记该节点有效
//            if(ans.size() > 1) {   
//    //            if(isPass() && dfs()) //是合数并且继续深搜仍然是合数，则返回true。
//				//	return true;   
//				//isVis[i] = false;  //若不是合数或者是合数但是深搜时是素数，则标记该节点无效 
//				//ans.pop_back();
//				if(isPass())//是合数则继续深搜
//				{
//					if(dfs()) //若继续深搜是合数，则返回true
//						return true;
//					else{     //若深搜返回结果是素数，则标记该节点无效并弹出堆栈
//						isVis[i]=false;
//						ans.pop_back();
//					}
//				}
//				else//若不是合数，则标记该节点无效并弹出堆栈
//				{
//					isVis[i]=false;
//					ans.pop_back();
//				}
//			}
//			else if(dfs())    //继续深搜，是合数返回true
//				return true;   
//			else{//当且只有一个节点并且深搜返回的是素数时，擦掉初始头节点，然后搜索i++节点。   
//				isVis[i] = false;    
//				ans.pop_back();
//			}   
//		}   
//    }   
//    return false;   
//}   
//
//void setPrime() {  // 设置1~9956里的质数表
//    memset(isPrime, true, sizeof(isPrime));   
//    isPrime[0] = isPrime[1] = false;   
//    for(int i = 2; i * i <= 9956; i++) {   
//        if(isPrime[i]) {   
//            for(int k = 2; k * i < 9956; k++)    
//                isPrime[k * i] = false;   
//        }   
//    }   
//}    
//
//int main() {   
//    setPrime();   
//    while(cin >> n >> m >> d && n != 0 && m != 0 && d != 0) {   
//        ans.clear();   
//        memset(isVis, false, sizeof(isVis));   
//        if(dfs()) {   
//            bool isFirst = true;   
//            for(vector<int>::iterator iter = ans.begin();   
//                iter != ans.end(); iter++) {   
//                if(isFirst) {   
//                    cout << *iter;   
//                    isFirst = false;   
//                }else cout << "," << *iter;   
//            }   
//            cout << endl;   
//        }else 
//			cout << "No anti-prime sequence exists.\n";   
//    }
//	return 0;
//}  
//
//



#include<iostream>            
#include<string>   
using namespace std;   
  
//书上的源代码，封装成函数形式，j的范围优化了一下，同时i的下限变成i>=1,其他不变  
pair<int,string> fun(const string &str)    
{    
    int count=0;    
    string substr,tep;    
    int i,j,len=str.length();    
    for(i=len-1;i>=1;--i){    
        for(j=0;j<=len-i;j++){    
                size_t t=0;    
                size_t num=0;    
                tep=str.substr(j,i);    
                t=str.find(tep);    
                num=str.rfind(tep);    
                if(t!=num){    
                    count=t+1;    
                    substr=tep;    
                    return make_pair(count,substr);    
                }     
        }    
    }    
    return make_pair(count,substr);    
}    
        
        
pair<int,string> fun1(const string& str)    
{    
    int index=0;    
    int maxlen=0;    
    string substr;    
    int i=0,j=0;    
    int len=str.length();    
    int k=i+1;    
    int s,lt;  
    while(i<len){    
        j=str.find(str[i],k); //从(k~len-1)范围内寻找str[i]    
        if(j==string::npos  )//若找不到，说明(k~len-1)范围内没有str[i]    
        {    
            i++;    
            k=i+1;    
        }else{ //若找到，则必有(j>=i+1)    
            s=i;     
            lt=1;    
            while(str[++s]==str[++j] && j<len){}    
            lt=s-i;    
            if(lt>maxlen)    
            {    
                maxlen=lt;    
                substr=str.substr(i,lt);    
                index=i+1;    
            }    
            k=j;    
        }//else    
    }//while    
    return make_pair(index,substr);    
}    
        
int main()    
{    
            
    string str;    
    pair<int,string> rs;    
    while(cin>>str)    
    {    
        rs=fun(str);    
        cout<<rs.second<<":"<<rs.first<<endl;    
        rs=fun1(str);    
        cout<<rs.second<<":"<<rs.first<<endl;    
        
    /*书上源代码   
    int count=0;  
        string substr,tep;  
        int i,j,len=str.length();  
        for(i=len-1;i>1;--i){  
            for(j=0;j<len;j++){  
                if(j+i<=len){  
                    size_t t=0;  
                    size_t num=0;  
                    tep=str.substr(j,i);  
                    t=str.find(tep);  
                    num=str.rfind(tep);  
                    if(t!=num){  
                        count=t+1;  
                        substr=tep;  
                        cout<<tep<<" : "<<t+1<<endl;  
                        return 0;  
                    }  
                }  
            }  
        }*/    
                
        
    }    
    return 0;    
}  