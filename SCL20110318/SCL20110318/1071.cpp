#include<iostream>
#include<iterator>
#include<set>
#include<map>
#include<numeric>
using namespace std;

int Tile[100][4];

int GetMaxAreaAfterCut(const int& XL,const int& YL,const int& XR,const int& YR,set<int>& RecInd)
{
	map<int, multiset<int> > XLine;
	map<int, multiset<int> > YLine;
	map<int, multiset<int> >::iterator ma;
	set<int> part1;
	set<int> part2;
	set<int>::iterator it;
	int Area1,Area2;
	int res;
	for(it=RecInd.begin();it!=RecInd.end();it++)
	{
		XLine[Tile[*it][0]].insert(Tile[*it][3]-Tile[*it][1]);
		YLine[Tile[*it][1]].insert(Tile[*it][2]-Tile[*it][0]);
	}
	for(ma=XLine.begin();ma!=XLine.end();ma++)
	{
		int Width=accumulate((ma->second).begin(),(ma->second).end(),0);
		if(Width==YR-YL && ma->first!=XL){//表示可以切割
			// 并且切割的不是边界，把RecInd分成2部分，继续递归
			for(it=RecInd.begin();it!=RecInd.end();it++)
			{
				if(Tile[*it][0]< (ma->first))
				{
					part1.insert(*it);
				}else{
					part2.insert(*it);
				}
			}
			Area1=GetMaxAreaAfterCut(XL,YL,ma->first,YR,part1);
			Area2=GetMaxAreaAfterCut(ma->first,YL,XR,YR,part2);
			return (Area1>Area2)?Area1:Area2;
		}
	}
	
	for(ma=YLine.begin();ma!=YLine.end();ma++)
	{
		int Length=accumulate((ma->second).begin(),(ma->second).end(),0);
		if(Length==XR-XL && ma->first!=YL)
		{
			for(it=RecInd.begin();it!=RecInd.end();it++)
			{
				if(Tile[*it][1]< (ma->first))
				{
					part1.insert(*it);
				}else{
					part2.insert(*it);
				}
			}
			Area1=GetMaxAreaAfterCut(XL,YL,XR,ma->first,part1);
			Area2=GetMaxAreaAfterCut(XL,ma->first,XR,YR,part2);
			return (Area1>Area2)?Area1:Area2;
		}
	}
	return (YR-YL)*(XR-XL);
}


int main(void)
{
	int N;
	int Length=0,Width=0;
	int T;
	int XL,XR,YD,YU;
	cin>>N;
	int area=0;
	for(int i=0;i<N;i++)
	{
		cin>>Length>>Width;
		cin>>T;
		set<int> Rec;
		for(int j=0;j<T;j++)
		{
			cin>>Tile[j][0]>>Tile[j][1]>>Tile[j][2]>>Tile[j][3];
			Rec.insert(j);
		}
		area=GetMaxAreaAfterCut(0,0,Length,Width,Rec);
		cout<<area<<endl;
	}//for
	return 0;
}


/*

思路：



7
300 400 
3 
200 200 300 400 
0 0 300 200 
0 200 200 400 
300 300 
5 
0 0 200 100 
100 200 300 300 
100 100 200 200
200 0 300 200 
0 100 100 300 
300 400 
3 
200 200 300 400 
0 0 300 200 
0 200 200 400 
300 300
7
0 0 100 100
100 0 200 100
200 0 300 100
0 100 300 200
0 200 100 300
100 200 200 300
200 200 300 300
300 300 
6 
0 0 100 100
100 0 200 100 
100 200 300 300 
100 100 200 200
200 0 300 200 
0 100 100 300 
300 300
1
0 0 300 300
200 200
4
0 0 100 100
100 100 200 200
100 0 200 100
0 100 100 200

60000 
90000
60000
30000
20000
90000
10000
*/