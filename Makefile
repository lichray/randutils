# ccconf example CXX=g++49 CXXFLAGS+=-Wall -std=c++1y -O2
CXX      = g++49
CXXFLAGS = -Wall -std=c++1y -O2

.PHONY : all clean
all : example
clean :
	rm -f example example.o tags

tags : *.h example.cc
	ctags *.h example.cc

example : example.o
	${CXX} ${LDFLAGS} -o example example.o
example.o: example.cc randutils.hpp
