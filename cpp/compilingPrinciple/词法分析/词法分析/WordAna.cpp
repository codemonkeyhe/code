#include<iostream>
#include<string>
#include <stdio.h> 
#include <conio.h> 
#include<stdlib.h>
using namespace std;

int ReKeyId(string str) //返回关键字的编码
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

int WordAna(FILE *fp1,FILE *fp2) //词法分析子程序
{
	char ch;
	int KeyId;
	string str;
	while(1){ 
		do{ //过滤空格
			ch = fgetc(fp1); 
		}while( isspace(ch) &&(ch != EOF)); 
		str.clear();
		if(ch == EOF) return 0; 
		if (isalpha(ch)) { //判断是否是字母
			while (isalpha(ch) || isalnum(ch)) { 
				str=str+ch;
				ch = fgetc(fp1); 
			} 
			fseek(fp1,-1,1); 
			KeyId=ReKeyId(str); 
			if (KeyId == 0) { //如果不是关键字，直接打印变量名
				printf("<$Var,%s>\n",str.c_str()); 
				fputs("<$Var,",fp2); fputs(str.c_str(),fp2); fputs(">\n",fp2); 
			} 
			else { //如果是关键字
				printf("<%d,Key>\n",KeyId); 
				char tmp=KeyId+'0';
				fputs("<",fp2); fputc(tmp,fp2); fputs(",#>\n",fp2); 
			} 
		} 
		else if (isalnum(ch)) { //判断是否是数字
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
			ch = fgetc(fp1); //过滤段注释
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
			else if(ch =='/'){//过滤行注释
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
		else if (ch == ';') {//分号 
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
	if((f1=fopen("input.txt","rt"))==NULL) //打开文件失败
	{ 
		printf("文件打开失败！按任意键退出！\n"); 
		getch(); 
		exit(1); 
	} 
	if((f2=fopen("out.txt","wt+"))==NULL) //打开文件失败
	{ 
		printf("创建输出文件失败！按任意键结束！\n"); 
		getch();
		exit(1); 
	} 
	WordAna(f1,f2); //词法分析
	fclose(f1); //关闭文件
	fclose(f2); 
} 




