all:
#  静态连接
#   g++ -o test -Wall -pthread test.cpp -Wl,-rpath,../../../codeLive/bin/ -Wl,-rpath,../../../codeLive/lib/  -lpthread  -static  -I./libbson/  ./libbson-1.0.a -lrt  
#   动态连接rt 静态连接libson
	g++ -o test -Wall -pthread test.cpp -Wl,-rpath,../../../codeLive/bin/ -Wl,-rpath,../../../codeLive/lib/  -lpthread  -I./libbson/  -Wl,-Bstatic ./libbson-1.0.a -Wl,-Bdynamic -lrt  



