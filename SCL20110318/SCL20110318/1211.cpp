#include<iostream>
#include<map>
#include<set>
#include<string>
#include<queue>
using namespace std;

struct Node
{
	Node(int P,int D):Place(P),Days(D){}
	int Place;
	int Days;
};

int main(void)
{
	int StateN,RoadM,ReachL;
	int From,To;
	int QueryN;
	int A,B;
	map< int,set<int> > World;
	cin>>StateN>>RoadM>>ReachL;
	for(int i=0;i<RoadM;i++)
	{
		cin>>From>>To;
		World[From].insert(To);
	}
	cin>>QueryN;
	for(int i=0;i<QueryN;i++)
	{
		cin>>A>>B;
		int count=0;
		queue<Node>HeadQ;
		Node HeadN(A,1);
		HeadQ.push(HeadN);
		while(!HeadQ.empty())
		{
			HeadN=HeadQ.front();
			HeadQ.pop();
			if(HeadN.Days>ReachL) continue;
			for(set<int>::const_iterator it=World[HeadN.Place].begin();
				it!=World[HeadN.Place].end();it++)
			{
				if(*it==B )//��Ҳ����Ŀ���·����1,������ⲻӦ����days<=ReachL������׼ȷ��L������
				{
					if(HeadN.Days==ReachL)
						count++;
					else
						HeadQ.push(Node(*it,HeadN.Days+1));
				}
				else 
					//if(*it!=A)//���ܵ���Ŀ��ķ���ʼ�ڵ����ͷ���
					//�������⣬���Ծ�����ʼ�ڵ㣬���Ծ���ͬһ�ڵ�
					//HeadQ.push(*it);
					HeadQ.push(Node(*it,HeadN.Days+1));
			}		
		}
		cout<<count<<endl;
	}
	return 0;
}

/*
��ȫ������⣬���Ծ���ͬһ��㣬ֻ����ÿ��������һ�죬����ͣ�����������޻�ͼ��
�����ȫ��ȷ�����ǳ�ʱ���أ�Ч��̫�ͣ����·���

4 5 6
1 2
2 3
3 4
4 1
2 4
2
1 4
4 2

2
1


4 5 50
1 2
2 3
3 4
4 1
2 4
1
1 3
4175

7 11 10
1 2
2 3
3 4
4 1
2 4
7 1
7 4
5 4
3 5
2 6
6 3
3
7 1
7 4
7 6
12
16
4
*/