#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <functional>


using namespace std;
using namespace std::placeholders;

#define  logInfo(s) cout << "["<<__FILE__<<":"<<__LINE__<<": "<<__FUNCTION__<<"] " << s << endl;


int f(int, char, double);

int main()
{

    if (true) {
        printf("\033[31;4mRed Underline Text\033[0m\n");
        //printf("#033[31m ERROR [main.go:20 main]#033[0m ");
        printf("\033[31;4m ERROR [main.go:20 main]\033[0m ");
    }

    cout << "hello" << endl;
    //f(1, 'c', 3.14);
    //auto ff = bind(f, _1, 'c', 1.2);
    //int x = ff(6);

    //auto frev = bind(f, _3, _2, _1);
    //int rev= frev(1.2, 'c', 7);

    //auto f2=bind<int>(f, 7, 'c', _1);
    //int xx = f2(1.2);
    //f(7, 'c', 1.2)

        

    return 0;
}


int f(int i, char c, double d)
{
    char buffer[200];
    sprintf(buffer, "1st=%d, 2nd=%c 3rd=%f", i, c, d);
    string str(buffer);
    logInfo(str);
    return 0;
}
