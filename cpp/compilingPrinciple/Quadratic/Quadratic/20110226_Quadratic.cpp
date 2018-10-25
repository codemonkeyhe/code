#include <iostream>
using namespace std;

struct Quadratic
{
	float a;
	float b;
	float c;
};

void Init(Quadratic &tmp,float x1,float x2,float x3)
{
	tmp.a=x1;
	tmp.b=x2;
	tmp.c=x3;
}

Quadratic Add(Quadratic tp1,Quadratic tp2)
{
	Quadratic tmp;
	tmp.a=tp1.a+tp2.a;
	tmp.b=tp1.b+tp2.b;
	tmp.c=tp1.c+tp2.c;
	return tmp;
}


void print(Quadratic tmp)
{
	if(tmp.a!=0) printf("%3.1fx^2",tmp.a);
	if(tmp.b>0) printf("+%3.1fx",tmp.b);
	if(tmp.b<0) printf("%3.1fx",tmp.b);
	if(tmp.c>0) printf("+%3.1f",tmp.c);
	if(tmp.c<0) printf("%3.1f",tmp.c);
}

int main()
{
	Quadratic Q1,Q2,Q3;
	Init(Q1,4,3,1);
	Init(Q2,2,4,3);
	Q3=Add(Q1,Q2);
	print(Q3);
	return 0;
}