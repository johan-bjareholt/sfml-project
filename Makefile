
NAME=SFML\ project
CXX=g++

LIBS=-lsfml-graphics -lsfml-window -lsfml-system
INCLUDES=-I./include

CPPFLAGS =-std=c++11 -g
CPPFLAGS += $(LIBS)
CPPFLAGS += $(INCLUDES)
LDFLAGS	 = $(LIBS)

# File names
FILEN=main menu game scene graphics celestialobject drawgroup
# Prepend src/ directory to filenames
FILEL=$(patsubst %,src/%,$(FILEN))

SRC=$(patsubst %,%.cpp,$(FILEL))
OBJ=$(patsubst %,%.o,$(FILEL))

$(NAME): $(OBJ)
	mkdir -p ./bin
	$(CXX) $(LDFLAGS) $(OBJ) -o ./bin/$(NAME)

.PHONY: all
all:
	$(NAME)

.PHONY: clean
clean:
	rm src/*.o
