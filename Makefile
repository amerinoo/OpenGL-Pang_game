# Project name: Pang Game
# Version 1
# Student : Albert Eduard Merino Pulido

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -lglut -lGLU -lGL -lm -ljpeg -Wall -g

# Files to compile
CFILES = main.cpp vector3.cpp

# Files' headers
HFILES = vector3.h

# The build target executable:
TARGET = pang_game

ALL : $(TARGET)

$(TARGET): $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
