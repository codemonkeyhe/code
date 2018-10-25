#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

typedef string::size_type StrNum;

struct Node
{
	char val;
	Node* left;
	Node* right;
};


Node* GetBinaryTree(const string& PreStr,const string& InStr)
{
	StrNum PreLength=PreStr.length();
	StrNum InLength=InStr.length();
	Node* TreRoot=new Node;
	TreRoot->val=PreStr[0];
	if(PreLength==1)
	{	
		TreRoot->left=0;
		TreRoot->right=0;
		return TreRoot;
	}
	StrNum RootInd= InStr.find(PreStr[0]);
	if(RootInd!=0)//Èô×ó×ÓÊ÷´æÔÚ
		TreRoot->left=GetBinaryTree(PreStr.substr(1,RootInd),InStr.substr(0,RootInd));
	else 
		TreRoot->left=0;
	if(RootInd!=InLength-1)//ÈôÓÒ×ÓÊ÷´æÔÚ
		TreRoot->right=GetBinaryTree(PreStr.substr(RootInd+1),InStr.substr(RootInd+1));
	else
		TreRoot->right=0;
	return TreRoot;
}

void WidePrint(Node* Root)
{
	queue<Node*> Tree;
	if(Root!=0)
	{
		Tree.push(Root);
	}
	while(!Tree.empty())
	{
		Node* temp=Tree.front();
		Tree.pop();
		cout<<temp->val;
		if(temp->left!=0)
			Tree.push(temp->left);
		if(temp->right!=0)
			Tree.push(temp->right);
	}
}

int main()
{
	int Num;
	cin>>Num;
	for(int i=0;i<Num;i++)
	{
		string PreStr,InStr;
		cin>>PreStr>>InStr;
		Node* TreRoot=GetBinaryTree(PreStr,InStr);
		WidePrint(TreRoot);
		cout<<endl;
	}
	return 0;
}


/*
2 
DBACEGF ABCDEFG 
BCAD CBAD


DBEACGF 
BCAD

*/