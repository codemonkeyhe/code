#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

struct ProDa
{
	int id; //����ʽ���
	char head; //����ʽ�����Vn
	string tail;//����ʽ���ұ��ַ���
};

string Action[100][100]; //��û��ʼ��,Ĭ��Ϊ�մ���
int Goto[100][100];//��û��ʼ��

int main(void)
{
	int i,j,k;
	int ProN;//����ʽ��Ŀ
	int VtN;//�ս����Ŀ
	int VnN;//���ս����Ŀ
	int StaN;//״̬��
	string str;//��ɨ����ַ���
	int strl;
	ifstream read;
	read.open("input.txt");
	if(read.fail()){
		cout<<"�ļ���ʧ�ܣ������������"<<endl;
		return 1;
	}
	read>>ProN; 
	ProDa* produ=new ProDa[ProN+1];
	for(i=1;i<=ProN;i++){//�������ʽ
		read>>produ[i].id>>produ[i].head>>produ[i].tail;
	}
	read>>VtN>>StaN;
	string Vt;//�ս����
	char ch;
	for(i=0;i<VtN;i++){ //�����ս��	
		read>>ch;
		Vt=Vt+ch;
	}
	read.get();
	int index;
	for(i=0;i<StaN;i++){//����ACTION��
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
	for(i=0;i<VnN;i++){//������ս��
		read>>ch;
		Vn=Vn+ch;
	}
	while(!read.eof()){	//����GOTO��
		read>>i>>ch>>j;
		index=Vn.find(ch);
		Goto[i][index]=j;
	}
	read.close();

	vector<char> s;
	vector<char>::iterator it;
	while(1){
		cout<<"�����ַ���(exit����������!):"<<endl;
	cin>>str;
	if(str=="exit") return 0;
	strl=str.length();
	k=0;
	s.push_back('0');
	string num;
	string op;
		while(!s.empty()){
			ch=s.back();
			if(isalpha(ch) ){//ջ������ĸ������goto��������״̬
				index=Vn.find(ch);
				it=s.end();
				it--;
				it--;
				num.clear();
				while( !isalpha((*it)) && isalnum((*it)) ){//��ȡջ������
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
			else{//���ջ�������֣������ACTION��  
				num.clear();
				it=s.end();
				it--;
				while( !isalpha((*it)) && isalnum((*it)) ){//��ȡջ������
					num.insert(0,1,(*it));
					if(it!=s.begin()) it--;
					else break;
				}
				i=atoi(num.c_str());
				index=Vt.find(str[k]);
				if(index==string::npos) {cout<<"���봮�����ս������Χ��"<<endl;break;}
				op=Action[i][index];
				if(op[0]=='s'|| op[0]=='S' ){//�ƽ�
					s.push_back(str[k]);
					k++;
					if(k==(int)str.length()) {cout<<"���봮ĩβȱ���ս��"<<endl;break;}
					for(i=1;i<(int)op.size();i++)
						s.push_back(op[i]);
				}
				else if(op[0]=='r' || op[0]=='R'){//��Լ
					op.erase(0,1);//ȥ��ͷ���ַ�r
					index=atoi(op.c_str());//ת��������
					while( s.back()!= produ[index].tail[0]) {
						s.pop_back();
					}
					s.pop_back();
					s.push_back(produ[index].head);//�滻
				}
				else if(op=="Acc") {//ΪAcc��ʾ����
					cout<<"�ô���LR�������ɹ����գ�"<<endl;
					break;
				}
				else{//����
					cout<<"�ô��Ƿ����������գ�"<<endl;
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

