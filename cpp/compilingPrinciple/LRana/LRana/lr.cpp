#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

struct ProDa
{
	int id; //产生式编号
	char head; //产生式的左边Vn
	string tail;//产生式的右边字符串
};

string Action[100][100]; //还没初始化,默认为空串，
int Goto[100][100];//还没初始化

int main(void)
{
	int i,j,k;
	int ProN;//产生式数目
	int VtN;//终结符数目
	int VnN;//非终结符数目
	int StaN;//状态数
	string str;//待扫描的字符串
	int strl;
	ifstream read;
	read.open("input.txt");
	if(read.fail()){
		cout<<"文件打开失败！任意键结束！"<<endl;
		return 1;
	}
	read>>ProN; 
	ProDa* produ=new ProDa[ProN+1];
	for(i=1;i<=ProN;i++){//读入产生式
		read>>produ[i].id>>produ[i].head>>produ[i].tail;
	}
	read>>VtN>>StaN;
	string Vt;//终结符串
	char ch;
	for(i=0;i<VtN;i++){ //读入终结符	
		read>>ch;
		Vt=Vt+ch;
	}
	read.get();
	int index;
	for(i=0;i<StaN;i++){//读入ACTION表
		char ch1;
		string ch2;	
		while(read.get(ch),ch!='\n'){
			if(ch==' ')continue;
			read.seekg(-1,ios::cur);
			read>>ch1>>ch2;
			index=Vt.find(ch1);
			Action[i][index]=ch2;
		}
	}
	read>>VnN;
	string Vn;
	for(i=0;i<VnN;i++){//读入非终结符
		read>>ch;
		Vn=Vn+ch;
	}
	while(!read.eof()){	//读入GOTO表
		read>>i>>ch>>j;
		index=Vn.find(ch);
		Goto[i][index]=j;
	}
	read.close();

	vector<char> s;
	vector<char>::iterator it;
	while(1){
		cout<<"输入字符串(exit串结束测试!):"<<endl;
	cin>>str;
	if(str=="exit") return 0;
	strl=str.length();
	k=0;
	s.push_back('0');
	string num;
	string op;
		while(!s.empty()){
			ch=s.back();
			if(isalpha(ch) ){//栈顶是字母，访问goto表，查找新状态
				index=Vn.find(ch);
				it=s.end();
				it--;
				it--;
				num.clear();
				while( !isalpha((*it)) && isalnum((*it)) ){//提取栈顶数字
					num.insert(0,1,(*it));
					if(it!=s.begin()) it--;
					else break;
				}
				i=atoi(num.c_str());
				int tmp=Goto[i][index];
				char ctmp[10];
				_itoa_s(tmp,ctmp,10);
				for(i=0;i<(int)strlen(ctmp);i++)
					s.push_back(ctmp[i]);	
			}
			else{//如果栈顶是数字，则访问ACTION表  
				num.clear();
				it=s.end();
				it--;
				while( !isalpha((*it)) && isalnum((*it)) ){//提取栈顶数字
					num.insert(0,1,(*it));
					if(it!=s.begin()) it--;
					else break;
				}
				i=atoi(num.c_str());
				index=Vt.find(str[k]);
				if(index==string::npos) {cout<<"输入串超出终结符集范围！"<<endl;break;}
				op=Action[i][index];
				if(op[0]=='s'|| op[0]=='S' ){//移进
					s.push_back(str[k]);
					k++;
					if(k==(int)str.length()) {cout<<"输入串末尾缺乏终结符"<<endl;break;}
					for(i=1;i<(int)op.size();i++)
						s.push_back(op[i]);
				}
				else if(op[0]=='r' || op[0]=='R'){//规约
					op.erase(0,1);//去掉头部字符r
					index=atoi(op.c_str());//转换成数字
					while( s.back()!= produ[index].tail[0]) {
						s.pop_back();
					}
					s.pop_back();
					s.push_back(produ[index].head);//替换
				}
				else if(op=="Acc") {//为Acc表示接受
					cout<<"该串被LR分析器成功接收！"<<endl;
					break;
				}
				else{//出错
					cout<<"该串非法！不被接收！"<<endl;
					break;
				}
			}//if
		}//while
		cout<<endl;
		s.clear();
	}
	delete []produ;
	return 0;
}

