CC=clang++
CFLAGS=-std=c++11 -Wall# -Wfatal-errors
CREQS=-lsfml-system -lsfml-window -framework GLUT -framework OpenGL
SRCROOT=src
BUILDROOT=build
TARGET=$(BUILDROOT)/rsim

all: RSim r

r:
	$(TARGET)

d:
	gdb $(TARGET)

cr: RSim r
	

cd: RSim d

RSim:
	$(CC) $(CFLAGS) $(CREQS) $(SRCROOT)/*.cpp -o $(TARGET)
