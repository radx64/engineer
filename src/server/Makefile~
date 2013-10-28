MUDUO_DIRECTORY ?= /home/radek/Pulpit/proj-inz/engineer/src/build/debug-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib


# the compiler: gcc for C program, define as g++ for C++
CC= g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -pthreads
CFLAGS= -g -Wall -I$(MUDUO_INCLUDE) -L$(MUDUO_LIBRARY)

LFLAGS= -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt 
# the build target executable:
TARGET= server

OBJECTS:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@echo "Linking "$(TARGET) "from" $(OBJECTS) 
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJECTS)

%.o : %.cpp
	@echo "Compiling" $< "to" $@
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(TARGET) $(wildcard *.o) -f

help:
	@echo "To compile and link program just make ;)"

configure: config
config:
	@echo "Make configuration:"
	@echo "     CFLAGS:" $(CFLAGS)
	@echo "     LFLAGS:" $(LFLAGS)
	@echo "     TARGET:" $(TARGET)

.PHONY: clean help configure config
