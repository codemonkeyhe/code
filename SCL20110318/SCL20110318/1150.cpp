#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include "tesy.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
using namespace std;

signed int j=0;
const int fact[9] = {0 , 1 , 2 , 6 , 24 , 120 , 720 , 5040 , 40320};

int cantor(int s)  
{
    int temp[9];
    int code = 0;
    for (int i = 8 ; i >= 1 ; --i)
    {
        temp[i] = s % 10;
        s /= 10;
    }
    for (int i = 1 ; i <= 8 ; ++i)
    {
        int cnt = 0;
        for (int j = i + 1 ; j <= 8 ; j++)
            if (temp[i] > temp[j]) ++cnt;
        code += fact[8-i] * cnt;
    }
    return code;
}




//
//
//unsigned long int cantor(unsigned long int S)
//{
//	long int  x=0;
//	int i,p,k,j;
//	bool hash[8]={false};
//	for(i=8;i>=2;i--)
//	{
//		k=S>>3*(i-1);
//		S-=k<<3*(i-1);
//		hash[k]=true;
//		p=k;
//		for(j=0;j<=k-1;j++)
//			if (hash[j])
//				p--;
//		x+=fac[i-1]*p; 
//	}
//	return x;
//}





int main()
{
	


	 //Item_base item; // object of base type
  //   Bulk_item bulk; // object of derived type

  //   //// ok: uses Item_base::Item_base(const Item_base&) constructor
  //   Item_base item1(bulk);  // bulk is "sliced down" to its Item_base portion 
	
      ////ok: calls Item_base::operator=(const Item_base&)
    //// item = bulk;           // bulk is "sliced down" to its Item_base portion

	 
////i=cantor(213);
	////cout<<i<<endl;
	return 0;
}

	



/*
4
5 8 7 6
4 1 2 3
3
8 7 6 5
1 2 3 4
-1


2 AB
1 A


*/