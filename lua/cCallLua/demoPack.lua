--local cjson = require "cjson" function runLua(param) local obj = { name = "test", data = param, }; local jsonStr = cjson.encode(obj); print(jsonStr); return 0,jsonStr;  end  
--local cjson = require "cjson" function runLua(param) local obj = { name = "test", data = param, }; local jsonStr = cjson.encode(obj); --print(jsonStr); return 0,jsonStr; end 
local cjson = require "cjson" function runLua(param) local obj = { name = "test", data = param, }; local jsonStr = cjson.encode(obj); --[[print(jsonStr);]] return 0,jsonStr; end 
runLua("123")
print("HI")



