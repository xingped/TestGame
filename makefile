CC=g++
CFLAGS=-g -Wall -Wformat -Werror -static-libgcc -static-libstdc++

IDIR=./include
ODIR=obj
LDIR=./lib
LIBS=-lglfw -lopengl32 -lglew32

PCFLAGS=-L$(LDIR) $(LIBS) -I$(IDIR)

OBJS=gameobj.o graphics.o shaders.o

all: testgame

testgame: src/main.cpp gameobj.o graphics.o shaders.o
	$(CC) $(CFLAGS) src/main.cpp -o testgame.exe obj/gameobj.o obj/graphics.o obj/shaders.o $(PCFLAGS)

gameobj.o: src/gameobj.cpp include/gameobj.hpp graphics.o
	$(CC) -c $(CFLAGS) src/gameobj.cpp -o obj/gameobj.o obj/graphics.o $(PCFLAGS)

graphics.o: src/graphics.cpp include/graphics.hpp shaders.o
	$(CC) -c $(CFLAGS) src/graphics.cpp -o obj/graphics.o obj/shaders.o $(PCFLAGS)
	
shaders.o: src/shaders.cpp include/shaders.h
	$(CC) -c $(CFLAGS) src/shaders.cpp -o obj/shaders.o $(PCFLAGS)
	
clean:
	del obj\*.o