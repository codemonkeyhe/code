#!/bin/bash
#g++ -o test test.cpp
rm test

# 现代连接器在处理动态库时将链接时路径（Link-time path）和运行时路径（Run-time path）分开,
#用户可以通过-L指定链接时库的路径，
#通过-R（或-rpath）指定程序运行时库的路径，
#gcc -O2 -g -Wall -D_GNU_SOURCE -o test_hello.o -c test_hello.c -I. -I../src
#gcc -O2 -g -o test_hello test_hello.o -L../src -lzlog -lpthread -Wl,-rpath ../src

#生成.o文件
g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c -o test.o test.cpp -I../lib/zlog-master/src

#错误用法1 原理如下
#g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -L../lib/zlog-master/src -lzlog -lpthread

#  下面这样编译随便不会报错，成功生成可执行文件，但是并没有指定运行时动态库的路径，-L只是指定链接时库的路径。
#   如果运行时在通用的so库路径中找不到，则报错.解决办法就是把需要的so文件放入/etc/ld.so.conf/XX.conf中，然后ldconfig刷新缓存
#   monkey@bogon te]$g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -L../lib/zlog-master/src -lzlog -lpthread 
#   [monkey@bogon te]$./test
#   ./test: error while loading shared libraries: libzlog.so.1.2: cannot open shared object file: No such file or directory
#


#错误用法2 虽然指明了so的搜索路径 但是缺乏-lzlog，-lzlog优先使用libzlog.so，没有的话采用libzlog.a
#g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -L../lib/zlog-master/src/libzlog.so -lpthread

#正确用法1，显示指明静态链接时的so 和 运行时的so位置
#g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -L../lib/zlog-master/src -lzlog -lpthread  -Wl,-rpath ../lib/zlog-master/src

#正确用法2, --static指定使用静态libzlog.a文件
g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o --static -L../lib/zlog-master/src -lzlog -lpthread



#


