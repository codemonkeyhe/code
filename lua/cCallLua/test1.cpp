#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

static void stackDump(lua_State* L);

int  callScript(const uint64_t &sid, const string &script,
                const string &paramJson, string *resultJson) {
    int rCode = 0;
    string &msg = *resultJson;
    msg = "OK";
    //创建一个新的Lua虚拟机
    lua_State* L = luaL_newstate();
    do { 
        if (L == NULL) {
            rCode = -1001;
            msg = "{\"ErrMsg\":\"new state error!\"}";
            break;
        }
        //打开一些必要的库，比如print等
        luaL_openlibs(L);
        //加载函数  lua_pcall是执行函数，但不是真正意义上的函数调用，而是为了让函数为发现
        int error = luaL_loadbuffer(L, script.c_str(),script.size(),"XXXXX") || lua_pcall(L,0,0,0);
        if (error) {
            rCode = -1002;
            msg =  "{\"ErrMsg\":\"load func error!script!\"}";
            break;
        }
        //相当于把lua的函数runLua加到lua的全局变量L里面
        lua_getglobal(L, "runLua");
        //把参数压入堆栈
        lua_pushlstring(L, paramJson.c_str(), paramJson.size()); 
        //然后调用lua_call执行runLua函数
        //1, 2是指函数有1个参数和2个返回值。
        rCode = lua_pcall(L, 1, 2, 0); 
        printf( "%d: call script DONE!rCode: %d, sid: %llu\n", __LINE__, rCode,  sid); 
        if (rCode != 0) { //调用失败 
            if (lua_isstring(L, -1)) { //错误信息会放到栈顶
                msg = lua_tostring(L, -1);
            } else {
                ostringstream ss;
                ss << "{\"ErrMsg\":\"lua_pcall error!\", \"rCode\": " << rCode << "}";
                msg = ss.str();
            }
            printf( "%d: call script Error!rCode: %d, Param: %s, Result: %s\n", 
                 __LINE__, rCode, paramJson.c_str(), msg.c_str());
            break;
        }
        //函数返回结果默认放在栈顶，lua的return从右往左压栈，所以return int,string时,string在栈顶-1，int在栈下面-2
        if (!lua_isnumber(L, -2)) {
            rCode = -1003;
            ostringstream ss;
            ss << "{\"ErrMsg\":\"get stack[-1] error!\", \"Type\":\"";
            ss << lua_typename(L, lua_type(L, -1)) <<  "\"}";
            msg = ss.str();
            break;
        }
        if (!lua_isstring(L, -1)) {
            rCode = -1004;
            ostringstream ss;
            ss <<  "{\"ErrMsg\":\"get stack[-2] error!\", \"Type\":\"";
            ss << lua_typename(L, lua_type(L, -2)) <<  "\"}";
            msg = ss.str();
            break;
        }   
        //-1 :表示从栈顶取得返回值。
        // :表示从堆栈中弹出一个元素，runLua函数已经执行完毕，参数和函数本身已经出栈，堆栈中只有返回值。
        //0 是成功 非零失败
        rCode = lua_tointeger(L, -2);
        msg = lua_tostring(L, -1);
        printf("%d: call script SUCCESS!Return: %d, Param: %s, Result: %s\n", 
             __LINE__, rCode, paramJson.c_str(), msg.c_str()); 
    } while(0);
    if (rCode != 0) {
        stackDump(L);
        printf("%d: call script FAIL!Return: %d, Param: %s, Result: %s\n", 
              __LINE__, rCode, paramJson.c_str(), msg.c_str());
    }
    //清理堆栈所有元素
    lua_settop(L, 0);
    //销毁给定的Lua_State中的所有对象并释放state所占用的动态内存
    lua_close(L);
    return rCode;
}



/*
string  callScript(const string &script, const string &paramJson) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    int rCode = 0;
    string msg = "OK";
    //加载函数
    int error = luaL_loadbuffer(L,script.c_str(),script.size(),"XXXXX") || lua_pcall(L,0,0,0);
    if (error) {
        fprintf(stderr, "%s:load func error!ErrMsg : %s", __LINE__, lua_tostring(L,-1));
        lua_pop(L,1);
        return ""; 
    }   
    //相当于把lua的函数runLua加到lua的全局变量L里面
    lua_getglobal(L, "runLua");
    //接着把x和y参数压入堆栈
    lua_pushlstring(L, paramJson.c_str(), paramJson.size() ); 
    //然后调用lua_call执行add函数
    //1, 2是指函数有1个参数和2个返回值。
    //0表示成功 非0表示失败
    rCode = lua_pcall(L, 1, 2, 0); 
    cout << __LINE__ << "-1111111" << endl;
    if (rCode!=0) {
        //调用失败 
        if (lua_isstring(L, -1)) {
            //错误信息会放到栈顶
            cout << __LINE__ << "-1111111" << endl;
            msg = lua_tostring(L, -1);
        } else {
            ostringstream ss; 
            ss << "{\"ErrMsg\":\"lua_pcall error!\", \"rCode\": " << rCode << "}";
            msg = ss.str();
        }   
        return  msg;
    }   
    cout << __LINE__ << "-1111111" << endl;
    //函数返回结果默认放在栈顶，
    if (!lua_isnumber(L, -2)) {
        rCode = -3; 
        ostringstream ss; 
        ss << "{\"ErrMsg\":\"get stack[-1] error!\", \"Type\":\"";
        ss << lua_typename(L, lua_type(L, -1)) <<  "\"}";
        msg = ss.str();
        return msg;
    }   
    cout << __LINE__ << "-1111111" << endl;
    if (!lua_isstring(L, -1)) {
        ostringstream ss; 
        ss <<  "{\"ErrMsg\":\"get stack[-2] error!\", \"Type\":\"";
        ss << lua_typename(L, lua_type(L, -2)) <<  "\"}";
        msg = ss.str();
        return msg;
    }   
    cout << __LINE__ << "-1111111" << endl;
    // :表示从堆栈中弹出一个元素，因为此时add函数已经执行完毕，参数和函数本身已经出栈，堆栈中只有返回值。
    //-1 :表示从栈顶取得返回值。
    rCode = lua_tointeger(L, -2);
    msg = lua_tostring(L, -1);
    cout << __LINE__ << "-1111111" << endl;
    lua_pop(L, 1); 
    printf("call script success!Param: %s, rCode: %d Msg: %s",  paramJson.c_str(), rCode,  msg.c_str()); // test
    lua_close(L);
    cout << __LINE__ << "-1111111" << endl;
    return msg;
}
*/


int main(void) {
    if (0) {
        //读取变量
        // https://www.kancloud.cn/thinkphp/lua-guide/43808
        int w, h;
        lua_State* L = luaL_newstate();
        // 读取文件，将内容作为一个函数压栈
        // 执行栈顶函数，0个参数、0个返回值、无出错处理函数（出错时直接把错误信息压栈）
        int ret;
        ret = luaL_loadfile(L, "data.lua") || lua_pcall(L, 0, 0, 0);
        printf("Err1:%d\n", ret);
        lua_getglobal(L, "width");     // 将全局变量 width的值 压栈
        lua_getglobal(L, "height");    // 将全局变量 height的值 压栈
        if (!lua_isnumber(L, -2))      // 自顶向下第二个元素是否为数字
            printf("Err2\n");
        if (!lua_isnumber(L, -1))      // 自顶向下第一个元素是否为数字
            printf("Err3\n");
        w = lua_tointeger(L, -2);      // 自顶向下第二个元素转为整型返回
        h = lua_tointeger(L, -1);      // 自顶向下第一个元素转为整型返回
        printf("w=%d h=%d\n", w, h);
    }

    if (0) {
        //读取table
        int chinese, english;
        lua_State* L = luaL_newstate();
        if (luaL_loadfile(L, "data.lua") || lua_pcall(L, 0, 0, 0))
            printf("Err3\n");
        lua_getglobal(L, "score");       // 全局变量 score 压栈
        lua_pushstring(L, "chinese");    // 字符串 也就是表的第一个元素的key  压栈
        // 以自顶向下第二个元素为表、第一个元素为索引key取值，chinese索引弹栈，将索引对应的值80压栈
        lua_gettable(L, -2);
        if (!lua_isnumber(L, -1))        // 栈顶元素是否为数字
            printf("Err3\n");
        chinese = lua_tointeger(L, -1);
        lua_pop(L, 1);                   // 清理栈顶的80,弹出一个元素 (此时栈顶为 score 变量)

        //这一行与前面等价，即english这个key入栈，然后key出栈，把key对应的value，85压栈。 
        lua_getfield(L, -1, "english");  // Lua5.1开始提供该函数简化七八两行 -1是table所在的栈序号

        if (!lua_isnumber(L, -1))
            printf("Err3\n");
        english = lua_tointeger(L, -1);
        lua_pop(L, 1);                   // 如果就此结束，这一行弹不弹都无所谓了, 弹出85
        int  l = lua_gettop(L);    //此时栈顶只有一个元素 就是table
        printf("chinese=%d english=%d size=%d\n", chinese, english, l);
    }


    if (1) {
        //const char* buff = "print(\"hello\")";
        string script = "function runLua(param) return -1,param;  end";
        //string param = "{\"K\":\"V\"}";
        string param = "{\"uid\": \"1223490925\", \"cid\": \"1339897452\", \"sid\": \"1339897452\", \"bss_code\":\"ent-template-video\",\"business\":\"yy_anchor_business\", \"action\":\"report_play_config\"}";
        string result;
        int ret =  callScript(123, script, param, &result);
        cout << "ret:" << ret << " result:" << result << endl;
    }

    if (false) {
        const char* buff = "print(\"hello\")";
        int error;
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        error = luaL_loadbuffer(L,buff,strlen(buff),"line") || lua_pcall(L,0,0,0);
        int s = lua_gettop(L);
        cout << "Data=" << s << endl;
        if (error) {
            fprintf(stderr,"%s",lua_tostring(L,-1));
            lua_pop(L,1);
        }
        lua_close(L);
    }
    return 0;
}


// Lua 中有八种基本类型： nil, boolean, number, string, function, userdata, thread, and table. 
static void stackDump(lua_State* L) {
    ostringstream os; 
    os << "{begin dump lua stack:---";
    int i = 0;
    int top = lua_gettop(L);
    for (i = 1; i <= top; ++i) {
        os << "  Stack Level #"  << i << ": ";
        int t = lua_type(L, i); 
        switch (t) { 
            case LUA_TSTRING: {
                    os << lua_tostring(L, i) << "  ";
                }   
                break;
            case LUA_TBOOLEAN: {
                    os << lua_toboolean(L, i) << "  ";
                }   
                break;
            case LUA_TNUMBER: {
                    os << lua_tonumber(L, i) << "  ";
                }   
                break;
            default: {
                    os << lua_typename(L, t) << "  ";
                }   
                break;
        }    
    }   
    os << "---end dump lua stack}";
    printf( "%d, STACK INFO: %s\n", __LINE__, os.str().c_str());
} 
