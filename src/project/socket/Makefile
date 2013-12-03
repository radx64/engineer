# the compiler: gcc for C program, define as g++ for C++
CC= g++
AR= ar rcs

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -pthreads
CFLAGS= -g -Wall

# compile library
TARGET= libtcp.a

OBJECTS:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	@echo "Compressing to "$(TARGET) "from" $(OBJECTS) 
	$(AR) $(TARGET) $(OBJECTS)

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
	@echo "     TARGET:" $(TARGET)

.PHONY: clean help configure config
