-- local cjson = require("cjson"); 两种方法都可以，同下面
local cjson = require "cjson"

function add(x, y)
    return x+y;
end

function runLua(param) 
local obj = {
    name = "自定义",
    data = param,
};
local jsonStr = cjson.encode(obj);
print(jsonStr);
return 0,jsonStr;  
end

pa = "{uid:XXX}"
print(runLua(pa))

