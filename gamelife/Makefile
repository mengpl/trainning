
dest = gameoflifeut
objects = unittest.o gameoflife.o

CC = g++
CPPFLAGS = -O2 -fpic -ggdb
CPPMICRO =
SUFFIX = 

.PHONY:all

all:$(dest) 

$(dest):$(objects)
	$(CC) $(CPPFLAGS) $(CPPMICRO) $(objects) -o $(dest)	

gameoflife.o:gameoflife.cpp 
unittest.o:unittest.cpp


.PHONY:clean
clean:
	rm -rf $(objects) $(dest)