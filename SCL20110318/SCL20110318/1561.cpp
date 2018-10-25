#include<iostream>
#include<memory.h>
using namespace std;

bool Prime[105001];

void PrimeTable()
{
	int i,j;
	memset(Prime,true,sizeof(Prime));
	Prime[0]=Prime[1]=false;
	for(i=2;i*i<=105000;i++)
	{
		if(Prime[i]){ // 如果I是素数，求它的倍数肯定不是素数
			for(j=2;j*i<=105000;j++)
			{
				Prime[i*j]=false;
			}
		}
	}
}


int main(void)
{
	PrimeTable();
	int n;
	int i=2;
	int k=0;
	cin>>n;
	while(k<n){
		if(Prime[i]){
			k++;
		}	
		i++;	
	}
	cout<<i-1<<endl;
	return 0;
}


/*
30 
113

*/

//#include<iostream>
//#include <stdio.h>
//#include <math.h>
//using namespace std;
//#define MAXLEN 110010
//int isPrime[MAXLEN];
//int prime[10000];
//void sieve(int arr[], int len)
//{    int i, j;   
//float sqrt_len = sqrt((float)len);  
//for(i = 2; i < len; i++)     
//arr[i] = 1;   
//for(i = 2; i < sqrt_len; i++)    
//{       
//	if (arr[i])       
//{     
//	for (j = i; j*i <= len; j++)           
//		arr[j * i] = 0;        }    }  
//int cnt = 0;    prime[0] = 1;  
//for(i = 2; i < len; i++)    {       
//	if(arr[i] == 1)        {         
//		prime[++cnt] = i;           
//		if(cnt == 10000)              
//			break;      
//	}    
//}
//}
//int main(){
//	sieve(isPrime, MAXLEN);  
//	int n;  
//	scanf("%d", &n); 
//	printf("%d\n", prime[n]);   
//	return 0;
//}