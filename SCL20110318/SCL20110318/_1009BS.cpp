#include<iostream>
#include <vector>
using namespace std;

//the function search in an ordered vector table between bot and top (inclusive) for x.
// It returns the index of its last oocurrence if search is successful, it returns -1 if search is unsuccessful.
template <typename Comparable>
int binarySearch(const vector<Comparable> table,int bot, int top, const Comparable &x)
{
	// insert your code here.
	while(bot<=top){
		int it;
		it=(top+bot)/2;
		if(x>=table[it]){
			bot=it;
			if(bot+1==top){
				if(table[top]==x) return top;
				else if(table[bot]==x) return bot;
				else return -1;
			}
		}
		else{
			top=it-1;
			if(top==bot)
			{
				if(table[bot]==x) return bot;
				else return -1;
			}
		}
	}
}

int main(void)
{
	int a[ ] = {0,1,1,3,3,3,6};
	int b[]={3,3,3,3,3};
	vector<int> v(a,a+7);
	vector<int> vb(b,b+5);
	cout << binarySearch(v, 0, 2, 1)<<endl;  //2
	cout << binarySearch(v, 0, v.size()-1, 3)<<endl;  // Êä³ö5
	cout << binarySearch(v, 0, v.size()-1, 7)<<endl;  //Êä³ö-1

	cout << binarySearch(v, 0, v.size()-1, 2)<<endl; 
	cout << binarySearch(vb, 0, vb.size()-1, 3)<<endl; 
	return 0;
}