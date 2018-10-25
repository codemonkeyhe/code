//Ƿȱ�Կ�ת�ƵĴ���
//#include   "stdafx.h"  

#include   <vector>   
#include   <string>   
#include   <queue>   
#include   <iostream>  
using   namespace   std;   
   
struct   Transform   
{   
	friend   class   FA;   
	char   state1;   
	char   letter;   
	char   state2;   
	bool   operator!=(char   ch);   
	//  friend   istream&   operator>>(istream& in,Transform& t);   
};   

struct   ChangeTable   
{   
	string   state;   
	int   flag;   
	vector<string>   changestate;   
}; 

bool   Transform::operator!=(char   ch)   
{   
	return   state1!=ch||letter!=ch||state2!=ch;   
}   

namespace   std   
{   
	istream &   operator>>(istream&   in,Transform&   t)   
	{   
		return   in>>t.state1>>t.letter>>t.state2;   
	}   
}

class   FA   
{   
	private:   
	vector<char>   state;									 //״̬��   
	vector<char>   table;									//������ĸ��   
	vector<Transform>   fun;								 //״̬��Ǩ����   
	char   q0;                                                     //��̬   
	vector<char>   Z;                                       //��̬��   
	string   GetChangeState(char   state1, char   table);   //��ӳ�伯fun������Ѱ��state1״̬����table�ַ�����������̬���ϲ�����
	void   RemoveRepeat(string   &str);					//����str�е��ظ�Ԫ��   
	void   ArcStr (string &str);					//ð������ʹstr�е��ַ������ֵ�������

	private:   
	vector<ChangeTable>   changetable;   
	bool   IsInChangeTable(string   str);         
	int   GetIndexofChangeTable();					//�ҳ���һ���� changetable������flagΪ0������   
	int   GetIndexofChangeTable(string   str);		 //�ҳ�str�ڱ��е�����   
	void   GetChangeTable();                                 
	void   OutputChangeTable();   

	public:   
	// FA(){}   
	void   Deterministic(FA   &dfa);   
	void   input();   
	void   output();  
	
};  

//����str�е��ظ�Ԫ��   
void   FA::RemoveRepeat(string   &str)   
{   
	string   mid;   
	string::size_type   idx;   
	string::iterator   pos;   
	for(pos=str.begin();pos!=str.end();++pos)   
	{   
		idx=mid.find(*pos);   
		if(idx==string::npos)               
		mid+=*pos;   
	}   
	str=mid;   
}


void   FA::ArcStr (string &str)//ð������ʹstr�е��ַ������ֵ�������
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


//�ж�str�Ƿ��� changetable�����У�����ڵĻ�����1�����򷵻�0
bool   FA::IsInChangeTable(string   str)   
{   
	vector<ChangeTable>::iterator   pos;   
	for(pos=changetable.begin();pos!=changetable.end();++pos)   
		if((*pos).state==str)   
			return   1;   
return   0;   
}   

//�ҳ���һ���� changetable������flagΪ0������
int   FA::GetIndexofChangeTable()                 
{   
	int index;   
	for(index=0;index<(int)changetable.size();++index) 
	{
		if(changetable[index].flag == 0)   
			return index;   
	}
	return -1;   
} 

//�ҳ���һ���� changetable������״̬state����str������
int   FA::GetIndexofChangeTable(string   str)   
{   
	int   index;   
	for(index=0;index<(int)changetable.size();++index)   
		if(changetable[index].state==str)   
			return   index;   
	return   -1;   
}  

//��ӳ�伯fun������Ѱ��state1״̬����table�ַ�����������̬���ϲ�����
string   FA::GetChangeState(char   state1,char   table)  
{   
	string   str;   
	vector<Transform>::iterator   pos;   
	for(pos=fun.begin();pos!=fun.end();++pos)   
	if( (*pos).state1==state1 && (*pos).letter==table )   
		str+=(*pos).state2;                             
	RemoveRepeat(str);   
	return   str;   
}  

  void   FA::input()   
  {   
        char   ch;   
        Transform   tran;   
        cout<<"input   the   set   of   state,ended   with   '#'"<<endl;   
        cin>>ch;   
        while(ch!='#')   
        {   
        state.push_back(ch);   
        cin>>ch;   
        }   
        cout<<"input   the   set   of   input's   table,ended   with   '#'"<<endl;   
        cin>>ch;   
        while(ch!='#')   
        {   
        table.push_back(ch);   
        cin>>ch;   
        }   
    
        cout<<"input   the   transform   of   function,formation   is   state1   letter   state1   "<<endl;   
        cout<<"ended   with   '#   #   #'"<<endl;   
        cin>>tran;     
        while(tran!='#')   
        {   
        fun.push_back(tran);   
        cin>>tran;   
        }   
        cout<<"input   the   state   of   Initlization   table"<<endl;   
        cin>>q0;   
          
        cout<<"input   the   set   of   termination,ended   with   '#'"<<endl;   
        cin>>ch;   
        while(ch!='#')   
        {   
        Z.push_back(ch);   
        cin>>ch;   
        }   
  }   




void   FA::GetChangeTable()   
{   
	ChangeTable   ct,midct;   
	string   str;   
	string   mid;   
	queue<string>   q;   
	vector<char>::iterator   pos;   
	string::iterator   p;   
	ct.state=string(1,q0);                         //�ӳ�ʼ״̬��ʼ   
	ct.flag=0;   
	changetable.push_back(ct);   
	int   index=GetIndexofChangeTable();    //�ҳ���һ���� changetable������flagΪ0������
	while(index!=-1)   
	{   
		changetable[index].flag=1;   
		str=changetable[index].state;                                   //����״̬   
		for(pos=table.begin();pos!=table.end();++pos)       //ÿ������״̬   
		{     
			mid.erase();       //���mid�е������ַ�                                                             
			for(p=str.begin();p!=str.end();++p)             //ÿ��״̬��ÿ���ַ�   
			{   
				mid+=GetChangeState(*p,*pos);   //��ӳ�伯fun������Ѱ��state1״̬����table�ַ�����������̬���ϲ�����
				RemoveRepeat(mid);   
				ArcStr(mid); 
			}   
			changetable[index].changestate.push_back(mid);   
			if(!mid.empty() && !IsInChangeTable(mid))  //�ж�str�Ƿ��� changetable�����У�����ڵĻ�����1�����򷵻�0        
			{   
				ct.state=mid;   
				ct.flag=0;   
				changetable.push_back(ct);   
			}   
		}   
		index=GetIndexofChangeTable();                         
	}   
}   

//����м�״̬ת���� changetable
void   FA::OutputChangeTable()   
{   
	vector<ChangeTable>::iterator   pos;   
	for(pos=changetable.begin();pos!=changetable.end();++pos)   
	{
		cout<<"{"<<(*pos).state<<"}     ";   
		for(int   i=0;i<(int)(*pos).changestate.size();i++)   
		cout<<"{"<<(*pos).changestate[i]<<"}     ";   
		cout<<endl;   
	}   
}   


void   FA::Deterministic(FA   &dfa)   
{   
	GetChangeTable();   
	//OutputChangeTable();                               //����м�״̬ת����   
	dfa.table=table;      //������ĸ���հ��dfa
	int   size=0;   
	while(size<(int)changetable.size())         //����changetable��С��dfa��״̬����������A,B,C,D....   
	{   
		dfa.state.push_back('A'+size);   
		size++;   
	}   
	dfa.q0='A';                                         //���ó�̬ΪA   
	Transform   tran;   
	vector<string>::iterator   pos;   
	vector<char>::iterator   p;   
	for(int   i=0;i<(int)changetable.size();++i)   //��������dfa������fun��ӳ�伯
	{   
		tran.state1='A'+i;   
		for(p=table.begin(),pos=changetable[i].changestate.begin();pos!=changetable[i].changestate.end();++pos,++p)   
		{   
			tran.letter=*p;   
			int   index=GetIndexofChangeTable(*pos);   
			tran.state2='A'+index;   
			if(index!=-1)   
			dfa.fun.push_back(tran);   
		}   
		//����������̬��   
		string   mid;   
		string   str=changetable[i].state;   
		for(p=Z.begin();p!=Z.end();++p)   
		{   
			mid.erase();   
			mid+=*p;   
		}   
		int   idx=str.find(mid);   
		if(idx!=string::npos)   
		dfa.Z.push_back('A'+i);   
	}   
}   
 
void   FA::output()   
  {   
  vector<char>::iterator   pos;   
  cout<<"M={Vn,Vt,F,q0,Z},����:"<<endl;   
  cout<<"Vn={";   
  for(pos=state.begin();pos!=state.end()-1;++pos)   
  cout<<*pos<<",";   
  cout<<*pos<<"}"<<endl;   
          cout<<"Vt={";   
  for(pos=table.begin();pos!=table.end()-1;++pos)   
  cout<<*pos<<",";   
  cout<<*pos<<"}"<<endl;   
    
  cout<<"F   is:"<<endl;   
          for(std::vector<Transform>::iterator   p=fun.begin();p!=fun.end();++p)   
  cout<<"f("<<(*p).state1<<","<<(*p).letter<<")="<<(*p).state2<<endl;   
    
  cout<<"q0="<<q0<<endl;   
    
  cout<<"Z={";   
  for(pos=Z.begin();pos!=Z.end()-1;++pos)   
  cout<<*pos<<",";   
  cout<<*pos<<"}"<<endl;   
    
  }   

/*
  int   main(int   argc,   char*   argv[])   
  {   
  FA   nfa,dfa;   
  nfa.input();   
  nfa.output();   
          nfa.Deterministic(dfa);   
  cout<<"ת����DFAΪ:"<<endl;   
  dfa.output();   
  return   0;   
  }  
*/



