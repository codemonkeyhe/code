#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <json/json.h>

using namespace std;


static void printValueTree( FILE *fout, Json::Value &value, const std::string &path = ".");

int main() {
/*
01430 bool 
01431 Value::isObject() const
01432 {
01433    return type_ == nullValue  ||  type_ == objectValue;
01434 }

 Json::nullValue,

//Examples:
Json::Value null_value; // null
Json::Value arr_value(Json::arrayValue); // []
Json::Value obj_value(Json::objectValue); // {}

Json::Value和C++中的map有一个共同的特点，就是当你尝试访问一个不存在的 key 时，会自动生成这样一个key-value默认为null的值对。也就是说
root["anything-not-exist"].isNull(); //false
root.isMember("anything-not-exist"); //true

http://jsoncpp.sourceforge.net/class_json_1_1_value.html#da6ba1369448fb0240bccc36efaa46f7

* */
    if (true) {
        Json::Value v;  
        //v["appkey"] = "1234";
        v["appkey"].append("test");
        v["appkey"].append("tes123");
        cout <<"TOString=" << v.toStyledString() << endl;
    }

    if (false) {
        //string json_str = "{\"key1\":\"v1\", \"K2\":\"v2\",\"k3\":\"v3\"}";
        string json_str="{}";
        Json::Value value;  
        Json::Reader reader;  
        Json::Value::iterator iter;  
        Json::Value::Members members;  
        bool parsingSuccessful = reader.parse( json_str, value );  
        if (parsingSuccessful) 
        {  
            members = value.getMemberNames();  
            for (Json::Value::Members::iterator it = members.begin();  it != members.end(); ++it) {  
                std::string name = *it;  
                std::string value_str = value[name].asString();  
                cout<<name<<":"<<value_str<<endl;  
            }  
            cout <<"TOString=" << value.toStyledString() << endl;
        } else {
            cout << "parse fail " << endl;
        } 
    }

    if (false) {
        Json::Value j;
        Json::Reader reader; 
        string test =  "{\"key\": null}";
        if(!reader.parse(test,  j)) { 
            cout << "parse err!" <<endl;
            return -1;
        }
        if (j["key"].isObject()) {
            cout << "key isObject" <<endl;
        } else {
            cout << "key is NOT Object" <<endl;
        }
        if (j["XXX"].isObject()) {
            cout << "XXX isObject" <<endl;
        } else {
            cout << "XXX is NOT Object" <<endl;
        }

        if (j["key"].isArray()) {
            cout << "key is Array" <<endl;
        } else {
            cout << "key is NOT Array" <<endl;
        }
        if (j["XXX"].isArray()) {
            cout << "XXX is Array" <<endl;
        } else {
            cout << "XXX is NOT Array" <<endl;
        }
        Json::Value null_value; // nul
        if (null_value.isObject()) {
            cout << "nullValue is Object" <<endl;
        } else {
            cout << "nullValue is NOT Object" <<endl;
        }
        if (null_value.type() == Json::nullValue) {
            cout << "====nullValue" <<endl;
        } else {
            cout << "!!nullValue" <<endl;
        }


        //j["nullValue"] = null_value;
        //if (j["nullValue"].isObject()) {
        //cout << "nullValue is Object" <<endl;
        //} else {
        //cout << "nullValue is NOT Object" <<endl;
        //}

    }


    if (false) {
        Json::Value j;
        Json::Reader reader; 
        string test =  "{\"$or\":[{\"sid\":80102494},{\"sid\":47258782}]}";
        if(!reader.parse(test,  j)) { 
            return -1;
        }
        cout  << "first size=" << j.size() << endl; 
        cout  << "r *begin.key=" << j.begin().key() << endl; 
        cout  << "r *begin.val=" <<  (*j.begin())<< endl; 
        cout  << "o *begin.TYPE=" <<  (*j.begin()).type()<< endl;   //6 表示数组

        test ="{\"id22\":2,\"name22\":\"KKKKKK\", \"z33333\":3}"; 
        if(!reader.parse(test,  j)) { 
            return -1;
        }
        cout  << "o size=" << j.size() << endl; 
        //注意，这里并不是打印整个json结构体，begin()返回指向第一个元素的iter,对该iter取值相当于取得第一个元素的val。
        cout  << "o *begin=" <<  (*j.begin()).toStyledString() << endl; 
        cout  << "o *begin.key=" << j.begin().key() << endl; 
        cout  << "o *begin.val=" <<  (*j.begin())<< endl; 
        cout  << "o *begin.TYPE=" <<  (*j.begin()).type()<< endl; 

        test = "[{\"id\":1,\"name\":\"kurama\"}, {\"id22\":2,\"name22\":\"KKKKKK\"}]"; 
        if(!reader.parse(test,  j)) { 
            return -1;
        }
        cout  << "size=" << j.size() << endl; 
        cout  << "*begin=" << (*j.begin()).toStyledString() << endl; 
        cout  << " *[(*begin).begin]=" <<  (*(*j.begin()).begin()).toStyledString() << endl; 


    }

    if (false) {
        Json::Value root;
        Json::Value arrayObj;
        Json::Value item;
        for (int i=0; i<10; i++)
        {
            item["key"] = i;
            arrayObj.append(item);
        }

        root["key1"] = "value1";
        root["key2"] = "value2";
        root["array"] = arrayObj;
        root.toStyledString();
        std::string out = root.toStyledString();
        std::cout << out << std::endl;
    }
    if (false) {
        string test ="{\"id\":1,\"name\":\"kurama\"}"; 
        Json::Reader reader; 
        Json::Value value; 
        if(reader.parse(test,value)) { 
            if(!value["id"].isNull()) { 
                cout << value["id"].asInt() << endl; 
                cout << value["name"].asString()<< endl; 
            } 
        } 
        // Json::FastWriter用来快速输出Json对象的值
        Json::FastWriter writer;
        cout << writer.write(value)<< std::endl;
        //Json::StyledWriter用来格式化输出Json对象的值。
        Json::StyledWriter writer2;
        std::cout << writer2.write(value) << std::endl;
    }

    if (false) {
        Json::Value value;
        ifstream in("public.json");
        string str;
        string msg;
        if(in.is_open()) {
            while(in>>str)
                msg += str;
        }
        Json::Reader reader;
        int ret = reader.parse(msg,value);
        if(ret) { 
            string url = value["text"].asString();
            string date = value["created_at"].asString();
            cout<<value["privacy"].asInt()<<endl;
            cout<<url<<"\t"<<date<<endl;
        }
        in.close();
    }


    for (;false;) {
        Json::Value objArray;
        string test ="[{\"id\":1,\"name\":\"kurama\"}, {\"id22\":2,\"name22\":\"KKKKKK\"}]"; 
        Json::Reader reader; 
        if(!reader.parse(test,objArray)) { 
            break;
        }

        Json::Value::Members member;
        //Members  这玩意就是vector<string>，typedef了而已
        //遍历数组的迭代器
        Json::Value::iterator itr;
        for ( itr = objArray.begin(); itr != objArray.end(); itr++) {
            //获取对象的所有key的名字
            member = (*itr).getMemberNames();
            Json::Value::Members::iterator iter;
            for (iter = member.begin(); iter != member.end(); iter++) {
                string str_temp = (*itr)[(*iter)].asString();
                cout << "K=" << (*iter) << "\t V=" << str_temp <<endl;
            }
        }
        break;
    }

    if (false) {
        FILE *fp = NULL;
        fp = fopen("./test.txt", "w+"); 
        //string test ="[{\"id\":1,\"list\":\"[3,4,5,6]\"}, {\"id22\":{\"array\":[\"aaa\", \"bbb\"]},\"name22\":\"KKKKKK\"}]"; 
        string test ="{\"id22\":{\"array\":[\"aaa\", \"bbb\"]},\"name22\":\"KKKKKK\"}"; 
        Json::Reader reader; 
        Json::Value value;
        if(!reader.parse(test,value)) { 
            return -1;
        }
        for (Json::Value::iterator _it = value.begin(); _it != value.end(); ++_it) {
            cout << "KK=" << _it.key() << " VType=" << (*_it).type() << " VV=" << (*_it) << endl;
        }
        if (false) {
            printValueTree(fp, value);
        }
    }
    return 0;
}


/**
 * @brief 迭代打印json结构体


 Json::ValueType有8种，以下是定义。 
 enum Json::ValueType
Enumerator: 
nullValue 　　    'null' value 
intValue 　　　　signed integer value 
uintValue 　　    unsigned integer value 
realValue 　　    double value 
stringValue 　　  UTF-8 string value. 
booleanValue 　　bool value 
arrayValue 　　   array value (ordered list) 
objectValue 　　 object value (collection of name/value pairs).


 * @param fout
 * @param value
 * @param path
 */
static void printValueTree( FILE *fout, Json::Value &value, const std::string &path) 
{ 
    switch ( value.type() ) 
    { 
    case Json::nullValue:    
        fprintf( fout, "%s=null\n", path.c_str() );
        break;
    case Json::intValue:
        fprintf( fout, "%s=%d\n", path.c_str(), value.asInt() );
        break;
    case Json::uintValue:
        fprintf( fout, "%s=%u\n", path.c_str(), value.asUInt() );
        break;
    case Json::realValue:
        fprintf( fout, "%s=%.16g\n", path.c_str(), value.asDouble() );
        break;
    case Json::stringValue:
        fprintf( fout, "%s=\"%s\"\n", path.c_str(), value.asString().c_str() );
        break;
    case Json::booleanValue:
        fprintf( fout, "%s=%s\n", path.c_str(), value.asBool() ? "true" : "false" );
        break;
    case Json::arrayValue:
        {
            fprintf( fout, "%s=[]\n", path.c_str() );
            int size = value.size();
            for ( int index =0; index < size; ++index )
            {
                static char buffer[16];
                sprintf( buffer, "[%d]", index );
                printValueTree( fout, value[index], path + buffer );
            }
        }
        break;
    case Json::objectValue:
        {
            fprintf( fout, "%s={}\n", path.c_str() );
            Json::Value::Members members( value.getMemberNames() );
            sort( members.begin(), members.end() );
            string suffix = *(path.end()-1) == '.' ? "" : ".";
            for ( Json::Value::Members::iterator it = members.begin(); it != members.end();         ++it )
            {
                const string &name = *it;
                printValueTree( fout, value[name], path + suffix + name );
            }
        }
        break;
    default:
        break; 
    } 
}



