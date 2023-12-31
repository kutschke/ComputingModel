OBJSRCS = $(wildcard *.cc)
OBJS    = $(OBJSRCS:.cc=.o)

INCSRCS = $(wildcard *.hh)


INCS= -I. -I$(FHICLCPP_INC) -I$(CETLIB_INC) -I$(CETLIB_EXCEPT_INC) -I$(ROOTSYS)/include
LIBS= -L$(FHICLCPP_LIB) -L$(CETLIB_LIB) -L$(CETLIB_EXCEPT_LIB) -L$(ROOTSYS)/lib -lCore -l fhiclcpp -l fhiclcpp_types -l cetlib -l cetlib_except
ROOTLIBS=  -L$(ROOTSYS)/lib -lHist -lRIO -lCore

all: main

%.o: %.cc
	g++ -Wall -Wpedantic -Werror -c -std=c++17 $(INCS) $< -o $@

main: $(OBJS)
	g++  -o main $(LIBS) $(ROOTLIBS) $(OBJS)

clean:
	rm $(OBJS) main





