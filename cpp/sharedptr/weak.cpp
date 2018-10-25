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
    weak_ptr<B> pb;
    //shared_ptr<B> pb;
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
    //weak_ptr<A> pa;
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
    shared_ptr<B> tmp = pb.lock();
    if (tmp) {
        tmp->hey();
    }
}

int main(int argc, char** argv)
{

    A* a = new A();
    B* b = new B(); 
    {
        shared_ptr<B> sb(b);
        shared_ptr<A> sa(a);
        if(sa && sb)
        {
            sa->pb=sb;
            sb->pa=sa;
            sa->work();
            sb->work();
        }
        //assert(sa.use_count()==1);
        cout<<"sa use count:"<<sa.use_count()<<endl; //2
        cout<<"sb use count:"<<sb.use_count()<<endl; //1
    }
    // sa sb已析构，递减计数，计数为0则delete
    assert(a!=nullptr);
    cout << "A.pb use_count=" << a->pb.use_count() << endl; //1
    cout << "B.pa use_count=" << b->pa.use_count() << endl; //1
    return 0;
}

