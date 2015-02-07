CC=g++
CLFLAG=-framework OpenCL
CPPFLAG=-Wall
LINK_FLAG=$(CLFLAG)

all: compile

%.o: %.cpp
	$(CC) -c $(CPPFLAG) -o $@ $<

compile: clut.o compile.o
	$(CC) $(LINK_FLAG) $^ -o $@
