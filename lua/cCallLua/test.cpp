#include <iostream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

/*
 *
 * http://gamedevgeek.com/tutorials/calling-lua-functions/
 * http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/
 *
 */

static lua_State *L = NULL;

static void stackDump(lua_State* L){
    cout<<"\nbegin dump lua stack"<<endl;
    int i = 0;
    int top = lua_gettop(L);
    for (i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: {
                    printf("'%s' ", lua_tostring(L, i));
                }
                break;
            case LUA_TBOOLEAN: {
                    printf(lua_toboolean(L, i) ? "true " : "false ");
                }break;
            case LUA_TNUMBER: {
                    printf("%g ", lua_tonumber(L, i));
                }
                break;
            default: {
                    printf("%s ", lua_typename(L, t));
                }
                break;
        }
    }
    cout<<"\nend dump lua stack"<<endl;
}



/**  
void lua_call (lua_State *L, int nargs, int nresults);
* @brief 

它的功能是调用一个函数，需要遵循以下协议：
首先，要调用的函数应该被压入堆栈；
接着把需要传递给这个函数的参数按正序压栈 ； 这是指第一个参数首先压栈。
最后调用一下lua_call； nargs 是你压入堆栈的参数个数。 
当函数调用完毕后，所有的参数以及函数本身都会出栈。
而函数的返回值这时则被压入堆栈。
返回值的个数将被调整为 nresults 个， 除非 nresults 被设置成 LUA_MULTRET。 在这种情况下，所有的返回值都被压入堆栈中。 
Lua 会保证返回值都放入栈空间中。 
函数返回值将按正序压栈（第一个返回值首先压栈）， 因此在调用结束后，最后一个返回值将被放在栈顶。

*/
int ladd(int x, int y) {
    int sum;
    //把全局变量 name 里的值压入堆栈.
    //这里lua_getglobal(L, “add”)把add函数压入堆
    //相当于把lua的函数add加到lua的全局变量L里面
    lua_getglobal(L, "add");
    //接着把x和y参数压入堆栈
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    //然后调用lua_call执行add函数
    //2,1是指函数有两个参数和一个返回值。
    int err = lua_pcall(L, 2, 1, 0);
    if (err!= 0 ) {
        fprintf(stderr, "%s:call func error!ErrCode : %d\n", __func__, err);
        if (lua_isstring(L, -1)) {
            fprintf(stderr, "%s:call func error!ErrMsg : %s\n", __func__, lua_tostring(L,-1));
        }
        stackDump(L);
        return -1;
    }
    //lua_call(L, 2, 1);
    //-1 :表示从栈顶取得返回值。
    sum = (int)lua_tointeger(L, -1);
    // :表示从堆栈中弹出一个元素，因为此时add函数已经执行完毕，参数和函数本身已经出栈，堆栈中只有返回值。
    lua_pop(L, 1);
    return sum;
}

/**
 * @brief
 * http://codingnow.cn/language/1530.html
 * http://codingnow.cn/language/1524.html
 *
 */
int main() {

    // 创建一个新的独立的状态机(新版lua使用luaL_newstate代替lua_open)
    //L = lua_open();
    L = luaL_newstate();  
    cout << "begin" << endl;

    // 打开所有标准lua库到指定的状态机
    luaL_openlibs(L);
    // 加载和运行指定lua文件，该lua文件只是定义了一个函数,并没有执行
    int err = luaL_dofile(L, "sum.lua");
    cout << "load ret=" << err << endl;
    if (err!= 0 ) {
        fprintf(stderr, "%s:load func error!ErrCode : %d\n", __func__, err);
        if (lua_isstring(L, -1)) {
            fprintf(stderr, "%s:load func error!ErrMsg : %s\n", __func__, lua_tostring(L,-1));
        }
    }

    int sum = ladd(10, 20);
    cout << "sum=" << sum << endl;
    lua_close(L);
    L = NULL;
    return 0;
}
