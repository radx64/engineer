# the compiler: gcc for C program, define as g++ for C++
CC= g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -pthreads
CFLAGS= -w -g `pkg-config --cflags gtkmm-3.0` 

LFLAGS= `pkg-config --libs gtkmm-3.0` -lpthread -lrt -L ../socket/ -ltcp -L ../voip/ -lvoip -llinphone -lmediastreamer
# the build target executable:
TARGET= client

OBJECTS:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : lib $(TARGET) 

$(TARGET) : $(OBJECTS)
	@echo "Linking "$(TARGET) "from" $(OBJECTS) 
	$(CC) -o $(TARGET) $(OBJECTS) $(LFLAGS)

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

lib:
	@echo "Preparing socket library"
	cd ../socket/ && make
	@echo "Socket library done"
	@echo "Preparing voip library"
	cd ../voip/ && make
	@echo "Socket voip done"

.PHONY: clean help configure config lib
