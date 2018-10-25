#include<iostream>
#include<string>
#include <stack>
#include <iomanip>
using namespace std;

inline float Parallel(float v1,float v2)
{
	return v1*v2;	
}

inline float Series (float v1,float v2)
{
	return 1-(1-v1)*(1-v2);
}

int main(void)
{
	int n;
	cin>>n;
	string exp;
	cin>>exp;
	float* Pi=new float[n];
	for(int i=0;i<n;i++)
		cin>>Pi[i];
	
	string::size_type it=0;//替换字符串，把所有的")("替换成")*("
	while( (it=exp.find(")(",it) )!=string::npos){
		exp.replace(it,2,")*(");
		it=it+3;
	}
	exp='('+exp+')';
	stack<char> op;
	stack<float> val;
	for(int i=0;i<exp.size();i++)
	{
		if(exp[i]=='('|| exp[i]==',' || exp[i]=='*' ){//压入操作符
			op.push(exp[i]);
		}
		else if(exp[i]==')'){//处理操作符和操作数
			char TopOp;
			while(	(TopOp=op.top()) !='(')//只能是'，'号，即两个最近的()之间只能是一系列逗号
			{
				if(TopOp!=',')
					cout<<"EEE"<<endl;
				float rv=val.top();
				val.pop();
				float lv=val.top();
				val.pop();
				float res=Series(lv,rv);
				val.push(res);
				op.pop();
			}
			op.pop(); //弹出优先级(,,,,)运算符中的（ 其次解决剩余的
			if(op.empty() && val.size()==1 ) 
			{
				float res=val.top();
				val.pop();
				cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(4);
				cout<<res<<endl;
				return 0;
			}
			TopOp=op.top();
			if(TopOp=='*') //*每次只能有一个在堆栈中，只需判断一次
			{
					float rv=val.top();
					val.pop();
					float lv=val.top();
					val.pop();
					float res=Parallel(lv,rv);
					val.push(res);
					op.pop();
			}
		}else{//压入操作数
			int index=exp[i]-'A';
			val.push(Pi[index]);
		}
	}//for
	delete []Pi;
	return 0;
}


/*
5
(A,B)((C)(D),E)
0.2
0.3
0.4
0.5
0.6

0.2992

5
A,B,C,D,E
0.2
0.3
0.4
0.5
0.6

0.9328
n 

5
(A)(B)(C)(D)(E)
0.2
0.3
0.4
0.5
0.6

0.0072

4
A,(B)(C)(D)
0.2
0.3
0.4
0.5
0.2480

3
(C)(A,B)
0.2
0.3
0.4
0.176
*/