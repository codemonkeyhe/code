#include<iostream>
#include<memory.h>
using namespace std;
int prime[5000];
bool isPrime[10010];

void setPrime() {  // 设置1~10000里的质数表
	int i;
	int k;
    memset(isPrime, true, sizeof(isPrime));   
    isPrime[0] = isPrime[1] = false;   
    for(i = 2; i * i <= 10010; i++) {   
        if(isPrime[i]) {   
            for(k = 2; k * i < 10010; k++)    
                isPrime[k * i] = false;   
        }   
    }   
	k=0;
	for(i=0;i<10000;i++)
	{
		if(isPrime[i]){
			prime[k]=i;
			k++;
		}
	}
}  

int main(void)
{
	setPrime();
	int n;
	int i,j,k;
	int sum;
	while(cin>>n,n!=0)
	{
		k=0;
		i=0;
		j=0;
		sum=0;
		while(j<=2 || prime[j-1]+prime[j-2]<=n)
		{
			if(sum<n)
			{
				sum=sum+prime[j];
				j++;
			}
			else if(sum==n){
				k++;
				sum=sum-prime[i];
				i++;
			}
			else{
				sum=sum-prime[i];
				i++;
			}
		}
		if(isPrime[n] && n>3 ) k++;
		cout<<k<<endl;
	}
	return 0;
}

/*
The integers are between 2 and 10 000
2
3
17
41
20
666
12
53
0

1
1
2
3
0
0
1
2

*/