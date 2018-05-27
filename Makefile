CC = g++

CompileParms = -c -Wall -O3

OBJS = main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o kaartspel

main.o: main.cc
	$(CC) $(CompileParms)  main.cc

