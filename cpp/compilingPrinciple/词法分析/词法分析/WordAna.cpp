#include<iostream>
#include<string>
#include <stdio.h> 
#include <conio.h> 
#include<stdlib.h>
using namespace std;

int ReKeyId(string str) //���عؼ��ֵı���
{
	if(str=="do")		return 1;
	if(str=="while")	return 2; 
	if(str=="for")		return 3; 
	if(str=="if")		return 4; 
	if(str=="else")		return 5;
	if(str=="then")		return 6;
	if(str=="switch")	return 7;
	if(str=="case")		return 8;
	if(str=="int")		return 9;
	if(str=="char")		return 10;
	if(str=="NULL")		return 11;
	return 0; 
} 

int WordAna(FILE *fp1,FILE *fp2) //�ʷ������ӳ���
{
	char ch;
	int KeyId;
	string str;
	while(1){ 
		do{ //���˿ո�
			ch = fgetc(fp1); 
		}while( isspace(ch) &&(ch != EOF)); 
		str.clear();
		if(ch == EOF) return 0; 
		if (isalpha(ch)) { //�ж��Ƿ�����ĸ
			while (isalpha(ch) || isalnum(ch)) { 
				str=str+ch;
				ch = fgetc(fp1); 
			} 
			fseek(fp1,-1,1); 
			KeyId=ReKeyId(str); 
			if (KeyId == 0) { //������ǹؼ��֣�ֱ�Ӵ�ӡ������
				printf("<$Var,%s>\n",str.c_str()); 
				fputs("<$Var,",fp2); fputs(str.c_str(),fp2); fputs(">\n",fp2); 
			} 
			else { //����ǹؼ���
				printf("<%d,Key>\n",KeyId); 
				char tmp=KeyId+'0';
				fputs("<",fp2); fputc(tmp,fp2); fputs(",#>\n",fp2); 
			} 
		} 
		else if (isalnum(ch)) { //�ж��Ƿ�������
			while (isalnum(ch)) { 
				str=str+ch;
				ch = fgetc(fp1); 
			}  
			fseek(fp1,-1,1); 
			printf("<$INT,%s>\n",str.c_str()); 
			fputs("<$INT,",fp2); 	fputs(str.c_str(),fp2); fputs(">\n",fp2); 
		} 
		else if (ch == '=') { 
			printf("<$=,#>\n"); 
			fputs("<$=,#>\n",fp2); 
		} 
		else if (ch == '<') { 
			printf("<$<,#>\n"); 
			fputs("<$<,#>\n",fp2); 
		} 
		else if (ch == '>') { 
			printf("<$>,#>\n"); 
			fputs("<$,#>\n",fp2); 
		} 
		else if (ch == '+') { 
			printf("<$+,#>\n"); 
			fputs("<$+,#>\n",fp2); 
		} 
		else if (ch == '-') { 
			printf("<$-,#>\n"); 
			fputs("<$-,#>\n",fp2); 
		} 
		else if (ch == '/') { 
			ch = fgetc(fp1); //���˶�ע��
			if (ch == '*') {
				do
				{ 
					ch = fgetc(fp1);
					if(ch=='*'){
						char ch1=fgetc(fp1);
						if(ch1=='/') break;
					}
				}while(ch!=EOF);  
			} 
			else if(ch =='/'){//������ע��
				do
				{ 
					ch = fgetc(fp1);	
				}while(ch!='\n' && ch!=EOF ); 
			}
			else { 
				fseek(fp1,-1,1); 
				printf("<$/,#>\n"); 
				fputs("<$/,#>\n",fp2); ; 
			} 	
		}
		else if (ch == '*') { 
			printf("<$*,#>\n"); 
			fputs("<$*,#>\n",fp2); 
		} 
		else if (ch == ';') {//�ֺ� 
			printf("<$;,#>\n"); 
			fputs("<$;,#>\n",fp2); 
		} 
		else if (ch == '(') { 
			printf("<$(,#>\n"); 
			fputs("<$(,#>\n",fp2); 
		} 
		else if (ch == ')') { 
			printf("<$),#>\n"); 
			fputs("<$),#>\n",fp2); 
		} 
		else if (ch == '{') { 
			printf("<${,#>\n"); 
			fputs("<${,#>\n",fp2); 
		} 
		else if (ch == '}') { 
			printf("<$},#>\n"); 
			fputs("<$},#>\n",fp2); 
		} 
		else { 
			printf("<$ERROR,#>\n"); 
			fputs("<$ERROR,#>\n",fp2); 
		}
	}//while
} 

void main(void) 
{
	FILE *f1,*f2; 
	if((f1=fopen("input.txt","rt"))==NULL) //���ļ�ʧ��
	{ 
		printf("�ļ���ʧ�ܣ���������˳���\n"); 
		getch(); 
		exit(1); 
	} 
	if((f2=fopen("out.txt","wt+"))==NULL) //���ļ�ʧ��
	{ 
		printf("��������ļ�ʧ�ܣ��������������\n"); 
		getch();
		exit(1); 
	} 
	WordAna(f1,f2); //�ʷ�����
	fclose(f1); //�ر��ļ�
	fclose(f2); 
} 




