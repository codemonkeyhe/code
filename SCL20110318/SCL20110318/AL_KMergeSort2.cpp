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

const unsigned int dataNum=10000000; //未排序文件中数据个数
const unsigned int divideNum=1000000;//分割成临时文件中数据个数
const unsigned int tempfileNum=dataNum/divideNum+(int)(dataNum%divideNum!=0); //所需临时文件个数
const unsigned int K =tempfileNum; //引用别名，归并数

//为文件fname创建num个初始化数据
//fname:文件名
//num：创建初始数据的个数
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

//分割文件
//每个临时文件包含divideNum个数据，最后一个临时文件包含dataNum%divideNum个数据
void DivideFile()
{
	int* data=new int[divideNum];
	FILE* infile=fopen(fileIn,"rt");
	char *tempfile = new char[256];  
	int index=1;    //临时文件下标
	while(true){
		int i=0;
		while(!feof(infile) && i<divideNum )
		{
			int res=fscanf(infile,"%d",&data[i]);
			if(res!=NULL && res!=EOF)
				i++;
		}
		if(i>0){   //从文件中读取的整数个数
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

//普通多路归并排序，
//tempfileNum为已经分割好的文件数，即待归并系数K
//临时数据文件名默认为TempDataX.txt,文件中不能出现其他非法字符，否则死循环
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
		if( fscanf(infile[i],"%d",&curData[i])==EOF )//不允许出现非法字符，否则死循环
			curData[i]=ENDFILE;
	}
	FILE* outfile=fopen(fileOut,"wt");
	while(true){
		int min=MAXV;
		int loc=-1;
		//寻找最小值
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


int ls[K];//非叶节点，记录败者值的下标
int leaf[K+1];//叶子节点，存储值

//沿从叶子节点leaf[s]到根节点ls[0]的路径调整败者树
void Adjust(int s)
{
	int t=(s+K)/2;
	while(t>0){
		if(leaf[s]>leaf[ls[t]]){//如果子节点大于父节点，即子节点是失败者，则父节点该记录败者的下标(子节点的下标)，
			int tmp=ls[t];
			ls[t]=s;
			s=tmp; //并且把胜者下标(父节点下标)暂存在S中，继续与父节点的父节点PK
		}
		t=t/2;//继续求其父结点在ls中的坐标
	}
	ls[0]=s;//ls[0]存储从叶节点s到根节点一路PK上去的最终的胜者，也就是整条PK路劲上的最小值
}

void CreateLoserTree()
{
	leaf[K]=MINV; //额外的存储一个最小值
	int i;
	for(i=0;i<K;++i)//先让所有的非叶结点存储最小值的下标，这样PK时枝干节点始终未胜者，叶节点为败者
		ls[i]=K; //因此依次从叶节点开始调整即可得到初始化的败者树
	for(i=K-1;i>=0;--i)//依次从b[k-1],b[k-2]...b[0]出发调整败者树
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

	for(int i=0;i<tempfileNum;++i){ //初始读取
		//if(feof(infile[i]) || fscanf(infile[i],"%d",&curData[i])==NULL)
		if( fscanf(infile[i],"%d",&leaf[i])==EOF )//不允许出现非法字符，否则死循环
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
	//MergeSort(); //普通归并排序，耗时36秒
	MergeSortWithLoserTree(); //败者树归并排序，耗时35秒
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