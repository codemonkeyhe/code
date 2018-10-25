PREFIX=/home/yy

test: test.o
	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -llua -ldl   -L$(PREFIX)/codeLive/bin -I$(PREFIX)/codeLive/common/lua   -Wl,-rpath,$(PREFIX)/codeLive/bin 
#	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o -llua -ldl   -L$(PREFIX)/codeLive/lib -I$(PREFIX)/codeLive/common/lua   

test.o: test.cpp
	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c test.cpp  -I$(PREFIX)/codeLive/common/lua  
# 	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c test.cpp  -llua  -L$(PREFIX)/codeLive/bin -I$(PREFIX)/codeLive/common/lua  -Wl,-rpath,$(PREFIX)/codeLive/bin 
#	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c test.cpp  -llua  -L$(PREFIX)/codeLive/lib -I$(PREFIX)/codeLive/common/lua

test1: test1.o
	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test1 test1.o -llua -ldl -L$(PREFIX)/codeLive/lib   -I$(PREFIX)/codeLive/common/lua
test1.o: test1.cpp
	g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c test1.cpp -llua -L$(PREFIX)/codeLive/lib -I$(PREFIX)/codeLive/common/lua

all: 
	make clean; make
## g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -c test.cpp -I/home/monkey/lua/lua-5.3.4/src -llua
## 加了phony语句后，如果test文件不存在，执行删除时会报错，终止Make流程
## 所以用-rm test来忽略删除的错误,但是感觉依然不爽
## 用rm -f 好一点，直接忽略错误
.PHONY : clean
clean:
	rm  -f test
	rm  -f test.o
