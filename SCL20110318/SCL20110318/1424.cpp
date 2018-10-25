#include<iostream>
#include<memory.h>

using namespace std;
//ͼ����󶥵�����Ҫ���ڵ��ھ���ͼ�Ķ�����n;
const int MaxVertexNum=10010;
//ͼ���ڽӱ�
struct edgenode
{
	int adjvex;   //�ڽӵ��򣬴�����ڽӵĽڵ�
	edgenode *next; //��һ����ָ��
};

//����adjlistΪ�洢n����ͷָ�����������
typedef edgenode* adjlist[MaxVertexNum];

//���ڽӱ�GL��ʾ�ľ���n�����������ͼ������������
int Toposort(adjlist GL,int n)
{
	int i,j,k,top,m=0; //m����ͳ���������еĶ�����
	int tol=0;
	int *wage=new int [n+1];
	for(i=1;i<=n;i++) wage[i]=100;
	edgenode *p;
	int *d=new int [n+1]; //d���ÿ����������
	for(i=0;i<=n;i++) d[i]=0;//��ʼ������
	for(i=0;i<=n;i++){//���ڽӱ��ÿ������ĳ���ͳ�Ƶ��������d��
		p=GL[i];
		while(p!=NULL){
			j=p->adjvex;
			d[j]++;
			p=p->next;
		}
	}
	top=-1;//ջ��ֵ����Ϊ-1��topΪջ��ָ��
	for(i=1;i<=n;i++){//�������Ϊ0����ջ
		if(d[i]==0){
			d[i]=top;
			top=i;
		}
	}
	while(top!=-1)//ÿѭ��һ��ɾ��һ�����Ϊ0�Ķ����Լ���Ӧ�����г���
	{
		j=top;   //jΪ��ǰ���Ϊ0�Ľڵ�
		top=d[top];//ջ��ָ�����ƣ����ѵ�ǰ���Ϊ0�Ľڵ��ջ
		//cout<<j<<' ';  //��Ϊ����Vj��Ӧ���������d���±꣨0~N-1��,�����ٴμ�һ�õ�ԭ�����±�
		m++;//�������ж��������1
		p=GL[j];//pָ��ǰ���Ϊ0�Ľڵ�Vj���ڵ��ڽӱ�ı�ͷλ��	
		while(p!=NULL){//�Ѻ�Vj���ڽӵ����ж�������ȫ����һ��������ɾ������Ӧ�����
			k=p->adjvex;
			if(wage[k]<=wage[j]) wage[k]=wage[j]+1;
			d[k]--;
			if(d[k]==0) {//������Ϊ0����Ѹýڵ���뵽��ջ��ջ��
				d[k]=top;top=k;
			}
			p=p->next;
		}	
	}
	for(i=1;i<=n;i++)
	{
		tol=tol+wage[i];
	}
	if(m<n) return -1;
	else return tol;
	delete []d;

}

int main(void)
{


	adjlist GL;
	int i,j,k,w;
	int n,e;
	cin>>n>>e;//���붥�����Լ�����
	//��ʼ���ڽӱ�
	for(i=0;i<=n;i++) GL[i]=NULL;
	//��������ͼ�ڽӱ�,�������˵�i,j�����ϵ�Ȩw
	for(k=1;k<=e;k++)
	{
		cin>>i>>j;
		edgenode* p=new edgenode;
		p->adjvex=i;
		p->next=GL[j];//���½ڵ���뵽Vi�ڽӱ�ı�ͷ
		GL[j]=p;
	}
	w=Toposort( GL, n);
	if(w!=-1) cout<<w<<endl;
	else cout<<"Poor Xed"<<endl;
	return 0;
}

/*

һ��AC������ģ��
5 4
1 2
4 1
3 1
4 3

7 6
3 1
1 2
1 7
6 2
4 1
4 3

7 6
3 1
1 2
1 7
6 2
1 4
4 3

*/