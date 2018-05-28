CC = g++

CompileParms = -c -Wall -O3

OBJS = main.o

kaartspel: $(OBJS)
	$(CC) $(OBJS) -o $@

main.o: main.cc
	$(CC) $(CompileParms)  main.cc

