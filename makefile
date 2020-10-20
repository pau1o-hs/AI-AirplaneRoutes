all:
	g++ main.cpp -g -W -o program lib/*.cpp

run:
	./program < entrada.txt