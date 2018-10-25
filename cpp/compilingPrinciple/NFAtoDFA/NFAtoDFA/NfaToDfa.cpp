#include <iostream> 
#include <fstream>	 
#include <string>
#include<vector>
#include<stack>
using   namespace   std; 

//��˵���ĵ�
void OutputFSAStatement()
{
	cout<<"------------------˵���ĵ�---------------------\n";
	cout<<"�ӵ�ǰ�ļ����е��ļ�nfa.txt����NFA!\n";
	cout<<"��һ��ΪNFA��Q��ÿ��״̬�ڵ�����ǵ����ַ�\n";
	cout<<"�ڶ���ΪNFA��Vt��ÿ��������ĸ�����ǵ����ַ�,���ܰ���@\n";
	cout<<"������ΪNFA��һ����ʼ״̬S�������ǵ����ַ�\n";
	cout<<"������ΪNFA����ֹ״̬��F��ÿ����ֹ̬�����ǵ����ַ�\n";
	cout<<"������һֱ��ĩβΪNFA�Ķ�ֵӳ��T,��@����Ϊ��ת��\n";
	cout<<"������֮�������ʽΪ<char OldNode,char edge,char NewNode>\n";
	cout<<"��nfa�ļ���#Ϊ������������ֻ��������һ��NFAʵ��!\n";
	cout<<"��Ϊ#����Ϊ�ļ���������@����Ϊ��ת�ƣ�����NFA��ʹ���������ַ�Ӧ��ע�⣡\n";
	system("pause"); 
	system("cls"); 
}


//FSA��ӳ�伯�����ݽṹ
struct FSATransSet
{
	string OldNode;    //�ɽڵ�
	char Edge;       //ת����
	string NewNode; //��̬����
};

//FSA�нڵ�����ݽṹ
struct FSANode
{
	string Nodes;
	bool OldState;
};


class FSA
{
public:
	 vector<FSANode> ExistState;   //��¼ת�������������ɵ�״̬�ڵ������
	int InputNFAfromFile();       //���ļ�����NFA
	int OutputFSAtoFile();        //��FSA������ļ�
	void OutputFSAtoScreen();     //��FSA�������Ļ
	string Closure(string str);  //����str�о���@ת��(��ת��)���Ե����״̬��
	string Moved(string str,char v);  //����str�о���������ĸv���Ե����״̬��    	
	int GetNewState();           //����ExistState���д����µ�״̬������
	bool InExistState(FSANode NodeTmp); //�жϽڵ�NodeTmp�Ƿ���ExistState���У����򷵻�true�����򷵻�false
	void SetDFA(string BegSt,char ch,string EndSt); //��t(BegSt,ch)={EndSt}��ӵ�Ҫ���ɵ�DFA��T��
	void   ArcStr (string &str);					//ð������ʹstr�е��ַ������ֵ�������
	void Deterministi(FSA &dfa);  //ȷ����������dfa��	
private:
	string Q;			//�ǿ�����״̬��
	string Vt;			//�ǿ�������ĸ��
	vector<FSATransSet>  T;  //��ֵӳ�伯T
	string q;				//��ʼ״̬
	string F;			//�ս�״̬��
};

//�����ļ���������ʹ֮��������FSATransSet�ṹ�����
ifstream& operator>>(ifstream& in,FSATransSet &node)   
{
	in>>node.OldNode>>node.Edge>>node.NewNode;
	return in;
}


//���ļ�����NFA
int FSA::InputNFAfromFile()
{
	char ch;
	FSATransSet  NodeTmp; 
	ifstream ReadFile;    
    ReadFile.open("nfa.txt"); 
	if (ReadFile.fail())
	{ 
		cerr<<"���ļ���������\n"<<endl;
		return 1;
	} 
	cout<<"�ӵ�ǰ�ļ����д�nfa.txt�ļ�"<<endl;
	while(!ReadFile.eof()){
		while(ch=ReadFile.get(),ch!='\n')
		{
			if(ch!=' ')
			Q=Q+ch;
		}
		while(ch=ReadFile.get(),ch!='\n')
		{
			if(ch!=' ')
			Vt=Vt+ch;
		}
		while(ch=ReadFile.get(),ch!='\n')
		{
			if(ch!=' ')
			q=ch;
		}
		while(ch=ReadFile.get(),ch!='\n')
		{
			if(ch!=' ')
			F=F+ch;
		}		
		while(ReadFile>>NodeTmp,NodeTmp.OldNode!="#")
		{
			T.push_back(NodeTmp);
		}	
	}
	ReadFile.close();
	return 0;
}

//��FSA�������Ļ
void FSA::OutputFSAtoScreen()
{
	vector<FSATransSet>::iterator pos;  
	int i=0;
	cout<<"Q={";
	for(i=0;i<(int)Q.length()-1;i++)
	{
		if(Q[i]!='[' &&  Q[i+1]!=']')
		{
			cout<<Q[i]<<",";
		}else 
		{
			cout<<Q[i];
		}
	
	}
	cout<<Q[i]<<"}"<<endl;
	cout<<"Vt={";
	for(i=0;i<(int)Vt.length()-1;i++)
	{
		cout<<Vt[i]<<",";
	}
	cout<<Vt[i]<<"}"<<endl;
	cout<<"S={"<<q<<"}"<<endl;
	cout<<"F={";
	for(i=0;i<(int)F.length()-1;i++)
	{
		if(F[i]!='[' &&  F[i+1]!=']')
		{
			cout<<F[i]<<",";
		}else 
		{
			cout<<F[i];
		}
	}
	cout<<F[i]<<"}"<<endl;
	cout<<"T={"<<endl;
	for(pos=T.begin();pos!=T.end();pos++)
	{
		cout<<"t("<<(*pos).OldNode<<","<<(*pos).Edge<<")="<<(*pos).NewNode<<endl; 
	}
	cout<<"}"<<endl;
	
}

//��FSA������ļ�
int FSA::OutputFSAtoFile()
{
	vector<FSATransSet>::iterator pos;  
	int i=0;
	ofstream WriteFile;
	WriteFile.open("dfa.txt");
	if(WriteFile.fail())
	{
		cerr<<"���ļ���������\n"<<endl;
		return 1;
	}
	WriteFile<<"Q={";
	for(i=0;i<(int)Q.length()-1;i++)
	{
		if(Q[i]!='[' &&  Q[i+1]!=']')
		{
			WriteFile<<Q[i]<<",";
		}else 
		{
			WriteFile<<Q[i];
		}
	}
	WriteFile<<Q[i]<<"}"<<endl;
	WriteFile<<"Vt={";
	for(i=0;i<(int)Vt.length()-1;i++)
	{
		WriteFile<<Vt[i]<<",";
	}
	WriteFile<<Vt[i]<<"}"<<endl;
	WriteFile<<"S={"<<q<<"}"<<endl;
	WriteFile<<"F={";
	for(i=0;i<(int)F.length()-1;i++)
	{
		if(F[i]!='[' &&  F[i+1]!=']')
		{
			WriteFile<<F[i]<<",";
		}else 
		{
			WriteFile<<F[i];
		}
	}
	WriteFile<<F[i]<<"}"<<endl;
	WriteFile<<"T={"<<endl;
	for(pos=T.begin();pos!=T.end();pos++)
	{
		WriteFile<<"t("<<(*pos).OldNode<<","<<(*pos).Edge<<")="<<(*pos).NewNode<<endl; 
	}
	WriteFile<<"}"<<endl;


	WriteFile.close();
	return 0;
}

//����str�о���@ת��(��ת��)���Ե����״̬��,���������� Closure�����㷨
string FSA::Closure(string str)
{
	string result;
	char ch1;
	char ch2;
	result=result+str;
	stack<char> sta;
	vector<FSATransSet>::iterator pos;
	int i;
	for(i=0;i<(int)str.length();i++)
	{
		sta.push(str[i]);
	}
	while(!sta.empty())
	{
		ch1=sta.top();
		sta.pop();
		for(pos=T.begin();pos!=T.end();pos++)
		{
			if((*pos).OldNode[0]==ch1 && (*pos).Edge=='@')
			{
				ch2=(*pos).NewNode[0];		
				if(string::npos==result.find(ch2))
				{
					result=result+ch2;
					sta.push(ch2);
				}		
			}
		}
	}
	return result;
} 

//����str�о���������ĸv���Ե����״̬��,���������� Closure�����㷨
string FSA::Moved(string str,char v)
{
	string result;
	char ch1;
	char ch2;
	stack<char> sta;
	vector<FSATransSet>::iterator pos;
	int i;
	for(i=0;i<(int)str.length();i++)
	{
		sta.push(str[i]);
	}
	while(!sta.empty())
	{
		ch1=sta.top();
		sta.pop();
		for(pos=T.begin();pos!=T.end();pos++)
		{
			if((*pos).OldNode[0]==ch1 && (*pos).Edge==v)
			{
			 	ch2=(*pos).NewNode[0];		
				if(string::npos==result.find(ch2))
				{
					result=result+ch2;
				}
			}
		}
	}
	return result;
} 

//����ExistState���д����µ�״̬������
int FSA::GetNewState()
{
   	int index;   
	for(index=0;index<(int)ExistState.size();++index) 
	{
		if(ExistState[index].OldState == false)   
			return index;   
	}
	return -1;
}

//�жϽڵ�NodeTmp�Ƿ���ExistState���У����򷵻�true�����򷵻�false
bool FSA::InExistState(FSANode NodeTmp)
{
	 int index;   
	for(index=0;index<(int)ExistState.size();++index) 
	{
		if(ExistState[index].Nodes== NodeTmp.Nodes)    // ExistState[index].OldState == NodeTmp.OldState
			return true;   
	}
	return false;
}

//��t(BegSt,ch)={EndSt}��ӵ�Ҫ���ɵ�DFA��T��
void FSA::SetDFA(string BegSt,char ch,string EndSt)
{
	if(!EndSt.empty())
	{
		FSATransSet Tmp;
		Tmp.OldNode=BegSt;
		Tmp.Edge=ch;
		Tmp.NewNode=EndSt;
		T.push_back(Tmp);
	}
}

void   FSA::ArcStr (string &str)//ð������ʹstr�е��ַ������ֵ�������
{
	int i=0,j=0;   
	for(i=0;i<(int)str.length()-1;i++)   
	{   
		for(j=0;j<(int)str.length()-1-i;j++)
		{
			char temp;
			if(str[j]>str[j+1])
			{
				temp=str[j];
				str[j]=str[j+1];
				str[j+1]=temp;
			}
		}
	} 
}


//ȷ����������dfa��,�������
void FSA::Deterministi(FSA &dfa)
{
	FSANode S;
 	S.Nodes=S.Nodes+q;
	S.Nodes=Closure(S.Nodes);
	ArcStr(S.Nodes);
	S.OldState=false;
	ExistState.push_back(S);  //��̬Closure(S.Nodes)��Ϊ��һ��δ��ǵĶ�����ӵ�ExistState����
	dfa.q=S.Nodes;
    int i,j;
	int index=-1;
	while(index=GetNewState(),index!=-1)  //���������е�����㷨
	{
		ExistState[index].OldState=true;		
		S=ExistState[index];
		string MovedStr;
		FSANode NewNodes;
		for(i=0;i<(int)Vt.length();i++)
		{
			MovedStr=Moved(S.Nodes,Vt[i]);
			NewNodes.Nodes=Closure(MovedStr);
			ArcStr(NewNodes.Nodes);
			NewNodes.OldState=false;
			if(!InExistState(NewNodes) && !NewNodes.Nodes.empty()){
				ExistState.push_back(NewNodes);
			}
			dfa.SetDFA(S.Nodes,Vt[i],NewNodes.Nodes);
		}
	}
	for(i=0;i<(int)ExistState.size();i++)   //����ȷ������dfa�е�״̬��Q
	{
		dfa.Q=dfa.Q+'['+ExistState[i].Nodes+']';
	}
	dfa.Vt=Vt;     //����ȷ������dfa�е�Vt
	bool FirstEnd=true;
	for(i=0;i<(int)ExistState.size();i++) //����ȷ������dfa�е���ֹ��Q
	{
		for(j=0;j<(int)F.length();j++){	
			if(	ExistState[i].Nodes.find(F[j]) != string::npos)
			{
				if(FirstEnd==true)
				{
					dfa.F=dfa.F+'['+ExistState[i].Nodes+']';
					FirstEnd=false;
				}
				else
				{
					if(dfa.F.find(ExistState[i].Nodes) == string::npos)
					{
						dfa.F=dfa.F+'['+ExistState[i].Nodes+']';
					}
				}
			}
		}
	}
}

void main()
{
	OutputFSAStatement(); //��ʾ˵���ĵ�
	FSA nfa;
	nfa.InputNFAfromFile();
	cout<<"-----------���ļ������NFA------------"<<endl;
	nfa.OutputFSAtoScreen();	
	FSA dfa;
	nfa.Deterministi(dfa);
	cout<<"-----------ȷ����ΪDFA------------"<<endl;
	dfa.OutputFSAtoScreen();
	cout<<"******����Ѿ��������ǰ�ļ������nfa.txt�ļ���******\n";
	dfa.OutputFSAtoFile();	
}