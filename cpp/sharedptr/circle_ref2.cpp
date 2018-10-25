#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <memory>
#include <assert.h>

using namespace std;

 
class B;
class A
{
public:
    shared_ptr<B> pb;
    void work();
 
    ~A()
    {
        cout << "A::~dtor" << endl;
    }

    void hey() {
        cout << "A::hey" << endl;
    }
};
 
class B
{
public:
    shared_ptr<A> pa;

    void work()
    {
        pa->hey();
    }
 

    ~B()
    {
        cout << "B::~dtor" << endl;
    }

    void hey() {
        cout << "B::hey" << endl;
    }
};


void A::work() {
    pb->hey();
}

int main(int argc, char** argv)
{

    A* a = new A(); //a->pb自动初始化为空指针
    B* b = new B(); 
    {
        cout << "A.pb use_count=" << a->pb.use_count() << endl; //0
        cout << "B.pa use_count=" << b->pa.use_count() << endl; //0
        a->pb.reset(b);
        b->pa.reset(a);
            // 这个例子没有外部的sa和sb，只有内部pa和pb环形引用，依然存在内存泄漏
            // 因为没有手动调用delete，也不会析构a和b，更不会触发a和b内部的pa和pb的析构了
        //assert(sa.use_count()==1);
        cout << "A.pb use_count=" << a->pb.use_count() << endl; //1
        cout << "B.pa use_count=" << b->pa.use_count() << endl; //1
    }
    assert(a!=nullptr);
    cout << "A.pb use_count=" << a->pb.use_count() << endl; //1
    cout << "B.pa use_count=" << b->pa.use_count() << endl; //1
    delete a;
    delete b;
    cout << "A.pb use_count=" << a->pb.use_count() << endl; //-1
    cout << "B.pa use_count=" << b->pa.use_count() << endl; //-1
    return 0;
}

