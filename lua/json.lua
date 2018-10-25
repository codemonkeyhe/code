--local cjson = require("framework.shared.json") 
--local cjson = require("json") 
local cjson = require("cjson") 

function tt()
  local json_data = '{"name":"tom", "age":"10"}' 
  local unjson = cjson.decode(json_data)  
  print(unjson["name"])  
  local json_data2 = cjson.encode(unjson)  
  print(json_data2)  
  print("Hello World")
end


tt()
