CC=g++
# -std=c++11 
CFLAGS=-Wall
CREQS=-lsfml-system -lsfml-window -framework GLUT -framework OpenGL
SRCROOT=src
BUILDROOT=build
TARGET=$(BUILDROOT)/RSim

all: RSim r

r:
	$(TARGET)

d:
	gdb $(TARGET)

cr: RSim r
	

cd: RSim d

RSim:
	$(CC) $(CFLAGS) $(CREQS) $(SRCROOT)/*.cpp -o $(TARGET)
