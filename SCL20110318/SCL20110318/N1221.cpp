#include<iostream>
#include<stdio.h>
#include<memory.h>
using namespace std;

#define MaxSize 101

int main(void)
{
	int StateN,RoadM,ReachL;
	int From,To;
	int QueryN;
	int A,B;
	int WorldMap[MaxSize][MaxSize]={0};
	int NDayMap[MaxSize][MaxSize]={0};
	int TMap[MaxSize][MaxSize]={0};
	cin>>StateN>>RoadM>>ReachL;
	for(int i=0;i<RoadM;i++)
	{
		cin>>From>>To;
		WorldMap[From][To]=1;
	}
	int Len=StateN+1;
	for(int i=0;i<Len;i++)
		for(int j=0;j<Len;j++)
			TMap[i][j]=WorldMap[i][j];
	for(int p=1;p<ReachL;p++){	
		for(int i=1;i<Len;i++)
			for(int j=1;j<Len;j++)	{
				int sum=0;
				for(int k=1;k<Len;k++){
					sum+=TMap[i][k]*WorldMap[k][j];
					NDayMap[i][j]=sum;
				}
			}
		for(int i=0;i<Len;i++)
			for(int j=0;j<Len;j++)
				TMap[i][j]=NDayMap[i][j];		
	}
	cin>>QueryN;
	for(int i=0;i<QueryN;i++)
	{
		cin>>A>>B;
		cout<<NDayMap[A][B]<<endl;
	}
	return 0;
}


/*
�ö�̬��������ᳬʱ����
����ֱ��ʹ�����飬��Ҫ��̬����
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

4 5 6
1 2
2 3
3 4
4 1
2 4
2
2 4
3 4 
*/


//��̬�������飬 ��ʱ
//
//inline void SetNDayMap(int** WorMap,int** NDayMap, int Len, int Pow)
//{
//	int** TMap=new int*[Len];//�����ά����
//	for(int i=0;i<Len;i++)
//	{
//		TMap[i]=new int[Len];
//	}
//	for(int i=0;i<Len;i++)
//		for(int j=0;j<Len;j++)
//			TMap[i][j]=WorMap[i][j];
//	for(int p=1;p<Pow;p++){	
//		for(int i=1;i<Len;i++)
//			for(int j=1;j<Len;j++)	{
//				int sum=0;
//				for(int k=1;k<Len;k++){
//					sum+=TMap[i][k]*WorMap[k][j];
//					NDayMap[i][j]=sum;
//				}
//			}
//		for(int i=0;i<Len;i++)
//			for(int j=0;j<Len;j++)
//				TMap[i][j]=NDayMap[i][j];
//			
//	}
//	for(int i=0;i<Len;i++)//�ͷŶ�ά����
//	{
//		delete TMap[i];
//		TMap[i]=NULL;
//	}
//	delete []TMap;
//	TMap=NULL;
//}



//int StateN,RoadM,ReachL;
	//int From,To;
	//int QueryN;
	//int A,B;
	//cin>>StateN>>RoadM>>ReachL;
	//int** WorldMap=new int*[StateN+1];//�����ά����
	//int** NDayMap=new int*[StateN+1];
	//int** TMap=new int*[StateN+1];
	//for(int i=0;i<=StateN;i++)
	//{
	//	WorldMap[i]=new int[StateN+1];
	//	memset(WorldMap[i],0,(StateN+1)*sizeof(int));//��ʼ��
	//	NDayMap[i]=new int[StateN+1];
	//	memset(NDayMap[i],0,(StateN+1)*sizeof(int));//��ʼ��
	//	TMap[i]=new int[StateN+1];
	//	memset(TMap[i],0,(StateN+1)*sizeof(int));//��ʼ��
	//}

	//for(int i=0;i<RoadM;i++)
	//{
	//	cin>>From>>To;
	//	WorldMap[From][To]=1;
	//}
	//int Len=StateN+1;
	//for(int i=0;i<Len;i++)
	//	for(int j=0;j<Len;j++)
	//		TMap[i][j]=WorldMap[i][j];
	//for(int p=1;p<ReachL;p++){	
	//	for(int i=1;i<Len;i++)
	//		for(int j=1;j<Len;j++)	{
	//			int sum=0;
	//			for(int k=1;k<Len;k++){
	//				sum+=TMap[i][k]*WorldMap[k][j];
	//				NDayMap[i][j]=sum;
	//			}
	//		}
	//	for(int i=0;i<Len;i++)
	//		for(int j=0;j<Len;j++)
	//			TMap[i][j]=NDayMap[i][j];
	//		
	//}


	////SetNDayMap(WorldMap,NDayMap,StateN+1,ReachL);
	//cin>>QueryN;
	//for(int i=0;i<QueryN;i++)
	//{
	//	cin>>A>>B;
	//	cout<<NDayMap[A][B]<<endl;
	//}
	//for(int i=0;i<StateN+1;i++)//�ͷŶ�ά����
	//{
	//	delete WorldMap[i];
	//	delete NDayMap[i];
	//	delete TMap[i];
	//	TMap[i]=NULL;
	//	WorldMap[i]=NULL;
	//	NDayMap[i]=NULL;
	//}
	//delete []WorldMap;
	//delete []NDayMap;
	//WorldMap=NULL;
	//NDayMap=NULL;
	//TMap=NULL;
	//return 0;