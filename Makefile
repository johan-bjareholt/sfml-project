
NAME=SFML\ project
CXX=g++
CPPFLAGS=-std=c++11 -g
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
INCLUDE=-I./include

SRC=src/main.cpp src/menu.cpp src/game.cpp src/scene.cpp src/graphics.cpp src/celestialobject.cpp


all:
	mkdir -p ./bin
	$(CXX) $(CPPFLAGS) $(INCLUDE) $(LIBS) $(SRC) -o ./bin/$(NAME)
