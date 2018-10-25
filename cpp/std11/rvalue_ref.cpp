#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

int main() {
    int &&rr1 = 42; // 正确，42是右值，rr1是变量，属于左值，但是其类型是右值引用 int&& 
    //int &&rr2 = rr1; //右值引用无法绑定到左值，也就是右值引用无法绑定到 一个右值引用类型的左值变量上(rr1)
    {
        int &&rr3 = std::move(rr1);
        cout << "rr3=" << rr3 << endl;
    }
    cout << " rr1=" << rr1 << endl;


    return 0;    
}

