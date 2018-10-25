#include<iostream>
#include<iomanip>
using namespace std;

#define PI		3.141592653589793
#define Sqrt2	1.414213562373095  
#define Sqrt3	1.732050807568877 
#define Sqrt6	2.449489742783178

template<typename T>
class Geometry
{
public:
	Geometry(){};
	Geometry(T p1,T p2=0.0000):m1(p1),m2(p2){};
	T GetICirCleArea(){return PI*m1*m1;};
	T GetICirClePeri(){return 2.0*PI*m1;};
	T GetRecArea(){return m1*m1*4.0;};
	T GetRecPeri(){return 8.0*m1;};
	T GetOCirCleArea(){return PI*2.0*m1*m1;};
	T GetOCirClePeri(){return 2.0*PI*m1*Sqrt2;};
	T GetRecDiagonal(){return 2.0*m1*Sqrt2;};
	T GetTriArea(){return 6.0*Sqrt3*m1*m1;};
	T GetTriPeri(){return 6.0*Sqrt6*m1;};
private:
	T m1;
	T m2;
};



int main(void)
{
	int T;
	double r;
	cin>>T;
	while(T>0)
	{
		--T;
		cin>>r;
		Geometry<double> Geo(r);
		cout<<fixed<<setprecision(4);
		cout<<Geo.GetICirCleArea()<<" "<<Geo.GetICirClePeri()<<endl;
		cout<<Geo.GetRecArea()<<" "<<Geo.GetRecPeri()<<" "<<Geo.GetRecDiagonal()<<endl;
		cout<<Geo.GetOCirCleArea()<<" "<<Geo.GetOCirClePeri()<<endl;
		cout<<Geo.GetTriArea()<<" "<<Geo.GetTriPeri()<<endl;
	}
	return 0;
}

/*
第1行为正整数T,表示测试数组组数。接下来有n行, 每行有 1 个实数r,表示圆c1的半径
1
2
第1行是计算得到的圆c1 的面积和周长;
第2行是矩形s 的面积,周长和对角线长度;
第3 行是圆c2的面积和周长,
第4行是三角形t的面积和周长,
结果四舍五入到四位数。


12.5664 12.5664
16.0000 16.0000 5.6569
25.1327 17.7715
41.5692 29.3939

*/