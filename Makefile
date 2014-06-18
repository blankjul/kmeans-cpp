# Makefile

CPP = g++
CPPFLAGS = -g -Wall
LDFLAGS =
EXEC = run

SOURCES = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

# Compile the program.
kmeans : $(OBJ)
	$(CPP) $(CPPFLAGS) -o bin/kmeans $(OBJ) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

# command to be executed.
clean:
	rm -f $(EXEC) $(OBJ)

