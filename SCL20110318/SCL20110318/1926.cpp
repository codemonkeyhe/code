class NumCal {
     int *p;    // �����׵�ַ
     int size; // ����size
 public:
     int sum(); // ��������Ԫ�غ�
     NumCal(); // ���캯��
     NumCal(int *new_p, int new_size); // ���캯��
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