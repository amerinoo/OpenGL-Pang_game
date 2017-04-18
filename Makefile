# Project name: Pang Game
# Version 1
# Student : Albert Eduard Merino Pulido

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -Wall -g -lglut -lGLU -lGL -lm -ljpeg

# Files to compile
CFILES = main.cpp vector3.cpp particle.cpp ball.cpp color.cpp forceGenerator.cpp \
		gravityForceGenerator.cpp plane.cpp particleContact.cpp ballPlaneColDetect.cpp \
		pangScenario.cpp ballBallColDetect.cpp character.cpp bullet.cpp player.cpp \
		humanPlayer.cpp game.cpp

# Files' headers
HFILES = vector3.h particle.h ball.h color.h forceGenerator.h \
	gravityForceGenerator.h plane.h particleContact.h ballPlaneColDetect.h \
	pangScenario.h ballBallColDetect.h character.h bullet.h player.h \
	humanPlayer.h game.h constants.h

# The build target executable:
TARGET = pang_game

ALL : $(TARGET)

$(TARGET): $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
