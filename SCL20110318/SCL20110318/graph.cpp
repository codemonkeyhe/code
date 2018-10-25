#include<iostream>
#include<memory.h>
#include<stack>
#include<queue>
using namespace std;


//ͼ����󶥵�����Ҫ���ڵ��ھ���ͼ�Ķ�����n;
const int MaxVertexNum=100;
//ͼ����������Ҫ���ڵ��ھ���ͼ�ı���e;
const int MaxEdgeNum=10000;
//����vexlistΪ�洢������Ϣ������
//VertexTypeΪ�û�����ȷ���Ķ���ֵ���ͣ�����char����string��
//��ʵ�����൱�ڶ�����Ϣ�;��󶥵㽨��һһӳ��Ĺ�ϵ,����������ʱ������Ҫ��������ӳ��ת��
//typedef VertexType vexlist[MaxVertexNum];
typedef int vexlist[MaxVertexNum];
//����adjmatrixΪ�ڽӾ���
typedef int adjmatrix[MaxVertexNum][MaxVertexNum];
const int MaxValue=100000;//���Ȩֵ
bool visited[MaxVertexNum];//������ʱ�����飬��ʼ��Ϊfalse



//��������(����)ͼ���ڽӾ���
//�β��б�������Ϣ���飬�ڽӾ���,������������
//������Ҫ�洢������Ϣ�����ɾȥ����1
//��Щ�������n,e�����ṩ����ֽ�˳���
void CreGraMatrix(vexlist GV,adjmatrix GA,int n,int e)
{
	int i,j,k,w;
	//����������Ϣ���飬
	for(i=0;i<n;i++)
		cin>>GV[i];
	//��ʼ���ڽӾ���
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)GA[i][j]=0;  //�Լ����Լ�Ϊ0
			else GA[i][j]=MaxValue;//���ɴ�ΪMaxValue
		}
	}
	//��������ͼ�ڽӾ���,�������˵�i,j�����ϵ�Ȩw
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		GA[i][j]=w;
		GA[j][i]=w;//**��ȥ���˾仰���Ϊ��������ͼ�ڽӾ���
	}
}


//�ӳ�ʼ�ڵ�i������������������ڽӾ��󹹳ɵ�ͼ
//***��������ͨͼ�ı���
void dfsGraMat(adjmatrix GA,int i,int n)
{
	cout<<i<<' ';//���ʶ���Viʱ����ö������ţ��ڴ˿������Ӧ������
	visited[i]=true;//��ǽڵ�Vi�ѱ����ʹ�
	for(int j=0;j<n;j++){//���α���Vi��ÿ���ڽӵ�
		if(GA[i][j]!=0 && GA[i][j]!=MaxValue && !visited[j])
			dfsGraMat(GA,j,n);
	}
}

//�ӳ�ʼ�ڵ�i������������������ڽӾ��󹹳ɵ�ͼ
//�ö�ջʵ�ֵķǵݹ��㷨
//***��������ͨͼ�ı���
void dfsGraMat1(adjmatrix GA,int i,int n)
{
	stack<int> S;
	S.push(i);//��ʼ�ڵ�Vi��ջ
	while(!S.empty())//ջ�ǿ�ʱ����ѭ������
	{
		int k=S.top();
		S.pop();
		if(!visited[k])//��Vkû�����ʹ�
		{
			cout<<k<<' ';//����Vk
			visited[k]=true;//���Vk�ѱ����ʹ�
			for(int j=0;j<n;j++){//�Ѻ�Vk�ڽӵ���δ�����ʹ��Ķ���ѹջ
			if(GA[k][j]!=0 && GA[k][j]!=MaxValue && !visited[j])
				S.push(j);
			}
		}
		//�����ʹ������ѭ��	
	}
}


//�ӳ�ʼ�ڵ�i������������������ڽӾ��󹹳ɵ�ͼ
//�ö���ʵ�ֵķǵݹ��㷨
//***��������ͨͼ�ı���
void bfsGraMat(adjmatrix GA,int i,int n)
{
	queue<int> S;
	cout<<i<<' ';
	visited[i]=true;
	S.push(i);
	while(!S.empty())
	{
		int k=S.front();
		S.pop();
		for(int j=0;j<n;j++){//�Ѻ�Vk�ڽӵ���δ�����ʹ��Ķ����ȷ��ʣ������
			if(GA[k][j]!=0 && GA[k][j]!=MaxValue && !visited[j]){	
				cout<<j<<' ';
				visited[j]=true;
				S.push(j);		
			}
		}
	}
}

//****************************************************************
//ͼ���ڽӱ�
struct edgenode
{
	int adjvex;   //�ڽӵ��򣬴�����ڽӵĽڵ�
	int weight;	  //Ȩֵ��
	edgenode *next; //��һ����ָ��
};
//����adjlistΪ�洢n����ͷָ�����������
typedef edgenode* adjlist[MaxVertexNum];


//��������(����)ͼ���ڽӱ�
//�β��б�������Ϣ���飬�ڽӱ�,������������
//������Ҫ�洢������Ϣ�����ɾȥ����1
//��Щ�������n,e�����ṩ����ֽ�˳���
void CreGralist(vexlist GV,adjlist GL,int n,int e)
{
	int i,j,k,w;
	//����������Ϣ���飬
	for(i=0;i<n;i++)
		cin>>GV[i];
	//��ʼ���ڽӱ�
	for(i=0;i<n;i++) GL[i]=NULL;
	//��������ͼ�ڽӱ�,�������˵�i,j�����ϵ�Ȩw
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		edgenode* p=new edgenode;
		p->adjvex=j;
		p->next=GL[i];//���½ڵ���뵽Vi�ڽӱ�ı�ͷ
		GL[i]=p;
		//���������������Ϊ��������ͼ�ڽӱ�
		/*p->adjvex=i;
		p->next=GL[j];
		GL[j]=p;*/
		//delete p;
	}
}


//�ӳ�ʼ�ڵ�i������������������ڽӱ��ɵ�ͼ
//***��������ͨͼ�ı���
void dfsGraList(adjlist GL,int i,int n)
{
	cout<<i<<' ';//���ʶ���Viʱ����ö������ţ��ڴ˿������Ӧ������
	visited[i]=true;//��ǽڵ�Vi�ѱ����ʹ�
	edgenode* p=GL[i];
	while(p!=NULL){//���α���Vi��ÿ���ڽӵ�		
		int j=p->adjvex;
		if(!visited[j])
			dfsGraList(GL,j,n); 
		p=p->next;
	}
}

//�ӳ�ʼ�ڵ�i������������������ڽӱ��ɵ�ͼ
//�ö�ջʵ�ֵķǵݹ��㷨
//***��������ͨͼ�ı���
void dfsGraList1(adjlist GL,int i,int n)
{
	stack<int> S;
	S.push(i);//��ʼ�ڵ�Vi��ջ
	while(!S.empty())//ջ�ǿ�ʱ����ѭ������
	{
		int k=S.top();
		S.pop();
		if(!visited[k])//��Vkû�����ʹ�
		{
			cout<<k<<' ';//����Vk
			visited[k]=true;//���Vk�ѱ����ʹ�
			edgenode * p=GL[k];
			while(p!=NULL){
				int j=p->adjvex;
				if(!visited[j])
					S.push(j);
				p=p->next;
			}
		}
		//�����ʹ������ѭ��	
	}
}


//�ӳ�ʼ�ڵ�i������������������ڽӱ��ɵ�ͼ
//�ö���ʵ�ֵķǵݹ��㷨
//***��������ͨͼ�ı���
void bfsGraList(adjlist GL,int i,int n)
{
	queue<int> S;
	cout<<i<<' ';
	visited[i]=true;
	S.push(i);
	while(!S.empty())
	{
		int k=S.front();
		S.pop();
		edgenode *p=GL[k];
		while(p!=NULL)//�Ѻ�Vk�ڽӵ���δ�����ʹ��Ķ����ȷ��ʣ������
		{
			int j=p->adjvex;
			if(!visited[j]){
				cout<<j<<' ';
				visited[j]=true;
				S.push(j);
			}
			p=p->next;
		}
	}
}


//����ͨͼ���ڽ������
void dfsGraLisUncne(adjlist GL,int n)
{
	for(int i=0;i<n;i++){	
		if(!visited[i])
			bfsGraList(GL,i,n);
	}
}


//����ͨͼ���ڽ������
void dfsGraMatUncne(adjmatrix GA,int n)
{
	for(int i=0;i<n;i++){
		if(!visited[i])
			//�˴���������κα����㷨���ڴ���dfsGraMatΪ��
		 //dfsGraMat(GA,i,n);
		 bfsGraMat(GA,i,n);
	}
}

//�������ݣ�����ͼ
const int NUM_VERTICE=9;
int graph[NUM_VERTICE][NUM_VERTICE]=
{
	{0, 1, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 1, 1},
	{0, 0, 0, 0, 0, 1, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 1, 1, 0}
};


const int NUMV=6;
int minsptre[NUMV][NUMV]=
{
	{0,			15,		7,		4,		12,		MaxValue},
	{15,		0,		MaxValue,MaxValue,10,	MaxValue},
	{7,			MaxValue, 0,	8,		5,			25},
	{4,			MaxValue, 8,	0,		MaxValue,	16},
	{12,		10,		5,		MaxValue,0,		MaxValue},
	{MaxValue,	MaxValue,25,	16,		MaxValue,	0},
};



//-------------------------------------------------------------

struct edgeset  //�洢��С�������Ľṹ��
{
	int formvex;
	int endvex;
	int weight;
};
//struct mint edgeset[100];


//����Prim�㷨�Ӷ���Va�������ͼ����С������
//ͼ���ڽӾ����ʾ����С�������ı߼���������CT��
void Prim(adjmatrix GA,edgeset CT[],int a,int n)
{
	int i,j,k,min,t,m,w;
	//��CT����ֵ����Ӧ��0�ε���̱ߺϼ�
	for(i=0;i<n;i++){
		k=i;
		if(i>a) k--;
		CT[k].formvex=a;
		CT[k].endvex=i;
		CT[k].weight=GA[a][i];
		
	}
	//����n-1��ѭ����ÿ�������С�������еĵ�K����
	for(k=1;k<n;k++){
		min=MaxValue;//��CT[k-1]~CT[n-2]�У�����̱ߺϼ���������̱�CT[m]
		m=k-1;
		for(j=k-1;j<n-1;j++){
			if(CT[j].weight<min)
			{
				min=CT[j].weight;
				m=j;
			}
		}
		edgeset temp=CT[k-1]; //����̱߶Ե�����K-1�±�λ��
		CT[k-1]=CT[m];
		CT[m]=temp;
		j=CT[k-1].endvex;//���¼��뵽��С������T�еĶ�����Ÿ���j
		for(i=k;i<n-1;i++){//�޸���̱߼��ϣ�ʹÿ�����㶼ά��һ����̱�
			t=CT[i].endvex;
			w=GA[j][t];
			if(w<CT[i].weight){
				CT[i].weight=w;
				CT[i].formvex=j;
			}
		}
	}
}


//---------------------------------------------------------------
//���ڽӱ�GL��ʾ�ľ���n�����������ͼ������������
void Toposort(adjlist GL,int n)
{
	int i,j,k,top,m=0; //m����ͳ���������еĶ�����
	edgenode *p;
	int *d=new int [n]; //d���ÿ����������
	for(i=0;i<n;i++) d[i]=0;//��ʼ������
	for(i=0;i<n;i++){//���ڽӱ��ÿ������ĳ���ͳ�Ƶ��������d��
		p=GL[i];
		while(p!=NULL){
			j=p->adjvex;
			d[j]++;
			p=p->next;
		}
	}
	top=-1;//ջ��ֵ����Ϊ-1��topΪջ��ָ��
	for(i=0;i<n;i++){//�������Ϊ0����ջ
		if(d[i]==0){
			d[i]=top;
			top=i;
		}
	}
	while(top!=-1)//ÿѭ��һ��ɾ��һ�����Ϊ0�Ķ����Լ���Ӧ�����г���
	{
		j=top;   //jΪ��ǰ���Ϊ0�Ľڵ�
		top=d[top];//ջ��ָ�����ƣ����ѵ�ǰ���Ϊ0�Ľڵ��ջ
		cout<<j<<' ';  //��Ϊ����Vj��Ӧ���������d���±꣨0~N-1��,�����ٴμ�һ�õ�ԭ�����±�
		m++;//�������ж��������1
		p=GL[j];//pָ��ǰ���Ϊ0�Ľڵ�Vj���ڵ��ڽӱ�ı�ͷλ��
		while(p!=NULL){//�Ѻ�Vj���ڽӵ����ж�������ȫ����һ��������ɾ������Ӧ�����
			k=p->adjvex;
			d[k]--;
			if(d[k]==0) {//������Ϊ0����Ѹýڵ���뵽��ջ��ջ��
				d[k]=top;top=k;
			}
			p=p->next;
		}
	}
	cout<<endl;
	if(m<n) cout<<"���ڻ�·"<<endl;
	delete []d;

}

int main(void)
{
	//�ڽ���ͼ��������
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMat(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMat1(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//bfsGraMat(graph,3,9);
	//memset(visited,false,sizeof(bool)*MaxVertexNum);
	//dfsGraMatUncne(graph,9);

	//�ڽӱ�ͼ��������
	//adjlist GL;
	//int i,j,k,w;
	//int n,e;
	//cin>>n>>e;//���붥�����Լ�����
	//��ʼ���ڽӱ�
	//for(i=0;i<n;i++) GL[i]=NULL;
	//��������ͼ�ڽӱ�,�������˵�i,j�����ϵ�Ȩw
	//for(k=1;k<=e;k++)
	//{
	//	cin>>i>>j>>w;
	//	edgenode* p=new edgenode;
	//	p->adjvex=j;
	//	p->next=GL[i];//���½ڵ���뵽Vi�ڽӱ�ı�ͷ
	//	GL[i]=p;
	//}
	//dfsGraList(GL,3,9);
	//dfsGraList1(GL,3,9);
	//bfsGraList(GL,1,9);
	//dfsGraLisUncne( GL,9);

	//��С����������
	//edgeset CT[6];
	//Prim(minsptre,CT,1,6);
	//cin.get();

	//�ڽӱ����˲���
	adjlist GL;
	int i,j,k,w;
	int n,e;
	cin>>n>>e;//���붥�����Լ�����
	//��ʼ���ڽӱ�
	for(i=0;i<n;i++) GL[i]=NULL;
	//��������ͼ�ڽӱ�,�������˵�i,j�����ϵ�Ȩw
	for(k=1;k<=e;k++)
	{
		cin>>i>>j>>w;
		edgenode* p=new edgenode;
		p->adjvex=j;
		p->next=GL[i];//���½ڵ���뵽Vi�ڽӱ�ı�ͷ
		GL[i]=p;
	}
	Toposort( GL, n);
	return 0;
}
/*
9
18
0 1 1
1 0 1
1 2 1
2 1 1
3 5 1
4 5 1
5 4 1
4 8 1
8 4 1
5 6 1
6 5 1
6 7 1
7 6 1
7 8 1
8 7 1
7 5 1
6 8 1
8 6 1


12
15
0 5 1
1 3 1
2 3 1
2 4 1
2 5 1
3 4 1
4 6 1
4 9 1
5 6 1
5 8 1
5 10 1
6 7 1
6 8 1
9 10 1
9 11 1


12
14
0 5 1
1 3 1
2 3 1
2 4 1
2 5 1
3 4 1
4 6 1
4 9 1
5 6 1
5 8 1
5 10 1
6 7 1
6 8 1
9 10 1

*/
 