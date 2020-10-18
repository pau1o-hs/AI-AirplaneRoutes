all:
	g++ main.cpp -g -W -o program lib/*.cpp

run:
	./program < case2.txt