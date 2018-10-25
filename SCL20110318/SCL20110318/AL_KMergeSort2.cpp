#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;

#define ENDFILE -1
#define MAXV 10000000
#define MINV -1
const char* fileIn="UnsortData.txt";
const char* fileOut="SortData.txt";

const unsigned int dataNum=10000000; //δ�����ļ������ݸ���
const unsigned int divideNum=1000000;//�ָ����ʱ�ļ������ݸ���
const unsigned int tempfileNum=dataNum/divideNum+(int)(dataNum%divideNum!=0); //������ʱ�ļ�����
const unsigned int K =tempfileNum; //���ñ������鲢��

//Ϊ�ļ�fname����num����ʼ������
//fname:�ļ���
//num��������ʼ���ݵĸ���
void InitData(const char* fname,const unsigned int num)
{
	srand((unsigned int)time(0));
	ofstream outfile(fname,ios::out);
	for(unsigned int i=0;i<num;++i)
		outfile<<rand()<<' ';
	outfile.close();
}

static int cmpfcn (const void *a, const void *b)  
{  
    return *(int*)a - *(int*)b;  
}  

//�ָ��ļ�
//ÿ����ʱ�ļ�����divideNum�����ݣ����һ����ʱ�ļ�����dataNum%divideNum������
void DivideFile()
{
	int* data=new int[divideNum];
	FILE* infile=fopen(fileIn,"rt");
	char *tempfile = new char[256];  
	int index=1;    //��ʱ�ļ��±�
	while(true){
		int i=0;
		while(!feof(infile) && i<divideNum )
		{
			int res=fscanf(infile,"%d",&data[i]);
			if(res!=NULL && res!=EOF)
				i++;
		}
		if(i>0){   //���ļ��ж�ȡ����������
			qsort(data,i,sizeof(int),cmpfcn);
			sprintf(tempfile,"TempData%d.txt",index++);  
			printf("read: %d intergers and create %s\n",i,tempfile);
			FILE* outfile=fopen(tempfile,"w");
			for(int j=0;j<i;++j){
				fprintf(outfile,"%d ",data[j]);
			}
			fclose(outfile);
		}else 
			break;
	}
	fclose(infile);
	delete []tempfile;
}

//��ͨ��·�鲢����
//tempfileNumΪ�Ѿ��ָ�õ��ļ����������鲢ϵ��K
//��ʱ�����ļ���Ĭ��ΪTempDataX.txt,�ļ��в��ܳ��������Ƿ��ַ���������ѭ��
void MergeSort()
{
	int* curData=new int[tempfileNum];
	char *tempfile = new char[256];  
	FILE** infile=new FILE*[tempfileNum];
	for(int i=0;i<tempfileNum;++i){
		sprintf(tempfile,"TempData%d.txt",i+1);  
		infile[i]=fopen(tempfile,"rt");
	}

	for(int i=0;i<tempfileNum;++i){
		//if(feof(infile[i]) || fscanf(infile[i],"%d",&curData[i])==NULL)
		if( fscanf(infile[i],"%d",&curData[i])==EOF )//��������ַǷ��ַ���������ѭ��
			curData[i]=ENDFILE;
	}
	FILE* outfile=fopen(fileOut,"wt");
	while(true){
		int min=MAXV;
		int loc=-1;
		//Ѱ����Сֵ
		for(int j=0;j<tempfileNum;++j){
			if(ENDFILE!=curData[j] && min>curData[j]){
				min=curData[j];
				loc=j;
			}
		}
		if(-1==loc) break;
		fprintf(outfile,"%d ",min);
		if( fscanf(infile[loc],"%d",&curData[loc])==EOF )
			curData[loc]=ENDFILE;
	}
	fclose(outfile);
	for(int i=0;i<tempfileNum;++i){
		fclose(infile[i]);
	}
	delete []tempfile;
	delete []infile;
	delete []curData;
}


int ls[K];//��Ҷ�ڵ㣬��¼����ֵ���±�
int leaf[K+1];//Ҷ�ӽڵ㣬�洢ֵ

//�ش�Ҷ�ӽڵ�leaf[s]�����ڵ�ls[0]��·������������
void Adjust(int s)
{
	int t=(s+K)/2;
	while(t>0){
		if(leaf[s]>leaf[ls[t]]){//����ӽڵ���ڸ��ڵ㣬���ӽڵ���ʧ���ߣ��򸸽ڵ�ü�¼���ߵ��±�(�ӽڵ���±�)��
			int tmp=ls[t];
			ls[t]=s;
			s=tmp; //���Ұ�ʤ���±�(���ڵ��±�)�ݴ���S�У������븸�ڵ�ĸ��ڵ�PK
		}
		t=t/2;//�������丸�����ls�е�����
	}
	ls[0]=s;//ls[0]�洢��Ҷ�ڵ�s�����ڵ�һ·PK��ȥ�����յ�ʤ�ߣ�Ҳ��������PK·���ϵ���Сֵ
}

void CreateLoserTree()
{
	leaf[K]=MINV; //����Ĵ洢һ����Сֵ
	int i;
	for(i=0;i<K;++i)//�������еķ�Ҷ���洢��Сֵ���±꣬����PKʱ֦�ɽڵ�ʼ��δʤ�ߣ�Ҷ�ڵ�Ϊ����
		ls[i]=K; //������δ�Ҷ�ڵ㿪ʼ�������ɵõ���ʼ���İ�����
	for(i=K-1;i>=0;--i)//���δ�b[k-1],b[k-2]...b[0]��������������
		Adjust(i);
}



void MergeSortWithLoserTree()
{
	
	char *tempfile = new char[256];  
	FILE** infile=new FILE*[tempfileNum];
	for(int i=0;i<tempfileNum;++i){
		sprintf(tempfile,"TempData%d.txt",i+1);  
		infile[i]=fopen(tempfile,"rt");
	}

	for(int i=0;i<tempfileNum;++i){ //��ʼ��ȡ
		//if(feof(infile[i]) || fscanf(infile[i],"%d",&curData[i])==NULL)
		if( fscanf(infile[i],"%d",&leaf[i])==EOF )//��������ַǷ��ַ���������ѭ��
			ls[i]=MAXV;
	}
	CreateLoserTree();

	FILE* outfile=fopen(fileOut,"wt");

	int loc;
	while(leaf[ls[0]]!=MAXV){
		loc=ls[0];
		fprintf(outfile,"%d ",leaf[loc]);
		if( fscanf(infile[loc],"%d",&leaf[loc])==EOF )
			leaf[loc]=MAXV;
		Adjust(loc);
	}

	fclose(outfile);
	for(int i=0;i<tempfileNum;++i){
		fclose(infile[i]);
	}
	delete []tempfile;
	delete []infile;
}


int main(){
	time_t start = time(NULL);  
	DivideFile();
	//MergeSort(); //��ͨ�鲢���򣬺�ʱ36��
	MergeSortWithLoserTree(); //�������鲢���򣬺�ʱ35��
	time_t end = time(NULL);  
    printf("Time Cost:%f\n",(end - start)*1000.0/CLOCKS_PER_SEC); 
	return 0;
}
 

	//char* fileIn="test.txt";
	//FILE* infile=fopen(fileIn,"rt");
	//int a=0;
	//int i=0;
	//while(!feof(infile) && i<10)
	//{
	//	int res=fscanf(infile,"%d",&a);
	//	if(res!=NULL && res!=EOF )
	//	{
	//		i++;
	//		cout<<a<<endl;
	//		cout<<"YES"<<endl;
	//	}else
	//		break;
	//}
	//fclose(infile);