#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct data
{
	string id;
	string ip;

};

struct majia
{
	string mid;
	string mj;
};

bool cmp(data a,data b)
{
	return (a.ip<b.ip);
}

bool cmp1(majia a,majia b)
{
	return (a.mid<b.mid);
}

int main(void)
{
	int i;
	int tesN;
	while(cin>>tesN,tesN!=0)
	{
		data *stu=new data[tesN];
		for(i=0;i<tesN;i++)
		{
			cin>>stu[i].id>>stu[i].ip;
		}
		//sort(stu,stu+tesN,cmp);������stable_sort��������sicily��ͨ��������ΪIP��ַ����ͬ�ģ�stable���ı�˳�����ȶ���
		stable_sort(stu,stu+tesN,cmp);
		majia *st=new majia[tesN/2];
		int len=tesN/2;
		for(i=0;i<len;i++)
		{
			st[i].mid=stu[2*i].id;
			st[i].mj=stu[2*i+1].id;
		}
		stable_sort(st,st+len,cmp1);
		for(i=0;i<len;i++)
		{
			cout<<st[i].mj<<" is the MaJia of "<<st[i].mid<<endl;
		}
		cout<<endl;
		delete []stu;
		delete []st;
	
	}
	return 0;
}



/*

8
inkfish 192.168.29.24
zhi 192.168.29.235
magicpig 192.168.50.170
pegasus 192.168.29.235
iamcs 202.116.77.131
finalBob 192.168.29.24
tomek 202.116.77.131
magicduck 192.168.50.170
4
mmmmmm 172.16.72.126
kkkkkk 192.168.49.161
llllll 192.168.49.161
nnnnnn 172.16.72.126
0
4
mmmmmm asdfdsagfg
kkkkkk dsfsdg
llllll dsfsd
nnnnnn bfddf

tomek is the MaJia of iamcs
finalBob is the MaJia of inkfish
magicduck is the MaJia of magicpig
pegasus is the MaJia of zhi
 
llllll is the MaJia of kkkkkk
nnnnnn is the MaJia of mmmmmm

*/
///------------------------------------------------

//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std;
//
//struct majia
//{
//	string id1,id2;
//};
//bool cmp(const majia& mj1,const majia& mj2)
//{
//     return mj1.id1<mj2.id1;
//}
//
//int main()
//{
//    int i,j,k,n;
//    majia mj[11];
//    string id[21],ip[21];
//    while(cin>>n && n)
//    {
//        for(i=0;i<n;i++)
//            cin>>id[i]>>ip[i];
//        k=0;
//        for(i=n-1;i>0;i--)
//        {
//            for(j=0;j<i;j++)
//            {
//               if(ip[j]==ip[i])
//               {
//                   k++;
//                   mj[k-1].id1=id[j];
//                   mj[k-1].id2=id[i];
//                   break;
//               }
//            }
//        }
//        sort(mj,mj+k,cmp);
//        for(i=0;i<k;i++)
//            cout<<mj[i].id2<<" is the MaJia of "<<mj[i].id1<<endl;
//        cout<<endl;
//    }
//    return 0;
//}
//
// 







//
//#include<iostream>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//struct data
//{
//	int id;
//	string s;
//};
//
//bool cmp(data s1,data s2)
//{
//	if(s1.s>s2.s)
//		return false;
//	if(s1.s<s2.s)
//		return true;
//	if(s1.s==s2.s)
//		return  false;//����Ϊtrue������,Ϊʲô????
//}
//
//int main()
//{
//	int i;
//	int n;
//	cin>>n;
//	data *a=new data[n];
//	for(i=0;i<n;i++)
//	{
//		cin>>a[i].s;
//		a[i].id=i+1;
//	}
//	stable_sort(a,a+n,cmp);
//	//sort(a,a+n,cmp);
//	for(i=0;i<n;i++)
//	{
//		cout<<a[i].id<<"  "<<a[i].s<<endl;
//
//	}
//	delete []a;
//}

/*

5
asdfsadfds
dsfs
dsfs
bfddf
dsfs


4
1 
3
3
2


sort�Ķ���Ϊstringʱ��Ӧ�÷ǳ�ע�⡣������CMP�������������жϣ�
bool cmp(string s1,string s2)
{
	if(s1<=s2)  
		return true;
	else 
		return false;
}
Ҳ�����������жϣ�
bool cmp(string s1,string s2)
{
	if(s1>s2)
		return false;
	else 
		return true;
}
��Ϊ����������Ϊ
4
asdfsadfds
dsfsdg
dsfsdg
bfddf
����ִ��󡣶�����Ϊ�������ַ������ʱ������true����������ʱ�������ַ������ʱ��λ��Ӧ�ò���ı䣬Ӧ�÷���true�Ŷԡ�Ϊʲô����
�ѵ������ַ������ʱ�����뷵��false������Ȼ��ˣ�Ϊʲô????
bool cmp(string s1,string s2)
{
	if(s1>s2)
		return false;
	 if(s1<s2)
		return true;
	 if(s1==s2)
		return  false;//����Ϊtrue������
}



*/


//bool cmp(string s1,string s2)
//{
//	if(s1>s2)
//		return false;
//	 if(s1<s2)
//		return true;
//	 if(s1==s2)
//		return  false;//����Ϊtrue������,Ϊʲô????
//
//}

//bool cmp(int a,int b)
//{
//	if(a<b)
//		return true;
//	if(a==b) return false;//����Ϊtrue������,Ϊʲô????
//	if(a>b)	return false;
//
//}

//int main()
//{
//	int i;
//	int n;
//	cin>>n;
//	//string *a=new string[n];
//	int *a=new int[n];
//	for(i=0;i<n;i++)
//	{
//		cin>>a[i];
//	}
//	stable_sort(a,a+n,cmp);
//	for(i=0;i<n;i++)
//	{
//		cout<<a[i]<<endl;
//
//	}
//	delete []a;
//}