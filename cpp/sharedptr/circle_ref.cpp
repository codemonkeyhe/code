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

    // demo1
    shared_ptr<A> sa(new A()); // sa.uc=1
    shared_ptr<B> sb(new B()); // sa.uc=1
    sa->pb = sb;  // sb.uc=2
    sb->pa = sa;  // sa.uc=2

    // demo2
    A* a = new A(); // a->pb.uc=0
    B* b = new B(); // b->pa.uc=0
    a->pb.reset(b); // a->pb.uc=1
    b->pa.reset(a); // b->pa.uc=1

    // demo3 
    shared_ptr<A> t(new A());  // t.uc=1
    t->pb = new B(); // t->pb.uc=1
    t->pb->pa = t;  //  t.uc=2 t->pb.uc=1  t->pb->pa.uc=2 



    A* a = new A();
    B* b = new B(); 
    {
        shared_ptr<A> sa;
        shared_ptr<B> sb;
        cout<<"sa use count:"<<sa.use_count()<<endl; //0
        cout<<"sb use count:"<<sb.use_count()<<endl; //0
        sa.reset(a);
        sb.reset(b);
        cout<<"sa use count:"<<sa.use_count()<<endl; //1
        cout<<"sb use count:"<<sb.use_count()<<endl; //1
        if(sa && sb)
        {
            sa->pb=sb; 
            sb->pa=sa;
            //sa->work();
            //sb->work();
            // 环形引用让refcount=2,因此智能指针析构时减1后变为1，不会调用delete函数，因此内存泄漏了。
            // 程序运行期间，可以看到没有调用dtor，说明没有delete内存
            // 但是这个例子说明力不够，因为sa和sb是外部的只能指针，而a和b内部的智能指针在对象A和B生命期结束时会自动析构，但a和b都是栈上对象，不手动调用delete是不会析构的。
            // 如果有个例子没有外部的sa和sb，只有内部pa和pb环形引用，依然会内存泄漏的,参见circle_ref2.cpp
        }
        //assert(sa.use_count()==1);
        cout<<"sa use count:"<<sa.use_count()<<endl; //2
        cout<<"sb use count:"<<sb.use_count()<<endl; //2
    }
    // sa sb已析构，递减计数，计数为0则delete
    assert(a!=nullptr);
    cout << "A.pb use_count=" << a->pb.use_count() << endl; //1
    cout << "B.pa use_count=" << b->pa.use_count() << endl; //1
    return 0;
}

