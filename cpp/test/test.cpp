#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#include <typeinfo>
#include <string>
#include <iostream>

using namespace std;
/*
//用法示例
//ResultCallbackT<int, pp> obj(i);
//obj.onResult();

template<typename T,  void (*FP)(string&, T&)>
class ResultCallbackT {
public:
    ResultCallbackT(T &data):ref_data(data){
    };  
    void onResult()
    {   
        string ss("ResultCallbackT-result");
        FP(ss, ref_data);
    }   

private:
    T& ref_data;
};
*/


// ResultCallbackT2<int> a(i, pp);
// a.onResult();

template<typename T>
class ResultCallbackT2 {
public:
    typedef void (*FPTYPE)(string&, T&); //FPTYPE是类型名，类型是一个函数指针，void(*)(string&, T&)
    typedef void (FPTYPE1)(string&, T&); //FPTYPE1 也是个函数类型， 类型是 void (string&, T&)
    typedef void FPTYPE2(string&, T&);  //同上
    void FPTYPE3(string&, T&){}

    ResultCallbackT2(T &data, FPTYPE f):ref_data(data), funcptr(f){
    };  
    void onResult()
    {   
        string ss("ResultCallbackT2-result");
        funcptr(ss, ref_data);
    }   

/*
funcptr name=void (*)(std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)
FPTYPE name=void (*)(std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)
p1 name=void (std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)
FPTYPE1 name=void (std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)
p2 name=void (std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)
FPTYPE2 name=void (std::basic_string<char, std::char_traits<char>, std::allocator<char> >&, int&)

*/
    void onTest() {
        //FPTYPE1 p1 = *funcptr; 报错 function is initialized like a variable
        FPTYPE2 p1;  // 这里相当于函数声明，相当于  void p1(string&, T&);  因此需要在其他地方进行函数定义
        FPTYPE2 p2;
        cout << "funcptr name=" << typeid(funcptr).name() << endl;
        cout << "FPTYPE name=" << typeid(FPTYPE).name() << endl;
        cout << "p1 name=" << typeid(p1).name() << endl;
        cout << "FPTYPE1 name=" << typeid(FPTYPE1).name() << endl;
        cout << "p2 name=" << typeid(p2).name() << endl;
        cout << "FPTYPE2 name=" << typeid(FPTYPE2).name() << endl;

        //p1 = funcptr; //错误，禁止把指针付给非指针
        //p1 = *funcptr; //错误，函数之间不存在赋值操作，只有函数指针才可以 
        
        // p1无法直接调用，因为p1是变量名，相当于函数名字，只能间接调用
         // string ss("ResultCallbackT2-p1");
         // p1(ss, ref_data);  //ld returned 1 exit status 相当于p1这个函数没有定义

        string ss3("ResultCallbackT2-p3");
        FPTYPE1 &p3 = *funcptr;  //引用一个指针,但是类型不同
        p3(ss3, ref_data);
    }

private:
    T& ref_data;
    FPTYPE funcptr;
};


void pp(string& p1, int& p2) {
    cout << "p1=" <<  p1 << " p2=" << p2 << endl;
}


template<typename T>
inline 
void make_test(void (*FP)(string&, T&) , T& param ) {
    string res="make_test";
    FP(res, param);
    //ResultCallbackT<T, FP> temp(param);  FP编译报错，即使是C++ 11也报错，FP是一个变量名，类型是函数指针，
    return;
}  

template<typename T>
inline 
ResultCallbackT2<T>  make_callback(void (*FP)(string&, T&) , T& param ) {
    //ResultCallbackT2<T> temp(param, FP); 
    //return temp;
    return  ResultCallbackT2<T>(param, FP); 

}  


//#define DUPLICATE_KEY_UPDATE(column, cond) "#column = IF(#cond < values(#cond), values(#column), #column)"

#define DUPLICATE_KEY_UPDATE(column, cond) \
    "\"" #column "=IF(" #cond "<values("#cond "),values(" #column ")," #column ")\""


#define DUPLICATE_KEY_UPDATE_VER(column, usever) \
    ((usever ) ?   \
     ("\"" #column "=IF(ver<values(ver),values(" #column ")," #column ")\"") \
     : ("\"" #column "=values(" #column")\""))


void dsptime(const struct tm * ptm)  
{  
    string pxq[7]={"日","一","二","三","四","五","六"};  
    cout << ptm->tm_year+1900 << "年" << ptm->tm_mon+1 << "月" << ptm->tm_mday << "日 " ;  
    cout << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec <<" " ;  
    cout << " 星期" << pxq[ptm->tm_wday] << " 当年的第" << ptm->tm_yday << "天 " << endl;  
}  

const char* f() {
    //return NULL;
    return "123";
}



string PurifyString(const string &str) {
    string::iterator it;
    string res = str; 
    for (it = res.begin(); it != res.end(); ++it) {
        if (*it == ':') {
            *it = '-'; 
        }    
    }    
    return res;
}



int main() {
    cout << "begin test" << endl;
    string ss = "XXXXXXX:XXXX:XXXX";
    cout << PurifyString(ss) << endl;


    //pp(t, i);
    //make_test(pp, i);

    //ResultCallbackT2<int> a(i, pp);
    //a.onResult();
    //a.onTest();
    //cout << DUPLICATE_KEY_UPDATE(cid, ver) << endl;
    //cout << DUPLICATE_KEY_UPDATE_VER(cid, 0) << endl;
    //cout << DUPLICATE_KEY_UPDATE_VER(cid, 1) << endl;
    //
    if (0) {
    string msg;
    msg = "query-";
    const char * str = f();
    if (str != NULL)
        msg += str;
    str = f();
    if (str != NULL)
        msg += str;
    cout << msg << endl;
    }

    if (0) {
        volatile int i = 3;
        int j = 0;
        j = (i++) + (++i) + (i++);
        cout << j << endl;

        volatile int n = 3;
        int v = 0;
        v= (--n)+(++n);
        cout << v  << endl;

        int m = 3;
        int k = (++m)+m;
        cout << k << endl;

        time_t now = time(NULL);
        cout << now << endl;
        tm* local = localtime(&now);
        dsptime(local);
        cout << "hello" << endl;


    }

    //bug();
    return 0;
}

