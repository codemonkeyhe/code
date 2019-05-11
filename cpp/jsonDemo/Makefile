test: test.o
	g++ -g -O3 -std=c++0x  -Wall -o test test.o  -ljson_linux-gcc-4.6_libmt   -I/mnt/hgfs/gitPro/code/cpp/jsonDemo/jsoncpp-0.10.6/include/
test.o: test.cpp
	g++ -g -O3 -std=c++0x  -Wall -c test.cpp   -ljson_linux-gcc-4.6_libmt  -I/mnt/hgfs/gitPro/code/cpp/jsonDemo/jsoncpp-0.10.6/include/

all: 
	make clean; make

## g++ -g -O3 -std=c++0x -Wno-deprecated -Wall -o test test.o  -ljsoncpp  -I/usr/local/include/json/ -Wdeprecated-declarations
## 加了phony语句后，如果test文件不存在，执行删除时会报错，终止Make流程
## 所以用-rm test来忽略删除的错误,但是感觉依然不爽
## 用rm -f 好一点，直接忽略错误
.PHONY : clean
clean:
	rm  -f test
