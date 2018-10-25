all: test 

test: src/b.o
	#g++ src/main.cpp  src/b.o -I./h/  -static -I../a/h/ -la -L../a/lib/  -o $@
	g++ src/main.cpp  src/b.o -I./h/  -static -I../a/h/ ../a/lib/liba.a -o $@

src/b.o: src/b.cpp
	g++ src/b.cpp -I./h/  -c -o $@ 

clean:
	rm test
	rm src/*.o


