class NumCal {
     int *p;    // 数组首地址
     int size; // 数组size
 public:
     int sum(); // 计算数组元素和
     NumCal(); // 构造函数
     NumCal(int *new_p, int new_size); // 构造函数
 };

NumCal::NumCal(){};
NumCal::NumCal(int* new_p,int new_size):p(new_p),size(new_size){};
int NumCal::sum()
{
	int vsum=0;
	for(int i=0;i<size;++i)
		vsum+=p[i];
	return vsum;

}