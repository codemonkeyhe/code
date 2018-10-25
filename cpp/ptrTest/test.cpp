#include <iostream>
using namespace std;


void hi() {
    cout << "Global hi" << endl;
}

class Test
{
public:
    typedef void (Test::*pFUN)();

    void hi() {
        cout << "Inner hi" << endl;
    }

    void sayHi(){
        hi();
        ::hi();
    }

    void func1()
    {
        func2(&Test::func3); //把func3的指针传递给func2
    }
    void func2(pFUN pfun)
    {
        (this->*pfun)();
    }
    void func3()
    {
        cout<<"Test func3."<<endl;
    }
};


/**
* @brief 普通函数指针，不等于类成员指针
*
* @param pf
*/
void fun4(void (*pf)()) {
    cout << "out fun4" << endl;
    (*pf)();
}

void fun5(void (Test::*pObjF)()) {
    cout << "out fun5" << endl;
    Test obj5;
    (obj5.*pObjF)();
}


/**
* @brief http://blog.sina.com.cn/s/blog_4298002e0100euh8.html
*
* @return 
*/
int main()
{
    Test obj;
    obj.sayHi();

    //类成员指针 ,指向类成员函数
    void (Test::*pfun)() = &Test::func3; //把func3的指针赋给pfun

    Test *pb=&obj;
    // .*和->*是两个新的操作符。能够使我们将成员指针绑定到实际对象。它们的左操作数必须是类类型对象或者是类类型指针，右操作数是该类型的成员指针。
    (obj.*pfun)();
    (pb->*pfun)();
    obj.func1();
    obj.func2(pfun); //把pfun传递给func2

    //向普通函数传递类成员函数指针 这样不行，
    //fun4(pfun);
    //可以通过bind来完成

    fun5(pfun);

    cin.get();
    return 0;
}
