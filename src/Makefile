.PHONY: main

CC = g++
CFLAGS = -g -Wall
OBJS = Message.o Router.o main.o

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

Message.o: Message.h Message.cpp
	$(CC) $(CFLAGS) -c Message.cpp

Router.o: Router.h Router.cpp
	$(CC) $(CFLAGS) -c Router.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

run:
	for file in in*.txt; do\
		./main $$file;\
	done

clean:
	rm -f Message.o Router.o main.o main
