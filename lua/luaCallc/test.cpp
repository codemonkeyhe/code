#include <iostream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

static lua_State *L = NULL;

//在lua中被调用的c函数类型(lua_CFunction)
//typedef int (*lua_CFunction) (lua_State *L);
// C函数通过 Lua 中的堆栈来接受参数，参数以正序入栈（第一个参数首先入栈）。
static int get_sum(lua_State *L) {
    //lua_gettop(L)可以返回函数收到的参数个数。
    //第一个参数（如果有的话）在索引 1 的地方，而最后一个参数在索引 lua_gettop(L) 处
    int n = lua_gettop(L);
    double sum = 0;
    int i;
    for(i = 1; i <= n; ++ i) {
        if(!lua_isnumber(L, i)) {
            cout << "invalid argument i=" << i << endl;
        }else {
            sum += lua_tonumber(L, i);
        }
    }
    //当需要向 Lua 返回值的时候，C 函数只需要把它们以正序压到堆栈上（第一个返回值最先压入）
    lua_pushnumber(L, n);
    lua_pushnumber(L, sum);
    //然后返回这些返回值的个数 
    return 2;
}

/**
 * @brief
 * http://codingnow.cn/language/1524.html
 *
 */
int main() {
    // 创建一个新的独立的状态机(新版lua使用luaL_newstate代替lua_open)
   // L = lua_open();
    L = luaL_newstate();  
    // 打开所有标准lua库到指定的状态机
    luaL_openlibs(L);
    // 把 C 函数 get_sum 设到lua的全局变量 getSum 中，在lua文件中就可以使用getSum函数了。
    lua_register(L, "getSum", get_sum);
    //加载和运行指定lua文件，该lua文件里面可以调用getSum函数
    luaL_dofile(L, "lCallC.lua");
    lua_close(L);
    L = NULL;
    return 0;
}
