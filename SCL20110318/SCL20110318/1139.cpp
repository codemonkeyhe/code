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
	
	string::size_type it=0;//�滻�ַ����������е�")("�滻��")*("
	while( (it=exp.find(")(",it) )!=string::npos){
		exp.replace(it,2,")*(");
		it=it+3;
	}
	exp='('+exp+')';
	stack<char> op;
	stack<float> val;
	for(int i=0;i<exp.size();i++)
	{
		if(exp[i]=='('|| exp[i]==',' || exp[i]=='*' ){//ѹ�������
			op.push(exp[i]);
		}
		else if(exp[i]==')'){//����������Ͳ�����
			char TopOp;
			while(	(TopOp=op.top()) !='(')//ֻ����'��'�ţ������������()֮��ֻ����һϵ�ж���
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
			op.pop(); //�������ȼ�(,,,,)������еģ� ��ν��ʣ���
			if(op.empty() && val.size()==1 ) 
			{
				float res=val.top();
				val.pop();
				cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setprecision(4);
				cout<<res<<endl;
				return 0;
			}
			TopOp=op.top();
			if(TopOp=='*') //*ÿ��ֻ����һ���ڶ�ջ�У�ֻ���ж�һ��
			{
					float rv=val.top();
					val.pop();
					float lv=val.top();
					val.pop();
					float res=Parallel(lv,rv);
					val.push(res);
					op.pop();
			}
		}else{//ѹ�������
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