#include<iostream>
#include <stack>
using namespace std;

struct Node
{
	char val;
	int left;
	int right;
};

Node Tree[1001];

void PrintPreTree(int root)
{
	cout<<Tree[root].val;
	if(Tree[root].left!=0)
		PrintPreTree(Tree[root].left);
	if(Tree[root].right!=0)
		PrintPreTree(Tree[root].right);
}

int main(void)
{
	int n;
	int Id;
	char Val;
	int L,R;
	bool head[1001];
	while(cin>>n)
	{
		for(int i=0;i<=1000;i++)//��ʼ��
		{
			Tree[i].val=0;
			//head[i]=false;
			head[i]=true;
		}

		for(int i=0;i<n;i++){
			cin>>Id>>Val>>L>>R;
		
			Tree[Id].val=Val;
			Tree[Id].left=L;
			Tree[Id].right=R;
			head[L]=false;
			head[R]=false;
		}
		for(int i=1;i<=1000;i++){//�ų����Ǹ��ڵ�Ľڵ�
			if(head[i] && Tree[i].val==0 ){
				head[i]=false;
			}
			//if(head[i]){
			//	//����˼·�����I�ڵ��Ƿ�Ҷ�ӽڵ㣬��������ڵ�Ҳ�Ƿ�Ҷ�ӽڵ㣬
			//	//��ô������ȫ�ų����е÷Ǹ��ڵ㣬��Ϊi����ڵ����ڵ�Ҳ����ΪT.
			//	head[Tree[i].left]=false;
			//	head[Tree[i].right]=false;
			//}
		}
		for(int i=1;i<=1000;i++)	//������ѯ���ڵ�
			if(head[i]){
				PrintPreTree(i);
				break;
			}
		cout<<endl;	
	}
	return 0;
}




/*
3
4 C 1 3
1 A 0 0
3 B 0 0
1
1000 Z 0 0
3
1 Q 0 2
2 W 3 0
3 Q 0 0


CAB
Z
QWQ


3
4 C 1 3
1 A 0 0
3 B 0 0

3
1 Q 0 2
2 W 3 0
3 Q 0 0

6
3 B 0 0
2 F 5 0
4 C 1 3
1 A 0 0
5 G 0 0
6 D 4 2
DCABFG
*/

//�ö�ջ�������
//stack<Node> PreTree;
//PreTree.push(Tree[root]);
//while(!PreTree.empty())
//{
//	Node temp=PreTree.top();
//	PreTree.pop();
//	cout<<temp.val;
//	if(temp.right!=0)//����������ö�ջ����ѹ��������
//		PreTree.push(Tree[temp.right]);	
//	if(temp.left!=0)
//		PreTree.push(Tree[temp.left]);		
//}