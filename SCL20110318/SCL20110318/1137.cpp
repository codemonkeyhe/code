#include<iostream>
using namespace std;
int main(void)
{
	int n,k;
	cin>>n>>k;
	int di[30001];
	int tail,head;
	int len;
	for(int i=0;i<n;++i)
		cin>>di[i];
	tail=head=0;
	int min=di[0];
	int max=di[0];
	int maxlen=0;
	len=1;
	while(tail<n)//tailβָ�룬���α���ÿ����㣬���ҳ���ߵ������
	{
		while(max-min<=k)// ���С��k,���ͷheadһֱ��ǰ������len+1,ÿ�ξ�����max��min��ֱ������K
		{
			++head;
			if(di[head]>max) max=di[head];
			else if(di[head]<min) min=di[head];
			++len;
		}
		--len;
		if(len>=maxlen) maxlen=len;//�ѵ�ǰtail��ָ���β�ڵ�Ϊ���ĸߵ������ĳ����ж��Ƿ����
		++tail;
		head=tail;
		max=di[tail];
		min=di[tail];
		len=1;
	}
	cout<<maxlen<<endl;
	return 0;
}


/*
��һ��������n��k���ֱ��ʾ������ĸ����Ͳ�ʿҪ������ˮ��Ҳ���ǺӴ����Ʋ��
�ڶ�����n����������ʾ�����ο�ʼ���εõ���ˮλ���di(1��i��n, 0��di��32767)��

6 2
5 3 2 2 4 5



*/


//���˴���
/*
#include <iostream>
using namespace std;

int maxlength(int deep[],int size, int index,int k)
{
    int length = 2;
    int max = (deep[index] > deep[index+1]) ? deep[index] : deep[index+1];
    int min = (deep[index] < deep[index+1]) ? deep[index] : deep[index+1];
    if(max - min > k)
    return 1;
    for(int i = index+2; i < size; i++)
    {
        if( deep[i] - max >= -k
        && deep[i] - max <= k
        && deep[i] - min <= k
        && deep[i] -min >=-k)
        {
            length++;
            if(deep[i] > max)
               max = deep[i] ;
            if(deep[i] < min)
               min = deep[i];
        }
        else break;
    }
    return length;
}
int main()
{
    int deep[32767],k;
    int size;
	cin >> size>>k;
    for(int i = 0; i < size; i++)
        cin >> deep[i];
    int max = 0;
    for(int i = 0; i <size; i++)
    {
       int temp = maxlength(deep,size,i,k);//���α���ÿ����Ϊ������󳤶ȴ����Ҹߵ���������K
       if(temp > max)//�ҳ����ĸߵ������
          max = temp;
    }
    cout << max<<endl;
    return 0;
}

*/