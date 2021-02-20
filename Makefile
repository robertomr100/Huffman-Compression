
all:
	g++ compress.cpp -std=c++11 -Wall -I /usr/local/boost/include

test:
	g++ test.cpp -std=c++11 -Wall -I /usr/local/boost/include

clean:
	rm a.out

