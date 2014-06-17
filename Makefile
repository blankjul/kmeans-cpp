# Makefile

CPP = g++
CPPFLAGS = -g -Wall
LDFLAGS = -lm
EXEC = run

SOURCES = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,bin/%.o,$(SOURCES))

# Compile the program.
kmeans : $(OBJ)
	$(CPP) $(CPPFLAGS) -o kmeans $(OBJ) $(LDFLAGS)

bin/%.o: src/%.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

# command to be executed.
clean:
	rm -f $(EXEC) $(OBJ)

