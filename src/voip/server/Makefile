CC= g++

CFLAGS= -g -Wall

LFLAGS= -llinphone -lmediastreamer

TARGET= server

OBJECTS:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : $(TARGET)

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

.PHONY: clean help configure config
