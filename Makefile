OBJSRCS = $(wildcard *.cc)
OBJS    = $(OBJSRCS:.cc=.o)

all: main

%.o: %.cc
	g++ -Wall -Wpedantic -Werror -c -std=c++17 -I. -I$(ROOTSYS)/include $< -o $@

main: $(OBJS)
	g++ -L$(ROOTSYS)/lib -lCore -o main $(OBJS)

clean:
	rm $(OBJS)
