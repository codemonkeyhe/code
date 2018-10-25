#include <iostream> 
#include <fstream>	 
#include <string>
#include<vector>
#include<stack>
using   namespace   std; 

//纯说明文档
void OutputFSAStatement()
{
	cout<<"------------------说明文档---------------------\n";
	cout<<"从当前文件夹中的文件nfa.txt输入NFA!\n";
	cout<<"第一行为NFA的Q，每个状态节点必须是单个字符\n";
	cout<<"第二行为NFA的Vt，每个输入字母必须是单个字符,不能包含@\n";
	cout<<"第三行为NFA的一个开始状态S，必须是单个字符\n";
	cout<<"第四行为NFA的终止状态集F，每个终止态必须是单个字符\n";
	cout<<"第五行一直到末尾为NFA的多值映射T,且@定义为空转移\n";
	cout<<"第五行之后输入格式为<char OldNode,char edge,char NewNode>\n";
	cout<<"该nfa文件以#为结束符，并且只允许输入一个NFA实例!\n";
	cout<<"因为#定义为文件结束符，@定义为空转移，所以NFA中使用这两个字符应该注意！\n";
	system("pause"); 
	system("cls"); 
}


//FSA的映射集的数据结构
struct FSATransSet
{
	string OldNode;    //旧节点
	char Edge;       //转换边
	string NewNode; //新态集合
};

//FSA中节点的数据结构
struct FSANode
{
	string Nodes;
	bool OldState;
};


class FSA
{
public:
	 vector<FSANode> ExistState;   //记录转换过程中新生成的状态节点的容器
	int InputNFAfromFile();       //从文件读入NFA
	int OutputFSAtoFile();        //把FSA输出到文件
	void OutputFSAtoScreen();     //把FSA输出到屏幕
	string Closure(string str);  //返回str中经过@转换(空转移)可以到达的状态集
	string Moved(string str,char v);  //返回str中经过输入字母v可以到达的状态集    	
	int GetNewState();           //返回ExistState表中存在新的状态的索引
	bool InExistState(FSANode NodeTmp); //判断节点NodeTmp是否在ExistState表中，是则返回true，否则返回false
	void SetDFA(string BegSt,char ch,string EndSt); //将t(BegSt,ch)={EndSt}添加到要生成的DFA的T中
	void   ArcStr (string &str);					//冒泡排序，使str中的字符按照字典序排序
	void Deterministi(FSA &dfa);  //确定化到对象dfa上	
private:
	string Q;			//非空有穷状态集
	string Vt;			//非空有穷字母集
	vector<FSATransSet>  T;  //多值映射集T
	string q;				//开始状态
	string F;			//终结状态集
};

//重载文件输入流，使之可以输入FSATransSet结构体对象
ifstream& operator>>(ifstream& in,FSATransSet &node)   
{
	in>>node.OldNode>>node.Edge>>node.NewNode;
	return in;
}


//从文件读入NFA
int FSA::InputNFAfromFile()
{
	char ch;
	FSATransSet  NodeTmp; 
	ifstream ReadFile;    
    ReadFile.open("nfa.txt"); 
	if (ReadFile.fail())
	{ 
		cerr<<"打开文件发生错误！\n"<<endl;
		return 1;
	} 
	cout<<"从当前文件夹中打开nfa.txt文件"<<endl;
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

//把FSA输出到屏幕
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

//把FSA输出到文件
int FSA::OutputFSAtoFile()
{
	vector<FSATransSet>::iterator pos;  
	int i=0;
	ofstream WriteFile;
	WriteFile.open("dfa.txt");
	if(WriteFile.fail())
	{
		cerr<<"打开文件发生错误！\n"<<endl;
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

//返回str中经过@转换(空转移)可以到达的状态集,采用龙书中 Closure构造算法
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

//返回str中经过输入字母v可以到达的状态集,采用龙书中 Closure构造算法
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

//返回ExistState表中存在新的状态的索引
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

//判断节点NodeTmp是否在ExistState表中，是则返回true，否则返回false
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

//将t(BegSt,ch)={EndSt}添加到要生成的DFA的T中
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

void   FSA::ArcStr (string &str)//冒泡排序，使str中的字符按照字典序排序
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


//确定化到对象dfa上,采用造表法
void FSA::Deterministi(FSA &dfa)
{
	FSANode S;
 	S.Nodes=S.Nodes+q;
	S.Nodes=Closure(S.Nodes);
	ArcStr(S.Nodes);
	S.OldState=false;
	ExistState.push_back(S);  //初态Closure(S.Nodes)作为第一个未标记的对象添加到ExistState表中
	dfa.q=S.Nodes;
    int i,j;
	int index=-1;
	while(index=GetNewState(),index!=-1)  //采用龙书中的造表算法
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
	for(i=0;i<(int)ExistState.size();i++)   //设置确定化后dfa中的状态集Q
	{
		dfa.Q=dfa.Q+'['+ExistState[i].Nodes+']';
	}
	dfa.Vt=Vt;     //设置确定化后dfa中的Vt
	bool FirstEnd=true;
	for(i=0;i<(int)ExistState.size();i++) //设置确定化后dfa中的终止集Q
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
	OutputFSAStatement(); //显示说明文档
	FSA nfa;
	nfa.InputNFAfromFile();
	cout<<"-----------从文件读入的NFA------------"<<endl;
	nfa.OutputFSAtoScreen();	
	FSA dfa;
	nfa.Deterministi(dfa);
	cout<<"-----------确定化为DFA------------"<<endl;
	dfa.OutputFSAtoScreen();
	cout<<"******结果已经输出到当前文件夹里的nfa.txt文件中******\n";
	dfa.OutputFSAtoFile();	
}